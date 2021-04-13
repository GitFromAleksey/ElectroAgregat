/*
 * Integer.h
 *
 *  Created on: 14 сент. 2020 г.
 *      Author: borzenkov
 */

#ifndef INTEGER_H_
#define INTEGER_H_

class Integer
{
	public:
		int value;

		Integer();
		virtual ~Integer();

		void operator=(const int i)
		{
			value = i;
		}

		void operator++() // prefix
		{
			++value;
		}
		void operator--() // prefix
		{
			--value;
		}
		Integer operator++(int) // postfix
		{
			Integer i = *this;
			this->value++;
			return i;
		}
		Integer operator--(int) // postfix
		{
			Integer i = *this;
			this->value--;
			return i;
		}

		void operator+=(int v)
		{
			this->value += v;
		}

		void operator-=(int v)
		{
			this->value -= v;
		}

		void PrintValue() const
		{
			std::cout << "value = "<< value << std::endl;
		}

	private:

};

#endif /* INTEGER_H_ */
