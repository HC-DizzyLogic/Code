////============================================================================
//// Name        : HashCode.cpp
//// Author      :
//// Version     :
//// Copyright   : Your copyright notice
//// Description : Hello World in C++, Ansi-style
////============================================================================
//
#include <fstream>
#include <sstream>
#include "Slice.cpp"

void leeFichero(string name, int & rows, int & cols, int & min, int & max, vector<vector<char> > & body);
vector<vector<int> > matrizValores(vector<vector<char> > pizza, int rows, int cols);
vector<int> getMultiples (int num);
void asignaVecinos(coord actual, Slice & best_slice, bool & cambiado, vector<int> mul, int n_rows, int n_cols, int n_max, int n_min, vector<vector<char> > & pizza);
void expand(vector<vector<char> > pizza, vector<Slice> & slices);
coord Vecino(int i, coord actual);

int main() {
	int n_rows = 0, n_cols = 0, n_min = 0, n_max = 0;
	vector<vector<char> > pizza;
	vector<Slice> slices;

	leeFichero("medium.in", n_rows, n_cols, n_min, n_max, pizza);

	bool new_possibilities = true;
	vector<vector<int> > pot = matrizValores(pizza, n_rows, n_cols);

	vector<int> mul = getMultiples(n_max);

	while (new_possibilities){
		new_possibilities = false;
		for (int i = 0; i < (int)pot.size(); i++){
			for (int j = 0; j < (int)pot[0].size(); j++){
				coord actual;
				actual.x = i;
				actual.y = j;
				Slice best_slice(actual, 1, n_max, n_min, n_max, pizza);
				bool cambiado = false;
				if (pot[i][j] == 0) {
					new_possibilities = true;
					asignaVecinos(actual, best_slice, cambiado, mul, n_rows, n_cols, n_max, n_min, pizza);

					if (cambiado){
						best_slice.toString();
						slices.push_back(best_slice);
						for (int i = 0; i < best_slice.getHeight(); i++){
							for (int j = 0; j < best_slice.getWidth(); j++){
								pizza[i + best_slice.getTopLeftCorner().x][j + best_slice.getTopLeftCorner().y] = 'V';
							}
						}
						pot = matrizValores(pizza, n_rows, n_cols);

					} else {
						pizza[actual.x][actual.y] = 'A';

					}
				}
			}
		}
		expand(pizza, slices);

		if (!new_possibilities){
			for (int i = 0; i < (int)pot.size(); i++){
				for (int j = 0; j < (int)pot[0].size(); j++){
					coord actual;
					actual.x = i;
					actual.y = j;
					Slice best_slice(actual, 1, n_max, n_min, n_max, pizza);
					bool cambiado = false;
					if (pot[i][j] == 1) {
						new_possibilities = true;
						asignaVecinos(actual, best_slice, cambiado, mul, n_rows, n_cols, n_max, n_min, pizza);

						if (cambiado){
							best_slice.toString();
							slices.push_back(best_slice);
							for (int i = 0; i < best_slice.getHeight(); i++){
								for (int j = 0; j < best_slice.getWidth(); j++){
									pizza[i + best_slice.getTopLeftCorner().x][j + best_slice.getTopLeftCorner().y] = 'V';
								}
							}
							pot = matrizValores(pizza, n_rows, n_cols);

						} else {
							pizza[actual.x][actual.y] = 'A';

						}
					}
				}
			}
		}

		if (!new_possibilities){
			for (int i = 0; i < (int)pot.size(); i++){
				for (int j = 0; j < (int)pot[0].size(); j++){
					coord actual;
					actual.x = i;
					actual.y = j;
					Slice best_slice(actual, 1, n_max, n_min, n_max, pizza);
					bool cambiado = false;
					if (pot[i][j] > 1) {
						new_possibilities = true;
						asignaVecinos(actual, best_slice, cambiado, mul, n_rows, n_cols, n_max, n_min, pizza);

						if (cambiado){
							best_slice.toString();
							slices.push_back(best_slice);
							for (int i = 0; i < best_slice.getHeight(); i++){
								for (int j = 0; j < best_slice.getWidth(); j++){
									pizza[i + best_slice.getTopLeftCorner().x][j + best_slice.getTopLeftCorner().y] = 'V';
								}
							}
							pot = matrizValores(pizza, n_rows, n_cols);

						} else {
							pizza[actual.x][actual.y] = 'A';

						}
					}
				}
			}
		}
		for (int i = 0; i < n_rows; i++){ // To get you all the lines.
			for (int j = 0; j < n_cols; j++){
				cout << pizza[i][j];
			}
			cout<< endl;
		}

		pot = matrizValores(pizza, n_rows, n_cols);
		int in_slice = 0, out_slice = 0;
		for (int i = 0; i < n_rows; i++){ // To get you all the lines.
			for (int j = 0; j < n_cols; j++){
				if (pizza[i][j] == 'V') in_slice ++;
				else if (pizza[i][j] == 'A') out_slice ++;
			}
		}

		cout << "Num in slice : " << ((float)in_slice / (float)(n_cols*n_rows))*100 << "%" << endl;
		cout << "Num out slice : " << ((float)out_slice / (float)(n_cols*n_rows))*100 << "%" <<  endl;

		cin.get();
	}

	return 0;
}

vector<int> getMultiples (int num){
	vector<int> multiples;
	for (int i = 1; i <= num / 2; i++){
		if (num % i == 0) {
			cout << i << endl;
			cout << num/i << endl;
			multiples.push_back(i);
			multiples.push_back(num/i);
		} else if (i != (num - 1) && (num - 1) % i == 0){
			cout << i << endl;
			multiples.push_back(i);
			if ((num - 1) / i != i) multiples.push_back((num - 1)/i);
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

void asignaVecinos (coord actual, Slice & best_slice, bool & cambiado, vector<int> mul, int n_rows, int n_cols, int n_max, int n_min, vector<vector<char> > & pizza) {
	cout << "actual: " << actual.x << ", " << actual.y << endl;
	for (int k = 0; k < (int)mul.size(); k++){
		int rows = mul[k];
		int cols = n_max / rows;

		coord corner;
		corner.x = actual.x - rows + 1;
		corner.y = actual.y - cols + 1;

		for (int l = 0; l < rows; l++){
			for (int m = 0; m < cols; m++){
				coord n_corner;
				n_corner.x = corner.x + l;
				n_corner.y = corner.y + m;
				//				cout << "n_corner = [" << n_corner.x << ", " << n_corner.y << "]" << endl;
				if (n_corner.x < 0) continue;
				if (n_corner.y < 0) continue;

				if (cols >= rows){
					for (int n = actual.y - n_corner.y + 1; n*rows <= n_max; n++){
						if (n_corner.x + rows - 1 > n_rows) continue;
						if (n_corner.y + n - 1 > n_cols) continue;
						if (n*rows >= 2*n_min){
							Slice intento (n_corner, rows,  n, n_min, n_max, pizza);
							//							cout << "w : " << n << " h : " << rows << "; ";
							//							intento.toString();
							//							if (intento.isCompleted()) cout << "Completed " << intento.getWidth()*intento.getHeight() << endl;
							if (intento.isCompleted() &&
									intento.getWidth()*intento.getHeight() < best_slice.getWidth()*best_slice.getHeight()){
								best_slice = intento;
								cambiado = true;
							}
						}
					}
				} else if (cols < rows){
					for (int n = actual.x - n_corner.x + 1; n*cols <= n_max; n++){
						if (n_corner.x + n - 1 > n_rows) continue;
						if (n_corner.y + cols - 1 > n_cols) continue;
						if (n*cols >= 2*n_min){
							Slice intento (n_corner, n,  cols, n_min, n_max, pizza);
							//							cout << "w : " << cols << " h : " << n << "; " << actual.y << ", " << n_corner.y << ";" ;
							//							intento.toString();
							//							if (intento.isCompleted()) cout << "Completed" <<  intento.getWidth()*intento.getHeight() << endl;
							if (intento.isCompleted() &&
									(intento.getWidth()*intento.getHeight()) < best_slice.getWidth()*best_slice.getHeight()){
								best_slice = intento;
								cambiado = true;
							}
						}
					}
				}
			}
		}
	}
	//	cout << "a" << endl;
	//	cout << cambiado << endl;
	//	best_slice.toString();
	//	cin.get();
}

void expand (vector<vector<char> > pizza, vector<Slice> & slices) {
	//	for (int i = 0; i < (int)pizza.size(); i++){
	//		for (int j = 0; j < (int)pizza[0].size(); j++){
	//			if
	//		}
	//	}
}

vector<vector<int> > matrizValores (vector<vector<char> > pizza, int rows, int cols){
	vector<vector<int> > potencial (rows, vector<int> (cols, 0));
	for (int i = 0; i < (int)pizza.size(); i ++){
		for (int j = 0; j < (int)pizza[i].size(); j++){
			if (pizza[i][j] == 'V'){
				potencial[i][j] = -1;
			} else if (pizza[i][j] == 'A'){
				potencial[i][j] = -2;
			} else {
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
	}

	//		for (int k = 0; k < (int)potencial.size(); k++){
	//			for (int l = 0; l < (int)potencial[0].size(); l++){
	//				cout << potencial[k][l] << "  ";
	//			}
	//			cout << endl;
	//		}
	return potencial;
}

void leeFichero(string name, int & rows, int & cols, int & min, int & max, vector<vector<char> > & body){
	string linea;
	ifstream infile;
	infile.open (name);
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

