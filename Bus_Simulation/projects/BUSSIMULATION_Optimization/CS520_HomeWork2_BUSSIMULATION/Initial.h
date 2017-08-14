/* * * * * * * * * * * * * * * * * * * * * * * * *
*  course       :  CS_520                        *
*  First Name   :  Xiao                          *
*  Second Name  :  Li                            *
*  CWID         :  10409766                      *
*  Subject      :  Home_work_2 Bus_Simulation    *
* * * * * * * * * * * * * ** * * * * * * * * * * */

#pragma once
#include "Event.h"
#include <queue>
#include <fstream>
#include <unordered_map>  // import hasmap method
using namespace std;

/* compare function: makesure the priority queue as  **
** ascending order by time, if events time are same, **
** the earlier event has higher priority             */
struct compare {	
	bool operator()(Event &a, Event &b) {
		if(a.get_time() > b.get_time())
			return true;
		else {
			if (a.get_time() == b.get_time())
				return a.get_Event_Count() > b.get_Event_Count();
			else
				return false;
		}
	}
};

void init_Event(priority_queue<Event, vector<Event>, compare> &queue_event); // initial event
double randomExponential(double lambda);		// generater a exponential random number, used from http://www.cnblogs.com/yeahgis/archive/2012/07/15/2592687.html
void save_Bus_info(Event event);				// save bus info at .txt as <time , current_location>

// save stop waiting people number at .txt,include max and min waiting length
void save_Stop_info(int hourly_time, int stop_number, double wait_number);

// save 8 hours total average  , max average and min average of each stop
void save_total_average_stop_info(int stop_number, double max, double min, double total_average);

// save stop waiting people number at every event time
void save_Stop_Waiting_info(vector<unordered_map<double, int> > &wait_sequence_counter);

// record every discreet time the stop waiting people number 
void record_squence(vector<unordered_map<double, int> > &wait_sequence_counter, Event event, vector<int> stop_wait_number); 

// calculate the average waiting sequence and record the max and min waiting length hourly
void calculate_average(vector<unordered_map<double, int> > &wait_sequence_counter,vector<int> &min_wait_length, vector<int> max_wait_length);




