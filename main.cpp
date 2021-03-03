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
int cantCarretasPila1=0;
int cantCarretasPila2=0;

int cantClientesPagando=0;
int cantClientesComprando=0;

int cantClientesSistema;
int pasoActual = 1;
int idClienteEntrar = 1;
int indexColaPagos= 0;
int cantAcciones;
int cantPersonasInicio=0;

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

int llenarCarretas(){
	int finalPila1 = cantCarretasPila1+cantClientesComprando+cantClientesPagando;

	for(int i=1;i<=(finalPila1);i++){
		pila1Carreta.add(i);
	}

	for(int i=1;i<=cantCarretasPila2;i++){
		pila2Carreta.add(i+finalPila1);
	}

	return 0;
}
void addCajas(){
	ClienteCarreta clienteCarreta;
	for(int i=1; i<=cantCajas;i++){
		CajaRegistradora caja(i,0,true,clienteCarreta);
		cajas.add(caja.getNumCaja(),caja);
	}
}
int addColaEspera1(){
	pilaClientesEspera.add(idClienteEntrar);
	printf("Llega el cliente %d y se agrega a la cola de espera\n",idClienteEntrar);
	cantAcciones++;
	idClienteEntrar++;
	cantClientesSistema++;
	return 0;
}
int buscarIdNewCompras(){
	for(int i=0; i <= compras.getSize();i++){
		if (compras.buscarId(i)==false)
		{
			return i;
		}
	}
	return (compras.getSize()+1);
}
int agarrarCarreta2(){
	while(pilaClientesEspera.getSize() > 0 && (pila1Carreta.getSize()>0 || pila2Carreta.getSize()>0) ){
		if (compras.getSize() >= 100)
		{
			return 0;
		}
		if (pilaClientesEspera.getSize() > 0){
			if (pila1Carreta.getSize() > 0)
			{
				int idClienteComprar = pilaClientesEspera.pop();
				int idCarretaComprar = pila1Carreta.pop();
				compras.add(buscarIdNewCompras(),idClienteComprar,idCarretaComprar);
				printf("El cliente %d entro a comprar con la carreta %d de la pila 1\n",idClienteComprar,idCarretaComprar);
				cantAcciones++;
			}
			else if(pila2Carreta.getSize() >0)
			{
				int idClienteComprar = pilaClientesEspera.pop();
				int idCarretaComprar =  pila2Carreta.pop();
				compras.add(buscarIdNewCompras(),idClienteComprar,idCarretaComprar);
				printf("El cliente %d entro a comprar con la carreta %d de la pila 2\n",idClienteComprar,idCarretaComprar);
				cantAcciones++;
			}
		}
	}

	return 0;
}
int pasarPagar4(int paso, int idCliente){
	if (colaPagos.getSize() == 0){
		return 0;
	}
	for(int i=1;i<=cantCajas;i++){
		if (cajas.libreCaja(i))
		{
			CajaRegistradora caja = cajas.getCajaRegistradora(i);
			ClienteCarreta clienteCarreta = colaPagos.pop();
			caja.estado = false;
			caja.clienteCarreta = clienteCarreta;
			cajas.mod(caja.getNumCaja(), caja);
			printf("El cliente %d esta siendo atendido por la caja %d\n",clienteCarreta.idCliente,caja.getNumCaja());
			cantAcciones++;
			return 0; 
		}
	}
	if (paso==3){
		printf("El cliente %d entra a la cola de pagos\n", idCliente);
		indexColaPagos++;
		cantAcciones++;
	}

	return 0;
}

int irColaPago3(){
	if (compras.getSize() == 0){
		return 0;
	}
	int numRandom = devolvernumRam(0,100);
	if (compras.buscarId(numRandom)){
		ClienteCarreta clienteCarreta = compras.pop(numRandom);
		if (colaPagos.getSize() > 0){
			colaPagos.add(indexColaPagos,clienteCarreta);
			printf("El cliente %d entra a la cola de pagos\n", clienteCarreta.idCliente);
			cantAcciones++;
			indexColaPagos++;
		}else{
			colaPagos.add(indexColaPagos,clienteCarreta);
			pasarPagar4(3, clienteCarreta.idCliente);
		}
	}

	return 0;
}
int salidaSistema5(){
	int cajaRevisar = devolvernumRam(1,cantCajas);
		if (cajas.libreCaja(cajaRevisar)==false)
		{
			CajaRegistradora caja = cajas.getCajaRegistradora(cajaRevisar);
			ClienteCarreta clienteCarreta;
			clienteCarreta = caja.clienteCarreta;
			int devolverCarreta = devolvernumRam(1,2);
			if (devolverCarreta==1)
			{
				pila1Carreta.add(clienteCarreta.idCarreta);
			}else{
				pila2Carreta.add(clienteCarreta.idCarreta);
			}
			caja.estado = true;
			caja.tiempo += 1;
			cajas.mod(caja.getNumCaja(), caja);
			cantClientesSistema--;
			printf("El cliente %d sale del sistema. Libera la carreta %d y la caja %d.\n",clienteCarreta.idCliente,clienteCarreta.idCarreta,caja.getNumCaja());
			cantAcciones++;
			return 0;
		}
	return 0;
}
int buscarCarreta(){
	int idCarreta=0;
	if(pila1Carreta.getSize() > 0){
		idCarreta = pila1Carreta.pop();
		return idCarreta;
	}else{
		idCarreta = pila2Carreta.pop();
		return idCarreta;
	}
	return idCarreta;
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
	srand(time(NULL));//tiene que ir se quiere usar devolverRam()
	
	printf("Simulacion de MiniMarket Manager\nCantidad de carretas al inicio en la pila 1: ");
	cin >> cantCarretasPila1;
	printf("Cantidad de carretas al inicio en la pila 2: ");
	cin>>cantCarretasPila2;
	printf("Cantidad de cajas: ");
	cin>>cantCajas;
	addCajas();
	printf("Cantidad de personas en cola de espera: ");
	cin>>cantPersonasInicio;

	printf("Cantidad de clientes comprando con carreta incluida:");
	cin>>cantClientesComprando;

	printf("Cantidad  de clienes pagando con carreta incluida:");
	cin>>cantClientesPagando;

	llenarCarretas();

	for(int i=0;i<cantClientesPagando;i++){
		ClienteCarreta clienteCarreta;
		clienteCarreta.idCliente = idClienteEntrar;
		clienteCarreta.idCarreta = buscarCarreta();
			colaPagos.add(indexColaPagos,clienteCarreta);
			indexColaPagos++;
			idClienteEntrar++;
			cantClientesSistema++;
	}

	for(int i=0;i<cantClientesComprando;i++){
		compras.add(buscarIdNewCompras(),idClienteEntrar,buscarCarreta());
		idClienteEntrar++;
		cantClientesSistema++;
	}

	for(int i=0; i<cantPersonasInicio;i++){
		pilaClientesEspera.add(idClienteEntrar);
		cantAcciones++;
		idClienteEntrar++;
		cantClientesSistema++;
	}

	int choice = 0;
	do
	{
		
		printf("\nCantidad clientes en cola de espera de carretas: %d\n",pilaClientesEspera.getSize());
		printf("Cantidad  de carretas en la pila 1: %d\nCantidad de carretas en la pila 2: %d\n",pila1Carreta.getSize(),pila2Carreta.getSize());
		printf("Cantidad de clientes comprando: %d\n",compras.getSize());
		printf("Cantidad clientes en cola de pagos: %d\n",colaPagos.getSize());
		printf("Cantidad de cajas: %d\n",cajas.getSize());
		printf("presione 1 para iniciar la simulacion: ");
		cin>>choice;
	} while (choice!= 1);

	graficar();
	pasoActual++;
	do
	{
		cantAcciones=0;
		printf("\n ************* Paso %d ************* \n",pasoActual);
		int agregaCliente = devolvernumRam(0,10);
		//agregamos un nuevo cliente al sistema
		if(agregaCliente==1){
			addColaEspera1();
		}
		//si hay carretas disponibles y personas en espera se agrega a las compras
		agarrarCarreta2();
		//pasamos a buscar a alguien de compras y los pasamos a la cola de pagos
		for(int i=0;i<10;i++){
			irColaPago3();
		}
		//vemos si se puede ir a pagar en alguna caja
		for(int i=0;i<cantCajas;i++){
			pasarPagar4(0,0);
		}
		//un cliente sale del sistema
		salidaSistema5();
		//ver si quieren graficar
		if (cantAcciones>0)
		{
			string sN;
			printf("Desea graficar los pasos? persione la letra s para si\n");
			cin >> sN;
			if (sN=="s"){
				graficar();
			}
		}
		pasoActual++;
	} while (cantClientesSistema > 0);

	printf("\nSimulacion Terminada\n");

	return 0;
}