#include "Slice.h"

int main() {
	int n_rows = 0, n_cols = 0, n_min = 0, n_max = 0;
	vector<Slice> slices;

	leeFichero("big.in", n_rows, n_cols, n_min, n_max);

	bool new_possibilities = true;
	vector<vector<int> > pot = matrizValores(n_rows, n_cols);

	vector<int> mul = getMultiples(n_max);

	while (new_possibilities){
		new_possibilities = false;
		for (int i = 0; i < (int)pot.size(); i++){
			for (int j = 0; j < (int)pot[0].size(); j++){
				coord actual;
				actual.x = i;
				actual.y = j;
				Slice best_slice(actual, 1, n_max, n_min, n_max);
				bool cambiado = false;
				if (pot[i][j] == 0) {
					new_possibilities = true;
					asignaVecinos(actual, best_slice, cambiado, mul, n_rows, n_cols, n_max, n_min);

					if (cambiado){
						best_slice.toString();
						slices.push_back(best_slice);
						cutPizza(best_slice);
						pot = matrizValores(n_rows, n_cols);

					} else {
						lonelyPizza(actual);
					}
				}
			}
		}
		expand(slices);

		if (!new_possibilities){
			for (int i = 0; i < (int)pot.size(); i++){
				for (int j = 0; j < (int)pot[0].size(); j++){
					coord actual;
					actual.x = i;
					actual.y = j;
					Slice best_slice(actual, 1, n_max, n_min, n_max);
					bool cambiado = false;
					if (pot[i][j] == 1) {
						new_possibilities = true;
						asignaVecinos(actual, best_slice, cambiado, mul, n_rows, n_cols, n_max, n_min);

						if (cambiado){
							best_slice.toString();
							slices.push_back(best_slice);
							cutPizza(best_slice);
							pot = matrizValores(n_rows, n_cols);

						} else {
							lonelyPizza (actual);
						}
					}
				}
			}
		}
		expand(slices);

		if (!new_possibilities){
			for (int i = 0; i < (int)pot.size(); i++){
				for (int j = 0; j < (int)pot[0].size(); j++){
					coord actual;
					actual.x = i;
					actual.y = j;
					Slice best_slice(actual, 1, n_max, n_min, n_max);
					bool cambiado = false;
					if (pot[i][j] > 1) {
						new_possibilities = true;
						asignaVecinos(actual, best_slice, cambiado, mul, n_rows, n_cols, n_max, n_min);

						if (cambiado){
							best_slice.toString();
							slices.push_back(best_slice);
							cutPizza(best_slice);
							pot = matrizValores(n_rows, n_cols);

						} else {
							lonelyPizza (actual);
						}
					}
				}
			}
		}
		expand(slices);

//		printPizza();
		pot = matrizValores(n_rows, n_cols);
		checkSuccess();

		cin.get();
	}

	  ofstream myfile;
	  myfile.open ("result.txt");
	  myfile << to_string((int)slices.size()) + "\n";
	  for (int i = 0; i < (int)slices.size(); i++){
		  myfile << slices[i].toString();
	  }
	  myfile.close();
	return 0;
}

