// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len > 0)
	{

		BitLen = len;
		MemLen = (BitLen + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
		pMem = new TELEM[MemLen];
		memset(pMem, 0, MemLen);
	}
	else 
	{
		throw " zero or negative length ";
	}
	if (pMem != NULL)
	{
		for (int i = 0; i < MemLen; i++)
			pMem[i] = 0;
	}
	else
	{
		throw " no memory";
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
			pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete pMem;
	pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return(n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % (sizeof(TELEM) * 8 ));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
  
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);

	}
	else
	{
		throw " cannot_set_bit_with_negative_index";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	
	if ((n > -1) && (n < BitLen))
	{
		int i = GetMemIndex(n);
		pMem[i] = pMem[i] & ~GetMemMask(n);
	}
	else
	{
		throw " cannot_clr_bit_with_negative_index";
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) && (n < BitLen))
	{
		return pMem[GetMemIndex(n)] & GetMemMask(n);
	}
		else
		{
			throw " cannot_get_bit_with_incorrect_index";
		}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	BitLen = bf.BitLen;
	if (MemLen != bf.MemLen)
	{
		MemLen = bf.MemLen;
		if (pMem != NULL) delete[]pMem;
		pMem = new TELEM[MemLen];
	}

	if (pMem != NULL)
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	else
	{
		throw" no memory ";
	}

return *this;


}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int res = 1;
		if (BitLen != bf.BitLen)
		{
			res = 0;
		}
		else
		{
			for (int i = 0; i < MemLen; i++)
			{
				if (pMem[i] != bf.pMem[i])
				{
					res = 0;
					break;
				}
			}
		}
		return res;

  
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int res = 0;
		if (BitLen != bf.BitLen)
		{
			res = 1;
		}
		else
		{
			for (int i = 0; i < MemLen; i++)
			{
				if (pMem[i] != bf.pMem[i])
				{
					res = 1;
					break;
				}
			}
		}
		return res;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}

	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] |= bf.pMem[i];
	}
	
	return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int i;
	int len = BitLen;
	if (bf.BitLen > len)
	{
		len = bf.BitLen;
	}

	TBitField tmp(len);
	for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = pMem[i];
	}
	for (int i = 0; i < bf.MemLen; i++)
	{
		tmp.pMem[i] &= bf.pMem[i];
	}

	return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	int len = BitLen;
	TBitField tmp(len);
	/*for (int i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = ~pMem[i];
	}*/
	for ( int i = 0; i < BitLen; i++)
	{
		if (this->GetBit(i) == 0)
		{
			tmp.SetBit(i);
		}
		else
		{
			tmp.ClrBit(i);
		}

	}
	return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int i = 0;
	char ch;

	/*char ch;
	for (int i = 0; i < bf.BitLen; i++)
	{
		istr >> ch;
		if (ch == 1)
		{
			bf.SetBit(i);
		}
		else
		{
			if (ch == 0)
			{
				bf.ClrBit(i);
			}
			else
				break;
		}
	}
	return istr;*/
	
	do { istr >> ch; } while (ch != ' ');

	while (1)
	{
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else 
			if (ch == '1')
			bf.SetBit(i++);
		else break;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len= bf.GetLength();
	for (int i = 0; i < len; i++)
	{
		if (bf.GetBit(i))
		{
			ostr << '1';
		}
		else
		{
			ostr << '0';
		}
	}
	return ostr;
}
