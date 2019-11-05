/*
 图形图像处理技术的功能列表头文件。
 通过注册不同的函数，来实现不同的图像处理功能。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "vardefs.h"
//界面渲染函数，位置位于main.c.
void renderScene(void);
//菜单显示函数，位置位于main.c.
void showmenu(void);
//高斯模糊函数，位置位于filter/blur/gauss.c.
void blur_gauss(int width,int height,void* bufferdata);
//中值模糊函数，位置位于filter/blur/medium.c.
void blur_medium(int width,int height,void* bufferdata);
//KNN中值模糊函数，位置位于filter/blur/knn.c.
void blur_knn(int width,int height,void* bufferdata);
//标准RGB转灰度算法，位置位于adjustment/decolourer/plain.c.
void decolourer_plain(int width,int height,void* bufferdata);
//两层图层混合函数，位置位于filter/sharpen/horizontal.c.
void blend(pixel* origpixel,pixel* deltapixel,int width,int height);
//水平方向锐化函数，位置位于filter/sharpen/horizontal.c.
void sharpen_horizontal(int width,int height,void* bufferdata,bool doblend);
//垂直方向锐化函数，位置位于filter/sharpen/horizontal.c.
void sharpen_vertical(int width,int height,void* bufferdata,bool doblend);
//Robert锐化函数，位置位于filter/sharpen/robert.c.
void sharpen_robert(int width,int height,void* bufferdata,bool doblend);
//Priwitt锐化函数，位置位于filter/sharpen/priwitt.c.
void sharpen_priwitt(int width,int height,void* bufferdata,bool doblend);

#endif // FUNCTIONS_H_INCLUDED
