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
		MemLen = (BitLen -1)/(8*sizeof(TELEM))  + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i]=0;
	}
	else
		throw "";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < BitLen; i++)
		if (bf.GetBit(i))
			SetBit(i);
		else
			ClrBit(i);
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
	return(1<<(n % (sizeof(TELEM) * 8)));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return (BitLen);
  //return 0;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >= 0) && (n <= BitLen))
	{
		int a;
		TELEM Mask;
		a = GetMemIndex(n);
		Mask = GetMemMask(n);
		pMem[a] = pMem[a] | Mask;
	}
	else
		throw "";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n <= BitLen))
	{
		int a;
		TELEM Mask;
		a = GetMemIndex(n);
		Mask = ~GetMemMask(n);
		pMem[a] = pMem[a] & Mask;
	} 
	else
		throw "";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n <= BitLen))
	{
		int a;
		a = pMem[GetMemIndex(n)] & GetMemMask(n);
		if (a)
			return(1);
		return 0;
	}
	else
		throw "";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
		delete[] pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < BitLen; i++)
			if (bf.GetBit(i))
				SetBit(i);
			else
				ClrBit(i);
	return(*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int k = 1;
	int i = 0;
	if (BitLen == bf.BitLen)
		while (i < BitLen, k)
		{
			if (pMem[i] != bf.pMem[i])
				k = 0;
			i++;
		}
	else return(0);
		return(k);
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return!(*this==bf);
  //return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{ 
	int min, max, k;
	min = (BitLen < bf.BitLen) ? BitLen : bf.BitLen;
	max = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;
	TBitField a(max);
	for (int i = 0; i < min; i++)
		a.pMem[i] = pMem[i] | bf.pMem[i];
	k = (BitLen < bf.BitLen) ? 1 : 0;
	if (k)
		for (int i = min; i < max; i++)
			a.pMem[i] = bf.pMem[i];
	else
		for (int i = min; i < max; i++)
			a.pMem[i] = pMem[i];
	return(a);
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int min;
	min = (BitLen < bf.BitLen) ? BitLen : bf.BitLen;
	TBitField a(min);
	for (int i = 0; i < min; i++)
		a.pMem[i] = pMem[i] & bf.pMem[i];
	return(a);
}

TBitField TBitField::operator~(void) // отрицание
{
	
	for (int i = 0; i < BitLen; i++) 
	{
		if (GetBit(i))
			ClrBit(i);
		else
			SetBit(i);
	}
	return(*this);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int l;
	for (int i=0; i < bf.BitLen; i++) 
	{
		istr >> l;
		if (l)
			bf.SetBit(i);
		else
			bf.ClrBit(i);
	}

	return(istr);
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	return(ostr);
}
