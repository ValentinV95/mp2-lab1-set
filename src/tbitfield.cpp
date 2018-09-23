// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw("Error");
	MemLen = (len - 1) / (8 * sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
	BitLen = len;
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
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n > BitLen) throw("Error");
	return n / (8 * sizeof(TELEM)) + 1;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n > BitLen) throw("Error");
	return 1 << ((n) % (8 * sizeof(TELEM)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n > BitLen) throw("Error");
	pMem[GetMemIndex(n) - 1] = pMem[GetMemIndex(n) - 1] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0 || n > BitLen) throw("Error");
	pMem[GetMemIndex(n) - 1] = pMem[GetMemIndex(n) - 1] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0 || n > BitLen) throw("Error");
	return (pMem[GetMemIndex(n) - 1] & GetMemMask(n)) ? 1 : 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf)
	{
		delete[]pMem;
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
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
	bool flag = true;
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
		{
			flag = false;
			break;
		}
	}
	return (flag) ? 1 : 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	bool flag = true;
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) != bf.GetBit(i))
		{
			flag = false;
			break;
		}
	}
	return (flag) ? 0 : 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen < bf.BitLen)
	{
		TBitField p(bf);
		for (int i = 0; i < BitLen; i++)
		{
			if ((p.GetBit(i) | GetBit(i)) == 1)
			{
				p.SetBit(i);
			}
			else
			{
				p.ClrBit(i);
			}
		}
		return p;
	}
	else
	{
		TBitField p(*this);
		for (int i = 0; i < bf.BitLen; i++)
		{
			if ((p.GetBit(i) | bf.GetBit(i)) == 1)
			{
				p.SetBit(i);
			}
			else
			{
				p.ClrBit(i);
			}
		}
		return p;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen < bf.BitLen)
	{
		TBitField p(bf);
		for (int i = 0; i < BitLen; i++)
		{
			if ((p.GetBit(i) & GetBit(i)) == 1)
			{
				p.SetBit(i);
			}
			else
			{
				p.ClrBit(i);
			}
		}
		for (int i = BitLen; i < bf.BitLen; i++)
		{
			p.ClrBit(i);
		}
		return p;
	}
	else
	{
		TBitField p(*this);
		for (int i = 0; i < bf.BitLen; i++)
		{
			if ((p.GetBit(i) & bf.GetBit(i)) == 1)
			{
				p.SetBit(i);
			}
			else
			{
				p.ClrBit(i);
			}
		}
		for (int i = bf.BitLen; i < BitLen; i++)
		{
			p.ClrBit(i);
		}
		return p;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField p(*this);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)
		{
			p.SetBit(i);
		}
		else
		{
			p.ClrBit(i);
		}
	}
	return p;
}

// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		TELEM x;
		cin >> x;
		if (x == 1) bf.SetBit(i);
		else bf.ClrBit(i);
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