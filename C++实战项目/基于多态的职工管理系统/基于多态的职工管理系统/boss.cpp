#include "boss.h"

Boss::Boss(int id, string name, int job) {
	this->m_id = id;
	this->m_name = name;
	this->m_job = job;
}

void Boss::showInfo() {
	cout << "system:工号：" << this->m_id << "\t姓名：" << this->m_name
		<< "\t职位：" << this->getjobname() << "\t职责：管理公司所有事务" << endl;
}

string Boss::getjobname() {
	return string("总裁");
}