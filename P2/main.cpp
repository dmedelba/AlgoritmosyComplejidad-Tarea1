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
    for (int i = 0; i < s.size(); i++)
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

class Experiment{
	private:
		int calidad;
		string nombre;
	public:
		void setDatos(int q, string nom);
		int getCalidad();
		string getNombre();

		
};

void Experiment::setDatos(int q, string nom){
	calidad=q;
	nombre=nom;
}



int Experiment::getCalidad(){
	return calidad;
}
string Experiment::getNombre(){
	return nombre;
}

//======================================================================
//funcion para dividir el array y hacer los intercambios
int dividir(Experiment vector[], int inicio, int fin){
  
  //variables para intercambiar valores 
  int v_izq;
  int v_der;
  int v_inicio;
  string v_izq_name;
  string v_der_name;
  string v_inicio_name;

  int pivote = vector[inicio].getCalidad();
  int izq = inicio;
  int der = fin;

  //Mientras no se cruzen los índices
  while (izq < der){
    while (vector[der].getCalidad() > pivote){
	  der--;
    }
	while ((izq < der) && (vector[izq].getCalidad() <= pivote)){
      izq++;
    }

    // Si todavia no se cruzan los indices seguimos intercambiando
	if(izq < der){
      v_izq= vector[izq].getCalidad();
      v_der= vector[der].getCalidad();
      v_izq_name= vector[izq].getNombre();
      v_der_name= vector[der].getNombre();

      vector[izq].setDatos(v_der, v_der_name);
      vector[der].setDatos(v_izq, v_izq_name);
    }
  }

  //Los indices ya se han cruzado, ponemos el pivote en el lugar que le corresponde
  v_der = vector[der].getCalidad();
  v_inicio= vector[inicio].getCalidad();
  v_der_name= vector[der].getNombre();
  v_inicio_name= vector[inicio].getNombre();

  vector[der].setDatos(v_inicio, v_inicio_name);
  vector[inicio].setDatos(v_der, v_der_name);

  //La nueva posición del pivote
  return der;
}

//						Funcion Quicksort
//======================================================================
//funcion recursiva para hacer el ordenamiento
void quicksort(Experiment vector[], int inicio, int fin)
{
  int pivote;
  if(inicio < fin)
  {
    pivote = dividir(vector, inicio, fin );
    quicksort( vector, inicio, pivote - 1 );//ordeno la lista de los menores
    quicksort( vector, pivote + 1, fin );//ordeno la lista de los mayores
  }
}

//======================================================================



int main( int argc, char **argv) {
	std::string n_str, k_str; // valor n y k en string
	string input_init= "_"; 
	string input = "_";
	//obtenemos nuestra primera linea
	while(getline(cin,input_init)){ 
		vector<string> TempBuff(0);
	    int size_V;
	    split(input_init, *" ",  TempBuff, size_V);
		n_str=TempBuff[0];
		k_str=TempBuff[1];
		int n = std::stoi(n_str); // n numero total de experimentos 
		int k = std::stoi(k_str); // k mejores experimentos 
		
		//creo arreglo para expermientos
		Experiment Array_experimentos[n];

		
		int quality;
		string name;
		string str_quality;
		for (int i = 0; i < n; ++i){
			getline(cin,input);
			vector<string> TempBuff1(0);
			int size_V1;
			split(input, *" ",  TempBuff1, size_V1);
			str_quality = TempBuff1[0];
			quality = std::stoi(str_quality); //paso a int
			name = TempBuff1[1];

			//creo el objeto experimento
			Array_experimentos[i].setDatos(quality, name);
		
		}
		//ordeno el arreglo mediante quicksort (nlogn)
		quicksort(Array_experimentos,0,n-1);
		
		//obtengo mejores k experimentos
		int contador=0;
		while(contador<k){
			n=n-1;
			cout<<Array_experimentos[n].getCalidad();cout<< " ";
			cout<< Array_experimentos[n].getNombre()<<endl;
			contador++;
		}
		cout<<endl;
	}


	


	

	

}