// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <math.h>


TBitField::TBitField(int len)
{
	if (len <= 0)
		throw ("Количество элементов в множестве не является положительным числом");
	else {
		BitLen = len;
		MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
		pMem = new TELEM[MemLen];
	if (pMem !=NULL) 
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		if (bf.pMem == 0)
			throw ("Нулевой указатель (некорректный адрес массива pMem в памяти)");
		else{
			pMem = new TELEM[bf.MemLen];
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
}

TBitField::~TBitField()
{
	BitLen = 0;
	MemLen = 0;
	delete[]pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen - 1))
		throw ("Индекс бита неположителен или превышает размер битового поля");
	else {
		int Index = n/(sizeof(TELEM)*8);
		return Index;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > BitLen - 1) || (n < 0))
		throw ("Индекс бита неположителен или превышает размер битового поля");
	else
	{
		int bias= n % (sizeof(TELEM) * 8);
		TELEM mask=0;
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
	if ((n > BitLen - 1) || (n < 0))
		throw ("Индекс бита неположителен или превышает размер битового поля");
	else {
		int numblock = (*this).GetMemIndex(n);
		pMem[numblock] = (pMem[numblock] | (*this).GetMemMask(n));
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > BitLen - 1) || (n < 0))
		throw ("Индекс бита неположителен или превышает размер битового поля");
	else {
		int numblock = (*this).GetMemIndex(n);
		pMem[numblock] = (pMem[numblock] & ~(*this).GetMemMask(n));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int value = 0;
	if ((n > BitLen - 1) || (n < 0))
		throw ("Индекс бита неположителен или превышает размер битового поля");
	else {
		int numblock = (*this).GetMemIndex(n);
		if( (pMem[numblock] & (*this).GetMemMask(n)))
			value =1;
		return value;
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
		if (bf.pMem != NULL)
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		else throw ("Нулевой указатель (некорректный адрес массива pMem в памяти)");;
}
	return *this;

		
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;//равны
	if ((BitLen != bf.BitLen)||(bf.pMem == 0))
		res = 0;
	else
		for (int i = 0; (i < MemLen) && (res == 1); i++)
			if (pMem[i] != bf.pMem[i])
				res = 0;
	return res;

}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int result;//result=1 - не равны, result=0 - равны
	int res=((*this)==bf);
	if (res == 1)// равны
		result = 0;
	else result = 1;
	return result;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	int minMlen;//minMemlen
	int k=1;//флаг, к=1 -> BitLen > bf.BitLen, k=0 -> BitLen < bf.BitLen
	if (BitLen < bf.BitLen)
		k = 0;
	if (k == 1) {
		len = BitLen;
		minMlen = bf.MemLen;
	}
	else {
		len = bf.BitLen;
		minMlen = MemLen;
	}
	TBitField merger(len);
	for (int i = 0; i < minMlen; i++)
		merger.pMem[i] = pMem[i] | bf.pMem[i];
	if (k==1)
		for (int i = minMlen; i < merger.MemLen; i++)
			merger.pMem[i] = pMem[i];
	else 
		for (int i = minMlen; i < merger.MemLen; i++)
			merger.pMem[i] = bf.pMem[i];
	return merger;
}
TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	int k = 1;//флаг, к=1 -> BitLen > bf.BitLen, k=0 -> BitLen < bf.BitLen
	if (BitLen < bf.BitLen)
		k = 0;
	if (k == 0)
		len = bf.BitLen;
	else
		len = BitLen;
	TBitField crossing(len);
	for (int i = 0; i < crossing.MemLen; i++)
		crossing.pMem[i] = pMem[i] & bf.pMem[i];
	return crossing;
}



TBitField TBitField::operator~(void) // отрицание
{
	TBitField opposite(BitLen);
	for (int i = 0; i < (MemLen-1); i++)
		opposite.pMem[i] = ~pMem[i];
	for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++)
		if (GetBit(i) == 0)
			opposite.SetBit(i);
	return opposite;
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
		ostr << bf.GetBit(i)<<' ';
	return ostr;
}
