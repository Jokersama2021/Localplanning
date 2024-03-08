#pragma once
#include "planning_base.h"

/******************************************״̬��******************************************/
enum Shift//��λ
{
	m_D,//ǰ����
	m_N,//�յ�
	m_R,//����
	m_P//פ����
};

enum TurnDirection//ת��״̬��
{
	TurnRight,//��ת
	TurnLeft,//��ת
};

/******************************************������******************************************/
class CarBase//������
{
public:
	virtual ~CarBase() = default;//������
	void initCar(const double& pos_x, const double& pos_y, const double& heading, const double& width, const double& length);//��ʼ��
	void updatePmidf();//����ǰ�е�xyֵ
	void updatePmidr();//���º��е�xyֵ
	void updatePmid();//���¼����е�xyֵ
	void showCar(const COLORREF& color);//���Ƴ�������
	void showCircle();//���ƹ켣��
	void coutInfo();//��ӡ��Ϣ

	void moveStraightStep();//��ֱ֡��	
	void carTurnStep();//��֡ת��
	void carRotationStep();//��֡��ת

	void updateRinRout(const double& R);//����4���뾶
	void updateTurnInfo(const int& turn_state, const double& R);//����ת����Ϣ
	void updateXYva();//����x��y������ٶȺͼ��ٶ�
	void updateStraightInfo();//����ֱ����Ϣ
	void updateDriftRotInfo();//����Ư����ת��Ϣ
	void updateDriftRotRevInfo(const Point& center);//����Ư����ת+��ת��Ϣ

public:
	double car_width = 80.0;//����
	double car_length = 160.0;//����

	unique_ptr<Point> plf;//��ǰ��
	unique_ptr<Point> plr;//����
	unique_ptr<Point> prf;//��ǰ��
	unique_ptr<Point> prr; //�Һ��
	unique_ptr<Point> p_center;//ת�����ĵ�

	unique_ptr<Point> pmidf;//ǰ���е�
	unique_ptr<Point> pmidr;//�����е�
	unique_ptr<Point> pmid;//�����е�

	double Rmin = 100.0;//��Сת��뾶
	double Rof = 0.0;//��ǰ�뾶
	double Ror = 0.0;//���뾶
	double Rif = 0.0;//��ǰ�뾶
	double Rir = 0.0;//�ں�뾶

	double R0;//��б������ת�뾶
	double theta0;//atan(car_length / car_width)

	double speed = 0.0;//���ٶȣ���������������ǰ������������
	double speed_x = 0.0;//x������ٶȣ�����������������������������
	double speed_y = 0.0;//y������ٶȣ������������������ϣ�����������

	double a = 0.0;//�ϼ��ٶȣ�����������������٣����������
	double a_x = 0.0;//x����ּ��ٶȣ���������������������٣����������Ҽ���
	double a_y = 0.0;//y����ּ��ٶȣ������������������ϼ��٣����������¼���

	double delta_theta = 0.0;//���ٶȣ���������������˳ʱ��ת����������ʱ��ת��
	double delta_theta_rot = 0.0;//��ת���ٶȣ���������������˳ʱ��ת����������ʱ��ת��
	double heading_theta = 0.0;//����ǣ�Ϊ0ʱ������ֱ���ϣ�����������ƫ��������������ƫ��

	int Gear = m_P;//��λ
};

/******************************************һ�㳵******************************************/
class CarNormal : public CarBase
{
public:
	CarNormal(const double& pos_x, const double& pos_y, const double& heading = 0.0, const double& width = 80.0, const double& length = 160.0);
};