#pragma once
//�ӵ����������װ�ã���ߵ����57���ұߵ����82
#include <opencv2/opencv.hpp>

//����ͷ�ķֱ��ʣ�ͼ�γߴ磺��ȣ�
static const int IMAGEWIDTH = 1280;
//����ͷ�ķֱ��ʣ�ͼ�γߴ磺�߶ȣ�  
static const int IMAGEHEIGHT = 1024;
static const double fx1 = 3431.98083802910;
static const double fy1 = 3431.81948404018;
static const double cx1 =634.418202639601;
static const double cy1 = 497.053019167256;
static const double skew1 = -0.446233215802896;

//�ڲξ���  MATLABԭ��������Ҫת�ú�ʹ��
//fx  0    u0
//0   fy   v0
//0   0    1

static const cv::Mat CAMERAMATRIX = (cv::Mat_<double>(3, 3) << fx1, skew1, cx1, 0, fy1, cy1, 0, 0, 1);

//���������� K1 K2 P1 P2 K3
static const cv::Mat DISTORTION = (cv::Mat_<double>(5, 1)
		<<-0.0628714882602943	,0.399222366948931 ,-0.000374675352017216	,-0.000672312413328586,	6.54608952883462);

