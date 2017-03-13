#include "../include/roadSegmentor.hpp"

using namespace std;
using namespace cv;

cv::Mat RoadSegmentor::hsvThres(cv::Mat img)
{
	int low1, low2, low3, high1, high2, high3;
	namedWindow("thresholding window", 1);
	createTrackbar("low1", "thresholding window", &low1, 255);
	createTrackbar("high1", "thresholding window", &high1, 255);
	createTrackbar("low2", "thresholding window", &low2, 255);
	createTrackbar("high2", "thresholding window", &high2, 255);
	createTrackbar("low3", "thresholding window", &low3, 255);
	createTrackbar("high3", "thresholding window", &high3, 255);

	low1=1; low2=67; low3=0;
	high1=58; high2=166; high3=23;

	cvtColor(img, img, CV_BGR2HLS);
	Mat output;
	while(true)
	{
		output=img-img;
		for(int i=0;i<img.rows;i++)
			for(int j=0;j<img.cols;j++)
				if(img.at<Vec3b>(i,j)[0]>low1 && img.at<Vec3b>(i,j)[1]>low2 && img.at<Vec3b>(i,j)[2]>low3 && img.at<Vec3b>(i,j)[0]<high1 && img.at<Vec3b>(i,j)[1]<high2 && img.at<Vec3b>(i,j)[2]<high3)
					output.at<Vec3b>(i,j)={255,255,255};
				else 
					output.at<Vec3b>(i,j)={0,0,0};
		//inRange(img,Scalar(low1,low2,low3), Scalar(high1,high2,high3),output);
		imshow("output", output);
		char c=waitKey(10);
		if((int)c==27)
			break;
	}

	medianBlur(output, output, 7);
	cvtColor(output, img, CV_HLS2BGR);
	return img;
}