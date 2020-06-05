#pragma once


#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;






class Base_Image {

private:
	int i, j;
	double sum, temp1, temp2, sqsum1, sqsum2, Wm, Sm;

protected:
	int size, RowC, ColumnC;

public:

	// Reads .txt file representing an image of R rows and C Columns stored in filename 
	// and converts it to a 1D array of doubles of size R*C
	// Memory allocation is performed inside readTXT
	// Read .txt file with image of size (R rows x C columns), and convert to an array of doubles
	static double* read_text(char *fileName, int sizeR, int sizeC)
	{
		double* data = new double[sizeR*sizeC];
		int i = 0;

		ifstream myfile(fileName);
		if (myfile.is_open())
		{

			while (myfile.good())
			{
				if (i > sizeR*sizeC - 1) break;

				myfile >> *(data + i);
				//cout << *(data + i) << ' '; // This line display the converted data on the screen, you may comment it out. 
				//cin >> Wallyarray[i];





			}
			myfile.close();
		}

		else cout << "Unable to open file";
		//cout << i;

		return data;
	}


	// Converts a 1D array of doubles of size R*C to .pgm image of R rows and C Columns
	// and stores .pgm in filename
	// Use Q = 255 for greyscale images and 1 for binary images.
	static void write_pgm(char *filename, vector<double> data, int sizeR, int sizeC, int Q)
	{
		int i, j;
		unsigned char *image;
		ofstream myfile;
		int Size = 786432;

		

		image = new unsigned char[Size];

		// convert the integer values to unsigned char


		

		for (i = 0; i < data.size(); i++) {
			image[i] = (unsigned char)data[i];

		}
		myfile.open(filename, ios::out | ios::binary | ios::trunc);

		if (!myfile) {
			cout << "Can't open file: " << filename << endl;
			exit(1);
		}

		myfile << "P5" << endl;
		myfile << sizeC << " " << sizeR << endl;
		myfile << Q << endl;

		myfile.write(reinterpret_cast<char *>(image), (Size) * sizeof(unsigned char));

		if (myfile.fail()) {
			cout << "Can't write image " << filename << endl;
			exit(0);
		}

		myfile.close();

		delete[] image;

	}


	float NCC(double** Wally, double** Section, int smallC, int smallR);
	double** circleImage(double** Full_Image, int xpos, int ypos);
	void deleteItem(double* item);
	void deleteItem(double** item, int h);
	~Base_Image();





};

class Ref_Image : public Base_Image {

private:
	int length, height, offsetx, offsety, counter1, counter2, check2, check1;
	double** tempmat;



public:

	Ref_Image();

	Ref_Image(int rows, int columns);
	double** getSection(double** Full_Image, int& Xoffset, int& Yoffset);

	~Ref_Image();
};

class Large_Image : public Base_Image {
	//getting the large image into a vector and outputting it
private:
	int length, height;
public:

	Large_Image();
	Large_Image(int rows, int columns);

	~Large_Image();
};

class Matrix {

private:
	int length, height, i, j;
	double* array;

public:
	Matrix(int rows, int columns);

	double** CreationMat(double array[], int height, int length);
	void operator- ();
	void operator+ ();
	vector<double> switchMatrix(double **mat);
	~Matrix();
};
