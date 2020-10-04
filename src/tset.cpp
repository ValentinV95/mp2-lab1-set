#include "tset.h"

//конструктор по умолчанию
TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower) {}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength()) {}

TSet::operator TBitField()
{
	TBitField tmp(BitField);
	return tmp;
}

// получить макс. к-во эл-тов
int TSet::GetMaxPower(void) const 
{
    return MaxPower;
}

// элемент множества ли? 
int TSet::IsMember(const int Elem) const
{
	return BitField.GetBit(Elem);
}

// включение элемента множества
void TSet::InsElem(const int Elem) 
{
	BitField.SetBit(Elem);
}

// исключение элемента множества
void TSet::DelElem(const int Elem)
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции
// присваивание
TSet& TSet::operator=(const TSet &s) 
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;

	return* this;
}

// сравнение ==
int TSet::operator==(const TSet &s) const 
{
    return (BitField == s.BitField);
}

// сравнение !=
int TSet::operator!=(const TSet &s) const
{
    return (BitField != s.BitField);
}

// объединение
TSet TSet::operator+(const TSet &s) 
{
	return ((BitField) | (s.BitField));
}

// объединение с элементом
TSet TSet::operator+(const int Elem) 
{
	if (Elem < MaxPower)
	{
		TSet tmp(*this);
		tmp.InsElem(Elem);
		return tmp;
	}
	else
	{
		throw "Elem > maxpPower";
	}
}

// разность с элементом
TSet TSet::operator-(const int Elem) 
{
	if (Elem < MaxPower)
	{
		TSet tmp(*this);
		tmp.DelElem(Elem);
		return tmp;
	}
	else
	{
		throw "Elem > Maxpower";
	}
}

// пересечение
TSet TSet::operator*(const TSet &s) 
{
	return ((BitField) & (s.BitField));
}

// дополнение
TSet TSet::operator~(void) 
{
	return (~BitField);
}

// перегрузка ввода/вывода
// ввод
istream &operator>>(istream &istr, TSet &s) 
{
	int el;
	for (int i = 0; i < s.GetMaxPower(); i++)
	{
		istr >> el;
		s.InsElem(el);
	}

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField << ' ';
	return ostr;
}
