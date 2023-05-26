#ifndef FCtools_H
#define FCtools_H
#include <iostream>
#include <cstdlib>
#include <vector>	
#include <fstream>
#include <cmath>
#include "Vec.h"
using namespace std;

class FCTools{
public:
	FCTools();
	~FCTools(){};

	vector<string> ReadFile2String(string str);
	vector<Vec> ReadFile2Vec(string str);
	Vec* ReadFile(string str);
};
#endif