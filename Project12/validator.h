#pragma once
#include"masina.h"
#include<vector>
#include<iostream>
class validatorException
{
private:
	std::vector<std::string>msgs;
public:
	validatorException(std::vector<std::string>msg) :msgs{ msg } {};
	~validatorException() = default;
	friend std::ostream& operator<<(std::ostream& os, const validatorException & msg);

};
class validator {
public:
	void validate(const masina& m);
};

