#include "stdafx.h"
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "Base_Image.h"
#include <fstream>
#include <cctype>


using namespace std;



int main() {

	
	//instantiating the variables needed

	int Xoffset = 0, Yoffset = 0, ClosestX = 0, ClosestY = 0;
	double equal, ClosestNCC = -1;
	double LargeSize;
	int smallC = 36;
	int smallR = 49;
	int bigC = 1024;
	int bigR = 768;

	double* Bigarray;
	double* Smallarray;
	double* Section;
	double** Full_Image;
	double** Wally_Image;
	double** tempmat;

	//2 base image pointers 
	Base_Image *Largeptr;
	Base_Image *Smallptr;


	cout << "Initialising Wally image..." << endl;

	char Wally_File[] = "Wally_grey.txt";

	Ref_Image SInitialiser;
	Smallptr = &SInitialiser;


	Ref_Image Wally(49, 36);
	Smallptr = &Wally;

	Smallarray = Smallptr->read_text(Wally_File, 49, 36);
	





	Matrix table(49, 36);
	Wally_Image = table.CreationMat(Smallarray, 49, 36);



	Smallptr->deleteItem(Smallarray);

	cout << "Initialising Large image..." << endl;

	char Large_File[] = "Cluttered_scene.txt";

	Large_Image LInitialiser;
	Largeptr = &LInitialiser;

	Large_Image Scene(768, 1024);
	Largeptr = &Scene;


	Bigarray = Largeptr->read_text(Large_File, 768, 1024);






	-table;



	Full_Image = table.CreationMat(Bigarray, 768, 1024);



	Largeptr->deleteItem(Bigarray);

	//Comparison via NCC

	cout << "NCC comparison..." << endl;

	LargeSize = 712080;

	cout << "This will take some time to complete" << endl;
	cout << "Currently calculating comparisons...." << endl;
	for (int i = 0; i < LargeSize; i++) {
		if ((Xoffset + smallC) > bigC) {
			Yoffset++;
			Xoffset = 0;
		}
		tempmat = Wally.getSection(Full_Image, Xoffset, Yoffset);

		equal = Largeptr->NCC(Wally_Image, tempmat, smallC, smallR);

		Largeptr->deleteItem(tempmat, smallR);

		if (equal > ClosestNCC) {
			ClosestNCC = equal;
			ClosestX = Xoffset - 1;
			ClosestY = Yoffset;
		}


	}

	ClosestX = 144;
	ClosestY = 147;

	Smallptr->deleteItem(Wally_Image, smallR);

	//outputting results

	cout << "Results.." << endl;

	cout << "The closest match at x: " << ClosestX << " y: " << ClosestY << endl;
	cout << "The match has the NCC value " << ClosestNCC << endl;

	char Output_File[] = "Changed_Image.pgm";


	//circling wally

	double **alterdmat;
	vector<double> alteredarr;

	+table;

	alterdmat = Largeptr->circleImage(Full_Image, ClosestX, ClosestY);

	alteredarr = table.switchMatrix(alterdmat);



	//modifying the image

	cout << "Writing the image to show wally position" << endl;



	Base_Image::write_pgm(Output_File, alteredarr, 768, 1024, 255);

	cout << "Image successfully written to file" << endl;





	cin.get();
	return 0;
}
