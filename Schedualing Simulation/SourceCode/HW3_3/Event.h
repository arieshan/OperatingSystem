#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

using namespace std;

class Event {		// define attributes of event 
private:
	double system_time;
	double arrival_time;
	double running_time;
	double remain_time;
	double predict_time;
	int pid;
	int type;
	string name;
public:
	Event(int type, int id, double arrival_time, double running_time, string na) {
		this->type = type;
		this->arrival_time = arrival_time;
		this->running_time = running_time;
		remain_time = running_time;
		system_time = arrival_time;
		name = na;
		pid = id;
		predict_time = 0;

	}
	Event() {};
	double get_sysTime() { return system_time; }
	double get_runTime() { return running_time; }
	double get_arrTime() { return arrival_time; }
	double get_remainTime() { return remain_time; }
	double get_predictTime() { return predict_time; }
	int get_ID() { return pid; }
	int get_type() { return type; }
	string get_Name() { return name; }

	void update_sysTime(double time) { system_time = time; }
	void update_remainTime(double time) { remain_time = time; }
	void update_ID(int id) { pid = id; }
	void update_type(int type) { this->type = type; }
	void update_predictTime(double time) { predict_time = time; }


};