#ifndef BANDCAMP_ARTIFACT_H_
#define BANDCAMP_ARTIFACT_H_

#include <SDL.h>
#include <string>

class Artifact
{
	private:
		std::string name;
		SDL_Texture* image;
		int r, g, b;

	public:
		Artifact(std::string name_, SDL_Texture* image_, int r, int g, int b);
		Artifact();
		std::string getName();
		SDL_Texture* getImage();
		int getR();
		int getG();
		int getB();
};

#endif  //  BANDCAMP_ARTIFACT_H_