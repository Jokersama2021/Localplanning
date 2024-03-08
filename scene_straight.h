#pragma once
#include "scene_base.h"

class StraightStopObs : public SceneBase //ͣ��
{
public:
	StraightStopObs();
	void showScene();//��ʾ
	bool planning_process() override;

public:
	unique_ptr<Cone> cone;//׶Ͱ
	double safedis = 50.0;//ֹͣ����
};

class StraightStation : public SceneBase //ͣ��վ��
{
public:
	StraightStation();
	void showScene();//��ʾ
	bool planning_process() override;

public:
	unique_ptr<Point> station;//վ��
	int stop_time = 3;//ͣվʱ�䣬s
};

class StraightFollow : public SceneBase //����
{
public:
	StraightFollow();
	void showScene();//��ʾ
	bool planning_process() override;

public:
	unique_ptr<CarNormal> carObs;//�ϰ���
	double safedis = 120.0;//���ֳ���
};

class StraightCrosswalk : public SceneBase //ͨ��������
{
public:
	StraightCrosswalk();
	bool peopleInCross();//�������Ƿ�����
	void showScene();//��ʾ
	bool planning_process() override;

public:
	int people_num = 5;//����
	vector<unique_ptr<Person>> people;//����
	double speedlimit_cross = -3.0;//����������
};