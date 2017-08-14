#include "Function.h"

int main() {
	srand(time(NULL));
	priority_queue<Event, vector<Event>, compare> event_queue;				// event queue to run the simulation 
	priority_queue<Event, vector<Event>, compare> event_queue_test;			// event queue to run the simulation
	priority_queue<Event, vector<Event>, compare_SJF> sjf_ready_queue;		// event queue to run the simulation
	unordered_map<int, string> PCB;			// record the process status
	deque<Event> ready_queue;				// record the ready queue
	bool CPU = false;						// CPU is free
	int count = 0;							// record the process ID
	double system_time = 0.0;				// system time
	double quantum = 5.0;					
	double lambda = 1.0;
	double alpha_1 = 1.0;
	double alpha_2 = 0.5;
	double alpha_3 = 1/3;
	queue<Event> sequeue;


	ini_JOB(event_queue_test);			// initial event queue
	priority_queue<Event, vector<Event>, compare> event_queue_test_1 = event_queue_test;
	priority_queue<Event, vector<Event>, compare> event_queue_test_2 = event_queue_test;
	priority_queue<Event, vector<Event>, compare> event_queue_test_3 = event_queue_test;
	priority_queue<Event, vector<Event>, compare> event_queue_test_4 = event_queue_test;




	/* simulation: FCFS methods */
	FCFS_Simulation(event_queue_test_1 ,PCB, count, CPU, ready_queue, system_time, lambda);
	PCB.clear();
	cout << endl;
	cout << endl;
	cout << endl;

	/* simulation: SJF  methods SJF with alpha = 1.0 */
	SJF_Simulation(event_queue_test_2, PCB, count, CPU, sjf_ready_queue, system_time, lambda, alpha_1, "SJF_alpha_=_1");   
	PCB.clear();
	cout << endl;
	cout << endl;
	cout << endl;

	/* simulation: SJF with alpha = 0.5 */
	SJF_Simulation(event_queue_test_3, PCB, count, CPU, sjf_ready_queue, system_time, lambda, alpha_2, "SJF_alpha_=_0_5");   
	PCB.clear();
	cout << endl;
	cout << endl;
	cout << endl;

	/* simulation: SJF with alpha = 1/3 */
	SJF_Simulation(event_queue_test_4, PCB, count, CPU, sjf_ready_queue, system_time, lambda, alpha_3, "SJF_alpha_=_0_3333"); 
	PCB.clear();
	
	/* simulation RR with diferent quantums */
	for (int i = 5; i < 70; i++) {
		ini_JOB(event_queue);
		quantum = i * 5.0;
		RR_Simulation(event_queue, PCB, count, CPU, ready_queue, system_time, quantum, lambda, "RR_quantum_=_"+itos(static_cast<int> (quantum)));
		cout << endl;
		cout << endl;
		PCB.clear();
	}







	return 0;
}