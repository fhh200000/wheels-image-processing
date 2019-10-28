/*
 普通去色算法的主函数。
 使用传统计算公式计算灰度信息。
 Gray = (0.299*Red+ 0.587*Green+ 0.114*Blue)
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#include "../../vardefs.h"
void decolourer_plain(int width,int height,void* bufferdata)
{
     //内存中的数据按照RGBRGB…………的顺序存储，因此只需将图像数据强制转化成“像素”结构体的指针即可。
    pixel* pixeldata = (pixel*) bufferdata;
    //创建临时内存空间。
    pixel* pixeltemp = (pixel*)malloc(width*height*sizeof(pixel));
    unsigned char tmp_alpha;
    for(int i=0;i<height*width;i++)
    {
        tmp_alpha = (int)(pixeldata[i].R*0.299+pixeldata[i].G*0.587+pixeldata[i].B*0.114);
        pixeltemp[i].R = pixeltemp[i].G = pixeltemp[i].B = tmp_alpha;
    }
    //将运算结果拷贝回原数组。
    memcpy(bufferdata,pixeltemp,width*height*3);
    free(pixeltemp);
}
