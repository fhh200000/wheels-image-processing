#ifndef VARDEFS_H_INCLUDED
#define VARDEFS_H_INCLUDED
#include <stdio.h>
#include <string.h>
//调试选项控制开关。
#define DEBUG
//包含glut头文件。
#include <GL/glut.h>
//设置窗口大小
extern int imagewidth,imageheight;
//定义抽象像素数据类型。
typedef  struct
{
    unsigned char B;
    unsigned char G;
    unsigned char R;
} pixel;
//定义布尔变量和值。
typedef unsigned char bool;
#define true 1
#define false 0
#endif // VARDEFS_H_INCLUDED
