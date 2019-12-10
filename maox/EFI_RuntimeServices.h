#ifndef __UEFI__EFI_RUNTIME_SERVICES_H__
#define __UEFI__EFI_RUNTIME_SERVICES_H__

class EFI_RuntimeServices {
public:
	static const auto SIGNATURE = 0x56524553544e5552;
	static const auto REVISION = EFI_SPECIFICATION_VERSION;

public:
	// ========
	// 時刻関連
	// ========
	struct EFI_TIME {
		UINT16 Year; // 1900 - 9999
		UINT8 Month; // 1 - 12
		UINT8 Day; // 1 - 31
		UINT8 Hour; // 0 - 23
		UINT8 Minute; // 0 - 59
		UINT8 Second; // 0 - 59
		UINT8 Pad1;
		UINT32 Nanosecond; // 0 - 999,999,999
		INT16 TimeZone; // -1440 to 1440 or 2047
		UINT8 Daylight;
		UINT8 Pad2;
	};
	static const auto EFI_TIME_ADJUST_DAYLIGHT = 0x01;
	static const auto EFI_TIME_IN_DAYLIGHT = 0x02;
	static const auto EFI_UNSPECIFIED_TIMEZONE = 0x07FF;

	struct EFI_TIME_CAPABILITIES {
		UINT32 Resolution;
		UINT32 Accuracy;
		BOOLEAN SetsToZero;
	};

public:
	// ========
	// 仮想メモリー関連
	// ========
	struct EFI_MEMORY_DESCRIPTOR {
		UINT32 Type;
		EFI_PHYSICAL_ADDRESS PhysicalStart;
		EFI_VIRTUAL_ADDRESS VirtualStart;
		UINT64 NumberOfPages;
		UINT64 Attribute;
	};

public:
	// ========
	// その他
	// ========
	enum EFI_RESET_TYPE  {
		ResetCold,
		ResetWarm,
		ResetShutdown,
		ResetPlatformSpecific,
	};

public:
	struct Base {
		EFI_TABLE_HEADER	Hdr;

		// 時刻
		EFI_STATUS(*GetTime)(EFI_TIME* Time, EFI_TIME_CAPABILITIES* Capabilities);
		EFI_STATUS(*SetTime)(EFI_TIME* Time);
		EFI_STATUS(*GetWakeupTime)(BOOLEAN* Enabled, BOOLEAN* Pending, EFI_TIME* Time);
		EFI_STATUS(*SetWakeupTime)(BOOLEAN* Enabled, EFI_TIME* Time);

		// 仮想メモリー
		EFI_STATUS(*SetVirtualAddressMap)(UINTN MemoryMapSize, UINTN DescriptorSize, UINT32 DescriptorVersion, EFI_MEMORY_DESCRIPTOR* VirtualMap);
		EFI_STATUS(*ConvertPointer)(UINTN DebugDisposition, VOID** Address);

		// 変数
		EFI_STATUS(*GetVariable)(CHAR16* VariableName, EFI_GUID* VendorGuid, UINT32* Attributes, UINTN* DataSize, VOID* Data);
		EFI_STATUS(*GetNextVariableName)(UINTN* VariableNameSize, CHAR16* VariableName, EFI_GUID* VendorGuid);
		EFI_STATUS(*SetVariable)(CHAR16* VariableName, EFI_GUID* VendorGuid, UINT32 Attributes, UINTN DataSize, VOID* Data);

		// その他
		EFI_STATUS(*GetNextHighMonotonicCount)(UINT32* HighCount);
		VOID(*ResetSystem)(EFI_RESET_TYPE ResetType, EFI_STATUS ResetStatus, UINTN DataSize, VOID* ResetData);
	};
};


#endif // __UEFI__EFI_RUNTIME_SERVICES_H__
