#include <iostream>
#include<opencv2/imgproc.hpp>
#include "opencv2/calib3d.hpp"
#include "CameraParams.h"
typedef struct {
	cv::Point2i cpt;
	int agl= 0;
} CptAgl;
CptAgl CptAgl1;


//显示图片
void DisplayImage(std::string winname, cv::Mat img) {
	cv::namedWindow(winname, cv::WINDOW_NORMAL);
	cv::imshow(winname, img);
	cv::waitKey();
}
int main() {
	cv::Point2i center(cx1,cy1);
	cv::Mat img = cv::imread("./right.jpg");
	cv::Mat imgraw  = img.clone();
	cv::Mat undistortimg;
	cv::undistort(img, undistortimg, CAMERAMATRIX, DISTORTION);
	cv::drawMarker(imgraw, center, cv::Scalar(0, 0, 255), 2);
	cv::cvtColor(undistortimg, img, cv::COLOR_BGR2GRAY);
//	DisplayImage("高斯滤波前", undistortimg);
//	// 高斯滤波
//	cv::GaussianBlur(img, img, cv::Size(5, 5), 3, 3);
	//DisplayImage("高斯滤波后", img);

	// 二值化
	cv::Mat binary;
	cv::threshold(img, binary, 200, 255, cv::THRESH_BINARY);
	//DisplayImage("二值化", binary);
	// 查找轮廓
	std::vector<std::vector<cv::Point>> contours;
	cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

	// 定义面积阈值
	double minArea = 20000.0; // 最小面积
	double maxArea = 50000.0; // 最大面积

	// 找到旋转的矩形并进行面积过滤
	for (size_t i = 0; i < contours.size(); i++) {
		double area = cv::contourArea(contours[i]);
		if (area > minArea && area < maxArea) {
			cv::RotatedRect minRect = cv::minAreaRect(contours[i]);
			CptAgl1.cpt = minRect.center;
			CptAgl1.agl = minRect.angle;
			if (minRect.size.height < 0.5 * img.rows && minRect.size.width < 0.5 * img.cols) {
				// 获取矩形的四个顶点
				cv::Point2f rect_points[4];
				minRect.points(rect_points);

				// 在原图上绘制矩形
				for (int j = 0; j < 4; j++) {
					cv::line(imgraw, rect_points[j], rect_points[(j + 1) % 4], cv::Scalar(0, 255, 0), 1);
					// 格式化角点坐标
					std::string label = "(" + std::to_string(static_cast<int>(rect_points[j].x)) + ", " +
					                    std::to_string(static_cast<int>(rect_points[j].y)) + ")";
					// 绘制角点坐标
					cv::putText(imgraw, label, rect_points[j], cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 1);

					double x = (rect_points[j].x -cx1 ) / fx1*1000;
					double y = -(rect_points[j].y -cy1 ) / fy1*1000;

					std::cout << "平面上的坐标 (X, Y): " << rect_points[j].x << "  " << rect_points[j].y<<"三维坐标（x,y,z）:"<<x<<"  "<<y<< "  "<<"980"
					          << std::endl;

				}
				//DisplayImage("查找轮廓", img);
				cv::imwrite("right_processed.jpg", imgraw);
			}
		}
	}

	return 0;
}
