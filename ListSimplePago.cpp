#include"biblioteca1.h"

ListSimplePago::ListSimplePago(){

}

void ListSimplePago::add(int id,ClienteCarreta clienteCarreta){
	Container *nuevo = new (Container);
	nuevo->id = id;
	nuevo->clienteCarreta = clienteCarreta;
	if (primero==NULL)
	{
		primero =nuevo;
		primero->sig=NULL;
		ultimo = primero;
		size++;
	}else{
		ultimo->sig=nuevo;
		nuevo->sig=NULL;
		ultimo = nuevo;
		size++;
	}
}

ClienteCarreta ListSimplePago::pop(){
	Container *tmp = new(Container);
	ClienteCarreta cliente;
	tmp=primero;
	if (primero!=NULL){
		cliente = primero->clienteCarreta;
		if (ultimo == primero){
			delete(tmp);
			primero =NULL;	
		}else{
			primero = primero->sig;
			delete(tmp);
		}
		size--;
		return cliente;
	}
	return cliente;
}

string ListSimplePago::mostrarLista(){
	Container *tmp = new(Container);
	tmp = primero;
	string pagos = cabecera();
	if (primero!=NULL){
		do
		{
			string actual = "e"+to_string(tmp->clienteCarreta.idCliente);
			if (tmp == primero)
			{
				if (ultimo!=primero)
				{
					string sig = "e"+to_string(tmp->sig->clienteCarreta.idCliente);
					pagos=pagos + actual +"->"+sig + ";";
				}
			}else if (tmp != ultimo){
				string sig = "e"+to_string(tmp->sig->clienteCarreta.idCliente);
				pagos=pagos + actual +"->"+sig + ";";
			}
			pagos = pagos + actual + "[label=\"cliente "+ to_string(tmp->clienteCarreta.idCliente) +" \"];";
			tmp=tmp->sig;
		} while (tmp!=NULL);
	}

	pagos = pagos + "}";
	return pagos;
}

string ListSimplePago::cabecera(){
	return "subgraph cluster_pagar{label = \"Cola de espera a pagar\";style=filled;style=filled;color=white;node [shape=box,color=black,style=rounded];";
}