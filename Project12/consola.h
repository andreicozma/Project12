#pragma once
#include"service.h"
class consola {
private:
	service & serv;
	int getcmd();
	void run_meniu();
	void show_add();
	void show_remove();
	void show_modify();
	void show_all(std::vector<masina> vd);
	void show_filtrare();
	void show_sortare();
	void show_golire();
	void show_adaugaLista();
	void show_generare();
	void show_salvare();
	void show_undo();
public:
	consola(service& ct) :serv{ ct } {};
	void run_main();
};
