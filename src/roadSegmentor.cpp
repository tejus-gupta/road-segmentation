#include "../include/roadSegmentor.hpp"

using namespace std;
using namespace cv;

int isvalid(Mat img,int i,int j)
{
  if(i<0 || i>=img.rows || j<0 || j>=img.cols)
    return 0;
  return 1;
}

void RoadSegmentor::k_means()
{
  ct++;
  if(ct>50)
    {
      cout<<"Iterations="<<ct<<endl;
      return;
    }
  Mat cls(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
  int a=0,road=0;
  for(int k=0;k<noc;k++){
  for(int i=0;i<n;i++)
    {
      if(P[i].x==380 && P[i].y==240)
	road=i;
      if(P[i].parent==C[k])
  	{a++;
  	  for(int j=0;j<=2;j++)
  	    {
  	      cls.at<Vec3b>(P[i].x,P[i].y)[j]=img.at<Vec3b>(P[C[k]].x,P[C[k]].y)[j];
  	    }
  	}
    }}
  for(int k=0;k<noc;k++)
    {
      for(int i=P[C[k]].x-1;i<=P[C[k]].x+1;i++)
	for(int j=P[C[k]].y-1;j<=P[C[k]].y+1;j++)
	  {
	    if(isvalid(cls,i,j)==0)
	      continue;
	    cls.at<Vec3b>(i,j)={179,255,255};
	  }
    }
  // road=P[road].parent;
  // for(int i=0;i<n;i++)
  //   {
  //   if(P[i].parent==road)
  //     cls.at<Vec3b>(P[i].x,P[i].y)={0,0,0};
  //   else cls.at<Vec3b>(P[i].x,P[i].y)={179,255,255};
  //   }  


  // imshow("img",img);
  // imshow("cls",cls);
  // waitKey(100);





  int sumx=0,sumy=0,count=0,sumh=0,sums=0;
    group();
    int flag=0;
  for(int i=0;i<noc;i++)
    {
      sumx=sumy=sumh=sums=count=0;
      for(int j=0;j<n;j++)
	{
	  if(P[j].parent!=C[i])
	    continue;
	  sumx+=P[j].x;
	  sumy+=P[j].y;
	  sumh+=P[j].h;
	  sums+=P[j].s;
	  count++;
	}
       if(count==0)
	continue;
      sumx/=count;
      sumy/=count;
      sumh/=count;
      sums/=count;
      // cout<<sumx<<' '<<sumy<<' '<<sumh<<' '<<sums;
      flag+=centre(i,sumx,sumy,sumh,sums);
    }
  if(flag==noc-1)
    {
      cout<<endl<<"Iterations="<<ct<<endl;
      return;
    }
   k_means();
}

void RoadSegmentor::group()
{
  for(int i=0;i<n;i++)
    {
      for(int j=0;j<noc;j++)
	if(i==C[j])
	  continue;
      int dist=INT_MAX,min;
      for(int j=0;j<noc;j++)
	{
	  int d=sqrt(pow(P[i].h-P[C[j]].h,2)+pow(P[i].s-P[C[j]].s,2)+pow(P[i].x-P[C[j]].x,1)+pow(P[i].y-P[C[j]].y,1));
	  if(d<dist)
	      {
		dist=d;
		min=C[j];
	      }
	}
      P[i].parent=min;
    }
}

int RoadSegmentor::centre(int cen,int sumx,int sumy,int sumh,int sums)
{
  int small=INT_MAX,min=0;
  for(int i=0;i<n;i++)
    {
      int d=sqrt(pow(P[i].h-sumh,2)+pow(P[i].s-sums,2)+pow(P[i].x-sumx,1)+pow(P[i].y-sumy,1));
      if(small>d)
	{
	  small=d;
	  min=i;
	}
    }
  if(C[cen]==min)
    return 1;
  C[cen]=min;
  return 0;
}

int* RoadSegmentor::initialize(Mat img1)
{
  ct=0;
  P=(point*)malloc(sizeof(point));
  n=0;
  cv::cvtColor(img1,img,CV_BGR2HSV);
  // imshow("img1",img1);
    for(int i=0;i<img.rows;i++)
    {
      for(int j=0;j<img.cols;j++)
	{
	  P=(point*)realloc(P,(n+1)*sizeof(point));
	  P[n].h=2*img.at<Vec3b>(i,j)[0];
	  P[n].s=img.at<Vec3b>(i,j)[1];
	  P[n].x=i;
	  P[n].y=j;
	  P[n].parent=-1;
	  n++;
	  //cout<<P[n-1].h<<' '<<P[n-1].s<<' '<<P[n-1].x<<' '<<P[n-1].y<<endl;
	  //waitKey(100);
	}
    }
    C=new int[noc];
    srand((unsigned)time(NULL));
    for(int i=0;i<noc;i++)
    {
      int j=i-1,flag=0;
      C[i]=rand()%n;
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
}

void RoadSegmentor::write()
{
  Mat cls(img.rows,img.cols,CV_8UC3,Scalar(0,0,0));
  cvtColor(cls,cls,CV_BGR2HSV);
  for(int k=0;k<noc;k++)
    {
      for(int i=0;i<n;i++)
  	{
  	  if(P[i].parent==C[k])
  	    {
  	      for(int j=0;j<=2;j++)
  		{
  		  cls.at<Vec3b>(P[i].x,P[i].y)[j]=img.at<Vec3b>(P[C[k]].x,P[C[k]].y)[j];
  		}
  	    }
  	}
    }
  cout<<"Written in images/output.png\n";
  waitKey(1);
  imwrite("../images/output.png",cls);

}
