#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>
#include "../include/roadSegmentor.hpp"

using namespace cv;
using namespace std;

int main()
{
	Mat img=imread("../images/test1.png");
  	imshow("input", img);

  	RoadSegmentor segmentor;
  	Mat output=segmentor.hsvThres(img);

  	imshow("road", output);
  	waitKey(0);

	return 0;
}