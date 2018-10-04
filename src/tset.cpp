// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf.GetLength())
{
	MaxPower = bf.GetLength();
	BitField = bf;
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
	if (Elem <= MaxPower)
	{
		if (BitField.GetBit(Elem) != 1)
		{
			return 0;
		}
	}
    return 1;
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < MaxPower)
	{
		BitField.SetBit(Elem);
	}
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < MaxPower)
	{
		BitField.ClrBit(Elem);
	}
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
	if (MaxPower == s.MaxPower && BitField == s.BitField)
	{
		return 1;
	}
	return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (MaxPower == s.MaxPower && BitField == s.BitField)
	{
		return 0;
	}
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	if (MaxPower > s.MaxPower)
	{
		TSet temp(MaxPower);
		temp.BitField = BitField | s.BitField;
		return temp;
	}
	if (MaxPower <= s.MaxPower)
	{
		TSet temp(s.MaxPower);
		temp.BitField = BitField | s.BitField;
		return temp;
	}
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{	
	if (Elem >= MaxPower)
	{
		throw "Elem > Maxpower";
	}
	else
	{
		TSet temp(MaxPower);
		temp.BitField = BitField;
		temp.BitField.SetBit(Elem);
		return temp;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet temp(MaxPower);
	temp.BitField = BitField;
	temp.BitField.ClrBit(Elem);
	return temp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	if (MaxPower > s.MaxPower)
	{
		TSet temp(MaxPower);
		temp.BitField = BitField & s.BitField;
		return temp;
	}
	if (MaxPower <= s.MaxPower)
	{
		TSet temp(s.MaxPower);
		temp.BitField = BitField & s.BitField;
		return temp;
	}
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(MaxPower);
	temp.BitField = ~BitField;
	return temp;
}
// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int i;
	istr >> i;
	s.InsElem(i);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (unsigned int i = 0; i < s.MaxPower; i++)
	{
		if (s.BitField.GetBit(i) == 1)
		{
			ostr << i << " ";
		}
	}
	ostr << endl;
	return ostr;
}
