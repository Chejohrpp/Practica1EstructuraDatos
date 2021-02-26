#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<string>
#include<stdlib.h>
#include<fstream>
#include"biblioteca1.h"
using namespace std;

int cantCarretas;

int cantCajas;
int cantClientesEspera;
int cantClientesPagando;
int cantCarretasPila1;
int cantCarretasPila2;
int cantClientesComprando;

int pasoActual = 1;

//listas
ListSimple pila1Carreta;
ListSimple pila2Carreta;
ListSimple pilaClientesEspera;
ListCircular compras;
ListDoble cajas;
ListSimplePago colaPagos;




int devolvernumRam(int inferior, int superior){	
	return inferior + rand()%(superior+1 - inferior);
}

int asignarCarreta(){
	return 0;

}
int carretaDisponible(){
	return 0;

}

int llenarCarretas(){
	//int numRandom;
	srand(time(NULL));//tiene que ir se quiere usar devolverRam()
	//pila 1
	for(int i=0; i<cantCarretasPila1; i++){
		//numRandom = devolvernumRam(1,2);
		pila1Carreta.add(i+1);

	}
	//pila 2
	for(int i=0; i<cantCarretasPila2;i++){
		pila2Carreta.add(cantCarretasPila1 + i+1);
	}
	return 0;
}

void estadoCajas(){

}

void crearArchivo(){
	ofstream file;
    string nombre = "dibujable.dot";
    file.open(nombre,ios::out);
    string caja = cajas.mostrarLista();
    string pago = colaPagos.mostrarLista();
    string compra = compras.mostrarLista();
    string pila1 = pila1Carreta.mostrarLista("b","Pila 1");
    string pila2 = pila2Carreta.mostrarLista("c","Pila 2");
    string clientesEspera = pilaClientesEspera.mostrarLista("a","Cola de espera");
    string carretas = "subgraph cluster_carretas{label =\"Carretas\";style=filled;color=white;" + pila1 + pila2 + "}";
    string content = "digraph G{"+ caja + pago + compra + carretas + clientesEspera +" }";
    file <<content;
    file.close();
}

void graficar(){
	crearArchivo();
	string comand = "dot -Tpng dibujable.dot -o img/paso_" + to_string(pasoActual) + ".png";
	system(comand.c_str());
}
int main(){
	
	ClienteCarreta clienteCarreta;
	clienteCarreta.idCliente =22;
	clienteCarreta.idCarreta=12;

	CajaRegistradora caja(1,0,true,NULL);
	CajaRegistradora caja1(2,5,false,&clienteCarreta);
	CajaRegistradora caja4(3,6,false,&clienteCarreta);

	cajas.add(caja.getNumCaja(),caja);
	cajas.add(caja1.getNumCaja(),caja1);
	cajas.add(caja4.getNumCaja(),caja4);

	ClienteCarreta clienteCarreta1;
	clienteCarreta1.idCliente =26;
	clienteCarreta1.idCarreta=12;

	ClienteCarreta clienteCarreta2;
	clienteCarreta2.idCliente =30;
	clienteCarreta2.idCarreta=12;

	colaPagos.add(1,clienteCarreta);
	colaPagos.add(2,clienteCarreta1);
	colaPagos.add(3,clienteCarreta2);

	compras.add(1,50,16);
	compras.add(2,56,96);
	compras.add(3,57,89);

	pila1Carreta.add(3);
	pila2Carreta.add(5);
	pila2Carreta.add(8);
	pilaClientesEspera.add(9);


	graficar();


	return 0;
}