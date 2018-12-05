#include "include/generator.h"

/*

*/

constexpr int ROOM_MAX_SIZE = 13;
constexpr int ROOM_MIN_SIZE = 5;

//default constructor
Generator::Generator() {
	width = 100;
	height = 100;
	cur_width = 0;
	cur_height = 0;
	rooms = {};
	room_objs = {};
	map = std::vector< std::vector< int > >(height, std::vector<int>(width, 0));
	srand(time(NULL));
}

//custom size constructor
Generator::Generator(int w, int h) {
	width = w;
	height = h;
	cur_width = 0;
	cur_height = 0;
	rooms = {};
	room_objs = {};
	map = std::vector< std::vector< int > >(height, std::vector<int>(width, 0));
	srand(time(NULL));
}

//destructor
Generator::~Generator() {
}

//returns the 2d vector representing the map
std::vector< std::vector< int > > Generator::getMap() {
	return map;
}


//checks a room against all rooms for overlap
bool Generator::checkOverlap(SDL_Rect room) {
	room.x += 1;
	room.y += 1;
	room.w -= 2;
	room.h -= 2;
	bool collides = false;
	for(auto r : room_objs) {
		SDL_Rect rect = r->getRectCopy();
		if(SDL_HasIntersection(&room, &rect)) {
			collides = true;
			break;
		}
		if((rect.x + rect.w) > map[0].size() || (rect.y + rect.h) > map.size()) {
			collides = true;
			break;
		}
	}
	if(collides) //std::cout << "Collides." << std::endl;
	return collides;
}

//place a room using rectangle packing
void Generator::placeRoom(SDL_Rect room, bool fill) {
	if(rooms.size() == 0) {
		//std::cout << "First room" << std::endl;
		rooms.push_back(room);
		room_objs.push_back(new Room(room));
		cur_width = room.w;
		cur_height = room.h;
		cutRoom(room);
	}
	else {
		//find a corner closest to the origin
		/*
			we want a corner like this:

			xx
			xo

			lets search the map and keep a list of coordinates to these corners
		*/
		std::vector<std::pair<int,int>> corners = getCorners();
		//now we check each corner to see if room fits
		for(auto corner : corners) {
			room.x = corner.second;
			room.y = corner.first;
			if(fill && growsMap(room)) {
				//dont use that corner
			}
			else if(!checkOverlap(room)) {
				rooms.push_back(room);
				room_objs.push_back(new Room(room));
				//cut the room
				cutRoom(room);
				//adjust cur width and height
				if((room.x + room.w) > cur_width) {
					cur_width = room.x + room.w;
				}
				if((room.y + room.h) > cur_height) {
					cur_height = room.y + room.h;
				}
				//std::cout << "Placing room:\n" << room.x << " " <<room.y << " " << room.w << " " << room.h << std::endl;
			}
		}
	}
}

bool Generator::growsMap(SDL_Rect room) {
	bool ret = false;
	if((room.x + room.w) > cur_width) {
		ret = true;
	}
	if((room.y + room.h) > cur_height) {
		ret = true;
	}
	return ret;
}

void Generator::cutRoom(SDL_Rect room) {
	for(int r=room.y;r<(room.y + room.h);r++){
		for(int c=room.x;c<(room.x + room.w);c++) {
			if(r == room.y || r == (room.y + room.h -1) || c == room.x || c == (room.x + room.w -1)) {
				map[r][c] = 2;
			}
			else {
				map[r][c] = 1;
			}	
		}
	}
}

void Generator::cutRoom(SDL_Rect room, int marker) {
	for(int r=room.y;r<(room.y + room.h);r++){
		for(int c=room.x;c<(room.x + room.w);c++) {
			map[r][c] = marker;	
		}
	}
}

void Generator::cutDoor(SDL_Rect intersect) {
	int r, c = 0;
	if(intersect.w > intersect.h && intersect.w > 2) {
		//horizontal wall
		r = intersect.y;
		c = intersect.x + (intersect.w/2);
		map[r][c] = 4;
	}
	else if(intersect.w < intersect.h && intersect.h > 2) {
		r = intersect.y + (intersect.h/2);
		c = intersect.x;
		map[r][c] = 4;
	}
	
}

//return a list of all corner candidates
std::vector<std::pair<int,int>> Generator::getCorners() {
	std::vector<std::pair<int,int>> corners = {};
	//iterate over map looking for walls
	for(int r=0;r<map.size();r++) {
		for(int c=0;c<map[0].size();c++) {
			if(map[r][c] == 2) {
				//wall found, check if its a valid corner
				if((r == 0 && map[r+1][c] == 2 && map[r+1][c+1] == 0) || (c == 0 && map[r][c+1] == 2 && map[r+1][c+1] == 0) || (map[r][c+1] == 2 && map[r+1][c] == 2 && map[r+1][c+1] == 0)) {
					//valid, add to list
					std::pair<int,int> corner = {r, c};
					corners.push_back(corner);
				}
			}
		}
	}
	//std::cout << corners.size() << " corners found." << std::endl;
	std::random_shuffle(corners.begin(), corners.end());
	return corners;
}

//create a room of random size
SDL_Rect Generator::genRoom(int min, int max) {
	//create a random room, stored as a rect
	int room_w = (rand() % (max - min)) + min;
	int room_h = (rand() % (max - min)) + min;
	int room_x = 0;
	int room_y = 0;
	SDL_Rect rect = {room_x, room_y, room_w, room_h};
	return rect;
}

int Generator::getNumRooms() {
	return rooms.size();
}

void Generator::finalize() {
	for(auto r : room_objs) {
		setRoomNeighbors(r);
		for(auto intersect : r->getIntersects()) {
			//cutRoom(intersect, 3);
			cutDoor(intersect);
		}
	}
}

//Pick 20 random spots
void Generator::addChests() {
	for(int x = 0; x < 20; x++){
		int randX = (rand() % (map.size()-1))+1;
		int randY = (rand() % (map[0].size()-1))+1;
		
		if(!(randX == 1 && randY == 1) && map[randX][randY] == 1 && map[randX][randY+1] != 4 && map[randX][randY-1] != 4 
			&& map[randX+1][randY] != 4 && map[randX-1][randY] != 4)
			map[randX][randY] = 5;
			
	}
}

void Generator::setRoomNeighbors(Room* r) {
	for(auto other : room_objs) {
		if(r != other) {
			SDL_Rect rect = r->getRectCopy();
			SDL_Rect other_rect = other->getRectCopy();
			SDL_Rect intersect;
			if(SDL_IntersectRect(&rect, &other_rect, &intersect)) {
				r->addIntersect(intersect);
				r->addNeighbor(other);
			}
		}
	}
}

std::vector<Room*> Generator::getRooms() {
	return room_objs;
}
