#include<iostream>
#include<vector>
#include<queue>
using namespace std;

#define MIN(val, min) (((val)>(min))?(val):(min))
#define ABS(val) ((val<0)?(-val):(val))

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

struct node {
	int x;
	int y;
	int G;
	int H;
};
struct cmp {
	bool operator()(node t, node u) {
		return t.G > u.G;
	}
};

void bfs(pair<int, int> start, pair<int, int> end, int w, int h) {
	int xx[4] = { 1, 0 ,-1, 0 };
	int yy[4] = { 0,-1,0,1 };
	priority_queue<node, vector<node>, cmp> pq;
	node cur;
	int x = start.first, y = start.second, nX, nY;
	visit[y][x] = 1;
	pq.push({x, y, visit[y][x], (ABS(x-end.first)+ABS(y-end.second))});
	while (!pq.empty()) {
		cur = pq.top();
		x = cur.x;
		y = cur.y;
		pq.pop();
		if (end.first == x && end.second == y)
			break;
		for (int i = 0; i < 4; i++) {
			nX = x + xx[i];
			nY = y + yy[i];
			if (inRange(nX, 0, w) && inRange(nY, 0, h)) {
				if (visit[nY][nX] == 0) {
					visit[nY][nX] = visit[y][x] + MIN(map[nY][nX] + 1 - visit[y][x], 0);
					pq.push({ nX, nY, visit[nY][nX], (ABS(nX - end.first) + ABS(nY - end.second)) });
				}
			}
		}
	}
}


int main() {
	cin.tie(0);
	ios::sync_with_stdio(false);
	int w, h;
	pair<int, int> swan[2] = { {-1,-1},{-1,-1} };
	cin >> h >> w;
	getMap(w, h, swan);

	setMapIceMeltTime(w, h);
	bfs(swan[0], swan[1], w, h);

	debug_printMap(w, h);
	cout << endl << "Visit";
	debug_printVisit(w, h);
	cout << visit[swan[1].second][swan[1].first]-1 << endl;
}