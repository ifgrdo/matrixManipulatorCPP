#include "FCmatrixFull.h"
using namespace std;

FCmatrixFull::FCmatrixFull() : FCmatrix(){}


FCmatrixFull::FCmatrixFull(double **fM, int fm, int fn) : FCmatrix(fM,fm,fn){
	for(int i=0; i<fm; ++i){
		Vec line(fn, fM[i]);
		M.push_back(line);
	}

	classname = "FCmatrixFull";
}


FCmatrixFull::FCmatrixFull(double *fM, int fm, int fn) : FCmatrix(fM, fm, fn){
	double line[fn];
	for(int i=0; i<fm; ++i){
		for(int j=0; j<fn; ++j){
			line[j] = fM[j+i*fn];
		}

		Vec lin(fn, line);
		M.push_back(lin);
	}
	classname = "FCmatrixFull";
}


FCmatrixFull::FCmatrixFull(vector<Vec> v) : FCmatrix(v){
	for(int i=0; i<v.size(); ++i){
		M.push_back(v.at(i));
	}

	classname = "FCmatrixFull";
}


//matriz que será obtida pela cópia de outra já existente
FCmatrixFull::FCmatrixFull(const FCmatrixFull &copy){
	for(int i=0; i<copy.Get_nRows(); ++i){
		M.push_back(copy.GetRow(i));
	}

	classname = "FCmatrixFull";
}


//operador = -> igualar uma matriz a outra já existente
FCmatrixFull FCmatrixFull::operator=(const FCmatrix &mat){
	if(this != &mat){
		for(int i=0; i<mat.Get_nRows(); ++i){
			M.push_back(mat.GetRow(i));
		}
	}
	return *this;
}


//operador + -> soma de matrizes
FCmatrixFull FCmatrixFull::operator+(const FCmatrix &mat) const{
	FCmatrixFull soma;

	if((Get_nRows() == mat.Get_nRows()) && (Get_nCols() == mat.Get_nCols())){

		for(int i=0; i<Get_nRows(); ++i){
			soma.M.push_back(GetRow(i) + mat.GetRow(i));
		}
	}

	return soma;	
}


//operador - -> subtração de matrizes
FCmatrixFull FCmatrixFull::operator-(const FCmatrix &mat) const{
	FCmatrixFull sub;

	if((Get_nRows() == mat.Get_nRows()) && (Get_nCols() == mat.Get_nCols())){

		for(int i=0; i<Get_nRows(); ++i){
			sub.M.push_back(GetRow(i) - mat.GetRow(i));
		}
	}
	return sub;
}


//operador * -> multiplicação entre matrizes
FCmatrixFull FCmatrixFull::operator*(const FCmatrix &mat) const{
	FCmatrixFull mult;
	if(Get_nCols() == mat.Get_nRows()){

		double line_final[mat.Get_nCols()];
		Vec line, col;
		double result;

		for(int i=0; i<Get_nRows(); ++i){
			for(int j=0; j<mat.Get_nCols(); ++j){
				result=0;
				line = GetRow(i);
				col = mat.GetCol(j);

				for(int k=0; k<Get_nCols(); ++k){
					result = result + line[k]*col[k];
				}
				
				line_final[j] = result;
			}
			
			Vec line_Final(mat.Get_nCols(), line_final);
			mult.M.push_back(line_Final);
		}
	}

	else
		cout << "Dimensões não compatíveis entre matrizes" << endl;

	return mult;
}


//operador * -> multiplicação por um escalar
FCmatrixFull FCmatrixFull::operator*(double lambda) const{
	FCmatrixFull mult_scalar(M);

	for(int i=0; i<Get_nRows(); ++i){
		for(int j=0; j<Get_nCols(); ++j){
			mult_scalar.M[i][j] = M[i][j] * lambda;
		}
	}

	return mult_scalar;
}


//operador * -> multiplicação por um vetor
Vec FCmatrixFull::operator*(const Vec &v) const{
	Vec v_final;
	if(Get_nCols() == v.size()){
		double array[Get_nRows()];
		double result;

		for(int i=0; i<Get_nRows(); ++i){
			result=0;
			for(int j=0; j<Get_nCols(); ++j){
				result = result + M[i][j] * v[j];
			}
			array[i] = result;
		}

		Vec v_result(Get_nRows(), array);
		v_final = v_result;
	}

	else
		cout << endl << "Dimensões não compatíveis entre a matriz e o vetor" << endl;

	return v_final;
}


//operador []
Vec& FCmatrixFull::operator[] (int x){
	return M.at(x);
}


int FCmatrixFull::Get_nRows() const{
	return M.size();
}


int FCmatrixFull::Get_nCols() const{
	return M[0].size();
}


Vec FCmatrixFull::GetRow(int i) const{
	return M[i];
}


//para criar um objeto da classe Vec a que estará associado um vetor coluna de uma determinada matriz
Vec FCmatrixFull::GetCol(int i) const{
	double coluna[Get_nRows()];
	for(int j=0; j<Get_nRows(); ++j){
		coluna[j] = M[j][i]; 	
	}

	Vec col(Get_nRows(), coluna);
	return col;
}


//cálculo do determinante de uma matriz
double FCmatrixFull::Determinant() const{
	double det=0;
	//cout << "row: " << Get_nRows() << "  col: " << Get_nCols() << endl;

    //primeiro, é necessário que a matriz seja quadrada para que procedamos à determinação do detreminante
	if(Get_nRows() == Get_nCols()){
	//o método aqui apresentado para calcular o determinante de uma matriz dada foi inspirado na fórmula de Laplace
		for(int k=0; k<Get_nRows(); ++k){
			vector<Vec> matrix_reduz;
			double new_line[Get_nCols()-1];

            //pelo método de Laplace, o valor do determinante pode ser calculado eliminando consecutivamente linhas e colunas de matrizes, calculando o determinante de submatrizes, e proceder ao somatório dos valores obtidos.
            //o que é feito a seguir tem como objetivo proceder à criação de uma matriz reduzida.
			if(M[k][0]!=0){

				if(k!=0){

					for(int j=0; j<k; ++j){
						for(int i=1; i<Get_nCols(); ++i){
							new_line[i-1] = M[j][i];
						}

						Vec line_antes(Get_nCols()-1, new_line);
						matrix_reduz.push_back(line_antes);
					}
				}

				for(int j=k+1; j<Get_nRows(); ++j){
					for(int i=1; i<Get_nCols(); ++i){
						new_line[i-1] = M[j][i];
					}

					Vec line_after(Get_nCols()-1, new_line);
					matrix_reduz.push_back(line_after);
				}

				FCmatrixFull matrix_final(matrix_reduz);

				double aux=0;
            	//k foi fixado, pelo que resta multiplicar a componente M[k][0] pelo determinante da matriz reduzida que se obtém eliminando a linha e coluna k da matriz (não esquecendo o fator pow(-1,k+2) ) para obter aux. Depois disso varia-se k (uma iteração) e volta-se a proceder da mesma forma para determinar det = det + aux . Faz-se isto até que é atingida a última linha da matriz.
				if(Get_nRows()>1){
					aux = pow(-1,k+2) * M[k][0] * matrix_final.Determinant();
					det = det + aux;
				}

				else{
					aux = det + M[0][0];
					det = det + aux;
				}
			}
		}
	}

	else
		cout << "Matriz não quadrada: retornou 0";

	return det;
}


//determinação do valor máximo (absoluto) de uma determinada linha de uma matriz
int FCmatrixFull::GetRowMax(int i) const{
	int max=0, pos;

	if(i>=0 && i<Get_nRows()){
		Vec line = GetRow(i);

		for(int k=0; k<line.size(); ++k){
			if(abs(line[k]) > max){
				max = abs(line[k]);
				pos = k;
			}
		}
	}

	return pos;
}


//determinação do valor máximo (absoluto) de uma determinada coluna de uma matriz
int FCmatrixFull::GetColMax(int i) const{
	int max=0, pos;

	if(i>=0 && i<Get_nCols()){
		Vec col = GetCol(i);

		for(int k=0; k<col.size(); ++k){
			if(abs(col[k]) > max){
				max = abs(col[k]);
				pos = k;
			}
		}
	}

	return pos;
}


Vec FCmatrixFull::Get_ld() const{//get lower diagonal 
	Vec diagonal;

	if(Get_nCols() != Get_nRows())
		cout << "A matriz não é quadrada!" << endl; 

	else{
		double diag[Get_nCols()-1];

		for(int i=1; i<Get_nCols(); ++i){
			diag[i-1] = M[i][i-1];
		}

		Vec aux(Get_nCols()-1, diag);
		diagonal = aux;
	}

	return diagonal;
}


Vec FCmatrixFull::Get_md() const{//get diagonal
	Vec diagonal;

	if(Get_nCols() != Get_nRows())
		cout << "A matriz não é quadrada!" << endl; 

	else{
		double diag[Get_nCols()];

		for(int i=0; i<Get_nCols(); ++i){
			diag[i] = M[i][i];
		}

		Vec aux(Get_nCols(), diag);
		diagonal = aux;
	}

	return diagonal;
}


Vec FCmatrixFull::Get_ud() const{//get upper diagonal
	Vec diagonal;

	if(Get_nCols() != Get_nRows())
		cout << "A matriz não é quadrada!" << endl; 

	else{
		double diag[Get_nCols()-1];

		for(int i=0; i<Get_nCols()-1; ++i){
			diag[i] = M[i][i+1];
		}

		Vec aux(Get_nCols()-1, diag);
		diagonal = aux;
	}

	return diagonal;
}


void FCmatrixFull::Print() const{

	for(int i=0; i<Get_nRows(); ++i){
		Vec l = GetRow(i);
		l.Print();
	}

	cout << endl;
}


void FCmatrixFull::swapRows(int i, int j){
	if(i>=0 && i<Get_nRows() && j>=0 && j<Get_nRows()){
		Vec aux = M[i];
		M[i] = M[j];
		M[j] = aux;
	}

	else
		cout << "Linha não encontrada!" << endl;
}


void FCmatrixFull::SetRow(Vec v){
	M.push_back(v);
}