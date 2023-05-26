#ifndef EqSolver_H
#define EqSolver_H
#include <iostream>
#include <vector>
#include "../../exercicio41/src/Vec.h"
#include "../../exercicio41/src/FCtools.h"
#include "../../exercicio43/src/FCmatrix.h"
#include "../../exercicio43/src/FCmatrixFull.h"
#include "../../exercicio43/src/FCmatrixBanded.h"

using namespace std;

class EqSolver{
private:
	void GaussElimination(FCmatrixFull&, Vec&);
	FCmatrixFull *LUdecomposition_Doolittle(FCmatrixFull &);
	Vec TridiagonalThomas(FCmatrixBanded&, Vec&);
	FCmatrixFull M;
	FCmatrixBanded Band;
	Vec b;

public:
	EqSolver();
	EqSolver(const FCmatrixFull&, const Vec&);
	EqSolver(const FCmatrixBanded&, const Vec&);

	void SetConstants(const Vec&);
	void SetMatrix(const FCmatrixFull&);
	void SetMatrix(const FCmatrixBanded&);

	Vec GaussEliminationSolver();
	Vec LUdecompositionSolver_Doolittle();
	Vec TridiagonalSolver();

	FCmatrixFull Identity(int);

};

#endif