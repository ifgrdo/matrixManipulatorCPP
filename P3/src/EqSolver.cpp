#include "EqSolver.h"
using namespace std;

int impossivel = 0; //Variável que testa se há ou não compatibilidade entre a matriz e o vetor do EqSolver
int Thomas_impossivel = 0; //Indeterminação no método de Thomas
FCmatrixFull multipl; //Matriz que guarda os multiplicadores da Eliminação de Gauss 
FCmatrixFull matrix_permutation; //Matriz de permutação
int is_Full;
int is_Banded;

//NOTA: GaussElimination e LUDecomposition apenas estão disponíveis no caso de FCMatrixFull
//      ThomasDecomposition apenas aceita Banded

EqSolver::EqSolver(){};


EqSolver::EqSolver(const FCmatrixFull &mat, const Vec &v){
	is_Full = 1;
	is_Banded = 0;

	//Verificar se a matriz e o vetor têm a mesma dimensão e se a matriz tem determinante nulo
	if(mat.Get_nRows() == mat.Get_nCols()){

		if(mat.Get_nRows() == v.size()){

			//if(mat.Determinant() !=0){ \\encontra-se em comentário para evitar esperar muito tempo para matrizes de grandes dimensões
			M = mat;
			b = v;
		}

		else{
			cout << "O número de linhas da matriz é diferente do número de componentes do vetor" << endl;
			impossivel = 1;
		}
	}

	else{
		cout << "Matriz não quadrada! O sistema não é possível e determinado" << endl;
		impossivel = 1;
	}
}


EqSolver::EqSolver(const FCmatrixBanded &mat, const Vec &v){
	is_Full = 0;
	is_Banded = 1;

	//Verificar se a matriz e o vetor têm a mesma dimensão e se a matriz tem determinante nulo
	if(mat.Get_nRows() == mat.Get_nCols()){

		if(mat.Get_nRows() == v.size()){

			//if(mat.Determinant() !=0){ \\encontra-se em comentário para evitar esperar muito tempo para matrizes de grandes dimensões
			Band = mat;
			b = v;
		}

		else{
			cout << "O número de linhas da matriz é diferente do número de componentes do vetor" << endl;
			impossivel = 1;
		}
	}

	else{
		cout << "Matriz não quadrada! O sistema não é possível e determinado" << endl;
		impossivel = 1;
	}
}


//Matriz identidade
FCmatrixFull EqSolver::Identity(int n){
	FCmatrixFull I;
	Vec line(n, 0.0);
	Vec nulo(n, 0.0);
	for(int i=0; i<n; ++i){
		line = nulo;
		line[i] = 1;
		I.SetRow(line);
	}

	return I;
}


void EqSolver::GaussElimination(FCmatrixFull &mat, Vec &v){
	double quoc;
	double max, pos;

	FCmatrixFull identity = Identity(mat.Get_nRows());
	multipl = identity; 	//Garantir que mult e matrix_permutation têm a mesma dimensão da matriz identidade
	matrix_permutation = identity;
	FCmatrixFull one_permutation; //Matriz de permutação individual

	for(int i=0; i<mat.Get_nRows(); ++i){ 	//determinação do máximo absoluto da coluna e troca respetiva
		if(i<mat.Get_nCols()){
			max = 0;
			for(int count=i; count < mat.Get_nRows(); ++count){
				if(abs(mat.GetCol(i)[count]) > max){
					pos = count;
					max = abs(mat.GetCol(i)[count]);
				}
			}

			if(pos!=i){ //caso o máximo da coluna se encontre numa linha abaixo da linha i, trocam-se as linhas
				mat.swapRows(i, pos);
				matrix_permutation.swapRows(i, pos);
				v.swap(i, pos);

				one_permutation = identity;
				one_permutation.swapRows(i, pos); //matriz de permutação necessária para alterar a posição das entradas da matriz multipl

				multipl = one_permutation * multipl; //troca de linha e de coluna
				multipl = multipl * one_permutation;
			}	
		}

		Vec line_princ = mat.GetRow(i);
		Vec line_sub;

		for(int j=i+1; j<mat.Get_nRows(); ++j){
			quoc = mat[j][i] / mat[i][i]; //quoc é o valor por que deve ser multiplicada a linha i de modo a obter um zero na linha j (j compreendido entre i+1 e o número de linhas da matriz).

			multipl[j][i] = quoc; //preenchimento da matriz dos multiplicadores

			line_sub = mat.GetRow(j);

			line_sub = line_sub - line_princ * quoc; //subtração
			mat[j] = line_sub;
			v[j] = v[j] - v[i] * quoc;
		}
	}

	//cout << endl << "Matriz em escada de linhas: " << endl;
    //mat.Print();
}


Vec EqSolver::GaussEliminationSolver(){
	Vec solution;

	if(impossivel == 0 && is_Banded==0 && is_Full==1){ //se todas as condições de tamanho e se det!=0

		GaussElimination(M, b); //chamar GaussElimination
		int tam = M.Get_nRows(); 
		double solut[tam];
		solut[tam-1] = b[tam-1] / M[tam-1][tam-1]; //última componente do vetor solução

		for(int i=tam-2; i>=0; --i){  //obter as restamtes componentes do vetor solução
			double total=0;
			for(int j=i+1; j<tam; ++j){
				total = total + M[i][j] * solut[j];
			}

			solut[i] = (b[i]-total) / M[i][i]; 
		}

		Vec sol(tam, solut);
		solution = sol;
	}

	return solution;
}


FCmatrixFull* EqSolver::LUdecomposition_Doolittle(FCmatrixFull &mat){

	FCmatrixFull *LU;
	LU = new FCmatrixFull[2];

	Vec v_gen(mat.Get_nRows());
	GaussElimination(mat, v_gen);

	if(impossivel==0){
		LU[1] = mat; //matriz U (obtém-se por Eliminação de Gauss)
		LU[0] = multipl; //matriz dos multiplicadores (variável global)
	}

	return LU;
}


Vec EqSolver::LUdecompositionSolver_Doolittle(){
	Vec solution;

	if(impossivel == 0 && is_Full==1 && is_Banded==0){
	
		FCmatrixFull *LU;
		Vec b_copy = b; //cópia do vetor coluna

		LU = LUdecomposition_Doolittle(M); //chamar LUdecomposition_Doolittle

		FCmatrixFull L(LU[0]);
		FCmatrixFull U(LU[1]);
		delete[] LU;

		cout << "Matriz L: " << endl;
		L.Print();

		cout << endl << "Matriz U: " << endl;
		U.Print();

		cout << endl << "Matriz P: " << endl;
		matrix_permutation.Print(); //matriz de permutação


		//Resolução Ly=Pb
		Vec y(b.size(), 0.0); //vetor y
		Vec b_permutated = matrix_permutation * b_copy; //obter Pb

		cout << "Vetor b após permutação" << endl;
		b_permutated.Print();

		for(int i=0; i<L.Get_nRows(); ++i){ //obter componentes do vetor y (de cima para baixo)
			y[i] = b_permutated[i] - L[i].dot(y);
		}

		cout << endl << "Vetor y: " << endl;
		y.Print();

		//Resolução Ux=y
		Vec sol(b.size(), 0.0); //vetor solução final
		for(int i=U.Get_nRows()-1; i>=0; --i){//obter componentes do vetor solução (de baixo para cima)
			sol[i] = (y[i] - U[i].dot(sol)) / U[i][i];
		}

		solution = sol;
	}

	return solution;
}


Vec EqSolver::TridiagonalThomas(FCmatrixBanded &mat, Vec &v){
	int tam = mat.Get_nCols(); 
	Vec thomas(2*tam-1, 0.0); //vetor que contém componentes c e componentes d
	double num, denum;

	//ciclo para c
	thomas[0] = mat[0][0] / mat[1][0];

	for(int i=1; i<tam-1; ++i){
		num = mat[0][i]; 
		denum = mat[1][i] - thomas[i-1]*mat[2][i-1];
		
		if(denum==0){ //impedir divisão por zero
			Thomas_impossivel = 1;
			cout << endl << "O algoritmo não pode ser aplicado - obteve-se denominador nulo!" << endl;
		}

		else
			thomas[i] = num/denum; //as componentes "c" vão ocupar a primeira parte do vetor thomas 
	}

	//ciclo para d
	Vec d(tam, 0.0);
	d[0] = v[0] / mat[1][0];

	for(int i=1; i<tam; ++i){
		num = v[i] - d[i-1] * mat[2][i-1];
		denum = mat[1][i] - thomas[i-1] * mat[2][i-1];
		
		if(denum==0){ //impedir divisão por zero
			Thomas_impossivel = 1;
			cout << endl << "O algoritmo não pode ser aplicado - obteve-se denominador nulo!" << endl;
		}
		else
			d[i] = num/denum;
	}

	//completar vetor - as componentes "d" vão ocupar a segunda metade do vetor thomas
	for(int i=0; i<tam; ++i){
		thomas[tam-1+i] = d[i];
	}

	if(Thomas_impossivel==1){ //se houver denominadores nulos, retorna vetor default
		Vec indetermination;
		return indetermination;
	}

	else
		return thomas;
}


Vec EqSolver::TridiagonalSolver(){

	if(impossivel == 0 && is_Banded==1 && is_Full==0){

		if(Band.Get_nRows() == 1){ //se a dimensão da matriz for 1, obtem-se a solução diretamente
			double sol = b[0]/Band[1][0]; //corresponde ao elemento da primeira linha e primeira coluna
			Vec solution(1, sol);
			return solution;
		}

		else{

			if (Band[1][0] == 0){
				cout << endl << "O algoritmo não pode ser aplicado - zero no primeiro elemento da diagonal principal" << endl;

				Vec indetermination;
				return indetermination;
			}

			else{
				Vec thomas = TridiagonalThomas(Band, b);
				int tam_c = (thomas.size()-1) / 2; //obter dimensão do vetor c
				int tam_d = thomas.size() - tam_c; //obter dimensão do vetor d

				Vec c(tam_c, 0.0);
				Vec d(tam_d, 0.0);

				for(int i=0; i<tam_c; ++i){
					c[i] = thomas[i];
				}

				for(int i=tam_c; i<thomas.size(); ++i){ //as componentes d encontravam-se na segunda parte do vetor thomas
					d[i-tam_c] = thomas[i];
				}

				/*cout << endl << "Vetor c:" << endl;
				c.Print();

				cout << endl << "Vetor d:" << endl;
				d.Print();*/

				Vec solution(tam_d, 0.0);
				solution[tam_d-1] = d[tam_d-1]; //obter solução final

				for(int i=tam_d-2; i>=0; --i){
					solution[i] = d[i] - solution[i+1] * c[i];
				}

				return solution;
			}
		}
	}

	else{
		Vec indetermination;
		return indetermination;
	}
}


void EqSolver::SetConstants(const Vec &v){
	b = v;
}


void EqSolver::SetMatrix(const FCmatrixFull &m_full){
	M = m_full;
}


void EqSolver::SetMatrix(const FCmatrixBanded &m_band){
	Band = m_band;
}


