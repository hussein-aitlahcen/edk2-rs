#![no_main]
#![no_std]
#![feature(abi_efiapi)]

use edk2_rs::*;

#[export_name = "efi_main"]
unsafe extern "efiapi" fn entrypoint(
    image_handle: EFI_HANDLE,
    system_table: &mut EFI_SYSTEM_TABLE,
) -> EFI_STATUS {
    initialize_libraries(image_handle, system_table);
    AsciiPrint("HELLO FROM RUST!\n\0".as_ptr());
    EFI_SUCCESS.into()
}
