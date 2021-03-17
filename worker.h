#pragma once
#include <string>
using namespace std;
//创建职工虚基类
class Worker
{
public:
	//显示个人信息
	virtual void showInfo() = 0;

	//获取岗位名称
	virtual string getDeptName() = 0;

	int m_Id;	//职工编号
	string m_Name; //职工姓名
	int m_DeptIt; //职工部门编号
};
