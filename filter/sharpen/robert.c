/*
 Robert锐化的主函数。
 输入图形数据，套用交叉微分的近似计算模板后输出。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#include "../../vardefs.h"
#include <math.h>
void blend(pixel* origpixel,pixel* deltapixel,int width,int height);
void sharpen_robert(int width,int height,void* bufferdata,bool doblend)
{
    //内存中的数据按照RGBRGB…………的顺序存储，因此只需将图像数据强制转化成“像素”结构体的指针即可。
    pixel* pixeldata = (pixel*) bufferdata;
    //创建临时内存空间。
    pixel* pixeltemp = (pixel*)malloc(width*height*sizeof(pixel));
     for(int i=1;i<height-1;i++)
     {
        for(int j=1;j<width-1;j++)
        {
            pixeltemp[i*width+j].R = (unsigned char)(
                                        sqrt(pow((int)pixeltemp[i*width+j+width+1].R-pixeltemp[i*width+j].R,2)
                                            +pow((int)pixeltemp[i*width+j+width].R-pixeltemp[i*width+j+1].R,2)));
            pixeltemp[i*width+j].G = (unsigned char)(
                                        sqrt(pow((int)pixeltemp[i*width+j+width+1].G-pixeltemp[i*width+j].G,2)
                                            +pow((int)pixeltemp[i*width+j+width].G-pixeltemp[i*width+j+1].G,2)));
            pixeltemp[i*width+j].B = (unsigned char)(
                                        sqrt(pow((int)pixeltemp[i*width+j+width+1].B-pixeltemp[i*width+j].B,2)
                                            +pow((int)pixeltemp[i*width+j+width].B-pixeltemp[i*width+j+1].B,2)));
        }
    }
    if(doblend)
        blend(pixeltemp,pixeldata,width,height);
    //将运算结果拷贝回原数组。
    memcpy(bufferdata,pixeltemp,width*height*3);
    free(pixeltemp);
}
