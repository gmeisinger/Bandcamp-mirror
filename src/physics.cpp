#include "include/physics.h"

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

int Room2::give_pressure() {
	return pressure;
}

void Room2::raise_oxygen(int resource_value) {
	oxygen = std::min(oxygen+resource_value, 100);
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

void Room2::changePres(int target) {
	if (target <= 5) target = 0;
	else if (target >= 95) target = 100;
	if (pressure < target) {
		pressure++;
	} else if (pressure > target) {
		pressure--;
	}
}

void Room2::changeOxyExternal() {
	if (oxygen > 10) {
		oxygen = (8.314f * oxygen) / 10;	//Uses the ideal gas constant to decide percent of oxygen that escaped
	} else if (oxygen > 0) {
		oxygen--;
	}
}

void Room2::changeTempExternal(int oldPres) {
	if (pressure > 0) {
		pressure--;
		temperature = (temperature * pressure) / oldPres; //Based off P1/T1=P2/T2
		
	} else if (temperature > 0) {
		temperature--;
	}
}