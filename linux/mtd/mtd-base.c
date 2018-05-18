1. cat /proc/mtd
dev:    size   erasesize  name
mtd0: 00500000 00020000 "boot"
mtd1: 09100000 00020000 "system"
mtd2: 13580000 00020000 "userdata"

2. cat /proc/partitions
major   minor     #blocks  name
31        0        128 mtdblock0
31        1        128 mtdblock1
31        2        512 mtdblock2
