#include"biblioteca1.h"
#include<string>



ListSimple::ListSimple(){

}
void ListSimple::add1(int id){
	primero = new(Container);
	primero->id = id;
	primero->sig=NULL;
	size++;

}
void ListSimple::add(int id){
	if (size ==0)
	{
		add1(id);
	}else
	{
		Container *newContainer;
		newContainer = primero;
		if (primero->sig==NULL){
			newContainer = new(Container);
			newContainer->id = id;
			newContainer->sig=NULL;
			primero->sig = newContainer;
			size++;
		}else{
			newContainer = newContainer->sig;
			int cycle = 0;
			while(cycle==0){
				if (newContainer->sig == NULL)
				{
					Container *tmp = newContainer;
					newContainer = new(Container);
					newContainer -> id = id;
					newContainer->sig = NULL;
					tmp->sig = newContainer;			
					size++;
					break;
				}else{
					newContainer = newContainer->sig;
				}

			}
		}

	}
}
int ListSimple::pop(){
	int id;
	if(size!=0){
		Container *tmp = primero;
		Container *tmpsig = primero->sig;
		if(size==1){
			id = primero->id;
			delete (primero);
			size--;
			return id;
		}
		for(int i=0; i<size; i++){
			if(i == size-2){
				id = tmpsig->id;
				tmp->sig =NULL;
				delete (tmpsig);
				size--;
				return id;
			}else{				
				tmp = tmp->sig;
				tmpsig = tmpsig->sig;
			}
		}
	}
	return -1;
}
string ListSimple::mostrarLista(string letra,string nombre){
	Container *tmp = new(Container);
	tmp = primero;
	string pilas = cabecera(letra,nombre);
	if (primero!=NULL){
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



