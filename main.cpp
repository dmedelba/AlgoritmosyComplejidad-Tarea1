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

class valores{
	private:
		int f;
		int g;
	public:
		void setDatos(int new_f, int new_g);
		int getF();
		int getG();
		
};

void valores::setDatos(int new_f, int new_g){
	f=new_f;
	g=new_g;
}



int valores::getF(){
	return f;
}
int valores::getG(){
	return g;
}


//bubblesort
void bubble_sort(valores array_ordenar[], int n)
{
  int c, d, t, t1, t_1,t_2;
 
  for (c = 0 ; c < ( n - 1 ); c++)
  {
    for (d = 0 ; d < n - c - 1; d++)
    {
      if (array_ordenar[d].getF() > array_ordenar[d+1].getF())
      {
        t         = array_ordenar[d].getF();
        t1        = array_ordenar[d].getG();
        t_1=array_ordenar[d+1].getF();
        t_2=array_ordenar[d+1].getG();
        array_ordenar[d].setDatos(t,t1);
        array_ordenar[d+1].setDatos(t_1,t_2);
      }
   }
  }
}
int main(){
	std::string n_str, k_str; // valor n y k en string
	string input_init= "_"; 
	string input = "_";
	int total=0;
	stack<valores> p_valores;
	//obtenemos nuestra primera linea
	while(getline(cin,input_init)){ 
		valores array_ordenar[5];
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

		for (int i=0; i<m; i++){
			//obtenemos los valores de f y g
			getline(cin,input_2);
			vector<string> TempBuff(0);
			int size_V;
			split(input_2, *" ",  TempBuff, size_V);

			f=std::stoi(TempBuff[0]);
			g=std::stoi(TempBuff[1]);
			//llenar matriz, al revez para ver cuantos caminos llegan, no cuantos salen.
			matriz_grafo[g][f]=1;
		}

		for(int i=0; i<n; i++){
			int count=0;
			for(int j=0; j<n; j++){
				//contamos los caminos que llegan a i
				if(matriz_grafo[i][j]==1){
					count+=1;
				}
			}
			// verificamos si hay mas de un camino que llega a i 
			if (count>1){
				//i es candidato
				int hay_camino=-1;
				//verificar que i tiene conexion a la base de datos
				if(array_bd[i]==1){
					//Los caminos que llegan a la fila i producen problemas con la bd
					hay_camino=i;

				}
				//verificar que el siguiente nodo conecta a la bd
				else{
					int cuentax=0;
					int marca=0;
					for(int a=0; a<n; a++){
						//camino que llega al siguiente nodo
						if(matriz_grafo[a][i]==1){
							cuentax+=1;
							//verificar si a tiene conexion con bd
							if(array_bd[a]==1){
								marca=1;
							}
						}

					}
					//verifico que desde ese nodo solo puedo llegar al que tiene conexion con la bd.
					if(cuentax==1 && marca==1){
						hay_camino=i;
					}
				}
				//imprimir las dependencias funcioanales que provocan problemas en la bd
				//caminos que estan en la fila "hay_camino"
				if(hay_camino!=-1){
					for(int b=0; b<n; b++){
						if(matriz_grafo[hay_camino][b]==1){
							total+=1;
							cout<<b;cout<<" "<<hay_camino<<endl; 
						}
					}
					
					//creo arreglo para ordenar
					
					//agrego valores al arreglo
					
				
					
					
					hay_camino=-1;
				}
			}

		}
		cout<<"hay ";cout<<total;cout<<" dependencias funcionales"<<endl;

		cout<<endl;
	}
}