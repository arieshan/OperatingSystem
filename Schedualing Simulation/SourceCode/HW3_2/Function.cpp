#include "Function.h"

/* initial event for the simulation   */
void ini_Event_5_3(priority_queue<Event, vector<Event>, compare> &event_queue) {

	Event new_event(1, 0.0, 8, 1, "P1", -3);
	event_queue.push(new_event);
	Event new_event1(1, 0.4, 4, 1, "P2", -2);
	event_queue.push(new_event1);
	Event new_event2(1, 1.0, 1, 1, "P3", -1);
	event_queue.push(new_event2);
}

/* initial event for the simulation   */
void ini_Event_5_12(priority_queue<Event, vector<Event>, compare> &event_queue) {
	Event new_event(1, 0.0, 10, 3, "P1", -10);
	event_queue.push(new_event);
	Event new_event1(1, 0.0, 1, 1, "P2", -8);
	event_queue.push(new_event1);
	Event new_event2(1, 0.0, 2, 3, "P3", -6);
	event_queue.push(new_event2);
	Event new_event3(1, 0.0, 1, 4, "P4", -4);
	event_queue.push(new_event3);
	Event new_event4(1, 0.0, 5, 2, "P5", -2);
	event_queue.push(new_event4);

}

/*  calculate the average waiting time , turnaround time and draw the Gantt charts */
void calculate(unordered_map<int, double> &waiting_time, unordered_map<int, double> &turnaround_time, string &algorithm, unordered_map<int, Event> &list_event, queue<Event> &sequeue) {
	double sum_waiting_time = 0.0;
	double sum_turnaround_time = 0.0;
	double average_waiting_time = 0.0;
	double average_turnaround_time = 0.0;
	double delay_time = 1.0;

	for (auto x : waiting_time) 
		sum_waiting_time += x.second;

	for (auto x : turnaround_time)
		sum_turnaround_time += x.second;

	cout << "The Average waiting time of " << algorithm << " is " << sum_waiting_time / waiting_time.size() << endl;
	cout << "The Average turnaround time of " << algorithm << " is " << sum_turnaround_time / turnaround_time.size() << endl;

	if(algorithm != "RR" && algorithm != "delay_SJF") {
		while (!sequeue.empty()) {
			Event current = sequeue.front();
			cout << " | " << current.get_Name();
			for (double i = 0; i < current.get_running_time(); i = i + 1)
				cout << "_";
			cout << turnaround_time[current.get_ID()] + current.get_arrival_time();
			sequeue.pop();
		}
		cout << " |" << endl;
		cout << endl;
	}


	if (algorithm == "delay_SJF") {
		for (int i = 0; i < delay_time; i++)
			cout << "| delay_" << delay_time;
		while (!sequeue.empty()) {
			Event current = sequeue.front();
			cout << " | " << current.get_Name();
			for (double i = 0; i < current.get_running_time(); i = i + 1)
				cout << "_";
			cout << turnaround_time[current.get_ID()] + current.get_arrival_time();
			sequeue.pop();
		}
		cout << " |" << endl;
		cout << endl;
	}
	
	
}

/*  calculate the average waiting time , turnaround time and draw the Gantt charts for RR */
void calculate_RR(unordered_map<int, double> &waiting_time, unordered_map<int, double> &turnaround_time, string &algorithm, unordered_map<int, Event> &list_event, queue<pair<Event, double> > &sequeue) {
	double sum_waiting_time = 0.0;
	double sum_turnaround_time = 0.0;
	double average_waiting_time = 0.0;
	double average_turnaround_time = 0.0;
	double delay_time = 1.0;

	for (auto x : waiting_time)
		sum_waiting_time += x.second;

	for (auto x : turnaround_time)
		sum_turnaround_time += x.second;

	cout << "The Average waiting time of " << algorithm << " is " << sum_waiting_time / waiting_time.size() << endl;
	cout << "The Average turnaround time of " << algorithm << " is " << sum_turnaround_time / turnaround_time.size() << endl;

	double time = 0.0;
	while (!sequeue.empty()) {
		Event current = sequeue.front().first;
		double time_length = sequeue.front().second;
		time += time_length;
		cout << " | " << current.get_Name();
		for (double i = 0; i < time_length; i = i + 1)
			cout << "_";
		cout << time;
		sequeue.pop();
	}
	cout << " |" << endl;
	cout << endl;

}

/*           FCFS methods      */
void FCFS(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, deque<Event> &ready_queue, double system_time) {
	unordered_map<int, double>  waiting_time;  // record average waiting time
	unordered_map<int, double> turnaround_time;      // record average turnaround time
	unordered_map<int, Event> list_event;		//  record event
	queue<Event> sequeue;		//  record event executing order
	while (!event_queue.empty()) {		// if there is an event not finished
		Event event = event_queue.top();		// get the event
		event_queue.pop();
		//system_time = event.get_time();
		switch (event.get_type()) {
		case 1: {//arrival
			if (PCB.find(event.get_ID()) == PCB.end()) {  // create PCB for this process
				++count;
				event.update_ID(count);						// create pid
				PCB[event.get_ID()] = "";					// initial status as null
				cout << "create PCB " << count << "successfully" << endl;		
				waiting_time.insert({event.get_ID(), 0.0});		// create waiting time position for this process
				turnaround_time.insert({ event.get_ID(), 0.0 });	// create turnaround time position for this process
				list_event.insert({event.get_ID(), event});		// put this process into the list
			}

			if (!CPU) {		// if CPU is free
				CPU = true;		// make cpu status is busy
				PCB[event.get_ID()] = "running";	// change process status to running
				event.update_type(2);		// change event type to completion
				event_queue.push(event);	
			}
			else {
				PCB[event.get_ID()] = "ready";		// if CPU is busy , the process' status is ready
				ready_queue.push_back(event);		// put the process into ready queue
				cout << "push event " << event.get_Name() << " into ready queue" << endl;
			}
		}break;
		case 2: {//completion
			system_time += event.get_running_time();	// finish the process
			PCB[event.get_ID()].clear();			// destory the process' PCB
			sequeue.push(event);					// put the process in the order queue
			if (event.get_ID() - 1 == 0) {			// if this is the first process, waiting time is 0 turnaround time is its burst time
				waiting_time[event.get_ID()] = 0;
				turnaround_time[event.get_ID()] = event.get_running_time();
			}
			else{		// if this process is not the first event,   waiting time is current system time minus the burst time and arrival time
				waiting_time[event.get_ID()] = system_time - event.get_running_time() - event.get_arrival_time();
				turnaround_time[event.get_ID()] = system_time - event.get_arrival_time();
				}
			cout << "finish " << event.get_Name() << "at time" << system_time << endl;
			if (!ready_queue.empty()) { // get next process from the ready queue and execute it 
				Event current = ready_queue.front();
				current.update_time(system_time);
				current.update_type(2);
				PCB[current.get_ID()] = "running";
				event_queue.push(current);
				ready_queue.pop_front();
			}
			else {
				CPU = false; // release CPU if all process is over
			}
		}break;

		}

	}

	cout << system_time << endl;
	string algorithm = "FCFS";
	calculate(waiting_time, turnaround_time, algorithm, list_event, sequeue); // calculate average waiting time and turnaround time and Gantt charts

}

/*            SJF methods          */
void SJF(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, priority_queue<Event, vector<Event>, compare_SJF> &sjf_ready_queue, double system_time) {
	unordered_map<int, double> waiting_time;     // record waiting time of each process
	unordered_map<int, double> turnaround_time;		// record turnaround time of wach process
	unordered_map<int, Event> list_event;		// record process
	queue<Event> sequeue;
	while (!event_queue.empty()) {		// if there is a process need to run
		Event event = event_queue.top();	// get the event
		event_queue.pop();
		switch (event.get_type()) {		// type 1 is arrival  type 2 is completion
		case 1: {//arrival
			if (PCB.find(event.get_ID()) == PCB.end()) {	// create the process' status 
				++count;
				event.update_ID(count);
				PCB[event.get_ID()] = "";
				cout << "create PCB " << count << "successfully" << endl;
				waiting_time.insert({ event.get_ID(), 0.0 });
				turnaround_time.insert({ event.get_ID(), 0.0 });
				list_event.insert({ event.get_ID(), event });
			}

			if (!CPU) {			// if CPU is free , complete the process
				CPU = true;
				PCB[event.get_ID()] = "running";
				event.update_type(2);
				sjf_ready_queue.push(event);
			}
			else {				// if CPU is not free, put this process into ready queue
				PCB[event.get_ID()] = "ready";
				event.update_type(2);
				sjf_ready_queue.push(event);
				cout << "push event " << event.get_Name() << " into ready queue" << endl;
			}
			if (event_queue.empty())
			{	
				Event new_event = sjf_ready_queue.top(); 
				sjf_ready_queue.pop();
				event_queue.push(new_event);

				while (!sjf_ready_queue.empty()) {
					Event temp = sjf_ready_queue.top();
					if (temp.get_time() >= system_time + new_event.get_running_time())
						break;
					temp.update_time(system_time + new_event.get_running_time());
					sjf_ready_queue.pop();
					sjf_ready_queue.push(temp);
				}
			}
		}break;
		case 2: {//completion
			system_time += event.get_running_time(); // complete the process execution
			PCB[event.get_ID()].clear();  // destroy the PCB
			sequeue.push(event);
			if ((system_time - event.get_running_time()) == 0) { // record the waiting time and turnaround time
				waiting_time[event.get_ID()] = 0;
				turnaround_time[event.get_ID()] = event.get_running_time() - event.get_arrival_time();
			}
			else {
				waiting_time[event.get_ID()] = system_time - event.get_running_time() - event.get_arrival_time();
				turnaround_time[event.get_ID()] = system_time - event.get_arrival_time();
			}
			cout << "finish " << event.get_Name() << "at time" << system_time << endl;
			if (!sjf_ready_queue.empty()) { // get the top process of the queue and execute
				Event current = sjf_ready_queue.top();
				current.update_time(system_time);
				PCB[current.get_ID()] = "running";
				event_queue.push(current);
				sjf_ready_queue.pop();

				while (!sjf_ready_queue.empty()) {	// update the ready queue's process system time
					Event temp = sjf_ready_queue.top();
					if (temp.get_time() >= system_time + current.get_running_time())
						break;
					temp.update_time(system_time + current.get_running_time());
					sjf_ready_queue.pop();
					sjf_ready_queue.push(temp);
				}
			}
			else
				CPU = false;
		}break;

		}

	}

	cout << system_time << endl;
	string algorithm = "SJF";
	calculate(waiting_time, turnaround_time, algorithm, list_event, sequeue);
}

/*  RR methods */
void RR(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, deque<Event> &ready_queue, double system_time, double &quantum) {
	unordered_map<int, double> waiting_time;
	unordered_map<int, double> turnaround_time;
	unordered_map<int, Event> list_event;
	queue<pair<Event, double> > sequeue;
	while (!event_queue.empty()) {	// if there is a process need to run
		Event event = event_queue.top();	// get the process
		event_queue.pop();
		switch (event.get_type()) {		// 1 arrival    2 completion   3 timer interrupt
		case 1: {//arrival
			if (PCB.find(event.get_ID()) == PCB.end()) {  // create the process' attributes
				++count;
				event.update_ID(count);
				PCB[event.get_ID()] = "";
				cout << "create PCB " << count << "successfully" << endl;
				cout << event.get_ID() << " running time is " << event.get_running_time() << endl;
				waiting_time.insert({ event.get_ID(), 0.0 });
				turnaround_time.insert({ event.get_ID(), 0.0 });
				list_event.insert({ event.get_ID(), event });
			}
			if (!CPU) {		// if CPU is free , run this process as for a quantum time
				CPU = true;
				PCB[event.get_ID()] = "running";
				event.update_type(3);
				event_queue.push(event);
			}
			else {			// if CPU is busy, push the process to a ready queue
				PCB[event.get_ID()] = "ready";
				ready_queue.push_back(event);
				cout << "push event " << event.get_ID() << " into ready queue" << endl;
			}
		}break;
		case 2: { // complete
			system_time += event.get_running_time();  // exectue the process for the rest time
			PCB[event.get_ID()].clear();			// destroy its PCB
			if ((system_time - event.get_running_time()) == 0) {	//  record the waiting time and turnaround time
				turnaround_time[event.get_ID()] = event.get_running_time() - event.get_arrival_time();
			}
			else {
				turnaround_time[event.get_ID()] = system_time - event.get_arrival_time();
				waiting_time[event.get_ID()] -= event.get_arrival_time();
			}
			cout << "finish " << event.get_ID() << "at time" << system_time << endl;
			if (ready_queue.empty()) 
				CPU = false;
			else {	// get another process from the ready queue and execute
				Event current = ready_queue.front();
				PCB[current.get_ID()] = "running";
				current.update_type(3);
				event_queue.push(current);
				ready_queue.pop_front();
			}
		}break;
		case 3: {//timer interrupt
			if (event.get_running_time() <= quantum) // if rest time less than quantum, then complete the process , otherwise call timer again 
				sequeue.push({ event,event.get_running_time() });
			else
				sequeue.push({event, quantum});
			if ((system_time ) == 0) {
				waiting_time[event.get_ID()] += 0;
			}
			else {
				waiting_time[event.get_ID()] += (system_time - event.get_time());
			}
			if (event.get_running_time() <= quantum) {
				event.update_type(2);
				event_queue.push(event);
				continue;
			}
			double remain_time = event.get_running_time() - quantum;	// calculate the remaining time
			system_time += quantum;	
			cout << "run " << event.get_ID() << " at time " << system_time << " and remaining  time is " << remain_time << endl;
			event.update_time(system_time);			// update the process system time 
			event.update_running_time(remain_time);		// update the process remaining time
			PCB[event.get_ID()] = "ready";				// change the status to ready
			ready_queue.push_back(event);				// put this process to the ready queue
			if (!ready_queue.empty()) {
				Event current = ready_queue.front();
				PCB[current.get_ID()] = "running";
				current.update_type(3);
				event_queue.push(current);
				ready_queue.pop_front();
			}

		}break;
		}
	}
	string algorithm = "RR";
	calculate_RR(waiting_time, turnaround_time, algorithm, list_event, sequeue);
}


/*  Nonpreemptive Priority methods */
void Priority_Sche(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count, bool &CPU,
	priority_queue<Event, vector<Event>, compare_Priority> &priority_ready_queue, double system_time) {
	unordered_map<int, double> waiting_time;
	unordered_map<int, double> turnaround_time;
	unordered_map<int, Event> list_event;
	queue<Event> sequeue;
	while (!event_queue.empty()) {		// if there is a process need to run 
		Event event = event_queue.top();		// get the event
		event_queue.pop();
		//system_time = event.get_time();
		switch (event.get_type()) {
		case 1: {//arrival
			if (PCB.find(event.get_ID()) == PCB.end()) {// create the process' attributes
				++count;
				event.update_ID(count);		
				PCB[event.get_ID()] = "";
				cout << "create PCB " << event.get_Name() << "successfully" << endl;
				waiting_time.insert({ event.get_ID(), 0.0 });
				turnaround_time.insert({ event.get_ID(), 0.0 });
				list_event.insert({ event.get_ID(), event });
			}

			if (!CPU) { // if CPU is free run the process
				CPU = true;
				PCB[event.get_ID()] = "running";
				event.update_type(2);
				priority_ready_queue.push(event);
			}
			else {	// otherwise push this process to the ready queue
				PCB[event.get_ID()] = "ready";
				event.update_type(2);
				priority_ready_queue.push(event);
				cout << "push event " << event.get_Name() << " into ready queue" << endl;
			}

			if (event_queue.empty())
			{	
				Event new_event = priority_ready_queue.top();
				priority_ready_queue.pop();
				event_queue.push(new_event);
				while (!priority_ready_queue.empty()) {
					Event temp = priority_ready_queue.top();
					if (temp.get_time() >= system_time + new_event.get_running_time())
						break;
					temp.update_time(system_time + new_event.get_running_time());
					priority_ready_queue.pop();
					priority_ready_queue.push(temp);
				}
			}
		}break;
		case 2: {//completion   
			system_time += event.get_running_time();	// execute the process
			PCB[event.get_ID()].clear();				// destroy the PCB
			sequeue.push(event);
			if ((system_time - event.get_running_time()) == 0) {	// record the waiting time and turnaround time
				waiting_time[event.get_ID()] = 0;
				turnaround_time[event.get_ID()] = event.get_running_time() - event.get_arrival_time();
			}
			else {
				waiting_time[event.get_ID()] = system_time - event.get_running_time() - event.get_arrival_time();
				turnaround_time[event.get_ID()] = system_time - event.get_arrival_time();
			}
			cout << "finish " << event.get_Name() << "at time" << system_time << endl;
			if (!priority_ready_queue.empty()) {	// continue execute the event in the ready queue
				Event current = priority_ready_queue.top();
				current.update_time(system_time);
				PCB[current.get_ID()] = "running";
				event_queue.push(current);
				priority_ready_queue.pop();

				while (!priority_ready_queue.empty()) {
					Event temp = priority_ready_queue.top();
					if (temp.get_time() >= system_time + current.get_running_time())
						break;
					temp.update_time(system_time + current.get_running_time());
					priority_ready_queue.pop();
					priority_ready_queue.push(temp);
				}
			}
			else {
				CPU = false;
			}
		}break;

		}

	}
	cout << system_time << endl;
	string algorithm = "Priority";
	calculate(waiting_time, turnaround_time, algorithm, list_event, sequeue);
}


void SJF_Delay(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count, bool &CPU,
	priority_queue<Event, vector<Event>, compare_SJF> &sjf_ready_queue, double system_time, double &delay_time) {

	unordered_map<int, double> waiting_time;
	unordered_map<int, double> turnaround_time;
	unordered_map<int, Event> list_event;
	system_time = delay_time;
	queue<Event> sequeue;
	while (!event_queue.empty()) {
		Event event = event_queue.top();
		event_queue.pop();
		switch (event.get_type()) {
		case 1: {//arrival
			if (PCB.find(event.get_ID()) == PCB.end()) {
				++count;
				event.update_ID(count);
				PCB[event.get_ID()] = "";
				cout << "create PCB " << count << "successfully" << endl;
				waiting_time.insert({ event.get_ID(), 0.0 });
				turnaround_time.insert({ event.get_ID(), 0.0 });
				list_event.insert({ event.get_ID(), event });
			}

			if (!CPU) {
				CPU = true;
				PCB[event.get_ID()] = "running";
				event.update_type(2);
				event_queue.push(event);
			}
			else {
				PCB[event.get_ID()] = "ready";
				event.update_type(2);
				sjf_ready_queue.push(event);
				cout << "push event " << event.get_Name() << " into ready queue" << endl;
			}

			if (event_queue.empty())
			{
				Event new_event = sjf_ready_queue.top();
				sjf_ready_queue.pop();
				event_queue.push(new_event);

				while (!sjf_ready_queue.empty()) {
					Event temp = sjf_ready_queue.top();
					if (temp.get_time() >= system_time + new_event.get_running_time())
						break;
					temp.update_time(system_time + new_event.get_running_time());
					sjf_ready_queue.pop();
					sjf_ready_queue.push(temp);
				}
			}break;

		case 2: {//completion
			if (event.get_time() < delay_time)
			{
				event.update_time(delay_time);
				sjf_ready_queue.push(event);
				CPU = false;
				if (!event_queue.empty())
					continue;
				else {
					Event new_event = sjf_ready_queue.top();
					sjf_ready_queue.pop();
					event_queue.push(new_event);
					CPU = true;
					continue;
				}
			}
			sequeue.push(event);
			PCB[event.get_ID()].clear();
			system_time += event.get_running_time();
			if ((system_time - event.get_running_time()) == delay_time) {
				waiting_time[event.get_ID()] = delay_time;
				turnaround_time[event.get_ID()] = event.get_running_time() + delay_time - event.get_arrival_time();
			}
			else {
				waiting_time[event.get_ID()] = system_time - event.get_running_time() - event.get_arrival_time();
				turnaround_time[event.get_ID()] = system_time - event.get_arrival_time();
			}
			cout << "finish " << event.get_Name() << "at time" << system_time << endl;
			if (!sjf_ready_queue.empty()) {
				Event current = sjf_ready_queue.top();
				current.update_time(system_time);
				PCB[current.get_ID()] = "running";
				event_queue.push(current);
				sjf_ready_queue.pop();

				while (!sjf_ready_queue.empty()) {
					Event temp = sjf_ready_queue.top();
					if (temp.get_time() >= system_time + current.get_running_time())
						break;
					temp.update_time(system_time + current.get_running_time());
					sjf_ready_queue.pop();
					sjf_ready_queue.push(temp);
				}
			}
			else
				CPU = false;
		}break;
		}
		}
	}

		cout << system_time << endl;
		string algorithm = "delay_SJF";
		calculate(waiting_time, turnaround_time, algorithm, list_event, sequeue);

}
