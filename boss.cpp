#include "boss.h"
#include <iostream>
using namespace std;


Boss::Boss() {}
Boss::Boss(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptIt = dId;
}


//显示个人信息
void Boss::showInfo()
{
	cout << "职工编号：" << this->m_Id
		<< "\t姓名：" << this->m_Name
		<< "\t岗位：" << this->getDeptName() 
		<<"\t职责：维持公司正常运营"<< endl;
}

//获取岗位名称
string Boss::getDeptName()
{
	return string("老板");
}