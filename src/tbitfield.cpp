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
		throw ("false len");
	else {
		BitLen = len;
		MemLen =(BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM [MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[bf.MemLen];
	for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >=BitLen))
		throw("false n in case 1");
	else {
		int temp = n / (8 * sizeof(TELEM));
		return temp;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >=BitLen))
		throw("false n in case 2");
	else {
		TELEM Maska = 0;
		TELEM OffSet = n % (8 * sizeof(TELEM));
		Maska = 1 << OffSet;
		return Maska;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n >=BitLen) || (n < 0))
		throw ("false n in case 3");
	else {
		TELEM Maska;
		Maska = GetMemMask(n);		int Index = GetMemIndex(n);		pMem[Index] = pMem[Index] | Maska;	}}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n >= BitLen) || (n < 0))
		throw ("false n in case 4");
	else {
		TELEM Maska;
		Maska = ~GetMemMask(n);
		int Index = GetMemIndex(n);
		pMem[Index] = pMem[Index] & Maska;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
		throw("false n in case 5");
	else {
		int Number = GetMemIndex(n);
		if (pMem[Number] & GetMemMask(n))
			return 1;
		else return 0;
	}
}
// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf != *this) {
		delete[] pMem;
		BitLen = bf.BitLen;		
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
		return *this;
	}
	else return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int k=1;
	if ((bf.pMem == 0) || (BitLen != bf.BitLen))
		return 0;
	else
		for (int i = 0; (i < MemLen) && (k == 1); i++)
			if (pMem[i] != bf.pMem[i])
				k = 0;
	return k;
 }

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (*this == bf)
		return 0;
	else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int Len=(BitLen < bf.BitLen)?bf.BitLen:BitLen;
	TBitField OR(Len);
	for (int i = 0; i < MemLen; i++)
		OR.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		OR.pMem[i] = OR.pMem[i] | bf.pMem[i];
	return OR;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{

	int flag = 1;//1_BitLen>bf.BitLen  0_BitLen<bf.BitLen
	int Len, MaxLen;
	if (BitLen < bf.BitLen) {
		Len = BitLen; MaxLen = bf.BitLen;
		flag = 0;
	}
	else {
		Len = bf.BitLen; MaxLen = BitLen;
	}
	TBitField AND(MaxLen);
	for (int i = 0; i < Len; i++)
		if (GetBit(i) & bf.GetBit(i))
			AND.SetBit(i);
	return AND;
}


TBitField TBitField::operator~(void) // отрицание
{
	TBitField Negation(BitLen);
	int N = BitLen - 1;
	int M = GetMemIndex(N);
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) != 0)
			Negation.ClrBit(i);
		else 
			Negation.SetBit(i);
	return Negation;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
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
		ostr << bf.GetBit(i) << ' ';
	return ostr;
}
