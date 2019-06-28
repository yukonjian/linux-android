iperf1. 基本使用
static int devctrl_get_link_by_ioctl(char *net_iface_name)
{
	struct mii_data *mii = NULL;
	int sockfd;
	struct ifreq ifr;
	int ret = 0;

	if(net_iface_name == NULL)
	{
		return 0;
	}

	if((sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		rl_log_err("socket failed.");
		return 0;
	}

	memset(&ifr, '\0', sizeof(ifr));
	strncpy(ifr.ifr_name, net_iface_name, IFNAMSIZ - 1);
	mii = (struct mii_data*)&ifr.ifr_data;
	mii->reg_num = 0x01;
	if(ioctl(sockfd, SIOCGMIIREG, &ifr) == -1)
	{
		close(sockfd);
		rl_log_err("ioctl SIOCGMIIREG failed.");
		return 0;
	}

	if(mii->val_out & 0x20)
	{
		ret = 1;
	}
	else
	{
		ret = 0;
	}

	close(sockfd);

	return ret;
}
AF_INET（又称 PF_INET）是 IPv4 网络协议的套接字类型
AF_INET6 则是 IPv6 的；
AF_UNIX 则是 Unix 系统本地通信。

SOCK_STREAM是基于TCP的，数据传输比较有保障。
SOCK_DGRAM是基于UDP的，专门用于局域网，基于广播
