#include "manager.h"
#include <iostream>
using namespace std;

Manager::Manager() {}

Manager::Manager(int id, string name, int dId)
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptIt = dId;
}


//��ʾ������Ϣ
void Manager::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\t������" << this->m_Name
		<< "\t��λ��" << this->getDeptName() 
		<<"\tְ������ϰ彻��������"<< endl;
}

//��ȡ��λ����
string Manager::getDeptName()
{
	return string("����");
}