#include "picture.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

Picture::Picture()
{
    memset(&_ip, 0, sizeof (_ip));
}
Picture::~Picture()
{
    releaseImagePropData(&_ip);
}

void Picture::read(const char* filepath)
{
    FILE* f = fopen(filepath, "rb");
    if (f == NULL)
        return;

    read((void*)f);
    fclose(f);
}
void Picture::read(const void* pFile)
{
    FILE* f = (FILE*)pFile;
    // unsigned char* data = (unsigned char*)malloc(54);
    // fread(data, sizeof(unsigned char), 54, f);
    
    // int width = *(int*)(data + 18);
    // int height = *(int*)(data + 22);
    // memcpy(&(_ip.header), data, 54);

    fread(&(_ip.header), sizeof(unsigned char), sizeof(_ip.header), f);

    int width       = _ip.header.infoHeader.biWidth;
    int height      = _ip.header.infoHeader.biHeight;
    int reserveSize = 0;

    _ip.pixelsH     = width;
    _ip.pixelsV     = height;
    _ip.bytesH      = (_ip.pixelsH * 3 +3 ) & (~3);
    _ip.data        = (unsigned char**)malloc(_ip.pixelsV * height * sizeof (unsigned char));
    reserveSize     = _ip.header.fileHeader.bfOffBits - sizeof(BMP_HEADER);
    printf("read file, width %d height %d, start bytes %d, reserve %d\n", 
        width, height, _ip.header.fileHeader.bfOffBits, reserveSize);

    if (reserveSize > 0)
    {
        _ip.reserved = (unsigned char*)malloc(reserveSize);
        fread(_ip.reserved, sizeof(unsigned char), reserveSize, f);
    }
    
    for (int i=0;i<height;i++)
    {
        _ip.data[i] = (unsigned char*)malloc(_ip.bytesH * sizeof(unsigned char));
    }

    for (int i=0;i<height;i++)
    {
        fread(_ip.data[i], sizeof(unsigned char), _ip.bytesH , f);
    }
}
void Picture::write(const char* filepath, const ImageProp& ip)
{
    FILE* f = fopen(filepath, "wb");
    if (f == NULL)
        return;
    write((void*)f, ip);
    fclose(f);
}
void Picture::write(const void* pFile, const ImageProp& ip)
{
    FILE* f = (FILE*) pFile;

    int headerSize = sizeof(BMP_HEADER);
    int reservedSize = ip.header.fileHeader.bfOffBits - sizeof(BMP_HEADER);
    fwrite(&ip.header, sizeof(unsigned char), headerSize, f);

    if (reservedSize > 0 && ip.reserved)
    {
        fwrite(ip.reserved, sizeof(unsigned char), reservedSize, f);
    }

    for (int i=0;i<ip.pixelsV;i++)
    {
        fwrite(ip.data[i], sizeof(unsigned char), ip.bytesH , f);
    }
}


Picture::ImageProp* Picture::_prepareImageProp()
{
    ImageProp* res  = _prepareImagePropEx();

    res->data = (unsigned char**)malloc(_ip.pixelsV  * sizeof (unsigned char*));
    for (int i=0;i<_ip.pixelsV;i++)
    {
        res->data[i] = (unsigned char*)malloc(_ip.bytesH * sizeof(unsigned char));
    }

    return res;
}

Picture::ImageProp* Picture::_prepareImagePropEx()
{
    ImageProp* res  = new ImageProp();
    memset(res, 0, sizeof(ImageProp));

    res->pixelsH    = _ip.pixelsH;
    res->pixelsV    = _ip.pixelsV;
    res->bytesH     = _ip.bytesH;
    memcpy(&(res->header), &(_ip.header), sizeof(BMP_HEADER));
    int reserveSize = _ip.header.fileHeader.bfOffBits - sizeof(BMP_HEADER);
    if (reserveSize > 0 && _ip.reserved)
    {
        res->reserved = (unsigned char*)malloc(reserveSize);
        memcpy(res->reserved, _ip.reserved, reserveSize);
    }

    res->data = NULL;
    return res;
}

// 水平-垂直翻转
Picture::ImageProp* Picture::rolloverH()
{
    ImageProp* res = _prepareImageProp();

    for (int k = 0;k<_ip.pixelsV;k++)
    {
        for (int i=0;i<_ip.bytesH;i+=3)
        {
            res->data[k][i]     = _ip.data[k][_ip.bytesH - 3 - i];
            res->data[k][i + 1] = _ip.data[k][_ip.bytesH - 2 - i];
            res->data[k][i + 2] = _ip.data[k][_ip.bytesH - 1 - i];
        }
    }

    return res;
}
Picture::ImageProp* Picture::rolloverV()
{
    ImageProp* res = _prepareImageProp();

    for (int i=0;i<_ip.pixelsV;i++)
    {
        memcpy(res->data[i], _ip.data[_ip.pixelsV - i - 1], _ip.bytesH);
    }

    return res;
}
Picture::Triplet Picture::line_sum(unsigned int y, unsigned int x1, unsigned int x2 )
{
    Triplet trp = {0};
    for (unsigned int i = x1;i <= x2; i++)
    {
        trp.a += _ip.data[y][i*3];
        trp.b += _ip.data[y][i*3+1];
        trp.c += _ip.data[y][i*3+2];
    }
    return trp;
}

Picture::Triplet Picture::wavefilter_sum(unsigned int x, unsigned int y, unsigned int r)
{
    Triplet p = {0 ,0 , 0};
    unsigned int rall = 0;
    unsigned int gall = 0;
    unsigned int ball = 0;

    for (int i = y - r; i <= y + r; i++ )
    {
        for (int j = x - r; j <= x + r; j++)
        {
            rall += _ip.data[i][j*3];
            gall += _ip.data[i][j*3+1];
            ball += _ip.data[i][j*3+2];
        }
    }
    p.a = rall;
    p.b = gall;
    p.c = ball;
    return p;
}

unsigned int Picture::wavefilter_count(unsigned int r)
{
    return (2 * r + 1) * (2 * r + 1);
}

Picture::Pixel Picture::wavefilter_avg(unsigned int x, unsigned int y, unsigned int r)
{
    
    Pixel p = {0 ,0 , 0};
    if (x - r < 0 || x + r > _ip.pixelsH + 1 ||
        y - r < 0 || y + r > _ip.pixelsH + 1 )
        return p;

    unsigned int count = wavefilter_count(r);
    Triplet trp = wavefilter_sum(x, y, r);

    p.R = trp.a / count;
    p.G = trp.b / count;
    p.B = trp.c / count;
    return p;
}


Picture::ImageProp* Picture::blurred(int r)
{
    if (r < 1 || r >= _ip.pixelsV || r >= _ip.pixelsH)
        return NULL;
    ImageProp* res = _prepareImageProp();

    for (int i=r;i<_ip.pixelsV-r;i++)
    {
        for (int j=r; j<_ip.pixelsH-r;j++)
        {
            Pixel p = wavefilter_avg(j, i, r);
            res->data[i][j*3] = p.R;
            res->data[i][j*3 + 1] = p.G;
            res->data[i][j*3 + 2] = p.B;
        }
    }
    return res;
}

// 角度旋转
Picture::ImageProp* Picture::rotate(short angle)
{
    return NULL;
}

// rgb 24位 彩色图像变为 B&W 8位 图像
Picture::ImageProp* Picture::tobwimage()
{
    ImageProp* bwimage = _prepareImagePropEx();
    bwimage->bytesH = _ip.pixelsH;
    bwimage->data = (unsigned char**)malloc(_ip.pixelsV * sizeof (unsigned char*));
    for (int i=0;i<_ip.pixelsV;i++)
    {
        bwimage->data[i] = (unsigned char*)malloc(_ip.pixelsH * sizeof(unsigned char));
    }
    
    for (unsigned int i = 0; i < _ip.pixelsV; i++)
    {
        for (unsigned int j = 0; j < _ip.pixelsH; j++)
        {
            unsigned int x = j*3;
            bwimage->data[i][x] = (_ip.data[i][x] +
                _ip.data[i][x+1] + 
                _ip.data[i][x+2]) / 3;
        }
    }

    return bwimage;
}
    // gaussfilter 平滑滤波减小噪声
Picture::ImageProp* Picture::gaussianfilter() 
{ 
    return NULL;
}
    // 边缘增强
Picture::ImageProp* Picture::sobel() 
{ 
    return NULL;
}
    // B&W灰度转二值黑白图像
Picture::ImageProp* Picture::threshold() 
{ 
    return NULL;
}



// 释放图像
void Picture::releaseImageProp(ImageProp** ppIp)
{
    int reserveSize = (*ppIp)->header.fileHeader.bfOffBits - sizeof(BMP_HEADER);
    if (reserveSize > 0 && (*ppIp)->reserved)
    {
        free((*ppIp)->reserved);
        (*ppIp)->reserved = NULL;
    }

    releaseImagePropData(*ppIp);
    free(*ppIp);
    *ppIp = NULL;
}

// 释放图像数据区
void Picture::releaseImagePropData(ImageProp* pIp)
{
    if (pIp->data == NULL)
        return;
    
    for (int i=0;i<pIp->pixelsV;i++)
    {
        if (pIp->data[i] != NULL)
            free(pIp->data[i]);
    }
    free(pIp->data);
    pIp->data = NULL;
}