/*
 高斯模糊的主函数。
 将每个像素的数据逐一取出，应用模板后存入数组。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#include "../../vardefs.h"

void blur_gauss(int width,int height,GLubyte* bufferdata)
{
    //内存中的数据按照RGBRGB…………的顺序存储，因此只需将图像数据强制转化成“像素”结构体的指针即可。
    pixel* pixeldata = (pixel*) bufferdata;
    //创建临时内存空间。
    pixel* pixeltemp = (pixel*)malloc(width*height*sizeof(pixel));
    double filter[3][3] =
	{ {0.0947416,0.118318,0.0947416},
	  {0.118318 ,0.147761,0.118318},
	  {0.0947416,0.118318,0.0947416} };
    for(int i=1;i<height-1;i++)
        for(int j=1;j<width-1;j++)
        {
            pixeltemp[i*width+j].R = (unsigned char)((pixeldata[(i-1)*width+j-1].R)*filter[0][0]+
                                                     (pixeldata[(i-1)*width+j  ].R)*filter[0][1]+
                                                     (pixeldata[(i-1)*width+j+1].R)*filter[0][2]+
                                                     (pixeldata[( i )*width+j-1].R)*filter[1][0]+
                                                     (pixeldata[( i )*width+j  ].R)*filter[1][1]+
                                                     (pixeldata[( i )*width+j+1].R)*filter[1][2]+
                                                     (pixeldata[(i+1)*width+j-1].R)*filter[2][0]+
                                                     (pixeldata[(i+1)*width+j  ].R)*filter[2][1]+
                                                     (pixeldata[(i+1)*width+j+1].R)*filter[2][2]);
            pixeltemp[i*width+j].G = (unsigned char)((pixeldata[(i-1)*width+j-1].G)*filter[0][0]+
                                                     (pixeldata[(i-1)*width+j  ].G)*filter[0][1]+
                                                     (pixeldata[(i-1)*width+j+1].G)*filter[0][2]+
                                                     (pixeldata[( i )*width+j-1].G)*filter[1][0]+
                                                     (pixeldata[( i )*width+j  ].G)*filter[1][1]+
                                                      (pixeldata[( i )*width+j+1].G)*filter[1][2]+
                                                     (pixeldata[(i+1)*width+j-1].G)*filter[2][0]+
                                                     (pixeldata[(i+1)*width+j  ].G)*filter[2][1]+
                                                     (pixeldata[(i+1)*width+j+1].G)*filter[2][2]);
            pixeltemp[i*width+j].B = (unsigned char)((pixeldata[(i-1)*width+j-1].B)*filter[0][0]+
                                                     (pixeldata[(i-1)*width+j  ].B)*filter[0][1]+
                                                     (pixeldata[(i-1)*width+j+1].B)*filter[0][2]+
                                                     (pixeldata[( i )*width+j-1].B)*filter[1][0]+
                                                     (pixeldata[( i )*width+j  ].B)*filter[1][1]+
                                                     (pixeldata[( i )*width+j+1].B)*filter[1][2]+
                                                     (pixeldata[(i+1)*width+j-1].B)*filter[2][0]+
                                                     (pixeldata[(i+1)*width+j  ].B)*filter[2][1]+
                                                     (pixeldata[(i+1)*width+j+1].B)*filter[2][2]);
        }
    //将运算结果拷贝回原数组。
    memcpy(bufferdata,pixeltemp,width*height*3);
    free(pixeltemp);
}
