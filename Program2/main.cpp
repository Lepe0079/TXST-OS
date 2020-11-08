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
int schedule_event(struct event** node);
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
	processLimit = 10;

	// schedule first events
	head = new event;
	head->burst = genexp(1/ARBURST);
	head->type = ARTYPE;
	head->arrival = 0;

	for(int i = 1; i < processLimit; ++i)
		schedule_event(&head);

	sClock = 0.0;
}
////////////////////////////////////////////////////////////////
void generate_report()
{
	// output statistics
}
//////////////////////////////////////////////////////////////// 
//schedules an event in the future
int schedule_event(struct event** node)
{
	// insert event in the event queue in its order of arrival
	struct event* cursor = (*node);
	struct event* backC;
	struct event* newProc = new event;

	newProc->type = ARTYPE;
	newProc->burst = genexp(1/ARBURST);
	newProc->arrival = genexp(ARLAMBDA);
	if(cursor->arrival > newProc->arrival)
	{
		newProc->next = (*node);
		(*node) = newProc;
	}
	else
	{
		while(cursor->next && cursor->next->arrival < newProc->arrival){
			cursor = cursor->next;
		}
		newProc->next = cursor->next;
		cursor->next = newProc;
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
	struct event* garbage;
	while (processed < processLimit)//run for 10k events
	{
		eve = head;
		sClock = eve->arrival;//increment the clock
		std::cout << "start" << std::endl;
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
		garbage = head;//set to the current node to be destroyed
		head = eve->next;

		delete garbage;//destroy the old data

		++processed;
	}
	std::cout << "clock: " << sClock;
	return 0;
}

int process_event1(event* eve){
	std::cout << processed+1 << ": " << eve->burst << std::endl;
	

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
