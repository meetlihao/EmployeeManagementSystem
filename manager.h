#pragma once
#include "worker.h"

//经理类
class Manager : public Worker
{
public:
	Manager();
	Manager(int id, string name, int dId);

	//显示个人信息
	void showInfo();

	//获取岗位名称
	string getDeptName();
};