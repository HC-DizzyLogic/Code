#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

using namespace std;

struct coord {
	int x;
	int y;
};

class Slice{
public:

	Slice(void){
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
	}

	Slice(coord tlc, int t, int m, int w, int h, int min, int max, bool c){
		this->top_left_corner = tlc;
		this->num_mushrooms = m;
		this->num_tomatoes = t;
		this->width = w;
		this->height = h;
		this->min_vegetables = min;
		this->max_size = max;
		this->completed = c;
	}

	Slice(coord tlc, int w, int h, int min, int max, vector<vector<char> > pizza){
		this->top_left_corner = tlc;
		this->num_mushrooms = 0;
		this->num_tomatoes = 0;
		this->width = w;
		this->height = h;
		this->min_vegetables = min;
		this->max_size = max;
		this->completed = false;
		this->lookForMushrooms(pizza);
		this->lookForTomatoes(pizza);
		this->checkSlice();
	}

	void lookForMushrooms(vector<vector<char> > pizza){
		int mushrooms = 0;
		for (int i = 0; i < this->width; i++){
			for (int j = 0; j < this->height; j++){
				if (i + this->top_left_corner.x < (int)pizza.size()
						&& j + this->top_left_corner.y < (int)pizza[0].size()){
					if (pizza[i + this->top_left_corner.x][j + this->top_left_corner.y] == 'M'){
						mushrooms ++;
					}
				}
			}
		}
		this->num_mushrooms = mushrooms;
	}

	void lookForTomatoes(vector<vector<char> > pizza){
		int tomatoes = 0;
		for (int i = 0; i < this->width; i++){
			for (int j = 0; j < this->height; j++){
				if (i + this->top_left_corner.x < (int)pizza.size()
						&& j + this->top_left_corner.y < (int)pizza[0].size()){
					if (pizza[i + this->top_left_corner.x][j + this->top_left_corner.y] == 'T'){
						tomatoes ++;
					}
				}
			}
		}
		this->num_tomatoes = tomatoes;
	}

	bool checkSlice() {
		//		if (this->num_mushrooms > this->min_vegetables) cout << "mushrooms ok";
		//		if (this->num_tomatoes > this->min_vegetables) cout << "tomatoes ok";
		this->completed = (this->num_mushrooms > this->min_vegetables) && (this->num_tomatoes > this->min_vegetables);
		return this->completed;
	}

	bool isCompleted() const {
		return this->completed;
	}

	void setCompleted(bool completed) {
		this->completed = completed;
	}

	int getHeight() const {
		return this->height;
	}

	void setHeight(int height) {
		this->height = height;
	}

	int getMaxSize() const {
		return this->max_size;
	}

	void setMaxSize(int maxSize) {
		max_size = maxSize;
	}

	int getNumMushrooms() const {
		return num_mushrooms;
	}

	int getNumTomatoes() const {
		return num_tomatoes;
	}

	int getWidth() const {
		return this->width;
	}

	void setWidth(int width) {
		this->width = width;
	}

	void toString(void) {
		cout <<  "[" + to_string(top_left_corner.x) + ", " + to_string(top_left_corner.y) + "], ["
				+ to_string(top_left_corner.x + width -1)+ ", " + to_string(top_left_corner.y + height - 1) + "]" << endl;
	}
private:
	coord top_left_corner;
	int num_tomatoes;
	int num_mushrooms;
	int width;
	int height;
	int min_vegetables;
	int max_size;
	bool completed;
};
