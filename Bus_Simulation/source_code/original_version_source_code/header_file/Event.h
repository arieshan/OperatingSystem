/* * * * * * * * * * * * * * * * * * * * * * * * *
*  course       :  Operating System              *
*  First Name   :  Xiaohan                       *
*  Last Name    :  Chang                         *
*  Subject      :  Bus_Simulation                *
* * * * * * * * * * * * * ** * * * * * * * * * * */
#pragma once
#include <iostream>
#include <queue>
using namespace std;

class Event {  //  define the event structure. Main simulation object
private:
	int event_type; // define event type
	double time;	// define the event time
	int stop_number;	// record the current event stop number
	int bus_number;		// record the current bus number
	int event_count;	// record the current event number
public:
	Event(int type, double system_time, int stop_number, int bus_number, int event_counter);  // constructor for bus event 
	Event(int type, double system_time, int stop_number,int event_counter);					  // constructor for person event
	int get_Type();									// get the event type
	double get_time();								// get the event time
	int get_Stop_Number();							// get the event stop number
	int get_Bus_Number();							// get the event bus number
	double update(double increase_time);			// update the event time
	int get_Event_Count();							// get the event number
};