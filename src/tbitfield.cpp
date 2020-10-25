// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Negative meaning";
	}
	else
	{
		BitLen = len;
		MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		memset(pMem, 0, MemLen);
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		this->pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n > -1) && (n < BitLen))
	{
		return (n / (sizeof(TELEM) * 8));

	}
	else
		throw "the bit does not exist";
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen))
	{
		throw "(n < 0) || (n >= BitLen)";
	}
	return 1 << (n & (sizeof(TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int index;
		index = GetMemIndex(n);
		pMem[index] |= (1 << (n % (sizeof(TELEM) * 8 - 1)));

	}
	else
		throw "the bit does not exist";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
	{
		int index;
		index = GetMemIndex(n);
		pMem[index] &= (~(1 << (n % (sizeof(TELEM) * 8 - 1))));

	}
	else
		throw "the bit does not exist";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if((n > -1) && (n < BitLen)
	  return pMem[GetMemIndex(n)] & GetMemMask(n);
  else
	  throw "the bit does not exist";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	else
		throw "lengths do not match";
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int k = 1;
		if (BitLen != bf.BitLen)
		{
			k = 0;
		}
		else
		{
			for (int i = 0; i < MemLen; i++)
			{
				if (pMem[i] != bf.pMem[i])
				{
					k = 0;
				}
			}
		}
	return k;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int k = 0;
		if (BitLen != bf.BitLen)
		{
			k = 1;
		}
		else
		{
			for (int i = 0; i < MemLen; i++)
			{
				if (pMem[i] != bf.pMem[i])
				{
					k = 1;
				}
			}
		}
		return k;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8); i++)
		{
			pMem[i] |= bf.pMem[i];
		}
	}
	else
		throw "lengths do not match";
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8); i++)
		{
			pMem[i] &= bf.pMem[i];
		}
	}
	else
		throw "lengths do not match";
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8); i++)
	{
		pMem[i] = ~pMem[i];
	}
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char x;
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> x;
		if (x == '0')
		{
			bf.ClrBit(i);
		}
		else if (x == '1')
		{
			bf.SetBit(i);
		}
		else
		{
			break;
		}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i))
			ostr << '1';
		else
			ostr << '0';
	}
	return ostr;
}
