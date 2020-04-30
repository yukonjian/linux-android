1. 查看动态库的依赖库
readelf -d xxx.so   //就可以看到xxx.so库所依赖的库
objdump -x libalsa_dsp.so | grep NEEDED //就可以看到xxx.so库所依赖的库
