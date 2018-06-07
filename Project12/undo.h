#pragma once
#include "masina.h"
#include "repo.h"
class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() {};

};
class UndoAdauga :public ActiuneUndo {
	masina mas;
	Irepo<masina>* rep;
public: 
	UndoAdauga(Irepo<masina>* r, const masina& m) :rep{ r }, mas{ m } {};
	void doUndo()override {
		rep->remove(mas);
	}
};
class UndoSterge :public ActiuneUndo {
	masina mas;
	Irepo<masina>* rep;
public:
	UndoSterge(Irepo<masina>* r, const masina& m) :rep{ r }, mas{ m } {};
	void doUndo()override {
		rep->add(mas);
	}
};
class UndoModifica :public ActiuneUndo {
	masina mas1, mas2;
	Irepo<masina>* rep;
public:
	UndoModifica(Irepo<masina>* r, const masina& m1, const masina& m2) :rep{ r }, mas1{ m1 }, mas2{ m2 } {};
	void doUndo()override {
		rep->update(mas2,mas1);
	}
};