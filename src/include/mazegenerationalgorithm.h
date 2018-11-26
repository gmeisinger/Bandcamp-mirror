#ifndef BANDCAMP_MAZEGENERATIONALGORITHM_H_
#define BANDCAMP_MAZEGENERATIONALGORITHM_H_

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <time.h>

class MGA
{
	private:
		std::vector<std::vector<int>> maze;
	
    public:
        MGA();
		MGA(int rowSize, int colSize);
        void printMaze();
        bool checkSpace(std::pair<int, int> currSpace, int dir);
        std::pair<int,int> update(std::pair<int,int> pair, int dir);
        std::string printDir(int dir);
        void genMazeDFS(std::pair <int, int> currSpace, int back);
		std::vector<std::vector<int>> getMaze();
};
#endif //BANDCAMP_MAZEGENERATIONALGORITHM_H_