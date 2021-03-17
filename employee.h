#pragma once
#include "worker.h"

//员工类
class Employee : public Worker
{
public:
	Employee();
	Employee(int id, string name, int dId);

	//显示个人信息
	void showInfo();

	//获取岗位名称
	string getDeptName() ;
};
