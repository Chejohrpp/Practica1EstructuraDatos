#include<iostream>
#include<string>
using namespace std;

typedef struct clienteCarreta{
	int idCliente;
	int idCarreta;
}ClienteCarreta;


class ListSimple{
private:
	typedef struct Container
	{
		int id;
		struct Container *sig;

	}Container;
	Container *primero;
	Container* ultimo;
	int size = 0;
public:
	ListSimple();
	void add(int id);
	int pop();
	int getSize(){return size;}
	string mostrarLista(string letra,string nombre);
	string cabecera(string letra,string nombre);
};

class ListCircular{
private:
	typedef struct Container
	{
		int id;
		ClienteCarreta clienteCarreta;
		struct Container *sig;

	}Container;
	Container *primero;
	Container *ultimo;
	int size = 0;
public:
	ListCircular();
	void add(int id, int idCliente, int idCarreta);
	ClienteCarreta pop(int id);
	bool buscarId(int id);
	string mostrarLista();
	int getSize(){return size;}
	string cabecera();

};

class CajaRegistradora{
private:
	int numCaja;
public:		
	int tiempo;
	bool estado;
	ClienteCarreta clienteCarreta;
	CajaRegistradora();
	CajaRegistradora(int numCaja1, int tiempo1, bool estado1, ClienteCarreta clienteCarreta1);
	int getNumCaja();
};


class ListDoble{
private:
	typedef struct Container
	{
		int id;
		CajaRegistradora cajaRegistradora;
		struct Container *sig;
		struct Container *ant;

	}Container;
	Container *primero;
	Container *ultimo;
	int size = 0;
public:
	ListDoble();
	void add(int id, CajaRegistradora cajaRegistradora);
	void mod(int id, CajaRegistradora cajaRegistradora);
	CajaRegistradora getCajaRegistradora(int id);
	bool libreCaja(int id);
	string mostrarLista();
	int getSize(){return size;}
	string cabecera();
	string estado(bool estado);
};


class ListSimplePago{
	private:
	typedef struct Container
	{
		int id;
		ClienteCarreta clienteCarreta;
		struct Container *sig;

	}Container;
	Container *primero;
	Container *ultimo;
	int size = 0;
public:
	ListSimplePago();
	void add(int id,ClienteCarreta clienteCarreta);
	ClienteCarreta pop();
	string mostrarLista();
	int getSize(){return size;}
	string cabecera();
};



