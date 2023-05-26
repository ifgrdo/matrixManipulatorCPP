#ifndef Vec_H
#define Vec_H
#include <iostream>
#include <cstdlib>
#include <vector>	
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

class Vec{
private:
	int N;
	double *entries;

public:
	Vec();
	Vec(int num1, double num2);
	Vec(int num1);
	Vec(int num1, double v[]);
	Vec(const Vec &copy);
	~Vec(){
		delete [] entries;
	}

	Vec operator+(const Vec &v);
	Vec operator-(const Vec &v);
	Vec& operator=(const Vec &v);
	Vec& operator+=(const Vec &v);
	Vec& operator-=(const Vec &v);
	double& operator[](int x);
	double operator[](int x) const;
	Vec operator*(const Vec &v);
	Vec operator*(const double &scalar);
	Vec operator-(const double &scalar);

	void Print();
	int size() const;
	int size();

	void Print_N();
	void SetEntries (int n, double v[]);
	double dot (const Vec &v);
	void swap(int n, int m);
};

#endif


