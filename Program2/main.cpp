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
void init();
int run_sim();
void generate_report();
int schedule_event(struct event* node);
int process_event1(struct event* eve);
int process_event2(struct event* eve);
float genexp(float);

////////////////////////////////////////////////////////////////
//Global variables
struct event* head; // head of event queue
float Eclock; // simulation Eclock

////////////////////////////////////////////////////////////////
void init()
{
	// initialize all varilables, states, and end conditions
	// schedule first events

	head = new event;
	Eclock = 0.0;
	for(int i = 0; i < )

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
	int i = 0;
	while (i < 1)
	{
		eve = head;
		Eclock += eve->time;
		switch (eve->type)
		{
			case EVENT1:
			process_event1(eve);
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

		head = eve->next;
		//free(eve);
		//eve = nullptr;
		//delete eve;
		//eve = NULL;
		++i;
	}
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
	init();
	run_sim();
	generate_report();
	return 0;
}
