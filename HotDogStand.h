#include "event.h"
#include <iostream>

using namespace std;

/**
Tomamos un stand de hot dogs con una determinada cantidad de asientos
*/
class HotDogStand : public Simulation 
	{
	public:
		HotDogStand(int s);
		/**
		Prueba si el cliente se puede sentar 
		Regresa TRUE si es posible
		*/
		bool can_seat();
		
		/**
		El CLiente consume, y se retira
		*/
		void customer_leaves();
	private:
		int free_seats;
	};

HotDogStand::HotDogStand(int s) : free_seats(s) {}

bool HotDogStand::can_seat()
{
	if (free_seats > 0) 
	{
		free_seats--;
		return true;
	}
	else
		return false;
}

void HotDogStand::customer_leaves() 
{
	free_seats++;
}

HotDogStand freds(5);

/**
Evento de llegada del cliente
Bien el cliente se sienta o se va
*/
class ArriveEvent : public Event 
	{
	public:
		ArriveEvent(int t);
		virtual void do_event();
	};

/**
Simulacion de Eventos
Cliente satisfecho y se va
*/
class LeaveEvent : public Event 
	{
	public:
		LeaveEvent(int t);
		virtual void do_event();
	};

ArriveEvent::ArriveEvent(int t) : Event(t) {}

void ArriveEvent::do_event()
{
	/**
	La prioridad se da de acuerdo al tiempo
	*/
	if (freds.can_seat()) 
	{
		cout << "Tiempo " << time << " Cliente "<< " esta sentado\n";
		freds.schedule_event(new LeaveEvent(time + rand_int(1, 5)));
		
	}
	else
		cout << "Tiempo " << time 
		<< " Cliente no encuentra asiento, se va\n";
	
}

LeaveEvent::LeaveEvent(int t) : Event(t) {}

void LeaveEvent::do_event()
{
	cout << "Tiempo " << time << " Cliente termina de comer,y se va\n";
	freds.customer_leaves();
}

