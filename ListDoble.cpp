#include"biblioteca1.h"
#include<string>

ListDoble::ListDoble(){

}

void ListDoble::add(int id, CajaRegistradora cajaRegistradora){
	Container *nuevo = new(Container);
	nuevo->id = id;
	nuevo->cajaRegistradora = cajaRegistradora;
	if (primero == NULL)
	{
		primero = nuevo;
		primero->sig=NULL;
		primero->ant=NULL;
		ultimo = primero;
		size++;
	}else{
		ultimo->sig=nuevo;
		nuevo->ant = ultimo;
		nuevo->sig=NULL;
		ultimo = nuevo;
		size++;
	}
}

void ListDoble::mod(int id, CajaRegistradora cajaRegistradora){
	Container *tmp = new(Container);
	tmp = primero;
	if (primero != NULL)
	{
		do
		{
			if (tmp->id ==id)
			{
				tmp->cajaRegistradora = cajaRegistradora;
				break;
			}
			tmp = tmp->sig;
		} while (tmp != NULL);
	}

}

CajaRegistradora ListDoble::getCajaRegistradora(int id){
	CajaRegistradora cajaRegistradora;
	Container *tmp = new(Container);
	tmp = primero;
	if (primero != NULL)
	{
		do
		{
			if (tmp->id ==id)
			{
				cajaRegistradora = tmp->cajaRegistradora;
				return cajaRegistradora;
			}
			tmp = tmp->sig;
		} while (tmp != NULL);
	}

	return cajaRegistradora;
}

bool ListDoble::libreCaja(int id){
	Container *tmp = new(Container);
	tmp = primero;
	if (primero != NULL)
	{
		do
		{
			if (tmp->id ==id)
			{
				if (tmp->cajaRegistradora.estado==true){
					return true;
				}else{
					return false;
				}				
			}
			tmp = tmp->sig;
		} while (tmp != NULL);
	}
	return false;
}

string ListDoble:: mostrarLista(){
	string cajas;
	cajas = cabecera();
	Container *tmp = new(Container);
	tmp = primero;
	if (primero != NULL)
	{
		do
		{
			string actual = "f"+to_string(tmp->id);
			string turno = to_string(tmp->cajaRegistradora.tiempo);
			string estados = estado(tmp->cajaRegistradora.estado);

			if (tmp==primero){
				if (ultimo!=primero)
				{
					string sig = "f"+to_string(tmp->sig->id);
					cajas=cajas + actual +"->"+sig + "[constraint=false];";	
				}			
			}else if (tmp==ultimo){
				string ant =  "f"+to_string(tmp->ant->id);
				cajas=cajas + actual +"->"+ant + "[constraint=false];";	
			}else{
				string sig = "f"+to_string(tmp->sig->id);
				string ant =  "f"+to_string(tmp->ant->id);
				cajas=cajas + actual +"->"+sig + "[constraint=false];";
				cajas=cajas + actual +"->"+ant + "[constraint=false];";	

			}
			cajas= cajas + actual + "[label=\"Caja "+ to_string(tmp->id) +" \n Turno: "+ turno+" \n "+ estados +" \"];";
			tmp = tmp->sig;
		} while (tmp != NULL);
	}

	cajas = cajas + "}";
	return cajas;
}

string ListDoble::cabecera(){
	string cabecera="subgraph cluster_cajas {label = \"Cajas\";	style=filled;style=filled;color=white;node [style=rounded,color=black,shape=box];";
	return cabecera;
}

string ListDoble::estado(bool estado){
	if (estado)
	{
		return "Libre";
	}
	return "Ocupado";
}



