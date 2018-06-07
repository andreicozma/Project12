#include"test.h"
#include<cassert>
#include<vector>
#include<iostream>

void test::teste_repo() {
	int d = 0;
	Irepo<masina>* rep = new repo<masina>;
	Irepo<masina>* frepo = new repoFile<masina>("test.txt");
	masina a{ "teatru", "bun", "fain", "2" };
	rep->add(a);
	d = rep->size();
	frepo->add(a);
	assert(d == 1);
	d = frepo->size();
	masina b{ "si", "sda", "dsaf", "2" };
	rep->add(b);
	frepo->add(b);
	frepo->remove(b);
	auto v = frepo->find(a);
	auto ve = frepo->getAll();
	masina c{ "ioana","silviu","asa","4" };
	frepo->update(a, c);
	d = rep->size();
	assert(d == 2);
	rep->add(c);
	d = rep->size();
	assert(d == 3);
	rep->remove(b);
	d = rep->size();
	assert(d == 2);
	rep->add(b);
	masina e{ "iustin","are","mere","2" };
	rep->update(b, e);
	auto vect = rep->getAll();
	assert(vect.size() == 3);
	auto it = vect.begin();
	masina g = *(it);
	assert(g.getNrI() == "teatru");
	assert(g.getProd() == "bun");
	assert(g.getModel() == "fain");
	assert(g.getTip() == "2");
	auto sil = rep->find(g);
	delete rep;
	delete frepo;
}

void test::teste_ctrl() {
	Irepo<masina>* rep = new repo<masina>;
	service ctrl{ rep };
	masina a{ "","","Ioana","x" };
	ctrl.add("teatru", "bun", "fain", "z");
	ctrl.add("si", "sda", "dsaf", "z");
	ctrl.remove("si" );
	ctrl.add("silviu", "sda", "dsaf","s");
	ctrl.remove("silviu");
	ctrl.remove("teatru");
	ctrl.undo();
	ctrl.add("si", "sda", "dsaf", "@");
	ctrl.modify("si", "iustin", "are", "mere", "2");
	ctrl.undo();
	ctrl.modify("si",  "iustin", "are", "mere", "1 ");
	ctrl.add("Silvan", "Ioana", "fain", " 1");
	ctrl.add("Silva", "I", "z", " ");
	auto l = ctrl.getAll();
	auto vect = ctrl.filtrare_prod("bun");
	vect = ctrl.filtrare_tip("asa");
	vect = ctrl.sortare_nrInmatriculare();
	vect = ctrl.sortare_tip();
	vect = ctrl.sortare_prodmod();
	ctrl.add("ioana", "are", "asa", " ");
	ctrl.undo();
	ctrl.add("ioana", "are", "asa", " ");
	vect = ctrl.sortare_prodmod();
	ctrl.salvareHTML("test", vect);
	ctrl.adaugaLista("Silvan");
	ctrl.generareLista(2);
	ctrl.salvareCSV("teste", vect);
	ctrl.golire();
	delete rep;
}
void test::teste_frepo() {
	Irepo<masina>* frepo = new repoFile<masina>("teste.txt");
	service ctrl2{ frepo };
	masina a{ "","","Ioana","-8"};
	try { ctrl2.undo(); }
	catch (repoException& ve) {
		std::cout << ve;
	}
	ctrl2.add("teatru", "bun", "fain", "2");
	ctrl2.add("si", "sda", "dsaf", "2");
	ctrl2.remove("si");
	ctrl2.add("silviu", "sda", "dsaf", "4");
	ctrl2.remove("silviu");
	ctrl2.remove("teatru");
	ctrl2.undo();
	ctrl2.add("si", "sda", "dsaf", "6");
	ctrl2.modify("si" ,"iustin", "are", "mere", "5");
	ctrl2.undo();
	ctrl2.modify("si", "iustin", "are", "mere", "5");
	ctrl2.add("Silvan", "Ioana", "fain", "4");
	ctrl2.add("Silva", "I", "z", "21");
	auto l = ctrl2.getAll();
	auto vect = ctrl2.filtrare_prod("bun");
	vect = ctrl2.filtrare_tip("asa");
	vect = ctrl2.sortare_prodmod();
	vect = ctrl2.sortare_tip();
	vect = ctrl2.sortare_nrInmatriculare();
	ctrl2.add("ioana", "are", "asa", "1");
	ctrl2.undo();
	ctrl2.add("ioana", "are", "asa", "1");
	try {
		ctrl2.add("ioana", "are", "asa", "1");
	}
	catch (repoException& ve) {
		std::cout << ve;
	}
	try {
		ctrl2.add("", "are", "asa", "0");
	}
	catch (validatorException& ve) {
		std::cout << ve;
	}
	ctrl2.dim();
	vect = ctrl2.sortare_prodmod();
	ctrl2.salvareHTML("test", vect);
	ctrl2.adaugaLista("Silvan");
	try { ctrl2.adaugaLista("sil"); }
	catch (repoException& r) {
		std::cout << r;
	}
	ctrl2.generareLista(2);
	auto sil = ctrl2.toateDinLista();
	ctrl2.salvareCSV("teste", vect);
	ctrl2.golire();
	/*try {
		Irepo<masina>* frepo = new repoFile<masina>("tseste.txt");
	}
	catch (repoException&) {};
	*/
	masina g{ "s","s","s","s" };
	try {
		frepo->find(g);
	}
	catch (repoException&) {};
	try {
		frepo->remove(g);
	}
	catch (repoException&) {};
	try {
		frepo->update(g, a);
	}
	catch (repoException&) {};
	delete frepo;
}

void test::run_tests() {
	teste_ctrl();
	teste_repo();
	teste_frepo();
}