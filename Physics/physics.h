#ifndef BANDCAMP_PHYSICS_H_
#define BANDCAMP_PHYSICS_H_

class Room
{
	public:
		void init_room();
		int give_oxygen();
		int give_temperature();
		void lower_oxygen();
		void raise_oxygen(int resource_value);
		void lower_temperature();
		void raise_temperature(int resource_value);
	private:
		int pressure, temperature;
}

#endif  //  BANDCAMP_PHYSICS_H_