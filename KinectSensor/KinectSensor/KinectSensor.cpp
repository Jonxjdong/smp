#include "KinectSensor.h"
#include <stdlib.h>
#include <sstream>  
using namespace std;
using namespace cv; 
KinectSensor::KinectSensor()
{
	// color_frame_.create(kColorHeight, kColorWidth, CV_8UC3); 
	// depth_frame_.create(kDepthHeight, kDepthWidth, CV_16U); 
	color_frame_ = Mat(kColorHeight, kColorWidth, CV_8UC3, color_buffer_);
	// depth_frame_ = 
}

KinectSensor::~KinectSensor()
{

}

int KinectSensor::Init()
{
	// check device
	int num_sensors;
    if (NuiGetSensorCount(&num_sensors) < 0 || num_sensors < 1) return false;
    if (NuiCreateSensorByIndex(0, &g_pNuiSensor_) < 0) return false;
	
	HRESULT hr = g_pNuiSensor_->NuiInitialize(NUI_INITIALIZE_FLAG_USES_DEPTH_AND_PLAYER_INDEX |	NUI_INITIALIZE_FLAG_USES_COLOR); 
	if(hr != S_OK)
	{
		std::cout<<"Camera: Fail in Initialization... " << std::endl; 
		return hr; 
	}

	hc_event_ = CreateEvent(NULL, TRUE, FALSE, NULL); 
	hc_frame_ = NULL; 
	hr = g_pNuiSensor_->NuiImageStreamOpen(NUI_IMAGE_TYPE_COLOR, 
		NUI_IMAGE_RESOLUTION_640x480, 0, 2, hc_event_, &hc_frame_); 
	// NUI_IMAGE_RESOLUTION_1280x960; 
	// NUI_IMAGE_RESOLUTION_640x480; 
	if(FAILED(hr))
	{
		std::cout<<"Camera: Fail in Opening Color Image Stream Video... "<< std::endl; 
		return hr; 
	}

	hd_event_ = CreateEvent(NULL, TRUE, FALSE, NULL); 
	hd_frame_ = NULL; 
	hr = g_pNuiSensor_->NuiImageStreamOpen(NUI_IMAGE_TYPE_DEPTH_AND_PLAYER_INDEX, 
		NUI_IMAGE_RESOLUTION_640x480, 0, 2, hd_event_, &hd_frame_);  // enable NEAR_MODE
	// NUI_IMAGE_RESOLUTION_640x480; 
	// NUI_IMAGE_RESOLUTION_320x240;
	// near mode: NUI_IMAGE_STREAM_FLAG_ENABLE_NEAR_MODE; common mode: 0; 
	if(FAILED(hr))
	{
		std::cout<<"Camera: Fail in Opening Depth Image Stream Video... "<< std::endl; 
		return hr; 
	}

	return 0; 
}
int KinectSensor::DrawColorFrame(int datalog_name)
{
	IplImage *tmp_colorframe;    // *************d
	const NUI_IMAGE_FRAME * pImageFrame = NULL; 
	// get the frame of color image; 
	HRESULT hr = NuiImageStreamGetNextFrame(hc_frame_, 0, &pImageFrame); 
	if(FAILED(hr))
	{
		std::cout <<"Camera: Fail in Getting Color Image..." << std::endl; 
		return -1; 
	}
	// store & lock data in "LockedRect"
	INuiFrameTexture * pTexture = pImageFrame->pFrameTexture; 
	NUI_LOCKED_RECT LockedRect; 
	pTexture->LockRect(0, &LockedRect, NULL, 0); 
	if(LockedRect.Pitch != 0)
	{
		color_buffer_ = (BYTE*) LockedRect.pBits; 
		
		cvSetData(tmp_colorframe, color_buffer_, LockedRect.Pitch);   // 
	}
	// cvFlip(color, color, 1); 
	// cvShowImage("Color Image", color_frame_); 
	// unlock the frame 
	ostringstream convert; 
	convert<<"zz_color_"<<datalog_name<<".jpg"; 
	cvSaveImage(convert.str().c_str(), tmp_colorframe);        // 
	// imwrite(convert.str().c_str(), color_frame_); 
	NuiImageStreamReleaseFrame(hc_frame_, pImageFrame); 
	return 0; 
}
