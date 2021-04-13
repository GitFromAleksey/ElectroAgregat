/*
 * cRegisterBase.h
 *
 *  Created on: 25 но€б. 2020 г.
 *      Author: borzenkov
 */

#ifndef CMYUINT32T_H_
#define CMYUINT32T_H_

#include <stdint.h>
#include <iostream>



using namespace std;
// базовый класс регистров
class cMyUint32_t
{
	public:
		cMyUint32_t();
		virtual ~cMyUint32_t();

		void Init(string name, uint32_t initVal);

		void operator = (cMyUint32_t & left);
		void operator = (const uint32_t & left);
		void operator |= (const uint32_t & right);
		void operator &= (const uint32_t & right);
		bool operator == (const uint32_t & right);
		uint32_t operator & (const uint32_t & right);
		uint32_t operator | (const uint32_t & right);
		void operator += (const uint32_t & right);
		void operator -= (const uint32_t & right);
		uint32_t operator ++ (); // префиксна€
		uint32_t operator -- (); // префиксна€

		uint32_t operator ++ (int); // постфиксна€
		uint32_t operator -- (int); // постфиксна€

		uint32_t GetValue()const;
		void Print(string str);
		void Print(string str, uint32_t value);
		void Print(uint32_t value);

	private:
		string m_name;
		uint32_t m_RegisterValue;

};


#endif /* CMYUINT32T_H_ */
