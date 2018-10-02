// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include "string"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw "Error: negative_length";


	BitLen = len;
	MemLen = (BitLen - 1) / (sizeof(TELEM) * 8) + 1;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
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
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0)
		throw "Error: negative_length";

	if (n >(*this).BitLen - 1)
		throw "Error: too_large_index";

	
	return (n / (sizeof(TELEM) * 8));
}


TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0)
		throw "Error: negative_length";

	if (n >(*this).BitLen - 1)
		throw "Error: too_large_index";

	
	int bias = n % (sizeof(TELEM) * 8);

	TELEM mask = 1 << bias;
	return (mask);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return (BitLen);
}


void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0)
		throw "Error: negative_length";

	if (n > (*this).BitLen-1)
		throw "Error: too_large_index";


	int mask = GetMemMask(n);
	pMem[GetMemIndex(n)] |= mask;
}


void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0)
		throw "Error: negative_length";

	if (n >(*this).BitLen - 1)
		throw "Error: too_large_index";


	int mask = ~GetMemMask(n);
	pMem[GetMemIndex(n)] &= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) 
		throw "Error: negative_length";

	if (n >(*this).BitLen - 1) 
		throw "Error: too_large_index";


	int mask = GetMemMask(n);

	if (pMem[GetMemIndex(n)] & mask)
		return(1);
	else
		return(0);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		delete[]pMem;
		pMem = new TELEM[MemLen];
	}

	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];

	return(*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i])
				return(0);
		return(1);
	}
	else
		return(0);
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return(0);
	else
		return(1);
}


TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	const TBitField *small_bf, *big_bf;

	if (BitLen > bf.BitLen)
	{
		small_bf = &bf;
		big_bf = this;
	}
	else
	{
		small_bf = this;
		big_bf = &bf;
	}
	
	TBitField res(*big_bf);

	for (int i = 0; i < small_bf->MemLen; i++)
		res.pMem[i] = small_bf->pMem[i] | big_bf->pMem[i];	

	return (res);
}


TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	const TBitField *small_bf, *big_bf;

	if (BitLen > bf.BitLen)
	{
		small_bf = &bf;
		big_bf = this;
	}
	else
	{
		small_bf = this;
		big_bf = &bf;
	}

	TBitField res(big_bf->BitLen);

	for (int i = 0; i < small_bf->MemLen; i++)
		res.pMem[i] = small_bf->pMem[i] & big_bf->pMem[i];

	return(res);
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);

	for (int i = 0; i < MemLen - 1; i++)
		res.pMem[i] = ~pMem[i];

	int num_of_low_bit = (MemLen - 1) * sizeof(TELEM);

	for (int i = num_of_low_bit; i < BitLen; i++)
	{
		if ( GetBit(i) )
			res.ClrBit(i);
		else
			res.SetBit(i);
	}

	return(res);
}


// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string sbf;
	istr >> sbf;
	
	if (sbf.length() != bf.BitLen)
		throw "Error: incorrect_length";


	for (int i = 0; i < sbf.length(); i++)
	{
		switch (sbf[i])
		{
		case '1': bf.SetBit(i);
			break;
		case '0': bf.ClrBit(i);
			break;
		default: throw "Error: incorrect_input";
			break;
		}
	}

	return(istr);
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);

	return(ostr);
}

