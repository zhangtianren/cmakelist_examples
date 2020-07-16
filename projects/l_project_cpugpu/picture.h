#pragma once
#pragma pack (1)
class Picture
{

public:
    typedef struct tag_BMP_FILEHEADER
    { 
        unsigned short  bfType;        //2Bytes，必须为"BM"，即0x424D 才是Windows位图文件
        unsigned int    bfSize;         //4Bytes，整个BMP文件的大小
        unsigned short  bfReserved1;  //2Bytes，保留，为0
        unsigned short  bfReserved2;  //2Bytes，保留，为0
        unsigned int    bfOffBits;     //4Bytes，文件起始位置到图像像素数据的字节偏移量
    } BMP_FILEHEADER;

    typedef struct tag_BMP_INFOHEADER
    {
        int     biSize;    //4Bytes，INFOHEADER结构体大小，存在其他版本I NFOHEADER，用作区分
        int     biWidth;    //4Bytes，图像宽度（以像素为单位）
        int     biHeight;    //4Bytes，图像高度，+：图像存储顺序为Bottom2Top，-：Top2Bottom
        short   biPlanes;    //2Bytes，图像数据平面，BMP存储RGB数据，因此总为1
        short   biBitCount;         //2Bytes，图像像素位数
        int     biCompression;     //4Bytes，0：不压缩，1：RLE8，2：RLE4
        int     biSizeImage;       //4Bytes，4字节对齐的图像数据大小
        int     biXPelsPerMeter;   //4 Bytes，用象素/米表示的水平分辨率
        int     biYPelsPerMeter;   //4 Bytes，用象素/米表示的垂直分辨率
        int     biClrUsed;          //4 Bytes，实际使用的调色板索引数，0：使用所有的调色板索引
        int     biClrImportant;     //4 Bytes，重要的调色板索引数，0：所有的调色板索引都重要
    }BMP_INFOHEADER;

    typedef struct tag_RGBQUAD
    {
        char  rgbBlue;       //指定蓝色强度
        char  rgbGreen;      //指定绿色强度
        char  rgbRed;        //指定红色强度
        char  rgbReserved;   //保留，设置为0
    } RGBQUAD;

    typedef struct tag_BMP_HEADER
    {
        BMP_FILEHEADER fileHeader;      // 文件头
        BMP_INFOHEADER infoHeader;      // 信息头
        //RGBQUAD rgbquad;                // 可选,调色板
    }BMP_HEADER;

    typedef struct tag_ImageProp
    {
        unsigned int pixelsH;           // 水平像素个数 宽
        unsigned int pixelsV;           // 垂直像素个数 高
        BMP_HEADER header;              // bmp头
        unsigned long int bytesH;       // 单行水平像素的字节数 (内存宽度对齐, 所以有可能不是单纯的 pixelsH*3)

        unsigned char* reserved;        // bmp 头到图像数据间的冗余区
        unsigned char** data;           // 图像数据 二维数组 （高 * 水平像素的字节数)
    }ImageProp;

    typedef struct tag_Pixel
    {
        unsigned char R;
        unsigned char G;
        unsigned char B;
    }Pixel;

    Picture();
    ~Picture();

    void read(const char* filepath);
    void read(const void* pFile);
    void write(const char* fildpath, const ImageProp& ip);
    void write(const void* pFile, const ImageProp& ip);

    // 水平-垂直翻转
    ImageProp* rolloverH();
    ImageProp* rolloverV();

    // 角度旋转
    ImageProp* rotate(short angle);

    // 释放图像
    void releaseImageProp(ImageProp** ppIp);
    // 释放图像数据区
    void releaseImagePropData(ImageProp* pIp);

protected:
    ImageProp _ip;
    
};