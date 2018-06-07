#include "consola.h"
#include<iostream>
#include<string>

void consola::run_meniu() {
	std::cout << "1.Adaugare masina" << "\n";
	std::cout << "2.Stergere masina" << "\n";
	std::cout << "3.Modificare masina" << "\n";
	std::cout << "4.Afisare masina" << "\n";
	std::cout << "5.Filtrare" << "\n";
	std::cout << "6.Sortare" << "\n";
	std::cout << "7.Goleste lista" << "\n";
	std::cout << "8.Adauga in lista" << "\n";
	std::cout << "9.Genereaza lista" << "\n";
	std::cout << "10.Salveaza lista in fisier" << "\n";
	std::cout << "11.Afisare lista" << "\n";
	std::cout << "12.Undo" << "\n";
	std::cout << "0.Exit" << "\n";
}
void consola::show_add() {
	std::string nrI;
	std::string producator;
	std::string tip;
	std::string model;
	std::cout << "Introduceti nrInmatriculare: ";
	std::cin >> nrI;

	std::cout << "Introduceti producatorul: ";
	std::cin >> producator;

	std::cout << "Introduceti modelul: ";
	std::cin >> model;

	std::cout << "Introduceti tipul: ";
	std::cin >> tip;

	(this->serv).add(nrI, producator, model, tip);
	std::cout << "Adaugat cu succes!!" << "\n";
}
void consola::show_remove() {
	std::string nr;

	std::cout << "Introduceti nrInmatriculare: ";
	std::cin >> nr;

	serv.remove(nr);
	std::cout << "Sters cu succes!!" << "\n";

}

void consola::show_modify() {
	std::string nr;

	std::cout << "Introduceti nrInmatriculare: ";
	std::cin >> nr;


	std::string nr1;
	std::string p;
	std::string m;
	std::string t;
	std::cout << "Introduceti nrInmatriculare nou: ";
	std::cin >> nr1;

	std::cout << "Introduceti producatorul nou: ";
	std::cin >> p;

	std::cout << "Introduceti modelul nou: ";
	std::cin >> m;

	std::cout << "Introduceti tipul nou: ";
	std::cin >> t;

	serv.modify(nr, nr1, p, m, t);

	std::cout << "Modificat cu succes!!" << "\n";

}
void consola::show_filtrare() {
	std::cout << "1.Producator" << "\n";
	std::cout << "2.Tip" << "\n";
	int cmd;
	std::cin >> cmd;
	std::string prod{ "" };
	std::string tip{ "" };
	std::vector<masina> ve;
	switch (cmd) {
	case 1:
		std::cout << "Introduceti producatorul: ";
		std::cin >> prod;
		ve = this->serv.filtrare_prod(prod);
		break;

	case 2:
		std::cout << "Introduceti tipul: ";
		std::cin >> tip;
		ve = this->serv.filtrare_tip(tip);
		break;
	default:
		std::cout << "Optiune invalida!" << "\n";
	}
	show_all(ve);

}
void consola::show_sortare() {
	std::cout << "1.NrInmatriculare" << "\n";
	std::cout << "2.Tip" << "\n";
	std::cout << "3.Producator + model" << "\n";
	int cmd;
	std::cin >> cmd;
	std::vector<masina> ve;
	switch (cmd) {
	case 1:
		ve = this->serv.sortare_nrInmatriculare();
		break;
	case 2:
		ve = this->serv.sortare_tip();
		break;
	case 3:
		ve = this->serv.sortare_prodmod();
		break;
	default:
		std::cout << "Optiune invalida!" << "\n";
	}
	show_all(ve);
}
void consola::show_all(const std::vector<masina> all) {
	if (all.size() == 0) {
		std::cout << "Nu exista masini!!" << "\n";
	}
	else {
		for (const auto& a : all) {
			std::cout << "NrInmatriculare: " << a.getNrI() << " ,Producator: " << a.getProd();
			std::cout << " ,Model: " << a.getModel() << " ,Tip:" << a.getTip() << "\n";
		}
	}

}
int consola::getcmd() {
	int cmd{ 0 };
	std::cout << "Introduceti optiunea:";
	std::cin >> cmd;
	return cmd;

}
void consola::show_golire() {
	this->serv.golire();
	std::cout << "Lista golita" << "\n";
	int i = serv.toateDinLista().size();
	std::cout << "In lista sunt " << i << " masini" << "\n";
}
void consola::show_adaugaLista() {
	std::string nri;
	std::cout << "Introduceti nr de inmatriculare: ";
	std::cin >> nri;
	if (nri.size() == 0) {
		std::cout << "Nr de inmatriculare nu poate fi vid" << "\n";
	}
	else {
		serv.adaugaLista(nri);
		std::cout << "Adaugat cu succes" << "\n";
		int i = serv.toateDinLista().size();
		std::cout << "In lista sunt " << i << " activitati" << "\n";
	}
}
void consola::show_generare() {
	int nr;
	std::cout << "Introduceti numarul:" << "\n";
	std::cin >> nr;
	serv.generareLista(nr);
	show_all(serv.toateDinLista());
	int i = serv.toateDinLista().size();
	std::cout << "In lista sunt " << i << " masini" << "\n";
}
void consola::show_salvare() {
	std::cout << "1.CSV" << "\n";
	std::cout << "2.HTML" << "\n";
	std::cout << "Introduceti optiunea" << "\n";
	int cm;
	std::cin >> cm;
	std::string nume;
	std::cout << "Introduceti numele fisierului" << "\n";
	std::cin >> nume;
	switch (cm)
	{
	case 1:
		serv.salvareCSV(nume, serv.toateDinLista());
		std::cout << "Salvat cu succes" << "\n";
		break;
	case 2:
		serv.salvareHTML(nume, serv.toateDinLista());
		std::cout << "Salvat cu succes" << "\n";
		break;
	default:
		std::cout << "Comanda invalida" << "\n";
		break;
	}
}
void consola::show_undo() {
	serv.undo();
	std::cout << "Undo efectuat cu succes" << "\n";
}
void consola::run_main() {
	int cmd{ 0 };
	while (true) {
		run_meniu();
		cmd = getcmd();
		try {
			switch (cmd) {
			case 0:
				return;
			case 1:
				show_add();
				std::cout << "=============================================================" << "\n";
				break;
			case 2:
				show_remove();
				std::cout << "=============================================================" << "\n";
				break;
			case 3:
				show_modify();
				std::cout << "=============================================================" << "\n";
				break;
			case 4:
				show_all(serv.getAll());
				std::cout << "=============================================================" << "\n";
				break;
			case 5:
				show_filtrare();
				std::cout << "=============================================================" << "\n";
				break;
			case 6:
				show_sortare();
				std::cout << "=============================================================" << "\n";
				break;
			case 7:
				show_golire();
				std::cout << "=============================================================" << "\n";
				break;
			case 8:
				show_adaugaLista();
				std::cout << "=============================================================" << "\n";
				break;
			case 9:
				show_generare();
				std::cout << "=============================================================" << "\n";
				break;
			case 10:
				show_salvare();
				std::cout << "=============================================================" << "\n";
				break;
			case 11:
				show_all(serv.toateDinLista());
				std::cout << "=============================================================" << "\n";
				break;
			case 12:
				show_undo();
				std::cout << "=============================================================" << "\n";
				break;
			default:
				std::cout << "Optiune invalida!!" << "\n";
			}
		}
		catch (repoException& ex) {
			std::cout << ex << "\n";
		}
		catch (validatorException& ex) {
			std::cout << ex << "\n";
		}

	}
}