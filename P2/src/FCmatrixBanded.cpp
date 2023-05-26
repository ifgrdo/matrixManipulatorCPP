#include "FCmatrixBanded.h"
using namespace std;

FCmatrixBanded::FCmatrixBanded() : FCmatrix(){}

FCmatrixBanded::FCmatrixBanded(double **fM, int fm, int fn){
	if(fm!=fn)
		cout << "Matriz não quadrada" << endl;

	else{
		Vec diag_princ(fm, fM[1]);
		Vec diag_sup(fm-1, fM[0]);
		Vec diag_inf(fm-1, fM[2]);

		M.push_back(diag_sup);
		M.push_back(diag_princ);
		M.push_back(diag_inf);
	}

	classname = "FCmatrixBanded";
}


FCmatrixBanded::FCmatrixBanded(double *fM, int fm, int fn){
	if(fm!=fn)
		cout << "Matriz não quadrada" << endl;

	else{
		double d_sup[fm-1];
		double d_princ[fm];
		double d_inf[fm-1];

		for(int i=0; i<fm-1; ++i){
			d_sup[i] = fM[i];
			d_inf[i] = fM[i + 2*fm-1];
		}

		for(int i=0; i<fm; ++i){
			d_princ[i] = fM[i+fm-1];
		}

		Vec diag_princ(fm, d_princ);
		Vec diag_sup(fm-1, d_sup);
		Vec diag_inf(fm-1, d_inf);
		
		M.push_back(diag_sup);
		M.push_back(diag_princ);
		M.push_back(diag_inf);
	}

	classname = "FCmatrixBanded";

}


FCmatrixBanded::FCmatrixBanded(vector<Vec> v) : FCmatrix(){
	if(v.size() != 3)
		cout << endl << "Erro! O vetor deverá ter 3 Vecs - diagonal superior, diagonal principal e diagonal inferior" << endl;

	else{
		if((v.at(0).size() == v.at(2).size()) && (v.at(1).size() == v.at(0).size()+1)){
			for(int i=0; i<3; ++i){
				M.push_back(v.at(i));
			}

		}
		else
			cout << "O primeiro e o terceiro Vec deverão ter menos uma componente do que o segundo!" << endl; 
	}

	classname = "FCmatrixBanded";
}

FCmatrixBanded::FCmatrixBanded(const FCmatrixBanded &copy){
	M.push_back(copy.Get_ud());
	M.push_back(copy.Get_md());
	M.push_back(copy.Get_ld());

	classname = "FCmatrixBanded";
}


FCmatrixBanded FCmatrixBanded::operator=(const FCmatrix &mat){
	if(this != &mat){
		M.clear();
		
		M.push_back(mat.Get_ud());
		M.push_back(mat.Get_md());
		M.push_back(mat.Get_ld());
	}
	return *this;
}


FCmatrixBanded FCmatrixBanded::operator+(const FCmatrix &mat) const{
	FCmatrixBanded soma;

	if((Get_nRows() == mat.Get_nRows()) && (Get_nCols() == mat.Get_nCols())){
		soma.M.push_back(Get_ud() + mat.Get_ud());
		soma.M.push_back(Get_md() + mat.Get_md());
		soma.M.push_back(Get_ld() + mat.Get_ld());
	}

	return soma;
}


FCmatrixBanded FCmatrixBanded::operator-(const FCmatrix &mat) const{
	FCmatrixBanded sub;

	if((Get_nRows() == mat.Get_nRows()) && (Get_nCols() == mat.Get_nCols())){
		sub.M.push_back(Get_ud() - mat.Get_ud());
		sub.M.push_back(Get_md() - mat.Get_md());
		sub.M.push_back(Get_ld() - mat.Get_ld());
	}

	return sub;
}


FCmatrixFull FCmatrixBanded::operator*(const FCmatrix &mat) const{
	FCmatrixFull mult;

	if(Get_nCols() == mat.Get_nCols()){
		int dim = Get_nRows(); //ambas são matrizes quadradas
		double line_final[dim];
		Vec line, col;
		double result;

		for(int i=0; i<dim; ++i){
			for(int j=0; j<dim; ++j){
				result=0;
				line = GetRow(i);
				col = mat.GetCol(j);

				for(int k=0; k<dim; ++k){
					result = result + line[k]*col[k];
				}

				line_final[j] = result;
			}

			Vec line_Final(dim, line_final);
			mult.SetRow(line_Final);
		}
	}

	else
		cout << "Dimensões não compatíveis" << endl;

	return mult;
}


Vec FCmatrixBanded::operator*(const Vec &v) const{
	Vec v_final;
	if(Get_nCols() == v.size()){
		int dim = Get_nCols(); //quadrada
		Vec line;
		double array[dim];
		double result;

		for(int i=0; i<dim; ++i){
			result=0;
			line = GetRow(i);

			for(int j=0; j<dim; ++j){
				result = result + line[j] * v[j]; 
			}
			array[i] = result;
		}

		Vec v_result(dim, array);
		v_final = v_result;
	}

	else
		cout << "Dimensões não compatíveis" << endl;

	return v_final;
}


FCmatrixBanded FCmatrixBanded::operator*(double lambda) const{
	FCmatrixBanded mult_scalar;

	mult_scalar.M.push_back(Get_ud() * lambda);
	mult_scalar.M.push_back(Get_md() * lambda);
	mult_scalar.M.push_back(Get_ld() * lambda);

	return mult_scalar;
}


Vec& FCmatrixBanded::operator[] (int x){
	return M.at(x);
}


int FCmatrixBanded::Get_nRows() const{
	//corresponde ao tamanho da diagonal principal
	return M[1].size();
}


int FCmatrixBanded::Get_nCols() const{
	return M[1].size();
}


Vec FCmatrixBanded::GetRow(int i) const{
	Vec row;
	int dim = Get_nRows();

	if(i<0 || i>=dim)
		cout << "Linha não encontrada!" << endl;

	else{
		double line[dim];
		for(int i=0; i<dim; ++i){
			line[i] = 0;
		}

		if(i==0){
			line[0] = M[1][0]; //diagonal principal
			line[1] = M[0][0]; //diagonal superior;
		}

		else{
			if(i==dim-1){
				line[dim-1] = M[1][dim-1]; //diagonal principal
				line[dim-2] = M[2][dim-2]; //diagonal inferior 
			}

			else{
				line[i] = M[1][i]; //diagonal principal
				line[i-1] = M[2][i-1];
				line[i+1] = M[0][i];
			}
		}

		Vec row_f(dim, line);
		row = row_f; //igualar vetores
	}

	return row;
}


Vec FCmatrixBanded::GetCol (int i) const{
	Vec col;
	int dim = Get_nRows();

	if(i<0 || i>=dim)
		cout << "Coluna não encontrada!" << endl;

	else{
		double coluna[dim];
		for(int i=0; i<dim; ++i){
			coluna[i] = 0;
		}

		if(i==0){
			coluna[0] = M[1][0]; //diagonal principal
			coluna[1] = M[2][0]; //diagonal inferior;
		}

		else{
			if(i==dim-1){
				coluna[dim-1] = M[1][dim-1]; //diagonal principal
				coluna[dim-2] = M[0][dim-2]; //diagonal superior
			}

			else{
				coluna[i] = M[1][i]; //diagonal principal
				coluna[i-1] = M[0][i-1]; //diagonal superior
				coluna[i+1] = M[2][i]; //diagonal inferior
			}
		}

		Vec col_f(dim, coluna);
		col = col_f; //igualar vetores
	}

	return col;
}


double FCmatrixBanded::Determinant() const{
	double det=1;
	int i=1;
	double quoc;
	Vec d_sup = M[0];
	Vec d_princ = M[1];
	Vec d_inf = M[2];

	while(1){
		if(i == Get_nRows())
			break;

		quoc = d_inf[i-1] / d_princ[i-1];
		d_inf[i-1] = d_inf[i-1] - d_princ[i-1] * quoc; //fica a zero
		d_princ[i] = d_princ[i] - d_sup[i-1] * quoc;
		
		++i;
	}

	//multiplicação pivots
	for(int i=0; i<Get_nRows(); ++i){
		det = det * d_princ[i];
	}

	/*vector<Vec> after_det;
	after_det.push_back(d_sup);
	after_det.push_back(d_princ);
	after_det.push_back(d_inf);*/

	//FCmatrixBanded determ(after_det);
	//cout << "Escada de linhas: " << endl;
	//determ.Print();

	return det;
}


int FCmatrixBanded::GetRowMax(int i) const{
	int pos;
	int dim = Get_nRows();

	//Primeira linha
	if(i==0){
		if(abs(M[1][0]) >= abs(M[0][0]))
			pos=0;
		else
			pos=1;
	}

	else{
		//Linha final
		if(i==dim-1){
			if(abs(M[1][dim-1]) >= abs(M[2][dim-2]))
				pos=dim-1;

			else
				pos=dim-2;
		}
		//Linhas intermédias
		else{
			if((abs(M[2][i-1]) >= abs(M[1][i])) && (abs(M[2][i-1]) >= abs(M[0][i])))
				pos = i-1;

			else{
				if((abs(M[1][i]) >= abs(M[2][i-1])) && (abs(M[1][i]) >= abs(M[0][i])))
					pos = i;
				
				else
					pos = i+1;
			}
		}
	}

	return pos;
}


int FCmatrixBanded::GetColMax(int i) const{
	int pos;
	int dim = Get_nCols();

	//Primeira coluna
	if(i==0){
		if(abs(M[1][0]) >= abs(M[2][0]))
			pos=0;
		else
			pos=1;
	}

	else{
		//Linha final
		if(i==dim-1){
			if(abs(M[1][dim-1]) >= abs(M[0][dim-2]))
				pos=dim-1;

			else
				pos=dim-2;
		}
		//Linhas intermédias
		else{
			if((abs(M[2][i]) >= abs(M[1][i])) && (abs(M[2][i]) >= abs(M[0][i-1])))
				pos = i+1;

			else{
				if((abs(M[1][i]) >= abs(M[2][i])) && (abs(M[1][i]) >= abs(M[0][i-1])))
					pos = i;
				
				else
					pos = i-1;
			}
		}
	}
	return pos;
}


Vec FCmatrixBanded::Get_ld() const{
	return M[2];
}


Vec FCmatrixBanded::Get_md() const{
	return M[1];
}


Vec FCmatrixBanded::Get_ud() const{
	return M[0];
}


void FCmatrixBanded::Print() const{
	for(int i=0; i<Get_nRows(); ++i){
		Vec line = GetRow(i);
		line.Print();
	}

	cout << endl;
}



