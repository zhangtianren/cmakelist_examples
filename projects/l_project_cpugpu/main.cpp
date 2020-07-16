
#pragma once
#include "picture.h"
#include "pictureex.h"
#include <sys/time.h>
#include <memory>

int main(void)
{
	std::shared_ptr<Picture> p1 = std::make_shared<Picture>();
    p1->read("abc.bmp");

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
	return 0;
}