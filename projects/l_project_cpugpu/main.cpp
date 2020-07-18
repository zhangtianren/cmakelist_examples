
#pragma once
#include "picture.h"
#include "pictureex.h"
#include <sys/time.h>
#include <memory>

void test(std::shared_ptr<Picture> p1)
{
    struct timeval start;
    struct timeval end;
    float timeuse = 0;

    gettimeofday(&start, NULL);
    Picture::ImageProp* ph = p1->rolloverH();
    gettimeofday(&end, NULL);
    timeuse = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("rolloverH cost %.2fms\n", timeuse/1000);

    gettimeofday(&start, NULL);
    Picture::ImageProp* pv = p1->rolloverV();
    gettimeofday(&end, NULL);
    timeuse = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("rolloverV cost %.2fms\n", timeuse/1000);

    gettimeofday(&start, NULL);
    Picture::ImageProp* pr = p1->rotate(45);
    gettimeofday(&end, NULL);
    timeuse = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
    printf("rotate cost %.2fms\n", timeuse/1000);

    p1->write("abc_h.bmp", *ph);
    p1->write("abc_v.bmp", *pv);
    //p1->write("abc_r.bmp", *pr);

    p1->releaseImageProp(&ph);
    p1->releaseImageProp(&pv);
    //p1->releaseImageProp(&pr);
}

void test_normal()
{
    std::shared_ptr<Picture> p1 = std::make_shared<Picture>();
    p1->read("abc.bmp");

    test(p1);
}

void test_ex(int threadnumber)
{
    std::shared_ptr<PictureEx> p1 = std::make_shared<PictureEx>();
    p1->read("abc.bmp");
    p1->setWorkerThreads(threadnumber);

    test(p1);
}

int main(void)
{
	test_normal();
    test_ex(2);
    test_ex(3);
    test_ex(4);
    test_ex(5);
    test_ex(6);
    test_ex(7);
    test_ex(8);
    test_ex(9);
    test_ex(10);
    test_ex(11);
    test_ex(12);
    test_ex(13);

	return 0;
}