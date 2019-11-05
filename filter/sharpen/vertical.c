/*
 垂直锐化的主函数。
 输入图形数据，套用模板后输出。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#include "../../vardefs.h"
void blend(pixel* origpixel,pixel* deltapixel,int width,int height);
void sharpen_vertical(int width,int height,void* bufferdata,bool doblend)
{
/*
    Filter:
    |1  0 -1|
    |2  0 -2|
    |1  0 -1|
*/
    //内存中的数据按照RGBRGB…………的顺序存储，因此只需将图像数据强制转化成“像素”结构体的指针即可。
    pixel* pixeldata = (pixel*) bufferdata;
    //创建临时内存空间。
    pixel* pixeltemp = (pixel*)malloc(width*height*sizeof(pixel));
    int tmpR,tmpG,tmpB;
    int filter[3][3] =
	{ {1,0,-1},
	  {2,0,-2},
	  {1,0,-1} };
    for(int i=1;i<height-1;i++)
        for(int j=1;j<width-1;j++)
        {
            tmpR = (abs(
                ((pixeldata[(i-1)*width+j-1].R)*filter[0][0])+
                ((pixeldata[(i-1)*width+j  ].R)*filter[0][1])+
                ((pixeldata[(i-1)*width+j+1].R)*filter[0][2])+
                ((pixeldata[(i+1)*width+j-1].R)*filter[2][0])+
                ((pixeldata[(i+1)*width+j  ].R)*filter[2][1])+
                ((pixeldata[(i+1)*width+j+1].R)*filter[2][2])));
            tmpG = (abs(
                (pixeldata[(i-1)*width+j-1].G)*filter[0][0]+
                (pixeldata[(i-1)*width+j  ].G)*filter[0][1]+
                (pixeldata[(i-1)*width+j+1].G)*filter[0][2]+
                (pixeldata[(i+1)*width+j-1].G)*filter[2][0]+
                (pixeldata[(i+1)*width+j  ].G)*filter[2][1]+
                (pixeldata[(i+1)*width+j+1].G)*filter[2][2]));
            tmpB = (abs(
                (pixeldata[(i-1)*width+j-1].B)*filter[0][0]+
                (pixeldata[(i-1)*width+j  ].B)*filter[0][1]+
                (pixeldata[(i-1)*width+j+1].B)*filter[0][2]+
                (pixeldata[(i+1)*width+j-1].B)*filter[2][0]+
                (pixeldata[(i+1)*width+j  ].B)*filter[2][1]+
                (pixeldata[(i+1)*width+j+1].B)*filter[2][2]));
            if(tmpR>255)
                tmpR = 255;
            if(tmpG>255)
                tmpG = 255;
            if(tmpB>255)
                tmpB = 255;
            pixeltemp[(i)*width+j].R = (unsigned char)tmpR;
            pixeltemp[(i)*width+j].G = (unsigned char)tmpG;
            pixeltemp[(i)*width+j].B = (unsigned char)tmpB;
        }
    if(doblend)

        blend(pixeltemp,pixeldata,width,height);
    //将运算结果拷贝回原数组。
    memcpy(bufferdata,pixeltemp,width*height*3);
    free(pixeltemp);

}
