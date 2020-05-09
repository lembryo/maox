#include "EFI.h"
#include "EFI_GraphicsOutputProtocol.h"

extern "C" {
	EFI_STATUS EFIAPI EfiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable);
}



EFI_STATUS EFIAPI
EfiMain(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable) {

	var pcGraphics = EFI_GraphicsOutputProtocol(SystemTable);

	// ExitBootServices
	EFI_BootServices::EFI_MEMORY_DESCRIPTOR* mmap = NULL;
	var mmap_size = 0ULL;
	var mmap_desc_size = 0ULL;
	{
		var map_key = 0ULL;
		var version = 0UL;
		var status = 0ULL;
		
		// メモリーマップを取得する
		do {
			// 成功するまでループ
			status = SystemTable->BootServices->GetMemoryMap(&mmap_size, mmap, &map_key, &mmap_desc_size, &version);
			while (status != EFI_SUCCESS) {
				if (mmap) {
					SystemTable->BootServices->FreePool(reinterpret_cast<LPVOID>(mmap));
				}
				SystemTable->BootServices->AllocatePool(EFI_BootServices::LoaderData, mmap_size, (void**)(&mmap));
				status = SystemTable->BootServices->GetMemoryMap(&mmap_size, mmap, &map_key, &mmap_desc_size, &version);
			}

			// ExitBootServices が失敗する場合があるらしいのでこちらも成功するまでループ
			status = SystemTable->BootServices->ExitBootServices(ImageHandle, map_key);
		} while (status != EFI_SUCCESS);
	}

	// ExitBootServices 後に画面を真っ白にしてみる
	pcGraphics.ClearRGB(255, 255, 255);
	while (TRUE) {
	}

	return EFI_SUCCESS;
}
