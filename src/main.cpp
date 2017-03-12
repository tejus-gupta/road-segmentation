#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

int main()
{
	Mat img=imread("../images/test1.png");
  	imshow("img", img);
  	waitKey(0);

	return 0;
}