IF NOT EXIST bios64.bin PowerShell -Command Invoke-WebRequest -Uri "https://github.com/BlankOn/ovmf-blobs/raw/master/bios64.bin" -OutFile bios64.bin
SET QEMU="C:\Program Files\qemu\qemu-system-x86_64.exe"
%QEMU% -bios bios64.bin -hda fat:rw:vfat
