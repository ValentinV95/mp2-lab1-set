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
	MaxPower=bf.GetLength();

}

TSet::operator TBitField()
{
	TBitField a(MaxPower);
	a = BitField;
	return a;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return(MaxPower);
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem))
		return 1;
    return 0;
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
	return (*this);
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if ((MaxPower == s.MaxPower) && (BitField == s.BitField))
		return 1;
    return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return!(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int max;
	max = (MaxPower > s.MaxPower) ? MaxPower : s.MaxPower;
	TSet a(max);
	a.BitField = BitField | s.BitField;
	return a;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet a(*this);
	a.BitField.SetBit(Elem);
	return(a);
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet a(*this);
	a.BitField.ClrBit(Elem);
	return(a);
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int min;
	min = (MaxPower < s.MaxPower) ? MaxPower : s.MaxPower;
	TSet a(min);
	a.BitField = BitField & s.BitField;
	return a;
}

TSet TSet::operator~(void) // дополнение
{
	TSet a(*this);
	~a.BitField;
	return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr >> s.BitField;
	return(istr);
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr << s.BitField;
	return(ostr);
}
