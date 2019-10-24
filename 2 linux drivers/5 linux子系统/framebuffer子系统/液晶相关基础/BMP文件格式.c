BMP文件格式详解
BMP文件格式，又称为Bitmap（位图）或是DIB(Device-Independent Device，设备无关位图)，
是Windows系统中广泛使用的图像文件格式。
它可以不作任何变换地保存图像像素域的数据，因此成为我们取得RAW数据的重要来源。
在BMP文件中，如果一个数据需要用几个字节来表示的话，那么该数据的存放字节顺序为“低地址村存放低位数据，高地址存放高位数据”。
如：RGB的数据，最高位为R,最低位为B;由于window存放为小端方式(little endian)；故先放B,再放G,最后放R
1. BMP文件的结构
BMP文件由文件头、位图信息头、颜色信息（调色板）和图形数据四部分组成。
1.1 BMP文件头（14字节）
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;//位图文件的类型，必须为BM(1-2字节）
    DWORD bfSize;//位图文件的大小，以字节为单位（3-6字节，低位在前）
    WORD bfReserved1;//位图文件保留字，必须为0(7-8字节）
    WORD bfReserved2;//位图文件保留字，必须为0(9-10字节）
    DWORD bfOffBits;//位图数据的起始位置，以相对于位图（11-14字节，低位在前）
    //文件头的偏移量表示，以字节为单位
}__attribute__((packed)) BITMAPFILEHEADER;

2.1 位图信息头（40字节）
typedef struct tagBITMAPINFOHEADER{
    DWORD biSize;//本结构所占用字节数（15-18字节）
    LONG biWidth;//位图的宽度，以像素为单位（19-22字节）
    LONG biHeight;//位图的高度，以像素为单位（23-26字节）
    WORD biPlanes;//目标设备的级别，必须为1(27-28字节）
    WORD biBitCount;//每个像素所需的位数，必须是1（双色），（29-30字节）
    //4(16色），8(256色）16(高彩色)或24（真彩色）之一
    DWORD biCompression;//位图压缩类型，必须是0（不压缩），（31-34字节）
    //1(BI_RLE8压缩类型）或2(BI_RLE4压缩类型）之一
    DWORD biSizeImage;//位图的大小，以字节为单位（35-38字节）
    LONG biXPelsPerMeter;//位图水平分辨率，每米像素数（39-42字节）
    LONG biYPelsPerMeter;//位图垂直分辨率，每米像素数（43-46字节)
    DWORD biClrUsed;//位图实际使用的颜色表中的颜色数（47-50字节）
    DWORD biClrImportant;//位图显示过程中重要的颜色数（51-54字节）
}__attribute__((packed)) BITMAPINFOHEADER;
