#pragma once
using namespace std;
#include<iostream>
#include"worker.h"

class Employee :public Worker {

public:
	Employee(int id, string name, int job);
	virtual void showInfo();
	virtual string getjobname();
};