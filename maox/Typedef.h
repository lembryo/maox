#ifndef __UEFI__TYPEDEF_H__
#define __UEFI__TYPEDEF_H__

constexpr auto NULL = nullptr;

typedef bool BOOLEAN;
typedef signed long long INTN;
typedef unsigned long long UINTN;
typedef signed char INT8;
typedef unsigned char UINT8;
typedef signed short int INT16;
typedef unsigned short int UINT16;
typedef signed long INT32;
typedef unsigned long UINT32;
typedef signed long long INT64;
typedef unsigned long long UINT64;
typedef void VOID;
typedef VOID* LPVOID;
typedef UINTN EFI_STATUS;
typedef LPVOID EFI_HANDLE;

typedef char CHAR8;
typedef wchar_t CHAR16;

#define EFIAPI
constexpr auto TRUE = true;
constexpr auto FALSE = false;

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

struct EFI_TABLE_HEADER {
	UINT64	Signature;
	UINT32	Revision;
	UINT32	HeaderSize;
	UINT32	CRC32;
	UINT32	Reserved;
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
	LPVOID* RuntimeServices; // TODO
	LPVOID* BootServices; // TODO
	UINTN NumberOfTableEntries;
	LPVOID* ConfigurationTable;
};

#endif // __UEFI__TYPEDEF_H__
