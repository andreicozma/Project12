#pragma once
#include"repo.h"
#include"validator.h"
#include"undo.h"
#include"lista.h"
#include"masina.h"
class service
{
private:
	Irepo<masina>* repo;
	validator val;
	lista listaMas;
	std::vector<ActiuneUndo*> undoAct;
public:
	service(Irepo<masina>* re) :repo{ re } {};
	service(const service& m) = delete;
	void operator=(const service& s) = delete;
	~service();
	void add(const std::string& nr, const std::string& p, const std::string& m, const std::string& t);
	void remove(const std::string& nr);
	void modify(const std::string& nr1, const std::string& nr, const std::string&p, const std::string&m, const std::string&t);
	const std::vector<masina>& getAll();
	int dim()const;
	std::vector<masina> filtrare_prod(const std::string& prod);

	std::vector<masina> filtrare_tip(const std::string& tip);

	std::vector<masina> sortare_nrInmatriculare();

	std::vector<masina> sortare_tip();

	std::vector<masina> sortare_prodmod();
	void golire();
	void adaugaLista(std::string nr);
	void generareLista(int nr);
	const std::vector<masina>& toateDinLista();
	void salvareCSV(const std::string& numefis, const std::vector<masina>& vect);
	void salvareHTML(const std::string& numefis, const std::vector<masina>& vect);
	void undo();
};

