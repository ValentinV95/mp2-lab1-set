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
	if (BitLen <= 0)
		throw(1);
		MemLen = ((BitLen - 1) / 8 * sizeof(unsigned)) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	if (BitLen != bf.BitLen)
	{
		delete[]pMem;
		pMem = new TELEM[MemLen];	
	}
	for (int i = 0; i < bf.BitLen; i++)
		pMem[i] = bf.pMem[i];
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
}

TBitField::~TBitField()
{
	delete[]pMem;
	BitLen = 0;
	MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n>(BitLen-1)))
		throw (7);
	int Ind = n/(sizeof(TELEM) * 8);

	return Ind;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM Mask=0;
	Mask = 1 << n;
	return Mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	TBitField Fuller(BitLen);
	int BlockNum = GetMemIndex(n);
	TELEM Mask = GetMemMask(n);
	TELEM NewBit = NewBit | Mask;
	pMem[BlockNum] = NewBit;
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	TBitField Fuller(BitLen);
	int BlockNum = GetMemIndex(n);
	TELEM Mask = GetMemMask(n);
	Mask = ~Mask;
	TELEM NewBit = NewBit & Mask;
	pMem[BlockNum] = NewBit;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n <= 0)
		throw 12;
  return pMem[n];
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		delete[]pMem;
		pMem = new TELEM[MemLen];
	}
	for (int i = 0; i < bf.BitLen; i++)
		pMem[i] = bf.pMem[i];

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 0;
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < BitLen; i++)
		{
			if (pMem[i] == bf.pMem[i])
				res++;
		}

		if (res == BitLen)
			return 1;
		else return 0;
	}
  else return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int flag = (pMem == bf.pMem);
	if (flag == 0)
		return 1;
	else return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField C(bf.BitLen);
	for (int i = 0; i < bf.BitLen; i++)
		C.pMem[i] = pMem[i]|bf.pMem[i];
	return C;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField C(bf.BitLen);
	for (int i = 0; i < bf.BitLen; i++)
		C.pMem[i] = pMem[i] & bf.pMem[i];
	return C;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField C(BitLen);
	for (int i = 0; i < BitLen; i++)
		C.pMem[i] = ~pMem[i];
	return C;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	for (int i = 0; i< bf.BitLen; i++)
		istr >> bf.pMem[i];
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i< bf.BitLen; i++)
		ostr << bf.pMem[i];
	return ostr;
}
