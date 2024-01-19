#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include"workManager.h"
int main()
{
	WorkManager wm;
	int choice = 0;
	while (1)
	{
		wm.Show_Menu();
		int choice = 0;
		cout << "请输入您的选项" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://退出管理程序
			wm.ExitSystem();
			break;
		case 1://增加职工信息
			wm.Add_Emp();
			break;
		case 2://显示职工信息
			wm.show_emp();
			break;
		case 3://删除离职职工
			wm.Del_Emp();
			break;
		case 4://修改职工信息
			wm.Mod_Emp();
			break;
		case 5://查找职工信息
			wm.Find_Emp();
			break;
		case 6://按照编号排序
			wm.Sort_Emp();
			wm.Save();
			break;
		case 7://清空所有文档
			wm.Clear_file();
			break;
		}
	}
	return 0;
}