// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0) throw ("Negative bitfield length");
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
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[bf.MemLen];
	
	for (int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n > BitLen - 1)) 
		throw ("Wrong number");
	else 
		return n / (sizeof(TELEM) << 3);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n > BitLen - 1) || (n < 0))
		throw ("Wrong number");
	else
		return 1 << n % (sizeof(TELEM) << 3);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > BitLen - 1) || (n < 0))
		throw ("Wrong number");
	else
		pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > BitLen - 1) || (n < 0))
		throw ("Wrong number");
	else
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int value = 0;
	if ((n > BitLen - 1) || (n < 0))
		throw ("Wrong number");
	else {
		if ((pMem[GetMemIndex(n)] & GetMemMask(n)))
			value = 1;
		return value;
	}
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
	int flag = 0;
	
	if (BitLen != bf.BitLen) return 0;

	for (int i = 0; i < BitLen; i++) {
		if (GetBit(i) != bf.GetBit(i))
			flag++;
		else
			continue;
	}
	
	if (flag) return 0;
		else return 1;
	
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if ((*this) == bf) return 0;
		else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int flag;
	if (BitLen >= bf.BitLen) 
		flag = 1;
	else 
		flag = 0;

	int m;
	if (flag) 
		m = bf.BitLen;
	else 
		m = BitLen;
	
	TBitField res = flag ? (*this) : bf;
	
	for (int i = 0; i < m; i++) {
		if (GetBit(i) | bf.GetBit(i)) res.SetBit(i);
	}
	return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n; 
	if (BitLen >= bf.BitLen) n = BitLen; 
		else n = bf.BitLen;
	
	int m;
	if (BitLen >= bf.BitLen) m = bf.BitLen;
		else m = BitLen;
	
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
	int tmp;
	for (int i = 0; i < bf.BitLen; i++) {
		istr >> tmp;
		if (tmp)
			bf.SetBit(tmp);
		else
			bf.ClrBit(tmp);
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i) << ' ';
	return ostr;
}