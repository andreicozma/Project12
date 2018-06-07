#include"teste.h"
#include<cassert>
#include<vector>
#include<iostream>

void Test::teste_repo() {
	int d = 0;
	IRepo<Activitate>* repo = new Repo<Activitate>;
	IRepo<Activitate>* frepo = new FileRepo<Activitate>("test.txt");
	Activitate a{ "teatru", "bun", "fain", 2 };
	repo->add(a);
	d = repo->size();
	frepo->add(a);
	assert(d == 1);
	d = frepo->size();
	Activitate b{ "si", "sda", "dsaf", 3 };
	repo->add(b);
	frepo->add(b);
	frepo->remove(b);
	auto v = frepo->find(a);
	auto ve = frepo->getAll();
	Activitate c{ "ioana","silviu","asa",8 };
	frepo->update(a, c);
	d = repo->size();
	assert(d == 2);
	repo->add(c);
	d = repo->size();
	assert(d == 3);
	repo->remove(b);
	d = repo->size();
	assert(d == 2);
	repo->add(b);
	Activitate e{ "iustin","are","mere",5 };
	repo->update(b, e);
	auto vect = repo->getAll();
	assert(vect.size() == 3);
	auto it = vect.begin();
	Activitate g = *(it);
	assert(g.getTitlu() == "teatru");
	assert(g.getDescriere() == "bun");
	assert(g.getTip() == "fain");
	assert(g.getDurata() == 2);
	auto sil = repo->find(g);
	delete repo;
	delete frepo;
}

void Test::teste_ctrl() {
	int d = 0;
	IRepo<Activitate>* repo = new Repo<Activitate>;
	Controller ctrl{ repo };
	Activitate a{ "","","Ioana",-8 };
	ctrl.add("teatru", "bun", "fain", 2);
	ctrl.add("si", "sda", "dsaf", 3);
	ctrl.remove("si", "sda", "dsaf", 3);
	ctrl.add("silviu", "sda", "dsaf", 3);
	ctrl.remove("silviu", "sda", "dsaf", 3);
	ctrl.remove("teatru", "bun", "fain", 2);
	ctrl.undo();
	ctrl.add("si", "sda", "dsaf", 3);
	ctrl.modify("si", "sda", "dsaf", 3, "iustin", "are", "mere", 5);
	ctrl.undo();
	ctrl.modify("si", "sda", "dsaf", 3, "iustin", "are", "mere", 5);
	ctrl.add("Silvan", "Ioana", "fain", 4);
	ctrl.add("Silva", "I", "z", 21);
	auto l = ctrl.getAll();
	auto vect = ctrl.filtrare_descriere("bun");
	vect = ctrl.filtrare_tip("asa");
	vect = ctrl.sortare_tip_durata();
	vect = ctrl.sortare_titlu();
	vect = ctrl.sortare_descriere();
	ctrl.add("ioana", "are", "asa", 9);
	ctrl.undo();
	ctrl.add("ioana", "are", "asa", 9);
	vect = ctrl.sortare_tip_durata();
	ctrl.salvareHTML("test", vect);
	ctrl.adaugaLista("Silvan");
	ctrl.generareLista(2);
	ctrl.salvareCSV("teste", vect);
	ctrl.golire();
	auto de = ctrl.dim();
	delete repo;
}
void Test::teste_frepo(){
	IRepo<Activitate>* frepo = new FileRepo<Activitate>("teste.txt");
	Controller ctrl2{ frepo };
	Activitate a{ "","","Ioana",-8 };
	try { ctrl2.undo(); }
	catch (RepoException& ve) {
		std::cout << ve;
	}
	ctrl2.add("teatru", "bun", "fain", 2);
	ctrl2.add("si", "sda", "dsaf", 3);
	ctrl2.remove("si", "sda", "dsaf", 3);
	ctrl2.add("silviu", "sda", "dsaf", 3);
	ctrl2.remove("silviu", "sda", "dsaf", 3);
	ctrl2.remove("teatru", "bun", "fain", 2);
	ctrl2.undo();
	ctrl2.add("si", "sda", "dsaf", 3);
	ctrl2.modify("si", "sda", "dsaf", 3, "iustin", "are", "mere", 5);
	ctrl2.undo();
	ctrl2.modify("si", "sda", "dsaf", 3, "iustin", "are", "mere", 5);
	ctrl2.add("Silvan", "Ioana", "fain", 4);
	ctrl2.add("Silva", "I", "z", 21);
	auto l= ctrl2.getAll();
	auto vect = ctrl2.filtrare_descriere("bun");
	vect = ctrl2.filtrare_tip("asa");
	vect = ctrl2.sortare_tip_durata();
	vect = ctrl2.sortare_titlu();
	vect = ctrl2.sortare_descriere();
	ctrl2.add("ioana", "are", "asa", 9);
	ctrl2.undo();
	ctrl2.add("ioana", "are", "asa", 9);
	try {
		ctrl2.add("ioana", "are", "asa", 9);
	}catch (RepoException& ve) {
		std::cout << ve;
	}
	try {
		ctrl2.add("", "are", "asa", -9);
	}catch (ValidateException& ve) {
		std::cout << ve;
	}
	vect = ctrl2.sortare_tip_durata();
	ctrl2.salvareHTML("test", vect);
	ctrl2.adaugaLista("Silvan");
	try { ctrl2.adaugaLista("sil"); }
	catch (RepoException& r) {
		std::cout << r;
	}
	ctrl2.generareLista(2);
	auto sil = ctrl2.toateDinLista();
	ctrl2.salvareCSV("teste", vect);
	ctrl2.golire();
	try {
		IRepo<Activitate>* frepo = new FileRepo<Activitate>("tseste.txt");
	}catch (RepoException&) {};
	Activitate g{ "s","s","s",9 };
	try {
		frepo->find(g);
	}catch (RepoException&) {};
	try {
		frepo->remove(g);
	}catch (RepoException&) {};
	try {
		frepo->update(g,a);
	}catch (RepoException&) {};
	delete frepo;
}

void Test::run_tests() {
	teste_ctrl();
	teste_repo();
	teste_frepo();
}