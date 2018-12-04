#include <iostream>
#include <string>
#include <time.h>

class Artifact_Descriptor {
	private:
		std::string get_first_descriptor();
		std::string get_second_descriptor();
	public:
		Artifact_Descriptor();
		std::string gen_item_description();
}