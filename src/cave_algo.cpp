#include 'include/cave_algo.h'

void init_array(int size, std::vector<std::vector<int>> cells, int start_percent) {
	int x = 0;
	int y = 0;
	int random_num = 0;
	
	for(y = 0; y < size; y++) {
		for(x = 0; x < size; x++) {
			random_num = rand() % 100;
			if(random_num < start_percent) cells[y].push_back(1);
			else cells.push_back(0);
		}
	}
}

void print_array(int size, std::vector<std::vector<int>> arr) {
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
			else if(cells[t_y][t_x] == 1) count += 1;
		}
	}
	return count;
}

std::vector<std::vector<int>> iterate(int size, std::vector<std::vector<int>> cells, int death_lim, int birth_lim) {
	int x = 0;
	int y = 0;
	
	std::vector<std::vector<int>> t_cells;
	t_cells.assign(size * size, 0);
	for(y = 0; y < size; y++) {
		for(x = 0; x < size; x++) {
			int c = count_neighbors(x, y, size, cells);
			if(cells[y][x] == 1) {
				if(c < death_lim) t_cells[y][x] = 0;
				else t_cells[y][x] = 1;
			}
			else {
				if(c > birth_lim) t_cells[y][x] = true;
				else t_cells[y][x] = 0;
			}
		}
	}
	
	return t_cells;
}

void flood_fill_recursive(std::vector<std::vector<int>> cells, std::vector<std::vector<bool>> visited, int size, int row, int column) {
	if(row >= size || y >= size) return;
	if(row < 0 || column < 0) return;
	
	if(visited[row][column]) return;
	
	visited[row][column] == true;
	
	int i = 0;
	int j = 0;
	for(i = row - 1; i <= row + 1; i++) {
		for(j = column - 1; j <= column + 1; j++) {
			if(i < size && j < size && i >= 0 && j >= 0) {
				if(!visited[i][j] && cells[i][j] != 0) flood_fill_recursive(cells, visited, size, i, j);
			}
		}
	}
}

std::vector<std::vector<bool>> flood_fill_from_point(std::vector<std::vector<int>> cells, int row, int column) {
	std::vector<std::vector<bool>> visited(size, std::vector<bool> (size, false));
	flood_fill_recursive(cells, visited, size, row, column);
	return visited;
}



bool cave_is_valid(std::vector<std::vector<int>> cells, int size) {
	return false;
}

std::vector<std::vector<int>> generate_cave(int death_limit, int birth_limit, int start_percent, int iter_count) {
	bool valid_cave = false;
	
	int sq_dim = 50;
	
	while(!valid_cave) {
		std::vector<std::vector<int>> cells;
		
		init_array(sq_dim, cells, start_percent);
		int i;
		for(i = 0; i < iter_count; i++) {
			cells = iterate(sq_dim, cells, death_limit, birth_limit);
		}
	}
	return cells;
}

int main() {
	std::vector<std::vector<int>> cells;
		
	init_array(sq_dim, cells, start_percent);
	int i;
	for(i = 0; i < iter_count; i++) {
		cells = iterate(sq_dim, cells, death_limit, birth_limit);
	}
	
	print_array(sq_dim, cells);
}
