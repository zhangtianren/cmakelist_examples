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

    _ip.pixelsH     = width;
    _ip.pixelsV     = height;
    _ip.bytesH      = (_ip.pixelsH * 3 +3 ) & (~3);
    _ip.data        = (unsigned char**)malloc(_ip.pixelsV * height * sizeof (unsigned char));

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

    int headersize = sizeof(BMP_HEADER);
    fwrite(&ip.header, sizeof(unsigned char), headersize, f);

    for (int i=0;i<ip.pixelsV;i++)
    {
        fwrite(ip.data[i], sizeof(unsigned char), ip.bytesH , f);
    }
}

// 水平-垂直翻转
Picture::ImageProp* Picture::rolloverH()
{
    ImageProp* res  = new ImageProp();
    memset(res, 0, sizeof(ImageProp));

    res->pixelsH    = _ip.pixelsH;
    res->pixelsV    = _ip.pixelsV;
    res->bytesH     = _ip.bytesH;
    memcpy(&(res->header), &(_ip.header), sizeof(BMP_HEADER));

    res->data = (unsigned char**)malloc(_ip.pixelsV * _ip.pixelsV * sizeof (unsigned char));
    for (int i=0;i<_ip.pixelsV;i++)
    {
        res->data[i] = (unsigned char*)malloc(_ip.bytesH * sizeof(unsigned char));
    }

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
    ImageProp* res  = new ImageProp();
    memset(res, 0, sizeof(ImageProp));

    res->pixelsH    = _ip.pixelsH;
    res->pixelsV    = _ip.pixelsV;
    res->bytesH     = _ip.bytesH;
    memcpy(&(res->header), &(_ip.header), sizeof(BMP_HEADER));

    res->data = (unsigned char**)malloc(_ip.pixelsV * _ip.pixelsV * sizeof (unsigned char));
    for (int i=0;i<_ip.pixelsV;i++)
    {
        res->data[i] = (unsigned char*)malloc(_ip.bytesH * sizeof(unsigned char));
    }

    for (int i=0;i<_ip.pixelsV;i++)
    {
        memcpy(res->data[i], _ip.data[_ip.pixelsV - i - 1], _ip.bytesH);
    }

    return res;
}

// 角度旋转
Picture::ImageProp* Picture::rotate(short angle)
{
    return NULL;
}

// 释放图像
void Picture::releaseImageProp(ImageProp** ppIp)
{
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