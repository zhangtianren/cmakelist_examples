#include "pictureex.h"

#include <list>
#include <deque>
#include <thread>
#include <iostream>
using namespace std;

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
    std::list<std::shared_ptr<std::thread>> listthread;
	for (int i = 0; i < _workerCount; ++i)
	{
        std::shared_ptr<std::thread> th =  std::make_shared<std::thread>(thread(&PictureEx::_rolloverH_thread, this, res, i));
        listthread.push_back(th);
    }

    for (std::shared_ptr<std::thread> th : listthread)
    {
        th->join();
    } 

    // ImageProp* res = _prepareImageProp();
	// for (int i = 0; i < _workerCount; ++i)
	// {
    //     std::thread th = std::thread(&PictureEx::_rolloverH_thread, this, res, i);
    //     th.join();
    // }

    return res;
}

Picture::ImageProp* PictureEx::rolloverV()
{
    if (_workerCount == 1)
    {
        return Picture::rolloverV();
    }
    ImageProp* res = _prepareImageProp();
    std::list<std::shared_ptr<std::thread>> listthread;
	for (int i = 0; i < _workerCount; ++i)
	{
        std::shared_ptr<std::thread> th =  std::make_shared<std::thread>(thread(&PictureEx::_rolloverV_thread, this, res, i));
        listthread.push_back(th);
	}

    for (std::shared_ptr<std::thread> th : listthread)
    {
        th->join();
    } 
    // ImageProp* res = _prepareImageProp();
	// for (int i = 0; i < _workerCount; ++i)
	// {
    //     std::thread th = std::thread(&PictureEx::_rolloverV_thread, this, res, i);
    //     th.join();
    // }

    return res;
}

// 角度旋转
Picture::ImageProp* PictureEx::rotate(short angle)
{
    return NULL;
}

Picture::ImageProp* PictureEx::blurred(int r)
{
    if (_workerCount == 1)
    {
        return Picture::blurred(r);
    }
    ImageProp* res = _prepareImageProp();
    std::list<std::shared_ptr<std::thread>> listthread;
	for (int i = 0; i < _workerCount; ++i)
	{
        std::shared_ptr<std::thread> th =  std::make_shared<std::thread>(thread(&PictureEx::_blurred_thread, this, res, i, r));
        listthread.push_back(th);
	}

    for (std::shared_ptr<std::thread> th : listthread)
    {
        th->join();
    } 

    // ImageProp* res = _prepareImageProp();
	// for (int i = 0; i < _workerCount; ++i)
	// {
    //     std::thread th = std::thread(&PictureEx::_blurred_thread, this, res, i, r);
    //     th.join();
    // }

    return res;
}


void PictureEx::_rolloverH_thread(ImageProp* res , int id)
{
    for (int k = id; k < _ip.pixelsV ;k+=_workerCount)
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
    for (int i = id; i < _ip.pixelsV ; i+=_workerCount)
    {
        //printf("print line %d of thread %d of task %d\n", i, std::this_thread::get_id(), id);
        memcpy(res->data[i], _ip.data[_ip.pixelsV - i - 1], _ip.bytesH);
    }
}

void PictureEx::_blurred_thread(ImageProp* res , int id, int r)
{
    // for (int i=r;i<_ip.pixelsV-r;i++)
    // {
    //     for (int j=id + r; j<_ip.pixelsH-r;j+=_workerCount)
    //     {
    //         Pixel p = wavefilter_avg(j, i, r);
    //         res->data[i][j*3] = p.R;
    //         res->data[i][j*3 + 1] = p.G;
    //         res->data[i][j*3 + 2] = p.B;
    //     }
    // }
    // r25 (t2 11919ms) (t4 12656ms) (t8 12317ms)


    // for (int i=id + r;i<_ip.pixelsV-r;i+=_workerCount)
    // {
    //     for (int j=r; j<_ip.pixelsH-r;j++)
    //     {
    //         Pixel p = wavefilter_avg(j, i, r);
    //         res->data[i][j*3] = p.R;
    //         res->data[i][j*3 + 1] = p.G;
    //         res->data[i][j*3 + 2] = p.B;
    //     }
    // }
    // r25 (t2 12338ms) (t4 10698ms) (t8 10151ms)
    
    unsigned int number = wavefilter_count(r);
    for (int j=id + r; j<_ip.pixelsH-r;j+=_workerCount)
    {
        Triplet sum = { 0, 0, 0};
        std::deque<Triplet> sumque;
        for (int k = 0; k<2*r+1; k++)
        {
            Triplet trp = line_sum(k, j-r, j+r);
            sum.a+= trp.a;
            sum.b+= trp.b;
            sum.c+= trp.c;
            sumque.push_back(trp);
        }
       
        res->data[r][j*3] = sum.a/number;
        res->data[r][j*3 + 1] = sum.b/number;
        res->data[r][j*3 + 2] = sum.c/number;

        for (int i=r+1;i<_ip.pixelsV-r;i++)
        {
            Triplet trp = line_sum(i+r, j-r, j+r);
            Triplet last = sumque.front();
            sumque.pop_front();
            sumque.push_back(trp);

            sum.a = sum.a + trp.a - last.a;
            sum.b = sum.b + trp.b - last.b;
            sum.c = sum.c + trp.c - last.c;

            res->data[i][j*3] = sum.a/number;
            res->data[i][j*3 + 1] = sum.b/number;
            res->data[i][j*3 + 2] = sum.c/number;
        }
    }
    // r25 (t2 1026ms) (t4 665ms) (t8 673ms) (t10 712ms) (t12 669ms)
}

void PictureEx::_rotate_thread(ImageProp* res , int id)
{
    
}