#include"biblioteca1.h"
#include<string>

ListCircular:: ListCircular(){

}

void ListCircular:: add(int id,int idCliente, int idCarreta){
	Container *newContainer = new(Container);
	ClienteCarreta clienteCarreta;
	newContainer->id = id;
	clienteCarreta.idCliente = idCliente;
	clienteCarreta.idCarreta = idCarreta;
	newContainer->clienteCarreta = clienteCarreta;	
	if(primero==NULL){
		primero = newContainer;
		primero->sig = primero;
		ultimo = primero;
		size++;
	}else{
		ultimo->sig = newContainer;
		ultimo = newContainer;
		ultimo->sig = primero;
		size++;
	}
}

ClienteCarreta ListCircular:: pop(int id){
	ClienteCarreta clienteCarret;
	if(primero!=NULL){
		Container *tmp = new (Container);
		tmp = primero;
		Container *tmpAnt = new (Container);
		tmpAnt = NULL;
		do
		{
			if (tmp->id == id)
			{
				clienteCarret = tmp->clienteCarreta;
						
				if (tmp == primero)
				{
					primero = primero->sig;
					ultimo->sig = primero;
				} 
				else if (tmp==ultimo)
				{
					tmpAnt->sig = primero;
					ultimo = tmpAnt;
				}else{
					tmpAnt->sig = tmp->sig;
				}
				delete (tmp);
				size--;
				if (size <= 0){
					primero = NULL;
				}
				return clienteCarret;
			}
			tmpAnt = tmp;
			tmp = tmp->sig;
		} while (tmp!=primero);
	}
	return clienteCarret;

}

bool ListCircular::buscarId(int id){
	Container *tmp = new (Container);
	tmp = primero;
	if (primero != NULL)
	{
		do
		{
			if (tmp->id==id)
			{
				return true;
			}
			tmp = tmp->sig;
		} while (tmp != primero);
		return false;
	}
	return false;
}

string ListCircular::mostrarLista(){
	Container *tmp = new (Container);
	tmp = primero;
	string compras;
	compras = cabecera();
	if (primero != NULL)
	{
		do
		{
			string actual = "d" + to_string(tmp->id);
			string sig = "d"+to_string(tmp->sig->id);
			compras += actual + "->" + sig +"[constraint=false];";
			compras += actual + "[label=\"Cliente "+ to_string(tmp->clienteCarreta.idCliente) +" \n Carreta "+to_string(tmp->clienteCarreta.idCarreta)+"\"];";
			
			tmp = tmp->sig;
		} while (tmp != primero);
	}

	compras = compras + "}";
	return compras;
}

string ListCircular::cabecera(){
	return "subgraph cluster_compras{label = \" compras \";style=filled;style=filled;color=white;node [style=rounded,color=black,shape=box];";
}

