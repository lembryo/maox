#ifndef __UEFI__EFI_BOOT_SERVICES_H__
#define __UEFI__EFI_BOOT_SERVICES_H__

typedef UINTN EFI_TPL;
typedef UINT64 EFI_PHYSICAL_ADDRESS;
typedef UINT64 EFI_VIRTUAL_ADDRESS;

class EFI_BootServices {
public:
	static const auto SIGNATURE = 0x56524553544f4f42;
	static const auto REVISION = EFI_SPECIFICATION_VERSION;

public:
	// ========
	// タスク優先度関連
	// ========
	enum EFI_TPL {
		APPLICATION = 4,
		CALLBACK = 8,
		NOTIFY = 16,
		HIGH_LEVEL = 31,
	};

public:
	// ========
	// メモリー関連
	// ========
	enum EFI_MEMORY {
		UC = 0x00000001,
		WC = 0x00000002,
		WT = 0x00000004,
		WB = 0x00000008,
		UCE = 0x00000010,
		WP = 0x00001000,
		RP = 0x00002000,
		XP = 0x00004000,
		NV = 0x00008000,
		MORE_RELIABLE = 0x00010000,
		RO = 0x00020000,
		SP = 0x00040000,
		CPU_CRYPTO = 0x00080000,
		RUNTIME = -1,
	};

	enum EFI_ALLOCATE_TYPE {
		AllocateAnyPages,
		AllocateMaxAddress,
		AllocateAddress,
		MaxAllocateType
	};

	enum EFI_MEMORY_TYPE {
		ReservedMemoryType,
		LoaderCode,
		LoaderData,
		BootServicesCode,
		BootServicesData,
		RuntimeServicesCode,
		RuntimeServicesData,
		ConventionalMemory,
		UnusableMemory,
		ACPIReclaimMemory,
		ACPIMemoryNVS,
		MemoryMappedIO,
		MemoryMappedIOPortSpace,
		PalCode,
		PersistentMemory,
		MaxMemoryType
	};

	struct EFI_MEMORY_DESCRIPTOR {
		UINT32 Type;
		EFI_PHYSICAL_ADDRESS PhysicalStart;
		EFI_VIRTUAL_ADDRESS VirtualStart;
		UINT64 NumberOfPages;
		UINT64 Attribute;
	};

public:
	// ========
	// プロトコルハンドラ関連
	// ========
	enum EFI_INTERFACE_TYPE {
		EFI_NATIVE_INTERFACE
	};

	enum EFI_LOCATE_SEARCH_TYPE {
		AllHandles,
		ByRegisterNotify,
		ByProtocol
	};

	struct EFI_DEVICE_PATH_PROTOCOL {
		UINT8 Type;
		UINT8 SubType;
		UINT8 Length[2];
	};

public:
	// ========
	// イベントとタイマー関連
	// ========
	typedef VOID(*EFI_EVENT_NOTIFY)(EFI_EVENT Event, LPVOID Context);

	enum EFI_TIMER_DELAY {
		TimerCancel,
		TimerPeriodic,
		TimerRelative
	};

public:
	struct EFI_OPEN_PROTOCOL_INFORMATION_ENTRY {
		EFI_HANDLE AgentHandle;
		EFI_HANDLE ControllerHandle;
		UINT32 Attributes;
		UINT32 OpenCount;
	};

public:
	// ========
	// BootServices 本体
	// ========
	struct Base {
		EFI_TABLE_HEADER Hdr;

		// タスク優先度
		EFI_TPL(*RaiseTPL)(EFI_TPL NewTpl);
		VOID(*RestoreTPL)(EFI_TPL OldTpl);

		//　メモリー
		EFI_STATUS(*AllocatePages)(EFI_ALLOCATE_TYPE Type, EFI_MEMORY_TYPE MemoryType, UINTN Pages, EFI_PHYSICAL_ADDRESS* Memory);
		EFI_STATUS(*FreePages)(EFI_PHYSICAL_ADDRESS Memory, UINTN Pages);
		EFI_STATUS(*GetMemoryMap)(UINTN* MemoryMapSize, EFI_MEMORY_DESCRIPTOR* MemoryMap, UINTN* MapKey, UINTN* DescriptorSize, UINT32* DescriptorVersion);
		EFI_STATUS(*AllocatePool)(EFI_MEMORY_TYPE PoolType, UINTN Size, LPVOID* Buffer);
		EFI_STATUS(*FreePool)(LPVOID Buffer);

		// イベントとタイマー
		EFI_STATUS(*CreateEvent)(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, LPVOID NotifyContext, EFI_EVENT* Event);
		EFI_STATUS(*SetTimer)(EFI_EVENT Event, EFI_TIMER_DELAY Type, UINT64 TriggerTime);
		EFI_STATUS(*WaitForEvent)(UINTN NumberOfEvents, EFI_EVENT* Event, UINTN* Index);
		EFI_STATUS(*SignalEvent)(EFI_EVENT Event);
		EFI_STATUS(*CloseEvent)(EFI_EVENT Event);
		EFI_STATUS(*CheckEvent)(EFI_EVENT Event);

		// プロトコルハンドラ
		EFI_STATUS(*InstallProtocolInterface)(EFI_HANDLE* Handle, EFI_GUID* Protocol, EFI_INTERFACE_TYPE InterfaceType, LPVOID Interface);
		EFI_STATUS(*ReinstallProtocolInterface)(EFI_HANDLE Handle, EFI_GUID* Protocol, LPVOID OldInterface, LPVOID NewInterface);
		EFI_STATUS(*UninstallProtocolInterface)(EFI_HANDLE Handle, EFI_GUID* Protocol, LPVOID Interface);
		EFI_STATUS(*HandleProtocol)(EFI_HANDLE Handle, EFI_GUID* Protocol, LPVOID Interface);
		LPVOID Reserved;
		EFI_STATUS(*RegisterProtocolNotify)(EFI_GUID* Protocol, EFI_EVENT Event, LPVOID* Registration);
		EFI_STATUS(*LocateHandle)(EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID* Protocol, LPVOID SearchKey, UINTN* BufferSize, EFI_HANDLE* Buffer);
		EFI_STATUS(*LocateDevicePath)(EFI_GUID* Protocol, EFI_DEVICE_PATH_PROTOCOL** DevicePath, EFI_HANDLE* Device);
		EFI_STATUS(*InstallConfigurationTable)(EFI_GUID* Guid, LPVOID Table);

		// イメージ
		EFI_STATUS(*LoadImage)(BOOLEAN BootPolicy, EFI_HANDLE ParentImageHandle, EFI_DEVICE_PATH_PROTOCOL* DevicePath, LPVOID SourceBuffer, UINTN SourceSize, EFI_HANDLE* ImageHandle);
		EFI_STATUS(*StartImage)(EFI_HANDLE ImageHandle, UINTN* ExitDataSize, CHAR16** ExitData);
		EFI_STATUS(*Exit)(EFI_HANDLE ImageHandle, EFI_STATUS ExitStatus, UINTN ExitDataSize, CHAR16* ExitData);
		EFI_STATUS(*UnloadImage)(EFI_HANDLE ImageHandle);
		EFI_STATUS(*ExitBootServices)(EFI_HANDLE ImageHandle, UINTN MapKey);

		// 
		EFI_STATUS(*GetNextMonotonicCount)(UINT64* Count);
		EFI_STATUS(*Stall)(UINTN Microseconds);
		EFI_STATUS(*SetWatchdogTimer)(UINTN Timeout, UINT64 WatchdogCode, UINTN DataSize, CHAR16* WatchdogData);

		// ドライバサポート
		EFI_STATUS(*ConnectController)(EFI_HANDLE ControllerHandle, EFI_HANDLE* DriverImageHandle, EFI_DEVICE_PATH_PROTOCOL* RemainingDevicePath, BOOLEAN Recursive);
		EFI_STATUS(*DisconnectController)(EFI_HANDLE ControllerHandle, EFI_HANDLE DriverImageHandle, EFI_HANDLE ChildHandle);

		// プロトコル
		EFI_STATUS(*OpenProtocol)(EFI_HANDLE Handle, EFI_GUID* Protocol, VOID** Interface, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle, UINT32 Attributes);
		EFI_STATUS(*CloseProtocol)(EFI_HANDLE Handle, EFI_GUID* Protocol, EFI_HANDLE AgentHandle, EFI_HANDLE ControllerHandle);
		EFI_STATUS(*OpenProtocolInformation)(EFI_HANDLE Handle, EFI_GUID* Protocol, EFI_OPEN_PROTOCOL_INFORMATION_ENTRY** EntryBuffer, UINTN* EntryCount);

		// ライブラリ
		EFI_STATUS(*ProtocolsPerHandle)(EFI_HANDLE Handle, EFI_GUID*** ProtocolBuffer, UINTN* ProtocolBufferCount);
		EFI_STATUS(*LocateHandleBuffer)(EFI_LOCATE_SEARCH_TYPE SearchType, EFI_GUID* Protocol, LPVOID SearchKey, UINTN* NoHandles, EFI_HANDLE** Buffer);
		EFI_STATUS(*LocateProtocol)(EFI_GUID* Protocol, LPVOID Registration, LPVOID* Interface);
		EFI_STATUS(*InstallMultipleProtocolInterfaces)(EFI_HANDLE* Handle, ...);
		EFI_STATUS(*UninstallMultipleProtocolInterfaces)(EFI_HANDLE* Handle, ...);

		// CRC
		EFI_STATUS(*CalculateCrc32)(LPVOID Data, UINTN DataSize, UINT32* Crc32);

		// 
		VOID(*CopyMem)(LPVOID Destination, LPVOID Source, UINTN Length);
		VOID(*SetMem)(LPVOID Buffer, UINTN Size, UINT8 Value);
		EFI_STATUS(*CreateEventEx)(UINT32 Type, EFI_TPL NotifyTpl, EFI_EVENT_NOTIFY NotifyFunction, LPVOID NotifyContext, EFI_GUID* EventGroup, EFI_EVENT* Even);
	};
};


#endif // __UEFI__EFI_BOOT_SERVICES_H__
