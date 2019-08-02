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
/////////////////////////////////////////////////////////////////////////////////
scp  root@172.25.2.88:/home/work/RK3308/rockchip_multicodecs.c ./rockchip_multicodecs.c
scp  root@172.25.2.88:/home/work/RK3308/rk3308_codec.c ../codecs/rk3308_codec.c
scp  root@172.25.2.88:/home/work/RK3308/rockchip_multi_dais.c ./rockchip_multi_dais.c

scp  root@172.25.2.88:/home/work/RK3308/module_init.c ./module_init.c
scp ./module_init.ko  root@172.25.2.88:/home/work/RK3308/


V:\work\RK3308\rk3308_codec.c
