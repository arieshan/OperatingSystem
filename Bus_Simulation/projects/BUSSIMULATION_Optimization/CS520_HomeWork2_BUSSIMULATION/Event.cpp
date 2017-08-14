/* * * * * * * * * * * * * * * * * * * * * * * * *
*  course       :  CS_520                        *
*  First Name   :  Xiao                          *
*  Second Name  :  Li                            *
*  CWID         :  10409766                      *
*  Subject      :  Home_work_2 Bus_Simulation    *
* * * * * * * * * * * * * ** * * * * * * * * * * */

#include "Event.h"

/*  constructor for bus event */
Event::Event(int type, double system_time, int stop_number, int bus_number, int event_counter) {
	event_type = type;
	time = system_time;
	this->stop_number = stop_number;
	this->bus_number = bus_number;
	event_count = event_counter;
}

/*  constructor for person event, bus number initial as -1 */
Event::Event(int type, double system_time, int stop_number, int event_counter) {
	event_type = type;
	time = system_time;
	this->stop_number = stop_number;
	bus_number = -1;
	event_count = event_counter;
}

/*  get the event type */
int Event::get_Type() {
	return event_type;
}

/*  get the event time */
double  Event::get_time() {
	return time;
}

/*  get the event stop number */
int  Event::get_Stop_Number() {
	return stop_number;
}

/*  get the event bus number */
int  Event::get_Bus_Number() {
	return bus_number;
}

/*  update the event time */
double Event::update(double increase_time) {
	time = increase_time;
	return time;
}

/*  get the event number */
int Event::get_Event_Count() {
	return event_count;
}