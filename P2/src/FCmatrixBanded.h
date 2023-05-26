#ifndef FCmatrixBanded_H
#define FCmatrixBanded_H
#include "FCmatrix.h"
#include "FCmatrixFull.h"
using namespace std;

class FCmatrixBanded: public FCmatrix{
public:
	//constructors
	FCmatrixBanded();
	FCmatrixBanded(double **fM, int fm, int fn);
	FCmatrixBanded(double *fM, int fm, int fn);
	FCmatrixBanded(vector<Vec> v);
	~FCmatrixBanded(){};

	//copy constructors
	FCmatrixBanded(const FCmatrixBanded &copy);

	//operators
	FCmatrixBanded operator=(const FCmatrix &mat);
	FCmatrixBanded operator+(const FCmatrix &mat) const; 
	FCmatrixBanded operator-(const FCmatrix &mat) const;
	FCmatrixFull operator*(const FCmatrix &mat) const;
	FCmatrixBanded operator*(double lambda) const;
	Vec operator*(const Vec &v) const;

	//operators
	Vec& operator[] (int x);

	//virtual inherited	
	int Get_nRows() const;
	int Get_nCols() const;
	Vec GetRow(int i) const;
	Vec GetCol (int i) const;
	double Determinant() const;

 	int GetRowMax(int i) const;
	int GetColMax(int i) const;
    Vec Get_ld() const;
    Vec Get_md() const;
    Vec Get_ud() const;

	void Print() const;

};

#endif