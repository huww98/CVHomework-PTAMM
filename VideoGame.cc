#include "VideoGame.h"
#include <cvd/convolution.h>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>

namespace PTAMM
{

using namespace CVD;

VideoGame::VideoGame()
    : Game("Video")
{
    height = 1.0;
    width = 1.0;
    mnFrameCounter = 0;
    frame_num=0;
}

void VideoGame::Init()
{
    string filename = "01.avi";
    cv::VideoCapture capture(filename);
    if (!capture.isOpened())
    {
        std::cerr << "Read video Failed !" << std::endl;
        return;
    }
    frame_num = capture.get(cv::CAP_PROP_FRAME_COUNT);
    
    cv::Mat img;
    while (true)
    {
        capture >> img;
        gl_texId.push_back(generateTexture(img));
        if (img.empty())
        {
            std::cerr << "File ended" << std::endl;
            break;
        }
    }
    capture.release();
}

void VideoGame::Draw3D(const GLWindow2 &glWindow, Map &map, SE3<> se3CfromW)
{
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, gl_texId[mnFrameCounter]);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3f, -0.3f, 0.0f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3f, 0.3f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.3f, 0.3f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.3f, -0.3f, 0.0f);
    glEnd();

    mnFrameCounter++;
    if(mnFrameCounter>=frame_num){
        mnFrameCounter=0;
    }
}

void VideoGame::Reset()
{
}

GLuint VideoGame::generateTexture(cv::Mat img)
{
    cv::Mat imgRgba;
    cv::cvtColor(img, imgRgba, cv::COLOR_BGR2RGBA);

    GLint last_texture_ID;
    GLuint texture_ID = 0;
    glGenTextures(1, &texture_ID);
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture_ID);
    glBindTexture(GL_TEXTURE_2D, texture_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.cols, img.rows,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, imgRgba.data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, last_texture_ID);
    return texture_ID;
}
} // namespace PTAMM
