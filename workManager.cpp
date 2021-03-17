#include "WorkerManager.h"
#include "employee.h"
#include "boss.h"
#include "manager.h"
#include <algorithm>

WorkerManager::WorkerManager()
{	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//���ļ�
	//1.�ļ�������ʱ��ȫ����ʼ��Ϊ0
	if (!ifs.is_open())
	{
		this->empNum = 0;
		this->staffArray = vector<Worker*>();
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//2.�ļ����ڣ����޼�¼
	char ch;
	ifs >> ch;
	//�������ַ����ļ�β��Ǵ����ļ�β��
	if (ifs.eof())
	{
		this->empNum = 0;
		this->staffArray = vector<Worker*>();
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}
	//�ļ����ڣ����м�¼
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

//�˵�����
void WorkerManager::showMenu()
{
	cout << "****************************************" << endl;
	cout << "********  ��ӭʹ��ְ������ϵͳ  ********" << endl;
	cout << "**********   0 �˳��������   **********" << endl;
	cout << "**********   1 ����ְ����Ϣ   **********" << endl;
	cout << "**********   2 ��ʾְ����Ϣ   **********" << endl;
	cout << "**********   3 ɾ����ְְ��   **********" << endl;
	cout << "**********   4 �޸�ְ����Ϣ   **********" << endl;
	cout << "**********   5 ����ְ����Ϣ   **********" << endl;
	cout << "**********   6 ���ձ������   **********" << endl;
	cout << "**********   7 ���ְ����Ϣ   **********" << endl;
	cout << "****************************************" << endl;
}

//�˳�ϵͳ
void WorkerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

//��ʾְ��
void WorkerManager::showEmp()
{
	if (this->empNum == 0)
	{
		cout << "\n��ǰ��¼Ϊ�գ�" << endl;
		system("pause");
	}
	else
	{
		cout << "\n��ǰ���� " << this->empNum << "��ְ��" << endl;
		for (auto it = staffArray.begin(); it != staffArray.end(); it++)
		{
			(*it)->showInfo();
			cout << endl;
		}
		system("pause");
	}

	system("cls");
}

//����ְ��
void WorkerManager::addEmp()
{
	cout << "������Ҫ��ӵ���Ա������";
	int num = 0;
	cin >> num;

	if (num < 0)
	{
		cout << "���������������������룡" << endl;
	}
	else
	{
		for (int i = 0; i < num; i++)
		{
			a : int id;
			string name;
			cout << "�������" << i + 1 << "��ְ���ı�ţ�";
			cin >> id;
			auto it = staffArray.begin();
			for (; it != staffArray.end(); it++)
			{
				if ((*it)->m_Id == id)
				{
					cout << "���Ϊ" << id << "��ְ���Ѵ��ڣ����������룡" << endl;
					goto a;
				}
			}
			if (it == staffArray.end())
			{
				cout << "�������" << i + 1 << "��ְ����������";
				cin >> name;

				cout << "��������Ҫ���ְ�����ͣ�" << endl;
				cout << "1.�ϰ�" << endl;
				cout << "2.����" << endl;
				cout << "3.Ա��" << endl;
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
					cout << "��������" << endl;
					exit(0);
					break;
				}
				}
			}
		}
		this->m_FileIsEmpty = false;	//����ְ�����ļ��Ͳ�Ϊ����
		this->empNum += num;
		cout << "�ɹ����" << num << "����ְ����" << endl;
		this->save();	//����Ϣ�������ļ�
		system("pause");
		system("cls");
	}
}

//���ձ��ɾ��ְ��
void WorkerManager::delEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "��ǰ��¼Ϊ�գ��޷�ɾ����" << endl;
		system("pause");
		system("cls");
		return;
	}
		
	int id;
	cout << "������Ҫɾ����ְ����ţ�";
	cin >> id;
	int idx = this->isExist(id);
	if (idx == -1)
	{
		cout << "�����ڸñ�ŵ�Ա����" << endl;
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
	cout << "�ɹ�ɾ�����Ϊ" << id << "��ְ����" << endl;
	this->save();
	system("pause");
	system("cls");
}


//�޸�ְ����Ϣ
void WorkerManager::modifyEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "��ǰ��¼Ϊ�գ��޷��޸ģ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��������Ҫ�޸ĵ�ְ����ţ�";
	int id;
	cin >> id;

	auto it = staffArray.begin();
	for (; it != staffArray.end(); it++)
	{
		if ((*it)->m_Id == id)
		{
			delete (*it);
			cout << "�������ְ����������";
			string name;
			cin >> name;
			

			cout << "�������ְ����λ��" << endl;
			cout << "1.�ϰ�" << endl;
			cout << "2.����" << endl;
			cout << "3.Ա��" << endl;
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
				cout << "��������";
				return;
			}
			cout << "�޸ĳɹ���" << endl;
			this->save();
			break;
		}
	}
	if (it == staffArray.end())
	{
		cout << "�����ڱ��Ϊ" << id << "��ְ��" << endl;
	}
	system("pause");
	system("cls");
}

//����ְ��
void WorkerManager::findEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "��ǰ��¼Ϊ�գ�" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��������ҷ�ʽ��" << endl;
	cout << "1.ְ�����" << endl;
	cout << "2.ְ������" << endl;
	int select;
	cin >> select;
	switch (select)
	{
		case 1:
		{
			cout << "������Ҫ���ҵ�ְ����ţ�" << endl;
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
				cout << "δ�ҵ����Ϊ" << id << "��ְ��" << endl;
			}
			break;
		}
		
		case 2:
		{
			cout << "������Ҫ���ҵ�ְ��������" << endl;
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
				cout << "δ�ҵ�����Ϊ" << name << "��ְ��" << endl;
			}
			break;
		}

		default:
			cout << "��������" << endl;
			break;
	}
	system("pause");
	system("cls");
}

//��ְ���������
void WorkerManager::sortEmp()
{
	if (this->m_FileIsEmpty == true)
	{
		cout << "��ǰ��¼Ϊ��!" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����������ʽ��" << endl;
	cout << "1.�������С����" << endl;
	cout << "2.������ɴ�С" << endl;
	
	while (true)
	{
		int select;
		cin >> select;
		if (select == 1)
		{
			sort(staffArray.begin(), staffArray.end(), [](const Worker* a, const Worker* b) {return a->m_Id < b->m_Id; });
			cout << "��С�����������" << endl;
			break;
		}
		else if (select == 2)
		{
			sort(staffArray.begin(), staffArray.end(), [](const Worker* a, const Worker* b) {return a->m_Id > b->m_Id; });
			cout << "�ɴ�С�������" << endl;
			break;
		}
		else
		{
			cout << "�����������������룡";
		}
	}
	this->save();
	system("pause");
	system("cls");
}

//��ְ����Ϣ���浽�ļ�
void WorkerManager::save()
{
	ofstream ofs;	//д�ļ�
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�
	//��ÿ������Ϣд�뵽�ļ�
	for (auto it = staffArray.begin(); it != staffArray.end(); it++)
	{
		ofs << (*it)->m_Id << " " << (*it)->m_Name << " " << (*it)->m_DeptIt << endl;
	}
	ofs.close(); //�ر��ļ�
}

//ͳ���ļ��е�ǰ�����Ա������
int WorkerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);	//���ļ� ��

	int id;
	string name;
	int dId;

	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		++num;	//����һ�У�������һ
	}
	return num;
}

//�ļ����м�¼ʱ����ʼ��Ա��
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
	ifs.close(); //�ر��ļ�
}

//�жϱ��Ϊid��ְ���Ƿ���ڣ������ڷ���-1
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

//����ĵ�
void WorkerManager::cleanRecord()
{
	cout << "���Ҫ��ռ�¼��y/n" << endl;
	char ch;
	cin >> ch;
	if (ch == 'y')
	{
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);	//ɾ���ļ������´���
		ofs.close();
		cout << "����ļ��ɹ���" << endl;
		for (auto it = staffArray.begin(); it != staffArray.end(); it++)
		{
			delete (*it);
		}
		this->empNum = 0;
		this->m_FileIsEmpty = true;
	}
	else
	{
		cout << "����ļ�ʧ�ܣ�" << endl;
	}
	system("pause");
	system("cls");
}