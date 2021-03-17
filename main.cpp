#include <iostream>
#include "WorkerManager.h"
#include "worker.h"
#include "employee.h"
#include "manager.h"
#include "boss.h"
using namespace std;


int main()
{
	WorkerManager wm;

	int choice = 0; //�洢�û���ѡ��
	while (true)
	{
		wm.showMenu();
	
		cout << "\n\n������ѡ�";
		cin >> choice;
		switch (choice)
		{
		case 0:	//�˳�ϵͳ
			wm.exitSystem();
			break;
		case 1: //����ְ��
			wm.addEmp();
			break;
		case 2: //��ʾְ����Ϣ
			wm.showEmp();
			break;
		case 3: //ɾ��ְ��
			wm.delEmp();
			break;
		case 4: //�޸�ְ��
			wm.modifyEmp();
			break;
		case 5: //����ְ��
			wm.findEmp();
			break;
		case 6: //ְ������
			wm.sortEmp();
			break;
		case 7: //����ĵ�
			wm.cleanRecord();
			break;
		default:	
			system("cls"); //����
			break;
		}
	}
	system("pause");
	return 0;
}