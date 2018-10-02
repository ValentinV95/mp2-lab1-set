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
		throw("Negative len");
	else
	{
		MemLen = ((BitLen - 1) / (8 * sizeof(unsigned))) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[]pMem;
	
	
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	
	if ((n < 0) || (n>(BitLen-1)))
		throw ("Uncorr num for get");
	else {
		int Ind = n / (sizeof(TELEM) * 8);

		return Ind;
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n>(BitLen - 1)))
		throw ("uncor num for mask");
	
	else 
	{
		int otst = n % (sizeof(TELEM) * 8);
		TELEM Mask = 0;
		Mask = 1 << otst;
		return Mask;
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n>(BitLen - 1)))
		throw ("uncorr num for set");
	else
	{
		TELEM maskto = GetMemMask(n);
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | maskto;
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n>(BitLen - 1)))
		throw ("uncorr num for clr");
	else {
		TELEM Mask = ~GetMemMask(n);
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & Mask;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n>(BitLen - 1)))
		throw ("uncorr num for get");
	else {
		int InMem = GetMemIndex(n);
		int Sm = n % (sizeof(TELEM) * 8);
		if ((pMem[InMem] & (1 << Sm)) == GetMemMask(Sm))
			return 1;
		else return 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen != bf.BitLen)
	{
		delete[]pMem;
		pMem = new TELEM[bf.MemLen];
	}
	for (int i = 0; i < bf.MemLen; i++)
		pMem[i] = bf.pMem[i];
	BitLen = bf.BitLen;
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen)
		return 0;
		for (int i = 0; i < BitLen; i++)
		{
			if (GetBit(i) != bf.GetBit(i))
				return 0;
		}

			
	 return 1;
	
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int flag = (*this == bf);
	if (flag == 0)
		return 1;
	else return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int Newbl, Newml;
	Newml = (bf.MemLen >= MemLen) ? bf.MemLen : MemLen;
	Newbl = (bf.BitLen >= BitLen) ? bf.BitLen : BitLen;
	TBitField C(Newbl);
	for (int i = 0; i < Newml; i++)
		C.pMem[i] = pMem[i]|bf.pMem[i];
	return C;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int Newbl,Newml;
	Newml = (bf.MemLen >= MemLen) ? bf.MemLen : MemLen;
	Newbl = (bf.BitLen >= BitLen) ? bf.BitLen : BitLen;
	TBitField C(Newbl);
	for (int i = 0; i < Newml; i++)
		C.pMem[i] = pMem[i] & bf.pMem[i];
	return C;
}

TBitField TBitField::operator~(void) // отрицание
{
	int rez;
	TBitField C(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		rez = GetBit(i);
		if (rez == 0)
			C.SetBit(i);
	}
		return C;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int a;
	int len = bf.BitLen;
	for (int i = 0; i < len; i++)

	{
		cin >> a;
		switch (a)
		{
		case 1: bf.SetBit(i);
			break;
		case 0: bf.ClrBit(i);
			break;
		default: throw ("Uncorrect i/o");
			break;
		}
		
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int a;
	int len = bf.BitLen;
	for (int i = 0; i < len; i++)
	{
		a = bf.GetBit(i);
		cout << a;

	}
	return ostr;
}
