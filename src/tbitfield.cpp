// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len<1)
		throw"";
	else
	{
		BitLen = len;
		MemLen = (BitLen-1)/(sizeof(TELEM)*8)+1;	
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i]=0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{	
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[BitLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return (n/ (sizeof(TELEM)*8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int Sm = n % (sizeof(TELEM) * 8);
	return (1 << Sm);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n>=0)&&(n<BitLen))
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
	else
		throw"";
		
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n>=0)&&(n<BitLen))
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & (~GetMemMask(n));
	else
		throw"";
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n>=0)&&(n<BitLen))
		if (GetMemMask(n) & pMem[GetMemIndex(n)])
			return 1;
		else
			return 0;
	else
		throw"";
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	delete[] pMem;
	pMem = new TELEM[BitLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
	return (*this);
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
	for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((*this) == bf)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int Maxlen;
	if (BitLen > bf.BitLen)
		Maxlen = BitLen;	
	else
		Maxlen = bf.BitLen;

	TBitField res(Maxlen);

	
	for (int i = 0; i < MemLen; i++) 
		res.pMem[i] = pMem[i]; 
	for (int i = 0; i < bf.MemLen; i++)
		res.pMem[i] |= bf.pMem[i];
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int Maxlen;
	if (BitLen > bf.BitLen)
		Maxlen = BitLen;
		
	else
		Maxlen = bf.BitLen;
		

	TBitField res(Maxlen);
	
		for (int i = 0; i < MemLen; i++) 
			res.pMem[i] = pMem[i]; 
		for (int i = 0; i < bf.MemLen; i++)
			res.pMem[i] &= bf.pMem[i];
	return res;

}

TBitField TBitField::operator~(void) // отрицание
{
	int g;
	for (int i = 0; i < BitLen; i++)
	{
		g=GetBit(i);
		if(g==0)
			SetBit(i);
		else
			ClrBit(i);
	}

	return (*this);
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int n;
	for (int i = 0; i < bf.BitLen; i++)
	{
		cin >> n;
		if (n)
			bf.SetBit(n);
		else
			bf.ClrBit(n);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		cout << bf.GetBit(i);
	return ostr;
}
