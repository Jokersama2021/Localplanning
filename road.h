#pragma once
#include "traffic.h"

/******************************************��·����******************************************/
class RoadBase//һ���·
{
public:
	virtual ~RoadBase() = default;
	virtual void showRoad() = 0;

	virtual double getUpLine() { return 0.0; }
	virtual double getMidLine() { return 0.0; }
	virtual double getDownLine() { return 0.0; }

public:
	double Rwidth = 200.0;//����������
	//�߽�
	double up_boundary = 0.0;//��
	double down_boundary = 0.0;//��
	double left_boundary = 0.0;//��
	double right_boundary = 0.0;//��
};

class RoadNormal : public RoadBase
{
public:
	RoadNormal(const double& r_width = 200.0);
	void showRoad() override;
};

class RoadDoubleLane : public RoadBase//˫�����ߵ�·
{
public:
	RoadDoubleLane(const double& r_width = 200.0);
	void showRoad() override;
};

class RoadCrosswalk : public RoadBase//�����ߵ�·
{
public:
	RoadCrosswalk(const double& r_width = 200.0);
	void showRoad() override;
	double getUpLine() { return this->up_line; }//��ȡ�������ϱ߽�
	double getMidLine() { return this->mid_line; }//��ȡ������������
	double getDownLine() { return this->down_line; }//��ȡ�������±߽�

public:
	double up_line = 0.0;//�������ϱ߽�
	double mid_line = 0.0;//������������
	double down_line = 0.0;//�������±߽�
	double disRec = 20.0;//���
};