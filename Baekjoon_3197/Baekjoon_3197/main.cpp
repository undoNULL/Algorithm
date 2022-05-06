#include<iostream>
#include<queue>
using namespace std;

#define MIN(val, min) (((val)>(min))?(val):(min))

int map[1501][1501] = { 0, };
int visit[1501][1501] = { 0, };

void debug_printMap(int w, int h) {
	cout << endl;
	for (int i = 0;i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}
void debug_printVisit(int w, int h) {
	cout << endl;
	for (int i = 0;i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << visit[i][j];
		}
		cout << endl;
	}
}

int conv(char c) {
	switch (c) {
	case '.': {return 0;}
	case'X': {return -1;}
	}
	return 0;
}
void getMap(int w, int h, pair<int, int> swan[2]) {
	char c;
	for (int i = 0;i < h; i++) {
		for (int j = 0; j < w; j++) {
			cin >> c;
			if (c == 'L') {
				if (swan[0].first == -1) {
					swan[0] = { j, i };
				}
				else {
					swan[1] = { j, i };
				}
			}
			else {
				map[i][j] = conv(c);
			}
		}
	}
}
bool inRange(int x, int start, int end) {
	return (start <= x) && (x < end);
}


void setTime(int x, int y, int w, int h) {
	int min = 10000;
	int xx[4] = { 1, 0 ,-1, 0 };
	int yy[4] = { 0,-1,0,1 };
	for (int i = 0; i < 4; i++) {
		if (inRange(x + xx[i], 0, w) && inRange(y + yy[i], 0, h)) {
			if (inRange(map[y + yy[i]][x + xx[i]],0, min)) {
				min = map[y + yy[i]][x + xx[i]];
			}
		}
	}
	map[y][x] = min + 1;
}
void spreadTime(int x, int y, int w, int h) {
	int xx[4] = { 1, 0 ,-1, 0 };
	int yy[4] = { 0,-1,0,1 };
	for (int i = 0; i < 4; i++) {
		if (inRange(x + xx[i], 0, w) && inRange(y + yy[i], 0, h)) {
			if (map[y + yy[i]][x + xx[i]] == -1) {
				map[y + yy[i]][x + xx[i]] = map[y][x] + 1;
			}
			else if(inRange(map[y][x]+1, 1, map[y+yy[i]][x+xx[i]])) {
				map[y + yy[i]][x + xx[i]] = map[y][x] + 1;
				spreadTime(x + xx[i], y + yy[i], w, h);
			}
		}
	}
}
void setMapIceMeltTime(int w, int h) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] != 0) {
				setTime(j, i, w, h);
				spreadTime(j, i, w, h);
			}
		}
	}
}

void bfs(pair<int, int> start, pair<int, int> end, int w, int h) {
	int xx[4] = { 1, 0 ,-1, 0 };
	int yy[4] = { 0,-1,0,1 };
	priority_queue<pair<int, pair<int, int>>> pq; //greater ÇÊ¿ä
	//queue<pair<int, int>> pq;
	pair<int, int> cur;
	int x = start.first, y = start.second, nX, nY;
	visit[y][x] = 1;
	pq.push({ visit[y][x], { x, y } });
	while (!pq.empty()) {
		cur = pq.top();
		x = cur.first;
		y = cur.second;
		pq.pop();
		if (end.first == x && end.second == y)
			break;
		for (int i = 0; i < 4; i++) {
			nX = x + xx[i];
			nY = y + yy[i];
			if (inRange(nX, 0, w) && inRange(nY, 0, h)) {
				if (visit[nY][nX] != 0)
					continue;
				//visit[nY][nX] = visit[y][x]; //map[nY][nX]+1;
				visit[nY][nX] = visit[y][x] + MIN(map[nY][nX]+1 - visit[y][x], 0);
				pq.push({visit[nY][nX], { nX,nY } });
			}
		}
	}
}


int main() {
	int w, h;
	pair<int, int> swan[2] = { {-1,-1},{-1,-1} };
	cin >> h >> w;
	getMap(w, h, swan);

	setMapIceMeltTime(w, h);
	bfs(swan[0], swan[1], w, h);

	debug_printMap(w, h);
	cout << endl << "Visit";
	debug_printVisit(w, h);

}