/*
 * cRegisterBase.cpp
 *
 *  Created on: 25 нояб. 2020 г.
 *      Author: borzenkov
 */

#include "cMyUint32t.h"

cMyUint32_t::cMyUint32_t() :
m_name(""),
m_RegisterValue(0)
{

}

cMyUint32_t::~cMyUint32_t()
{

}

void cMyUint32_t::Init(string name, uint32_t initVal)
{
	m_name = name;
	m_RegisterValue = initVal;
}

void cMyUint32_t::operator = (cMyUint32_t & left)
{
	Print("= 0x", this->m_RegisterValue);
	left.m_RegisterValue = this->m_RegisterValue;
}

void cMyUint32_t::operator = (const uint32_t & left)
{
	Print("= 0x", left);
	this->m_RegisterValue = left;
}

void cMyUint32_t::operator|=(const uint32_t & right)
{
	Print("|= 0x", right);
	this->m_RegisterValue |= right;
}

void cMyUint32_t::operator &= (const uint32_t & right)
{
	Print("&= 0x", right);
	this->m_RegisterValue &= right;
}

bool cMyUint32_t::operator == (const uint32_t & right)
{
	Print( "== ", (this->m_RegisterValue == right) );
	return (this->m_RegisterValue == right);
}

uint32_t cMyUint32_t::operator & (const uint32_t & right)
{
	Print( "& ", (this->m_RegisterValue & right) );
	return (this->m_RegisterValue & right);
}

uint32_t cMyUint32_t::operator | (const uint32_t & right)
{
	Print( "| ", (this->m_RegisterValue | right) );
	return (this->m_RegisterValue | right);
}

void cMyUint32_t::operator += (const uint32_t & right)
{
	Print("+= 0x", right);
	this->m_RegisterValue += right;
}

void cMyUint32_t::operator -= (const uint32_t & right)
{
	Print("-= 0x", right);
	this->m_RegisterValue -= right;
}
// префиксная
uint32_t cMyUint32_t::operator ++ ()
{
	this->m_RegisterValue++;
	Print("++Val = 0x", this->m_RegisterValue);
	return (this->m_RegisterValue);
}
// префиксная
uint32_t cMyUint32_t::operator -- ()
{
	this->m_RegisterValue--;
	Print("--Val = 0x", this->m_RegisterValue);
	return (this->m_RegisterValue);
}

// постфиксная
uint32_t cMyUint32_t::operator ++ (int)
{
	uint32_t oldVal = this->m_RegisterValue;
	this->m_RegisterValue++;
	Print("Val++ = 0x", this->m_RegisterValue);
	return oldVal;
}
// постфиксная
uint32_t cMyUint32_t::operator -- (int)
{
	uint32_t oldVal = this->m_RegisterValue;
	this->m_RegisterValue--;
	Print("Val-- = 0x", this->m_RegisterValue);
	return oldVal;
}


uint32_t cMyUint32_t::GetValue()const
{
	return m_RegisterValue;
}
void cMyUint32_t::Print(string str)
{
	cout << m_name << " " << str << endl;
}
void cMyUint32_t::Print(string str, uint32_t value)
{
	cout << m_name << " " << str << hex << value << endl;
}
void cMyUint32_t::Print(uint32_t value)
{
	cout << m_name << " " << hex << value << endl;
}
