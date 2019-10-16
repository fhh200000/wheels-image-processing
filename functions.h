/*
 图形图像处理技术的功能列表头文件。
 通过注册不同的函数，来实现不同的图像处理功能。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
//界面渲染函数，位置位于main.c.
void renderScene(void);
//菜单显示函数，位置位于main.c.
void showmenu(void);
//高斯模糊函数，位置位于filter/blur/gauss.c.
void blur_gauss(int width,int height,void* bufferdata);
//中值模糊函数，位置位于filter/blur/medium.c/
void blur_medium(int width,int height,void* bufferdata);

#endif // FUNCTIONS_H_INCLUDED
