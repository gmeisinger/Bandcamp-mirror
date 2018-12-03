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
	bool breached = false;
	num_breaches = 0;
}

void Room2::rand_room() //this will be every room but the first, creating random values between 100 and 25(?) for each attribute
{
	oxygen = (rand()%100)+25; //this will go from a range of 25 to 125
	if(oxygen>100)
		oxygen = 100;
	temperature = (rand()%100)+25;
	if(temperature>100)
		temperature = 100;
	pressure = (rand()%100)+25;
	if(pressure>100)
		pressure = 100;
	bool breached = false;
	num_breaches = 0;
	std::cout << "Room was created with:" <<std::endl;
	std::cout << "oxygen: " << oxygen <<std::endl;
	std::cout << "temperature:" << temperature << std::endl;
	std::cout << "pressure:" << pressure << std::endl;
}

void Room2::adv_init_room(int o, int t, int p, int o2, int t2, int p2) 	//this will need to be "randomized"
/* Summary
 * Argument  
 *
*/
{
	oxygen = (o+o2)/2;						//for now, takes the previous room's values and this one ("100") and averages them
	temperature = (t+t2)/2;
	pressure = (p+p2)/2;
	previous_pressure = pressure;
	bool breached = false;
	num_breaches = 0;
}

int Room2::give_oxygen()
{
	return oxygen;
}

int Room2::give_temperature()
// get temp value 
{
	return temperature;
}

void Room2::lower_pressure() //depending on how many breaches in the room
/* Summary
 * Argument  
 *
*/
{
	previous_pressure = pressure;
	// switch(num_of_breaches)				//lets try to figure out a better way for this, but for now this is what we have
	// {
		// case(0):
			// pressure = 100;
			// break;
		// case(1):
			// pressure = 95;
			// break;
		// case(2):
			// pressure = 90;
			// break;
		// case(3):
			// pressure = 80;
			// break;
		// case(4):
			// pressure = 60;
			// break;
		// case(5):
			// pressure = 20;
			// break;
		// case(6):
			// pressure = 0;
			// break;
	// }
	if(breached)
	{
		int i;
		for(i=0; i<=num_breaches, i++)
			pressure-=5;
		if(pressure<=0)
			pressure = 0;
	}
}

void Room2::lower_oxygen()
/* Summary
 * Argument  
 *
*/
{
	//lowers oxygen by a set amount, for now 5?
	oxygen-=5;
}

void Room2::adv_lower_oxygen() //something porportional with pressure
/* Summary
 * Argument  
 *
*/
{
	//PV=nRT
	double P = (double)pressure;
	double V = 8.314472; 			//since we are assuming this can be whatever we want, which we'll set to match the gas constant R (for percentage values)
	double n; 						//what we are looking for
	double R = 8.314472 			//this is the Ideal Gas Law's constant
	double T = (double)temperature;
	
	//rearranging formula to n = (PV)/(RT)
	n = (P*V)/(R*T);
	
	//now that we have moles, we need to translate it to a percentage value
	if(n>=1)
	{
		oxygen = 100;
	}
	else
	{
		oxygen = 100*(int)n;
	}
	std::cout << "oxygen level: " << oxygen << std::endl;
}

void Room2::raise_oxygen(int resource_value)
/* Summary
 * Argument  
 *
*/
{
	//raises oxygen by the value of the resource that was picked up (set by procgen team)
	oxygen+=resource_value;
}

void Room2::lower_temperature()
//
{
	//lowers temperature by a set amount, for now 5?
	temperature-=5;
}

void Room2::adv_lower_temperature() //k=T1/P1 T2=k*P2
// 
{
	int k = temperature/previous_pressure;
	int temp = k*pressure;
	temperature = temp;
	std::cout << "temperature level: " << temperature << std::endl;
}

void Room2::raise_temperature(int resource_value)
{
	//raises temperature by the value of the resource that was picked up (set by procgen team)
	temperature+=resource_value;
}

void Breach::set_type(int type, Room2 room)
{
	room.breached = true;
	if(type == 1)
	{
		isInterior = true;
	}
	if(type == 2)
	{
		isExterior = true;
	}
}

void Breach::check_type()
{
	//need to figure out how this is being stored
	//pretty much will check for adjacent rooms then call Breach::set_type whatever is calculated
}

int Breach::return_type()
{
	if(isInterior)
	{
		return 1;
	}
	if(isExterior)
	{
		return 2;
	}
}

void Breach::seal_breach()
{
	num_breaches-=1;
	if(num_breaches==0)
	{
		breached = false;
	}
}