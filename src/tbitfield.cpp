// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (BitLen - 1) / sizeof(TELEM) + 1;
		pMem = new TELEM [MemLen];
		for (unsigned int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
	{
		throw "len < 0";
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = (BitLen - 1) / sizeof(TELEM) + 1;
	pMem = new TELEM [MemLen];
	for (unsigned int i = 0; i < MemLen; i++)
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
	return n / sizeof(TELEM);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % sizeof(TELEM));
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
		throw "Bit < 0 or >= BitLen";
	}
	else
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "Bit < 0 or >= BitLen";
	}
	else
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n >= BitLen)
	{
		throw "Bit < 0 or >= BitLen";
	}
	else
	{
		if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM [MemLen];
	for (unsigned int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
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
		for (unsigned int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				return 0;
			}
		}
		return 1;
	}
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
	{
		return 1;
	}
	else
	{
		for (unsigned int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
			{
				return 1;
			}
		}
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen < bf.BitLen)
	{
		TBitField temp(bf.BitLen);
		for (unsigned int i = 0; i < BitLen ; i++)
		{
			if (GetBit(i) == 1)
			{
				temp.SetBit(i);
			}
			
		}
		for (unsigned int i = 0; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i) == 1)
			{
				temp.SetBit(i);
			}
		}
		return temp;
	}
	if (BitLen >= bf.BitLen)
	{
		TBitField temp(BitLen);
		for (unsigned int i = 0; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i) == 1)
			{
				temp.SetBit(i);
			}

		}
		for (unsigned int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) == 1)
			{
				temp.SetBit(i);
			}
		}
		return temp;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen < bf.BitLen)
	{
		TBitField temp(bf.BitLen);
		for (unsigned int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) == 1 && bf.GetBit(i) == 1)
			{
				temp.SetBit(i);
			}
		}
		return temp;
	}
	if (BitLen >= bf.BitLen)
	{
		TBitField temp(BitLen);
		for (unsigned int i = 0; i < bf.BitLen; i++)
		{
			if (bf.GetBit(i) == 1 && GetBit(i) == 1)
			{
				temp.SetBit(i);
			}
		}
		return temp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField temp(BitLen);
	for (unsigned int i = 0; i < MemLen - 1; i++)
	{
		temp.pMem[i] = ~pMem[i];
	}
	for (unsigned int i = (MemLen - 1) * sizeof(TELEM); i < BitLen; i++)
	{
	    if (GetBit(i) == 1)
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
	int k;
	for (unsigned int i = 0; i < bf.MemLen; i++)
	{
		istr >> k;
		if (k == 0)
		{
			bf.ClrBit(i);
		}
		else if (k == 1)
		{
			bf.SetBit(i);
		}
		else
		{
			throw "Input != 0, != 1";
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (unsigned int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i) << " ";
	}
	ostr << endl;
	return ostr;
}
