#include "EFI.h"
#include "EFI_GraphicsOutputProtocol.h"

extern "C" {
	EFI_STATUS EFIAPI EfiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);
}

EFI_STATUS EFIAPI
EfiMain(EFI_HANDLE /* ImageHandle */, EFI_SYSTEM_TABLE* SystemTable) {

	EFI_GraphicsOutputProtocol pcGraphics = EFI_GraphicsOutputProtocol(SystemTable);
	pcGraphics.ClearRGB(255, 255, 255);

	while (TRUE) {
	}


	return EFI_SUCCESS;
}
