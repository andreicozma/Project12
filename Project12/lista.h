#pragma once
#include<vector>
#include<algorithm>
#include<random>
#include<chrono>
#include"masina.h"
class lista
{
	std::vector<masina> list;
public:
	lista()=default;
	void adauga(const masina &m) {
		list.push_back(m);
	}
	void goleste() {
		list.clear();
	}
	void umple(std::size_t nr, std::vector<masina> all) {
		std::shuffle(all.begin(), all.end(), std::default_random_engine(std::random_device{}()));
		while (list.size() < nr&& all.size() > 0) {
			list.push_back(all.back());
			all.pop_back();
		}
	}
	const std::vector<masina>& slist()const {
		return list;
	}
};

