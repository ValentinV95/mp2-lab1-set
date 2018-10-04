// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <iostream>
#include <string>

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (int)(len / (sizeof(TELEM) * 8));
		if ((len % (sizeof(TELEM) * 8)) > 0)
			MemLen++;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
		throw "Wrong data";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	pMem = new TELEM[bf.MemLen];
	MemLen = bf.MemLen;
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
	BitLen = bf.BitLen;
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int index = (int)(n / (sizeof(TELEM) * 8));
	return index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM maska = 1;
	int position = (n % (sizeof(TELEM) * 8));		
	maska = maska << position;
	return maska;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит 
{
	if ((n < 0) || (n >= BitLen)) {
		throw 3;
	}
	else {
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит 
{
	if ((n < 0) || (n >= BitLen)) {
		throw 4;
	}
	else {
		int number = (*this).GetMemIndex(n);
		pMem[number] = (pMem[number] & ~(*this).GetMemMask(n));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита 
{
	int tmp = 0;
	if ((n > BitLen - 1) || (n < 0))
		throw ("Индекс бита неположителен или превышает размер битового поля");
	else {
		int numblock = (*this).GetMemIndex(n);
		if ((pMem[numblock] & (*this).GetMemMask(n)))
			tmp = 1;
		return tmp;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание 
{
	if (*this != bf) {
		delete[]pMem;
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const// сравнение
{
	int count = 1;
	if ((BitLen != bf.BitLen) || (bf.pMem == 0))
		count = 0;
	else
		for (int i = 0; (i < MemLen) && (count == 1); i++)
			if (pMem[i] != bf.pMem[i])
				count = 0;
	return count;	
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int count = 0;
	if (this->MemLen != bf.MemLen)
		return 1;
	else
	{
		for (int i = 0; i < bf.MemLen; i++)
			if (this->pMem[i] == bf.pMem[i])
				count++;
		if (count != bf.MemLen)
			return 1;
		else
			return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int mp;
	if (BitLen > bf.BitLen)
		mp = BitLen;
	else
		mp = bf.BitLen;
	TBitField s(mp);
	for (int i = 0; i < MemLen; i++)
		s.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		s.pMem[i] |= bf.pMem[i];
	return s;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и" 
{
	int mp, bitlen;
	if (bf.BitLen > BitLen) {
		mp = MemLen;
		bitlen = bf.BitLen;
	}
	else {
		mp = bf.MemLen;
		bitlen = BitLen;
	}
	TBitField c(bitlen);
	for (int i = 0; i < mp; i++)
		c.pMem[i] = pMem[i] & bf.pMem[i];
	return c;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField s(BitLen);
	int n = BitLen - 1;
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) != 0)
			s.ClrBit(i);
		else
			s.SetBit(i);
	return s;
}


// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	int k;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> k;
		while ((k != 1) && (k != 0))
			istr >> k;
		if (k == 1)
			bf.SetBit(i);
		else
			bf.ClrBit(i);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if ((bf.pMem[(int)(i / (sizeof(TELEM) * 8))] & bf.GetMemMask(i)) == bf.GetMemMask(i))
			{
				ostr << "1";
			}
		else
			{
				ostr << "0";
			}
	}
	return ostr;
}
