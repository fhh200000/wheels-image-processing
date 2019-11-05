/*
 图形图像处理技术的主函数。
 此处使用了图形库OpenGL与图形辅助库GLUT进行图像的输出。
 Copyright Igniculus 2019, licensed under GNU GPL 3.
*/
//通过向functions.h中申明图像处理函数完成功能扩展。
#include "functions.h"
#include "vardefs.h"

#include <FreeImage.h>
int imagewidth,imageheight;
static GLubyte *pixeldata,*origdata;
FIBITMAP *dib ;
float angle=0.0;
void keyboardProc(unsigned char button, int x, int y)
{
#ifdef DEBUG
    printf("%d\n",button);
#endif // DEBUG
    switch(button)
    {
    case 109:case 77:{showmenu();break;}    //'m'/'M'
    case  99:case 67:{memset(pixeldata,0,imageheight*imagewidth*3);renderScene();break;}    //'c'/'C'
    case 100:case 68:{decolourer_plain(imagewidth,imageheight,pixeldata);renderScene();break;}    //'c'/'C'
    case 114:case 82:{memcpy(pixeldata,origdata,imageheight*imagewidth*3);renderScene();break;}    //'r'/'R'
    case 103:case 71:{blur_gauss(imagewidth,imageheight,pixeldata);renderScene();break;}    //'g'/'G'
    case 104:case 72:{sharpen_horizontal(imagewidth,imageheight,pixeldata,(button-72));renderScene();break;}    //'h'/'H'
    case 118:case 86:{sharpen_vertical(imagewidth,imageheight,pixeldata,(button-86));renderScene();break;}    //'v'/'V'
    case 111:case 79:{sharpen_robert(imagewidth,imageheight,pixeldata,(button-79));renderScene();break;}    //'o'/'O'
    case 112:case 80:{sharpen_priwitt(imagewidth,imageheight,pixeldata,(button-80));renderScene();break;}    //'p'/'P'
    case 107:case 75:{blur_knn(imagewidth,imageheight,pixeldata);renderScene();break;}    //'k'/'K'
    case 122:case 90:{blur_medium(imagewidth,imageheight,pixeldata);renderScene();break;}    //'z'/'Z'
    case 120:case 88:{FreeImage_Unload(dib);exit(0);}   //'x'/'X'
    default:{printf("不支持的功能入口。\n");}
    }
    printf("就绪。\n");
}
void renderScene(void)
{
    glDrawPixels(imagewidth,imageheight,GL_BGR_EXT,GL_UNSIGNED_BYTE,pixeldata);
    glFlush();
}
void showmenu(void)
{
    printf(\
           "欢迎使用图形图像处理系统。\n\
请在图形界面直接按下对应按键。\n\
目前，支持的选项有：\n\
C.清空。\n\
D.标准去色。\n\
H.水平锐化（不混合）。\n\
h.水平锐化（混合）。\n\
V.垂直锐化（不混合）。\n\
v.垂直锐化（混合）。\n\
O.Robert锐化（不混合）。\n\
o.Robert锐化（混合）。\n\
P.Priwitt锐化（不混合）。\n\
p.Priwitt锐化（混合）。\n\
G.高斯模糊。\n\
Z.中值模糊。\n\
K.KNN中值模糊。\n\
X.退出程序。\n\
R.恢复源数据。\n\
M.打印菜单。\n");
}
int main(int argc, char **argv)
{
    //打开文件
    char* filename="/home/fhh/ImageProcessing/aoe.bmp";
    FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(filename, 0);
    dib = FreeImage_Load(fifmt,filename, 0);
    dib = FreeImage_ConvertTo24Bits(dib);   //convert to 24 bits
    imagewidth = FreeImage_GetWidth(dib);    //get the width of texture
    imageheight = FreeImage_GetHeight(dib);  //height
    pixeldata = (GLubyte*)FreeImage_GetBits(dib); //pixels
    origdata = (GLubyte*)malloc(imageheight*imagewidth*3);
    memcpy(origdata,pixeldata,imageheight*imagewidth*3);
    glutInit(&argc, argv);
    showmenu();
    glutInitDisplayMode(GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(imagewidth,imageheight);
    glutCreateWindow("图形图像处理技术预览窗口");
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(keyboardProc);

    glutMainLoop();
    FreeImage_Unload(dib);
}
