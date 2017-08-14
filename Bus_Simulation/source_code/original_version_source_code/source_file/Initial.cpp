/* * * * * * * * * * * * * * * * * * * * * * * * *
*  course       :  Operating System              *
*  First Name   :  Xiaohan                       *
*  Last Name    :  Chang                         *
*  Subject      :  Bus_Simulation                *
* * * * * * * * * * * * * ** * * * * * * * * * * */

#include "Initial.h"

/* initial the event and other parameter from the   **
** initial.txt file.  person event and bus event    **
** use different constructor of class Event         **
*/

void init_Event(priority_queue<Event, vector<Event>, compare> &queue_event) { 
	ifstream infile("initial.txt");		// read the initial.txt file
	int type, stop_number, bus_number;
	double time;
	int event_counter = 0;

	if (!infile.is_open()) {
		cerr << "cannot open initial_bus.txt" << endl;
	}

	cout << "The initial information is as follows :" << endl;
	cout << "Bus number : 5 " << endl;
	cout << "Stop number : 15" << endl;
	cout << "The person arrive rate is 5 in every minute" << endl;
	cout << "The boarding time is 2s each person" << endl;
	cout << endl;
	while (!infile.eof()) {  // generate events, type = 1 means that is person event
		infile >> type >> time >> stop_number >> bus_number;
		if (type == 1) {
			Event new_event(type, time, stop_number, event_counter);
			queue_event.push(new_event);
			cout << "Stop number " << new_event.get_Stop_Number() << " at time " << new_event.get_time() << " comes the first person " << endl;
		}
		else {
			Event new_event(type, time, stop_number, bus_number, event_counter);
			queue_event.push(new_event);
			cout << "Bus number " << new_event.get_Bus_Number() << " at time " << new_event.get_time() << " at stop " << new_event.get_Stop_Number() << endl;

		}
	}

	infile.close();

}


/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **
**  generate a random number from Exponential distribution                       **
**  used from http://www.cnblogs.com/yeahgis/archive/2012/07/15/2592687.html     **
** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * **/
double randomExponential(double lambda)
{
	double pV = 0.0;
	while (true)
	{
		pV = (double)rand() / (double)RAND_MAX;
		if (pV != 1)
		{
			break;
		}
	}
	pV = (-1.0 / lambda)*log(1 - pV);
	return pV;
}

/*  store the event time and stops waiting people number as <time, wait_length> pairs  */
void record_squence(vector<unordered_map<double, int> > &wait_sequence_counter, Event event, vector<int> stop_wait_number) {
	for (int i = 0; i < wait_sequence_counter.size(); i++)
		wait_sequence_counter[i].insert({ event.get_time(), stop_wait_number[i] });
}

/*  calculate the average waiting sequence and record the max and min waiting length hourly  */
void calculate_average(vector<unordered_map<double, int> > &wait_sequence_counter, vector<int> &min_wait_length, vector<int> max_wait_length) {
	for (int k = 0; k < 15; k++) {
		double temp = 0.0; // store the total waiting people number in one hour, it will be set zero in another hour
		int count = 0;    // store the number of times we store the waiting people number,  it will be set zero in another hour
		double temp_total_sum = 0; //store 8 hour total sum
		double max = 0;
		double min = 99999;

		for (int i = 0; i < 8;i++) {
			temp = 0;
			count = 0;
			for (auto& x : wait_sequence_counter[k]) {  // x.first stores the time, x. second stores the waiting people number
				if (x.first > i * 3600 && x.first < 3600 * (i + 1))
				{
					if (max_wait_length[k] < x.second)
						max_wait_length[k] = x.second;
					if (min_wait_length[k] > x.second)
						min_wait_length[k] = x.second;
					temp += x.second;
					count++;

				}
			}
			temp /= count;
			if (max < temp) max = temp;
			if (min > temp) min = temp;
			temp_total_sum += temp;
			save_Stop_info(i + 1, k, temp); // call the save_Stop_info function to save the average ,max and min waiting length at each stop hourly
		}
		save_total_average_stop_info(k , max, min, temp_total_sum / 8);
	}
}

/*  save the bus current time and current location to a txt file  */
void save_Bus_info(Event event) {
	ofstream fileout;
	switch (event.get_Bus_Number()) {
	case 1: {
		fileout.open("Bus_number_one.txt", ios::app);
	}break;
	case 2: {
		fileout.open("Bus_number_two.txt", ios::app);
	}break;
	case 3: {
		fileout.open("Bus_number_three.txt", ios::app);
	}break;
	case 4: {
		fileout.open("Bus_number_four.txt", ios::app);
	}break;
	case 5: {
		fileout.open("Bus_number_five.txt", ios::app);
	}break;
	}
	fileout << event.get_time() << " " << event.get_Stop_Number() << endl;
	fileout.close();
}


/*  save the stop number waiting people infomation to Data_file.txt , include average waiting length , max length, min length hourly */
void save_Stop_info(int hourly_time, int stop_number, double wait_number) {
	ofstream fileout;
	fileout.open("Stop_waiting_length_hourly.txt", ios::app);
	fileout << "stop " <<stop_number << " average waiting number in the "<< hourly_time <<" hour is: " << wait_number  << endl;
	fileout.close();
}
/*  save stop waiting people number at every event time  */
void save_Stop_Waiting_info(vector<unordered_map<double, int> > &wait_sequence_counter) {
	ofstream fileout;
	fileout.open("Bus_Stop_waiting_Observe.txt");
	for (int i = 0; i < 15; i++) {
		for(auto& x:wait_sequence_counter[i])
			fileout << i << " " << x.first << " " << x.second << endl;
	}
	fileout.close();
}

/*  save 8 hours total average  , max average and min average of each stop  */
void save_total_average_stop_info(int stop_number, double max, double min, double total_average) {
	ofstream fileout;
	fileout.open("Stop_total_average_waiting_info.txt", ios::app);
	fileout << "stop " << stop_number << "  max average waiting length is " << max << "  min average waiting length is " << min << "  total average waiting length is " << total_average << endl;
	fileout.close();
}