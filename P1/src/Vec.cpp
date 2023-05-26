#include "Vec.h"
using namespace std;

Vec::Vec(){
	N = 0;
	entries = nullptr;
}


Vec::Vec(int num1, double num2){
	N = num1;
	entries = new double[N];

	for (int i=0; i<N; ++i){
		entries[i] = num2;
	}
}


Vec::Vec(int num1){
	N = num1;
	entries = new double[N];

	for (int i=0; i<N; ++i){
		entries[i] = 0;
	}
}


Vec::Vec(int num1, double v[]){
	N = num1;
	entries = new double[N];

	for (int i=0; i<N; ++i){
		entries[i] = v[i];
	}
}


Vec::Vec(const Vec &copy){
	N = copy.N;
	entries = new double[N];
	
	for (int i=0; i<N; ++i){
		entries[i] = copy.entries[i];
	}
}


Vec Vec::operator+(const Vec &v){
	Vec soma;
	if(N == v.N){
		soma.N = N;
		soma.entries = new double[N];

		for(int i=0; i<N; ++i){
			soma.entries[i] = entries[i] + v.entries[i];
		}
	}

	else
		cout << "Impossível somar" << endl;

	return soma;
}


Vec Vec::operator-(const Vec &v){
	Vec sub;
	if(N == v.N){
		sub.N = N;
		sub.entries = new double[N];

		for(int i=0; i<N; ++i){
			sub.entries[i] = entries[i] - v.entries[i];
		}
	}

	else
		cout << "Impossível subtrair" << endl;

	return sub;
}


Vec& Vec::operator=(const Vec &v){
	if(this != &v){
		delete [] entries;
		N = v.N;
		entries = new double[N];

		for(int i=0; i<N; ++i){
			entries[i] = v.entries[i];
		}
	}
	return *this;
}


Vec& Vec::operator+=(const Vec &v){
	if(N == v.N){
		for(int i=0; i<N; ++i){
			entries[i]+=v.entries[i];
		}
	}

	else
		cout << "Impossível! Tamanhos não compatíveis" << endl;
	return *this;
}


Vec& Vec::operator-=(const Vec &v){
	if(N == v.N){
		for(int i=0; i<N; ++i){
			entries[i]-=v.entries[i];
		}
	}

	else
		cout << "Impossível! Tamanhos não compatíveis" << endl;
	return *this;
}


double& Vec::operator[](int x){
	if(x>=0 && x<N)
		return entries[x];
	else{

		if(x<0){
			cout << "Erro! Foi retornado o valor entries[0]" << endl;
			return entries[0];
		}

		else{
			cout << "Erro! Foi retornado o valor entries[N-1]" << endl;
			return entries[N-1];
		}
	}
}

double Vec::operator[](int x) const{
	if(x>=0 && x<N)
		return entries[x];
	else{

		if(x<0){
			cout << "Erro! Foi retornado o valor entries[0]" << endl;
			return entries[0];
		}

		else{
			cout << "Erro! Foi retornado o valor entries[N-1]" << endl;
			return entries[N-1];
		}
	}
}



Vec Vec::operator*(const Vec &v){
	Vec mult;
	if(N == v.N){
		mult.N = N;
		mult.entries = new double[N];

		for(int i=0; i<N; ++i){
			mult.entries[i] = entries[i] * v.entries[i];
		}
	}

	else
		cout << "Impossível multiplicar componente a componente" << endl;

	return mult;
}


Vec	Vec::operator*(const double &scalar){
	Vec mult_s;
	mult_s.N = N;
	mult_s.entries = new double[N];

	for(int i=0; i<N; ++i){
		mult_s.entries[i] = scalar * entries[i];
	}

	return mult_s;
}


Vec Vec::operator-(const double &scalar){
	Vec dif_s;
	dif_s.N = N;
	dif_s.entries = new double[N];

	for(int i=0; i<N; ++i){
		dif_s.entries[i] = entries[i] - scalar;
	}

	return dif_s;
}


void Vec::Print(){
    if(N != 0){
	for(int i=0; i<N-1; ++i){
		cout << setw(3) << entries[i] << "  ";
	}

  cout << setw(3) << entries[N-1] << endl;
    }
    if(N == 0){
        cout << "0" << endl;
    }
}


void Vec::Print_N(){
	cout << "N: " << N << endl;
}

int Vec::size() const{
	return N;
}

int Vec::size(){
	return N;
}


void Vec::SetEntries (int n, double v[]){
	delete [] entries;
	N = n;
	entries = new double[N];

	for (int i=0; i<n; ++i){
		entries[i] = v[i];
	}
}


double Vec::dot (const Vec &v){
	double dot_prod=0;
	if(N == v.N){
		for(int i=0; i<N; ++i){
			dot_prod = dot_prod + entries[i]*v.entries[i];
		}
		return dot_prod;
	}

	else{
		cout << "Dimensões incompatíveis";
		return 0;
	}
}


void Vec::swap(int n, int m){
	if(n>=0 && n<N && m>=0 && m<N){
		double aux;
		aux = entries[n];
		entries[n] = entries[m];
		entries[m] = aux;
	}
	else
		cout << "Posições não encontradas" << endl;
}





