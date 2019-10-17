/*
 KNN中值模糊的主函数。
 将每个像素的数据逐一取出，进行KNN运算后存入数组。
 为简便运算，此处直接计算出距离后，对距离进行排序。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#include "../../vardefs.h"
int cmp(const void *a , const void *b)
{
        return *(unsigned char *)a - *(unsigned char *)b;
}
void blur_knn(int width,int height,void* bufferdata,int K)
{
     //内存中的数据按照RGBRGB…………的顺序存储，因此只需将图像数据强制转化成“像素”结构体的指针即可。
    pixel* pixeldata = (pixel*) bufferdata;
    //创建临时内存空间。
    pixel* pixeltemp = (pixel*)malloc(width*height*sizeof(pixel));
    unsigned char tempDistanceR[9],tempDistanceG[9],tempDistanceB[9];
    for(int i=1;i<height-1;i++)
        for(int j=1;j<width-1;j++)
        {
            int curr=0;
            for(int k=(i-1);k<(i+2);k++)
            {
                for(int l=k*width+j-1;l<k*width+j+2;l++)
                    {
                        tempDistanceR[curr]=abs(pixeldata[l].R-pixeltemp[i*width+j].R);
                        tempDistanceG[curr]=abs(pixeldata[l].G-pixeltemp[i*width+j].G);
                        tempDistanceB[curr]=abs(pixeldata[l].B-pixeltemp[i*width+j].B);
                        curr++;
                    }
            }
            //排序。
            qsort(tempDistanceR,9,1,cmp);
            qsort(tempDistanceG,9,1,cmp);
            qsort(tempDistanceB,9,1,cmp);
            //查找最接近的K个像素。
            //由于将自身加入比较，第一位必为0(自身)。
            unsigned offsetR=0,offsetG=0,offsetB=0;
            for(int k=0;k<K+1;k++)
            {
                offsetR+=tempDistanceR[k];
                offsetG+=tempDistanceG[k];
                offsetB+=tempDistanceB[k];
            }
            offsetR/=K;
            offsetG/=K;
            offsetB/=K;
            //将数值放回。
            pixeltemp[i*width+j].R += offsetR;
            pixeltemp[i*width+j].G += offsetG;
            pixeltemp[i*width+j].B += offsetB;
        }
    //将运算结果拷贝回原数组。
    memcpy(bufferdata,pixeltemp,width*height*3);
    free(pixeltemp);
}
