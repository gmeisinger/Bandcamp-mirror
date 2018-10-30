#ifndef BANDCAMP_PHYSICS_H_
#define BANDCAMP_PHYSICS_H_

class Room
{
	public:
		void init_room();
		void adv_init_room(int o, int t, int p);
		int give_oxygen();
		int give_temperature();
		void lower_pressure(int num_of_breaches);
		void lower_oxygen();
		void adv_lower_oxygen();
		void raise_oxygen(int resource_value);
		void lower_temperature();
		void adv_lower_temperature;
		void raise_temperature(int resource_value);
	private:
		int oxygen, temperature, pressure;
};

#endif  //  BANDCAMP_PHYSICS_H_