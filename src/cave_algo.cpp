#include <iostream>
#include <vector>
#include <string>
#include <time.h>

std::vector<std::vector<int>> init_array(int size, int start_percent) {
	std::vector<std::vector<int>> cells(size, std::vector<int> (size, 1));
	int x = 0;
	int y = 0;
	int random_num = 0;
	
	for(y = 0; y < size; y++) {
		for(x = 0; x < size; x++) {
			random_num = rand() % 100;
			
			if(random_num < start_percent) std::cout <<  random_num << std::endl;
			if(random_num < start_percent) {
				cells[y][x] = 0;
			}
			else {
				cells[y][x] = 1;
			}
		}
	}
	return cells;
}

void print_array(int size, std::vector<std::vector<int>> arr) {
	int x = 0;
	int y = 0;
	for(y = 0; y < size; y++) {
		for(x = 0; x < size; x++) {
			if(arr[y][x] != 0) std::cout << arr[y][x] << " ";
			else std::cout << "  ";
		}
		std::cout << std::endl;
	}
}

void print_array_b(int size, std::vector<std::vector<int>> arr) {
	int x = 0;
	int y = 0;
	for(y = 0; y < size; y++) {
		for(x = 0; x < size; x++) {
			std::cout << arr[y][x] << " ";
		}
		std::cout << std::endl;
	}
}
int count_neighbors(int x, int y, int size, std::vector<std::vector<int>> cells) {
	int count = 0;
	int i;
	int j;
	for(i = -1; i < 2; i++) {
		for(j = -1; j < 2; j++) {
			int t_x = x + j;
			int t_y = y + i;
			
			if(t_x < 0 || t_y < 0 || t_x >= size || t_y >= size) count += 1;
			else if(i == 0 && j == 0) count += 0;
			else if(cells[t_y][t_x] == 0) count += 1;
		}
	}
	return count;
}

std::vector<std::vector<int>> iterate(int size, std::vector<std::vector<int>> cells, int death_lim, int birth_lim) {
	int x = 0;
	int y = 0;
	
	std::vector<std::vector<int>> t_cells(size, std::vector<int> (size, 1));
	for(y = 0; y < size; y++) {
		for(x = 0; x < size; x++) {
			int c = count_neighbors(x, y, size, cells);
			if(cells[y][x] == 0) {
				if(c < death_lim) t_cells[y][x] = 1;
				else t_cells[y][x] = 0;
			}
			else {
				if(c > birth_lim) t_cells[y][x] = 0;
				else t_cells[y][x] = 1;
			}
		}
	}
	
	return t_cells;
}

std::vector<std::vector<int>> flood_fill_recursive(std::vector<std::vector<int>> cells, std::vector<std::vector<int>> visited, int size, int row, int column, int * counter) {
	//std::vector<std::vector<int>> std::vector<std::vector<int>> visited = *visitedptr;
	*counter += 1;
	if(*counter >= size * size) {
		return visited;
	}
	if(cells[row][column] == 0) {
		//std::cout << "bumpis" << std::endl;
		visited[row][column] = -1;
		return visited;
	}
	else { 
		visited[row][column] = 1;
		//std::cout << "1! Counter: " << *counter << "; visited: " << visited[row][column] << std::endl;
		//std::cout << visited[row][column] << std::endl;
	}
	int i = 0;
	int j = 0;
	for(i = row - 1; i <= row + 1; i++) {
		for(j = column - 1; j <= column + 1; j++) {
			//std::cout << "row: " << i << "; column: " << j << std::endl;
			if(i < size && j < size && i >= 0 && j >= 0 && (i != row || j != column) && (i == row || j == column)) {
				if(visited[i][j] == 0 && cells[i][j] != 0) {
					//std::cout << "v: " << visited[i][j] << "; cells: " << cells[i][j] << std::endl;
					//visited[i][j] = 1;
					visited = flood_fill_recursive(cells, visited, size, i, j, counter);
				}
			}
		}
	}
	
	return visited;
	//std::cout << "Ugg" << std::endl;
}

std::vector<std::vector<int>> flood_fill_from_point(std::vector<std::vector<int>> cells, int row, int column, int size) {
	std::cout << "x: " << row << "; y: " << column << std::endl;
	int counter = 0;
	std::vector<std::vector<int>> visited(size, std::vector<int> (size, 0));
	//visited[3][3] = 1;
	//print_array_b(size, visited);
	visited = flood_fill_recursive(cells, visited, size, row, column, &counter);
	print_array(size, visited);
	return visited;
}

int get_area(std::vector<std::vector<int>> cells_visited, int size) {
	int row;
	int column;
	int counter = 0;
	for(row = 0; row < size; row++) {
		for(column = 0; column < size; column++) {
			if(cells_visited[row][column] == 1) counter++;
		}
	}
	return counter;
}

std::vector<std::vector<int>> mask_cave(std::vector<std::vector<int>> cells, std::vector<std::vector<int>> visited, int size) {
	int row;
	int column;
	for(row = 0; row < size; row++) {
		for(column = 0; column < size; column++) {
			if(visited[row][column] == 1) cells[row][column] = 1;
			else cells[row][column] = 0;
		}
	}
	return cells;
}


std::vector<std::vector<int>> create_walls(std::vector<std::vector<int>> cells, int size) {
	int row;
	int column;
	int t_row;
	int t_column;
	
	for(row = 0; row < size; row++) {
		for(column = 0; column < size; column++) {
			if(cells[row][column] == 1) {
				for(t_row = row - 1; t_row <= row + 1; t_row++) {
					for(t_column = column - 1; t_column <= column + 1; t_column++) {
						if(t_row >= 0 && t_column >= 0 && t_row < size && t_column < size && (t_row != row || t_column != column)) {
							if(cells[t_row][t_column] == 0) cells[t_row][t_column] = 2;
						} else if(t_row < 0 || t_column < 0 || t_row >= size || t_column >= size) cells[row][column] = 2;
					}
				}
			}
		}
	}
	return cells;
}


std::vector<std::vector<int>> validate_cave(std::vector<std::vector<int>> cells, int size, int size_coefficient) {
	int rx;
	int ry;
	bool coord_found = false;
	std::vector<std::vector<int>> visited(size, std::vector<int> (size, false));
	std::cout << "A" << std::endl;
	while(!coord_found) {
		std::cout << "b" << std::endl;
		rx = rand() % size;
		ry = rand() % size;
		if(cells[ry][rx] == 1) {
			std::cout << "C" << std::endl;
			visited = flood_fill_from_point(cells, ry, rx, size);
			std::cout << "D" << std::endl;
			//print_array_b(size, visited);
			coord_found = true;
			
		}
	}
	
	if(get_area(visited, size) < (size/size_coefficient) * (size/size_coefficient)) {
		std::vector<std::vector<int>> invalid_cave(0, std::vector<int> (0, 0));
		return invalid_cave;
	}
	return visited;
	
}

//Parameters for the generation of the cave are as follows:
//size is the number of rows/columns (max total area will be a square of size * size)
//death_limit and birth_limit are parameters for cellular automata; values should be between 0 and 8, usually closer to 3 or 4.
//Low death limit results in smaller caves; too low can cause rejections, so try a larger size coefficient.
//Higher death limit results in wide open areas.
//Higher birth limit results in wide areas filled with walls.
//Birth limits lower than 4 tend to be unstable and should be avoided.
//Start percent is the chance that a tile starts as a cell. 40 is a good default; higher results in small caves, while lower results in larger caves.
//Iter count is the number of iterations; with most parameters, this isn't very important and won't change much after around 10 iterations, but it could cause issues with unstable parameters.
//Size coefficient is inversely proportional to minimum cave area. The minimum acceptable cave is calculated by (size/size_coefficient)^2
std::vector<std::vector<int>> generate_cave(int size, int death_limit, int birth_limit, int start_percent, int iter_count, int size_coefficient) {
	bool is_valid = false;
	std::vector<std::vector<int>> cells;
	std::vector<std::vector<int>> valid_cave;
	while(!is_valid) {
		cells = init_array(size, start_percent);
		print_array(size, cells);
		int i;
		for(i = 0; i < iter_count; i++) {
			//std::cin.get();
			cells = iterate(size, cells, 3, 4);
			//print_array(size, cells);
		}
		std::cout << "nnnnnnn" << std::endl;
		valid_cave = validate_cave(cells, size, size_coefficient);
		if(valid_cave.size() != 0) {
			is_valid = true;
			valid_cave = create_walls(valid_cave, size);
			print_array(size, valid_cave);
		}
	}
	
	return valid_cave;
}

int main() {
	srand(time(NULL));
	int iter_count = 10;
	int size = 30;
	int start_percent = 40;
	bool is_valid = false;
	std::vector<std::vector<int>> cells;
	
	while(!is_valid) {
		cells = init_array(size, start_percent);
		print_array(size, cells);
		int i;
		for(i = 0; i < iter_count; i++) {
			//std::cin.get();
			cells = iterate(size, cells, 3, 4);
			//print_array(size, cells);
		}
		std::cout << "nnnnnnn" << std::endl;
		std::vector<std::vector<int>> valid_cave = validate_cave(cells, size, 2);
		if(valid_cave.size() != 0) {
			is_valid = true;
			valid_cave = create_walls(valid_cave, size);
			print_array(size, valid_cave);
		}
	}
	//print_array(size, v);
}
