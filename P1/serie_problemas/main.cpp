#include "Vec.h"
#include "FCtools.h"
#include "TCanvas.h"
#include "TH2F.h"

using namespace std;

int main(){

    //criação vetor de duas componentes, ambas inicializadas a 0, seguida de print
	Vec v1(2);
	cout << endl << "v1(2): " << endl ;
	v1.Print_N();
	v1.Print();

    //criação vetor de 10 componentes inicializadas a 3, seguida de print
	Vec v2(10,3);
	cout << endl << "v2(10,3): " << endl;;
	v2.Print_N();
	v2.Print();

    //criação de vetor seguido de determinação do seu tamanho; cria-se um vetor vec com as mesmas componentes e tamanho que o vetor criado, seguindo-se a impressão das suas componentes
	double a[]={1.2, 3.0, 5.4, 5.2, 1.0, 7, 9, -11};
	int size = sizeof(a)/sizeof(double);
	Vec v3(size, a);
	cout << endl << "v3(size,a): " << endl ;
	v3.Print_N();
	v3.Print();

    //criação de um objeto que resulta da cópia de outro já existente, seguindo-se print
	Vec v4(v2);
	cout << endl << "v4(v2): " << endl ;
	v4.Print_N();
	v4.Print();

    //cria-se um vetor de 5 componentes inicializadas a -7
	Vec v5(5,-7);
	cout << endl << "v5(5,-7) antes de SetEntries: " << endl;
	v5.Print_N();
	v5.Print();

    //alteram-se as componentes, entries, do objeto da class vec anteriormente criado. Neste caso, altera-se o tamanho para size - valor anteriormente calculado - e as componentes para as do vetor de doubles a.
	v5.SetEntries(size, a);
	cout << endl << "v5 após SetEntries(size,a): " << endl;
	v5.Print_N();
	v5.Print();

    //criação de objeto vec com constructor default
	Vec v6;
	cout <<  endl << "v6(): " << endl;
	v6.Print_N();
	v6.Print();

	cout << endl;
 
    
    //CM é um vetor de vetores, funcionando como uma matriz.
	double CM[][5]={{1.0, 7.0, 5.0, 3.0, -3.0}, {5.0, 2.0, 8.0, -2.0, 4.0}, {1.0, -5.0, -4.0, 6.0, 7.6}, {0.0, -5.0, 3.0, 3.2, 3.3}, {1.0, 7.0, 2.0, 2.1, 1.2}};	
	
	cout << "Cópia do conteúdo da matriz CM para o array cv:" << endl;
    //cria-se um vetor de 5 componentes da classe Vec.
    //de seguida, a cada cv[i] estará associado um vetor de entries equivalentes às do vetor CM[i].
    //os objetos são impressos no terminal e o conjunto das linhas/vetores impressos constitui uma potencial matriz.
	Vec cv[5];
	for(int i=0; i<5; ++i){
		cv[i].SetEntries(5, CM[i]);
		cout << "Linha " << i << endl;
		cv[i].Print();
		cout << endl;
	}

    //leitura de matrizes através de ficheiros, recorrendo a diferentes métodos
	vector<string> leitura1; //leitura1 é um vetor de strings
	vector<Vec> leitura2;
	Vec *leitura3;
    
	//designação de três objetos da classe FCTools, onde os métodos de leitura são explicitados
	FCTools l1, l2, l3;
	leitura1 = l1.ReadFile2String("../vec.txt");
	leitura2 = l2.ReadFile2Vec("../vec.txt");
	leitura3 = l3.ReadFile("../vec.txt");

    //cada linha da matriz é lida como uma única string. Como tal, a impressão será feita desde a linha 0 - leitura1.at(0) - até à última linha da matriz, ou seja, até à linha leitura1.size() - 1.
	cout << "Leitura ficheiro - método 1: " << endl;
	for(int i=0; i<leitura1.size(); ++i){
		cout << leitura1.at(i) << endl;
        //após ser apresentada cada componente do vetor de strings, realiza-se uma mudança de linha, sendo os resultados apresentados tal como os valores são enunciados no ficheiro.
	}

    //neste caso, cada linha do ficheiro corresponde a um objeto da classe Vec, pelo que a apresentação dos resultados da leitura poderá ser feita recorrendo ao método Print()
	cout << endl << "Leitura ficheiro - método 2: " << endl;

	for(int i=0; i<leitura2.size(); ++i){
		leitura2.at(i).Print();
		
	}

    
    //a ideia neste caso é semelhante à anterior, com a diferença de que neste caso leitura3 é um ponteiro para objetos da classe Vec.
	cout << endl << "Leitura ficheiro - método 3: " << endl;

	for(int i=0; i<5; ++i){
		leitura3[i].Print();
	}

	
	Vec v_a(6,3);
	Vec v_b(6,4);
	Vec v_c(5,1);
	Vec v_d(5,7);

    //Soma - utilização de operador +
	Vec soma1 = v_a + v_b;
	cout << endl << "Operador +" << endl << "v_a(6,3) + v_b(6,4): " << endl;
	soma1.Print();

	//Subtração - utilização de operador -
	Vec sub = v_c-v_d;
	cout << endl << "Operador -" << endl << "v_c(5,1) - v_d(5,7): " << endl;
	sub.Print();

	//Igualdade - utilização do operador =
	Vec v_e(2,5);
	Vec v_f(5,-1);
	cout << endl << "v_e(2,5) antes: " << endl;
	v_e.Print();
	v_e=v_f;
	cout << endl << "Operador =" << endl << "v_e(2,5) = v_f(5,-1): " << endl;
	v_e.Print();

	//+= - sem que seja criado um novo objeto, alteram-se as componentes de um dos vetores que constituem a operação. Neste caso, somam-se as suas componentes iniciais com as de um vetor dado.
	cout << endl << "v_b(6,4) antes: " << endl;
	v_b.Print();
	v_b+=v_a;
	cout << endl << "Operador +=" << endl << "v_b(6,4) += v_a(6,3): " << endl;
	v_b.Print();

	//-= - sem que seja criado um novo objeto, alteram-se as componentes de um dos vetores que constituem a operação. Neste caso, subtraem-se as suas componentes iniciais com as de um vetor dado.
	cout << endl << "v_c(5,1) antes: " << endl;
	v_c.Print();
	v_c-=v_d;
	cout << endl << "Operador -=" << endl << "v_c(5,1) -= v_d(5,7): " << endl;
	v_c.Print();

	//[] - utiliza-se o operador [] para que seja retornada a componente de um vetor associado a um objeto da class Vec.
	cout << endl << "Operador []" << endl << "Elemento 1 de v4: " << v4[0] << endl;

	//Produto - utilização do operador * - multiplicação entre componentes correspondentes -> (a,b) * (c,d) = (a*c, b*d)
	Vec v_g(5,-2);
	Vec v_h(5,0.25);
	Vec mult;
	mult = v_g*v_h;
	cout << endl << "Operador *" << endl << "v_g(5,-2) * v_h(5,0.25): " << endl;
	mult.Print();

	//Produto - multiplicação por um escalar recorrendo ao operador *
	cout << endl << "Operador * (scalar)" << endl << "v_g(5,-2) * 4: " << endl;
	Vec scalar;
	scalar = v_g*4;
	scalar.Print();

	//Produto interno - recorre-se a um método da classe Vec para calcular o produto interno entre dois vetores
	Vec v_i(4,-2);
	Vec v_j(4,2);
	double dot = v_j.dot(v_i);
	cout << endl << "Prod interno" << endl << "v_i(4,-2) dot v_j(4,2): " << dot << endl;

	//swap - troca da posição de componentes de um determinado vetor, recorrendo-se a um método da classe Vec. Neste caso swap(2,7) irá originar a troca de posição entre as componentes 2 e 7 do vetor em questão
	cout << endl << "v3 antes troca: " << endl;
	v3.Print();
	v3.swap(2,7);
	cout << endl << "v3 após swap(2,7): " << endl;
	v3.Print();

    cout << endl;
    
    //realização de histograma relativo ao valor das componentes da matriz potenciada por cv
	/*TCanvas *c1 = new TCanvas("Histo", "c1", 1200, 800);
	TH2F *h2 =  new TH2F("Matrix", "Matrix histogram", 5, 1, 5, 5, 1, 5);
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			h2->Fill(i, j, cv[i][j]);
		}
	}*/

	//h2->Draw("Lego2");
	//c1->SaveAs("Matrix.eps");

delete [] leitura3;
return 0;
}
