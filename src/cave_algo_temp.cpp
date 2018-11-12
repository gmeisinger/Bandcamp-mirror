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

void flood_fill_recursive(std::vector<std::vector<int>> cells, std::vector<std::vector<int>> visited, int size, int row, int column) {
	if(cells[row][column] == 0) {
		//std::cout << "bumpis" << std::endl;
		visited[row][column] = -1;
		return;
	}
	else { 
		//std::cout << "1!" << std::endl;
		visited[row][column] = 1;
		//std::cout << visited[row][column] << std::endl;
	}
	int i = 0;
	int j = 0;
	for(i = row - 1; i <= row + 1; i++) {
		for(j = column - 1; j <= column + 1; j++) {
			std::cout << "row: " << i << "; column: " << j << std::endl;
			if(i < size && j < size && i >= 0 && j >= 0 && i != row && j != column) {
				if(visited[i][j] == 0 && cells[i][j] != 0) {
					std::cout << "v: " << visited[i][j] << "; cells: " << cells[i][j] << std::endl;
					visited[i][j] = 1;
					flood_fill_recursive(cells, visited, size, i, j);
				}
			}
		}
	}
	//std::cout << "Ugg" << std::endl;
}

std::vector<std::vector<int>> flood_fill_from_point(std::vector<std::vector<int>> cells, int row, int column, int size) {
	std::cout << "x: " << row << "; y: " << column << std::endl;
	std::vector<std::vector<int>> visited(size, std::vector<int> (size, 0));
	flood_fill_recursive(cells, visited, size, row, column);
	print_array_b(size, visited);
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

void mask_cave(std::vector<std::vector<int>> cells, std::vector<std::vector<int>> visited, int size) {
	int row;
	int column;
	for(row = 0; row < size; row++) {
		for(column = 0; column < size; column++) {
			if(visited[row][column] == 1) cells[row][column] = 1;
		}
	}
}

bool cave_is_valid(std::vector<std::vector<int>> cells, int size) {
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
			print_array_b(size, visited);
			coord_found = true;
			
		}
	}
	
	
	mask_cave(cells, visited, size);
	return true;
	
}

std::vector<std::vector<int>> generate_cave(int size, int death_limit, int birth_limit, int start_percent, int iter_count) {
	bool valid_cave = false;
	
	std::vector<std::vector<int>> cells = init_array(size, start_percent);
	print_array(size, cells);
	int i;
	for(i = 0; i < iter_count; i++) {
		std::cin.get();
		cells = iterate(size, cells, 3, 4);
		
		print_array(size, cells);
	}
	
	return cells;
}

int main() {
	srand(time(NULL));
	int iter_count = 10;
	int size = 50;
	int start_percent = 40;
	std::vector<std::vector<int>> cells = init_array(size, start_percent);
	print_array(size, cells);
	int i;
	for(i = 0; i < iter_count; i++) {
		//std::cin.get();
		cells = iterate(size, cells, 3, 4);
		//print_array(size, cells);
	}
	std::cout << "nnnnnnn" << std::endl;
	cave_is_valid(cells, size);
	
	print_array(size, cells);
}
