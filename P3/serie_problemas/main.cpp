#include "EqSolver.h"
using namespace std;

int main(){
	/*

	//Main com vários testes

	//Eliminação de Gauss
	int ncol_0 = 7;
	int nlin_0 = 7;
	double array_0[nlin_0][ncol_0] = {{1,2,-1,0,1,0,3}, {1,3,2,1,1,3,4}, {1,1,-2,0,3,1,0}, {2,1,2,4,1,4,7}, {0,1,-1,2,0,4,1}, {1,1,1,1,2,1,2}, {2,-1,0,-1,2,5,7}};
	vector<Vec> v_0;

	for(int i=0; i<nlin_0; ++i){
		v_0.push_back(Vec(ncol_0, array_0[i]));
	}

	cout << endl << "Resolução do sistema Ax=b" << endl;
	FCmatrixFull matrix_0(v_0);
	cout << "Matriz A:" << endl;
	matrix_0.Print();
	cout << endl;

	//double det = matrix_0.Determinant();
	//cout << "Determinante da matriz: " << det << endl;

	double a[nlin_0] = {1,2,3,1,1,2,5};
	Vec v_coluna_0 (nlin_0,a);
	cout << "Vetor b:" << endl;
	v_coluna_0.Print();

	EqSolver solver_0(matrix_0, v_coluna_0);
	Vec solution_0 = solver_0.GaussEliminationSolver();
	
	if(solution_0.size() != 0){
		cout << endl << "Solução x: " << endl;
		solution_0.Print();
	}

	//Decomposição LU
	int ncol_1 = 7;
	int nlin_1 = 7;
	double array_1[nlin_1][ncol_1] = {{1,3,2,1,1,3,4}, {1,1,-2,0,3,1,0}, {2,1,2,4,1,4,7}, {0,1,-1,2,0,4,1}, {1,1,1,1,2,1,2}, {2,-1,0,-1,2,5,7}, {1,1,1,1,2,3,4}};
	vector<Vec> v_1;

	for(int i=0; i<nlin_1; ++i){
		v_1.push_back(Vec(ncol_1, array_1[i]));
	}

	FCmatrixFull matrix_1(v_1);
	
	double b[nlin_1] = {1,2,3,1,1,2,1};
	Vec v_coluna_1 (nlin_1,b);

	EqSolver solver_1(matrix_1, v_coluna_1);
	cout << endl << endl << "Decomposição LU" << endl;
	cout << "Matriz B:" << endl;
	matrix_1.Print();
	cout << "Vetor b:" << endl;
	v_coluna_1.Print();

	Vec solution_1 = solver_1.LUdecompositionSolver_Doolittle();

	if(solution_1.size() != 0){
		cout << endl << "Solução x: " << endl;
		solution_0.Print();
	}

	//Criar matriz banded sob a forma de matrixFull - o EqSolver aceita FCmatrixFull
	int ncol_2 = 6;
	int nlin_2 = 6;
	double array_2[nlin_2][ncol_2] = {{1,-1,0,0,0,0}, {4,2,0,0,0,0}, {0,3,3,2,0,0}, {0,0,1,4,1,0}, {0,0,0,0,5,2}, {0,0,0,0,2,6}};
	vector<Vec> v_2;

	for(int i=0; i<nlin_2; ++i){
		v_2.push_back(Vec(ncol_2, array_2[i]));
	}

	FCmatrixFull matrix_2(v_2);
	cout << endl << endl << "Thomas algorithm" << endl;
	cout << "Matriz C:" << endl;
	matrix_2.Print();

	double c[nlin_2] = {1,2,-1,2,3,5};
	Vec v_coluna_2 (nlin_2,c);
	cout << "Vetor b:" << endl;
	v_coluna_2.Print();
	
	EqSolver solver_2(matrix_2, v_coluna_2);
	Vec solution_2 = solver_2.TridiagonalSolver();

	if(solution_2.size() == 0)
		cout << endl << "Sem solução devido a indeterminação no algoritmo" << endl;

	else{
		cout << endl << "Solução x: " << endl;
		solution_2.Print();
	}*/



	//Main pedida

	//Sistema 1
	cout << endl << endl << "-------Sistema 1 -------" << endl ;
	double rows_1[3][3] = {{4,-2,1},{-2,4,-2},{1,-2,4}};
	vector<Vec> M1;

	for(int i=0; i<3; ++i){
		M1.push_back(Vec(3, rows_1[i]));
	}

	FCmatrixFull Matriz_1(M1);
	cout << endl << "Matriz 1: " << endl;
	Matriz_1.Print();

	double col_1[3] = {11,-16,17};
	Vec vetor_coluna_1(3, col_1);
	cout << "Vetor coluna 1:" << endl;
	vetor_coluna_1.Print();

	//Método 1
	EqSolver resolver_1_1(Matriz_1, vetor_coluna_1);
	Vec solut_1_1 = resolver_1_1.GaussEliminationSolver();
	cout << endl << "--Método de Eliminação de Gauss--" << endl;

	if(solut_1_1.size() != 0){
		cout << endl << "Solução x: " << endl;
		solut_1_1.Print();
	}

	//Método 2
	EqSolver resolver_1_2(Matriz_1, vetor_coluna_1);
	cout << endl << endl << "--Decomposição PA = LU--" << endl;
	Vec solut_1_2 = resolver_1_2.LUdecompositionSolver_Doolittle();

	if(solut_1_2.size() != 0){
		cout << endl << "Solução x: " << endl;
		solut_1_2.Print();
	}


	//Sistema 2
	//Declaração como banded para impressão
	cout << endl << endl << endl << "-------Sistema 2 -------" << endl ;
	vector <Vec> diagonal;
	double diag_sup[4] = {1,1,1,1};
	double diag_princ[5] = {-2,-2,-2,-2,-2};
	double diag_inf[4] = {1,1,1,1};

	diagonal.push_back(Vec(4, diag_sup));
	diagonal.push_back(Vec(5, diag_princ));
	diagonal.push_back(Vec(4, diag_inf));

	FCmatrixBanded Matriz_2(diagonal);
	cout << endl << "Matriz 2: " << endl;
	Matriz_2.Print();

	double col_2[5] = {1,2,3,4,5};
	Vec vetor_coluna_2(5, col_2);
	cout  << "Vetor coluna 2:" << endl;
	vetor_coluna_2.Print();

	//Para o EqSolver desenvolvido, a matriz tem que ser FCMatrixFull para o caso de LU e Gauss Elimination
	double rows_banded[5][5] = {{-2,1,0,0,0}, {1,-2,1,0,0}, {0,1,-2,1,0}, {0,0,1,-2,1}, {0,0,0,1,-2}};
	vector <Vec> MBand;

	for(int i=0; i<5; ++i){
		MBand.push_back(Vec(5, rows_banded[i]));
	}

	FCmatrixFull Matriz_Band(MBand);
	
	//Método 1
	EqSolver resolver_2_1(Matriz_Band, vetor_coluna_2);
	Vec solut_2_1 = resolver_2_1.GaussEliminationSolver();
	cout << endl << "--Método de Eliminação de Gauss--" << endl;

	if(solut_2_1.size() != 0){
		cout << endl << "Solução x: " << endl;
		solut_2_1.Print();
	}

	//Método 2
	EqSolver resolver_2_2(Matriz_Band, vetor_coluna_2);
	cout << endl << endl << "--Decomposição PA = LU--" << endl;
	Vec solut_2_2 = resolver_2_2.LUdecompositionSolver_Doolittle();

	if(solut_2_2.size() != 0){
		cout << endl << "Solução x: " << endl;
		solut_2_2.Print();
	}

	//Método 3 
	cout << endl << endl << "--Método de Thomas--" << endl;
	EqSolver resolver_2_3(Matriz_2, vetor_coluna_2);
	Vec solut_2_3 = resolver_2_3.TridiagonalSolver();

	if(solut_2_3.size() == 0)
		cout << endl << "Sem solução devido a indeterminação no algoritmo" << endl;

	else{
		cout << endl << "Solução x: " << endl;
		solut_2_3.Print();
	}



	//Sistema 3
	cout << endl << endl << endl << "-------Sistema 3 -------" << endl ;
	double rows_2[3][3] = {{2,-2,6},{-2,4,3},{-1,8,4}};
	vector<Vec> M3;

	for(int i=0; i<3; ++i){
		M3.push_back(Vec(3, rows_2[i]));
	}

	FCmatrixFull Matriz_3(M3);
	cout << endl << "Matriz 3: " << endl;
	Matriz_3.Print();

	double col_3[3] = {16,0,-1};
	Vec vetor_coluna_3(3, col_3);
	cout  << "Vetor coluna 3:" << endl;
	vetor_coluna_3.Print();

	//Método 1 
	EqSolver resolver_3_1(Matriz_3, vetor_coluna_3);
	Vec solut_3_1 = resolver_3_1.GaussEliminationSolver();
	cout << endl << "--Método de Eliminação de Gauss--" << endl;

	if(solut_3_1.size() != 0){
		cout << "Solução x: " << endl;
		solut_3_1.Print();
	}

	//Método 2
	EqSolver resolver_3_2(Matriz_3, vetor_coluna_3);
	cout << endl << endl << "--Decomposição PA = LU--" << endl;
	Vec solut_3_2 = resolver_3_2.LUdecompositionSolver_Doolittle();

	if(solut_3_2.size() != 0){
		cout << endl << "Solução x: " << endl;
		solut_3_2.Print();
	}

	return 0;
}