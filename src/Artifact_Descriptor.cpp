#include 'include/Artifact_Descriptor.h'

Artifact_Descriptor::Artifact_Descriptor() {
	
}

std::string Artifact_Descriptor::get_first_descriptor() {
	std::string s = "An item owned by an unknown ruler. ";
	return s;
}

std::string Artifact_Descriptor::get_second_descriptor() {
	int r = rand() % 10;
	std::string s;
	switch(r) {
		case 0 : s = "It is a tawdry trinket.";
			break;
		case 1 : s = "It has little more than sentimental value.";
			break;
		case 2 : s = "It was somewhat common, but useful nonetheless.";
			break;
		case 3 : s = "It is uncommon, but not exceptionally so.";
			break;
		case 4 : s = "It is entirely unique, and more valuable for it.";
			break;
		case 5 : s = "It was considered an irreplaceable treasure by its owner.";
			break;
		case 6 : s = "It was widely thought of as a symbol of the ruler that owned it.";
			break;
		case 7 : s = "It is utterly priceless and spoken of in historical texts.";
			break;
		case 8 : s = "Allies of the ruler that held this item revere it; their enemies revile it.";
			break;
		case 9 : s = "It's an ancient heirloom spoken of in hushed tones and referenced in old legends.";
			break;
		default : s = "It is a tawdry trinket.";
	}
	
	return s;
}

// Usage of this class is pretty simple; create an artifact descriptor and call gen_item_description() to get a string containing
// the two-part description.
std::string Artifact_Descriptor::gen_item_description() {
	std::string s = get_first_descriptor() + get_second_descriptor();
	return s;
}