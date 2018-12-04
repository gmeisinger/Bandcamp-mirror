#include "include/physics.h"

//really important to note that this is a physic simulation, NOT real life. If we do REAL physics, whenever a breach is in a pressurized zone, 
//it rapidly depressurizes and equalizes. That's no fun because we'll instantly die. So we'll have to figure out how to make this interesting
//but still a physics simulation...

int previous_pressure;

void Room2::init_room() {
	oxygen = 100;
	temperature = 100;
	pressure = 100;
	previous_pressure = pressure;
	bool breached = false;
	num_breaches = 0;
}

void Room2::rand_room() {
	oxygen = (rand()%100)+25;
	if(oxygen>100)
		oxygen = 100;
	temperature = (rand()%100)+25;
	if(temperature>100)
		temperature = 100;
	pressure = 100;
	bool breached = false;
	num_breaches = 0;
	//std::cout << "Room was created with:" <<std::endl;
	//std::cout << "oxygen: " << oxygen <<std::endl;
	//std::cout << "temperature:" << temperature << std::endl;
	//std::cout << "pressure:" << pressure << std::endl;
}

void Room2::adv_init_room(int o, int t, int p, int o2, int t2, int p2) {
	oxygen = (o+o2)/2;
	temperature = (t+t2)/2;
	pressure = (p+p2)/2;
	previous_pressure = pressure;
	bool breached = false;
	num_breaches = 0;
}

int Room2::give_oxygen() {
	return oxygen;
}

int Room2::give_temperature() {
	return temperature;
}

void Room2::lower_pressure() {
	previous_pressure = pressure;
	if(breached) {
		//int i;
		for(int i=0; i<=num_breaches; i++)
			pressure-=5;
		if(pressure<=0)
			pressure = 0;
	}
}

void Room2::lower_oxygen() {
	oxygen-=5;
}

void Room2::adv_lower_oxygen() {
	//PV=nRT
	double P = (double)pressure;
	double V = 8.314472; 			//since we are assuming this can be whatever we want, which we'll set to match the gas constant R (for percentage values)
	double n; 						//what we are looking for
	double R = 8.314472; 			//this is the Ideal Gas Law's constant
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
	//std::cout << "oxygen level: " << oxygen << std::endl;
}

void Room2::raise_oxygen(int resource_value) {
	oxygen = std::min(oxygen+resource_value, 100);
}

void Room2::lower_temperature() {
	temperature-=5;
}

void Room2::adv_lower_temperature() {
	int k = temperature/previous_pressure;
	int temp = k*pressure;
	temperature = temp;
	//std::cout << "temperature level: " << temperature << std::endl;
}

void Room2::raise_temperature(int resource_value) {
	temperature = std::min(temperature+resource_value, 100);
}

void Room2::changeOxy(int target) {
	if (target <= 5) target = 0;
	else if (target >= 95) target = 100;
	if (oxygen < target) {
		oxygen++;
	} else if (oxygen > target) {
		oxygen--;
	}
}

void Room2::changeTemp(int target) {
	if (target <= 5) target = 0;
	else if (target >= 95) target = 100;
	if (temperature < target) {
		temperature++;
	} else if (temperature > target) {
		temperature--;
	}
}