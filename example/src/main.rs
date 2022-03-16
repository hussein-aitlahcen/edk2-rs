#![no_main]
#![no_std]
#![feature(alloc_error_handler)]

use alloc::vec::Vec;
use core::alloc::Layout;
use core::fmt::Display;
use cstr_core::*;
use edk2_rs::*;
use static_alloc::Bump;
use widestring::*;
#[macro_use]
extern crate alloc;

#[global_allocator]
static X: Bump<[u8; 1 << 16]> = Bump::uninit();

#[alloc_error_handler]
fn alloc_error_handler(_: Layout) -> ! {
    loop {}
}

fn print<T: Display>(x: T) {
    unsafe {
        AsciiPrint(format!("{}\n\0", x).as_ptr());
    }
}

#[derive(Copy, Clone, Debug)]
enum ProgramError {
    NoContentLength,
}

#[derive(Copy, Clone, Debug)]
enum Error {
    Api(Status),
    Program(ProgramError),
}

#[derive(Copy, Clone, Debug)]
struct Status(EFI_STATUS);

impl From<EFI_STATUS> for Status {
    fn from(s: EFI_STATUS) -> Self {
        Status(s)
    }
}

impl Status {
    fn ok(self) -> Result<(), Error> {
        let Status(status) = self;
        if status != EFI_SUCCESS.into() {
            Err(Error::Api(self))
        } else {
            Ok(())
        }
    }
}

#[export_name = "efi_main"]
unsafe extern "C" fn entrypoint(
    image_handle: EFI_HANDLE,
    system_table: &mut EFI_SYSTEM_TABLE,
) -> EFI_STATUS {
    initialize_libraries(image_handle, system_table);

    let bs = *gBS;

    let f = || -> Result<(), Error> {
        let mut http_sbp: *mut EFI_SERVICE_BINDING_PROTOCOL = core::ptr::null_mut();
        Status(bs.LocateProtocol.unwrap()(
            &mut gEfiHttpServiceBindingProtocolGuid,
            core::ptr::null_mut(),
            core::mem::transmute(&mut http_sbp),
        ))
        .ok()?;

        let mut http_service_handle: EFI_HANDLE = core::ptr::null_mut();
        Status((*http_sbp).CreateChild.unwrap()(
            http_sbp,
            core::mem::transmute(&mut http_service_handle),
        ))
        .ok()?;

        let mut http_protocol: *mut EFI_HTTP_PROTOCOL = core::ptr::null_mut();
        Status(bs.HandleProtocol.unwrap()(
            http_service_handle,
            &mut gEfiHttpProtocolGuid,
            core::mem::transmute(&mut http_protocol),
        ))
        .ok()?;

        let mut http_access_point: EFI_HTTPv4_ACCESS_POINT = Default::default();
        http_access_point.UseDefaultAddress = 1;

        let mut http_config: EFI_HTTP_CONFIG_DATA = Default::default();

        http_config.HttpVersion = EFI_HTTP_VERSION::HttpVersion11;
        http_config.LocalAddressIsIPv6 = 0;
        http_config.TimeOutMillisec = 10_000;
        http_config.AccessPoint.IPv4Node = &mut http_access_point;

        Status((*http_protocol).Configure.unwrap()(
            http_protocol,
            &mut http_config,
        ))
        .ok()?;

        let expected_bytes = 8196;

        // Get from httpbin.org/range/nb => stream nb of bytes
        // Don't bother resolving the hostname here...
        let mut url =
            U16CString::from_str(format!("http://3.214.21.228/range/{expected_bytes}")).unwrap();

        let mut req = EFI_HTTP_REQUEST_DATA {
            Method: EFI_HTTP_METHOD::HttpMethodGet,
            Url: url.as_mut_ptr(),
        };

        // Mandatory Host
        let mut value = *b"httpbin.org\0";
        let mut key = *b"Host\0";

        let mut req_header = EFI_HTTP_HEADER {
            FieldName: key.as_mut_ptr(),
            FieldValue: value.as_mut_ptr(),
        };

        let mut req_msg: EFI_HTTP_MESSAGE = Default::default();
        req_msg.BodyLength = 0;
        req_msg.Body = core::ptr::null_mut();
        req_msg.Data.Request = &mut req;
        req_msg.HeaderCount = 1;
        req_msg.Headers = &mut req_header;

        let mut req_token: EFI_HTTP_TOKEN = Default::default();
        req_token.Status = EFI_SUCCESS.into();
        req_token.Message = &mut req_msg;

        static mut REQ_COMPLETED: bool = false;
        unsafe extern "C" fn callback(_: EFI_EVENT, _: *mut c_void) {
            REQ_COMPLETED = true;
        }

        Status(bs.CreateEvent.unwrap()(
            EVT_NOTIFY_SIGNAL,
            TPL_CALLBACK.into(),
            Some(callback),
            core::ptr::null_mut(),
            &mut req_token.Event,
        ))
        .ok()?;

        Status((*http_protocol).Request.unwrap()(
            http_protocol,
            &mut req_token,
        ))
        .ok()?;

        while !REQ_COMPLETED {
            Status((*http_protocol).Poll.unwrap()(http_protocol)).ok()?;
        }

        let mut res: EFI_HTTP_RESPONSE_DATA = Default::default();
        let mut res_msg: EFI_HTTP_MESSAGE = Default::default();
        res_msg.Data.Response = &mut res;

        REQ_COMPLETED = false;

        let mut res_token: EFI_HTTP_TOKEN = Default::default();
        res_token.Status = EFI_SUCCESS.into();
        res_token.Message = &mut res_msg;

        Status(bs.CreateEvent.unwrap()(
            EVT_NOTIFY_SIGNAL,
            TPL_CALLBACK.into(),
            Some(callback),
            core::ptr::null_mut(),
            &mut res_token.Event,
        ))
        .ok()?;

        Status((*http_protocol).Response.unwrap()(
            http_protocol,
            &mut res_token,
        ))
        .ok()?;

        while !REQ_COMPLETED {
            Status((*http_protocol).Poll.unwrap()(http_protocol)).ok()?;
        }

        let s = |p| CStr::from_ptr(p as _).to_str().unwrap();

        let headers = core::slice::from_raw_parts(res_msg.Headers, res_msg.HeaderCount as _);

        headers.iter().for_each(|h| {
            print(format!(
                "Header: {n}, Value: {v}",
                n = s(h.FieldName),
                v = s(h.FieldValue)
            ))
        });

        let content_length = headers
            .into_iter()
            .find_map(|h| {
                if CStr::from_ptr(h.FieldName as _)
                    == CStr::from_bytes_with_nul_unchecked(HTTP_HEADER_CONTENT_LENGTH)
                {
                    str::parse::<usize>(s(h.FieldValue)).ok()
                } else {
                    None
                }
            })
            .ok_or(Error::Program(ProgramError::NoContentLength))?;

        print(format!("Content length: {content_length}."));

        // Example of abstraction of the imperative `Response` call to a stream of chunks.
        let receive = itertools::unfold(
            Ok((content_length, [0u8; 512])),
            |st: &mut Result<(usize, [u8; 512]), Error>| match st {
                // Completed
                Ok((0, _)) => None,
                // Partial
                Ok((received, buffer)) => {
                    let mut g = || -> Result<u64, Error> {
                        let mut res_msg: EFI_HTTP_MESSAGE = Default::default();
                        res_msg.BodyLength = buffer.len() as _;
                        res_msg.Body = buffer.as_mut_ptr() as _;

                        let mut res_token: EFI_HTTP_TOKEN = Default::default();
                        res_token.Status = EFI_SUCCESS.into();
                        res_token.Message = &mut res_msg;

                        Status(bs.CreateEvent.unwrap()(
                            EVT_NOTIFY_SIGNAL,
                            TPL_CALLBACK.into(),
                            Some(recv_callback),
                            core::ptr::null_mut(),
                            &mut res_token.Event,
                        ))
                        .ok()?;

                        static mut RECV_COMPLETED: bool = false;
                        unsafe extern "C" fn recv_callback(_: EFI_EVENT, _: *mut c_void) {
                            RECV_COMPLETED = true;
                        }

                        RECV_COMPLETED = false;

                        Status((*http_protocol).Response.unwrap()(
                            http_protocol,
                            &mut res_token,
                        ))
                        .ok()?;

                        while !RECV_COMPLETED {
                            Status((*http_protocol).Poll.unwrap()(http_protocol)).ok()?;
                        }

                        Ok(res_msg.BodyLength)
                    };
                    match g() {
                        Ok(len) => {
                            *received -= len as usize;
                            Some(Ok(buffer[0..len as _].to_vec()))
                        }
                        Err(e) => Some(Err(e)),
                    }
                }
                // Shortcut on error
                Err(_) => None,
            },
        );

        // Actually fold the stream of received chunks.
        let final_content = receive
            .into_iter()
            .try_fold(Vec::<u8>::new(), |mut v, chunk| {
                chunk.map(|mut c| {
                    print(format!("Received {bytes}", bytes = c.len()));
                    v.append(&mut c);
                    v
                })
            })?;

        // Must be == expected bytes
        print(format!(
            "Received a total of {x} bytes, expected {y} bytes",
            x = final_content.len(),
            y = expected_bytes
        ));

        Ok(())
    };

    match f() {
        Err(Error::Api(Status(e))) => {
            print(format!("An API error occured {:#02x}", e));
        }
        Err(Error::Program(e)) => {
            print(format!("A program error occured {:?}", e));
        }
        Ok(()) => {
            print("Completed successfully.");
        }
    }

    EFI_SUCCESS.into()
}
