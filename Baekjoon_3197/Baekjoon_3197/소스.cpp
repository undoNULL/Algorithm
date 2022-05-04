#include<iostream>
#include<random>

using namespace std;

int main() {
	cout.tie(0);
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, 10);
	
	int w, h;

	while (1) {
		cin >> w >> h;
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (dis(gen) < 7) {
					cout << "X";
				}
				else {
					cout << ".";
				}
			}
			cout << endl;
		}
	}

}