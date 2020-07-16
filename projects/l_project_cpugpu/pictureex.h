# include "picture.h"

class PictureEx : public Picture
{
    PictureEx();
    ~PictureEx();

    void setWorkerThreads(unsigned short n);

    // 水平-垂直翻转
    void rolloverH();
    void rolloverV();

    // 角度旋转
    void rotate(short angle);

};