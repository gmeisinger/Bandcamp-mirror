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


typedef std::chrono::high_resolution_clock myclock; // Create Timer
myclock::time_point beginning = myclock::now();     // Set beginning
myclock::duration d = myclock::now() - beginning;   // Take time span
unsigned seed2 = d.count();                         // Obtain a seed from the timer
std::mt19937 generator(seed2);                                 // Random number generator
std::uniform_int_distribution<int> uniform_dist(-3,3);   // Create Distribution
std::normal_distribution<float> norm_dist(0,2);   // Create Distribution

// Generates int with high probability of being -1,0, or 1, with lesser probabilies outside of that range
int utils::normDist() {
    return((int)norm_dist(generator));
}
// Generates int in [-3,3] range with equal probability
int utils::uniformDist() {
    return(uniform_dist(generator));
}
//std::cout << dice()+dice()+dice() << std::endl;
