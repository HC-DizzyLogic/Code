////============================================================================
//// Name        : HashCode.cpp
//// Author      :
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Slice.cpp"


void leeFichero(string name, int & rows, int & cols, int & min, int & max, vector<vector<char> > & body);
vector<vector<int> > matrizValores (vector<vector<char> > pizza, int rows, int cols);
vector<int> getMultiples (int num);
coord Vecino (int i, coord actual);

int main() {
	int n_rows = 0, n_cols = 0, n_min = 0, n_max = 0, num_slices = 1;
	vector<vector<char> > pizza;

	leeFichero("small.in", n_rows, n_cols, n_min, n_max, pizza);
	vector<vector<int> > slices(n_rows, vector<int> (n_cols, 0));
	int min_slices = n_rows * n_cols / n_max;

	bool new_possibilities = true;
	vector<vector<int> > pot = matrizValores(pizza, n_rows, n_cols);
	cout << "!!!" << endl;

	vector<int> mul = getMultiples(n_max);

	while (new_possibilities){
		new_possibilities = false;
		for (int i = 0; i < (int)pot.size(); i++){
			for (int j = 0; j < (int)pot[0].size(); j++){
				coord actual;
				actual.x = i;
				actual.y = j;
				Slice best_slice(actual, 1, 5, n_min, n_max, pizza);
				if (pot[i][j] == 0) {
					new_possibilities = true;
					cout << endl << endl << "Actual is : [" << i << ", " << j << "]" << endl;
					for (int k = 0; k < (int)mul.size(); k++){
						int height = mul[k];
						int width = n_max / height;
						cout << height << " : " << width << endl;

						coord corner;
						corner.x = actual.x - width + 1;
						corner.y = actual.y - height + 1;

						for (int l = 0; l < width; l++)
							for (int m = 0; m < height; m++){
								coord n_corner; n_corner.x = corner.x + l; n_corner.y = corner.y + m;
								if (n_corner.x < 0) continue;
								if (n_corner.y < 0) continue;
								if (n_corner.x + width - 1 > n_rows) continue;
								if (n_corner.y + height - 1 > n_cols) continue;


								if (width >= height){
									for (int n = actual.x - n_corner.x + 1; n*height <= n_max; n++){
										if (n*height > 2*n_min - 1){
											Slice intento (n_corner, n,  height, n_min, n_max, pizza);
//											cout << "w : " << n << " h : " << height << "; ";
//											intento.toString();
											if (intento.isCompleted()) cout << "hue" << intento.getWidth()*intento.getHeight() << endl;
											if (intento.isCompleted()
													&& intento.getWidth()*intento.getHeight() < best_slice.getWidth()*best_slice.getHeight())
												best_slice = intento;
										}
									}
								}
								if (height > width){
									for (int n = actual.y - n_corner.y + 1; n*width <= n_max; n++){
										if (n*width > 2*n_min - 1){
											Slice intento (n_corner, width,  n, n_min, n_max, pizza);
//											cout << "w : " << width << " h : " << n << "; " ;
//											intento.toString();
											if (intento.isCompleted()) cout << "hue" <<  intento.getWidth()*intento.getHeight() << endl;
											if (intento.isCompleted()
													&& (intento.getWidth()*intento.getHeight()) < (best_slice.getWidth()*best_slice.getHeight()))
												best_slice = intento;
										}
									}
								}
							}
					}
				best_slice.toString();
				}
			}
		}

		cin.get();
	}

	/*	while (num_slices <= min_slices){
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
	 */

	for (int k = 0; k < (int)slices.size(); k++){
		for (int l = 0; l < (int)slices[0].size(); l++){
			cout << slices[k][l] << " : " << pizza[k][l] << "  ";
		}
		cout << endl;
	}
	return 0;
}

vector<int> getMultiples (int num){
	vector<int> multiples;
	for (int i = 1; i <= num; i++){
		if ((num % i == 0) || (i != (num - 1) && (num - 1) % i == 0)){

			cout << i << endl;
			multiples.push_back(i);
		}
	}

	return multiples;
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

vector<vector<int> > matrizValores (vector<vector<char> > pizza, int rows, int cols){
	vector<vector<int> > potencial (rows, vector<int> (cols, 0));
	for (int i = 0; i < (int)pizza.size(); i ++){
		for (int j = 0; j < (int)pizza[i].size(); j++){
			int num_vecinos_diferentes = 0;
			for (int n = 0; n < 4; n++){
				coord actual; actual.x = i; actual.y = j;
				coord vec = Vecino(n, actual);
				if (vec.x >= 0 && vec.x < rows && vec.y >= 0 && vec.y < cols){
					if ((pizza[actual.x][actual.y] == 'T' && pizza[vec.x][vec.y] == 'M')
							|| (pizza[actual.x][actual.y] == 'M' && pizza[vec.x][vec.y] == 'T')){
						num_vecinos_diferentes ++;
					}
				}
			}
			potencial[i][j] = num_vecinos_diferentes;
		}
	}

	for (int k = 0; k < (int)potencial.size(); k++){
		for (int l = 0; l < (int)potencial[0].size(); l++){
			cout << potencial[k][l] << "  ";
		}
		cout << endl;
	}
	return potencial;
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

