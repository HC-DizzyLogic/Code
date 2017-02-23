#include "Slice.h"

vector<vector<char> > pizza;

Slice::Slice(void){
	coord zero;
	zero.x = 0; zero.y = 0;
	this->top_left_corner = zero;
	this->num_mushrooms = 0;
	this->num_tomatoes = 0;
	this->width = 0;
	this->height = 0;
	this->min_vegetables = 0;
	this->max_size = 0;
	this->completed = false;
	this->empties = true;
}

Slice::Slice(coord tlc, int t, int m, int h, int w, int min, int max, bool c, bool e){
	this->top_left_corner = tlc;
	this->num_mushrooms = m;
	this->num_tomatoes = t;
	this->width = w;
	this->height = h;
	this->min_vegetables = min;
	this->max_size = max;
	this->completed = c;
	this->empties = e;
}

Slice::Slice(coord tlc, int h, int w, int min, int max){
	this->top_left_corner = tlc;
	this->num_mushrooms = 0;
	this->num_tomatoes = 0;
	this->width = w;
	this->height = h;
	this->min_vegetables = min;
	this->max_size = max;
	this->completed = false;
	this->empties = false;
	this->lookForMushrooms();
	this->lookForTomatoes();
	this->checkSlice();
}

void Slice::lookForMushrooms(void){
	int mushrooms = 0;
	for (int i = 0; i < this->height; i++){
		for (int j = 0; j < this->width; j++){
			if (i + this->top_left_corner.x < (int)pizza.size()
					&& j + this->top_left_corner.y < (int)pizza[0].size()){
				if (pizza[i + this->top_left_corner.x][j + this->top_left_corner.y] == 'M'){
					mushrooms ++;
				} else if (pizza[i + this->top_left_corner.x][j + this->top_left_corner.y] == 'V'){
					this->empties = true;
				}
			}
		}
	}
	this->num_mushrooms = mushrooms;
}

void Slice::lookForTomatoes(void){
	int tomatoes = 0;
	for (int i = 0; i < this->height; i++){
		for (int j = 0; j < this->width; j++){
			if (i + this->top_left_corner.x < (int)pizza.size()
					&& j + this->top_left_corner.y < (int)pizza[0].size()){
				if (pizza[i + this->top_left_corner.x][j + this->top_left_corner.y] == 'T'){
					tomatoes ++;
				} else if (pizza[i + this->top_left_corner.x][j + this->top_left_corner.y] == 'V'){
					this->empties = true;
				}
			}
		}
	}
	this->num_tomatoes = tomatoes;

	//		for (int i = 0; i < this->height; i++){
	//			for (int j = 0; j < this->width; j++){
	//				cout << pizza[i + this->top_left_corner.x][j + this->top_left_corner.y];
	//			}
	//			cout << endl;
	//		}
}

bool Slice::checkSlice() {
	//		if (this->num_mushrooms > this->min_vegetables) cout << "mushrooms ok";
	//		if (this->num_tomatoes > this->min_vegetables) cout << "tomatoes ok";
	this->completed = !this->empties && (this->num_mushrooms >= this->min_vegetables) && (this->num_tomatoes >= this->min_vegetables);
	return this->completed;
}

bool Slice::isCompleted() const {
	return this->completed;
}

void Slice::setCompleted(bool completed) {
	this->completed = completed;
}

int Slice::getHeight() const {
	return this->height;
}

void Slice::setHeight(int height) {
	this->height = height;
}

int Slice::getMaxSize() const {
	return this->max_size;
}

void Slice::setMaxSize(int maxSize) {
	max_size = maxSize;
}

int Slice::getNumMushrooms() const {
	return num_mushrooms;
}

int Slice::getNumTomatoes() const {
	return num_tomatoes;
}

int Slice::getWidth() const {
	return this->width;
}

void Slice::setWidth(int width) {
	this->width = width;
}

string Slice::toString(void) {
	string slice;
	slice = to_string(top_left_corner.x) + " " + to_string(top_left_corner.y) + " "
			+ to_string(top_left_corner.x + height -1)+ " " + to_string(top_left_corner.y + width - 1) + "\n";
	cout << slice;
	return slice;
}

coord Slice::getTopLeftCorner() const {
	return top_left_corner;
}

void Slice::setTopLeftCorner(coord topLeftCorner) {
	top_left_corner = topLeftCorner;
}

bool Slice::expandibleN(void){
	bool exp = false;
	bool libre = true;
	bool space = (width * height + width) < max_size;

	if (!space) return false;
	else {
		for (int i = 0; i < width; i++){
			if (this->top_left_corner.x - 1 >= 0){
				if(pizza[this->top_left_corner.x - 1][this->top_left_corner.y + i] == 'A') exp = true;
				if(pizza[this->top_left_corner.x - 1][this->top_left_corner.y + i] == 'V') libre = false;
			}
		}
		return exp && libre;
	}
}

bool Slice::expandibleS(void){
	bool exp = false;
	bool libre = true;
	bool space = (width * height + width) <= max_size;

	if (!space){
		//			cout << "not enough space" << endl;
		return false;
	}
	else {
		for (int i = 0; i < width; i++){
			if (this->top_left_corner.x + height < (int)pizza.size()){
				//					cout << "pizza[" << this->top_left_corner.x + height << "][" << this->top_left_corner.y + i << "]" << endl;
				if(pizza[this->top_left_corner.x + height][this->top_left_corner.y + i] == 'A'){
					exp = true;
				}
				if(pizza[this->top_left_corner.x + height][this->top_left_corner.y + i] == 'V'){
					libre = false;
				}
			}
		}
		return exp && libre;
	}
}

bool Slice::expandibleE(void){
	bool exp = false;
	bool libre = true;
	bool space = (width * height + height) < max_size;

	if (!space) return false;
	else {
		for (int i = 0; i < height; i++){
			if (this->top_left_corner.y + width < (int)pizza[0].size()){
				if(pizza[this->top_left_corner.x + i][this->top_left_corner.y + width] == 'A') exp = true;
				if(pizza[this->top_left_corner.x + i][this->top_left_corner.y + width] == 'V') libre = false;
			}
		}
		return exp && libre;
	}
}

bool Slice::expandibleW(void){
	bool exp = false;
	bool libre = true;
	bool space = (width * height + height) < max_size;

	if (!space) return false;
	else {
		for (int i = 0; i < height; i++){
			if (this->top_left_corner.y - 1 >= 0){
				if(pizza[this->top_left_corner.x + i][this->top_left_corner.y - 1] == 'A') exp = true;
				if(pizza[this->top_left_corner.x + i][this->top_left_corner.y - 1] == 'V') libre = false;
			}
		}
		return exp && libre;
	}
}

void Slice::expandN(void){
	this->top_left_corner.x --;
	this->height ++;
	for (int i = 0; i < width; i++){
		//			cout << "pizza[" << this->top_left_corner.x << "][" << this->top_left_corner.y + i << "]" << endl;
		pizza[this->top_left_corner.x][this->top_left_corner.y + i] = 'V';
	}
}

void Slice::expandS(void){
	this->height ++;
	for (int i = 0; i < width; i++){
		//				cout << "pizza[" << this->top_left_corner.x + height - 1 << "][" << this->top_left_corner.y + i << "]" << endl;
		pizza[this->top_left_corner.x + height - 1][this->top_left_corner.y + i] = 'V';
	}
}

void Slice::expandE(void){
	this->width ++;
	for (int i = 0; i < height; i++){
		//				cout << "pizza[" << this->top_left_corner.x + i << "][" << this->top_left_corner.y + width - 1 << "]" << endl;
		pizza[this->top_left_corner.x + i][this->top_left_corner.y + width - 1] = 'V';
	}
}

void Slice::expandW(void){
	this->top_left_corner.y --;
	this->width ++;
	for (int i = 0; i < height; i++){
		//				cout << "pizza[" << this->top_left_corner.x + i << "][" << this->top_left_corner.y << "]" << endl;
		pizza[this->top_left_corner.x + i][this->top_left_corner.y ] = 'V';
	}
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

void asignaVecinos (coord actual, Slice & best_slice, bool & cambiado, vector<int> mul, int n_rows, int n_cols, int n_max, int n_min) {
//	cout << "actual: " << actual.x << ", " << actual.y << endl;
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
							Slice intento (n_corner, rows,  n, n_min, n_max);
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
							Slice intento (n_corner, n,  cols, n_min, n_max);
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

void expand (vector<Slice> & slices) {
//	cout << "Expand!" << endl;
	for (int i = 0; i < (int)slices.size(); i++){
//		cout << "Slice " << i << endl;
		if (slices[i].expandibleN()){
//			cout << "Expandible N" << endl;
			slices[i].expandN();
		}// else cout << "n_e_N" << endl;
		if (slices[i].expandibleS()){
//			cout << "Expandible S" << endl;
			slices[i].expandS();
		}// else cout << "n_e_S" << endl;
		if (slices[i].expandibleE()){
//			cout << "Expandible E" << endl;
			slices[i].expandE();
		}// else cout << "n_e_E" << endl;
		if (slices[i].expandibleW()){
//			cout << "Expandible W" << endl;
			slices[i].expandW();
		}// else cout << "n_e_W" << endl;

//		cout << " - " << i << endl;
	}
}

vector<vector<int> > matrizValores (int rows, int cols){
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

void leeFichero(string name, int & rows, int & cols, int & min, int & max){
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

	pizza = vector<vector<char> > (rows, vector<char> (cols, 0));

	for (int i = 0; i < rows; i++){ // To get you all the lines.
		getline(infile,linea); // Saves the line in STRING.
		for (int j = 0; j < cols; j++){
			pizza[i][j] = linea.at(j);
			cout << pizza[i][j];
		}
		cout<< endl;
	}
}

void cutPizza (Slice best_slice){
	for (int i = 0; i < best_slice.getHeight(); i++){
		for (int j = 0; j < best_slice.getWidth(); j++){
			pizza[i + best_slice.getTopLeftCorner().x][j + best_slice.getTopLeftCorner().y] = 'V';
		}
	}
}

void lonelyPizza (coord actual){
	pizza[actual.x][actual.y] = 'A';
}

void printPizza(){
	for (int i = 0; i < (int)pizza.size(); i++){ // To get you all the lines.
		for (int j = 0; j < (int)pizza[0].size(); j++){
			cout << pizza[i][j];
		}
		cout<< endl;
	}
}

void checkSuccess(){
	int n_rows = (int)pizza.size();
	int n_cols = (int)pizza[0].size();
	int in_slice = 0, out_slice = 0;
	for (int i = 0; i < n_rows; i++){ // To get you all the lines.
		for (int j = 0; j < n_cols; j++){
			if (pizza[i][j] == 'V') in_slice ++;
			else if (pizza[i][j] == 'A') out_slice ++;
		}
	}

	cout << "Num in slice : " << ((float)in_slice / (float)(n_cols*n_rows))*100 << "%" << endl;
	cout << "Num out slice : " << ((float)out_slice / (float)(n_cols*n_rows))*100 << "%" <<  endl;

}
