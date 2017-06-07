#ifndef LIBUVM_ENTITY_DEFINITION_HPP
#define LIBUVM_ENTITY_DEFINITION_HPP

// namespace ASSEMBLY_DEFINITION {

#include <vector>

class CEntityDefinition;

#include "SymbolTable.hpp"
#include "PropertyDefinition.hpp"
#include "MethodDefinition.hpp"
#include "LibuvmDefs.hpp"
#include "BinString.hpp"

class CEntityDefinition
{
public:
	CEntityDefinition(CSymbolTable *symbolTable);
	CEntityDefinition(CSymbolTable *_symbolTable, std::string name);
	CPropertyDefinition *addProperty(VisibilityType visibility, LiteralType type, std::string name);
	CMethodDefinition *addMethod(VisibilityType visibility, std::string name);
	size_t getSymbolIndex(std::string name, LiteralType type);
	SymbolType getSymbolType(std::string name);
	CSymbol* getSymbolByIndex(size_t index);
	std::string toTextAssembly(bool high_level);
	void saveBytecode(CBinString& bytecode);
	bool loadBytecode(CBinString& bytecode);
	CMethodDefinition* getMethod(std::string name);
	std::string getName() const
	{
		return _name;
	}
	bool isParallel(); // const;
	void setOption(std::string option);
	CPropertyDefinition* findProperty(std::string identifier);
	std::vector<CPropertyDefinition*> _propertyList;
private:
	std::vector<CMethodDefinition*> _methodList;
	CSymbolTable *_symbolTable;
	std::string _name;
	std::map<std::string,std::string> _optionList;
};

#endif

