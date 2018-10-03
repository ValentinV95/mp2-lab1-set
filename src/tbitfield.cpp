// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <algorithm>
#include <string>

TBitField::TBitField(int len)
{
	if (len <= 0)
	{
		throw "Unexceptable constructor parameters";
	}
	else
	{
		BitLen = len;
		MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0;i < MemLen;i++)
		{
			pMem[i] = 0;
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0;i < MemLen;i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	
	if (n < 0 || n >= BitLen)
	{
		throw "Out of range";
	}
	else
	{
		return n / (8 * sizeof(TELEM));
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of range";
	}
	else
	{
		return 1 << (8 * sizeof(TELEM) - n % (8 * sizeof(TELEM)));
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of range";
	}
	else
	{
		pMem[GetMemIndex(n)]|= GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of range";
	}
	else
	{
		pMem[GetMemIndex(n)]&= (~GetMemMask(n));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of range";
	}
	else
	{
		if (GetMemMask(n) == (pMem[GetMemIndex(n)] & GetMemMask(n)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if ((*this) != bf)
	{
		if (bf.BitLen != BitLen)
		{
			delete[] pMem;
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
		}
		for (int i = 0;i < MemLen;i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{	
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	else
	{
		for (int i = 0;i < MemLen;i++)
		{
			if (pMem[i] != bf.pMem[i])
			{
				return 0;
			}
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((*this) == bf)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField a(max(BitLen, bf.BitLen)); // a = {0}
	//максимум из полей по BitLen кладем в а
	if (BitLen > bf.BitLen) 
	{
		for (int i = 0;i < MemLen;i++)
		{
			a.pMem[i] = pMem[i];
		}
	}
	else
	{
		for (int i = 0;i < bf.MemLen;i++)
		{
			a.pMem[i] = bf.pMem[i];
		}
	}
	for (int i = 0;i < min(MemLen, bf.MemLen);i++)
	{
		a.pMem[i] = pMem[i] | bf.pMem[i];
	}
	return a;	
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField a(max(BitLen, bf.BitLen));  // a = {0}
	//минимум из полей по BitLen кладем в а
	if (BitLen > bf.BitLen)
	{
		for (int i = 0;i < bf.MemLen;i++)
		{
			a.pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		for (int i = 0;i < MemLen;i++)
		{
			a.pMem[i] = pMem[i];
		}
	}
	for (int i = 0;i < min(MemLen, bf.MemLen);i++)
	{
		a.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return a;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField a(this->BitLen);
	int k;
	for (int i = 0;i < MemLen - 1;i++)
	{
		a.pMem[i] = ~(this->pMem[i]);
	}
	k = this->BitLen % (8 * sizeof(TELEM));
	for (int i = 0;i < k;i++)
	{
		if (GetBit(8 * sizeof(TELEM)*(MemLen - 1) + i) == 1)
		{
			a.ClrBit(8 * sizeof(TELEM)*(MemLen - 1) + i);
		}
		else
		{
			a.SetBit(8 * sizeof(TELEM)*(MemLen - 1) + i);
		}
	}
	return a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string a;
	istr >> a;
	for (int i = 0;(i < bf.BitLen)&&(i<a.size());i++)
	{
		if (a[i] == '1')
		{
			bf.SetBit(i);
		}
		else
		{
			if (a[i] == '0')
			{
				bf.ClrBit(i);
			} 
			else
			{
				throw "Non '0' or '1' type of element in bitfield";
			}
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0;i < bf.BitLen;i++)
	{
		ostr << bf.GetBit(i);
	}
	cout << endl;
	return ostr;
}
