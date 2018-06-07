#include "service.h"
#include <iterator>
#include<algorithm>
#include<numeric>
#include<fstream>
#include"lista.h"


void service::add(const std::string& nr, const std::string& p, const std::string& m, const std::string& t) {
	masina a{ nr,p,m,t };
	val.validate(a);
	repo->add(a);
	undoAct.push_back(new UndoAdauga{ this->repo, a });
}


void service::remove(const std::string& nrInmatriculare) {
	masina a{ nrInmatriculare,"default","default","default" };
	val.validate(a);
	repo->remove(a);
	undoAct.push_back(new UndoSterge{ this->repo, a });
}


void service::modify(const std::string& nr, const std::string& nr1, const std::string& p, const std::string& m, const std::string& t) {
	masina a{ nr, "default","default","default" };
	masina b{ nr1,p,m,t };
	val.validate(a);
	val.validate(b);
	repo->update(a, b);
	undoAct.push_back(new UndoModifica{ this->repo, a, b });
}
const std::vector<masina>& service::getAll() {
	return(this->repo)->getAll();
}
int service::dim() const {
	return(this->repo)->size();
}
std::vector<masina> service::filtrare_prod(const std::string& prod) {
	std::vector<masina> v;
	v = this->getAll();
	std::vector<masina> r;
	copy_if(v.begin(), v.end(), back_inserter(r), [prod](masina & m) {return m.getProd() == prod; });
	return r;
}
std::vector<masina> service::filtrare_tip(const std::string& tip) {
	std::vector<masina> v;
	v = this->getAll();
	std::vector<masina> r;
	copy_if(v.begin(), v.end(), back_inserter(r), [tip](masina & m) {return m.getTip() == tip; });
	return r;
}
std::vector<masina> service::sortare_nrInmatriculare() {
	auto v = this->getAll();
	sort(v.begin(), v.end(), [](masina& m1, masina &m2) {return m1.getNrI() < m2.getNrI(); });
	return v;
}
std::vector<masina> service::sortare_tip() {
	auto v = this->getAll();
	sort(v.begin(), v.end(), [](masina& m1, masina &m2) {return m1.getTip() < m2.getTip(); });
	return v;
}
std::vector<masina> service::sortare_prodmod() {
	auto v = this->getAll();
	sort(v.begin(), v.end(), [](masina& m1, masina &m2) {return cmpProdMod(m1,m2); });
	return v;
}
void service::golire() {
	(this->listaMas).goleste();
}
void service::adaugaLista(std::string nr) {
	bool ok = 0;
	for (auto a : repo->getAll()) {
		if (a.getNrI() == nr) {
			(this->listaMas).adauga(a);
			ok = 1; break;
		}
	}
	if (ok == 0) {
		throw repoException("Nu exista masini cu nrI respectiv");
	}
}
void service::generareLista(int nr) {
	(this->listaMas).umple(nr, repo->getAll());
}
const std::vector<masina>& service::toateDinLista() {
	return (this->listaMas).slist();

}
void service::salvareCSV(const std::string& numefis, const std::vector<masina>& vect) {
	std::ofstream out(numefis, std::ios::trunc);
	if (!out.is_open()) {
		//throw repoException("Nu s-a putut deschide fisierul" + numefis);
	}
	for (const auto& a : vect) {
		out << a.getNrI() << ",";
		out << a.getProd() << ",";
		out << a.getModel() << ",";
		out << a.getTip() << std::endl;
	}
	out.close();
}
void service::salvareHTML(const std::string& numefis, const std::vector<masina>& vect) {
	std::ofstream out(numefis, std::ios::trunc);
	if (!out.is_open()) {
		//	throw RepoException("Nu s-a putut deschide fisierul " + numefis);
	}
	out << "<html><body>" << std::endl;
	out << "<table border=\"1\" style=\"width:100 % \">" << std::endl;
	for (const auto& a : vect) {
		out << "<tr>" << std::endl;
		out << "<td>" << a.getNrI() << "</td>" << std::endl;
		out << "<td>" << a.getProd() << "</td>" << std::endl;
		out << "<td>" << a.getModel() << "</td>" << std::endl;
		out << "<td>" << a.getTip() << "</td>" << std::endl;
		out << "</tr>" << std::endl;
	}
	out << "</table>" << std::endl;
	out << "</body></html>" << std::endl;
	out.close();

}
void service::undo() {
	if (undoAct.empty()) {
		throw repoException("Nu mai exista operatii");
	}
	ActiuneUndo *act = undoAct.back();
	act->doUndo();
	undoAct.pop_back();
	delete act;
}
service::~service() {
	for (auto act : undoAct) {
		delete act;
	}
}