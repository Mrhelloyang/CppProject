#pragma once
#include<iostream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<string>
using namespace std;
#include<fstream>
#define FILENAME "empfile.txt"
class WorkManager {
public:
	WorkManager();
	void ExitSystem();
	int m_EmpNum;//记录职工人数
	Worker** m_EmpArray;//职工数组指针
	void Add_Emp();//增加职工
	void Save();//保存职工
	bool m_Fileisempty;//文件为空或者不存在
	void Show_Menu();//展示菜单
	int get_EmpNum();//获取职工人数
	void init_Emp();//读取文件到内存
	void show_emp();//展示职工表
	void Del_Emp();//删除职工;
	int IsExist(int id);//判断是否存在，存在返回位置，不存在返回-1；
	void Mod_Emp();
	void Find_Emp();
	void Sort_Emp();
	void Clear_file();
	~WorkManager();
};