
#pragma once
#include "picture.h"
#include "pictureex.h"
#include <iostream>
#include <set>
#include <sys/time.h>

std::set<char> cmd_set;

void test(Picture* p1, int threadnumber)
{
    char filename[256];
    

    struct timeval start;
    struct timeval end;
    float timeuse = 0;

    if (cmd_set.find('h') != cmd_set.end())
    {
        gettimeofday(&start, NULL);
        Picture::ImageProp* ph = p1->rolloverH();
        gettimeofday(&end, NULL);
        timeuse = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
        printf("%d rolloverH cost %.2fms\n", threadnumber, timeuse/1000);

        sprintf(filename, "%d_abc_h.bmp", threadnumber);
        p1->write(filename, *ph);

        p1->releaseImageProp(&ph);
    }

    if (cmd_set.find('v') != cmd_set.end())
    { 
        gettimeofday(&start, NULL);
        Picture::ImageProp* pv = p1->rolloverV();
        gettimeofday(&end, NULL);
        timeuse = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
        printf("%d rolloverV cost %.2fms\n", threadnumber,  timeuse/1000);

        sprintf(filename, "%d_abc_v.bmp", threadnumber);
        p1->write(filename, *pv);

        p1->releaseImageProp(&pv);
    }

    if (cmd_set.find('r') != cmd_set.end())
    { 
        gettimeofday(&start, NULL);
        Picture::ImageProp* pr = p1->rotate(45);
        gettimeofday(&end, NULL);
        timeuse = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
        printf("%d rotate cost %.2fms\n", threadnumber,  timeuse/1000);

        //p1->write("abc_r.bmp", *pr);

        p1->releaseImageProp(&pr);
    }   
    
    if (cmd_set.find('b') != cmd_set.end())
    { 
        gettimeofday(&start, NULL);
        Picture::ImageProp* pblurred = p1->blurred(20);
        gettimeofday(&end, NULL);
        timeuse = (end.tv_sec-start.tv_sec)*1000000+(end.tv_usec-start.tv_usec);//微秒
        printf("%d blurred cost %.2fms\n", threadnumber,  timeuse/1000);

        sprintf(filename, "%d_abc_blurred.bmp", threadnumber);
        p1->write(filename, *pblurred);
        
        p1->releaseImageProp(&pblurred);
    }
    
}

void test_normal()
{
    Picture* p1 = new Picture();
    p1->read("abc.bmp");

    test(p1, 1);
    delete p1;
}

void test_ex(int threadnumber)
{
    PictureEx* p1 = new PictureEx();
    p1->read("abc.bmp");
    p1->setWorkerThreads(threadnumber);

    test(p1, threadnumber);
    delete p1;
}

int main(int argc,char *argv[])
{
    if (argc != 3)
    {
        printf("l_cpugpu [threadnum] !!\n");
        return 1;
    }

    std::string s_cmd = argv[2];

    for (int i=0;i< s_cmd.length();i++)
    {
        cmd_set.insert(s_cmd.at(i));
    }

    test_ex(atoi(argv[1]));

	return 0;
}
