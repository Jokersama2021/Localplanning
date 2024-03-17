#include "traffic.h"

/******************************************�ϰ���******************************************/
Cone::Cone(const double& pos_x, const double& pos_y, const double& R) : r(R)//׶Ͱ
{
	p_center = make_unique<Point>(pos_x, pos_y);
}

void Cone::showCone()//����
{
	setfillcolor(RGB(255, 127, 0));//��ɫ
	solidcircle(p_center->x, p_center->y, r);
}

Person::Person(const double& pos_x, const double& pos_y)//����
{
	p_center = make_unique<Point>(pos_x, pos_y);
}

void Person::personMove()//�����ƶ�
{
	p_center->x += speed;
}

void Person::showPerson()
{
	setfillcolor(YELLOW);
	fillcircle(p_center->x, p_center->y, r);
}

CarObsStatic::CarObsStatic(const double& pos_x, const double& pos_y, const double& heading, const double& width, const double& length)//��̬�ϰ���
{
	initCar(pos_x, pos_y, heading, width, length);

	topPos = min(min(plf->y, prf->y), min(plr->y, prr->y));
	bottomPos = max(max(plf->y, prf->y), max(plr->y, prr->y));
	leftPos = min(min(plf->x, prf->x), min(plr->x, prr->x));
	rightPos = max(max(plf->x, prf->x), max(plr->x, prr->x));
	cout << "topPos = " << topPos << ", bottomPos = " << bottomPos << ", leftPos = " << leftPos << ", rightPos = " << rightPos << endl;
}