#pragma once
#include "traffic.h"

/******************************************��·����******************************************/
class RoadBase//��·����
{
public:
	virtual ~RoadBase() = default;//������
	virtual void showRoad() = 0;//���Ƶ�·

	//�麯�������಻�Ǳ�����д�������ø���ָ���ȡ�����Ա����
	virtual double getUpLine() { return 0.0; }
	virtual double getMidLine() { return 0.0; }
	virtual double getDownLine() { return 0.0; }

public:
	double Rwidth = 200.0;//����������
	double up_boundary = 0.0;//�ϱ߽�
	double down_boundary = 0.0;//�±߽�
	double left_boundary = 0.0;//��߽�
	double right_boundary = 0.0;//�ұ߽�
};

class RoadNormal : public RoadBase//һ���·
{
public:
	RoadNormal(const double& r_width = 200.0);
	void showRoad() override;//���Ƶ�·
};

class RoadDoubleLane : public RoadBase//˫�����ߵ�·
{
public:
	RoadDoubleLane(const double& r_width = 200.0);
	void showRoad() override;//���Ƶ�·
};

class RoadCrosswalk : public RoadBase//�����ߵ�·
{
public:
	RoadCrosswalk(const double& r_width = 200.0);
	void showRoad() override;//���Ƶ�·
	double getUpLine() { return this->up_line; }//��ȡ�������ϱ߽�
	double getMidLine() { return this->mid_line; }//��ȡ������������
	double getDownLine() { return this->down_line; }//��ȡ�������±߽�

public:
	double up_line = 0.0;//�������ϱ߽�
	double mid_line = 0.0;//������������
	double down_line = 0.0;//�������±߽�
	double disRec = 20.0;//���
};