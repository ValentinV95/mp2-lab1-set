// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

struct incorrect_evalue {
	string s;
	incorrect_evalue(string ss = "Error: incorrect evalue") { s = ss; }
};

TBitField::TBitField(int len)
{
	if (len <= 0) throw(incorrect_evalue());

	BitLen = len;
	MemLen = ((BitLen - 1) / (8 * sizeof(TELEM))) + 1;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}


TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];

	for (int i = 0; i < MemLen; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen - 1)) throw (incorrect_evalue());

	return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n > BitLen - 1)) throw (incorrect_evalue());

	return 1 << n % (sizeof(TELEM) * 8);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n > BitLen - 1)) throw (incorrect_evalue());

	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n > BitLen - 1)) throw (incorrect_evalue());

	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n > BitLen - 1)) throw (incorrect_evalue());

	int offset = n % (sizeof(TELEM) * 8);

	return (pMem[GetMemIndex(n)] >> offset) & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (this != &bf) {
		delete[] pMem;

		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++) {
			pMem[i] = bf.pMem[i];
		}
	}

	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 0;

	for (int i = 0; i < BitLen; i++) {
		
		if (GetBit(i) != bf.GetBit(i)) 	return 0;

	}

	return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return ((*this) == bf) ? 0 : 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if ((*this) == bf) return (*this);

	int flag = (BitLen >= bf.BitLen) ? 1 : 0;

	int n = flag ? BitLen : bf.BitLen;
	int m = flag ? bf.BitLen : BitLen;

	TBitField res = flag ? (*this) : bf;

	for (int i = 0; i < m; i++) {

		if (GetBit(i) | bf.GetBit(i)) res.SetBit(i);

	}

	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if ((*this) == bf) return (*this);

	int n = (BitLen >= bf.BitLen) ? BitLen : bf.BitLen;
	int m = (BitLen >= bf.BitLen) ? bf.BitLen : BitLen;

	TBitField res(n);

	for (int i = 0; i < m; i++) {

		if (GetBit(i) & bf.GetBit(i)) res.SetBit(i);

	}

	return res;
}


TBitField TBitField::operator~(void) // отрицание
{
	TBitField res = (*this);

	for (int i = 0; i < BitLen; i++) {
		
		if (res.GetBit(i)) res.ClrBit(i);

		else res.SetBit(i);
	
	}

	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string in; 
	istr >> in;
	int len_in = in.length();
	int len_bf = bf.GetLength();

	for (int i = 0; i < len_in; i++) {

		if (in[i] == '1') bf.SetBit(i); 
		
		else if (in[i] == '0') bf.ClrBit(i);

		else break;

	}

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int lenght = bf.GetLength();

	for (int i = 0; i < lenght; i++) {
		ostr << bf.GetBit(i);
	}

	return ostr;
}
