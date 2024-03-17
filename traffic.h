#pragma once
#include "planning_base.h"
#include "car.h"

/******************************************�ϰ���******************************************/
class Cone//׶Ͱ
{
public:
	Cone() = default;
	Cone(const double& pos_x, const double& pos_y, const double& R = 20.0);
	void showCone();

public:
	unique_ptr<Point> p_center;//���ĵ�
	double r = 20.0;//�뾶
};

class Person//����
{
public:
	Person() = default;
	Person(const double& pos_x, const double& pos_y);
	void personMove();//�����ƶ�
	void showPerson();

public:
	unique_ptr<Point> p_center;//���ĵ�
	double r = 20.0;//�뾶
	double speed = 0.0;//�ٶ�
};

class CarObsStatic : public CarBase//��̬�ϰ���
{
public:
	CarObsStatic() = default;
	CarObsStatic(const double& pos_x, const double& pos_y, const double& heading = 0.0, const double& width = 80.0, const double& length = 160.0);//��̬�ϰ���

public:
	//4����λ��
	double topPos = 0.0;
	double rightPos = 0.0;
	double leftPos = 0.0;
	double bottomPos = 0.0;
};