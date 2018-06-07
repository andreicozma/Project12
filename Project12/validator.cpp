#include "validator.h"

std::ostream& operator<<(std::ostream &os, const validatorException& ex) {
	for (const auto& a: ex.msgs)
		os << a << "\n";
	return os;
}
void validator::validate(const masina& m) {
	std::vector<std::string> msg;
	if (m.getNrI().size() == 0)msg.push_back("Nr inmatriculare vid!");
	if (m.getProd().size() == 0)msg.push_back("Producator invalid!");
	if (m.getModel().size() == 0)msg.push_back("Model invalid!");
	if (m.getTip().size() == 0)msg.push_back("Tip invalid!");
	if (msg.size() > 0)
		throw validatorException(msg);
}