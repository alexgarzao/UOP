/***************************************************************************
 *   Copyright (C) 2009 by Alex Sandro Garzão   *
 *   alexgarzao@gmail.com   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>

#include "LibuvmDefs.hpp"
#include "BinString.hpp"

/**
	@author Alex Sandro Garzão <alexgarzao@gmail.com>
*/
class CSymbol{
public:
	CSymbol();
    CSymbol(std::string name, LiteralType type, size_t index);
    ~CSymbol();
	std::string toTextAssembly();
	void saveBytecode(CBinString& bytecode);
	bool loadBytecode(CBinString& bytecode);
   const void* getValue();
	void setValue(LiteralType type, const void* value);
	void setValue(LiteralType type, std::string value);
	std::string getString();
	int getInteger();
	double getReal();
	bool getBoolean();

//private:
    std::string _name;
    LiteralType _type;
    size_t _index;
	union {
		int integerValue;
		double realValue;
		bool booleanValue;
		std::string* stringValue;
	} _value;
};

#endif
