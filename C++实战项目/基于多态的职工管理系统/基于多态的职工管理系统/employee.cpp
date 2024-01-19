using namespace std;
#include<iostream>
#include"employee.h"

Employee::Employee(int id, string name, int job)
{
	this->m_id = id;
	this->m_name = name;
	this->m_job = job;
}
void Employee::showInfo()
{
	cout << "system:工号：" << this->m_id << "\t姓名：" << this->m_name
		<< "\t职位：" << this->getjobname() << "\t职责：完成经理交给的任务" << endl;
}
string Employee::getjobname()
{
	return string("员工");
}