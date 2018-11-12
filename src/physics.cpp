#include "include/physics.h"

//really important to note that this is a physic simulation, NOT real life. If we do REAL physics, whenever a breach is in a pressurized zone, 
//it rapidly depressurizes and equalizes. That's no fun because we'll instantly die. So we'll have to figure out how to make this interesting
//but still a physics simulation...

int previous_pressure;

void Room2::init_room() //this will always be used for the first room
{
	//we'll use "percent" values (0-100) to keep things simple
	oxygen = 100;
	temperature = 100;
	pressure = 100;
	previous_pressure = pressure;
}

void Room2::adv_init_room(int o, int t, int p) 	//this will be implemented when multiple rooms are created, taking into account the other room's values
{
	oxygen = (o+100)/2;						//for now, takes the previous room's values and this one ("100") and averages them
	temperature = (t+100)/2;
	pressure = (p+100)/2;
	previous_pressure = pressure;
}

int Room2::give_oxygen()
{
	return oxygen;
}

int Room2::give_temperature()
{
	return temperature;
}

void Room2::lower_pressure(int num_of_breaches) //depending on how many breaches in the room
{
	previous_pressure = pressure;
	switch(num_of_breaches)				//lets try to figure out a better way for this, but for now this is what we have
	{
		case(0):
			pressure = 100;
			break;
		case(1):
			pressure = 95;
			break;
		case(2):
			pressure = 90;
			break;
		case(3):
			pressure = 80;
			break;
		case(4):
			pressure = 60;
			break;
		case(5):
			pressure = 20;
			break;
		case(6):
			pressure = 0;
			break;
	}
}

void Room2::lower_oxygen()
{
	//lowers oxygen by a set amount, for now 5?
	oxygen-=5;
}

void Room2::adv_lower_oxygen() //something porportional with pressure
{
	//to be determined
}

void Room2::raise_oxygen(int resource_value)
{
	//raises oxygen by the value of the resource that was picked up (set by procgen team)
	oxygen+=resource_value;
}

void Room2::lower_temperature()
{
	//lowers temperature by a set amount, for now 5?
	temperature-=5;
}

void Room2::adv_lower_temperature() //k=T1/P1 T2=k*P2
{
	int k = temperature/previous_pressure;
	int temp = k*pressure;
	temperature = temp;
}

void Room2::raise_temperature(int resource_value)
{
	//raises temperature by the value of the resource that was picked up (set by procgen team)
	temperature+=resource_value;
}