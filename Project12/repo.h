#pragma once
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>

class repoException {
private:
	std::string msg;
public:
	repoException(const std::string& ms) :msg{ ms } {};
	std::string getMsg()const { return msg; }
	friend std::ostream& operator<<(std::ostream& os, const repoException& msg);
};

template <typename T>
class Irepo {
protected:
	std::vector<T> elems;
public:
	virtual void add(const T&) = 0;
	virtual void remove(const T&) = 0;
	virtual void update(const T&, const T&) = 0;
	virtual int size() = 0;
	virtual const T& find(const T&) = 0;
	virtual std::vector<T>& getAll() = 0;
};

template<typename T>
class repo :public Irepo<T> {
public:
	//constructor
	repo() {};
	//nu vreau sa se poata copia un repo
	repo(const repo& ot) = delete;

	//adaugare
	virtual void add(const T& t)override {
		auto it = std::find(this->elems.begin(), this->elems.end(), t);
		if (it != this->elems.end()) {
			throw repoException{ "Elementul exista!" };
		}
		this->elems.push_back(t);
	}

	//stergere
	virtual void remove(const T& t)override {
		auto it = std::find(this->elems.begin(), this->elems.end(), t);
		if (it == this->elems.end()) {
			throw repoException{ "Elementul nu exista!" };
		}
		this->elems.erase(it);
	}

	//modificare
	virtual void update(const T& vechi, const T& nou)override {
		auto it = std::find(this->elems.begin(), this->elems.end(), vechi);
		if (it == this->elems.end()) {
			throw repoException{ "Elementul nu exista!" };
		}
		replace(this->elems.begin(), this->elems.end(), *it, nou);
		//.erase(it);
		//elems.push_back(nou);

	}

	//dimensiune
	virtual int size() override {
		return this->elems.size();
	}

	//cautare
	virtual const T& find(const T& t)override {
		auto it = std::find(this->elems.begin(), this->elems.end(), t);
		if (it == this->elems.end()) {
			throw repoException{ "Nu exista!" };
		}
		return *it;
	}

	//toate elementele
	virtual std::vector<T>& getAll() override {
		return this->elems;
	}
};

template <typename T>
class repoFile :public repo<T> {
private:
	std::string fileName;
	void store() {
		std::ofstream fout{ fileName };
		if (!fout.is_open()) {
			//throw RepoException{"Fisier invalid!"};
		}
		for (auto& el : this->elems) {
			fout << el << "\n";
		}
		fout.close();
	}
	void load() {
		std::ifstream fin{ fileName };
		if (!fin.is_open()) {
			throw repoException{ "Fisier invalid!" };
		}
		T t;
		while (fin >> t) {
			this->elems.push_back(t);
		}
		fin.close();
	}

public:
	repoFile(std::string nume) :fileName{ nume } { load(); };
	void add(const T& t)override {
		repo<T>::add(t);
		store();
	}
	void remove(const T& t)override {
		repo<T>::remove(t);
		store();
	}
	void update(const T& v, const T& n)override {
		repo<T>::update(v, n);
		store();
	}
};

