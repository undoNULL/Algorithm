#include<iostream>
using namespace std;

int map[1501][1501] = { 0, };

int conv(char c) {
	switch (c) {
	case '.': {return 0;}
	case'X': {return 1;}
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
int minFilter(int x, int y, int w, int h) {
	int min = map[y][x];
	int xx[4] = { 1, 0 ,-1, 0 };
	int yy[4] = { 0,-1,0,1 };
	for (int i = 0; i < 4; i++) {
		if (inRange(x + xx[i], 0, w) && inRange(y + yy[i], 0, h)) {
			if (map[y + yy[i]][x + xx[i]] < min) {
				min = map[y + yy[i]][x + xx[i]];
			}
		}
	}
	return min;
}
int setMapIceMeltTime(int w, int h) {
	int increment = 0;
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (map[i][j] != 0) {
				if (map[i][j] < minFilter(j, i, w, h) + 1) {
					map[i][j] = minFilter(j, i, w, h) + 1;
					increment++;
				}
			}
		}
	}
	return increment;
}

void debug_printMap(int w, int h) {
	cout << endl;
	for (int i = 0;i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	int w, h;
	pair<int, int> swan[2] = { {-1,-1},{-1,-1} };
	cin >> h >> w;
	getMap(w, h, swan);

	// ´À¸²
	while (setMapIceMeltTime(w, h) != 0);

	debug_printMap(w, h);


}