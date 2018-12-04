#ifndef BANDCAMP_PHYSICS_H_
#define BANDCAMP_PHYSICS_H_

#include <algorithm>

#include "utils.h"

class Room2
{
	public:
		void init_room();
		void rand_room();
		void adv_init_room(int o, int t, int p, int o2, int t2, int p2);
		int give_oxygen();
		int give_temperature();
		void lower_pressure();
		void lower_pressure(int num_of_breaches);
		void lower_oxygen();
		void adv_lower_oxygen();
		void raise_oxygen(int resource_value);
		void lower_temperature();
		void adv_lower_temperature();
		void raise_temperature(int resource_value);
		void changeOxy(int target);
		void changeTemp(int target);
	private:
		int oxygen, temperature, pressure, num_breaches;
		bool breached;
};

#endif  //  BANDCAMP_PHYSICS_H_ 