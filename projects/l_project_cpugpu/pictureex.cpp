#include "pictureex.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

PictureEx::PictureEx()
{
    
}

PictureEx::~PictureEx()
{

}

void PictureEx::setWorkerThreads(unsigned short n)
{

}

// 水平-垂直翻转
Picture::ImageProp* PictureEx::rolloverH()
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

Picture::ImageProp* PictureEx::rolloverV()
{

}

// 角度旋转
Picture::ImageProp* PictureEx::rotate(short angle)
{
    
}