// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) { 
		throw 1; 
	} else { 
		MemLen = (len + 31) >> 5;   
		BitLen = len;   
		pMem = new TELEM[MemLen];  
		if (pMem != NULL) {
			for (int i = 0; i < MemLen; i++) {
				pMem[i] = 0;
			}
		}
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (MemLen != NULL) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n >> 5);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen)) {
		throw 2;
	} else {
		return (1 << (n & 31));
	}
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
	if ((n < 0) || (n >= BitLen)) {
		throw 5;
	}
	else {
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen) {
		BitLen = bf.BitLen;
	}
	if (MemLen != bf.MemLen) {
		MemLen = bf.MemLen;
	}
	delete[] pMem;
	pMem = new TELEM[MemLen];
	if (bf.pMem != 0) {
		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}
	return (*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int result = 1;
	if (BitLen != bf.BitLen) {
		result = 0;
	} else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				result = 0;
				break;
			}
		}
	}
  return result;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int result = 0;
	if (BitLen != bf.BitLen) {
		result = 1;
	}
	else {
		for (int i = 0; i < MemLen; i++) {
			if (pMem[i] != bf.pMem[i]) {
				result = 1;
				break;
			}
		}
	}
	return result;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int k = 1;
	int len;
	int mimLen;
	if (BitLen < bf.BitLen) {
		k = 0;
	} 
	if (k == 1) {
		len = BitLen;
		mimLen = bf.MemLen;
	} else {
		len = bf.BitLen;
		mimLen = MemLen;
	}
	TBitField result(len);
	for (int i = 0; i < mimLen; i++) {
			result.pMem[i] = pMem[i] | bf.pMem[i];
	}
	if (k==1) {
		for (int i = mimLen; i < result.MemLen; i++) 
			result.pMem[i] = pMem[i];
	} else {
		for (int i = mimLen; i < result.MemLen; i++)
			result.pMem[i] = bf.pMem[i];
	}
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int k = 1;
	int len;
	int mimLen;
	if (BitLen < bf.BitLen) {
		k = 0;
	}
	if (k == 1) {
		len = BitLen;
		mimLen = bf.MemLen;
	}
	else {
		len = bf.BitLen;
		mimLen = MemLen;
	}
	TBitField result(len);
	for (int i = 0; i < mimLen; i++) {
		result.pMem[i] = pMem[i] & bf.pMem[i];
	}
	if (k == 1) {
		for (int i = mimLen; i < result.MemLen; i++)
			result.pMem[i] = pMem[i];
	}
	else {
		for (int i = mimLen; i < result.MemLen; i++)
			result.pMem[i] = bf.pMem[i];
	}
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	for (int i = 0; i < (MemLen - 1); i++) {
		result.pMem[i] = ~pMem[i];
	}
	for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++) {
		if (GetBit(i) == 0) {
			result.SetBit(i);
		}
	}
	return result;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int k;
	istr >> k;
	if (k = 0) {
		bf.SetBit(k);
	} 
	if (k = 1) {
		bf.ClrBit(k);
	}
	if ((k != 0) && (k != 1)) {
		throw 6;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++) {
		ostr << bf.GetBit(i) << ' ' ;
	}
	return ostr;
}

