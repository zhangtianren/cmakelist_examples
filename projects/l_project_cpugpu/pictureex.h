#pragma once
# include "picture.h"

/**
 * 支持多线程处理图形的
 * 减少循环层次
 * 优化访存次数
 * 考虑CPU 中内存cache命中机制
 **/
class PictureEx : public Picture
{
public:
    PictureEx();
    ~PictureEx();

    void setWorkerThreads(unsigned short n);

    // 水平-垂直翻转
    ImageProp* rolloverH();
    ImageProp* rolloverV();

    // 角度旋转
    ImageProp* rotate(short angle);

private:
    unsigned short _workerCount;
};