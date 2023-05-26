#include "FCtools.h"
using namespace std;

FCTools::FCTools(){}

vector<string> FCTools::ReadFile2String(string str){
	vector<string> matrix_s;
	string line;
	ifstream file(str);

	while(1){
		getline(file, line);
		if(line == "")
			break;
		matrix_s.push_back(line);
	}

	file.close();
	return matrix_s;
}


vector<Vec> FCTools::ReadFile2Vec(string str){
	vector<Vec> matrix_v;
	//vector<string> matrix_s = ReadFile2String(str);
	string s;
	vector<double> line;

	ifstream file(str);
	ifstream file1(str);
	ifstream file2(str);

	int num_line=0, num_col=0, num_items=0;

	while(1){
		getline(file, s);
		if(s == "")
			break;

		++num_line;
	}

	double value;
	while(file1 >> value){
		++num_items;
	}

	num_col = num_items/num_line;

	double array[num_col];

	for(int i=0; i<num_line; ++i){
		for(int j=0; j<num_col; ++j){
			file2 >> array[j];
		}
		matrix_v.push_back(Vec(num_col, array));
	}

	file.close();
	file1.close();
	file2.close();
	return matrix_v;
}

Vec* FCTools::ReadFile(string str){
	Vec *matrix_p;
	vector<Vec> matrix_v = ReadFile2Vec(str);
	int num_line, num_col;

	ifstream file(str);

	num_line = matrix_v.size();
	num_col = matrix_v.at(1).size();

	matrix_p = new Vec[num_line];

	double array[num_col];

	for(int i=0; i<num_line; ++i){
		for(int j=0; j<num_col; ++j){
			file >> array[j];
		}
		matrix_p[i].SetEntries(num_col, array);
	}

	/*for(int i=0; i<num_line; ++i){
		Vec copy(matrix_v.at(i));
		matrix_p[i](copy);
	}*/

	file.close();
	return matrix_p;
}