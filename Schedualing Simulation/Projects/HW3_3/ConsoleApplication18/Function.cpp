#include "Function.h"

/* generate random burst time*/
double randomUniform(double dMinValue, double dMaxValue)
{
	double pRandomValue = (double)(rand() / (double)RAND_MAX);
	pRandomValue = pRandomValue*(dMaxValue - dMinValue) + dMinValue;
	return pRandomValue;
}
/* convert integer to  string */
string itos(int i){ 
	stringstream s;
	s << i;
	return s.str();
}
/* initial JOBS*/
void ini_JOB(priority_queue<Event, vector<Event>, compare> &event_queue) {
	for (int i = 0; i < 10; i++) {
		double burst_time = randomUniform(120*1000, 240*1000);
		string name = "JOB " + itos(i+1);
		Event new_event(1, -10 + i, 0.0, burst_time, name);
		event_queue.push(new_event);
		//cout << burst_time << endl;
	}
}

/* generate random number with specific JOB*/
double randomGenerate(double lambda, string name) {
	
	if (name == "JOB 1") {
		return  30.0 * randomExponential(lambda);
	}

	if (name == "JOB 2") {
		return  35.0 * randomExponential(lambda);
	}

	if (name == "JOB 3") {
		return  40.0 * randomExponential(lambda);
	}

	if (name == "JOB 4") {
		return  45.0 * randomExponential(lambda);
	}

	if (name == "JOB 5") {
		return  50.0 * randomExponential(lambda);
	}

	if (name == "JOB 6") {
		return  55.0 * randomExponential(lambda);
	}
	if (name == "JOB 7") {
		return  60.0 * randomExponential(lambda);
	}
	if (name == "JOB 8") {
		return  65.0 * randomExponential(lambda);
	}
	if (name == "JOB 9") {
		return  70.0 * randomExponential(lambda);
	}
	if (name == "JOB 10") {
		return  75.0 * randomExponential(lambda);
	}
	return 0;
}
/* generat a random number with means equals lambda*/
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
/* calculate the average waiting time and ohter attributes */
void calculate(unordered_map<int, double> &waiting_time, unordered_map<int, double> &turnaround_time, string &algorithm,
	unordered_map<int, Event> &list_event, queue<pair<Event, double> > &sequeue, int count_switch, double total_time, double quantum) {
	double sum_waiting_time = 0.0;
	double sum_turnaround_time = 0.0;
	double average_waiting_time = 0.0;
	double average_turnaround_time = 0.0;
	double delay_time = 1.0;
	double switch_time = 60.0;
	ofstream fileout,fileout2, fileout3, fileout4;
	string file = algorithm + ".txt";
	string file2 = "log.txt";
	fileout.open(file);
	fileout2.open(file2, ios::app);
	fileout3.open("Waitingtime_Observe.txt", ios::app);
	fileout4.open("CPU_Observe.txt", ios::app);
	double max_time = 0.0;
	for (auto x : waiting_time)
		sum_waiting_time += x.second;

	for (auto x : turnaround_time) {
		sum_turnaround_time += x.second;
		if (x.second > max_time)
			max_time = x.second;
	}
	double minutes = 60 * 1000;

	cout << "Simulation \t" << algorithm << endl;
	cout << "Simulation time is \t" << max_time / minutes << "\t minutes "<< endl;
	cout << "The Average waiting time of \t" << algorithm << "\t is " << ((sum_turnaround_time - total_time) / waiting_time.size()) / minutes  << "\t minutes"  << endl;
	cout << "The Average turnaround time of \t" << algorithm << "\t is " << (sum_turnaround_time / turnaround_time.size()) / minutes << "\t minutes" << endl;
	cout << "The Average CPU utilization of \t" << algorithm << "\t is " << (total_time)/(max_time) << endl;
	cout << "Throughput rate is \t" << (10 / max_time) * 1000 * 60 * 60 << "/hour" << endl;

	fileout2 << "Simulation \t" << algorithm << endl;
	fileout2 << "Simulation time is \t" << max_time / minutes << "\t minutes" << endl;
	fileout2 << "The Average waiting time of \t" << algorithm << "\t is " << ((sum_turnaround_time - total_time) / waiting_time.size()) / minutes << "\t minutes" << endl;
	fileout2 << "The Average turnaround time of \t" << algorithm << "\t is " << (sum_turnaround_time / turnaround_time.size()) / minutes << "\t minutes" << endl;
	fileout2 << "The Average CPU utilization of \t" << algorithm << "\t is " << (total_time) / (max_time) << endl;
	fileout2 << "Throughput rate is \t" << (10 / max_time) * 1000 * 60 * 60 << "/hour" << endl;
	/*  this part is to generate the Gantt charts 
	double time = 0.0;
	while (!sequeue.empty()) {
		Event current = sequeue.front().first;
		double time_length = sequeue.front().second;
		time += time_length;
		fileout << " | " << current.get_Name();
		for (double i = 0; i < time_length; i = i + 1)
			fileout << "_";
		fileout << time;
		sequeue.pop();
	}
	fileout << " |" << endl;
	fileout << endl;*/
	fileout.close();
	fileout2.close();

	if (quantum != 0.0) {
		fileout3 << quantum << " " << ((sum_turnaround_time - total_time) / waiting_time.size()) / minutes <<endl;
		fileout4 << quantum << " " << ((total_time) / (max_time)) * 100 <<endl;
	}
	fileout3.close();
	fileout4.close();
}

/* simulation for FCFS methods*/
void FCFS_Simulation(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, deque<Event> &ready_queue, double system_time, double lambda) {

	unordered_map<int, double>  waiting_time;
	unordered_map<int, double> turnaround_time;
	unordered_map<int, Event> list_event;
	queue<pair<Event, double> > sequeue;
	int count_switch = 0;
	double total_time = 0.0;

	while (!event_queue.empty()) {
		Event current = event_queue.top();
		event_queue.pop();

		switch (current.get_type()) {
		case 1:
		{// initial
			if (PCB.find(current.get_ID()) == PCB.end()) {
				++count;
				current.update_ID(count);
				PCB[current.get_ID()] = "";
				cout << "create PCB " << count << "successfully" << endl;
				waiting_time.insert({ current.get_ID(), 0.0 });
				turnaround_time.insert({ current.get_ID(), 0.0 });
				list_event.insert({ current.get_ID(), current });
				total_time += current.get_runTime();
			}

			if (!CPU) {
				CPU = true;
				PCB[current.get_ID()] = "running";
				current.update_type(2);
				event_queue.push(current);
			}
			else {
				PCB[current.get_ID()] = "ready";
				ready_queue.push_back(current);
				cout << "push event " << current.get_Name() << " into ready queue" << endl;
			}
		}break;

		case 2:
		{//ready_queue
			PCB[current.get_ID()] = "running";
			double temp =  randomGenerate(lambda, current.get_Name());
			double temp_time = system_time + temp;

			if (system_time == 0) {
				waiting_time[current.get_ID()] += 0;
			}
			else {
				waiting_time[current.get_ID()] += (system_time - current.get_sysTime() + 60 );
			}

			if (current.get_remainTime() <= temp) {
				current.update_type(4);
				event_queue.push(current);
			}
			else {
				system_time = temp_time ;
				sequeue.push({ current, temp });
				current.update_sysTime(system_time);
				current.update_remainTime(current.get_remainTime() - temp);
				current.update_type(3);
				event_queue.push(current);
				if (!ready_queue.empty()) {
					Event new_event = ready_queue.front();
					ready_queue.pop_front();
					new_event.update_type(2);
					event_queue.push(new_event);
				}
			}


		}break;

		case 3:
		{//I/O queue
			count_switch++;
			PCB[current.get_ID()] = "I/O interrupt";
			current.update_sysTime(current.get_sysTime() + 60);
			current.update_type(2);
			ready_queue.push_back(current);

			if (event_queue.empty()) {
				Event new_event = ready_queue.front();
				new_event.update_type(2);
				ready_queue.pop_front();
				PCB[new_event.get_ID()] = "running";
				event_queue.push(new_event);
				system_time += 60;
			}

		}break;

		case 4:
		{//completion
			sequeue.push({ current, current.get_remainTime() });
			
			waiting_time[current.get_ID()] -= current.get_arrTime();
			PCB[current.get_ID()].clear();
			system_time += current.get_remainTime();
			turnaround_time[current.get_ID()] = system_time - current.get_arrTime();
			cout << "finish " << current.get_Name() << "at time" << system_time << endl;
			if (event_queue.empty()) {
				if (ready_queue.empty()) {
					CPU = false;
				}
				else {
						Event new_event = ready_queue.front();
						new_event.update_type(2);
						ready_queue.pop_front();
						PCB[new_event.get_ID()] = "running";
						event_queue.push(new_event);
				}
			}
		}break;
		}
	}
	string algorithm = "FCFS";
	calculate(waiting_time, turnaround_time, algorithm, list_event, sequeue, count_switch, total_time, 0.0);
}

/* simulation for SJF methods */
void SJF_Simulation(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, priority_queue<Event, vector<Event>, compare_SJF> &sjf_ready_queue, double system_time, double lambda, double alpha, string algorithm) {

	unordered_map<int, double>  waiting_time;
	unordered_map<int, double> turnaround_time;
	unordered_map<int, Event> list_event;
	queue<pair<Event, double> > sequeue;
	unordered_map<int, double> update_time_delta;
	double last_time = 0.0;
	Event last_event;
	int count_switch = 0;
	double total_time = 0.0;

	while (!event_queue.empty()) {
		Event current = event_queue.top();
		event_queue.pop();

		switch (current.get_type()) {
		case 1:
		{// initial
			if (PCB.find(current.get_ID()) == PCB.end()) {
				++count;
				current.update_ID(count);
				PCB[current.get_ID()] = "";
				cout << "create PCB " << count << "successfully" << endl;
				waiting_time.insert({ current.get_ID(), 0.0 });
				turnaround_time.insert({ current.get_ID(), 0.0 });
				update_time_delta.insert({ current.get_ID(), 0.0 });
				list_event.insert({ current.get_ID(), current });
				total_time += current.get_runTime();
			}

			if (!CPU) {
				CPU = true;
				PCB[current.get_ID()] = "running";
				current.update_type(2);
				event_queue.push(current);
				last_event = current;
			}
			else {
				PCB[current.get_ID()] = "ready";
				double temp = (last_event.get_arrTime() - 0.0) * alpha + (1 - alpha) * last_event.get_predictTime();
				current.update_predictTime(temp);
				last_event = current;
				sjf_ready_queue.push(current);
				cout << "push event " << current.get_Name() << " into ready queue" << endl;
			}
		}break;

		case 2:
		{//ready_queue
		 // system_time = system_time + (0.2) * randomExponential(1.0) * 60;
			PCB[current.get_ID()] = "running";
			double temp = randomGenerate(lambda, current.get_Name());
			double temp_time = system_time + temp;

			last_time = temp;

			if ((system_time) == 0) {
				waiting_time[current.get_ID()] += 0;
			}
			else {
				double last_execute_time = update_time_delta[current.get_ID()];
				waiting_time[current.get_ID()] += (system_time - last_execute_time );
			}

			if (current.get_remainTime() <= temp) {
				current.update_type(4);
				event_queue.push(current);
			}
			else {
				system_time = temp_time;
				sequeue.push({ current, temp });
				current.update_sysTime(temp_time);
				current.update_remainTime(current.get_remainTime() - temp);
				current.update_type(3);
				event_queue.push(current);
				update_time_delta[current.get_ID()] = system_time ;
				if (!sjf_ready_queue.empty()) {
					Event new_event = sjf_ready_queue.top();
					sjf_ready_queue.pop();
					new_event.update_sysTime(system_time);
					new_event.update_type(2);
					event_queue.push(new_event);

					while (!sjf_ready_queue.empty()) {
						Event temp = sjf_ready_queue.top();
						if (temp.get_sysTime() >= system_time)
							break;

						temp.update_sysTime(system_time);
						sjf_ready_queue.pop();
						sjf_ready_queue.push(temp);
					}
				}
			}


		}break;

		case 3:
		{//I/O queue
			count_switch++;
			PCB[current.get_ID()] = "I/O interrupt";
			current.update_sysTime(current.get_sysTime() + 60);
			current.update_type(2);
			PCB[current.get_ID()] = "ready";
			double temp = last_time * alpha + (1 - alpha) * last_event.get_predictTime();
			current.update_predictTime(temp);
			last_event = current;
			sjf_ready_queue.push(current);

			if (event_queue.empty())
			{
				Event new_event = sjf_ready_queue.top();
				sjf_ready_queue.pop();
				PCB[new_event.get_ID()] = "running";
				new_event.update_type(2);
				event_queue.push(new_event);
				system_time += 60;
				while (!sjf_ready_queue.empty()) {
					Event temp = sjf_ready_queue.top();
					if (temp.get_sysTime() >= system_time +  new_event.get_predictTime())
						break;
					temp.update_sysTime(system_time +  new_event.get_predictTime());
					sjf_ready_queue.pop();
					sjf_ready_queue.push(temp);
				}
			}



		}break;

		case 4:
		{//completion
			sequeue.push({ current, current.get_remainTime() });
			
			waiting_time[current.get_ID()] -= current.get_arrTime();
			PCB[current.get_ID()].clear();
			system_time += current.get_remainTime();
			turnaround_time[current.get_ID()] = system_time - current.get_arrTime();
			cout << "finish " << current.get_Name() << "at time" << system_time << endl;
			if (event_queue.empty()) {
				if (sjf_ready_queue.empty()) {
					CPU = false;
				}
				else {
					Event new_event = sjf_ready_queue.top();
					new_event.update_type(2);
					sjf_ready_queue.pop();
					PCB[new_event.get_ID()] = "running";
					event_queue.push(new_event);

					while (!sjf_ready_queue.empty()) {
						Event temp = sjf_ready_queue.top();
						if (temp.get_sysTime() >= system_time + 0.5 * new_event.get_predictTime())
							break;
						temp.update_sysTime(system_time + 0.5 * new_event.get_predictTime());
						sjf_ready_queue.pop();
						sjf_ready_queue.push(temp);
					}
				}
			}
		}break;
		}
	}
	calculate(waiting_time, turnaround_time, algorithm, list_event, sequeue, count_switch, total_time, 0.0);
}

/* simulation for RR simulaitons */
void RR_Simulation(priority_queue<Event, vector<Event>, compare> &event_queue, unordered_map<int, string> &PCB, int count,
	bool &CPU, deque<Event> &ready_queue, double system_time, double &quantum, double lambda, string algorithm) {
	unordered_map<int, double>  waiting_time;
	unordered_map<int, double> turnaround_time;
	unordered_map<int, Event> list_event;
	queue<pair<Event, double> > sequeue;
	double last_time = 0.0;
	Event last_event;
	int count_switch = 0;
	double total_time = 0.0;
	string file = "log_" + itos(static_cast<int>(quantum)) + ".txt";
	ofstream fileout(file);
	
	while (!event_queue.empty()) {
		Event current = event_queue.top();
		event_queue.pop();
		switch (current.get_type()) {
		case 1:
		{// initial
			if (PCB.find(current.get_ID()) == PCB.end()) {
				++count;
				current.update_ID(count);
				PCB[current.get_ID()] = "";
				fileout << "create PCB \t\t" << count << "\t\t  for \t\t"<< current.get_Name() <<"\t\t successfully at time \t" << current.get_sysTime() <<"\t ms" << endl;
				waiting_time.insert({ current.get_ID(), 0.0 });
				turnaround_time.insert({ current.get_ID(), 0.0 });
				list_event.insert({ current.get_ID(), current });
				total_time += current.get_runTime();
			}

			if (!CPU) {
				CPU = true;
				PCB[current.get_ID()] = "running";
				current.update_type(2);
				event_queue.push(current);
				fileout << current.get_Name() << "\t\t is running at CPU at time \t\t"<< current.get_sysTime() << "\t ms" << endl;
			}
			else {
				PCB[current.get_ID()] = "ready";
				ready_queue.push_back(current);
				fileout << "push event \t\t" << current.get_Name() << "\t\t into ready queue at time \t\t"<< current.get_sysTime() << "\t ms" << endl;

			}
		}break;
		case 2:
		{ // ready queue
			PCB[current.get_ID()] = "running";
			double temp = randomGenerate(1.0, current.get_Name());
			double temp_time = 0.0;
			last_time = temp;

			if ((system_time) == 0) {
				waiting_time[current.get_ID()] += 0;
			}
			else {
				waiting_time[current.get_ID()] += (system_time - current.get_sysTime() + 60);
			}

			double min_time = min(temp, quantum);
			temp_time = system_time + min_time;
			if (current.get_remainTime() <= min_time) {
				current.update_type(4);
				event_queue.push(current);
			}
			else {
				system_time = temp_time;
				sequeue.push({ current, min_time });
				current.update_sysTime(system_time);
				current.update_remainTime(current.get_remainTime() - min_time);
				current.update_type(3);
				fileout << current.get_Name() << "\t\t is leaving CPU and entering IO queue at time "<< current.get_sysTime() << "\t ms" << endl;
				event_queue.push(current);
				if (!ready_queue.empty()) {
					Event new_event = ready_queue.front();
					ready_queue.pop_front();
					new_event.update_type(2);
					event_queue.push(new_event);
					fileout << current.get_Name() << "\t\t is running at CPU at time "<< current.get_sysTime() << "\t ms" << endl;
				}
			}
		}break;
		case 3: 
		{// I/O queue
			count_switch++;
			PCB[current.get_ID()] = "I/O interrupt";
			current.update_sysTime(current.get_sysTime() + 60);
			current.update_type(2);
			ready_queue.push_back(current);
			fileout << current.get_Name() <<"\t\t leaves from IO at time \t\t" << current.get_sysTime() << "\t ms" << endl;
			if (event_queue.empty()) {
				Event new_event = ready_queue.front();
				new_event.update_type(2);
				ready_queue.pop_front();
				PCB[new_event.get_ID()] = "running";
				event_queue.push(new_event);
				system_time += 60;
				fileout << current.get_Name() << "\t\t is running at CPU at time \t\t"<< current.get_sysTime() << "\t ms" << endl;
			}
		}break;
		case 4:
		{// completion

			sequeue.push({ current, current.get_remainTime() });

			waiting_time[current.get_ID()] -= current.get_arrTime();
			PCB[current.get_ID()].clear();
			system_time += current.get_remainTime();
			turnaround_time[current.get_ID()] = system_time - current.get_arrTime();
			fileout << current.get_Name() << "\t\t finished at CPU at time \t\t"<< system_time << "\t ms" << endl;
			if (event_queue.empty()) {
				if (ready_queue.empty() && event_queue.empty()) {
					CPU = false;
					fileout << "all job is done at time \t"<< system_time << endl;
				}
				else {
					Event new_event = ready_queue.front();
					new_event.update_type(2);
					ready_queue.pop_front();
					PCB[new_event.get_ID()] = "running";
					event_queue.push(new_event);
					fileout << current.get_Name() << "\t\t is running at CPU at time \t\t" << system_time << "\t ms" << endl;
				}
			}
		}break;
		}
	}
	fileout.close();
	calculate(waiting_time, turnaround_time, algorithm, list_event, sequeue, count_switch, total_time, quantum);
}