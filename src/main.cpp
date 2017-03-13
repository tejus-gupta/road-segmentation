#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>
#include "../include/roadSegmentor.hpp"

using namespace cv;
using namespace std;

int main()
{
	Mat img=imread("../images/test2.png");
  	imshow("input", img);

  	RoadSegmentor segmentor;
  	Mat output=segmentor.hsvThres(img);

  	imshow("road", output);
  	imwrite("../images/output.png", output);
  	waitKey(0);

	return 0;
}