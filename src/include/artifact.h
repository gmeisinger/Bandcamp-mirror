#ifndef BANDCAMP_ARTIFACT_H_
#define BANDCAMP_ARTIFACT_H_

#include <SDL.h>
#include <string>

class Artifact
{
	private:
		std::string name;
		std::string owner;
		std::string description;
		SDL_Texture* image;
		int r, g, b;

	public:
		Artifact(std::string name_, std::string owner_, std::string description_, SDL_Texture* image_, int r, int g, int b);
		Artifact();
		std::string getName();
		std::string getOwner();
		std::string getDescription();
		SDL_Texture* getImage();
		int getR();
		int getG();
		int getB();
};

#endif  //  BANDCAMP_ARTIFACT_H_