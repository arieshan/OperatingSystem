#include "Function.h"





int main() {

	unordered_map<int, string> PCB;   // record processes' status ( running, ready)
	deque<Event> ready_queue;   // recorde  the process which in the ready queue

	priority_queue<Event, vector<Event>, compare> event_queue_test_5_3_FCFS;  // test FCFS methods for 5.3
	priority_queue<Event, vector<Event>, compare> event_queue_test_5_3_SJF;   // test SJF methods for 5.3
	priority_queue<Event, vector<Event>, compare> event_queue_test_5_3_delay;  // test delay 1 seconds for 5.3

	priority_queue<Event, vector<Event>, compare> event_queue_test_5_12_1;    // test FCFS for 5.12
	priority_queue<Event, vector<Event>, compare> event_queue_test_5_12_2;	  // test SJF for 5.12
	priority_queue<Event, vector<Event>, compare> event_queue_test_5_12_3;	  // test Nonpreemptive Priority for 5.12
	priority_queue<Event, vector<Event>, compare> event_queue_test_5_12_4;	  // test RR for 5.12
	priority_queue<Event, vector<Event>, compare_SJF> sjf_ready_queue;			// ready queue for SJF, priority is burst time
	priority_queue<Event, vector<Event>, compare_Priority> priority_ready_queue;  // ready queue for Nonpreemptive Priority

	bool CPU = false;  // CPU is free
	int count = 0;     // processes order
	double system_time = 0.0;   
	double quantum = 1.0;
	double delay_time = 1.0;


	/* initial event queue for the simulation*/
	ini_Event_5_3(event_queue_test_5_3_FCFS);
	ini_Event_5_3(event_queue_test_5_3_SJF); 
	ini_Event_5_3(event_queue_test_5_3_delay);

	ini_Event_5_12(event_queue_test_5_12_1);
	ini_Event_5_12(event_queue_test_5_12_2);
	ini_Event_5_12(event_queue_test_5_12_3);
	ini_Event_5_12(event_queue_test_5_12_4);

	/* 5.3 */
	{
		FCFS(event_queue_test_5_3_FCFS, PCB, count, CPU, ready_queue, system_time);  // call FCFS methods
		PCB.clear();
		SJF(event_queue_test_5_3_SJF, PCB, count, CPU, sjf_ready_queue, system_time);  // call SJF methods
		PCB.clear();
	    SJF_Delay(event_queue_test_5_3_delay, PCB, count, CPU, sjf_ready_queue, system_time, delay_time);  // call SJF delay methods
		PCB.clear();
	}

	/* 5.12*/
	
	{
		FCFS(event_queue_test_5_12_1, PCB, count, CPU, ready_queue, system_time);  // call FCFS  methods
		PCB.clear();
		SJF(event_queue_test_5_12_2, PCB, count, CPU, sjf_ready_queue, system_time);  // call SJF methods
		PCB.clear();
		RR(event_queue_test_5_12_3, PCB, count, CPU, ready_queue, system_time, quantum);  // call SJF methods
		PCB.clear();
		Priority_Sche(event_queue_test_5_12_4, PCB, count, CPU, priority_ready_queue, system_time);  // call priority methods
		PCB.clear();
	}


	return 0;
}