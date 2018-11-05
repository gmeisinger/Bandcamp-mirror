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