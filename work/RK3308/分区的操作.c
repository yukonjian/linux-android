1. 擦除一块分区
dd bs=1024k count=1 if=/dev/zero of=/dev/rkflash0p5
2. 格式化分区
mkfs.ext2 ./dev/rkflash0p5
