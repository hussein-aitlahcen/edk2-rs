#![allow(non_upper_case_globals)]
#![allow(non_camel_case_types)]
#![allow(non_snake_case)]
#![no_std]

#[panic_handler]
fn panic_handler(_info: &core::panic::PanicInfo) -> ! {
    loop {}
}

pub mod ctypes {
    pub type c_void = ();
    pub type c_char = u8;
    pub type c_uchar = u8;
    pub type c_schar = i8;
    pub type c_ushort = u16;
    pub type c_short = i16;
    pub type c_uint = u32;
    pub type c_int = i32;
    pub type c_ulong = u64;
    pub type c_long = i64;
    pub type c_ulonglong = u64;
    pub type c_longlong = i64;
}

pub type MEMORY_ERROR_CORRECT_CAPABILITY = u8;

#[cfg(target_arch = "aarch64")]
include!("./bindings_AArch64.rs");

#[cfg(target_arch = "arm")]
include!("./bindings_Arm.rs");

#[cfg(target_arch = "x86")]
include!("./bindings_Ia32.rs");

#[cfg(target_arch = "x86_64")]
include!("./bindings_X64.rs");

pub fn initialize_libraries(image_handle: EFI_HANDLE, system_table: &mut EFI_SYSTEM_TABLE) {
    unsafe {
        UefiBootServicesTableLibConstructor(image_handle, system_table);
        UefiRuntimeServicesTableLibConstructor(image_handle, system_table);
        DevicePathLibConstructor(image_handle, system_table);
    }
}
