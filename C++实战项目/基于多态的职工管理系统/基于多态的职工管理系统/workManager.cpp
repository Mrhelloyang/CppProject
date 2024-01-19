#include"workManager.h"
WorkManager::WorkManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		//cout << "文件打开失败" << endl;
		this->m_EmpNum = 0;//初始化记录人数
		this->m_Fileisempty = true;//文件为空
		this->m_EmpArray = NULL;//初始化数组指针为空
		ifs.close();
		return;
	}
	//文件存在，数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "问价为空" << endl;
		this->m_EmpNum = 0;
		this->m_Fileisempty = true;
		this->m_EmpArray = NULL;
		ifs.close();
		return;
	}
	//文件存在，数据为空
	int num = this->get_EmpNum();
	//cout << "职工人数为：" << num << endl;
	this->m_EmpNum = num;
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	this->init_Emp();

	//for (int i = 0; i < this->m_EmpNum; i++)
	//{
	//	cout << "id:" << this->m_EmpArray[i]->m_id
	//		<< "name:" << this->m_EmpArray[i]->m_name
	//		<< "job:" << this->m_EmpArray[i]->m_job << endl;
	//}
}
void WorkManager::Show_Menu()
{
	cout << "**************************************" << endl;
	cout << "******* 欢迎使用职工管理系统！ *******" << endl;
	cout << "*********** 0.退出管理程序 ***********" << endl;
	cout << "*********** 1.增加职工信息 ***********" << endl;
	cout << "*********** 2.显示职工信息 ***********" << endl;
	cout << "*********** 3.删除离职职工 ***********" << endl;
	cout << "*********** 4.修改职工信息 ***********" << endl;
	cout << "*********** 5.查找职工信息 ***********" << endl;
	cout << "*********** 6.按照编号排序 ***********" << endl;
	cout << "*********** 7.清空所有文档 ***********" << endl;
	cout << "**************************************" << endl;
	cout << endl;
}

void WorkManager::ExitSystem()
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);//结束程序；

}

void  WorkManager::Add_Emp()
{
	int addNum = 0;
	cout << "请输入添加人数:" << endl;
	cin >> addNum;
	if (addNum > 0)
	{
		int newSize = addNum + this->m_EmpNum;
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dselect;
			cout << "请输入第" << i + 1 << "个新职工的编号" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个新职工的姓名" << endl;
			cin >> name;
			cout << "system:请选择该职工的职位（1 员工 2 经理 3 总裁）:";
			cin >> dselect;
			Worker* worker = NULL;
			switch (dselect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "system:输入错误！请仔细查看后再次输入！！！" << endl;
				break;
			}
			newSpace[this->m_EmpNum + i] = worker;


		}
		delete[]this->m_EmpArray;//释放以前的空间
		this->m_EmpArray = newSpace;//更新空间的指向
		this->m_EmpNum = newSize;//更新职工人数
		this->m_Fileisempty = false;
		cout << "成功添加" << addNum << "个新职工" << endl;//成功提示
		this->Save();
	}
	else
	{
		cout << "输入数据有误!" << endl;

	}
	system("pause");
	system("cls");
}
void WorkManager::Save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_id << " "
			<< this->m_EmpArray[i]->m_name << " "
			<< this->m_EmpArray[i]->m_job << " " << endl;
	}
	ofs.close();
}
int WorkManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		num++;
	}
	return num;
}

void WorkManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1)
		{
			worker = new Employee(id, name, dId);
		}
		if (dId == 2)
		{
			worker = new Manager(id, name, dId);
		}
		if (dId == 3)
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index++] = worker;
	}
}
void WorkManager::show_emp()
{
	if (this->m_Fileisempty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}

	}
	system("pause");
	system("cls");
}

void WorkManager::Del_Emp()
{
	if (this->m_Fileisempty)
	{
		cout << "文件不存在或者为空！" << endl;
	}
	else
	{
		cout << "请输入删除员工编号：" << endl;
		int id;
		cin >> id;
		int index = this->IsExist(id);
		if (index == -1)
		{
			cout << "职工不存在" << endl;
		}
		else
		{
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			this->m_EmpNum--;
			this->Save();
			cout << "删除成功" << endl;
		}
	}
	system("pause");
	system("cls");
}
int WorkManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}

void WorkManager::Mod_Emp()
{
	if (this->m_Fileisempty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入需要修改信息的职工编号" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret != -1)
		{
			delete this->m_EmpArray[ret];
			int newid;
			string newname;
			int newdselect;
			cout << "查到：" << id << "号职工，请输入新职工号" << endl;
			cin >> newid;
			cout << "请输入新职工姓名" << endl;
			cin >> newname;
			cout << "system:请选择该职工的职位（1 员工 2 经理 3 总裁）:";
			cin >> newdselect;
			Worker* worker = NULL;
			switch (newdselect)
			{
			case 1:
				worker = new Employee(newid, newname, newdselect);
				break;
			case 2:
				worker = new Manager(newid, newname, newdselect);
				break;
			case 3:
				worker = new Boss(newid, newname, newdselect);
				break;
			default:
				cout << "system:输入错误！请仔细查看后再次输入！！！" << endl;
				break;
			}
			this->m_EmpArray[ret] = worker;
			cout << "修改成功" << endl;
			this->Save();

		}
		else
		{
			cout << "查无此人" << endl;
		}

	}
	system("pause");
	system("cls");

}


void WorkManager::Find_Emp()
{
	if (this->m_Fileisempty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入查找方式：" << endl;
		cout << "1、按职工编号查找" << endl;
		cout << "2、按职工姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1)
		{
			cout << "请输入需要查找的职工编号" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				this->m_EmpArray[ret]->showInfo();
			}
			else
			{
				cout << "没有查到该职工编号信息" << endl;
			}
		}
		else if (select == 2)
		{
			string name;
			cout << "请输入需要查找的职工姓名" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_name == name)//千万别再if后面写;重点
				{
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "没有查到该姓名员工信息" << endl;
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}
	}
	system("pause");
	system("cls");
}

void WorkManager::Sort_Emp()
{
	if (this->m_Fileisempty)
	{
		cout << "文件不存在或者为空" << endl;
	}
	else
	{
		cout << "请输入排序方式：" << endl;
		cout << "1、按职工编号降序" << endl;
		cout << "2、按职工编号升序" << endl;
		int select;
		cin >> select;
		Worker* worker = NULL;
		if (select == 1)
		{
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				for (int j = 0; j < this->m_EmpNum - 1 - i; j++)
				{
					if (this->m_EmpArray[j]->m_id < this->m_EmpArray[j + 1]->m_id)
					{
						worker = this->m_EmpArray[j + 1];
						this->m_EmpArray[j + 1] = this->m_EmpArray[j];
						this->m_EmpArray[j] = worker;
					}
				}
			}
		}
		else if (select == 2)
		{
			for (int i = 0; i < this->m_EmpNum - 1; i++)
			{
				for (int j = 0; j < this->m_EmpNum - 1 - i; j++)
				{
					if (this->m_EmpArray[j]->m_id > this->m_EmpArray[j + 1]->m_id)
					{
						worker = this->m_EmpArray[j + 1];
						this->m_EmpArray[j + 1] = this->m_EmpArray[j];
						this->m_EmpArray[j] = worker;
					}
				}
			}
		}
		else
		{
			cout << "输入有误" << endl;
		}

	}
	system("pause");
	system("cls");
}
void WorkManager::Clear_file()
{
	cout << "清空文件?" << endl;
	cout << "1、确认清空文件" << endl;
	cout << "2、取消清空文件" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[]this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_Fileisempty = true;
		}
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}
WorkManager::~WorkManager()
{
	if (this->m_EmpArray != NULL)
	{
		delete[]this->m_EmpArray;//这里加[]就是把这个指针所指向的空间一一释放
		this->m_EmpArray = NULL;//然后置空
	}
}