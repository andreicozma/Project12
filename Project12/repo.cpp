#include "repo.h"

std::ostream & operator<<(std::ostream& os, const repoException& ex) {
	os << ex.getMsg();
	return os;
}