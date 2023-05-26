#ifndef FCmatrixFull_H
#define FCmatrixFull_H
#include "FCmatrix.h"
using namespace std;

class FCmatrixFull: public FCmatrix {
public:
	//constructors
	FCmatrixFull();
	FCmatrixFull(double **fM, int fm, int fn);
	FCmatrixFull(double *fM, int fm, int fn);
	FCmatrixFull(vector<Vec> v);
	~FCmatrixFull(){};

	//copy constructors
	FCmatrixFull(const FCmatrixFull &copy);

	//operators
	FCmatrixFull operator=(const FCmatrix &mat);
	FCmatrixFull operator+(const FCmatrix &mat) const; 
	FCmatrixFull operator-(const FCmatrix &mat) const;
	FCmatrixFull operator*(const FCmatrix &mat) const;
	FCmatrixFull operator*(double lambda) const;
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

	void swapRows(int l1, int l2);
	void SetRow(Vec v);

};

#endif
