// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

TBitField::TBitField(int len)
{
	BitLen = len;
	if (len <= 0)
	{
		throw "Incorrect length";
	}
	MemLen = GetMemIndex(len);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[]pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / (8 * sizeof(TELEM)) + 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << ((n - 1) % 32);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen)
	{
		throw "Incorrect length";
	}
	pMem[GetMemIndex(n) - 1] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen)
	{
		throw "Incorrect length";
	}
	pMem[GetMemIndex(n) - 1] &= ~(GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen)
	{
		throw "Incorrect length";
	}
	if (pMem[GetMemIndex(n) - 1] & GetMemMask(n))
	{
		return 1;
	}
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (bf.GetBit(i) != GetBit(i))
			{
				return 0;
			}
		}
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bf == *this)
	{
		return 0;
	}
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen < bf.BitLen)
	{
		TBitField temp(bf);
		for (int i = 0; i < MemLen; i++)
		{
			temp.pMem[i] |= pMem[i];
		}
		return temp;
	}
	TBitField temp(*this);
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] |= bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField temp(*this);
	if (BitLen < bf.BitLen)
	{
		TBitField temp = bf;
		for (int i = 0; i < MemLen; i++)
		{
			temp.pMem[i] &= pMem[i];
		}
		return temp;
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		temp.pMem[i] &= bf.pMem[i];
	}
	return temp;
}


TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp = *this;
	for (int i = 0; i < temp.BitLen; i++)
	{
		if (temp.GetBit(i))
		{
			temp.ClrBit(i);
		}
		else
		{
			temp.SetBit(i);
		}
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string temp;
	istr >> temp;
	reverse(temp.begin(), temp.end());
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (temp[i] == '0')
		{
			bf.ClrBit(i);
		}
		else
		{
			bf.SetBit(i);
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << 1;
		}
		else
		{
			ostr << 0;
		}
	}
	return ostr;
}
