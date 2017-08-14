/* * * * * * * * * * * * * * * * * * * * * * * * *
*  course       :  CS_520                        *
*  First Name   :  Xiao                          *
*  Second Name  :  Li                            *
*  CWID         :  10409766                      *
*  Subject      :  Home_work_2 Bus_Simulation    *
* * * * * * * * * * * * * ** * * * * * * * * * * */

#include "Initial.h"   // import the initial function and other functions
 

int main() {

	priority_queue<Event, vector<Event>, compare> queue_event; // define a priority_queue to store event, so the event in specific order
	vector<int> stop_wait_number(15, 0);    // record every stop waiting sequence
	vector<int> stop_mutex(15, 1);          // simulate semaphore for each stop, only one bus can boarding at one stop
	vector<int> max_wait_length(15, 0);     // record the max waiting people number for each stop hourly 
	vector<int> min_wait_length(15, 99999);  // record the min waiting people number for each stop hourly
	vector<double> average(15, 0.0);         // record the average waiting people number for each stop hourly
	vector<unordered_map<double, int> > wait_sequence_counter(15);      // record the stop people waiting number and the current time by each time 
	double system_time = 0.0;				 // define a system time 							
	int hour, min;
	double second;
	ofstream outfile("log.txt");			// generate log.txt
	int event_count = 0;					// count event, make sure every event has a number so that if some evens have same system time, they will be sort as event number

	init_Event(queue_event);				// initial event and other parametors

	while (true) {							// start simulating
		Event current = queue_event.top();   // get an event from the priority queue
		system_time = current.get_time();	 // get the event time

		if (current.get_time() > 28800)		// simulate time is 8 hour = 8 *60 * 60 = 28800
			break;
	
		/* change the system time to real time */
		hour = static_cast<int>(system_time / 3600);		
		min = static_cast<int>(system_time / 60 - hour * 60);
		second = system_time - hour*3600 - min*60;

		/* according to the event type to select responding action  **
		** There three action: person, arrival and boarding         **
		**	                                                        **
		*/
		switch (current.get_Type()) {    // get event type: 1 is person, 2 is arrival, 3 is boarding

		case 1: {		// person event: generate a person at each stop at exponential randomly
			stop_wait_number[current.get_Stop_Number()]++;		// current event stop number comes one person
			system_time = system_time + (0.2) * randomExponential(1.0) * 60;	// calculate next person event time 
			queue_event.push(Event(1, system_time,current.get_Stop_Number(),event_count));	// generate a new person event
			// output the event to log.txt
			outfile << "another person at  " << current.get_Stop_Number() << "  at time: " << hour << " : " << min << " : " << second << endl;
			
		}break;

		case 2: {	// arrival event
			save_Bus_info(current);  // save the current bus location
			if (stop_wait_number[current.get_Stop_Number()] == 0) {			// is there is no one waiting at current stop, just leaving(generate new arrival event at system time + 5min)
				queue_event.push(Event(2, system_time + 5 * 60, (current.get_Stop_Number() + 1) % 15, current.get_Bus_Number(), event_count));
				outfile << "The bus " << current.get_Bus_Number() << " is arrive at stop "<< current.get_Stop_Number() <<" and leaving form stop " << current.get_Stop_Number() << " (no passagers waiting) at time: " << hour << " : " << min << " : " << second << endl;
			}
			else {	// there are some people waiting  
				stop_mutex[current.get_Stop_Number()] --;	//lock the current bus station
				if (stop_mutex[current.get_Stop_Number()] < 0) { // if there have some buses already there, the current bus waiting for a boarding time(generate new arrival event at system time + 2s)
					queue_event.push(Event(2, system_time + 2, current.get_Stop_Number(), current.get_Bus_Number(), event_count));
					outfile << "The bus " << current.get_Bus_Number() << " is waiting at stop " << current.get_Stop_Number() << "  at time: " << hour << " : " << min << " : " << second << endl;
					stop_mutex[current.get_Stop_Number()]++;  // unlock the bus station
				}
				else {	// there is no other bus at the stop , call boarding event
					record_squence(wait_sequence_counter, current, stop_wait_number); //  record current time and stops waiting people number
					queue_event.push(Event(3, system_time, current.get_Stop_Number(), current.get_Bus_Number(), event_count));
					outfile << "The bus " << current.get_Bus_Number() << " is arrive at stop " << current.get_Stop_Number() << "  at time: " << hour << " : " << min << " : " << second << endl;
				}
			}
		}break;
			
		case 3: { // boarding event, every single person boarding time is 2s
			stop_wait_number[current.get_Stop_Number()]--; // one person boarding at the current bus 
			system_time += 2;		// boarding cost 2s 
			current.update(system_time);
			save_Bus_info(current);
			outfile << "The bus "<< current.get_Bus_Number() << " is boarding at stop " <<current.get_Stop_Number() << "  at time: " << hour << " : " << min << " : " << second << "  the wait sequence now is "<< stop_wait_number[current.get_Stop_Number()]<<endl;
			
			if (stop_wait_number[current.get_Stop_Number()] > 0) { // if there is any other person waiting at the stop, call the boarding again
				queue_event.push(Event(3, system_time, current.get_Stop_Number(), current.get_Bus_Number(), event_count));
			}
			else {	// if there is no other peroson at the current stop, go to next stop			
				queue_event.push(Event(2, system_time + 5*60, (current.get_Stop_Number() + 1) % 15, current.get_Bus_Number(), event_count));
				stop_mutex[current.get_Stop_Number()]++;
				outfile << "The bus " << current.get_Bus_Number() << " is leaving form stop " << current.get_Stop_Number() << "  at time: " << hour << " : " << min << " : " << second << endl;
			}
			
		}break;
		}
		queue_event.pop();	// pop the current event from the priority queue
		event_count++;		// event couter increase by one
	}

	/*  calculate the average waiting sequence and record the max and min waiting length hourly  */
	calculate_average(wait_sequence_counter, min_wait_length, max_wait_length);

	/*  save stop waiting people number at every event time  */
	save_Stop_Waiting_info(wait_sequence_counter);

	outfile.close(); // close the ofstream

	return 0;
}