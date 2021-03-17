#pragma once
#include <iostream>
#include <vector>
#include "worker.h"
#include <fstream>
#define FILENAME "empFile.txt"

using namespace std;

class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();

	//չʾ�˵�
	void showMenu();

	//�˳�ϵͳ
	void exitSystem();

	//��ʾְ��
	void showEmp();

	//����ְ��
	void addEmp();

	//�޸�ְ����Ϣ
	void modifyEmp();

	//���ձ��ɾ��ְ��
	void delEmp();

	//����ְ��
	void findEmp();

	//��ְ���������
	void sortEmp();

	//����ĵ�
	void cleanRecord();

	//��ְ����Ϣ���浽�ļ�
	void save();
	
	//ͳ���ļ��е�ǰ�����Ա������
	int get_EmpNum();

	//�ļ����м�¼ʱ����ʼ��Ա��
	void init_Emp();

	//�жϱ��Ϊid��ְ���Ƿ���ڣ������򷵻������е������������ڷ���-1
	int isExist(int id);

	int empNum;	//��¼Ա������
	vector<Worker*> staffArray ; //���Ա��������
	bool m_FileIsEmpty; //�ļ��Ƿ�Ϊ�յı�־
	
};