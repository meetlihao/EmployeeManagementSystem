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

	int choice = 0; //存储用户的选择
	while (true)
	{
		wm.showMenu();
	
		cout << "\n\n请输入选项：";
		cin >> choice;
		switch (choice)
		{
		case 0:	//退出系统
			wm.exitSystem();
			break;
		case 1: //增加职工
			wm.addEmp();
			break;
		case 2: //显示职工信息
			wm.showEmp();
			break;
		case 3: //删除职工
			wm.delEmp();
			break;
		case 4: //修改职工
			wm.modifyEmp();
			break;
		case 5: //查找职工
			wm.findEmp();
			break;
		case 6: //职工排序
			wm.sortEmp();
			break;
		case 7: //清空文档
			wm.cleanRecord();
			break;
		default:	
			system("cls"); //清屏
			break;
		}
	}
	system("pause");
	return 0;
}