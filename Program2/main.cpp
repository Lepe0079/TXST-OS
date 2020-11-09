#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

////////////////////////////////////////////////////////////////
// sample events
#define EVENT1 1
#define EVENT2 2
#define EVENT3 3

#define ARTYPE atoi(argv[1])
#define ARLAMBDA atof(argv[2])
#define ARBURST atof(argv[3])
#define ARQUANTUM atof(argv[4])
// .. add more events

////////////////////////////////////////////////////////////////     
//event structure
struct event{
  float burst;//burst
  float arrival;
  int   type;
  // add more fields
  struct event* next;
};

////////////////////////////////////////////////////////////////
// function definition
void init();
int run_sim();
void generate_report();
int addReady();
int schedule_event(struct event** node);
int scheduleFCFS();
int process_event1();
int process_event2(struct event* eve);
int process_event3(struct event* eve);
float genexp(float);

////////////////////////////////////////////////////////////////
//Global variables
struct event* head; // head of event queue
struct event* ready; //head of ready queue
struct event* garbage; //garbage collector
float sClock; // simulation Eclock
char **argv; //used to extract arguments from main and use them globally
int processed, processLimit;

//metrics

float start, finish, wait, totalWait;

////////////////////////////////////////////////////////////////
void init()
{
	// initialize all varilables, states, and end conditions
	processed = 0;
	processLimit = 100;

	for(int i = 0; i < processLimit; ++i)
	{	
		addReady();
	}
	scheduleFCFS();

	sClock = 0.0;
	start = 0.0;
	finish = 0.0;
	wait = 0.0;	
	totalWait = 0.0;
}
////////////////////////////////////////////////////////////////
void generate_report()
{
	// output statistics
	std::cout << "average turnaround: " << (totalWait/processed) << "\n";
	std::cout << "throughtput: " << (sClock/processed);
}


//add an event to the ready queue
int addReady()
{
	struct event* cursor = ready;
	struct event* backC;
	struct event* newProc = new event;

	newProc->type = ARTYPE;
	newProc->burst = genexp(1/ARBURST);
	newProc->arrival = genexp(ARLAMBDA);
	if(!ready)
	{
		ready = newProc;
		return 0;
	}
	if(cursor->arrival > newProc->arrival)
	{
		newProc->next = ready;
		ready = newProc;
	}
	else
	{
		while(cursor->next && cursor->next->arrival < newProc->arrival){
			cursor = cursor->next;
		}
		newProc->next = cursor->next;
		cursor->next = newProc;
	}
	return 0;
}
//////////////////////////////////////////////////////////////// 
//schedules an event in the future
int schedule_event(struct event** node)
{
	// insert event in the event queue in its order of burst
	return 0;
}

int scheduleFCFS()
{//remember ready queue is sorted by arrival time
	struct event* cursor;
	struct event* temp;

	if(!ready)//make sure there is something in the ready queue
	{
		addReady();
	}
	
	cursor = head;
	temp = ready;

	if(!head)//if there is nothing at the event queue add the ready object to the head
	{
		ready = ready->next;
		temp->next = NULL;
		head = temp;
		return 0;
	}
	else
	{//otherwise insert by arrival time
		if(cursor->arrival > temp->arrival)
		{//insert before head
			ready = ready->next;
			temp->next = cursor;
			head = temp;
		}
		else
		{//search for insert point
			while(cursor->next && (cursor->next->arrival < temp->arrival))
			{cursor = cursor->next;}
			
			ready = ready->next;
			temp->next = cursor->next;
			cursor->next = temp;
		}
	}
	return 0;
}
////////////////////////////////////////////////////////////////
// returns a random number between 0 and 1
float urand(){return( (float) rand()/RAND_MAX );}
/////////////////////////////////////////////////////////////
// returns a random number that follows an exp distribution
float genexp(float lambda)
{
	float u,x;
	x = 0;
	while (x == 0)
		{
			u = urand();
			x = (-1/lambda)*log(u);
		}
	return(x);
}
////////////////////////////////////////////////////////////
int run_sim()
{
	//scheduleFCFS();
	while (processed < processLimit)//run for 10k events
	{
		switch (ARTYPE)
		{
			case EVENT1:
				process_event1();//generate the next event
				break;
			case EVENT2:
				//process_event2();
				break;
			case EVENT3:
				break;

			// add more events

			default:
				break;	
			// error 
		}
		++processed;
	}
	return 0;
}

int process_event1(){	
	std::cout << processed+1 << ": " << head->burst << std::endl << head->arrival << std::endl;
	//gather metrics
	
	sClock += head->burst;

	if(head->arrival > finish)
	{
		wait = 0;
		finish = head->burst+head->arrival;
	}	
	else
	{
		wait = start - head->arrival;
		finish = start + head->burst;
	}
		
	start = finish;	
	totalWait += wait;

	//go to next event and schedule another
	garbage = head;	
	head = head->next;
	scheduleFCFS();
	delete garbage;
}

int process_event2(event* eve){
}
////////////////////////////////////////////////////////////////
int main(int argc, char *argv[] )
{
	// parse arguments
	::argv = argv;
	// Scheduling Type = argv[1]
	// Lambda = argv[2] processes per second
	// Burst = argv[3]
	// Quantum = argv[4]

	init();
	run_sim();
	generate_report();

	return 0;
}