#pragma once
#include "car.h"
#include "road.h"

/******************************************״̬��******************************************/
enum LaneChangeType//��������
{
	singleType,//������
	doubleType//˫����
};

class SceneBase//��������
{
public:
	virtual ~SceneBase() = default;
	virtual void showScene();//��ʾ����
	virtual void obsMoveStep() {}//�飬�ϰ��ﵥ֡�ƶ�
	virtual bool planning_process() = 0;//�������̣�����

	/******************************************ֱ��******************************************/
	void uniformStraight(const double& total_s);//ֱ�У���ʻָ������ //total_sΪ����Ϊ�ۼ�ʻ���ľ���
	void uniformAccBySpeed(const double& target_speed_y);//ֱ�У���֪���ٶȣ���ʻ��ָ�����ٶȣ��ȼӣ�������ֱ���˶�
	void uniformAccByDis(const double& dis, const double& target_speed_y);//ֱ�У���ʻָ���ľ���ʱ�ٶȴﵽָ���ٶȣ��ȼӣ�������ֱ���˶�
	void uniformAccByTime(const double& target_speed, const double& target_time);//ֱ�У���Ŀ��ʱ���ڴﵽĿ���ٶȣ��ȼӣ�������ֱ���˶�

	/******************************************ת��******************************************/
	void carTurn(const int& turn_state, const double& R, const double& total_theta);//ת����֪�뾶�ͽǶ� //total_thetaΪ����Ϊ�ۼ�ת���ĽǶ�
	void laneChange(const Point& target_point, const int& type, const double& s = 0.0);//����������߻�˫����

	/******************************************Ư��******************************************/
	void driftStraightByS(const double& total_s);//ֱ��Ư�ƣ���ת+ֱ���˶�����ֻ����ָ����λ��
	void driftStraightByTheta(const double& total_theta);//ֱ��Ư�ƣ���ת+ֱ���˶�����ֻ����ת��
	void driftTurnByRot(const double& total_theta, const Point& center);//Ư�ƹ��䣨��ת+��ת����ֻ������תת�� 
	void driftTurnByRev(const double& total_theta, const Point& center);//Ư�ƹ��䣨��ת+��ת����ֻ���ǹ�תת�� 

public:
	unique_ptr<RoadBase> road0;//��·����ָ��
	unique_ptr<CarBase> car0;//��������ָ��
	double speedlimit = -6.0;//��·����
};

