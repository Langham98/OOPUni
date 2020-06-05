#include "stdafx.h"
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Base_Image.h"
#include <fstream>

using namespace std;

//constructors

Ref_Image::Ref_Image() {

	cout << "Ref_Image constructor..." << endl;
}


Ref_Image::Ref_Image(int rows, int columns) {
	length = columns;
	height = rows;
}

Large_Image::Large_Image() {

	cout << "Large_Image constructor..." << endl;

}

Large_Image::Large_Image(int rows, int columns) {
	length = columns;
	height = rows;
}






//Destructors
Base_Image::~Base_Image() {
	cout << "Base image destructor called" << endl;
};
Large_Image::~Large_Image() {
	cout << "Large image destructor called" << endl;
}
Ref_Image::~Ref_Image() {
	cout << "Ref image destructor called" << endl;
}

double** Ref_Image::getSection(double** Full_Image, int& Xoffset, int& Yoffset) {

	tempmat = nullptr;
	counter1 = 0;
	counter2 = 0;

	//upper limits

	check1 = height + Yoffset;
	check2 = length + Xoffset;

	//lower limits

	offsetx = Xoffset;
	offsety = Yoffset;

	tempmat = new double *[height];

	for (int h = offsety; h < check1; h++) {

		tempmat[counter1] = new double[length];
		counter2 = 0;

		for (int l = offsetx; l < check2; l++) {

			tempmat[counter1][counter2] = Full_Image[h][l];
			counter2++;
		}
		counter1++;
	}

	Xoffset++;
	return tempmat;
};



float Base_Image::NCC(double** Wally, double** Section, int smallC, int smallR) {
	sum = 0;
	temp1 = 0;
	temp2 = 0;
	sqsum1 = 0;
	sqsum2 = 0;
	Wm = 0;
	Sm = 0;
	size = smallC * smallR;

	for (int h = 0; h < smallR; h++) {
		for (int l = 0; l < smallC; l++) {
			temp1 += Wally[h][l];
		}
	}

	for (int h = 0; h < smallR; h++) {
		for (int l = 0; l < smallC; l++) {
			temp2 += Section[h][l];
		}
	}

	Wm = temp1 / size;
	Sm = temp2 / size;

	for (int x = 0; x < smallR; x++) {
		for (int y = 0; y < smallC; y++) {
			sum += (Wally[x][y] - Wm) * (Section[x][y] - Sm);
			sqsum1 += pow((Wally[x][y] - Wm), 2);
			sqsum2 += pow((Section[x][y] - Sm), 2);
		}
	}
	float result = (sum / (sqrt(sqsum1*sqsum2)));

	return result;
};

double** Base_Image::circleImage(double** Full_Image, int xpos, int ypos) {
	//Above
	for (int x = xpos; x <= (xpos + 36); x++) {
		Full_Image[ypos][x] = 0;
	}
	//Below
	for (int x = xpos; x <= (xpos + 36); x++) {
		Full_Image[(ypos + 50)][x] = 0;
	}
	//Left
	for (int y = ypos; y <= (ypos + 50); y++) {
		Full_Image[y][(xpos - 1)] = 0;
	}
	//Right
	for (int y = ypos; y <= (ypos + 50); y++) {
		Full_Image[y][(xpos + 37)] = 0;
	}
	return Full_Image;
};




void Base_Image::deleteItem(double *item) {
	delete[] item;
	item = nullptr;
}

void  Base_Image::deleteItem(double **item, int h) {

	for (int i = 0; i < h; i++) {
		delete[] item[i];

	}


	delete[] item;
	item = nullptr;


}