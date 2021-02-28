#include"biblioteca1.h"
#include<string>

CajaRegistradora::CajaRegistradora(){
	
}
CajaRegistradora::CajaRegistradora(int numCaja1, int tiempo1, bool estado1, ClienteCarreta clienteCarreta1){
	numCaja = numCaja1;
	tiempo = tiempo1;
	estado = estado1;
	clienteCarreta = clienteCarreta1;
}
int CajaRegistradora::getNumCaja(){
	return numCaja;
}
