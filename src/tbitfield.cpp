// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле
#include <iostream>
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0) {
	BitLen = len;
	MemLen = (len - 1)/(8*sizeof(TELEM)) + 1;
	pMem = new TELEM[MemLen];
	for(int i =0 ; i < MemLen; i++){
	pMem[i]=0;
	}
	}
	else {
		throw("Отрицательная длина");
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM [MemLen];
	for (int i = 0; i < BitLen; i++) {
		pMem[i] = bf.pMem[i];
	}
	
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	TELEM tmp = n /(8*sizeof(TELEM));
	return tmp;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM tmp = 1 << (n%(8*sizeof(TELEM)));
	return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if(n >= 0 && n <= BitLen) {		
	
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | (GetMemMask(n)) ;
		
	}
	else {
		throw ("Значение отрицательно или больше допустимого");
	}
	
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if(n >= 0 && n <= BitLen) {
	
	pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~(GetMemMask(n)) ;
	}
	else {
	throw ("Значение отрицательно или больше допустимого");
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if(n >= 0 && n <= BitLen) {

	int tmp;
	
	tmp = pMem[GetMemIndex(n)] & (GetMemMask(n)) ;

	if (tmp != 0) {
	tmp = 1;
	}
	 return tmp;
	}
	else {
	throw ("Значение отрицательно или больше допустимого");
	}
 
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	delete [] pMem;
	BitLen = bf.GetLength();
	MemLen = bf.MemLen;
	pMem = new TELEM [MemLen];
	for (int i =0 ; i < MemLen; i++	) {
		pMem[i] =bf.pMem[i];
	}
	return *this;
}


int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int i = 0, tmp = 0, n = bf.GetLength();
	if(BitLen == n){
		tmp = 1;
		while (i < n){

			if (bf.GetBit(i) !=  GetBit(i)) {
				tmp = 0;
				
				break;

			}
			i++;
		}
	}
  return tmp;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	return (!((*this) == bf)); 
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int max = bf.GetLength(), min = BitLen;
	if (BitLen > bf.GetLength()) {
		max = BitLen;
		min = bf.GetLength();
	}

	TBitField a(max);
 	for (int i = 0; i < max; i++)
	{

		if(i < min)
		{
			if (GetBit(i) || bf.GetBit(i))
			{

				a.SetBit(i);
			}
		} else {
			if(BitLen > bf.GetLength()) {
				if(GetBit(i)){
				a.SetBit(i);
				}
			} else {
				if(bf.GetBit(i)){
				a.SetBit(i);
				}
			}
		}
		
	}
	return a;
	
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int max = bf.GetLength(), min = BitLen;
	if (BitLen > bf.GetLength()) {
		max = BitLen;
		min = bf.GetLength();
	}

	TBitField a(max);
 	for (int i = 0; i < max; i++)
	{

		if(i < min)
		{
			if (GetBit(i) && bf.GetBit(i))
			{

				a.SetBit(i);
			}
		}
	}
	return a;
}

TBitField TBitField::operator~(void) // отрицание
{	
	TBitField a = *this;
	for (int i = 0; i < (MemLen); i++){

		a.pMem[i] = ~pMem[i];
	}

	for (int i = (MemLen - 1) * sizeof(TELEM) * 8; i < BitLen; i++){

		if (GetBit(i))
		{
			a.ClrBit(i);
			
		} else {
			a.SetBit(i);
		}

	}
	return a;	
	
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	unsigned int  temp;
	
	for(int i =0 ; i < bf.BitLen; i++) {
		istr >> temp ;
		if(temp) {
			bf.SetBit(i);
		}else {
			bf.ClrBit(i);
		}
	}
	
	
   return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for(int i = 1; i <= bf.GetLength() ; i++)

		ostr << bf.GetBit(i)<<' ';

    return ostr; 
}