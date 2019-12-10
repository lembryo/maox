#ifndef __UEFI__EFI_H__
#define __UEFI__EFI_H__

#include "Typedef.h"

constexpr EFI_STATUS EFI_SUCCESS = 0;

class EFI_GUID {
public:
	BOOLEAN	operator ==(const EFI_GUID rcGUID) const {
		return rcGUID.Data1 == Data1 && rcGUID.Data2 == Data2 && rcGUID.Data3 == Data3 /* && rcGUID.Data4 == Data4 */;
	};

	UINT32	Data1;
	UINT16	Data2;
	UINT16	Data3;
	UINT8	Data4[8];
};

extern const EFI_GUID EFI_ACPI_20_TABLE_GUID;

struct EFI_TABLE_HEADER {
	UINT64	Signature;
	UINT32	Revision;
	UINT32	HeaderSize;
	UINT32	CRC32;
	UINT32	Reserved;
};

constexpr auto EFI_SYSTEM_TABLE_SIGNATURE = 0x5453595320494249;
constexpr auto EFI_2_80_SYSTEM_TABLE_REVISION = ((2 << 16) | (80));
constexpr auto EFI_2_70_SYSTEM_TABLE_REVISION = ((2 << 16) | (70));
constexpr auto EFI_2_60_SYSTEM_TABLE_REVISION = ((2 << 16) | (60));
constexpr auto EFI_2_50_SYSTEM_TABLE_REVISION = ((2 << 16) | (50));
constexpr auto EFI_2_40_SYSTEM_TABLE_REVISION = ((2 << 16) | (40));
constexpr auto EFI_2_31_SYSTEM_TABLE_REVISION = ((2 << 16) | (31));
constexpr auto EFI_2_30_SYSTEM_TABLE_REVISION = ((2 << 16) | (30));
constexpr auto EFI_2_20_SYSTEM_TABLE_REVISION = ((2 << 16) | (20));
constexpr auto EFI_2_10_SYSTEM_TABLE_REVISION = ((2 << 16) | (10));
constexpr auto EFI_2_00_SYSTEM_TABLE_REVISION = ((2 << 16) | (00));
constexpr auto EFI_1_10_SYSTEM_TABLE_REVISION = ((1 << 16) | (10));
constexpr auto EFI_1_02_SYSTEM_TABLE_REVISION = ((1 << 16) | (02));
constexpr auto EFI_SYSTEM_TABLE_REVISION = EFI_2_80_SYSTEM_TABLE_REVISION;
constexpr auto EFI_SPECIFICATION_VERSION = EFI_SYSTEM_TABLE_REVISION;

#include "EFI_BootServices.h"
#include "EFI_RuntimeServices.h"

struct EFI_CONFIGURATION_TABLE {
	EFI_GUID VendorGuid;
	VOID* VendorTable;
};

struct EFI_SYSTEM_TABLE {
	EFI_TABLE_HEADER Header;
	CHAR16* FirmwareVendor;
	UINT32 FirmwareRevision;
	EFI_HANDLE ConsoleInHandle;
	LPVOID ConIn;
	EFI_HANDLE ConsoleOutHandle;
	LPVOID ConOut;
	EFI_HANDLE StandardErrorHandle;
	LPVOID StdErr;
	EFI_RuntimeServices::Base* RuntimeServices;
	EFI_BootServices::Base* BootServices;
	UINTN NumberOfTableEntries;
	EFI_CONFIGURATION_TABLE* ConfigurationTable;
};

#endif // __UEFI__EFI_H__
