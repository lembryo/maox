#include "EFI.h"
#include "EFI_GraphicsOutputProtocol.h"

EFI_GUID EFI_GraphicsOutputProtocol::GUID = { 0x9042a9de,0x23dc,0x4a38, { 0x96,0xfb,0x7a,0xde,0xd0,0x80,0x51,0x6a } };

EFI_GraphicsOutputProtocol::EFI_GraphicsOutputProtocol(EFI_SYSTEM_TABLE* SystemTable) : m_SystemTable(SystemTable) {
	m_SystemTable->BootServices->LocateProtocol(&EFI_GraphicsOutputProtocol::GUID, NULL, reinterpret_cast<LPVOID*>(&m_pcThis));
}

EFI_GraphicsOutputProtocol::~EFI_GraphicsOutputProtocol() {
}

VOID
EFI_GraphicsOutputProtocol::ClearRGB(INT8 Red, INT8 Green, INT8 Blue) {

	val Base = reinterpret_cast<EFI_GraphicsOutputProtocol::EFI_GRAPHICS_OUTPUT_BLT_PIXEL*>(m_pcThis->Mode->FrameBufferBase);
	val VerticalResolution = m_pcThis->Mode->Info->VerticalResolution;
	val HorizontalResolution = m_pcThis->Mode->Info->HorizontalResolution;
	for (var y = 0ULL; y < VerticalResolution; y++) {
		for (var x = 0ULL; x < HorizontalResolution; x++) {
			EFI_GraphicsOutputProtocol::EFI_GRAPHICS_OUTPUT_BLT_PIXEL* p = Base + (HorizontalResolution * y) + x;
			p->Red = Red;
			p->Green = Green;
			p->Blue = Blue;
			p->Reserved = 0;
		}
	}
}

LPVOID
EFI_GraphicsOutputProtocol::GetVRam() const {
	return reinterpret_cast<LPVOID>(m_pcThis->Mode->FrameBufferBase);
}

UINT32
EFI_GraphicsOutputProtocol::GetWidth() const {
	return m_pcThis->Mode->Info->HorizontalResolution;
}

UINT32
EFI_GraphicsOutputProtocol::GetHeight() const {
	return m_pcThis->Mode->Info->VerticalResolution;
}

UINT32
EFI_GraphicsOutputProtocol::GetDelta() const {
	return m_pcThis->Mode->Info->PixelsPerScanLine;
}
