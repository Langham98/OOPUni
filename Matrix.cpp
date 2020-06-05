#include "stdafx.h"
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Base_Image.h"
#include <fstream>

using namespace std;

//desructor
Matrix::~Matrix() {
	cout << "Matrix destructor called" << endl;
}

//getting the rows and cols constructor
Matrix::Matrix(int rows, int columns) {
	length = columns;
	height = rows;

	cout << "Matrix constructor called with columns " << length << " and rows " << height << endl;
}



//creates the matrix by taking a 1d array and running through 2 for loops to enter the values
double** Matrix::CreationMat(double array[], int height, int length) {
	cout << "Creation of matrix called" << endl;

	double** matrix = nullptr;
	matrix = new double*[height];

	for (int h = 0; h < height; h++) {
		matrix[h] = new double[length];
		for (int l = 0; l < length; l++) {
			matrix[h][l] = array[(h*length) + l];
		}

	}
	return matrix;
}
//function definitions for changing the operators
void Matrix::operator+() {
	length = 36;
	height = 49;
}

void Matrix::operator-() {
	length = 1024;
	height = 768;
}

//switch matrix, turning a 2d array matrix into a 1d vector

vector<double> Matrix::switchMatrix(double **mat) {

	vector<double> newVect;
	cout << "Switch matrix working..." << endl;

	for (int i = 0; i <= height; i++) {
		for (int j = 0; j <= length; j++) {
			newVect.push_back(mat[i][j]);
		}
	}
	cout << "Switch matrix fully switched.." << endl;
	return newVect;

}