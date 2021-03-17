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

	//展示菜单
	void showMenu();

	//退出系统
	void exitSystem();

	//显示职工
	void showEmp();

	//增加职工
	void addEmp();

	//修改职工信息
	void modifyEmp();

	//按照编号删除职工
	void delEmp();

	//查找职工
	void findEmp();

	//按职工编号排序
	void sortEmp();

	//清空文档
	void cleanRecord();

	//将职工信息保存到文件
	void save();
	
	//统计文件中当前保存的员工人数
	int get_EmpNum();

	//文件中有记录时，初始化员工
	void init_Emp();

	//判断编号为id的职工是否存在，存在则返回数组中的索引，不存在返回-1
	int isExist(int id);

	int empNum;	//记录员工个数
	vector<Worker*> staffArray ; //存放员工的数组
	bool m_FileIsEmpty; //文件是否为空的标志
	
};