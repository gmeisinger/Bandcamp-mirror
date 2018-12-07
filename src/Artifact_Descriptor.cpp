#include "include/Artifact_Descriptor.h"
std::vector<std::string> historical_figures;

Artifact_Descriptor::Artifact_Descriptor() {
    std::vector<std::string> t_vec(10, "");
    historical_figures = t_vec;
    int i;
    for(i = 0; i < 10; i++) {
        historical_figures[i] = get_ruler();
    }
}

std::string Artifact_Descriptor::get_first_descriptor() {
    std::string s = "an item owned by " + historical_figures[rand() % 10] + ". ";
    return s;
}

std::string Artifact_Descriptor::get_name() {
    std::vector<std::string> syllables {
        "go", "slof", "rin", "pol", "tir", "melp", "zix", "nil",
        "grem", "drard", "darg", "oem", "oen", "quet", "woi", "ez",
        "rop", "trel", "yihl", "ull", "ip", "oer", "puz", "aurt",
        "seir", "duey", "flune", "gaio", "herz", "jyk", "klao", "leiz",
        "zrif", "xont", "ximm", "xiaa", "cret", "coel", "veot", "bim", "newl",
        "mrav", "jhoer", "bual", "xol", "ghel", "awr", "eia", "eri", "it", "imk"
    };
    int num_syllables = rand() % 5 + 1;
    std::string name = "";
    int i;
    for(i = 0; i < num_syllables; i++) {
        name += syllables[rand() % syllables.size()];
    }
    return name;
}
std::string Artifact_Descriptor::get_ruler() {
    std::string title;
    int r = rand() % 5;
    switch(r) {
        case 0 : title = "king ";
            break;
        case 1 : title = "queen ";
            break;
        case 2 : title = "tyrant ";
            break;
        case 3 : title = "master ";
            break;
        case 4 : title = "oozelord ";
            break;
        default : title = "king ";
    }
    std::string full_name = title + get_name();
    return full_name;
}


std::string Artifact_Descriptor::get_second_descriptor() {
    int r = rand() % 10;
    std::string s;
    switch(r) {
        case 0 : s = "it is a tawdry trinket.";
            break;
        case 1 : s = "it has little more than sentimental value.";
            break;
        case 2 : s = "it was somewhat common, but useful nonetheless.";
            break;
        case 3 : s = "it is uncommon, but not exceptionally so.";
            break;
        case 4 : s = "it is entirely unique, and more valuable for it.";
            break;
        case 5 : s = "it was considered an irreplaceable treasure by its owner.";
            break;
        case 6 : s = "it was widely thought of as a symbol of the ruler that owned it.";
            break;
        case 7 : s = "it is utterly priceless and spoken of in historical texts.";
            break;
        case 8 : s = "allies of the ruler that held this item revere it; their enemies revile it.";
            break;
        case 9 : s = "it's an ancient heirloom spoken of in hushed tones and referenced in old legends.";
            break;
        default : s = "it is a tawdry trinket.";
    }
    
    return s;
}

// Usage of this class is pretty simple; initialize an Artifact_Descriptor and call gen_item_description() to get a string containing
// the two-part description. 
std::string Artifact_Descriptor::gen_item_description() {
    std::string s = get_first_descriptor() + get_second_descriptor();
    return s;
}
