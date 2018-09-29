#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = BitField.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0 || Elem >= MaxPower)
	{
		throw "Incorrect element";
	}
	if (BitField.GetBit(Elem))
	{
		return 1;
	}
	return 0;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower)
	{
		throw "Incorrect element";
	}
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 || Elem >= MaxPower)
	{
		throw "Incorrect element";
	}
	BitField.ClrBit(Elem );
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
	{
		return 0;
	}
	else if (BitField != s.BitField)
	{
		return 0;
	}
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (*this == s)
	{
		return 0;
	}
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet temp = *this;
	temp.BitField = temp.BitField | s.BitField;
	if (s.MaxPower > temp.MaxPower)
	{
		temp.MaxPower = s.MaxPower;
	}
	return temp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= MaxPower)
	{
		throw "Incorrect element";
	}
	BitField.SetBit(Elem);
	return *this;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem >= MaxPower)
	{
		throw "Incorrect element";
	}
	BitField.ClrBit(Elem);
	return *this;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet temp = *this;
	temp.BitField = temp.BitField & s.BitField;
	if (s.MaxPower > temp.MaxPower)
	{
		temp.MaxPower = s.MaxPower;
	}
	return temp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp = *this;
	temp.BitField = ~temp.BitField;
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int Elem;
	istr >> Elem;
	if (Elem >= s.BitField.GetLength())
	{
		throw "Incorrect element";
	}
	s.BitField.SetBit(Elem);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "Elements of the set: ";
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{
		if (s.BitField.GetBit(i))
		{
			ostr << i << ((i == s.BitField.GetLength() - 1) ? "." : ", ");
		}
	}
	return ostr;
}
