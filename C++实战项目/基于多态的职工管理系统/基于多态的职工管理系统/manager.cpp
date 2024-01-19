#include "manager.h"

Manager::Manager(int id, string name, int job) {
	this->m_id = id;
	this->m_name = name;
	this->m_job = job;
}

void Manager::showInfo() {
	cout << "system:工号：" << this->m_id << "\t姓名：" << this->m_name
		<< "\t职位：" << this->getjobname() << "\t职责：完成总裁交给的任务,并下发任务给员工" << endl;
}

string Manager::getjobname() {
	return string("经理");
}