#pragma once
#include <iostream>
#include <graphics.h>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

/*********************************ȫ�ֱ���***********************************/
constexpr auto SWIDTH = 1200.0;
constexpr auto SHEIGHT = 1200.0;
constexpr auto PI = 3.14159265358979323846;
constexpr auto SHOWCIRCLE = false;//���ƹ켣��
constexpr auto DELAYTIME = 20;//���ʱ�䣬ms
constexpr auto CHANGETIME = 1000;//����ʱ�䣬ms

/******************************************��******************************************/
class Point
{
public:
	Point() = default;
	Point(const double& p_x, const double& p_y, const double& p_theta = 0.0, const double& p_R = 0.0);
	void showPoint();
	void pointMove(const double& speed_x, const double& speed_y);//����ƶ�
	void pointTurn(const Point& center, const double& turn_speed);//����center��ת��turn_speedΪ���ٶ�
	double distanceTo(const Point& p) const;//����
	double thetaTo(const Point& p) const;//this->�����p�Ƕ�

public:
	double x;
	double y;
	double thetaP = 0.0;//�Ƕ�
	double Rp = 0.0;//��ת�뾶
	int r = 5;//���ư뾶
};

/******************************************����******************************************/
class Vec2d
{
public:
	Vec2d() = default;
	Vec2d(const double& new_x, const double& new_y, const bool& flag);//ͨ������ֵ����������flag����������һ�����캯��
	Vec2d(const Point& p_start, const Point& p_end);//ͨ�������㹹������
	Vec2d(const double& length, const double& angle);//ͨ�����Ⱥͷ���������
	double length();//ģ
	double crossProd(const Vec2d& other) const;//���
	double innerProd(const Vec2d& other) const;//���

public:
	double x;
	double y;
};

/******************************************ȫ�ֺ���******************************************/
void delay(const int& time); //��ʱ������ms
double normalizeAngle(const double& theta); //�Ƕ�������[-PI, PI)֮��
void correctAngleError(double& target_theta, const double& delta_theta);//�Ƕ��������
double disPointToLine(const Point& p, const Point& p_start, const Point& p_end);//�㵽ֱ�ߵľ���