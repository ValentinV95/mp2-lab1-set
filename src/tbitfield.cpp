// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{

	if ( len > 0 )
	{	
	MemLen = (len + 31) >> 5;
	pMem = new TELEM [MemLen];
	BitLen = len;
	for ( int i = 0; i < MemLen; i++)
		pMem[i] = 0;
	}
	else 
	{
		throw("Negative len");
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{

	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM [MemLen];
	for ( int i = 0; i < MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete []pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int i = n / (8*sizeof(TELEM));
	return i;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	int  Bias = n % (8*sizeof(TELEM));
	TELEM MemMask = 1 << Bias;// находи смещение 1<<смещение
	return MemMask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
	{
		throw("Negative len");
	}
	else
	{
	int i = GetMemIndex (n);
	pMem[i] = pMem[i] | GetMemMask (n);
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
	{
		throw("Negative len");
	}
	else
	{
	int i = GetMemIndex (n);
	TELEM Mask = ~GetMemMask (n);
	pMem[i] = pMem[i] & Mask;
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
	{
		throw("Negative len");
	}
	else
	{
	int i = GetMemIndex(n);
	TELEM Mask = GetMemMask (n);
	if ((Mask & pMem[i]) != 0)
		return 1;
	else 
		return 0;
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if ( this != &bf)
	{
		delete []pMem;
		int len  = bf.GetLength(); 
		BitLen = len;
		MemLen = bf.MemLen;
		pMem = new TELEM [MemLen];
		for ( int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];

	}
	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int i;
  if (BitLen != bf.BitLen)
	  return 0;
  else
  {
	for ( i = 0 ; i < MemLen; i++ )
	{
		if( pMem[i] != bf.pMem[i] )
			 return 0;
	}
  }
  return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
 int i;
  if (BitLen != bf.BitLen)
	  return 1;
  else
  {
	for ( i = 0; i < MemLen; i++ )
		if( pMem[i] != bf.pMem[i] )
			 return 1;
  }

  return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int len;
	
	if ( BitLen > bf.BitLen)
		len = BitLen;
	else 
		len = bf.BitLen;
	TBitField Tmp (len);

	for (int i = 0; i < MemLen; i++)
		Tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Tmp.pMem[i] |= bf.pMem[i];
		
	return Tmp;	
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int len;
	
	if ( BitLen > bf.BitLen)
		len = BitLen;
	else 
		len = bf.BitLen;
	TBitField Tmp (len);
		
	for (int i = 0; i < MemLen; i++)
		Tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Tmp.pMem[i] &= bf.pMem[i];

	return Tmp;	

}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField Tmp (BitLen);

	for (int i = 0; i < BitLen; i++)
	{
		int j = 0;
		j = GetBit(i);
		if ( j == 1 ) Tmp.ClrBit(i);
		else Tmp.SetBit(i);
	}

	return Tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int k ;
	for ( int i = 0; i < bf.BitLen; i++)
	{
		 istr >> k ;					
		if ( k == 0)
			bf.ClrBit (i);
		else if ( k == 1) 
			bf.SetBit(i);
		else 
	{
		throw("Negative len");
	}
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int Elem;
	for (int i = 0; i < bf.BitLen; i++)
	{
		Elem = bf.GetBit(i);
		if (Elem == 1)
			ostr << i << " ";
	}
	return ostr;
}
