#ifndef __VIDEOGAME_H
#define __VIDEOGAME_H

#include <TooN/TooN.h>
#include "OpenGL.h"
#include "Game.h"
#include <opencv2/core.hpp>

namespace PTAMM {

using namespace TooN;

class VideoGame : public Game
{
  public:
    VideoGame( );
    void Draw3D( const GLWindow2 &glWindow, Map &map, SE3<> se3CfromW );
    void Reset();
    void Init();

  private:
    double width;
    double height;
    int mnFrameCounter; 
    vector<GLuint> gl_texId; 
    int frame_num;
    GLuint generateTexture(cv::Mat img);
};

}

#endif
