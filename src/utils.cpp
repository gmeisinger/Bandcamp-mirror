/* Team Bandcamp
 * Class function: contains utility functions 
 * 
*/

#include "include/utils.h"

//loads image at specified path as a texture
//fname = relative path to image
SDL_Texture* utils::loadTexture(SDL_Renderer* renderer, std::string fname) {
    //the final texture
    SDL_Texture* newTexture = nullptr;
    //load the image
	SDL_Surface* startSurf = IMG_Load(fname.c_str());
	if (startSurf == nullptr) {
		std::cout << "Unable to load image " << fname << "! SDL Error: " << SDL_GetError() << std::endl;
		return nullptr;
	}
	//color key
	SDL_SetColorKey(startSurf, SDL_FALSE, SDL_MapRGB(startSurf->format, 0, 0xFF, 0xFF));
    //create texture from image
	newTexture = SDL_CreateTextureFromSurface(renderer, startSurf);
	if (newTexture == nullptr) {
		std::cout << "Unable to create texture!" << std::endl;
	}
    //free original surface
	SDL_FreeSurface(startSurf);

	return newTexture;
}

/*destroys a vector of textures
 */
void utils::destroyTextureVector(std::vector<SDL_Texture*> vect)
{
	for(auto i : vect)
	{
		SDL_DestroyTexture(i);
		i = nullptr;
	}
}

/* normDist_sd1:
 * Random number generator using Normal Distribution, Mean of 0, Standard Distribution 1
 * Generates number usually between [-3,3], most commonly 0
 */
//std::default_random_engine generator;
//std::random_device r;
std::mt19937 generator{};                                 // Random number generator
//generator.seed(std::random_device()());                 // Seed Generator
std::uniform_int_distribution<int> distribution(-3,3);   // Create Distribution

int utils::normDist_sd1() {
    return(distribution(generator));
}
//std::cout << dice()+dice()+dice() << std::endl;
