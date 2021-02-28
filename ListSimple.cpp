#include"biblioteca1.h"
#include<string>



ListSimple::ListSimple(){

}

void ListSimple::add(int id){
	Container *nuevo = new (Container);
	nuevo->id = id;
	if (primero==NULL)
	{
		primero = nuevo;
		primero->sig =NULL;
		ultimo = primero;
		size++;
	}else{
		ultimo->sig =nuevo;
		nuevo->sig = NULL;
		ultimo = nuevo;
		size++;
	}
}
int ListSimple::pop(){
	Container *tmp = new (Container);
	int id;
	tmp = primero;
	if (primero!=NULL){
		id = primero->id;
		if (ultimo == primero){
			delete(tmp);
			primero = NULL;	
		}else{
			primero = primero->sig;
			delete(tmp);
		}
		size--;
		return id;
	}
	return -1;
}
string ListSimple::mostrarLista(string letra,string nombre){
	Container *tmp = new(Container);
	tmp = primero;
	string pilas = cabecera(letra,nombre);
	if (primero != NULL){
		do
		{
			string actual = letra+to_string(tmp->id);
			if (tmp == primero)
			{
				if (primero->sig!=NULL)
				{
					string sig = letra+to_string(tmp->sig->id);
					pilas=pilas + actual +"->"+sig + ";";
				}
			}else if (tmp->sig != NULL){
				string sig = letra+to_string(tmp->sig->id);
				pilas=pilas + actual +"->"+sig + ";";
			}
			if (letra == "a")
			{
				pilas = pilas + actual + "[label=\"cliente "+ to_string(tmp->id) +" \"];";
			}else{
				pilas = pilas + actual + "[label=\" "+ to_string(tmp->id) +" \"];";
			}			
			tmp=tmp->sig;
		} while (tmp!=NULL);
	}

	pilas = pilas + "}";
	return pilas;

}
string ListSimple::cabecera(string letra, string nombre){
	return "subgraph cluster_"+letra+"{label = \" "+nombre+" \";style=filled;style=filled;color=white;node [shape=box,color=black];";
}



