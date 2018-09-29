// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if(len < 0)
	{
		throw("Negative lenght");
	}
	BitLen = len;
	MemLen = (BitLen - 1)/(8*sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	for(int i = 0; i < MemLen; i++)
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
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if(n >= BitLen)
	{
		throw("Too_large_bit_index ");
	}
	if(n < 0)
	{
		throw("Negative_index");
	}
	return (n)/(8*sizeof(TELEM));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if(n >= BitLen)
	{
		throw("Too_large_bit_index ");
	}
	if(n < 0)
	{
		throw("Negative_index");
	}
	return 1 << (n % (8*sizeof(TELEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if(n >= BitLen)
	{
		throw("Too_large_bit_index ");
	}
	if(n < 0)
	{
		throw("Negative_index");
	}
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if(n >= BitLen)
	{
		throw("Too_large_bit_index ");
	}
	if(n < 0)
	{
		throw("Negative_index");
	}
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n >= BitLen)
	{
		throw("Too_large_bit_index ");
	}
	if(n < 0)
	{
		throw("Negative_index");
	}
	return pMem[GetMemIndex(n)] & GetMemMask(n) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf.pMem != pMem)
	{
		delete[] pMem;
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
	if(BitLen != bf.BitLen)
	{
		return 0;
	}
	for (int i = 0; i < BitLen; i++)
	{
		if(GetBit(i) != bf.GetBit(i))
		{
			return 0;
		}
	}
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  return (!((*this) == bf));
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int t, k;
	BitLen < bf.BitLen ? t = bf.BitLen : t = BitLen;
	BitLen < bf.BitLen ? k = BitLen : k = bf.BitLen;
	TBitField tmp(t);

	for (int i = 0; i < t; i++)
	{
		if(i < k)
		{
			if (GetBit(i) | bf.GetBit(i))
			{
				tmp.SetBit(i);
			}
		}
		else
		{
			(BitLen < bf.BitLen) ? 
				(bf.GetBit(i) ? tmp.SetBit(i) : tmp.ClrBit(i))
										: (GetBit(i) ? tmp.SetBit(i) : tmp.ClrBit(i));
		}
	}
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int t, k;
	BitLen < bf.BitLen ? t = bf.BitLen : t = BitLen;
	BitLen < bf.BitLen ? k = BitLen : k = bf.BitLen;
	TBitField tmp(t);

	for (int i = 0; i < t; i++)
	{
		if(i < k)
		{
			if (GetBit(i) & bf.GetBit(i))
			{
				tmp.SetBit(i);
			}
		}
	}
	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp=(*this);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = ~tmp.pMem[i];
	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string x;
	istr >> x;
	for (int i = 0; i < bf.BitLen; i++)
	{	
		x[i] == '0' ? bf.ClrBit(i) : bf.SetBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{	
		ostr << bf.GetBit(i);
	}
	return ostr;
}
