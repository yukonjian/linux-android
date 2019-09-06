环境上rk3308编译:
cd rk3308
sudo su
./docker.sh         //进入docker
git log             //查看修改
./build.sh  --help   //查看编译选项
./build.sh  rootfs   //编译rootfs
./mkfirmware.sh      //打包？？
exit                //退出docker

docker image
docker image list

mount -t nfs  -o nolock 172.25.2.88:/home/   ./rk3308mount
/////////////////////////////////////////////////////////////////////////////////
scp  root@172.25.2.88:/home/work/RK3308/rockchip_multicodecs.c ./rockchip_multicodecs.c
scp  root@172.25.2.88:/home/work/RK3308/rk3308_codec.c ../codecs/rk3308_codec.c
scp  root@172.25.2.88:/home/work/RK3308/rockchip_multi_dais.c ./rockchip_multi_dais.c

scp  root@172.25.2.88:/home/work/RK3308/rk3308-firefly.dtsi ./
scp  root@172.25.2.88:/home/work/RK3308/rk3308-evb-dmic-pdm-v11.dts ./


scp  root@172.25.2.88:/home/work/RK3308/module_init.c ./module_init.c
scp ./rockdev/boot.img  root@172.25.2.88:/home/work/RK3308/



V:\work\RK3308\rk3308_codec.c

/home/project/buildroot/output/rockchip_rk3308_release/host/usr/bin/output/host/usr/bin/aarch64-rockchip-linux-gnu-gcc main.c -o test

/home/project/buildroot/output/firefly_rk3308_release/host/bin/aarch64-rockchip-linux-gnu-readelf

umask 0022 && make -C /home/project/buildroot O=/home/project/buildroot/output/firefly_rk3308_release busybox-update-config

umask 0022 && make -C /home/project/buildroot O=/home/project/buildroot/output/firefly_rk3308_release busybox-update-config
/usr/bin/install -m 0644 support/misc/target-dir-warning.txt /home/project/buildroot/output/firefly_rk3308_release/target/THIS_IS_NOT_YOUR_ROOT_FILESYSTEM
/home/project/buildroot/output/firefly_rk3308_release/host/bin/mksquashfs /home/project/buildroot/output/firefly_rk3308_release/target /home/project/buildroot/output/firefly_rk3308_release/images/rootfs.squashfs -noappend -processors 24 -comp gzip
./mksquashfs ./target rootfs.img -noappend -processors  -comp lzma

./mksquashfs ./target ./rootfs.squashfs -noappend -processors 24 -comp gzip

./mksquashfs ./target ./rootfs.squashfs -noappend -processors 24 -comp gzip

mount -t jffs2 /dev/mtdblock5 /app

mount -t ext2 /dev/mmcblk1p8 /tmp/test/

[  143.110602] rk_gmac-dwmac ff4e0000.ethernet eth0: Link is Down

[   22.174784] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: rk_vendor_read eth mac address failed (-1)
[   22.174907] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: generate random eth mac address: 16:15:ff:$ cc:64:79
[   22.174942] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: rk_vendor_write eth mac address failed (-1)
[   22.174989] rk_gmac-dwmac ff4e0000.ethernet: rk_get_eth_addr: mac address: 16:15:ff:cc:64:79
[   22.175056] eth0: device MAC address 16:15:ff:cc:64:79

mkfs.jffs2 --eraseblock=0x10000 -l -n --pad=0x100000 -d ./factory -o ./config-new.img
export LD_LIBRARY_PATH=./:$LD_LIBRARY_PATH
