// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле


#include "tbitfield.h"
#include "iostream"
#include "string"
#include "math.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (BitLen / (sizeof(TELEM) * 8)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
		throw "Invalid length";
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int k = 0; k < MemLen; k++)
		pMem[k] = bf.pMem[k];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return  (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM mask = 1;
	int pos = n % (sizeof(TELEM) * 8);
	mask = mask << pos;
	return mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= 0 && n < BitLen)
	{
		int index = GetMemIndex(n);
		int pos = n % (sizeof(TELEM) * 8);
		pMem[index] = pMem[index] | GetMemMask(pos);
	}
	else
		throw "incorrect value";
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= 0 && n < BitLen)
	{
		
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
	}
	else
		throw "Invalid index";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= 0 && n <= BitLen) {
		TELEM mask = GetMemMask(n);
		if ((pMem[GetMemIndex(n)] & mask) == mask)
			return 1;
		else
			return 0;
	}
	else
		throw "invalid index";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete[] this->pMem;
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	for (int k = 0; k < bf.MemLen; k++)
		this->pMem[k] = bf.pMem[k];
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i])
				return 0;
		}
	}
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 1;
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i])
				return 1;
		}
	}
	return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(BitLen);
		TBitField bftmp(BitLen);
		for (int i = 0; i < bf.MemLen; i++) {
			bftmp.pMem[i] = bftmp.pMem[i] | bf.pMem[i];
		}
		for (int i = 0; i < bf.MemLen; i++) {
			tmp.pMem[i] = pMem[i] | bftmp.pMem[i];
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf.BitLen);
		TBitField thistmp(bf.BitLen);
		for (int i = 0; i < MemLen; i++) {
			thistmp.pMem[i] = thistmp.pMem[i] | pMem[i];
		}
		for (int i = 0; i < MemLen; i++) {
			tmp.pMem[i] = thistmp.pMem[i] | bf.pMem[i];
		}
		return tmp;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(BitLen);
		for (int i = 0; i < bf.MemLen; i++) {
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return tmp;
	}
	else
	{
		TBitField tmp(bf.BitLen);
		for (int i = 0; i < MemLen; i++) {
			tmp.pMem[i] = pMem[i] & bf.pMem[i];
		}
		return tmp;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	TELEM tmp = 0;
	TBitField tmpbit(*this);
	int index = BitLen % (sizeof(TELEM) * 8);
	for (int i = 0; i < index; i++) {
		tmp += pow(2, i);
	}
	for (int i = 0; i < MemLen; i++) {
		if (i == MemLen - 1)
			tmpbit.pMem[i] = ~pMem[i] & tmp;
		else
			tmpbit.pMem[i] = ~pMem[i];
	}
	return tmpbit;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод

{
	string str;
	istr >> str;
	for (int i = 0; (i < bf.BitLen) && (i < str.length()); i++)

	{
		if ((str[i] != '0') && (str[i] != '1'))
		{
			throw("Unacceptable_input");
		}
	}

	for (int i = 0; (i < bf.BitLen) && (i < str.length()); i++)
	{
		str[i] == '0' ? bf.ClrBit(i) : bf.SetBit(i);
	}
	for (int i = str.length(); i < bf.BitLen; i++)

	{
		bf.ClrBit(i);
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