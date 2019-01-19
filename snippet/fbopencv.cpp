#include <unistd.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <fcntl.h>  
#include <string.h>  
#include <linux/fb.h>  
#include <sys/mman.h>  
#include <sys/ioctl.h>  
#include <arpa/inet.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void showMatToFb(Mat img, char* fbc, int x0, int y0);

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        cout << "no image selected or no fb dev selected!\n";
        return -1;
    }
    
    Mat img = imread(argv[1]);
    if(img.empty())
    {
        cout << "image read failed!\n";
        return -1;
    }
    
    int x = 0, y = 0;
    if(argc >= 5)
    {
        x = atoi(argv[3]);
        y = atoi(argv[4]);
    }
    
    showMatToFb(img, argv[2], x, y);
    
    return 0;
}    

void showMatToFb(Mat img, char* fbc, int x0, int y0)
{
    char *fbp;
    int fbfd = 0;
    struct fb_fix_screeninfo finfo;
    struct fb_var_screeninfo vinfo;
    long int screensize = 0;
    
    fbfd = open(fbc, O_RDWR);
    if(!fbfd)
    {
        cout << "error open fb device\n";
        return;
    }
    
    if(ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo))
    {
        cout << "error read fixed information.\n";
        return;
    }
    
    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo))  
    {  
        cout << "error read variable information.\n";
        return; 
    }
    
    screensize = vinfo.xres_virtual * vinfo.yres_virtual * vinfo.bits_per_pixel / 8;
    fbp = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);
    if((int)fbp == -1)
    {
        cout << "error map framebuffer device to memory.\n";
        return;
    }
    
    cout << "xres: " << vinfo.xres << ", yres:" << vinfo.yres << endl;
    cout << "xres_virtual: " << vinfo.xres_virtual << ", yres_virtual:"
        << vinfo.yres_virtual << endl;
    
    for(int y=0; y<img.rows; y++)
    {
        int sy = y+y0;
        
        if(sy < 0)
            continue;
        if(sy >= vinfo.yres_virtual)
            break;
        
        for(int x=0; x<img.cols; x++)
        {
            int sx = x+x0;
            
            if(sx>vinfo.xres_virtual || sx<0)
                continue;
            
            long int offset = sy * finfo.line_length + sx * vinfo.bits_per_pixel / 8;
            
            *(fbp + offset + 0) = img.at<Vec3b>(y,x)[0];
            *(fbp + offset + 1) = img.at<Vec3b>(y,x)[1];
            *(fbp + offset + 2) = img.at<Vec3b>(y,x)[2];
        }
    }
    
    vinfo.yoffset = 1;  
    ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo);
    vinfo.yoffset = 0;  
    ioctl(fbfd, FBIOPUT_VSCREENINFO, &vinfo);
    
    munmap(fbp, screensize);
    
    close(fbfd);
    
    return;
}
