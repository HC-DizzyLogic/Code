/*
 * Slice.h
 *
 *  Created on: 23 feb. 2017
 *      Author: irenerrrd
 */

#ifndef SLICE_H_
#define SLICE_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct coord {
	int x;
	int y;
};

void leeFichero(string name, int & rows, int & cols, int & min, int & max);
vector<vector<int> > matrizValores(int rows, int cols);
vector<int> getMultiples (int num);
coord Vecino(int i, coord actual);

class Slice{
public:

	Slice(void);
	Slice(coord tlc, int t, int m, int h, int w, int min, int max, bool c, bool e);
	Slice(coord tlc, int h, int w, int min, int max);

	void lookForMushrooms(void);
	void lookForTomatoes(void);
	int getNumMushrooms() const;
	int getNumTomatoes() const;

	bool checkSlice();

	bool isCompleted() const;
	void setCompleted(bool completed);

	int getHeight() const;
	void setHeight(int height);

	int getWidth() const;
	void setWidth(int width);

	int getMaxSize() const;
	void setMaxSize(int maxSize);

	string toString(void);

	coord getTopLeftCorner() const;
	void setTopLeftCorner(coord topLeftCorner);

	bool expandibleN(void);
	bool expandibleS(void);
	bool expandibleE(void);
	bool expandibleW(void);
	void expandN(void);
	void expandS(void);
	void expandE(void);
	void expandW(void);

private:
	coord top_left_corner;
	int num_tomatoes;
	int num_mushrooms;
	int width;
	int height;
	int min_vegetables;
	int max_size;
	bool completed;
	bool empties;
};

void asignaVecinos(coord actual, Slice & best_slice, bool & cambiado, vector<int> mul, int n_rows, int n_cols, int n_max, int n_min);
void expand(vector<Slice> & slices);
void cutPizza (Slice best_slice);
void lonelyPizza (coord actual);
void printPizza();
void checkSuccess();

#endif /* SLICE_H_ */
