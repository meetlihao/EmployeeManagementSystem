#include "employee.h"
#include <iostream>
using namespace std;

Employee::Employee() {}

Employee::Employee(int id, string name, int dId) 
{
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptIt = dId;
}


//��ʾ������Ϣ
void Employee::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\t������" << this->m_Name
		<< "\t��λ��" << this->getDeptName()
		<< "\tְ����ɾ�����������" << endl;
}

//��ȡ��λ����
string Employee::getDeptName()
{
	return string("Ա��");
}