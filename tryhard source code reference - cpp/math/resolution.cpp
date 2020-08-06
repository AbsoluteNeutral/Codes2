
#include "resolution.h"

namespace zg{
  

	unsigned int GOBAL_RESOLUTION_WIDTH  = 1280;
	unsigned int GOBAL_RESOLUTION_HEIGHT = 720;
	void SetResolution(RESOLUTION_SIZE size_) 
  {
		switch (size_) 
    {
      //4::3
      case R_640x480:		  GOBAL_RESOLUTION_WIDTH = 640;  GOBAL_RESOLUTION_HEIGHT = 480;   break;
      case R_800x600:		  GOBAL_RESOLUTION_WIDTH = 800;  GOBAL_RESOLUTION_HEIGHT = 600;   break;
      case R_960x720: 	  GOBAL_RESOLUTION_WIDTH = 960;  GOBAL_RESOLUTION_HEIGHT = 720;   break;
      case R_1024x768: 	  GOBAL_RESOLUTION_WIDTH = 1024; GOBAL_RESOLUTION_HEIGHT = 768;   break;
      case R_1280x960: 	  GOBAL_RESOLUTION_WIDTH = 1280; GOBAL_RESOLUTION_HEIGHT = 960;   break;
      case R_1440x1050: 	GOBAL_RESOLUTION_WIDTH = 1440; GOBAL_RESOLUTION_HEIGHT = 1050;	break;
      case R_1440x1080: 	GOBAL_RESOLUTION_WIDTH = 1440; GOBAL_RESOLUTION_HEIGHT = 1080;	break;
      case R_1600x1200: 	GOBAL_RESOLUTION_WIDTH = 1600; GOBAL_RESOLUTION_HEIGHT = 1200;	break;
      case R_1856x1392: 	GOBAL_RESOLUTION_WIDTH = 1856; GOBAL_RESOLUTION_HEIGHT = 1392;	break;
      case R_1920x1440: 	GOBAL_RESOLUTION_WIDTH = 1920; GOBAL_RESOLUTION_HEIGHT = 1440;	break;
      case R_2048x1536: 	GOBAL_RESOLUTION_WIDTH = 2048; GOBAL_RESOLUTION_HEIGHT = 1536;	break;
        //16:10
      case R_1280x800: 	  GOBAL_RESOLUTION_WIDTH = 1280; GOBAL_RESOLUTION_HEIGHT = 800;	  break;
      case R_1440x900: 	  GOBAL_RESOLUTION_WIDTH = 1440; GOBAL_RESOLUTION_HEIGHT = 900;	  break;
      case R_1680x1050: 	GOBAL_RESOLUTION_WIDTH = 1680; GOBAL_RESOLUTION_HEIGHT = 1050;	break;
      case R_1920x1200: 	GOBAL_RESOLUTION_WIDTH = 1920; GOBAL_RESOLUTION_HEIGHT = 1200;	break;
      case R_2560x1600: 	GOBAL_RESOLUTION_WIDTH = 2560; GOBAL_RESOLUTION_HEIGHT = 1600;	break;
        //16:9
      case R_1024x576: 	  GOBAL_RESOLUTION_WIDTH = 1024; GOBAL_RESOLUTION_HEIGHT = 576;	  break;
      case R_1152x648: 	  GOBAL_RESOLUTION_WIDTH = 1152; GOBAL_RESOLUTION_HEIGHT = 648;	  break;
      case R_1280x720: 	  GOBAL_RESOLUTION_WIDTH = 1280; GOBAL_RESOLUTION_HEIGHT = 720;	  break;
      case R_1366x768: 	  GOBAL_RESOLUTION_WIDTH = 1366; GOBAL_RESOLUTION_HEIGHT = 768;	  break;
      case R_1600x900: 	  GOBAL_RESOLUTION_WIDTH = 1600; GOBAL_RESOLUTION_HEIGHT = 900;	  break;
      case R_1920x1080: 	GOBAL_RESOLUTION_WIDTH = 1920; GOBAL_RESOLUTION_HEIGHT = 1080;	break;
      case R_2560x1440: 	GOBAL_RESOLUTION_WIDTH = 2560; GOBAL_RESOLUTION_HEIGHT = 1440;	break;
      case R_3840x2160: 	GOBAL_RESOLUTION_WIDTH = 3840; GOBAL_RESOLUTION_HEIGHT = 2160;	break;
      case R_7680x4320:	  GOBAL_RESOLUTION_WIDTH = 7680; GOBAL_RESOLUTION_HEIGHT = 4320;	break;
		}
	}
	void SetResolution(unsigned int* width_, unsigned int* height_, RESOLUTION_SIZE size_) 
  {
    switch (size_) {
      //4::3
      case R_640x480:		  *width_ = 640;  *height_ = 480;		break;
      case R_800x600:		  *width_ = 800;  *height_ = 600;		break;
      case R_960x720: 	  *width_ = 960;  *height_ = 720;		break;
      case R_1024x768: 	  *width_ = 1024; *height_ = 768;		break;
      case R_1280x960: 	  *width_ = 1280; *height_ = 960;		break;
      case R_1440x1050: 	*width_ = 1440; *height_ = 1050;	break;
      case R_1440x1080: 	*width_ = 1440; *height_ = 1080;	break;
      case R_1600x1200: 	*width_ = 1600; *height_ = 1200;	break;
      case R_1856x1392: 	*width_ = 1856; *height_ = 1392;	break;
      case R_1920x1440: 	*width_ = 1920; *height_ = 1440;	break;
      case R_2048x1536: 	*width_ = 2048; *height_ = 1536;	break;
        //16:10
      case R_1280x800: 	  *width_ = 1280; *height_ = 800;		break;
      case R_1440x900: 	  *width_ = 1440; *height_ = 900;		break;
      case R_1680x1050: 	*width_ = 1680; *height_ = 1050;	break;
      case R_1920x1200: 	*width_ = 1920; *height_ = 1200;	break;
      case R_2560x1600: 	*width_ = 2560; *height_ = 1600;	break;
        //16:9
      case R_1024x576: 	  *width_ = 1024; *height_ = 576;		break;
      case R_1152x648: 	  *width_ = 1152; *height_ = 648;		break;
      case R_1280x720: 	  *width_ = 1280; *height_ = 720;		break;
      case R_1366x768: 	  *width_ = 1366; *height_ = 768;		break;
      case R_1600x900: 	  *width_ = 1600; *height_ = 900;		break;
      case R_1920x1080: 	*width_ = 1920; *height_ = 1080;	break;
      case R_2560x1440: 	*width_ = 2560; *height_ = 1440;	break;
      case R_3840x2160: 	*width_ = 3840; *height_ = 2160;	break;
      case R_7680x4320:	  *width_ = 7680; *height_ = 4320;	break;
    }
	}

}//namespace zg
