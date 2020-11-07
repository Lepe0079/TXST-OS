#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

////////////////////////////////////////////////////////////////
// sample events
#define EVENT1 1
#define EVENT2 2
#define EVENT3 3
// .. add more events

////////////////////////////////////////////////////////////////     
//event structure
struct event{
  float time;//burst
  int   type;
  // add more fields
  struct event* next;
};

////////////////////////////////////////////////////////////////
// function definition
void init(int);
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

////////////////////////////////////////////////////////////////
void init(int eType)
{
	// initialize all varilables, states, and end conditions
	// schedule first events

	head = new event;
	head->time = genexp(1/.06);
	head->type = eType;
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
	int i = 0;
	while (i < 5)//run for 10k events
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
		++i;
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
	int scheduling = atoi(argv[1]);
	int lambdaVal = atoi(argv[2]);//processes per second
	float avBurst = atof(argv[3]);
	float quantum = atof(argv[4]);

	init(scheduling);
	run_sim();
	generate_report();
	return 0;
}
