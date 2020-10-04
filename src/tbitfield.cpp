#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw "Error: u input size < 0";
	}

	this->BitLen = len;
	this->MemLen = (len + sizeof(TELEM) * 8 - 1) / (sizeof(TELEM) * 8);
	this->pMem = new TELEM[MemLen];
	memset(pMem, 0, MemLen);
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
	return 1 << (n & (sizeof(TELEM) * 8 - 1));
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
	pMem[(n / (sizeof(TELEM) * 8))] = pMem[(n / (sizeof(TELEM) * 8))] | (1 << (n % (sizeof(TELEM) * 8))); 				//пример : 1 на 3 месте (начиная с 0ой) -> (1 << (i % (sizeof(uchar) * 8)) = 8 = 1000(3 % (sizeof(uchar) * 8) =
}

// очистить бит
void TBitField::ClrBit(const int n) 
{
	if ((n > BitLen) || (n < 0))
	{
		throw "(n > BitLen) or (n < 0)";
	}
		
	pMem[(n / (sizeof(TELEM) * 8))] = pMem[(n / (sizeof(TELEM) * 8))] & ~(1 << (n % (sizeof(TELEM) * 8)));
}

// получить значение бита
int TBitField::GetBit(const int n) const 
{
	if ((n > BitLen) || (n < 0))
	{
		throw "(n > BitLen) or (n < 0)";
	}

	return ((pMem[(n / (sizeof(TELEM) * 8))] & (1 << (n % (sizeof(TELEM) * 8))))) ? 1 : 0;
}

//Операции-методы
void TBitField::or_b(const TBitField& bf)
{
	if (BitLen >= bf.BitLen)
	{
		for (int i = 0; i < bf.MemLen; i++)
		{
			pMem[i] = pMem[i] | bf.pMem[i];
		}
	}
	else
	{
		TELEM* new_pMem = new TELEM[bf.MemLen];

		for (int i = 0; i < MemLen; i++)
		{
			new_pMem[i] = pMem[i] | bf.pMem[i];
		}

		for (size_t i = MemLen; i < bf.MemLen; i++)
		{
			new_pMem[i] = bf.pMem[i];
		}

		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		delete pMem;
		pMem = new TELEM[MemLen];

		for (size_t i = 0; i < MemLen; i++)
		{
			pMem[i] = new_pMem[i];
		}
	}
}

void TBitField::and_b(const TBitField& bf)
{
	if (BitLen == bf.BitLen)
	{
		for (size_t i = 0; i < bf.MemLen; i++)
		{
			pMem[i] = pMem[i] & bf.pMem[i];
		}
	}
	else
	{
		if (BitLen > bf.BitLen)
		{
			TBitField tmp(BitLen);
			for (size_t i = 0; i < bf.MemLen; i++)
			{
				tmp.pMem[i] = bf.pMem[i];
			}

			for (size_t i = 0; i < bf.MemLen; i++)
			{
				pMem[i] = pMem[i] & tmp.pMem[i];
			}
		}
		else
		{
			for (size_t i = 0; i < MemLen; i++)
			{
				pMem[i] = pMem[i] & bf.pMem[i];
			}
		}
	}
}

void TBitField::sub_b(const TBitField& bf)
{
	if (BitLen >= bf.BitLen)
	{
		for (size_t i = 0; i < bf.MemLen; i++)
		{
			pMem[i] = pMem[i] & (~bf.pMem[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < MemLen; i++)
		{
			pMem[i] = pMem[i] & (~bf.pMem[i]);
		}
	}
}

void TBitField::un_sub_b()
{
	for (size_t i = 0; i < MemLen; i++)
	{
		pMem[i] = ~pMem[i];
	}
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
		for (int i = 0; i < MemLen; i++)
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
	if(BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
		{

			if (pMem[i] != bf.pMem[i])
			{
				return 1;
			}

			return 0;
		}
	}
	else
	{
		return 1;
	}

	return 0;
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
		TBitField tmp(*this);

		for (size_t i = 0; i < bf.MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] & bf.pMem[i];
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

TBitField TBitField::operator-(const TBitField& bf)
{
	TBitField tmp(*this);

	if (BitLen >= bf.BitLen)
	{
		for (size_t i = 0; i < bf.MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] & (~bf.pMem[i]);
		}
	}
	else
	{
		for (size_t i = 0; i < MemLen; i++)
		{
			tmp.pMem[i] = tmp.pMem[i] & (~bf.pMem[i]);
		}
	}

	return tmp;
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
	char str;
	
	while (true) 
	{
		istr >> str;

			if (str == '0')
			{
				bf.ClrBit(i++);
			}
			else
			{
				if (str == '1')
				{
					bf.SetBit(i++);
				}
				else
				{
					break;
				}
			}
	}

	return istr;
}

// вывод
ostream &operator<<(ostream &ostr, const TBitField &bf) 
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}

	return ostr;
}

TBitField::~TBitField()
{
	delete pMem;
	BitLen = 0;
	MemLen = 0;
}
