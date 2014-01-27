#include <windows.h>
#include <iostream>
#include <time.h>
#include <Ole2.h>
#include <fstream>
#include <string>
#include <vector>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>

#include <NuiApi.h>
#include <NuiImageCamera.h>
#include <NuiSensor.h>
#include <NuiSkeleton.h>

const int kColorWidth				= 640;
const int kColorHeight				= 480; 
const int kDepthWidth				= 640;
const int kDepthHeight				= 480; 
const int kSkeletonWidth			= 640; 
const int kSkeletonHeight			= 480; 
const int kChannel					= 3;
const int kKinectDepthMin			= 800; 
const int kKinectDepthMax			= 3810;
const int kKinectDepthNearModeMin	= 400; 
const int kKinectDepthNearModeMax	= 2980; 



class KinectSensor
{
	// Property: 
	// 1. Display and record
	// 2. Mapping class
	// 3. ??? 
public: 
	INuiSensor* g_pNuiSensor_; 
	KinectSensor(); 
	~KinectSensor(); 
	HANDLE hc_event_; 
	HANDLE hc_frame_; 
	HANDLE hd_event_; 
	HANDLE hd_frame_; 

	BYTE * color_buffer_; 
	BYTE * depth_buffer_; 
	cv::Mat color_frame_; 
	cv::Mat depth_frame_; 



	// initilization
	int Init(); 
	int DrawColorFrame(int datalog_name); 
	int DrawDepthFrame(int datalog_name); 
}; 