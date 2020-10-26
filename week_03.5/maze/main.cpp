#include "queue_ll.h"

// Task: MAZE
//              { {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
//				  {1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
//				  {1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
//				  {0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
//				  {1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
//				  {1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
//				  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
//				  {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
//				  {1, 1, 0, 0, 0, 0, 1, 0, 0, 1 } };
//   start -> index row, column
//   end -> index row, column

// Algorithm:
// 1. Modify the queue class. done
// 2. Implement BFS for our case.
//    -> start from source -> push in queue
//    -> boolean array - visited flag (beggining - false)
//    -> bfs:
//       -> loop until queue is not empty
//       -> dequeue -> current
//       -> check if current == destination? return pathLength : continue
//       -> for each adjacent cell, if !visited -> add to queue with pathLength of current + 1
// 3. Call bfs() with source, end destination.

const int COLS = 10;
const int ROWS = 10;

const int helperRow[] = { -1, 1, 0, 0 };
const int helperCol[] = { 0, 0, -1, 1 };

bool isValidCell(int r, int c) {
	return (r < ROWS && r >= 0 && c < COLS && c >= 0);
}

int bfs(
	bool maze[][COLS], 
	int sRow, int sCol,
	int eRow, int eCol) 
{
	// if the way is impossible
	if (maze[sRow][sCol] || maze[eRow][eCol]) {
		return -1;
	}

	// init visited matrix
	bool visited[ROWS][COLS];
	memset(visited, false, sizeof(visited));

	// mark the source cell as visited
	visited[sRow][sCol] = true;

	// create the queue
	Queue queue;
	//QNode first(sRow, sCol);
	queue.enqueue(sRow, sCol, 0);

	while (!queue.empty()) {
		QNode *current = queue.first();
		int cRow = current->row, cCol = current->col, cPathLength = current->pathLength;
		queue.dequeue();
		
		if (cRow == eRow && cCol == eCol) {
			std::cout << cRow << " " << cCol << std::endl;
			return cPathLength;
		}
		for (int i = 0; i < 4; ++i) {
			int nextRow = cRow + helperRow[i];
			int nextCol = cCol + helperCol[i];

			if (isValidCell(nextRow, nextCol) &&
				!visited[nextRow][nextCol] &&
				!maze[nextRow][nextCol]) {
				visited[nextRow][nextCol] = true;
				queue.enqueue(nextRow, nextCol, cPathLength + 1);
			}
		}
	}
	return -1;
}

int main() {

	bool maze[ROWS][COLS] = {   {1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
								{1, 0, 1, 0, 1, 1, 1, 0, 1, 1 },
								{1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
								{0, 0, 0, 0, 1, 0, 0, 0, 0, 1 },
								{1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
								{1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
								{1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
								{1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
								{1, 1, 0, 0, 0, 0, 1, 0, 0, 1 } };
	int sRow = 3, sCol = 0, eRow = 4, eCol = 3;
	int distance = bfs(maze, sRow, sCol, eRow, eCol);

	if (distance == -1) {
		std::cout << "Shortest path doesn't exist" << std::endl;
		system("pause");
		return 0;
	}
	std::cout << "Shortest path is: " << distance << std::endl;

	system("pause"); // Only because my VS version is old
	return 0;
}