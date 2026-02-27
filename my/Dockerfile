FROM archlinux

RUN pacman -Syu --noconfirm --disable-sandbox-syscalls make clang gtest
# --disable-sandbox-syscalls: amd64 on Apple Siliconのimage buildが失敗するためsandbox無効化
