/*
 中值模糊的主函数。
 将每个像素的数据逐一取出，取出中位数后存入数组。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#include "../../vardefs.h"
int cmp(const void *a , const void *b);
void blur_medium(int width,int height,void* bufferdata)
{
     //内存中的数据按照RGBRGB…………的顺序存储，因此只需将图像数据强制转化成“像素”结构体的指针即可。
    pixel* pixeldata = (pixel*) bufferdata;
    //创建临时内存空间。
    pixel* pixeltemp = (pixel*)malloc(width*height*sizeof(pixel));
    unsigned char tempR[9],tempG[9],tempB[9];
    for(int i=1;i<height-1;i++)
        for(int j=1;j<width-1;j++)
        {
            int curr=0;
            for(int k=(i-1);k<(i+2);k++)
            {
                for(int l=k*width+j-1;l<k*width+j+2;l++)
                    {
                        tempR[curr]=pixeldata[l].R;
                        tempG[curr]=pixeldata[l].G;
                        tempB[curr++]=pixeldata[l].B;
                    }
            }
            //排序。
            qsort(tempR,9,1,cmp);
            qsort(tempG,9,1,cmp);
            qsort(tempB,9,1,cmp);
            //将数值放回。
            pixeltemp[i*width+j].R = tempR[4];
            pixeltemp[i*width+j].G = tempG[4];
            pixeltemp[i*width+j].B = tempB[4];
        }
    //将运算结果拷贝回原数组。
    memcpy(bufferdata,pixeltemp,width*height*3);
    free(pixeltemp);
}

