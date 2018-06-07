#include "masina.h"

void masina::operator=(const masina& m) {
	this->nrI = m.nrI;
	this->prod = m.prod;
	this->model = m.model;
	this->tip = m.tip;
}

//cpy-constr
masina::masina(const masina &m)
{
	this->nrI = m.nrI;
	this->prod = m.prod;
	this->model = m.model;
	this->tip = m.tip;
}

bool cmpProdMod(const masina& m1, const masina& m2) {
	if (m1.getProd() < m2.getProd())
		return true;
	else if (m1.getProd() == m2.getProd())
		if (m1.getModel() < m2.getModel())
			return true;
	return false;
}
bool masina::operator==(const masina& m) {
	return m.nrI == this->nrI;
}