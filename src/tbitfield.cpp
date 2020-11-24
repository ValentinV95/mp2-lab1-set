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
		MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw("ERORRE");
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return(n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return(1 << (n % (sizeof(TELEM) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return (BitLen);
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int a;
		TELEM Mask;
		a = GetMemIndex(n);
		Mask = GetMemMask(n);
		pMem[a] = pMem[a] | Mask;
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen))
	{
		int a;
		TELEM Mask;
		a = GetMemMask(n);
		Mask = ~GetMemMask(n);
		pMem[a] = pMem[a] & Mask;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{ 
	if ((n < 0)||(n>BitLen))
	{
		int k;
		k = pMem[GetMemIndex(n)] & GetMemMask(n);
		if (k > 0)
			return(1);
		return 0;
    }
  
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete pMem;
		pMem = new TELEM[MemLen];
		for (size_t i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		for (size_t i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return*this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int f = 1;
	int i = 0;
	if (BitLen == bf.BitLen)
		while (i < BitLen)
		{
			if (GetBit(i) != bf.GetBit(i))
				f = 0;
			i++;
		}
	else return(0);
  return (f);
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this==bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(*this);
		for (size_t i = 0; i < bf.MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] | bf.pMem[i];
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (size_t i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] | pMem[i];
		}
		return tmp;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(BitLen);
		for (size_t i = 0; i < bf.BitLen; i++)
		{
			if ((GetBit(i) == 1) && (bf.GetBit(i) == 1))
			{
				std::cout << GetBit(i) << "  " << bf.GetBit(i) << endl;
				tmp.SetBit(i);
			}
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf);
		for (size_t i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] & pMem[i];
		}
		return tmp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tmp(*this);
	for (int i = 0; i < MemLen; i++)
		tmp.pMem[i] = ~pMem[i];
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int l;
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> l;
		cout << endl;
		if ((l % 10) == l)
			if (l)
				bf.SetBit(i);
			else
				bf.ClrBit(i);
	}
	return (istr);
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
	return ostr;
}
