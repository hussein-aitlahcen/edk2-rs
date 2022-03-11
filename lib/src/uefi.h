#include <Uefi.h>

#include <Pi/PiMultiPhase.h>

#include <Protocol/AbsolutePointer.h>
#include <Protocol/AcpiSystemDescriptionTable.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/AdapterInformation.h>
#include <Protocol/Arp.h>
#include <Protocol/AtaPassThru.h>
#include <Protocol/AuthenticationInfo.h>
#include <Protocol/Bds.h>
#include <Protocol/Bis.h>
#include <Protocol/BlockIo.h>
#include <Protocol/BlockIo2.h>
#include <Protocol/BlockIoCrypto.h>
#include <Protocol/BluetoothAttribute.h>
#include <Protocol/BluetoothConfig.h>
#include <Protocol/BluetoothHc.h>
#include <Protocol/BluetoothIo.h>
#include <Protocol/BluetoothLeConfig.h>
#include <Protocol/BootManagerPolicy.h>
#include <Protocol/BusSpecificDriverOverride.h>
#include <Protocol/Capsule.h>
#include <Protocol/CcMeasurement.h>
#include <Protocol/ComponentName.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/Cpu.h>
#include <Protocol/CpuIo2.h>
#include <Protocol/DebugPort.h>
#include <Protocol/DebugSupport.h>
#include <Protocol/Decompress.h>
#include <Protocol/DeferredImageLoad.h>
#include <Protocol/DeviceIo.h>
#include <Protocol/DevicePath.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/DevicePathToText.h>
#include <Protocol/DevicePathUtilities.h>
#include <Protocol/Dhcp4.h>
#include <Protocol/Dhcp6.h>
#include <Protocol/DiskInfo.h>
#include <Protocol/DiskIo.h>
#include <Protocol/DiskIo2.h>
#include <Protocol/Dns4.h>
#include <Protocol/Dns6.h>
#include <Protocol/DriverBinding.h>
#include <Protocol/DriverConfiguration.h>
#include <Protocol/DriverConfiguration2.h>
#include <Protocol/DriverDiagnostics.h>
#include <Protocol/DriverDiagnostics2.h>
#include <Protocol/DriverFamilyOverride.h>
#include <Protocol/DriverHealth.h>
#include <Protocol/DriverSupportedEfiVersion.h>
#include <Protocol/DxeMmReadyToLock.h>
#include <Protocol/DxeSmmReadyToLock.h>
#include <Protocol/Eap.h>
#include <Protocol/EapConfiguration.h>
#include <Protocol/EapManagement.h>
#include <Protocol/EapManagement2.h>
#include <Protocol/Ebc.h>
#include <Protocol/EdidActive.h>
#include <Protocol/EdidDiscovered.h>
#include <Protocol/EdidOverride.h>
#include <Protocol/EraseBlock.h>
#include <Protocol/FirmwareManagement.h>
#include <Protocol/FirmwareVolume2.h>
#include <Protocol/FirmwareVolumeBlock.h>
#include <Protocol/FormBrowser2.h>
#include <Protocol/Ftp4.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/GuidedSectionExtraction.h>
#include <Protocol/Hash.h>
#include <Protocol/Hash2.h>
#include <Protocol/HiiConfigAccess.h>
#include <Protocol/HiiConfigKeyword.h>
#include <Protocol/HiiConfigRouting.h>
#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiFont.h>
#include <Protocol/HiiImage.h>
#include <Protocol/HiiImageDecoder.h>
#include <Protocol/HiiImageEx.h>
#include <Protocol/HiiPackageList.h>
#include <Protocol/HiiPopup.h>
#include <Protocol/HiiString.h>
#include <Protocol/Http.h>
#include <Protocol/HttpBootCallback.h>
#include <Protocol/HttpUtilities.h>
#include <Protocol/I2cBusConfigurationManagement.h>
#include <Protocol/I2cEnumerate.h>
#include <Protocol/I2cHost.h>
#include <Protocol/I2cIo.h>
#include <Protocol/I2cMaster.h>
#include <Protocol/IScsiInitiatorName.h>
#include <Protocol/IdeControllerInit.h>
#include <Protocol/IncompatiblePciDeviceSupport.h>
#include <Protocol/Ip4.h>
#include <Protocol/Ip4Config.h>
#include <Protocol/Ip4Config2.h>
#include <Protocol/Ip6.h>
#include <Protocol/Ip6Config.h>
#include <Protocol/IpSec.h>
#include <Protocol/IpSecConfig.h>
#include <Protocol/IsaHc.h>
#include <Protocol/Kms.h>
#include <Protocol/LegacyRegion2.h>
#include <Protocol/LegacySpiController.h>
#include <Protocol/LegacySpiFlash.h>
#include <Protocol/LegacySpiSmmController.h>
#include <Protocol/LegacySpiSmmFlash.h>
#include <Protocol/LoadFile.h>
#include <Protocol/LoadFile2.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/ManagedNetwork.h>
#include <Protocol/Metronome.h>
#include <Protocol/MmAccess.h>
#include <Protocol/MmBase.h>
#include <Protocol/MmCommunication.h>
#include <Protocol/MmCommunication2.h>
#include <Protocol/MmConfiguration.h>
#include <Protocol/MmControl.h>
#include <Protocol/MmCpu.h>
#include <Protocol/MmCpuIo.h>
#include <Protocol/MmEndOfDxe.h>
#include <Protocol/MmGpiDispatch.h>
#include <Protocol/MmIoTrapDispatch.h>
#include <Protocol/MmMp.h>
#include <Protocol/MmPciRootBridgeIo.h>
#include <Protocol/MmPeriodicTimerDispatch.h>
#include <Protocol/MmPowerButtonDispatch.h>
#include <Protocol/MmReadyToLock.h>
#include <Protocol/MmReportStatusCodeHandler.h>
#include <Protocol/MmStandbyButtonDispatch.h>
#include <Protocol/MmStatusCode.h>
#include <Protocol/MmSwDispatch.h>
#include <Protocol/MmSxDispatch.h>
#include <Protocol/MmUsbDispatch.h>
#include <Protocol/MonotonicCounter.h>
#include <Protocol/MpService.h>
#include <Protocol/Mtftp4.h>
#include <Protocol/Mtftp6.h>
#include <Protocol/NetworkInterfaceIdentifier.h>
#include <Protocol/NvdimmLabel.h>
#include <Protocol/NvmExpressPassthru.h>
#include <Protocol/PartitionInfo.h>
#include <Protocol/Pcd.h>
#include <Protocol/PcdInfo.h>
#include <Protocol/PciEnumerationComplete.h>
#include <Protocol/PciHostBridgeResourceAllocation.h>
#include <Protocol/PciHotPlugInit.h>
#include <Protocol/PciHotPlugRequest.h>
#include <Protocol/PciIo.h>
#include <Protocol/PciOverride.h>
#include <Protocol/PciPlatform.h>
#include <Protocol/PciRootBridgeIo.h>
#include <Protocol/PiPcd.h>
#include <Protocol/PiPcdInfo.h>
#include <Protocol/Pkcs7Verify.h>
#include <Protocol/PlatformDriverOverride.h>
#include <Protocol/PlatformToDriverConfiguration.h>
#include <Protocol/PxeBaseCode.h>
#include <Protocol/PxeBaseCodeCallBack.h>
#include <Protocol/RamDisk.h>
#include <Protocol/RealTimeClock.h>
#include <Protocol/RedfishDiscover.h>
#include <Protocol/RegularExpressionProtocol.h>
#include <Protocol/ReportStatusCodeHandler.h>
#include <Protocol/Reset.h>
#include <Protocol/ResetNotification.h>
#include <Protocol/RestEx.h>
#include <Protocol/RestJsonStructure.h>
#include <Protocol/Rng.h>
#include <Protocol/Runtime.h>
#include <Protocol/S3SaveState.h>
#include <Protocol/S3SmmSaveState.h>
#include <Protocol/ScsiIo.h>
#include <Protocol/ScsiPassThru.h>
#include <Protocol/ScsiPassThruExt.h>
#include <Protocol/SdMmcPassThru.h>
#include <Protocol/Security.h>
#include <Protocol/Security2.h>
#include <Protocol/SecurityPolicy.h>
#include <Protocol/SerialIo.h>
#include <Protocol/ServiceBinding.h>
#include <Protocol/Shell.h>
#include <Protocol/ShellDynamicCommand.h>
#include <Protocol/ShellParameters.h>
#include <Protocol/SimpleFileSystem.h>
#include <Protocol/SimpleNetwork.h>
#include <Protocol/SimplePointer.h>
#include <Protocol/SimpleTextIn.h>
#include <Protocol/SimpleTextInEx.h>
#include <Protocol/SimpleTextOut.h>
#include <Protocol/SmartCardEdge.h>
#include <Protocol/SmartCardReader.h>
#include <Protocol/Smbios.h>
#include <Protocol/SmbusHc.h>
#include <Protocol/SmmAccess2.h>
#include <Protocol/SmmBase2.h>
#include <Protocol/SmmCommunication.h>
#include <Protocol/SmmConfiguration.h>
#include <Protocol/SmmControl2.h>
#include <Protocol/SmmCpu.h>
#include <Protocol/SmmCpuIo2.h>
#include <Protocol/SmmEndOfDxe.h>
#include <Protocol/SmmGpiDispatch2.h>
#include <Protocol/SmmIoTrapDispatch2.h>
#include <Protocol/SmmPciRootBridgeIo.h>
#include <Protocol/SmmPeriodicTimerDispatch2.h>
#include <Protocol/SmmPowerButtonDispatch2.h>
#include <Protocol/SmmReadyToLock.h>
#include <Protocol/SmmReportStatusCodeHandler.h>
#include <Protocol/SmmStandbyButtonDispatch2.h>
#include <Protocol/SmmStatusCode.h>
#include <Protocol/SmmSwDispatch2.h>
#include <Protocol/SmmSxDispatch2.h>
#include <Protocol/SmmUsbDispatch2.h>
#include <Protocol/SpiConfiguration.h>
#include <Protocol/SpiHc.h>
#include <Protocol/SpiIo.h>
#include <Protocol/SpiNorFlash.h>
#include <Protocol/SpiSmmConfiguration.h>
#include <Protocol/SpiSmmHc.h>
#include <Protocol/SpiSmmNorFlash.h>
#include <Protocol/StatusCode.h>
#include <Protocol/StorageSecurityCommand.h>
#include <Protocol/SuperIo.h>
#include <Protocol/SuperIoControl.h>
#include <Protocol/Supplicant.h>
#include <Protocol/TapeIo.h>
#include <Protocol/Tcg2Protocol.h>
#include <Protocol/TcgService.h>
#include <Protocol/Tcp4.h>
#include <Protocol/Tcp6.h>
#include <Protocol/Timer.h>
#include <Protocol/Timestamp.h>
#include <Protocol/Tls.h>
#include <Protocol/TlsConfig.h>
#include <Protocol/TrEEProtocol.h>
#include <Protocol/Udp4.h>
#include <Protocol/Udp6.h>
#include <Protocol/UfsDeviceConfig.h>
#include <Protocol/UgaDraw.h>
#include <Protocol/UgaIo.h>
#include <Protocol/UnicodeCollation.h>
#include <Protocol/Usb2HostController.h>
#include <Protocol/UsbFunctionIo.h>
#include <Protocol/UsbHostController.h>
#include <Protocol/UsbIo.h>
#include <Protocol/UserCredential.h>
#include <Protocol/UserCredential2.h>
#include <Protocol/UserManager.h>
#include <Protocol/Variable.h>
#include <Protocol/VariableWrite.h>
#include <Protocol/VlanConfig.h>
#include <Protocol/WatchdogTimer.h>
#include <Protocol/WiFi.h>
#include <Protocol/WiFi2.h>

EFI_STATUS
EFIAPI
UefiMain(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);

EFI_STATUS
EFIAPI
UefiUnload(IN EFI_HANDLE ImageHandle);

EFI_STATUS
EFIAPI
UefiBootServicesTableLibConstructor(IN EFI_HANDLE ImageHandle,
                                    IN EFI_SYSTEM_TABLE *SystemTable);

EFI_STATUS
EFIAPI
UefiRuntimeServicesTableLibConstructor(IN EFI_HANDLE ImageHandle,
                                       IN EFI_SYSTEM_TABLE *SystemTable);

EFI_STATUS
EFIAPI
UefiLibConstructor(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable);

EFI_STATUS
EFIAPI
DevicePathLibConstructor(IN EFI_HANDLE ImageHandle,
                         IN EFI_SYSTEM_TABLE *SystemTable);

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <Library/BaseLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/PrintLib.h>
