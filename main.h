#pragma once
#include "scene_straight.h"
#include "scene_obs_pass.h"
#include "scene_park.h"
#include "scene_drift.h"

enum PlanType//����
{
	//ֱ��
	StraightStopObsType,//ͣ��
	StraightStationType,//ͣ��վ��
	StraightFollowType,//����
	StraightCrosswalkType,//ͨ��������

	//����
	ObsPassStaticType,//��̬����
	ObsPassOvertakeType,//����
	ObsPassMeetingType,//�ᳵ

	//����
	ParkReverse1Type,//����1
	ParkReverse2Type,//����2
	ParkParallelType,//�෽λ

	//Ư��
	DriftPointType,//����Ư��
	DriftparkType,//Ư�Ʋ���
};