#pragma once
#include "worker.h"

//�ϰ���
class Boss : public Worker
{
public:
	Boss();
	Boss(int id, string name, int dId);

	//��ʾ������Ϣ
	void showInfo();

	//��ȡ��λ����
	string getDeptName();
};