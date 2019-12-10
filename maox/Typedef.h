#ifndef __UEFI__TYPEDEF_H__
#define __UEFI__TYPEDEF_H__

constexpr auto NULL = nullptr;

// Typedef is UEFI Like
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
// typedef signed INT128;
// typedef unsigned UINT128;
typedef void VOID;
typedef VOID* LPVOID;

typedef char CHAR8;
typedef wchar_t CHAR16;

typedef UINTN EFI_STATUS;
typedef LPVOID EFI_HANDLE;
typedef LPVOID EFI_EVENT;
typedef UINT64 EFI_LBA;
typedef UINTN EFI_TPL;
// typedef xxxx EFI_MAC_ADDRES;
// typedef xxxx EFI_IPv4_ADDRESS;
// typedef xxxx EFI_IPv6_ADDRESS;
// typedef EFI_IPv4_ADDRESS EFI_IP_ADDRESS;

#define EFIAPI
constexpr auto TRUE = true;
constexpr auto FALSE = false;

#define var auto
#define val const auto

#endif // __UEFI__TYPEDEF_H__
