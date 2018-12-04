#include <iostream>
#include <string>
#include <time.h>
#include <vector>

class Artifact_Descriptor {
	private:
		std::string get_name();
		std::string get_ruler();
		std::vector<std::string> historical_figures;
		std::string get_first_descriptor();
		std::string get_second_descriptor();
	public:
		Artifact_Descriptor();
		std::string gen_item_description();
};