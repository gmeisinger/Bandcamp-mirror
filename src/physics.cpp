#include "include/physics.h"

void Room::init_room()
{
	//initialize room values based of procgen
	//we'll use "percent" values (0-100) to keep things simple
	int oxygen = 100;
	int temperature = 100;
}

int Room::give_oxygen()
{
	return oxygen;
}

int Room::give_temperature()
{
	return temperature;
}

void Room::lower_oxygen()
{
	//lowers oxygen by a set amount, for now 5?
	oxygen-=5;
}

void Room::raise_oxygen(int resource_value)
{
	//raises oxygen by the value of the resource that was picked up (set by procgen team)
	oxygen+=resource_value;
}

void Room::lower_temperature()
{
	//lowers temperature by a set amount, for now 5?
	temperature-=5;
}

void Room::raise_temperature(int resource_value)
{
	//raises temperature by the value of the resource that was picked up (set by procgen team)
	temperature+=resource_value;
}