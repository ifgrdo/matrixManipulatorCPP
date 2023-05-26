#ifndef FCmatrix_H
#define FCmatrix_H
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "../../exercicio41/src/Vec.h"
#include "../../exercicio41/src/FCtools.h"
using namespace std;

class FCmatrix{
protected:
	vector<Vec> M{}; //the matrix is a vector of Vec objects...
	string classname; //give the class a name...
public:
	//constructors
	FCmatrix();
	FCmatrix(double **fM, int fm, int fn);//matrix fm x fn given from pointer of pointers
	FCmatrix(double *fM, int fm, int fn);//matrix fm x fn given as single pointer 
	FCmatrix(vector<Vec> v);//matrix fm x fn given as vector of Vec
	~FCmatrix(){};

	//operators
	virtual Vec& operator[] (int x) = 0;//get a row by giving índex inside []

	//methods
	virtual int Get_nRows() const = 0;//number of rows of M
	virtual int Get_nCols() const = 0;//number of columns of M
	virtual Vec GetRow(int i) const = 0;// retrieve row i
	virtual Vec GetCol (int i) const = 0;// retrieve column i
	virtual double Determinant() const = 0; //determinant of the matrix

	virtual int GetRowMax(int i) const = 0; // in row-i, return column-index of max element (in absolute value)
	virtual int GetColMax(int i) const = 0; // in column-j, return row-index (>=j) for which relative amplitude of Mij on the row is highest.
	virtual Vec Get_ld() const = 0;
	virtual Vec Get_md() const = 0;
	virtual Vec Get_ud() const = 0;

	virtual void Print() const = 0;

	void get_classname();

};

#endif
