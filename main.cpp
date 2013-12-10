#include "HotDogStand.h"

#include "event.h"

using namespace std;

void Simulation::run()
{
	while(!event_queue.empty()) 
	{
		Event* next_event = event_queue.top();
		event_queue.pop();
		next_event->do_event();
		delete next_event;
	}
}

int main()
{
	for (int i = 0; i < 50; i++)
		freds.schedule_event(new ArriveEvent(rand_int(1, 20)));
	freds.run();
	return 0;
}
