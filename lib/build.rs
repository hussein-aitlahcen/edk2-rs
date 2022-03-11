use glob::glob;
use std::{env::consts::ARCH, path::Path};

fn main() {
    let arch = match ARCH {
        "arm" => "Arm",
        "x86_64" => "X64",
        "x86" => "Ia32",
        "aarch64" => "AArch64",
        _ => panic!("Unsupported architecture"),
    };

    let blocklist = [
        "FilePaths.c",
        "UnitTestHost.c",
        "X86MemoryFence.c",
        "X86SpeculationBarrier.c",
    ];

    let libraries = [
        "UefiLib",
        "BaseMemoryLib",
        "BasePrintLib",
        "BaseLib",
        "BaseDebugLibNull",
        "UefiMemoryAllocationLib",
        "UefiBootServicesTableLib",
        "UefiRuntimeServicesTableLib",
        "UefiDevicePathLib",
        "UefiDevicePathLibDevicePathProtocol",
    ]
    .into_iter()
    .map(|lib| {
        let library_path = format!("extra/edk2/MdePkg/Library/{lib}");
        glob(&format!("{library_path}/*.c"))
    })
    .collect::<Result<Vec<_>, _>>()
    .unwrap();

    let mut c = cc::Build::new();

    // INCLUDES
    c.include(Path::new("extra/edk2/MdePkg/Include/"))
        .include(Path::new(&format!("extra/edk2/MdePkg/Include/{}", arch)))
        .include(Path::new("extra/edk2/MdePkg/Include/Library/"))
        .include(Path::new("extra/edk2/ShellPkg/Include/"))
        .include(Path::new("extra/edk2/MdeModulePkg/Include/"));

    // DEFINES
    c.define("_PCD_GET_MODE_BOOL_PcdDriverDiagnosticsDisable", "FALSE")
        .define("_PCD_GET_MODE_BOOL_PcdComponentName2Disable", "FALSE")
        .define("_PCD_GET_MODE_BOOL_PcdComponentNameDisable", "FALSE")
        .define("_PCD_GET_MODE_BOOL_PcdDriverDiagnostics2Disable", "FALSE")
        .define(
            "_PCD_GET_MODE_BOOL_PcdUefiVariableDefaultLangDeprecate",
            " FALSE",
        )
        .define("_PCD_GET_MODE_BOOL_PcdUgaConsumeSupport", "TRUE")
        .define("_PCD_GET_MODE_BOOL_PcdVerifyNodeInList", "FALSE")
        .define("_PCD_GET_MODE_BOOL_PcdValidateOrderedCollection", "FALSE")
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueEfiWatchDogTimerExpired",
            "EFI_COMPUTING_UNIT_HOST_PROCESSOR | EFI_CU_HP_EC_TIMER_EXPIRED",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueSetVirtualAddressMap",
            "EFI_SOFTWARE_EFI_RUNTIME_SERVICE | EFI_SW_RS_PC_SET_VIRTUAL_ADDRESS_MAP",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueMemoryTestStarted",
            "EFI_COMPUTING_UNIT_MEMORY | EFI_CU_MEMORY_PC_TEST",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueUncorrectableMemoryError",
            "EFI_COMPUTING_UNIT_MEMORY | EFI_CU_MEMORY_EC_UNCORRECTABLE",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueRemoteConsoleError",
            "EFI_PERIPHERAL_REMOTE_CONSOLE | EFI_P_EC_CONTROLLER_ERROR",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueRemoteConsoleReset",
            "EFI_PERIPHERAL_REMOTE_CONSOLE | EFI_P_PC_RESET",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueRemoteConsoleInputError",
            "EFI_PERIPHERAL_REMOTE_CONSOLE | EFI_P_EC_INPUT_ERROR",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueRemoteConsoleOutputError",
            "EFI_PERIPHERAL_REMOTE_CONSOLE | EFI_P_EC_OUTPUT_ERROR",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueMouseInterfaceError",
            "EFI_PERIPHERAL_MOUSE | EFI_P_EC_INTERFACE_ERROR",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueMouseEnable",
            "EFI_PERIPHERAL_MOUSE | EFI_P_PC_ENABLE",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueMouseDisable",
            "EFI_PERIPHERAL_MOUSE | EFI_P_PC_DISABLE",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardEnable",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_PC_ENABLE",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardDisable",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_PC_DISABLE",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardPresenceDetect",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_PC_PRESENCE_DETECT",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardReset",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_PC_RESET",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardClearBuffer",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_KEYBOARD_PC_CLEAR_BUFFER",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardSelfTest",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_KEYBOARD_PC_SELF_TEST",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardInterfaceError",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_EC_INTERFACE_ERROR",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueKeyboardInputError",
            "EFI_PERIPHERAL_KEYBOARD | EFI_P_EC_INPUT_ERROR",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueMouseInputError",
            "EFI_PERIPHERAL_MOUSE | EFI_P_EC_INPUT_ERROR",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueMouseReset",
            "EFI_PERIPHERAL_MOUSE | EFI_P_PC_RESET",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValuePeiHandoffToDxe",
            "EFI_SOFTWARE_PEI_CORE | EFI_SW_PEI_CORE_PC_HANDOFF_TO_NEXT",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValuePeimDispatch",
            "EFI_SOFTWARE_PEI_CORE | EFI_SW_PC_INIT_BEGIN",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValuePeiCoreEntry",
            "EFI_SOFTWARE_PEI_CORE | EFI_SW_PC_INIT",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueDxeCoreEntry",
            "EFI_SOFTWARE_DXE_CORE | EFI_SW_DXE_CORE_PC_ENTRY_POINT",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueDxeCoreHandoffToBds",
            "EFI_SOFTWARE_DXE_CORE | EFI_SW_DXE_CORE_PC_HANDOFF_TO_NEXT",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueBootServiceExit",
            "EFI_SOFTWARE_EFI_BOOT_SERVICE | EFI_SW_BS_PC_EXIT_BOOT_SERVICES",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueDxeDriverBegin",
            "EFI_SOFTWARE_DXE_CORE | EFI_SW_PC_INIT_BEGIN",
        )
        .define(
            "_PCD_GET_MODE_32_PcdStatusCodeValueDxeDriverEnd",
            "EFI_SOFTWARE_DXE_CORE | EFI_SW_PC_INIT_END",
        )
        .define(
            "_PCD_GET_MODE_32_PcdFixedDebugPrintErrorLevel",
            "0xFFFFFFFF",
        )
        .define("_PCD_GET_MODE_32_PcdMaximumUnicodeStringLength", "1000000")
        .define("_PCD_GET_MODE_32_PcdMaximumAsciiStringLength", "1000000")
        .define("_PCD_GET_MODE_32_PcdMaximumLinkedListLength", "1000000")
        .define("_PCD_GET_MODE_32_PcdMaximumDevicePathNodeCount", "0")
        .define("_PCD_GET_MODE_32_PcdSpinLockTimeout", "10000000")
        .define("_PCD_GET_MODE_8_PcdDebugPropertyMask", "0")
        .define("_PCD_GET_MODE_32_PcdDebugPrintErrorLevel", "0x80000000")
        .define("_PCD_GET_MODE_8_PcdReportStatusCodePropertyMask", "0")
        .define("_PCD_GET_MODE_8_PcdDebugClearMemoryValue", "0xAF")
        .define("_PCD_GET_MODE_8_PcdPerformanceLibraryPropertyMask", "0")
        .define("_PCD_GET_MODE_8_PcdPostCodePropertyMask", "0")
        .define("_PCD_GET_MODE_32_PcdFSBClock", "200000000")
        .define("_PCD_GET_MODE_32_PcdUefiLibMaxPrintBufferSize", "320")
        .define(
            "_PCD_GET_MODE_16_PcdUefiFileHandleLibPrintBufferSize",
            "1536",
        )
        .define("_PCD_GET_MODE_32_PcdMaximumGuidedExtractHandler", "0x10")
        .define("_PCD_GET_MODE_32_PcdUsbTransferTimeoutValue", "3000")
        .define(
            "_PCD_GET_MODE_64_PcdGuidedExtractHandlerTableAddress",
            "0x1000000",
        )
        .define(
            "_PCD_GET_MODE_64_PcdIoBlockBaseAddressForIpf",
            "0x0ffffc000000",
        )
        .define("_PCD_GET_MODE_64_PcdPciExpressBaseAddress", "0xE0000000")
        .define("_PCD_GET_MODE_64_PcdUartDefaultBaudRate", "115200")
        .define("_PCD_GET_MODE_8_PcdUartDefaultDataBits", "8")
        .define("_PCD_GET_MODE_8_PcdUartDefaultParity", "1")
        .define("_PCD_GET_MODE_8_PcdUartDefaultStopBits", "1")
        .define("_PCD_GET_MODE_8_PcdDefaultTerminalType", "0")
        .define("_PCD_GET_MODE_16_PcdHardwareErrorRecordLevel", "0")
        .define("_PCD_GET_MODE_16_PcdPlatformBootTimeOut", "0xffff")
        .define("_PCD_GET_MODE_BOOL_PcdShellLibAutoInitialize", "FALSE")
        .define("_PCD_GET_MODE_16_PcdShellPrintBufferSize", "16000");

    // Glue
    c.file("src/glue/guid.c");

    // SOURCES
    for lib in libraries {
        for src in lib {
            let src = src.expect("impossible to extract source file path");
            if !blocklist.iter().any(|x| {
                src.to_str()
                    .expect("source file path contains invalid characters")
                    .ends_with(x)
            }) {
                c.file(src);
            }
        }
    }

    // COMPILE
    c.compiler("clang-cl")
        .flag("/GS-")
        .flag("/W0")
        .static_flag(true)
        .compile("uefi");
}
