#ifndef __UEFI__EFI_GRAPHICS_OUTPUT_PROTOCOL_H__
#define __UEFI__EFI_GRAPHICS_OUTPUT_PROTOCOL_H__

class EFI_GraphicsOutputProtocol {
public:
	static EFI_GUID GUID;
	static const auto REVISION = EFI_SPECIFICATION_VERSION;

public:
	enum EFI_GRAPHICS_PIXEL_FORMAT {
		PixelRedGreenBlueReserved8BitPerColor,
		PixelBlueGreenRedReserved8BitPerColor,
		PixelBitMask,
		PixelBltOnly,
		PixelFormatMax
	};

	enum EFI_GRAPHICS_OUTPUT_BLT_OPERATION  {
		EfiBltVideoFill,
		EfiBltVideoToBltBuffer,
		EfiBltBufferToVideo,
		EfiBltVideoToVideo,
		EfiGraphicsOutputBltOperationMax
	};

	struct EFI_PIXEL_BITMASK {
		UINT32 RedMask;
		UINT32 GreenMask;
		UINT32 BlueMask;
		UINT32 ReservedMask;
	};

	struct EFI_GRAPHICS_OUTPUT_MODE_INFORMATION {
		UINT32 Version;
		UINT32 HorizontalResolution;
		UINT32 VerticalResolution;
		EFI_GRAPHICS_PIXEL_FORMAT PixelFormat;
		EFI_PIXEL_BITMASK PixelInformation;
		UINT32 PixelsPerScanLine;
	};

	struct EFI_GRAPHICS_OUTPUT_BLT_PIXEL {
		UINT8 Blue;
		UINT8 Green;
		UINT8 Red;
		UINT8 Reserved;
	};

	struct EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE {
		UINT32 MaxMode;
		UINT32 Mode;
		EFI_GRAPHICS_OUTPUT_MODE_INFORMATION* Info;
		UINTN SizeOfInfo;
		EFI_PHYSICAL_ADDRESS FrameBufferBase;
		UINTN FrameBufferSize;
	};

public:
	struct Base {
		EFI_STATUS(*QueryMode)(Base* This, UINT32 ModeNumber, UINTN* SizeOfInfo, EFI_GRAPHICS_OUTPUT_MODE_INFORMATION** Info);
		EFI_STATUS(*SetMode)(Base* This, UINT32 ModeNumber);
		EFI_STATUS(*Blt)(Base* This, EFI_GRAPHICS_OUTPUT_BLT_PIXEL* BltBuffer, EFI_GRAPHICS_OUTPUT_BLT_OPERATION BltOperation, UINTN SourceX, UINTN SourceY, UINTN DestinationX, UINTN DestinationY, UINTN Width, UINTN Height, UINTN Delta);
		EFI_GRAPHICS_OUTPUT_PROTOCOL_MODE* Mode;
	};

public:
	explicit EFI_GraphicsOutputProtocol(EFI_SYSTEM_TABLE* SystemTable);
	~EFI_GraphicsOutputProtocol();

	VOID	ClearRGB(INT8 Red, INT8 Green, INT8 Blue);
    LPVOID	GetVRam() const;
	UINT32	GetWidth() const;
	UINT32	GetHeight() const;
	UINT32	GetDelta() const;

private:
	EFI_SYSTEM_TABLE* m_SystemTable;
	Base* m_pcThis = NULL;
};

#endif // __UEFI__EFI_GRAPHICS_OUTPUT_PROTOCOL_H__
