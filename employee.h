#pragma once
#include "worker.h"

//Ա����
class Employee : public Worker
{
public:
	Employee();
	Employee(int id, string name, int dId);

	//��ʾ������Ϣ
	void showInfo();

	//��ȡ��λ����
	string getDeptName() ;
};
