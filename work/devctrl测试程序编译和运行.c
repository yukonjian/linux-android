1. 编译
/opt/emlix/pnx8181/bin/arm-linux-gnueabi-gcc -I. -I /home/steven/work/project/xm_c63_t1/include/  -L/home/steven/work/project/xm_c63/target_C63/lib -lrllib -lipc -lipc -lrllib -lrllog -lpthread  -ldevctrl -lcfg -ltinyxml -lntp -lrllib  -lpjlib -lpjlib-util -lssl -lrt  -Wl,-rpath=/home/steven/work/project/xm_c63_t1/build/../target_C63/lib/   test.c -o test

2. 运行
export LD_LIBRARY_PATH=/basic/lib:/app/lib/:$LD_LIBRARY_PATH
