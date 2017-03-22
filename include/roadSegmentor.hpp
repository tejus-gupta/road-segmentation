#ifndef _LANE_SEGMENTOR_HPP_
#define _LANE_SEGMENTER_HPP_

#include "opencv/cv.h"
#include <opencv2/highgui/highgui.hpp>
#include <bits/stdc++.h>
#include<iostream>
#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<time.h>
#include<limits.h>

using namespace cv;
using namespace std;

struct point
{
  int h,s,x,y;
  int parent;
};

class RoadSegmentor{
public:
  point *P;
  Mat img;
  int n,noc;

public:
  void k_means(int* C);
  void group(int* C);
  int centre(int* C,int cen,int sumx,int sumy,int sumh,int sums);
};

#endif /* _LANE_SEGMENTER_HPP_ */
