// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	for (int i = 0;i < MemLen;i++)
	{
		pMem[i] = 0;
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
	
		if (n <= 0 || n > BitLen)
		{
			throw "f";
		}
		else
		{
			return n / (8 * sizeof(TELEM));
		}
	

}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	try
	{
		if (n <= 0 || n > BitLen)
		{
			throw 123;
		}
		else
		{
			return 1 << (8 * sizeof(TELEM) - n % (8 * sizeof(TELEM)));
		}
	}
	catch (int i)
	{

	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	try
	{
		if (n <= 0 || n > BitLen)
		{
			throw 123;
		}
		else
		{
			pMem[GetMemIndex(n)]|= GetMemMask(n);
		}
	}
	catch (int i)
	{

	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	try
	{
		if (n <= 0 || n > BitLen)
		{
			throw 123;
		}
		else
		{
			pMem[GetMemIndex(n)]&= (~GetMemMask(n));
		}
	}
	catch (int i)
	{

	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	try
	{
		if (n <= 0 || n > BitLen)
		{
			throw 123;
		}
		else
		{
			if ((1 << (8 * sizeof(TELEM) - n % (8 * sizeof(TELEM)))) == (pMem[GetMemIndex(n)] & GetMemMask(n)))
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
	catch (int i)
	{

	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	try
	{
		if (BitLen != bf.BitLen)
		{
			throw 22;
		}
		else
		{
			for (int i = 0;i < MemLen;i++)
			{
				pMem[i] = bf.pMem[i];
			}
		}
		return *this;
	}
	catch (int i)
	{

	}
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	
		if (BitLen != bf.BitLen)
		{
			throw 22;
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
	try
	{
		if (BitLen != bf.BitLen)
		{
			throw 22;
		}
		else
		{
			TBitField *a = new TBitField(bf.BitLen);
			for (int i = 0;i < MemLen;i++)
			{
				a->pMem[i] = pMem[i] | bf.pMem[i];
			}
			return *a;
		}
	}
	catch (int i)
	{

	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	try
	{
		if (BitLen != bf.BitLen)
		{
			throw 22;
		}
		else
		{
			TBitField *a = new TBitField(bf.BitLen);
			for (int i = 0;i < MemLen;i++)
			{
				a->pMem[i] = pMem[i] & bf.pMem[i];
			}
			return *a;
		}
	}
	catch (int i)
	{

	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField *a = new TBitField(this->BitLen);
	for (int i = 0;i < MemLen - 1;i++)
	{
		a->pMem[i] = ~(this->pMem[i]);
	}
	for (int i = 0;i < (this->BitLen % (8 * sizeof(TELEM)));i++)
	{
		if (GetBit(8 * sizeof(TELEM)*(MemLen - 1) + i) == 1)
		{
			ClrBit(8 * sizeof(TELEM)*(MemLen - 1) + i);
		}
		else
		{
			SetBit(8 * sizeof(TELEM)*(MemLen - 1) + i);
		}
	}
	return *a;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int k;
	for (int i = 0;i < bf.BitLen;i++)
	{
		istr >> k;
		if (k == 1)
		{
			bf.SetBit(i);
		}
		else
		{
			bf.ClrBit(i);
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
