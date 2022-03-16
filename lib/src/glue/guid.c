/** @file
  Global GUID Definitions

Copyright (c) 2015, Alex Ionescu. All rights reserved.<BR>
This program and the accompanying materials
are licensed and made available under the terms and conditions of the BSD License
which accompanies this distribution.  The full text of the license may be found at
http://opensource.org/licenses/bsd-license.php

THE PROGRAM IS DISTRIBUTED UNDER THE BSD LICENSE ON AN "AS IS" BASIS,
WITHOUT WARRANTIES OR REPRESENTATIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED.

**/

#include <Uefi.h>
#include <Library/UefiLib.h>

#include <Protocol/HiiFont.h>
#include <Protocol/GraphicsOutput.h>
#include <Protocol/UgaDraw.h>
#include <Protocol/DebugPort.h>
#include <Protocol/DevicePathFromText.h>
#include <Protocol/DevicePathToText.h>
#include <Protocol/DevicePathUtilities.h>
#include <Protocol/PciIo.h>
#include <Protocol/LoadedImage.h>
#include <Protocol/AcpiTable.h>
#include <Protocol/Decompress.h>

#include <Protocol/SerialIo.h>
#include <Protocol/UsbIo.h>

#include <Pi/PiDxeCis.h>
#include <Protocol/MpService.h>

#include <Guid/PcAnsi.h>
#include <Guid/GlobalVariable.h>
#include <Guid/EventGroup.h>

#include <Protocol/EfiShellInterface.h>
#include <Protocol/Shell.h>
#include <Protocol/EfiShellEnvironment2.h>
#include <Protocol/ShellParameters.h>
#include <Protocol/UnicodeCollation.h>

#include <Protocol/HiiDatabase.h>
#include <Protocol/HiiString.h>
#include <Protocol/HiiConfigRouting.h>
#include <Protocol/FormBrowser2.h>
#include <Guid/MdeModuleHii.h>

#include <Guid/ImageAuthentication.h>
#include <Guid/SmBios.h>
#include <Guid/TlsAuthentication.h>
#include <Guid/HttpTlsCipherList.h>
#include <Protocol/AdapterInformation.h>
#include <Protocol/Dns4.h>
#include <Protocol/Dns6.h>
#include <Protocol/Dpc.h>
#include <Protocol/HttpUtilities.h>
#include <Protocol/Ip4Config2.h>
#include <Protocol/Ip6Config.h>
#include <Protocol/ManagedNetwork.h>
#include <Protocol/RestEx.h>
#include <Protocol/SimpleNetwork.h>
#include <Protocol/Smbios.h>
#include <Protocol/Tcp4.h>
#include <Protocol/Tcp6.h>
#include <Protocol/Tls.h>
#include <Protocol/TlsConfig.h>
#include <Protocol/HttpCallback.h>

EFI_GUID gEfiPciIoProtocolGuid = EFI_PCI_IO_PROTOCOL_GUID;
EFI_GUID gEfiDriverDiagnosticsProtocolGuid = EFI_DRIVER_DIAGNOSTICS_PROTOCOL_GUID;
EFI_GUID gEfiDriverDiagnostics2ProtocolGuid = EFI_DRIVER_DIAGNOSTICS2_PROTOCOL_GUID;
EFI_GUID gEfiDriverConfigurationProtocolGuid = EFI_DRIVER_CONFIGURATION_PROTOCOL_GUID;
EFI_GUID gEfiDriverConfiguration2ProtocolGuid = EFI_DRIVER_CONFIGURATION2_PROTOCOL_GUID;
EFI_GUID gEfiComponentName2ProtocolGuid = EFI_COMPONENT_NAME2_PROTOCOL_GUID;
EFI_GUID gEfiComponentNameProtocolGuid = EFI_COMPONENT_NAME_PROTOCOL_GUID;
EFI_GUID gEfiDriverBindingProtocolGuid = EFI_DRIVER_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiSimpleTextOutProtocolGuid = EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID;
EFI_GUID gEfiGraphicsOutputProtocolGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
EFI_GUID gEfiUgaDrawProtocolGuid = EFI_UGA_DRAW_PROTOCOL_GUID;
EFI_GUID gEfiHiiFontProtocolGuid = EFI_HII_FONT_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathProtocolGuid = EFI_DEVICE_PATH_PROTOCOL_GUID;
EFI_GUID gEfiPcAnsiGuid = EFI_PC_ANSI_GUID;
EFI_GUID gEfiVT100Guid = EFI_VT_100_GUID;
EFI_GUID gEfiVT100PlusGuid = EFI_VT_100_PLUS_GUID;
EFI_GUID gEfiVTUTF8Guid = EFI_VT_UTF8_GUID;
EFI_GUID gEfiUartDevicePathGuid = DEVICE_PATH_MESSAGING_UART_FLOW_CONTROL;
EFI_GUID gEfiSasDevicePathGuid = EFI_SAS_DEVICE_PATH_GUID;
EFI_GUID gEfiDebugPortProtocolGuid = EFI_DEBUGPORT_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathUtilitiesProtocolGuid = EFI_DEVICE_PATH_UTILITIES_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathToTextProtocolGuid = EFI_DEVICE_PATH_TO_TEXT_PROTOCOL_GUID;
EFI_GUID gEfiDevicePathFromTextProtocolGuid = EFI_DEVICE_PATH_FROM_TEXT_PROTOCOL_GUID;
EFI_GUID gEfiGlobalVariableGuid = EFI_GLOBAL_VARIABLE;
EFI_GUID gEfiLoadedImageProtocolGuid = EFI_LOADED_IMAGE_PROTOCOL_GUID;
EFI_GUID gEfiAcpiTableProtocolGuid = EFI_ACPI_TABLE_PROTOCOL_GUID;
EFI_GUID gEfiDecompressProtocolGuid = EFI_DECOMPRESS_PROTOCOL_GUID;

EFI_GUID gEfiEventExitBootServicesGuid = EFI_EVENT_GROUP_EXIT_BOOT_SERVICES;
EFI_GUID gEfiEventVirtualAddressChangeGuid = EFI_EVENT_GROUP_VIRTUAL_ADDRESS_CHANGE;

EFI_GUID gEfiUsbIoProtocolGuid = EFI_USB_IO_PROTOCOL_GUID;
EFI_GUID gEfiSerialIoProtocolGuid = EFI_SERIAL_IO_PROTOCOL_GUID;

EFI_GUID gEfiMpServiceProtocolGuid = EFI_MP_SERVICES_PROTOCOL_GUID;

EFI_GUID gEfiShellInterfaceGuid = SHELL_INTERFACE_PROTOCOL_GUID;
EFI_GUID gEfiShellProtocolGuid = EFI_SHELL_PROTOCOL_GUID;
EFI_GUID gEfiFileInfoGuid = EFI_FILE_INFO_ID;
EFI_GUID gEfiShellEnvironment2Guid = SHELL_ENVIRONMENT_PROTOCOL_GUID;
EFI_GUID gEfiShellEnvironment2ExtGuid = EFI_SE_EXT_SIGNATURE_GUID;
EFI_GUID gEfiSimpleFileSystemProtocolGuid = EFI_SIMPLE_FILE_SYSTEM_PROTOCOL_GUID;
EFI_GUID gEfiShellParametersProtocolGuid = EFI_SHELL_PARAMETERS_PROTOCOL_GUID;
EFI_GUID gEfiUnicodeCollation2ProtocolGuid = EFI_UNICODE_COLLATION_PROTOCOL2_GUID;

EFI_GUID gEfiHiiStringProtocolGuid = EFI_HII_STRING_PROTOCOL_GUID;
EFI_GUID gEfiHiiDatabaseProtocolGuid = EFI_HII_DATABASE_PROTOCOL_GUID;
EFI_GUID gEfiHiiImageProtocolGuid = EFI_HII_IMAGE_PROTOCOL_GUID;
EFI_GUID gEfiHiiConfigRoutingProtocolGuid = EFI_HII_CONFIG_ROUTING_PROTOCOL_GUID;

EFI_GUID gEfiFormBrowser2ProtocolGuid = EFI_FORM_BROWSER2_PROTOCOL_GUID;

EFI_GUID gEdkiiIfrBitVarstoreGuid = EDKII_IFR_BIT_VARSTORE_GUID;
EFI_GUID gEfiHttpServiceBindingProtocolGuid = EFI_HTTP_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiHttpProtocolGuid = EFI_HTTP_PROTOCOL_GUID;
EFI_GUID gEfiRestExProtocolGuid = EFI_REST_EX_PROTOCOL_GUID;
EFI_GUID gEfiRestExServiceBindingProtocolGuid = EFI_REST_EX_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiHttpUtilitiesProtocolGuid = EFI_HTTP_UTILITIES_PROTOCOL_GUID;

EFI_GUID gEfiVirtualDiskGuid = EFI_VIRTUAL_DISK_GUID;
EFI_GUID gEfiVirtualCdGuid = EFI_VIRTUAL_CD_GUID;
EFI_GUID gEfiPersistentVirtualDiskGuid = EFI_PERSISTENT_VIRTUAL_DISK_GUID;
EFI_GUID gEfiPersistentVirtualCdGuid = EFI_PERSISTENT_VIRTUAL_CD_GUID;

EFI_GUID gEfiAdapterInformationProtocolGuid = EFI_ADAPTER_INFORMATION_PROTOCOL_GUID;
EFI_GUID gEfiAdapterInfoMediaStateGuid = EFI_ADAPTER_INFO_MEDIA_STATE_GUID;
EFI_GUID gEfiAdapterInfoNetworkBootGuid = EFI_ADAPTER_INFO_NETWORK_BOOT_GUID;
EFI_GUID gEfiAdapterInfoSanMacAddressGuid = EFI_ADAPTER_INFO_SAN_MAC_ADDRESS_GUID;
EFI_GUID gEfiAdapterInfoUndiIpv6SupportGuid = EFI_ADAPTER_INFO_UNDI_IPV6_SUPPORT_GUID;

EFI_GUID gEfiDpcProtocolGuid = EFI_DPC_PROTOCOL_GUID;

EFI_GUID gEfiManagedNetworkServiceBindingProtocolGuid = EFI_MANAGED_NETWORK_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiManagedNetworkProtocolGuid = EFI_MANAGED_NETWORK_PROTOCOL_GUID;

EFI_GUID gEfiSimpleNetworkProtocolGuid = EFI_SIMPLE_NETWORK_PROTOCOL_GUID;

EFI_GUID gEfiIp4Config2ProtocolGuid = EFI_IP4_CONFIG2_PROTOCOL_GUID;

EFI_GUID gEfiSmbiosTableGuid = SMBIOS_TABLE_GUID;
EFI_GUID gEfiSmbios3TableGuid = SMBIOS3_TABLE_GUID;

EFI_GUID gEfiTcp4ServiceBindingProtocolGuid = EFI_TCP4_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiTcp4ProtocolGuid = EFI_TCP4_PROTOCOL_GUID;

EFI_GUID gEfiTcp6ServiceBindingProtocolGuid = EFI_TCP6_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiTcp6ProtocolGuid = EFI_TCP6_PROTOCOL_GUID;

EFI_GUID gEfiTlsServiceBindingProtocolGuid = EFI_TLS_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiTlsProtocolGuid = EFI_TLS_PROTOCOL_GUID;

EFI_GUID gEfiTlsCaCertificateGuid = EFI_TLS_CA_CERTIFICATE_GUID;

EFI_GUID gEfiTlsConfigurationProtocolGuid = EFI_TLS_CONFIGURATION_PROTOCOL_GUID;

EFI_GUID gEfiDns4ServiceBindingProtocolGuid = EFI_DNS4_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiDns4ProtocolGuid = EFI_DNS4_PROTOCOL_GUID;

EFI_GUID gEfiDns6ServiceBindingProtocolGuid = EFI_DNS6_SERVICE_BINDING_PROTOCOL_GUID;
EFI_GUID gEfiDns6ProtocolGuid = EFI_DNS6_PROTOCOL_GUID;

EFI_GUID gEfiIp6ConfigProtocolGuid = EFI_IP6_CONFIG_PROTOCOL_GUID;

EFI_GUID gEfiCertX509Guid = EFI_CERT_X509_GUID;

EFI_GUID gEdkiiHttpTlsCipherListGuid = EDKII_HTTP_TLS_CIPHER_LIST_GUID;

EFI_GUID gEdkiiHttpCallbackProtocolGuid = EDKII_HTTP_CALLBACK_PROTOCOL_GUID;
