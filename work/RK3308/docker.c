1. docker 安装
1.1 sudo apt-get update
1.2 sudo apt-get install curl -y
1.3 curl -sSL https://get.daocloud.io/docker | sh

3. 加载docker映像(image.tar)
docker load --input image.tar

4. 运行docker
docker run --dns 8.8.8.8 -it --rm -v /etc/timezone:/etc/timezone -v /etc/localtime:/etc/localtime  -e USER_ID=$UID --mount type=bind,source="$PWD",target="/home/project" tchip/buildroot-builder /bin/bash
