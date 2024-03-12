#include "scene_base.h"

void SceneBase::showScene()//��ʾ���麯��
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	car0->showCar(BLACK);

	if (SHOWCIRCLE && car0->p_center)//���ƹ켣��
	{
		car0->showCircle();
	}
	EndBatchDraw();
	delay(DELAYTIME);
}

/******************************************ֱ��******************************************/
void SceneBase::uniformStraight(const double& total_s)//ֱ�У���ʻָ������ //total_sΪ����Ϊ�ۼ�ʻ���ľ���
{
	car0->updateStraightInfo();//����ֱ����Ϣ

	double s = 0.0;
	while (s < total_s)
	{
		s += fabs(car0->speed);
		car0->moveStraightStep();
		obsMoveStep();
		showScene();//��ʾ
	}
	car0->coutInfo();
}

void SceneBase::uniformAccBySpeed(const double& target_speed_y)//ֱ�У���֪���ٶȣ���ʻ��ָ�����ٶȣ��ȼӣ�������ֱ���˶�
{
	while (car0->pmidr->y > 0.0)
	{
		car0->moveStraightStep();
		obsMoveStep();
		if (fabs(car0->speed_y - target_speed_y) > fabs(car0->a_y))//��ǰ������Ŀ�공������㹻��
		{
			car0->speed_y += car0->a_y;
		}
		else
		{
			car0->speed_y = target_speed_y;
			car0->a_y = 0.0;

			if (target_speed_y == 0.0)//�����ͣ������Ҫ����ѭ������Ȼp0�ƶ�����0.0��λ��
			{
				break;
			}
		}
		showScene();//��ʾ
	}
	car0->coutInfo();
}

void SceneBase::uniformAccByDis(const double& dis, const double& target_speed_y)//ֱ�У���ʻָ���ľ���ʱ�ٶȴﵽָ���ٶȣ��ȼӣ�������ֱ���˶�
{
	//������ٶ�
	car0->a_y = (pow(car0->speed_y, 2) - pow(target_speed_y, 2)) / dis / 2.0; // ���ٶ�
	cout << "a_y = " << car0->a_y << ", dis = " << dis << endl;

	uniformAccBySpeed(target_speed_y);
}

void SceneBase::uniformAccByTime(const double& target_speed_y, const double& target_time)//ֱ�У���Ŀ��ʱ���ڴﵽĿ���ٶȣ��ȼӣ�������ֱ���˶�
{
	//������ٶ�
	double freq = target_time * 1000 / DELAYTIME;//����wihileѭ���Ĵ���
	car0->a_y = (target_speed_y - car0->speed_y) / freq;//���ٶ� //ÿ��whileѭ�����ٶȵı仯ֵ
	cout << "a_y = " << car0->a_y << endl;

	uniformAccBySpeed(target_speed_y);
}

/******************************************ת��******************************************/
void SceneBase::carTurn(const int& turn_state, const double& R, const double& total_theta)//ת�� //total_thetaΪ����Ϊ�ۼ�ת���ĽǶ�
{
	car0->updateTurnInfo(turn_state, R);//����ת����Ϣ

	double theta = 0.0;
	while (theta < total_theta)
	{
		theta += fabs(car0->delta_theta);
		correctAngleError(car0->delta_theta, theta - total_theta);//�������
		car0->carTurnStep();
		obsMoveStep();
		showScene();
	}
	car0->coutInfo();
}

void SceneBase::laneChange(const Point& target_point, const int& type, const double& s)//����������߻�˫����
{
	double dis = car0->pmidr->distanceTo(target_point);
	Vec2d vec0(dis, car0->heading_theta + PI / 2.0);
	Vec2d vec(*car0->pmidr, target_point);
	double L = vec0.crossProd(vec) / dis / 2.0;
	double H = vec0.innerProd(vec) / dis / 2.0;

	if (fabs(L) < 1e-10)//target_point�ڳ���ֱ�з����ϣ�����Ҫ�����ж���
	{
		uniformStraight(car0->pmidr->distanceTo(target_point));
		return;
	}

	double R = (pow(L, 2) + pow(H, 2)) / fabs(L) / 2.0;//ת��뾶 //LΪ0������������Ѿ�return��
	double target_theta = asin(H / R);//Ŀ��ת��
	double target_delta_theta = fabs(car0->speed / R);//���ٶȾ���ֵ
	cout << "dis = " << dis << ", L = " << L << ", H = " << H << ", R = " << R << ", target_theta = " << target_theta / PI << ", target_delta_theta = " << target_delta_theta / PI << endl;

	if (L > 0.0)//����
	{
		car0->delta_theta = target_delta_theta;
		carTurn(TurnDirection::TurnLeft, R, target_theta);

		if (type == singleType)
		{
			car0->delta_theta = -target_delta_theta;
			carTurn(TurnDirection::TurnRight, R, target_theta);
		}
		else
		{
			car0->delta_theta = -target_delta_theta;
			carTurn(TurnDirection::TurnRight, R, target_theta);

			uniformStraight(s);

			car0->delta_theta = -target_delta_theta;
			carTurn(TurnDirection::TurnRight, R, target_theta);

			car0->delta_theta = target_delta_theta;
			carTurn(TurnDirection::TurnLeft, R, target_theta);
		}
	}
	else if (L < 0.0)//����
	{
		car0->delta_theta = -target_delta_theta;
		carTurn(TurnDirection::TurnRight, R, target_theta);

		if (type == singleType)
		{
			car0->delta_theta = target_delta_theta;
			carTurn(TurnDirection::TurnLeft, R, target_theta);
		}
		else
		{
			car0->delta_theta = target_delta_theta;
			carTurn(TurnDirection::TurnLeft, R, target_theta);

			uniformStraight(s);//����ǳ�����������Ҫֱ��һ�ξ���

			car0->delta_theta = target_delta_theta;
			carTurn(TurnDirection::TurnLeft, R, target_theta);

			car0->delta_theta = -target_delta_theta;
			carTurn(TurnDirection::TurnRight, R, target_theta);
		}
	}
}

/******************************************Ư��******************************************/
void SceneBase::driftStraightByS(const double& total_s)//ֱ��Ư�ƣ���ת+ֱ���˶�����ֻ����ָ����λ��
{
	car0->updateDriftRotInfo();
	double s = 0.0;
	while (s < total_s)
	{
		s += fabs(car0->speed);
		car0->carRotationStep();//����ת
		car0->pmid->pointMove(car0->speed_x, car0->speed_y);//������ĵ�ֱ��
		obsMoveStep();
		showScene();//��ʾ
	}
	car0->coutInfo();
}

void SceneBase::driftStraightByTheta(const double& total_theta)//ֱ��Ư�ƣ���ת+ֱ���˶�����ֻ����ת��
{
	car0->updateDriftRotInfo();

	double theta = 0.0;
	while (theta < total_theta)
	{
		theta += fabs(car0->delta_theta_rot);
		correctAngleError(car0->delta_theta_rot, theta - total_theta);//�������
		car0->carRotationStep();//����ת
		car0->pmid->pointMove(car0->speed_x, car0->speed_y);//������ĵ�ֱ��
		obsMoveStep();
		showScene();
	}
	car0->coutInfo();
}

void SceneBase::driftTurnByRot(const double& total_theta, const Point& center)//Ư�ƹ��䣨��ת+��ת����ֻ������תת��
{
	car0->updateDriftRotRevInfo(center);

	double theta_rot = 0.0;//��ת�ۼ�ת���ĽǶ�
	while (theta_rot < total_theta)
	{
		theta_rot += fabs(car0->delta_theta_rot);
		correctAngleError(car0->delta_theta_rot, theta_rot - total_theta);//�������
		car0->carRotationStep();//����ת	
		car0->pmid->pointTurn(center, car0->delta_theta);//������ĵ���center��ת
		obsMoveStep();
		showScene();
	}
	car0->coutInfo();
}

void SceneBase::driftTurnByRev(const double& total_theta, const Point& center)//Ư�ƹ��䣨��ת+��ת����ֻ���ǹ�תת��
{
	car0->updateDriftRotRevInfo(center);
	double theta_rev = 0.0;//��ת�ۼ�ת���ĽǶ�
	while (theta_rev < total_theta)
	{
		theta_rev += fabs(car0->delta_theta);
		correctAngleError(car0->delta_theta, theta_rev - total_theta);//�������
		car0->carRotationStep();//����ת	
		car0->pmid->pointTurn(center, car0->delta_theta);//������ĵ���center��ת
		obsMoveStep();
		showScene();
	}
	car0->coutInfo();
}