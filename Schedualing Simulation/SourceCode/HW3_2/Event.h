#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include <deque>
#include <queue>
#include <string>
#include <utility>
using namespace std;

class Event {  // define event attributes 
private:
	int event_type;
	double sys_time;
	int pid;
	double running_time;
	double arrive_time;
	int priority;
	string name;
public:
	Event(int type, double time, double run_time, int pri, string na, int id) 
	{
		event_type = type; sys_time = time; pid = id;
		running_time = run_time; priority = pri; name = na;
		arrive_time = time;
	}
	Event() {};
	int get_type() { return event_type; }
	double get_time() { return sys_time; }
	int get_ID() { return pid; }
	int get_pri() { return priority; }
	double get_running_time() { return running_time; }
	double get_arrival_time() { return arrive_time; }
	string get_Name() { return name; }
	void update_ID(int ID) { pid = ID; }
	void update_type(int type) { event_type = type; }
	void update_time(double time) { sys_time = time; }
	void update_running_time(double time) { running_time = time; }

};