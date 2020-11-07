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
  float time;//burst
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
int schedule_event(struct event* node);
int process_event1(struct event* eve);
int process_event2(struct event* eve);
int process_event3(struct event* eve);
float genexp(float);

////////////////////////////////////////////////////////////////
//Global variables
struct event* head; // head of event queue
float sClock; // simulation Eclock
char **argv; //used to extract arguments from main and use them globally
int processed, processLimit;

////////////////////////////////////////////////////////////////
void init()
{
	// initialize all varilables, states, and end conditions
	processed = 0;
	processLimit = 1;

	// schedule first events
	head = new event;
	head->time = genexp(1/ARBURST);
	head->type = ARTYPE;
	head->arrival = 0;

	sClock = 0.0;
}
////////////////////////////////////////////////////////////////
void generate_report()
{
	// output statistics
}
//////////////////////////////////////////////////////////////// 
//schedules an event in the future
int schedule_event(struct event* node)
{
	// insert event in the event queue in its order of time
	struct event* cursor = node;
	struct event* newProc = new event;

	newProc->type = ARTYPE;
	newProc->time = genexp(1/ARBURST);
	newProc->arrival = genexp(ARLAMBDA);
	switch (node->type)
	{
	case 1://FCFS, creates a list of processes sorted by arrival time
		if(cursor->time > newProc->time)
		{
			newProc->next = cursor;
			node = newProc;
		}
		else
		{
			if(cursor->next)
			{
				
			}
		}
		break;
	
	default:
		break;
	}
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
	struct event* eve;
	struct event* garbageE;
	while (processed < processLimit)//run for 10k events
	{
		eve = head;
		sClock = eve->time;//increment the clock
		switch (eve->type)
		{
			case EVENT1:
			process_event1(eve);//generate the next event
			break;
			case EVENT2:
			process_event2(eve);
			break;
			case EVENT3:
			break;

			// add more events

			default:
			break;	
			// error 
		}
		garbageE = head;
		head = eve->next;
		delete garbageE;
		++processed;
	}
	garbageE = nullptr;
	return 0;
}

int process_event1(event* eve){
	std::cout << "processing event";

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
