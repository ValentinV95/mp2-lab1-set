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
	TBitField bf(BitField);
	return bf;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem)) return 1;

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
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField != s.BitField) return 0;
	
    return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return ((*this) == s) ? 0 : 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet res = (MaxPower > s.MaxPower) ? (*this) : s;
	res.BitField = BitField | s.BitField;

	return res;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet res((*this));
	res.InsElem(Elem);

	return res;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet res((*this));
	res.DelElem(Elem);

	return res;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet res = (MaxPower > s.MaxPower) ? s : (*this);
	res.BitField = BitField & s.BitField;

	return res;
}

TSet TSet::operator~(void) // дополнение
{
	TSet res(MaxPower);
	res.BitField = ~BitField;

	return res;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int n = s.GetMaxPower();

	for (int i = 0; i < n; i++) {

		TELEM tmp;
		istr >> tmp;

		s.InsElem(tmp);

	}

	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int n = s.GetMaxPower();

	for (int i = 0; i < n; i++) {

		if (s.IsMember(i)) ostr << i << " ";

	}

	return ostr;
}
