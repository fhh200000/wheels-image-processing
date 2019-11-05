/*
 Priwitt锐化的主函数。
 输入图形数据，分别套用水平锐化和垂直锐化的近似计算模板后，使用毕达哥拉斯三角公式计算几何平均值后输出。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#include "../../vardefs.h"
#include <math.h>
#define pythagoras(x,y) (unsigned char)(sqrt(x*x+y*y))
void blend(pixel* origpixel,pixel* deltapixel,int width,int height);
void sharpen_priwitt(int width,int height,void* bufferdata,bool doblend)
{
    /*
    FilterW:
    |-1 -1 -1|
    | 0  0  0|
    | 1  1  1|
     FilterH:
    |-1  0  1|
    |-1  0  1|
    |-1  0  1|
*/
    //内存中的数据按照RGBRGB…………的顺序存储，因此只需将图像数据强制转化成“像素”结构体的指针即可。
    pixel* pixeldata = (pixel*) bufferdata;
    //创建临时内存空间。
    pixel* pixeltemp = (pixel*)malloc(width*height*sizeof(pixel));
    int tmpRW,tmpGW,tmpBW;
    int tmpRH,tmpGH,tmpBH;
    int filterW[3][3] =
	{ {1,1,1},
	  {0,0,0},
	  {-1,-1,-1} };
    int filterH[3][3] =
	{ {-1,0,1},
	  {-1,0,1},
	  {-1,0,1} };
    for(int i=1;i<height-1;i++)
        for(int j=1;j<width-1;j++)
        {
            tmpRW = (abs(
                ((pixeldata[(i-1)*width+j-1].R)*filterW[0][0])+
                ((pixeldata[(i-1)*width+j  ].R)*filterW[0][1])+
                ((pixeldata[(i-1)*width+j+1].R)*filterW[0][2])+
                ((pixeldata[(i+1)*width+j-1].R)*filterW[2][0])+
                ((pixeldata[(i+1)*width+j  ].R)*filterW[2][1])+
                ((pixeldata[(i+1)*width+j+1].R)*filterW[2][2])));
            tmpGW = (abs(
                (pixeldata[(i-1)*width+j-1].G)*filterW[0][0]+
                (pixeldata[(i-1)*width+j  ].G)*filterW[0][1]+
                (pixeldata[(i-1)*width+j+1].G)*filterW[0][2]+
                (pixeldata[(i+1)*width+j-1].G)*filterW[2][0]+
                (pixeldata[(i+1)*width+j  ].G)*filterW[2][1]+
                (pixeldata[(i+1)*width+j+1].G)*filterW[2][2]));
            tmpBW = (abs(
                (pixeldata[(i-1)*width+j-1].B)*filterW[0][0]+
                (pixeldata[(i-1)*width+j  ].B)*filterW[0][1]+
                (pixeldata[(i-1)*width+j+1].B)*filterW[0][2]+
                (pixeldata[(i+1)*width+j-1].B)*filterW[2][0]+
                (pixeldata[(i+1)*width+j  ].B)*filterW[2][1]+
                (pixeldata[(i+1)*width+j+1].B)*filterW[2][2]));
            if(tmpRW>255)
                tmpRW = 255;
            if(tmpGW>255)
                tmpGW = 255;
            if(tmpBW>255)
                tmpBW = 255;
            tmpRH = (abs(
                ((pixeldata[(i-1)*width+j-1].R)*filterH[0][0])+
                ((pixeldata[(i-1)*width+j  ].R)*filterH[0][1])+
                ((pixeldata[(i-1)*width+j+1].R)*filterH[0][2])+
                ((pixeldata[(i+1)*width+j-1].R)*filterH[2][0])+
                ((pixeldata[(i+1)*width+j  ].R)*filterH[2][1])+
                ((pixeldata[(i+1)*width+j+1].R)*filterH[2][2])));
            tmpGH = (abs(
                (pixeldata[(i-1)*width+j-1].G)*filterH[0][0]+
                (pixeldata[(i-1)*width+j  ].G)*filterH[0][1]+
                (pixeldata[(i-1)*width+j+1].G)*filterH[0][2]+
                (pixeldata[(i+1)*width+j-1].G)*filterH[2][0]+
                (pixeldata[(i+1)*width+j  ].G)*filterH[2][1]+
                (pixeldata[(i+1)*width+j+1].G)*filterH[2][2]));
            tmpBH = (abs(
                (pixeldata[(i-1)*width+j-1].B)*filterH[0][0]+
                (pixeldata[(i-1)*width+j  ].B)*filterH[0][1]+
                (pixeldata[(i-1)*width+j+1].B)*filterH[0][2]+
                (pixeldata[(i+1)*width+j-1].B)*filterH[2][0]+
                (pixeldata[(i+1)*width+j  ].B)*filterH[2][1]+
                (pixeldata[(i+1)*width+j+1].B)*filterH[2][2]));
            if(tmpRH>255)
                tmpRH = 255;
            if(tmpGH>255)
                tmpGH = 255;
            if(tmpBH>255)
                tmpBH = 255;
            pixeltemp[(i)*width+j].R = pythagoras(tmpRH,tmpRW);
            pixeltemp[(i)*width+j].G = pythagoras(tmpGH,tmpGW);
            pixeltemp[(i)*width+j].B = pythagoras(tmpBH,tmpBW);
        }
    if(doblend)
        blend(pixeltemp,pixeldata,width,height);
    //将运算结果拷贝回原数组。
    memcpy(bufferdata,pixeltemp,width*height*3);
    free(pixeltemp);

}
