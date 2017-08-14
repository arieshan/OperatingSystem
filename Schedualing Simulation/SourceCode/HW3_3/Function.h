#pragma once
#include "Event.h"
#include <time.h>
#include <stdlib.h>
#include <queue>
#include <sstream>
#include <fstream>

struct compare {		// sort the event by time and type
	bool operator()(Event &a, Event &b) {
		if (a.get_type() > b.get_type())
			return true;
		else {
			if (a.get_type() == b.get_type()) {
				if (a.get_sysTime() > b.get_sysTime())
					return true;
				else
					if (a.get_sysTime() == b.get_sysTime())
						return a.get_ID() > b.get_ID();
					else
						return false;
			}
			else
				return false;
		}
	}
};

struct compare_SJF {		// sort the event by predict time and type
	bool operator()(Event &a, Event &b) {
		if (a.get_sysTime() > b.get_sysTime())
			return true;
		else {
			if (a.get_sysTime() == b.get_sysTime()) {
				if (a.get_predictTime() > b.get_predictTime())
					return true;
				else {
					if (a.get_predictTime() == b.get_predictTime())
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

/* generate random burst time*/
double randomUniform(double dMinValue, double dMaxValue);

/* initial JOBS*/
void ini_JOB(priority_queue<Event, vector<Event>, compare> &event_queue);

/* convert integer to  string */
string itos(int i);

/* FCFS simulation */
void FCFS_Simulation(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, deque<Event> &ready_queue, double system_time, double lambda);

/* SJF simulation */
void SJF_Simulation(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, priority_queue<Event, vector<Event>, compare_SJF> &sjf_ready_queue, double system_time, double lambda, double alpha, string algorithm);

/* generat a random number with means equals lambda*/
double randomExponential(double lambda);

/* generate random number with specific JOB*/
double randomGenerate(double lambda, string name);

/* calculate the average waiting time and ohter attributes */
void calculate(unordered_map<int, double> &waiting_time, unordered_map<int, double> &turnaround_time, string &algorithm, unordered_map<int, Event> &list_event,
	queue<pair<Event, double> > &sequeue, int count_switch, double total_time, double quantum);

/* RR simulation */
void RR_Simulation(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, deque<Event> &ready_queue, double system_time, double &quantum, double lambda, string algorithm);

