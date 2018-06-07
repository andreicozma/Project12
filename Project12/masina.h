#pragma once
#include <string>
#include <iostream>

class masinaException {
	std::string msg;
	public:
		masinaException(const std::string &ms) :msg{ ms } {};
		std::string getMsg()const { return  msg; }
};
class masina
{
private:
	std::string nrI;
	std::string prod;
	std::string model;
	std::string tip;
public:
	//constructor
	masina() {};
	masina(std::string _nr, std::string _p, std::string _m, std::string _t) : nrI{ _nr }, prod{ _p }, model{ _m }, tip{ _t } {};

	//destructor
	~masina() = default;

	//copy-constructor
	masina(const masina& mas);

	//assignment operator
	void operator=(const masina& mas);
	std::string getNrI()const { return this->nrI; }
	std::string getProd()const { return this->prod; }
	std::string getModel()const { return this->model; }
	std::string getTip()const { return this->tip; }
	void setNrI(std::string n) {
		this->nrI = n;
	}
	void setProd(std::string p) {
		this->prod = p;
	}
	void setModel(std::string m) {
		this->model = m;
	}
	void setTip(std::string t) {
		this->tip = t;
	}
	friend std::istream& operator >> (std::istream & is, masina m) {
		is >> m.nrI >> m.prod >> m.model >> m.tip;
		return is;
	}
	friend std::ostream& operator <<(std::ostream & os, masina m) {
		os << m.nrI << m.prod << m.model << m.tip;
		return os;
	}
	bool operator==(const masina& m);
};

bool cmpProdMod(const masina& m1, const masina& m2);

