FROM archlinux

# --disable-sandbox-syscalls: amd64 on Apple Siliconのimage buildが失敗するためsandbox無効化
RUN pacman -Syu --noconfirm --needed --disable-sandbox-syscalls make clang gtest \
  && pacman -Scc --noconfirm \
  && rm -rf /var/cache/pacman/pkg/*
