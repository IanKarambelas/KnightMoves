#include <iostream>
#include <string>
#include <queue>

using namespace std;

/* defines a square on the chessboard as a Node */
typedef struct Node {
	int x, y;
} square;
 
/* defines the legal moves allowed by a knight (+-1 in the x or y, +-2 in the other) */
square move[8] = {{-2, 1}, {2, 1}, {2, -1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2}};

/* g[][] changes from 10000 to 0 when a move has been made at that location to 
 * prevent backtracking. h[][] places the number of moves thus far in each location
 * on the board starting with 0 in the original location.*/
int g[10][10], h[10][10];

/* prevents the knight from moving off the chess board */
bool outOfBounds(int x, int y) {

	if (x < 1 || x > 8 || y < 1 || y > 8)
		return true;

	return false;

}

/* performs the calculation by "moving" the knight around using a queue
 * INPUT: xy for the origin and xy for the destination
 * OUTPUT: number of knight moves to get there
 */
int BFS(int x1, int y1, int x2, int y2) {
	
	/* initializes the arrays. 0 in g[][] indicates the knight has not yet 
	 * moved there. h[][] will be filled up with the current move count
	 */
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++) {
			g[i][j] = 0;
			h[i][j] = 10000;
		}

	//the first location has been moved to, and is move count 0
	g[x1][y1] = 1;
	h[x1][y1] = 0;

	//sets up a queue to check multiple branching paths
	queue<square> path;
	
	//for the current, next, and temporary locations
	square temp, current, next;

	//original location
	temp.x = x1;
	temp.y = y1;

	path.push(temp);

	while (!path.empty()) {
		
		//moves the knight
		current = path.front();
		path.pop();
		
		//checks all 8 potential moves
		for (i = 0; i < 8; i++) {

			next.x = current.x + move[i].x;
			next.y = current.y + move[i].y;

			//if the move is not out of bounds and is not backtracking
			if (!outOfBounds(next.x, next.y) && g[next.x][next.y] == 0) {
				//marks it as having been moved to
				g[next.x][next.y] = 1;
				//increments the move count
				h[next.x][next.y] = h[current.x][current.y] + 1;
				
				//if it is the destination
				if(next.x == x2 && next.y == y2)
					//return the current move count 
					return h[next.x][next.y];
				//otherwise, check the next potential move
				path.push(next);
			}
		}
	}
	//returns 10000 if there was no possible path, seeing this return indicates a bug
	return h[x2][y2];
}

int main()
{

	int x1, x2, y1, y2;    
	string begin, end;			/* starting and ending square */
    cin >> begin;               /* read the data in the first column */
    while (!cin.eof())
    {
		cin >> end;             /* read the data in the second column */
        
		x1 = begin[0] - 'a' + 1;
		x2 = end [0] - 'a' + 1;
		y1 = begin[1] - '0';
		y2 = end[1] - '0';	
	
        /* print answer */
        cout << "To get from " << begin << " to " << end << " takes " << BFS(x1, y1, x2, y2) << " moves." << endl;
 
        cin >> begin;			/* read the next line */
    }
    return 0;
}
