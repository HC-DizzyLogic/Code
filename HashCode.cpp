//============================================================================
// Name        : HashCode.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
struct coord {
	int x;
	double y;
};

void leeFichero(string name, int & rows, int & cols, int & min, int & max, vector<vector<char> > & body);
coord Vecino (int i, coord actual);

int main() {
	int n_rows = 0, n_cols = 0, n_min = 0, n_max = 0, num_slices = 1;
	vector<vector<char> > pizza;

	leeFichero("small.in", n_rows, n_cols, n_min, n_max, pizza);
	vector<vector<int> > slices(n_rows, vector<int> (n_cols, 0));
	int min_slices = n_rows * n_cols / n_max;

	while (num_slices <= min_slices){
		int x = rand() % n_rows;
		int y = rand() % n_cols;
		int m = 0, t = 0;
		if (slices[x][y] == 0){
			bool completed = false;
			cout << "New slice in: " << x << ", " << y << endl;
			slices[x][y] = num_slices;
			coord actual;
			actual.x = x;
			actual.y = y;

			if (pizza[x][y] == 'T') t++;
			else if (pizza[x][y] == 'M') m++;
			else cout << "error";

			for (int j = 0; j < 4; j++){
				coord vecino = Vecino(j, actual);
				if (vecino.x < n_rows && vecino.x >= 0 && vecino.y < n_cols && vecino.y >= 0){
					if (slices[vecino.x][vecino.y] == 0){
						if (pizza[vecino.x][vecino.y] == 'T' && t < n_min){
							slices[vecino.x][vecino.y] = num_slices;
							t++;
						}
						if (pizza[vecino.x][vecino.y] == 'M' && m < n_min){
							slices[vecino.x][vecino.y] = num_slices;
							m++;
						}
						if (m == n_min && t == n_min){
							completed = true;
							num_slices ++;
							break;
						}
					}
				}
			}
			if (!completed){
				slices[x][y] = 0;
			}

			if (completed){
				cout << "Slice completed: " << num_slices - 1 << endl;
				for (int k = 0; k < (int)slices.size(); k++){
					for (int l = 0; l < (int)slices[0].size(); l++){
						cout << slices[k][l];
					}
					cout << endl;
				}
			}
		}
	}

	for (int k = 0; k < (int)slices.size(); k++){
		for (int l = 0; l < (int)slices[0].size(); l++){
			cout << slices[k][l] << " : " << pizza[k][l] << "  ";
		}
		cout << endl;
	}
	return 0;
}

coord Vecino (int i, coord actual){
	int x, y;
	switch(i){
	case 0:
		x = 0;
		y = 1;
		break;
	case 1:
		x = 1;
		y = 0;
		break;
	case 2:
		x = 0;
		y = -1;
		break;
	case 3:
		x = -1;
		y = 0;
		break;
	}
	coord vecino;
	vecino.x = x + actual.x;
	vecino.y = y + actual.y;
	return vecino;
}

void leeFichero(string name, int & rows, int & cols, int & min, int & max, vector<vector<char> > & body){
	string linea;
	ifstream infile;
	infile.open ("small.in");
	string firstline="";

	getline(infile,firstline);

	stringstream ss;
	ss.str("");
	ss.clear();
	ss << firstline;

	ss >> rows;
	ss >> cols;
	ss >> min;
	ss >> max;

	cout << "nº de filas: " << rows << ", nº de columnas: " << cols << endl;
	cout << "nº de ingredientes de cada tipo: " << min << " , nº max de casillas: " << max << endl;

	body = vector<vector<char> > (rows, vector<char> (cols, 0));

	for (int i = 0; i < rows; i++){ // To get you all the lines.
		getline(infile,linea); // Saves the line in STRING.
		for (int j = 0; j < cols; j++){
			body[i][j] = linea.at(j);
			cout << body[i][j];
		}
		cout<< endl;
	}
}

