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
  s.P=(point*)malloc(sizeof(point));
  Mat img1=imread("../images/test2.png",CV_LOAD_IMAGE_COLOR);
  //Mat img;
  s.n=0;
  //cout<<img1.rows<<' '<<img1.cols<<endl;
  cv::cvtColor(img1,s.img,CV_BGR2HSV);
  // imshow("img1",img1);
    for(int i=0;i<s.img.rows;i++)
    {
      for(int j=0;j<s.img.cols;j++)
	{
	  s.P=(point*)realloc(s.P,(s.n+1)*sizeof(point));
	  s.P[s.n].h=2*s.img.at<Vec3b>(i,j)[0];
	  s.P[s.n].s=s.img.at<Vec3b>(i,j)[1];
	  s.P[s.n].x=i;
	  s.P[s.n].y=j;
	  s.P[s.n].parent=-1;
	  s.n++;
	  //	  cout<<P[n-1].h<<' '<<P[n-1].s<<' '<<P[n-1].x<<' '<<P[n-1].y<<endl;
	  //waitKey(100);
	}
    }
  cout<<"\nEnter number of clusters\n";
  cin>>s.noc;
  namedWindow("Clusters",WINDOW_AUTOSIZE);
  createTrackbar("Clusters","Clusters",&s.noc,5);
   while(1)
    {
  int *C;
  C=new int[s.noc];
  srand((unsigned)time(NULL));
  for(int i=0;i<s.noc;i++)
    {
      int j=i-1,flag=0;
      C[i]=rand()%s.n;
      while(j>=0)
	{
	  if(C[i]==C[j])
	    {
	      flag=1;
	      break;
	    }
	  j--;
	}
      if(flag)
	i--;
    }
  s.k_means(C);
  Mat cls(s.img.rows,s.img.cols,CV_8UC3,Scalar(0,0,0));
  cvtColor(cls,cls,CV_BGR2HSV);
  int a=0;
  for(int i=0;i<s.n;i++)
    {
      if(s.P[i].parent==C[1])
	{a++;
	  for(int j=0;j<=2;j++)
	    {
	      cls.at<Vec3b>(s.P[i].x,s.P[i].y)[j]=s.img.at<Vec3b>(s.P[C[0]].x,s.P[C[0]].y)[j];
	    }
	}
    }
  imshow("cls",cls);
  imshow("img",s.img);
  waitKey(1);
  }
  waitKey(0);
}
