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

int g[10][10], h[10][10];

bool outOfBounds(int x, int y) {

	if (x < 1 || x > 8 || y < 1 || y > 8)
		return true;

	return false;

}

int BFS(int x1, int y1, int x2, int y2) {
	
	int i, j;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 10; j++) {
			g[i][j] = 0;
			h[i][j] = 10000;
		}

	g[x1][y1] = 1;
	h[x1][y1] = 0;

	queue<square> path;
	
	square temp, current, next;

	temp.x = x1;
	temp.y = y1;
	
	path.push(temp);

	while (!path.empty()) {
		
		current = path.front();
		path.pop();
		
		for (i = 0; i < 8; i++) {

			next.x = current.x + move[i].x;
			next.y = current.y + move[i].y;

			if (!outOfBounds(next.x, next.y) && g[next.x][next.y] == 0) {
				g[next.x][next.y] = 1;
				h[next.x][next.y] = h[current.x][current.y] + 1;
				if(next.x == x2 && next.y == y2) 
					return h[next.x][next.y];
				path.push(next);
			}
		}
	}
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
