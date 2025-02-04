#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

// Convertir boolean a string
std::string toString(bool valor) {
    return valor ? "true" : "false";
}
//funcion cuenta para hacer split 
void Cuenta(string s, const char Separadorr, int &TotalChars) {
    for (unsigned int i = 0; i < s.size(); i++)
        if (s[i] == Separadorr) TotalChars++;
}
//split 
void split(string Linea, char Separador, vector<string> &TempBuff, int &TotalVector) {
    TempBuff.resize(0);
    TotalVector = 0;
    int Nums = -1;
    int NumPos = -1;
    int ValorNum = 0;
    int TotalChars = 0;
    int TotalEspacios = Linea.length();
    string Valor;
    Cuenta(Linea, Separador, TotalChars);
    if (TotalChars != 0) {
        while (Nums < TotalChars) {
            Nums++;
            ValorNum = Linea.find(Separador, NumPos + 1);
            Valor = Linea.substr(NumPos + 1,ValorNum);
            Valor = Valor.substr(0, Valor.find_first_of(Separador));
            TempBuff.push_back(Valor);
            NumPos = ValorNum;
            TotalEspacios++;
        }
        TotalVector = TempBuff.size();
    }
    else {
        //TempBuff.push_back(Linea.substr(0, Linea.find_first_of(Separador)));
        TotalVector = 0;
    }
}

int main(){
	std::string n_str, k_str; // valor n y k en string
	string input_init= "_"; 
	string input = "_";
	//obtenemos nuestra primera linea
	while(getline(cin,input_init)){ 
		int n =std::stoi(input_init);
		int array_bd[n];// array que nos indica si nodo n-esimo tiene conexion con la bd
		for(int i=0; i<n; i++){
			getline(cin,input);
			int valor =std::stoi(input);
			array_bd[i]= valor; //0: no tiene conexion, 1:si tiene conexion
		}

		string str_m= "_"; //variable para guardar m (cantidad de dependencias funcionales)
		getline(cin,str_m);
		int m= std::stoi(str_m);
		//crear matriz de nxm
		int matriz_grafo[n][m];
		//llenar matriz de ceros;
		for (int i=0;i<n; i++){
			for(int j=0; j<m; j++){
				matriz_grafo[i][j]=0;
			}
		}

		string input_2;
		int f; // f->g
		int g; // dependencias funcionales
		int array_count[n]; //arreglo que guarda la cantidad de enlacen entrantes
		for (int i=0;i<n; i++){
			array_count[i]=0;
		}


		for (int i=0; i<m; i++){
			//obtenemos los valores de f y g
			getline(cin,input_2);
			vector<string> TempBuff(0);
			int size_V;
			split(input_2, *" ",  TempBuff, size_V);

			f=std::stoi(TempBuff[0]);
			g=std::stoi(TempBuff[1]);
			//llenar matriz.
			matriz_grafo[f][g]=1;
			array_count[g]++;
		}

		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				//buscamos que coincida un 1 con el array_bd
				//ademas comparamos en array_count para ver si hay más de un camino
				//que llega a ese mismo nodo
				if((matriz_grafo[i][j]==1) && (array_bd[j]==1) && (array_count[j]>1)){
					cout << i ;cout << " " << j << endl;
				}
			}

		}
		cout<<endl;
	}
}