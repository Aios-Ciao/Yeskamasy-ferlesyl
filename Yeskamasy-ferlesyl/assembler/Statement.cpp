#include <vector>
#include <string>
#include "Statement.h"

Statement::Statement()
	: mnemonic(nullptr)
{

}

Statement::~Statement()
{

}

// １ステートメントを逆アセしたように文字列に直す
std::string Statement::ToString()
{
	std::string statement;

	statement += mnemonic->getName() + " ";
	for (Mnemonic::tParamCount idx = 0; idx < mnemonic->getParamCount(); ++idx) {
		Mnemonic::tParamCount pos = mnemonic->getParamIndex(idx, eci);

		Parameter &prm = param[pos];

		switch (prm.type) {
		case Parameter::eptImmidiate:
			statement += prm.imm;
			break;
		case Parameter::eptCondition:
			statement += prm.cond;
			break;
		case Parameter::eptLabel:
			statement += prm.label;
			break;
		case Parameter::eptRegister:
			statement += Parameter::RegNameFrom(prm.base);
			break;
		case Parameter::eptReg_Ofs_Imm:
			statement += Parameter::RegNameFrom(prm.base);
			if (prm.imm != 0) {
				statement += "+";
				statement += prm.imm;
			}
			statement += "@";
			break;
		case Parameter::eptReg_Ofs_Reg:
			statement += Parameter::RegNameFrom(prm.base) + "+";
			statement += Parameter::RegNameFrom(prm.dsp) + "@";
			break;
		default:
			break;
		}

		if (idx < (mnemonic->getParamCount() - 1)) {
			statement += " ";
		}

	}

	return( statement );
}

