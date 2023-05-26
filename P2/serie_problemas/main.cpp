#include <iostream>
#include <vector>
#include "FCmatrix.h"
#include "FCmatrixFull.h"
#include "FCmatrixBanded.h"
using namespace std;

int main(){
	//FCmatrixFull
	//Construtor 1
	int ncol_0 = 3;
	int nlin_0 = 5;
	double **m1;
	m1 = new double *[nlin_0];
	/*for(int i=0; i<nlin_0; ++i){
		m1[i] = new double[ncol_0];
	}*/

	double line1[3]={8,-2,1};
	double line2[3]={3,1,0};
	double line3[3]={3,1,-6};
	double line4[3]={7,0,7};
	double line5[3]={-2,-1,0};

	m1[0] = line1;
	m1[1] = line2;
	m1[2] = line3;
	m1[3] = line4;
	m1[4] = line5;

	FCmatrixFull matrix_0(m1, nlin_0, ncol_0);
	cout << endl << "-----------------FCmatrixFull----------------" << endl;
	cout << "Constructor 1" << endl << "Matrix_0: " << endl;
	matrix_0.Print();


	//Construtor 2
	int ncol_9 = 5;
	int nlin_9 = 3;
	double *m2;

	double m_line[ncol_9 * nlin_9] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	m2 = m_line;
	FCmatrixFull matrix_9(m2, nlin_9, ncol_9);
	cout << "Construtor 2" << endl << "Matrix_9: " << endl;
	matrix_9.Print();


	//Construtor 3
	int ncol_1 = 4;
	int nlin_1 = 4;
	double array_1[nlin_1][ncol_1] = {{1,-2,3,1}, {-1,0.5,4,1}, {1,1,1,-1}, {-5,0,0,1}};
	vector<Vec> v_1;

	for(int i=0; i<nlin_1; ++i){
		v_1.push_back(Vec(ncol_1, array_1[i]));
	}

	FCmatrixFull matrix_1(v_1);
	cout << endl << "Constructor 3 " << endl << "Matrix_1: " << endl;
	matrix_1.Print();

	cout << endl << "Número de linhas da Matrix_1: " << matrix_1.Get_nRows() << endl;
	cout << "Número de colunas da Matrix_1: " << matrix_1.Get_nCols() << endl << endl;

	cout << "GetRow - Matrix_1: " << endl;
	for(int i=0; i<4; ++i){
		cout << "Linha " << i+1 << ":  ";
		Vec l = matrix_1.GetRow(i);
		l.Print();
	}

	cout << endl << "GetCol - Matrix_1: " << endl;
	for(int i=0; i<4; ++i){
		cout << "Coluna " << i+1 << ":  ";
		Vec c = matrix_1.GetCol(i);
		c.Print();
	}

	cout << endl << "GetRowMax - Matrix_1:" << endl;
	for(int i=0; i<4; ++i){
		int max_line = matrix_1.GetRowMax(i);
		cout << "Linha " << i+1 << ": " << max_line << endl;
	}

	cout << endl << "GetColMax - Matrix_1:" << endl;
	for(int i=0; i<4; ++i){
		int max_col = matrix_1.GetColMax(i);
		cout << "Coluna " << i+1 << ": " << max_col << endl;
	}

	double det = matrix_1.Determinant();
	cout << endl << "Determinante da Matrix_1: " << det << endl;


cout << endl << "------------operações entre matrizes----------------" << endl;
	//Matrix_2
	int ncol_2 = 4;
	int nlin_2 = 4;
	double array_2[nlin_2][ncol_2] = {{1,0,3,4}, {1,1,1,0}, {-2,-2,-1,0}, {1,1,1,1}};
	vector<Vec> v_2;

	for(int i=0; i<nlin_2; ++i){
		v_2.push_back(Vec(ncol_2, array_2[i]));
	}

	cout << endl << "Matrix_1:" << endl;
	matrix_1.Print();

	FCmatrixFull matrix_2(v_2);
	cout << endl << "Matrix_2:" << endl;
	matrix_2.Print();

	cout << endl << "Matrix_1 + Matrix_2:" << endl;
	FCmatrixFull matrix_soma = matrix_1 + matrix_2;
	matrix_soma.Print();

	cout << endl << "Matrix_1 - Matrix_2:" << endl;
	FCmatrixFull matrix_sub = matrix_1 - matrix_2;
	matrix_sub.Print();

	cout << endl << "Matrix_1 * Matrix_2:" << endl;
	FCmatrixFull matrix_mult_1 = matrix_1 * matrix_2;
	matrix_mult_1.Print();


	//Matrix_3
	int ncol_3 = 4;
	int nlin_3 = 3;
	double array_3[nlin_3][ncol_3] = {{1,2,3,4}, {-1,-1,2,2}, {-2,-3,-1,5}};
	vector<Vec> v_3;

	for(int i=0; i<nlin_3; ++i){
		v_3.push_back(Vec(ncol_3, array_3[i]));
	}
	
	FCmatrixFull matrix_3(v_3);
	cout << endl << "Matrix_3:" << endl;
	matrix_3.Print();


	//Matrix_4
	int ncol_4 = 6;
	int nlin_4 = 4;
	double array_4[nlin_4][ncol_4] = {{1,0,-2,1,0,0}, {1,1,1,0,2,3}, {-2,-2,-1,0,1,8}, {1,1,1,1,1,1}};
	vector<Vec> v_4;

	for(int i=0; i<nlin_4; ++i){
		v_4.push_back(Vec(ncol_4, array_4[i]));
	}

	FCmatrixFull matrix_4(v_4);
	cout << endl << "Matrix_4:" << endl;
	matrix_4.Print();

	FCmatrixFull matrix_mult_2 = matrix_3 * matrix_4;
	cout << endl << "Matrix_3 * Matrix_4:" << endl;
	matrix_mult_2.Print();


	//swapRows
	matrix_4.swapRows(1,2);
	matrix_4.swapRows(2,3);
	cout << endl << "Matrix_4 após swap entre (linha 2, linha 3) e (linha 3, linha 4):" << endl;
	matrix_4.Print();


	//Igual matrizes e copy constructor
	FCmatrixFull matrix_5(matrix_4);
	cout << endl << "Matrix_5(Matrix_4):" << endl;
	matrix_5.Print();

	FCmatrixFull matrix_6 = matrix_4;
	cout << endl << "Matrix_6 = Matrix_4:" << endl;
	matrix_6.Print();


	//Multiplicar matriz por escalar
	cout << endl << "Matrix_7 = Matrix_6 * 2:" << endl;
	FCmatrixFull matrix_7 = matrix_6 * 2;
	matrix_7.Print();


	//Multiplicar matriz por vetor
	double a[6] = {1,2,3,4,5,6};
	Vec vetor_coluna1(6, a);
	cout << endl << "Vetor v1:" << endl;
	vetor_coluna1.Print();

	Vec matrix_8 = matrix_4 * vetor_coluna1;
	cout << endl << "Matrix_4 * v1: " << endl;
	matrix_8.Print();

	//Diagonais
	Vec md = matrix_2.Get_md();
	cout << endl << "Diagonal principal da matrix_2: " << endl;
	md.Print();

	Vec ud = matrix_2.Get_ud();
	cout << endl << "Diagonal superior da matrix_2: " << endl;
	ud.Print();

	Vec ld = matrix_2.Get_ld();
	cout << endl << "Diagonal inferior da matrix_2: " << endl;
	ld.Print();


	//FCmatrixBanded
	//Construtor 1
	int ncolb_0 = 3;
	int nlinb_0 = 3;
	double **b0;
	b0 = new double *[3]; //3 diagonais

	double b0_sup[nlinb_0-1]={0,1};
	double b0_princ[nlinb_0]={4,5,3};
	double b0_inf[nlinb_0-1]={2,3};

	b0[0] = b0_sup;
	b0[1] = b0_princ;
	b0[2] = b0_inf;

	FCmatrixBanded M_banded_0(b0, nlinb_0, ncolb_0);
	cout << endl << endl << "-----------------FCmatrixBanded----------------" << endl;
	cout << endl << "Construtor 1" << endl << "Matrix_banded_1:" << endl;
	M_banded_0.Print();


	//Construtor 2
	int ncolb_1 = 4;
	int nlinb_1 = 4;
	double *b1;

	double mat_diagonal[3*nlinb_1 - 2] = {3,1,2,4,5,3,1,2,3,6};
	b1 = mat_diagonal;

	FCmatrixBanded M_banded_1(b1, nlinb_1, ncolb_1);
	cout << endl << "Construtor 2" << endl << "Matrix_banded_2:" << endl;
	M_banded_1.Print();

	
	//Construtor 3
	vector<Vec> band;
	int dim = 4;
	double diag_sup[dim-1] = {-10,1,20};
	double diag_princ[dim] = {7,5,-30,1};
	double diag_inf[dim-1] = {21,3,6};

	band.push_back(Vec(dim-1, diag_sup));
	band.push_back(Vec(dim, diag_princ));
	band.push_back(Vec(dim-1, diag_inf));

	FCmatrixBanded M_banded_2(band);
	cout << endl << "Construtor 3" << endl << "Matrix_banded_3:" << endl;
	M_banded_2.Print();

	//GetRow, GetCol, GetRowMax, GetColMax
	Vec get_line;
	cout << endl << "GetRow - Matrix_banded_2:" << endl;
	for(int i=0; i<M_banded_1.Get_nRows(); ++i){
		get_line = M_banded_1.GetRow(i);
		cout << "Linha " << i+1 << ": ";
		get_line.Print();
	}

	Vec get_coluna;
	cout << endl << "GetCol -  Matrix_banded_2: " << endl;
	for(int i=0; i<M_banded_1.Get_nCols(); ++i){
		get_coluna = M_banded_1.GetCol(i);
		cout << "Coluna " << i+1 << ": ";
		get_coluna.Print();
	}

	cout << endl << "GetRowMax - Matriz_Banded_2: " << endl;
	for(int i=0; i<M_banded_1.Get_nRows(); ++i){
		cout << "Linha " << i+1 << ": " << M_banded_1.GetRowMax(i) << endl; 
	}

	cout << endl << "GetColMax - Matriz_Banded_2: " << endl;
	for(int i=0; i<M_banded_1.Get_nCols(); ++i){
		cout << "Linha " << i+1 << ": " << M_banded_1.GetColMax(i) << endl; 
	}


	//Copiar FCmatrixBanded
	FCmatrixBanded M_banded_3(M_banded_2);
	cout << endl << "Matrix_banded_4(Matrix_banded_3):" << endl;
	M_banded_3.Print();

	//Determinantes das 3 FCmatrixBanded
	int band_det_0 = M_banded_0.Determinant();
	cout << "Determinante da Matrix_banded_1: " << band_det_0 << endl;

	int band_det_1 = M_banded_1.Determinant();
	cout << "Determinante da Matrix_banded_2: " << band_det_1 << endl;

	int band_det_2 = M_banded_2.Determinant();
	cout << "Determinante da Matrix_banded_3: " << band_det_2 << endl;

	//Soma de FCmatrixBanded
	cout << endl << "Matrix_banded_2 + Matrix_banded_3:" << endl;
	FCmatrixBanded M_banded_4 = M_banded_1 + M_banded_2;
	M_banded_4.Print();

	//Subtração de FCmatrixBanded
	cout << endl << "Matrix_banded_2 - Matrix_banded_3:" << endl;
	FCmatrixBanded M_banded_5 = M_banded_1 - M_banded_2;
	M_banded_5.Print();

	//Multiplicação de FCmatrixBanded
	cout << endl << "Matrix_banded_2 * Matriz_Banded_3:" << endl;
	FCmatrixFull matrix_10 = M_banded_1 * M_banded_2;
	matrix_10.Print();

	//Multiplicação de FCmatrixBanded por um escalar
	cout << endl << "Matrix_banded_2 * 3:" << endl;
	FCmatrixBanded M_banded_7 = M_banded_1 * 3;
	M_banded_7.Print();

	//Multiplicação de FCmatrixBanded com vetor
	double v_b[4] = {1,-1,2,-2};
	Vec vetor_coluna2(4, v_b);
	cout << endl << "Vetor v2: " << endl;
	vetor_coluna2.Print();
	Vec solution = M_banded_1 * vetor_coluna2;
	cout << endl << "Matrix_banded_2 * v2:" << endl;
	solution.Print();




	//Main pedida no enunciado:
	cout << endl << "---------------main pedida no enunciado----------------" << endl;
	//Matriz A
	double A[3][4] = {{8,-2,1,4},{3,1,-3./2.,5},{1./2.,0,3,3}};
	vector <Vec> vA;

	for(int i=0; i<3; ++i){
		vA.push_back(Vec(4, A[i]));}

	FCmatrixFull MA(vA);
	cout << endl << "Matrix A:" << endl;
	MA.Print();


	//Matriz B
	double B[4][3] = {{2,-1,3}, {1,8,-1./2.}, {5./2., 6, 2}, {3,4,5}};
	vector <Vec> vB;

	for(int i=0; i<4; ++i){
		vB.push_back(Vec(3, B[i]));}

	FCmatrixFull MB(vB);
	cout << endl << "Matrix B:" << endl;
	MB.Print();

	double lambda=2.5;
	FCmatrixFull MC(MA*lambda);
	FCmatrixFull MD(MA*MB);

	cout << endl << "Matrix A * 2.5" << endl;
	MC.Print();
	cout << endl << "Matrix A * Matriz B" << endl;
	MD.Print();

	cout << "Determinante de (Matrix A * Matrix B)" << endl << MD.Determinant() << endl;

	cout <<  endl << "(Matriz A * 2.5) após swapRows(1,2)" << endl;
	MC.swapRows(1,2);
	MC.Print();

	//Desalocação de memória

	/*for(int i=0; i<nlin_0; ++i){
		delete m1[i];
	}*/

	delete [] m1;
	delete [] b0;

	return 0;
}
