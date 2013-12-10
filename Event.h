#ifndef EVENT_H
#define EVENT_H
#include <stdlib.h>
#include <vector>
#include <queue>

using std::priority_queue;
using std::vector;

/**
A single event for a discrete event driven simulation.
*/
class Event 
	{
	public:
		Event(int t);
		
		/**
		Perform one event in the simulation.
		*/
		virtual void do_event() = 0;
		
	protected:
		friend class EventComparison;
		int time;
	};

/**
Compare two events based on their time.
*/
class EventComparison 
	{
	public:
		bool operator()(const Event* left, const Event* right) const;
	};

inline int rand_int(int a, int b)
{
	return a + rand() % (b - a + 1);
}

inline Event::Event(int t) : time(t) {}

inline bool EventComparison::operator()
	(const Event* left, const Event* right) const
	{
		return left->time > right->time;
	}

/**
Simulation framework for event driven simulation.
*/
class Simulation 
	{
	public:
		/**
		Add new event to simulation.
		@param new_event the event to add
		*/
		void schedule_event(Event* new_event);
		
		/**
		Run the simulation through all events.
		*/
		void run();
	private:
		priority_queue<Event*, vector<Event*>, EventComparison> event_queue;
	};

inline void Simulation::schedule_event(Event* new_event)
{ 
	event_queue.push(new_event); 
}

#endif

