// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)//конструктор для инициализации
{
	if (len < 0)
		throw ("Wrong length");
	else {
		BitLen = len;
		MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	BitLen = bf.BitLen;
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()//деструктор
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= BitLen || n < 0)
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
	else {
		int index = n / (sizeof(TELEM) * 8);
		return index;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n >= BitLen || n<0) 
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
	else
	{
		int bias = n % (sizeof(TELEM) * 8);
		TELEM mask = 0;
		mask = 1 << bias;
		return mask;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ( n >= BitLen || n < 0)
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
	else
		pMem[(*this).GetMemIndex(n)] =(pMem[(*this).GetMemIndex(n)] | (*this).GetMemMask(n));
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen ||n < 0)
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
	if ((n > -1) && (n < BitLen))
		pMem[(*this).GetMemIndex(n)] = (pMem[(*this).GetMemIndex(n)] & ~ (*this).GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int val = 0;
	if (n >= BitLen || n < 0)
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
	else {
		int numblock = (*this).GetMemIndex(n);
		if ((pMem[numblock] & (*this).GetMemMask(n)))
			val = 1;
		return val;
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

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
	if (BitLen != bf.BitLen || bf.pMem == 0)
		res = 0;
	else
		for (int i = 0; (i < MemLen) && (res == 1); i++)
			if (pMem[i] != bf.pMem[i])
				res = 0;
	return res;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int rez = 0;
	if (BitLen != bf.BitLen)
		rez = 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i]) {
				rez = 1;
				break;
			}
  return rez;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int temp;
	if (BitLen > bf.BitLen)
		temp = BitLen;
	else
		temp = bf.BitLen;
	TBitField rez(temp);
	for (int i = 0; i < MemLen; i++)
		rez.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		rez.pMem[i] |= bf.pMem[i];
	return rez;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int temp;
	if (BitLen > bf.BitLen)
		temp = BitLen;
	else
		temp = bf.BitLen;
	TBitField rez(temp);
	for (int i = 0; i < rez.MemLen; i++)
		rez.pMem[i] = pMem[i];
	for (int i = 0; i < rez.MemLen; i++)
		rez.pMem[i] &= bf.pMem[i];
	return rez;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField rez(BitLen);
	int n = BitLen - 1;
	int m = GetMemIndex(n);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) != 0)
			rez.ClrBit(i);
		else
			rez.SetBit(i);
	return rez;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	char m;
	int i;
	do istr >> m;
	while (m != ' ');
	while (1) {
		istr >> m;
		if (m == '1')
			bf.SetBit(i++);
		else 
			if (m == '0')
			bf.ClrBit(i++);
			else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i) << ' ';
	return ostr;
}
