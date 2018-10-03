// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <math.h>
#include <string>

TBitField::TBitField(int len) 
{
	if (len > 0)
	{
		BitLen = len;
		MemLen = (int)(len / (sizeof(TELEM) * 8));
		if ((len % (sizeof(TELEM) * 8)) > 0)
		{
			MemLen++;
		}
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	else
	{
		throw "Wrong data";
	}
}

TBitField::TBitField(const TBitField &bf) //конструктор копирования
{
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	BitLen = bf.BitLen;
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}

}

TBitField::~TBitField() //деструктор
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int Index = (int)(n / (sizeof(TELEM) * 8));
	
	return Index;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	TELEM Mask = 1;
	int position = (n % (sizeof(TELEM) * 8));
	Mask = Mask << position;
	return Mask;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const 
{
	return BitLen;
}

void TBitField::SetBit(const int n) 
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = (int)(n / (sizeof(TELEM) * 8)); 
		pMem[num] = pMem[num] | GetMemMask(n); 
	}
	else
	{
		throw "Wrong data";
	}
}

void TBitField::ClrBit(const int n)
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = (int)(n / (sizeof(TELEM) * 8));

		pMem[num] = pMem[num] & ~GetMemMask(n); // очистка
	}
	else
	{
		throw "Индекс бита отрицателен(или равен нулю) или превышает размер битового поля";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n >= 0) && (n <= BitLen))
	{
		int num = (int)(n / (sizeof(TELEM) * 8)); 		
		if ((pMem[num] & GetMemMask(n)) == GetMemMask(n))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		throw "Индекс бита отрицателен(или равен нулю) или превышает размер битового поля";
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
	int result = 1;
	if ((BitLen != bf.BitLen) || (bf.pMem == 0))
		result = 0;
	else
		for (int i = 0; (i < MemLen) && (result == 1); i++)
			if (pMem[i] != bf.pMem[i])
				result = 0;
	return result;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int result = 0;
	if (BitLen != bf.BitLen)
		result = 1;
	else
		for (int i = 0; i < MemLen; i++)
			if (pMem[i] != bf.pMem[i]) {
				result = 1;
				break;
			}
	return result;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int tmp;
	if (BitLen > bf.BitLen)
		tmp = BitLen;
	else
		tmp = bf.BitLen;
	TBitField result(tmp);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		result.pMem[i] |= bf.pMem[i];
	return result;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int tmp;
	if (BitLen > bf.BitLen)
		tmp = BitLen;
	else
		tmp = bf.BitLen;
	TBitField result(tmp);
	for (int i = 0; i < MemLen; i++)
		result.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		result.pMem[i] &= bf.pMem[i];
	return result;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField result(BitLen);
	int n = BitLen - 1;
	for (int i = 0; i < BitLen; i++)
		if (GetBit(i) != 0)
			result.ClrBit(i);
		else
			result.SetBit(i);
	return result;
}

// ввод/вывод

istream &operator >> (istream &istr, TBitField &bf) // ввод
{
	string strtmp;
	cin >> strtmp;
	const char* tmp = strtmp.c_str();
	TBitField b(strlen(tmp));
	for (int i = 0; i < strlen(tmp); i++)
	{
		if (tmp[i] == '1')
		{
			b.SetBit(i);
		}
	}
	bf = b;
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i) == bf.GetMemMask(i))
		{
			ostr << "1";
		}
		else
		{
			ostr << "0";
		}
	}
	return ostr;
}


