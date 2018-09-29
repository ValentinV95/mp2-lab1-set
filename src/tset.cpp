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
	TBitField a(BitField);
	return a;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	 return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if(MaxPower != s.MaxPower)
	{
		return 0;
	}
	if(BitField != s.BitField)
	{
		return 0;
	}
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	 return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int t;
	MaxPower > s.MaxPower ? t = MaxPower : t = s.MaxPower;
	TSet set(t);
	set.BitField = BitField | s.BitField;
	return set;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet set(*this);
	set.BitField.SetBit(Elem);
	return set;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet set(*this);
	set.BitField.ClrBit(Elem);
	return set;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int t;
	MaxPower > s.MaxPower ? t = MaxPower : t = s.MaxPower;
	TSet set(t);
	set.BitField = BitField & s.BitField;
	return set;
}

TSet TSet::operator~(void) // дополнение
{
	TSet set(*this);
	set.BitField = ~BitField;
	return set;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int x;
	istr >> x;
	s.BitField.SetBit(x);
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << "Set contains the following elements:" << endl;
	for (int i = 0; i < s.BitField.GetLength(); i++)
	{	
		if(s.BitField.GetBit(i))
		{
			ostr << i << " ";
		}
	}
	return ostr;
}
