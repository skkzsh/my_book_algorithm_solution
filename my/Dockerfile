FROM archlinux

RUN pacman -Syu --noconfirm --disable-sandbox make clang gtest
# --disable-sandbox: amd64 on Apple Siliconのimage buildが失敗するためsandbox無効化
