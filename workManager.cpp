#include "WorkerManager.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include <algorithm>

WorkerManager::WorkerManager()
{	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//读文件
	//1.文件不存在时，全部初始化为0
	if (!ifs.is_open())
	{
		this->empNum = 0;
		this->staffArray = vector<Worker*>();
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.文件存在，但无记录
	char ch;
	ifs >> ch;
	//读到的字符是文件尾标记代表文件尾空
	if (ifs.eof())
	{
		this->empNum = 0;
		this->staffArray = vector<Worker*>();
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//文件存在，且有记录
	int num = this->get_EmpNum();
	this->empNum = num;
	this->init_Emp();
}


WorkerManager::~WorkerManager()
{
	if ((this->staffArray).size() != 0)
	{
		for (auto it = staffArray.begin(); it != staffArray.end(); it++)
			delete (*it);
	}
}

//菜单界面
void WorkerManager::showMenu()
{
	cout << "****************************************" << endl;
	cout << "********  欢迎使用职工管理系统  ********" << endl;
	cout << "**********   0 退出管理程序   **********" << endl;
	cout << "**********   1 增加职工信息   **********" << endl;
	cout << "**********   2 显示职工信息   **********" << endl;
	cout << "**********   3 删除离职职工   **********" << endl;
	cout << "**********   4 修改职工信息   **********" << endl;
	cout << "**********   5 查找职工信息   **********" << endl;
	cout << "**********   6 按照编号排序   **********" << endl;
	cout << "**********   7 清空职工信息   **********" << endl;
	cout << "****************************************" << endl;
}

//退出系统
void WorkerManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

//显示职工
void WorkerManager::showEmp()
{
	if (this->empNum == 0)
	{
		cout << "\n当前记录为空！" << endl;
		system("pause");
	}
	else
	{
		cout << "\n当前共有 " << this->empNum << "名职工" << endl;
		for (auto it = staffArray.begin(); it != staffArray.end(); it++)
		{
			(*it)->showInfo();
			cout << endl;
		}
		system("pause");
	}

	system("cls");
}

//增加职工
void WorkerManager::addEmp()
{
	cout << "请输入要添加的人员数量：";
	int num = 0;
	cin >> num;

	if (num < 0)
	{
		cout << "您的输入有误，请重新输入！" << endl;
	}
	else
	{
		for (int i = 0; i < num; i++)
		{
			a : int id;
			string name;
			cout << "请输入第" << i + 1 << "个职工的编号：";
			cin >> id;
			auto it = staffArray.begin();
			for (; it != staffArray.end(); it++)
			{
				if ((*it)->m_Id == id)
				{
					cout << "编号为" << id << "的职工已存在，请重新输入！" << endl;
					goto a;
				}
			}
			if (it == staffArray.end())
			{
				cout << "请输入第" << i + 1 << "个职工的姓名：";
				cin >> name;

				cout << "请输入您要添加职工类型：" << endl;
				cout << "1.老板" << endl;
				cout << "2.经理" << endl;
				cout << "3.员工" << endl;
				char choice;
				cin >> choice;
				Worker* worker = nullptr;

				switch (choice - '0')
				{
				case 1:
				{
					worker = new Boss(id, name, 1);
					staffArray.push_back(worker);
					break;
				}
				case 2:
				{
					worker = new Manager(id, name, 2);
					staffArray.push_back(worker);
					break;
				}
				case 3:
				{
					worker = new Employee(id, name, 3);
					staffArray.push_back(worker);
					break;
				}
				default:
				{
					cout << "输入有误" << endl;
					exit(0);
					break;
				}
				}
			}
		}
		this->m_FileIsEmpty = false;	//加入职工后文件就不为空了
		this->empNum += num;
		cout << "成功添加" << num << "名新职工！" << endl;
		this->save();	//将信息保存至文件
		system("pause");
		system("cls");
	}
}

//按照编号删除职工
void WorkerManager::delEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "当前记录为空，无法删除！" << endl;
		system("pause");
		system("cls");
		return;
	}
		
	int id;
	cout << "请输入要删除的职工编号：";
	cin >> id;
	int idx = this->isExist(id);
	if (idx == -1)
	{
		cout << "不存在该编号的员工！" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (int i = idx; i < this->staffArray.size() - 1; i++)
	{
		staffArray[i] = staffArray[i + 1];
	}
	this->empNum--;
	this->staffArray.pop_back();
	cout << "成功删除编号为" << id << "的职工！" << endl;
	this->save();
	system("pause");
	system("cls");
}


//修改职工信息
void WorkerManager::modifyEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "当前记录为空，无法修改！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入您要修改的职工编号：";
	int id;
	cin >> id;

	auto it = staffArray.begin();
	for (; it != staffArray.end(); it++)
	{
		if ((*it)->m_Id == id)
		{
			delete (*it);
			cout << "请输入该职工的姓名：";
			string name;
			cin >> name;
			

			cout << "请输入该职工岗位：" << endl;
			cout << "1.老板" << endl;
			cout << "2.经理" << endl;
			cout << "3.员工" << endl;
			int dId;
			cin >> dId;
			switch (dId)
			{
			case 1:
				(*it) = new Boss(id, name, 1);
				break;
			case 2:
				(*it) = new Manager(id, name, 2);
				break;
			case 3:
				(*it) = new Employee(id, name, 3);
				break;
			default:
				cout << "输入有误！";
				return;
			}
			cout << "修改成功！" << endl;
			this->save();
			break;
		}
	}
	if (it == staffArray.end())
	{
		cout << "不存在编号为" << id << "的职工" << endl;
	}
	system("pause");
	system("cls");
}

//查找职工
void WorkerManager::findEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "当前记录为空！" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入查找方式：" << endl;
	cout << "1.职工编号" << endl;
	cout << "2.职工姓名" << endl;
	int select;
	cin >> select;
	switch (select)
	{
		case 1:
		{
			cout << "请输入要查找的职工编号：" << endl;
			int id;
			cin >> id;
			
			auto it = staffArray.begin();
			for (; it != staffArray.end(); it++)
			{
				if ((*it)->m_Id == id)
				{
					(*it)->showInfo();
					break;
				}

			}
			if (it == staffArray.end())
			{
				cout << "未找到编号为" << id << "的职工" << endl;
			}
			break;
		}
		
		case 2:
		{
			cout << "请输入要查找的职工姓名：" << endl;
			bool flag = false;
			string name;
			cin >> name;
			auto it = staffArray.begin(); 
			for (; it != staffArray.end(); it++)
			{
				if ((*it)->m_Name == name)
				{
					(*it)->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "未找到姓名为" << name << "的职工" << endl;
			}
			break;
		}

		default:
			cout << "输入有误！" << endl;
			break;
	}
	system("pause");
	system("cls");
}

//按职工编号排序
void WorkerManager::sortEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "当前记录为空!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入排序方式：" << endl;
	cout << "1.按编号由小到大" << endl;
	cout << "2.按编号由大到小" << endl;
	
	while (true)
	{
		int select;
		cin >> select;
		if (select == 1)
		{
			sort(staffArray.begin(), staffArray.end(), [](const Worker* a, const Worker* b) {return a->m_Id < b->m_Id; });
			cout << "由小到大排序完毕" << endl;
			break;
		}
		else if (select == 2)
		{
			sort(staffArray.begin(), staffArray.end(), [](const Worker* a, const Worker* b) {return a->m_Id > b->m_Id; });
			cout << "由大到小排序完毕" << endl;
			break;
		}
		else
		{
			cout << "输入有误，请重新输入！";
		}
	}
	this->save();
	system("pause");
	system("cls");
}

//将职工信息保存到文件
void WorkerManager::save()
{
	ofstream ofs;	//写文件
	ofs.open(FILENAME, ios::out); //以输出的方式打开文件
	//将每个人信息写入到文件
	for (auto it = staffArray.begin(); it != staffArray.end(); it++)
	{
		ofs << (*it)->m_Id << " " << (*it)->m_Name << " " << (*it)->m_DeptIt << endl;
	}
	ofs.close(); //关闭文件
}

//统计文件中当前保存的员工人数
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//打开文件 读

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		++num;	//读完一行，人数加一
	}
	return num;
}

//文件中有记录时，初始化员工
void WorkerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	int id;
	string name;
	int dId;
	
	Worker* worker = nullptr;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		if (dId == 1)
		{
			worker = new Boss(id, name, dId);	
		}
		else if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)
		{
			worker = new Employee(id, name, dId);
		}
		this->staffArray.push_back(worker);
	}
	ifs.close(); //关闭文件
}

//判断编号为id的职工是否存在，不存在返回-1
int WorkerManager::isExist(int id)
{
	int idx = 0;
	for (auto it = staffArray.begin(); it != staffArray.end(); it++)
	{
		if ((*it)->m_Id == id)
			return idx;
		++idx;
	}
	return -1;
}

//清空文档
void WorkerManager::cleanRecord()
{
	cout << "真的要清空记录吗？y/n" << endl;
	char ch;
	cin >> ch;
	if (ch == 'y')
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);	//删除文件后重新创建
		ofs.close();
		cout << "清空文件成功！" << endl;
		for (auto it = staffArray.begin(); it != staffArray.end(); it++)
		{
			delete (*it);
		}
		this->empNum = 0;
		this->m_FileIsEmpty = true;
	}
	else
	{
		cout << "清空文件失败！" << endl;
	}
	system("pause");
	system("cls");
}