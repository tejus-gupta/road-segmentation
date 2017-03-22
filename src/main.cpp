#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>
#include<opencv2/imgproc/imgproc.hpp>
#include "../include/roadSegmentor.hpp"

using namespace cv;
using namespace std;

int main()
{
  RoadSegmentor s;
  cout<<"\nEnter number of clusters\n";
  cin>>s.noc;
  Mat img1=imread("../images/test2.png",CV_LOAD_IMAGE_COLOR);
  s.initialize(img1);
  s.k_means();
  s.write();
  waitKey(0);
}
