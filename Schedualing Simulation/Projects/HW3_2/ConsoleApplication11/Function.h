#pragma once
#include "Event.h"

struct compare {   //  make sure event sorted as ascending time order
	bool operator()(Event &a, Event &b) {
		if (a.get_type() > b.get_type())
			return true;
		else {
			if (a.get_type() == b.get_type()) {
				if (a.get_time() > b.get_time())
					return true;
				else 
					if(a.get_time() == b.get_time())
						return a.get_ID() > b.get_ID();
					else
						return false;
			}
			else
				return false;
		}
	}
};

struct compare_SJF { //  make sure shortest job at the top the queue
	bool operator()(Event &a, Event &b) {
		if (a.get_time() > b.get_time())
			return true;
		else {
			if (a.get_time() == b.get_time()) {
				if (a.get_running_time() > b.get_running_time())
					return true;
				else {
					if (a.get_running_time() == b.get_running_time())
						return a.get_ID() > b.get_ID();
					else
						return false;
				}
			}
			else
				return false;
		}
	}
};

struct compare_Priority {  //  make sure the highest priority process at the top of the queue
	bool operator()(Event &a, Event &b) {
		if (a.get_time() > b.get_time())
			return true;
		else {
			if (a.get_time() == b.get_time()) {
				if (a.get_pri() > b.get_pri())
					return true;
				else {
					if (a.get_pri() == b.get_pri())
						return a.get_ID() > b.get_ID();
					else
						return false;
				}
			}
			else
				return false;
		}
	}
};


/* initial methods   */
void ini_Event_5_3(priority_queue<Event, vector<Event>, compare> &event_queue);
void ini_Event_5_12(priority_queue<Event, vector<Event>, compare> &event_queue);


/*  schedualing methods */
void FCFS(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count, bool &CPU,
	deque<Event> &ready_queue, double  system_time);

void SJF(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count, bool &CPU,
	priority_queue<Event, vector<Event>, compare_SJF> &sjf_ready_queue, double  system_time);

void SJF_Delay(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count, bool &CPU,
	priority_queue<Event, vector<Event>, compare_SJF> &sjf_ready_queue, double  system_time, double &delay_time);

void RR(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count, bool &CPU,
	deque<Event> &ready_queue, double  system_time, double &quantum);

void Priority_Sche(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count, bool &CPU,
	priority_queue<Event, vector<Event>, compare_Priority> &priority_ready_queue, double  system_time);


/* calculation methods  */
void calculate_RR(vector<double> &waiting_time, vector<double> &turnaround_time, string &algorithm, unordered_map<int, Event> &list_event, queue<pair<Event, double> > &sequeue);
void calculate(vector<double> &waiting_time, vector<double> &turnaround_time, string &algorithm, unordered_map<int, Event> &list_event, queue<Event> &sequeue);