/***************************************************************************
 *   Copyright (C) 2009 by Alex Sandro Garzão                              *
 *   alexgarzao@gmail.com                                                  *
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
#include <map>

#include <sys/types.h>

#include "Literal.hpp"

#include "Tools.hpp"

CLiteral::CLiteral()
{
	_type = UserdataType; // TODO: nao deveria ter um tipo especifico ???
	memset(&_value, 0, sizeof(_value));
}

CLiteral::CLiteral(const CLiteral& literal)
{
	_type = literal._type;
	_value = literal._value;
	if (_type == StringType) {
		_value.stringValue = new std::string();
		*_value.stringValue = *literal._value.stringValue;
	} else if (_type == TableType) {
		// TODO: O codigo abaixo nao pode ficar comentado !!! Eh so um teste !!!
		// TODO: desse jeito, as tabelas sao passadas sempre por referencia na pilha, e nunca por valor
// 		_value.tableValue = new CMultiIndex<CLiteral>();
// 		*_value.tableValue = *literal._value.tableValue;
	} else if (_type == TupleType) {
		_value.tupleValue = new CTuple();
		*_value.tupleValue = *literal._value.tupleValue;
	}
	_events = literal._events;
}

CLiteral::CLiteral(LiteralType type, const void* value)
{
	setValue(type, value);
}

CLiteral::CLiteral(LiteralType type)
	: _type(type)
{
	if (_type == StringType) {
		_value.stringValue = new std::string();
	} else if (_type == IntegerType) {
		_value.integerValue = 0;
	} else if (_type == RealType) {
		_value.realValue = 0.0;
	} else if (_type == BooleanType) {
		_value.booleanValue = false;
	} else if (_type == ElementType) {
		_value.elementValue = new CElement();
	} else if (_type == UserdataType) {
		//_value.elementValue = new CElement();
		//TODO: userdata
	} else if (_type == TableType) {
		_value.tableValue = new CMultiIndex<CLiteral>();
	} else if (_type == TupleType) {
		_value.tupleValue = new CTuple();
	} else if (_type == PointerType) {
		_value.pointerValue = NULL;
	}
}


CLiteral::~CLiteral()
{
}

const void* CLiteral::getValue()
{
	if (_type == StringType) {
		return _value.stringValue;
	} else if (_type == ElementType) {
		return _value.elementValue;
	} else if (_type == TableType) {
		return _value.tableValue;
	} else if (_type == TupleType) {
		return _value.tupleValue;
	} else if (_type == PointerType) {
		return _value.pointerValue;
	} else {
		return &_value;
	}
	//TODO: userdata
}

// void CLiteral::setValue(const void* value)
// {
// }

void CLiteral::setValue(LiteralType type, const void* value)
{
	_type = type;

	if (_type == StringType) {
		_value.stringValue = new std::string();
		*_value.stringValue = *((std::string*) value);
	} else if (_type == ElementType) {
		_value.elementValue = ((CElement*) value);
	} else if (_type == TableType) {
		_value.tableValue = new CMultiIndex<CLiteral>();
		*_value.tableValue = *((CMultiIndex<CLiteral>*) value);
	} else if (_type == TupleType) {
		_value.tupleValue = new CTuple();
		*_value.tupleValue = *((CTuple*) value);
	} else {
		std::map<LiteralType, size_t> typeSizeMap;

		typeSizeMap[IntegerType] = sizeof(int);
		typeSizeMap[RealType] = sizeof(double);
		typeSizeMap[BooleanType] = sizeof(bool);
		typeSizeMap[PointerType] = sizeof(void*);
//		typeSizeMap[ElementType] = sizeof(CElement*);

		memcpy(&_value, value, typeSizeMap[type]);
	}
	// TODO: userdata

}

std::string CLiteral::getText()
{
	if ( _type == StringType) {
		return *_value.stringValue;
	} else if (_type == IntegerType) {
		return itoa(_value.integerValue);
	} else if (_type == RealType) {
		return ftoa(_value.realValue);
	} else if (_type == BooleanType) {
		// TODO: fazer conversao descente...
		if (_value.booleanValue == true) {
			return "true";
		} else {
			return "false";
		}
	} else if (_type == ElementType) {
		return "Element*";
	} else if (_type == TableType) {
		// TODO: poderia converter os literais para string e retornar...
		return "Table*";
	} else if (_type == PointerType) {
		// TODO: poderia converter os literais para string e retornar...
		return "Pointer*";
	} else if (_type == TupleType) {
		// TODO: poderia converter para string e retornar...
		std::string result;
		result += "Keys: [";
		result += _value.tupleValue->getComposedKeys();
		result += "] Values: [";
		result += _value.tupleValue->getComposedValues();
		result += "]";
		return result;
	}

	// TODO: userdata
	return "Invalid literal value !!!";
}

std::string CLiteral::getString()
{
	return *_value.stringValue;
}

int CLiteral::getInteger()
{
	return _value.integerValue;
}

double CLiteral::getReal()
{
	return _value.realValue;
}

bool CLiteral::getBoolean()
{
	return _value.booleanValue;
}

CElement* CLiteral::getElement()
{
	return _value.elementValue;
}

CMultiIndex<CLiteral>* CLiteral::getTable()
{
	return _value.tableValue;
}

CTuple* CLiteral::getTuple()
{
	return _value.tupleValue;
}

void* CLiteral::getPointer()
{
	return _value.pointerValue;
}

// TODO: trocar nome da funcao para serialize ???
void CLiteral::saveBytecode(CBinString& bytecode)
{
	bytecode.save(&_type, sizeof(_type));

	if (_type == StringType) {
		bytecode.save(*_value.stringValue);
	} else if (_type == IntegerType) {
		bytecode.save(&_value.integerValue, sizeof(_value.integerValue));
	} else if (_type == RealType) {
		bytecode.save(&_value.realValue, sizeof(_value.realValue));
	} else if (_type == BooleanType) {
		bytecode.save(&_value.booleanValue, sizeof(_value.booleanValue));
	} else {
		std::cout << "serializacao nao implementada para tipo " << _type << " (" << (char) _type << ")" << std::endl;
	}
}

bool CLiteral::loadBytecode(CBinString& bytecode)
{
	bytecode.load(&_type, sizeof(_type));

	if (_type == StringType) {
		std::string value;
		bytecode.load(value);
		_value.stringValue = new std::string(value);
	} else if (_type == IntegerType) {
		bytecode.load(&_value.integerValue, sizeof(_value.integerValue));
	} else if (_type == RealType) {
		bytecode.load(&_value.realValue, sizeof(_value.realValue));
	} else if (_type == BooleanType) {
		bytecode.load(&_value.booleanValue, sizeof(_value.booleanValue));
	} else {
		std::cout << "serializacao nao implementada para tipo " << _type << " (" << (char) _type << ")" << std::endl;
	}

	return true;
}


void CLiteral::bind_event(std::string event_name, CMethodDefinition* method)
{
	_events[event_name] = method;
}
