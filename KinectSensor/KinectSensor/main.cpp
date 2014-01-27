#include <iostream>
#include "KinectSensor.h"
using namespace cv; 
using namespace std; 

int test_01_color(); 
int test_opencv(); 

int main()
{
	int a; 
	a = test_01_color(); 
	return a; 
}

int test_opencv()
{
	
	float arr[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
	Mat xx; 
	xx = Mat(3, 3, CV_32F, arr); 

	int datalog_name = 1; 
	ostringstream convert; 
	convert<<"zz_color_"<<datalog_name<<".jpg"; 
	// cvSaveImage(convert.str().c_str(), color_frame_);        // 
	imwrite(convert.str().c_str(), xx); 



	std::cout<<"Display: "<< xx << std::endl; 
	return 0; 

}

int test_01_color()
{
	KinectSensor *camera = new KinectSensor(); 
	camera->Init(); 
	camera->DrawColorFrame(0); 
	return 0; 
}