



#include "picture.h"
#include <memory>

int main(void)
{
	std::shared_ptr<Picture> p1 = std::make_shared<Picture>();

    printf("start");
    p1->read("abc.bmp");

    Picture::ImageProp* ph = p1->rolloverH();
    Picture::ImageProp* pv = p1->rolloverV();

    p1->write("abc_h.bmp", *ph);
    p1->write("abc_v.bmp", *pv);

    p1->releaseImageProp(&ph);
    p1->releaseImageProp(&pv);
	return 0;
}