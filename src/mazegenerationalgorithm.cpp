#include "include/mazegenerationalgorithm.h"
using namespace std;

constexpr int WALL_TILE = 2;
constexpr int FLOOR_TILE = 1;

MGA::MGA(){}

MGA::MGA(int rowSize, int colSize)
{
    srand(time(NULL));
    maze = std::vector<std::vector<int>>(rowSize, std::vector<int>(colSize, WALL_TILE));
    std::pair<int,int> start = {((rand() % (rowSize-2))+1), ((rand() % (colSize-2))+1)};
    genMazeDFS(start, -1);
    std::cout<<"end"<<endl;
}

void MGA::printMaze(){
    for (int i = 0; i < maze.size(); i++) {
        for (int j = 0; j < maze[i].size(); j++)
            if(maze[i][j] == WALL_TILE)
                cout << "#";
            else
                cout << " ";
        cout << endl;
    }
    cout << "--------------------------------------" << endl;
}

std::vector<std::vector<int>> MGA::getMaze(){ return maze; }

/*
	Checks how many squares are exposed.
	Returns:
 true - if this is a viable square to move into
 false - if this is not a viable square to move into.
	dir:
	1 - up
	2 - right
	3 - down
	4 - left
 */
bool MGA::checkSpace(std::pair<int, int> currSpace, int dir){
    //Check if we can move in that direction.
    switch(dir){
        case 1: //up
            if((currSpace.first - 1) == 0) //Row
                return false; // We want a 1 space border around the map.
            else
                currSpace.first--;
            break;
            
        case 2: //right
            if((currSpace.second + 1) == maze[0].size()-1) //Col
                return false; // We want a 1 space border around the map.
            else
                currSpace.second++;
            break;
            
        case 3: //down
            if((currSpace.first + 1) == maze.size()-1) //Row
                return false; // We want a 1 space border around the map.
            else
                currSpace.first++;
            break;
            
        case 4: //left
            if((currSpace.second - 1) == 0) //Col
                return false; // We want a 1 space border around the map.
            else
                currSpace.second--;
            break;
    }
    
    int exposedSquares = 0;
    
    if(maze[currSpace.first - 1][currSpace.second] == FLOOR_TILE) //Check up
        exposedSquares++;
    if(maze[currSpace.first + 1][currSpace.second] == FLOOR_TILE)
        exposedSquares++;
    if(maze[currSpace.first][currSpace.second + 1] == FLOOR_TILE)//Check right
        exposedSquares++;
    if(maze[currSpace.first][currSpace.second - 1] == FLOOR_TILE)//Check right
        exposedSquares++;
    
    //cout << "Exposed Sq: " << exposedSquares << endl;
    return exposedSquares <= 1;
}

std::pair<int,int> MGA::update(std::pair<int,int> pair, int dir){
    switch(dir){
        case 1: //up
            return std::pair <int, int> (pair.first-1, pair.second);
            
        case 3: //down
            return std::pair <int, int> (pair.first+1, pair.second);
            
        case 2: //right
            return std::pair <int, int> (pair.first, pair.second+1);
            
        case 4: //left
            return std::pair <int, int> (pair.first, pair.second-1);
    }
}

std::string MGA::printDir(int dir){
    switch(dir){
        case 1: //up
            return "up";
            
        case 3: //down
            return "down";
            
        case 2: //right
            return "right";
            
        case 4: //left
            return "left";
    }
}


/*
	Generates the maze via DFS
	currX and currY let the maze know where it is currently.
	back lets it know what direction is backwards
	1 - up
	2 - right
	3 - down
	4 - left
 */
void MGA::genMazeDFS(std::pair <int, int> currSpace, int back){
    maze[currSpace.first][currSpace.second] = FLOOR_TILE; //Mark it as open
    
    std::vector<int> directions = {1,2,3,4};
    
    std::random_shuffle ( directions.begin(), directions.end() );
    
    for (std::vector<int>::iterator it=directions.begin(); it!=directions.end(); ++it)
    {
        //printMaze();
        std::string d = printDir(*it);
        
        if(checkSpace(currSpace, *it) && (*it+2)%4 != back) //Check exposed squares
        {
            std::pair<int, int> newSpace = update(currSpace, *it);
            genMazeDFS(newSpace, *it);
        }
    }
}



/*int main(int argc, char* argv[]) {
	srand (time(NULL)); //Seed our random with the time.
	
	int row, col;
	cout << "Rows?: ";
	cin >> row;
	cout << "Columns?: ";
	cin >> col;
	cout << "Maze size of ("<<row<<","<<col<<")"<<endl;
	
	std::vector<std::vector<int>> array(row, std::vector<int>(col, 1));
	maze = array;
	std::pair<int,int> currSpace = {(rand() % (row-2))+1,(rand() % (col-2))+1};
	cout << "Starting at ("<<currSpace.first<<","<<currSpace.second<<")"<<endl;
	genMazeDFS(currSpace, -1);
	printMaze();
 }*/
