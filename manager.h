#pragma once
#include "worker.h"

//������
class Manager : public Worker
{
public:
	Manager();
	Manager(int id, string name, int dId);

	//��ʾ������Ϣ
	void showInfo();

	//��ȡ��λ����
	string getDeptName();
};