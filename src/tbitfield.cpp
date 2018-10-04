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
		throw "Индекс бита не положительный или превышает размер битового поля";
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
	if ((n >= 0) && (n <= BitLen))
	{
		int num = (int)(n / (sizeof(TELEM) * 8)); 	
		pMem[num] = pMem[num] | GetMemMask(n); 
	}
	else
		throw "Индекс бита не положительный или превышает размер битового поля";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = (int)(n / (sizeof(TELEM) * 8)); 

		pMem[num] = pMem[num] & ~GetMemMask(n); 
	}
	else
		throw "Индекс бита не положительный или превышает размер битового поля";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = (int)(n / (sizeof(TELEM) * 8)); 	
		if ((pMem[num] & GetMemMask(n)) == GetMemMask(n))
			return 1;
		else
			return 0;
	}
	else
		throw "Индекс бита не положительный или превышает размер битового поля";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this->BitLen == bf.BitLen)
	{
		for (int i = 0; i <= bf.MemLen; i++)
			this->pMem[i] = bf.pMem[i];
	}
	else
	{
		delete[] this->pMem;
		this->BitLen = bf.BitLen;
		this->MemLen = (int)(bf.BitLen / (sizeof(TELEM) * 8));
		if ((bf.BitLen % (sizeof(TELEM) * 8)) > 0)
			this->MemLen++;
		this->pMem = new TELEM[this->MemLen];
		for (int i = 0; i <= bf.MemLen; i++)
			this->pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const// сравнение
{
	int count = 0;
	if (this->MemLen == bf.MemLen)
	{
		for (int i = 0; i < bf.MemLen; i++)
			if (this->pMem[i] == bf.pMem[i])
				count++;
		if (count == bf.MemLen)
			return 1;
		else
			return 0;
	}
	else
		return 0;
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
	TBitField t(bf.BitLen);
	for (int i = 0; i < this->MemLen; i++)
		t.pMem[i] = this->pMem[i] | bf.pMem[i];
	return t;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField t(bf.BitLen);
	for (int i = 0; i < this->MemLen; i++)
		t.pMem[i] = this->pMem[i] & bf.pMem[i];
	return t;
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int i = 0; i < this->BitLen; i++)
		this->pMem[(int)(i / (sizeof(TELEM) * 8))] = pMem[(int)(i / (sizeof(TELEM) * 8))] ^ GetMemMask(i);
	return *this;
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
		if (bf.GetBit(i) == bf.GetMemMask(i))
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
