
#ifndef _ZG_RESOLUTION_H
#define _ZG_RESOLUTION_H

enum ZG_API ASPECT_RATIO {
  CAM_4_3 = 0,
  CAM_16_10,
  CAM_16_9
};

enum ZG_API RESOLUTION_SIZE {
  //4::3
  R_640x480 = 0,
  R_800x600,
  R_960x720,
  R_1024x768,
  R_1280x960,
  R_1440x1050,
  R_1440x1080,
  R_1600x1200,
  R_1856x1392,
  R_1920x1440,
  R_2048x1536,

  //16:10
  R_1280x800,
  R_1440x900,
  R_1680x1050,
  R_1920x1200,
  R_2560x1600,

  //16:9
  R_1024x576,
  R_1152x648,
  R_1280x720,
  R_1366x768,
  R_1600x900,
  R_1920x1080,
  R_2560x1440,
  R_3840x2160,
  R_7680x4320
};
  
namespace zg
{
	extern unsigned int GOBAL_RESOLUTION_WIDTH;
	extern unsigned int GOBAL_RESOLUTION_HEIGHT;

	void SetResolution(RESOLUTION_SIZE size_);
	void SetResolution(unsigned int* width_, unsigned int* height_, RESOLUTION_SIZE size_);

}

#endif //_ZG_RESOLUTION_H
