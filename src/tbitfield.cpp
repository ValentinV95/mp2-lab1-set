#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len <= 0)
	{
		throw "Error: u input size < 0";
	}

	this->BitLen = len;
	this->MemLen = (len - 1) / (8 * sizeof(TELEM)) + 1;
	this->pMem = new TELEM[MemLen];
	
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	this->BitLen = bf.BitLen;
	this->MemLen = bf.MemLen;
	this->pMem = new TELEM[MemLen];
	for (size_t i = 0; i < MemLen; i++)
	{
		this->pMem[i] = bf.pMem[i];
	}
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen))
	{
		throw "(n < 0) || (n >= BitLen)";
	}
		
	return (n / (sizeof(TELEM) * 8));
}

// битовая маска для бита n
TELEM TBitField::GetMemMask(const int n) const 
{
	if ((n < 0) || (n >= BitLen))
	{
		throw "(n < 0) || (n >= BitLen)";
	}
	return (1 << (n % (sizeof(TELEM) * 8)));
}

// доступ к битам битового поля
// получить длину (к-во битов)
int TBitField::GetLength(void) const 
{
  return BitLen;
}

// установить бит
void TBitField::SetBit(const int n) 
{
	if ((n > BitLen) || (n < 0))
	{
		throw "(n > BitLen) or (n < 0)";
	}	
																					//с data[область памяти iого бита] логическое или, чтобы прибавить вместо нулей единицы от числа (1 << (i % (sizeof(uchar) * 8))
	pMem[(GetMemIndex(n))] = pMem[(GetMemIndex(n))] | (GetMemMask(n)); 				//пример : 1 на 3 месте (начиная с 0ой) -> (1 << (i % (sizeof(uchar) * 8)) = 8 = 1000(3 % (sizeof(uchar) * 8) =
}

// очистить бит
void TBitField::ClrBit(const int n) 
{
	if ((n > BitLen) || (n < 0))
	{
		throw "(n > BitLen) or (n < 0)";
	}
		
	pMem[(GetMemIndex(n))] = pMem[(GetMemIndex(n))] & ~(GetMemMask(n));
}

// получить значение бита
int TBitField::GetBit(const int n) const 
{
	if ((n > BitLen) || (n < 0))
	{
		throw "(n > BitLen) or (n < 0)";
	}

	return ((pMem[(GetMemIndex(n))] & (GetMemMask(n)))) ? 1 : 0;
}

// битовые операции
// присваивание
TBitField& TBitField::operator=(const TBitField &bf) 
{
	if (BitLen != bf.BitLen)
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete pMem;
		pMem = new TELEM[MemLen];
		for (size_t i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		for (size_t i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}

	return*this;
}

// сравнение
int TBitField::operator==(const TBitField &bf) const 
{
	if (BitLen != bf.BitLen)
	{
		return 0;
	}
	else
	{
		for (int i = 0; i < BitLen; i++)
		{
		
			if (GetBit(i) != bf.GetBit(i))
			{	
				return 0;
			}
		}

		return 1;
	}
}

// сравнение
int TBitField::operator!=(const TBitField &bf) const 
{
	return !(*this == bf);
}

// операция "или"
TBitField TBitField::operator|(const TBitField &bf) 
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(*this);

		for (size_t i = 0; i < bf.MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] | bf.pMem[i];
		}

		return tmp;
	}
	else
	{
		TBitField tmp(bf);

		for (size_t i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] | pMem[i];
		}

		return tmp;
	}
}

// операция "и"
TBitField TBitField::operator&(const TBitField &bf) 
{
	if (BitLen >= bf.BitLen)
	{
		TBitField tmp(BitLen);

		for (size_t i = 0; i < bf.BitLen; i++)
		{
			if ((GetBit(i) == 1) && (bf.GetBit(i) == 1))
			{
				std::cout << GetBit(i) << "  " << bf.GetBit(i) << endl;
				tmp.SetBit(i);
			}
		}

		return tmp;
	}
	else
	{
		TBitField tmp(bf);

		for (size_t i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] & pMem[i];
		}

		return tmp;
	}
}

// отрицание
TBitField TBitField::operator~(void) 
{
	TBitField tmp(*this);

	for (size_t i = 0; i < MemLen; i++)
	{
		tmp.pMem[i] = ~pMem[i];
	}

	return tmp;
}

// ввод/вывод
// ввод
istream &operator>>(istream &istr, TBitField &bf) 
{
	int i = 0;
	char ch;
	do { istr >> ch; } while (ch != ' ');

	while (1)
	{
		istr >> ch;
		if (ch == '0')
			bf.ClrBit(i++);
		else if (ch == '1')
			bf.SetBit(i++);
		else break;
	}
	return istr;
}

// вывод
ostream &operator<<(ostream &ostr, const TBitField &bf) 
{
	for (int i = 0; i < bf.GetLength(); i++)
		if (bf.GetBit(i)) ostr << '1';
		else ostr << '0';
	return ostr;
}

TBitField::~TBitField()
{
	delete pMem;
	BitLen = 0;
	MemLen = 0;
}
