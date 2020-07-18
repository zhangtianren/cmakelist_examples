#include "pictureex.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <list>
#include <thread>
#include <atomic>

PictureEx::PictureEx()
{
    _workerCount = 4;
}

PictureEx::~PictureEx()
{

}

void PictureEx::setWorkerThreads(unsigned short n)
{
    if (n == 0 || n >= 64)
        return;

    _workerCount = n;
}

// 水平-垂直翻转
Picture::ImageProp* PictureEx::rolloverH()
{
    if (_workerCount == 1)
    {
        return Picture::rolloverH();
    }

    ImageProp* res = _prepareImageProp();
    std::list<std::thread> listThread;
	for (int i = 0; i < _workerCount; ++i)
	{
        std::thread th(std::mem_fn(&PictureEx::_rolloverH_thread), this, i);
		listThread.push_back(th);
	}

    for (auto& th : listThread)
	{
		th.join();
	}

    return res;
}

Picture::ImageProp* PictureEx::rolloverV()
{
    if (_workerCount == 1)
    {
        return Picture::rolloverH();
    }

    ImageProp* res = _prepareImageProp();
    std::list<std::thread> listThread;
	for (int i = 0; i < _workerCount; ++i)
	{
        std::thread th(&PictureEx::_rolloverV_thread, this, i);
		listThread.push_back(th);
	}

    for (auto& th : listThread)
	{
		th.join();
	}

    return res;
}

// 角度旋转
Picture::ImageProp* PictureEx::rotate(short angle)
{
    
}

void PictureEx::_rolloverH_thread(ImageProp* res , int id)
{
    int devide = _ip.pixelsV / _workerCount;

    for (int k = id; k < _ip.pixelsV && (_ip.pixelsV % k == id) ;k+=devide)
    {

        for (int i=0;i<_ip.bytesH;i+=3)
        {
            res->data[k][i]     = _ip.data[k][_ip.bytesH - 3 - i];
            res->data[k][i + 1] = _ip.data[k][_ip.bytesH - 2 - i];
            res->data[k][i + 2] = _ip.data[k][_ip.bytesH - 1 - i];
        }
    }

}
void PictureEx::_rolloverV_thread(ImageProp* res , int id)
{
    int devide = _ip.pixelsV / _workerCount;
    for (int i = id; i < _ip.pixelsV && (_ip.pixelsV % i == id) ; i+=devide)
    {
        memcpy(res->data[i], _ip.data[_ip.pixelsV - i - 1], _ip.bytesH);
    }
}
void PictureEx::_rotate_thread(ImageProp* res , int id)
{
    
}