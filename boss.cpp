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


//��ʾ������Ϣ
void Boss::showInfo()
{
	cout << "ְ����ţ�" << this->m_Id
		<< "\t������" << this->m_Name
		<< "\t��λ��" << this->getDeptName() 
		<<"\tְ��ά�ֹ�˾������Ӫ"<< endl;
}

//��ȡ��λ����
string Boss::getDeptName()
{
	return string("�ϰ�");
}