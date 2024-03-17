#include "scene_straight.h"

/******************************************ͣ��******************************************/
StraightStopObs::StraightStopObs()//ͣ��
{
	road0 = make_unique<RoadNormal>();
	cone = make_unique<Cone>(SWIDTH / 2.0, SWIDTH / 4.0, 50.0);//����׶Ͱ

	car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
	car0->speed_y = -5.0;

	car0->coutInfo();
	showScene();
	system("pause");
}

void StraightStopObs::showScene()
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	cone->showCone();
	car0->showCar(BLACK);

	EndBatchDraw();
	delay(DELAYTIME);
}

bool StraightStopObs::planning_process()
{
	double stopline = cone->p_center->y + cone->r + safedis;
	uniformAccByDis(car0->pmidf->y - stopline, 0.0);
	return true;
}

/******************************************ͣ��վ��******************************************/
StraightStation::StraightStation()//ͣ��վ��
{
	road0 = make_unique<RoadNormal>();
	station = make_unique<Point>(SWIDTH / 2.0, SHEIGHT / 2.0);

	car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
	car0->speed_y = -5.0;

	car0->coutInfo();
	showScene();
	system("pause");
}

void StraightStation::showScene()
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	station->showPoint();
	car0->showCar(BLACK);

	EndBatchDraw();
	delay(DELAYTIME);
}

bool StraightStation::planning_process()
{
	uniformAccByDis(car0->pmid->y - station->y, 0.0);//���ٽ�վ
	delay(stop_time * 1000);//ͣվ�ȴ�
	uniformAccByTime(speedlimit, 2.0);//��վ
	return true;
}

/******************************************����******************************************/
StraightFollow::StraightFollow()//����
{
	road0 = make_unique<RoadNormal>();
	carObs = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT / 2.0, 0.0, 50.0, 100.0);
	car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
	carObs->speed_y = -2.0;
	car0->speed_y = -5.0;

	car0->coutInfo();
	carObs->coutInfo();
	showScene();
	system("pause");
}

void StraightFollow::showScene()
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	carObs->showCar(RED);
	car0->showCar(BLACK);

	EndBatchDraw();
	delay(DELAYTIME);
}

bool StraightFollow::planning_process()
{
	double dis = car0->pmidf->y - carObs->pmidr->y;//��ʼ���
	double delta_dis = dis - safedis;//��ʼ���-Ŀ����
	double delta_speed_y = car0->speed_y - carObs->speed_y;//�ٶȲ�
	if (dis <= 0.0 || delta_dis <= 0.0 || delta_speed_y > 0.0)//ֻ�����������ٸ��졢��Ҫ���ٵ����
	{
		return false;
	}

	car0->a_y = pow(delta_speed_y, 2) / delta_dis / 2.0;
	cout << "car0->a_y = " << car0->a_y << endl;

	while (car0->pmidr->y > 0.0)
	{
		car0->moveStraightStep();
		carObs->moveStraightStep();
		if (fabs(car0->speed_y - carObs->speed_y) > fabs(car0->a_y))//�ٶȲ��㹻��
		{
			car0->speed_y += car0->a_y;
		}
		else
		{
			car0->speed_y = carObs->speed_y;
			car0->a_y = 0.0;
		}
		showScene();	
	}
	car0->coutInfo();
	return true;
}

/******************************************ͨ��������******************************************/
StraightCrosswalk::StraightCrosswalk()//ͨ��������
{
	road0 = make_unique<RoadCrosswalk>();
	car0 = make_unique<CarNormal>(SWIDTH / 2.0, SHEIGHT - 70.0);
	car0->speed_y = -4.0;

	for (int i = 0; i < people_num; i++)
	{
		unique_ptr<Person> ps = make_unique<Person>(road0->right_boundary + 20 * (i * 3 + 1), road0->getMidLine());
		ps->speed = -2;
		people.emplace_back(move(ps));
	}

	car0->coutInfo();
	showScene();
	system("pause");
}

bool StraightCrosswalk::peopleInCross()//�������Ƿ�����
{
	for (auto& i : people)
	{
		if (i->p_center->x >= road0->left_boundary - i->r && i->p_center->x <= road0->right_boundary + i->r)
		{
			return true;
		}
	}
	return false;
}

void StraightCrosswalk::showScene()
{
	BeginBatchDraw();
	cleardevice();

	road0->showRoad();
	car0->showCar(BLACK);

	car0->moveStraightStep();
	car0->speed_y += car0->a_y;

	for (auto& i : people)
	{
		i->showPerson();
		i->personMove();
	}

	EndBatchDraw();
	delay(DELAYTIME);
}

bool StraightCrosswalk::planning_process()
{
	//��������߳�����һ���ȼ���
	double dis = car0->pmidf->y - road0->getDownLine();
	car0->a_y = pow(car0->speed_y, 2) / 2.0 / dis;

	while (dis > 0.0)
	{
		dis = car0->pmidf->y - road0->getDownLine();
		if (!peopleInCross())//���������û��
		{
			if (car0->speed_y >= speedlimit_cross)//����������
			{
				car0->a_y = 0.0;//��Ϊ�����˶�
			}
		}
		else
		{
			if (dis <= 7.0)//ֹͣ��ǰ�ó�����ȫͣ�£���ֹ����Ų���򵹳�
			{
				car0->speed_y = 0.0;
				car0->a_y = 0.0;
				break;
			}
		}

		cout << "dis = " << dis << ", car speed_y = " << car0->speed_y << ", a_y = " << car0->a_y << endl;
		showScene();
	}

	//����ͨ��������
	while (car0->pmidr->y > road0->getUpLine())//����������
	{
		if (!peopleInCross())//���������û����
		{
			if (car0->speed_y > speedlimit_cross)//û�ﵽ����������
			{
				car0->a_y = -0.05;//����
			}
			else //�ﵽ����������
			{
				car0->a_y = 0.0;//��Ϊ�����˶�
			}
		}

		cout << "car speed_y = " << car0->speed_y << ", a_y = " << car0->a_y << endl;
		showScene();
	}

	//���˰����ߣ��������٣�ֱ���ﵽ��·����
	while (car0->pmidr->y > 0.0)
	{
		if (car0->speed_y > speedlimit)//û�ﵽ��·����
		{
			car0->a_y = -0.05;//����
		}
		else
		{
			car0->a_y = 0.0;//��Ϊ�����˶�
		}

		cout << "car speed_y = " << car0->speed_y << ", a_y = " << car0->a_y << endl;
		showScene();
	}

	return true;
}