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
	TSet rez(BitField);
	return rez;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;

}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (BitField.GetBit(Elem) == 0)
		return 0;
	else return 1;
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
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (BitField == s.BitField)
		return 1;
    else return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (BitField != s.BitField)
		return 1;
	else return 0;

}

TSet TSet::operator+(const TSet &s) // объединение
{
	
	TSet Sum = (MaxPower > s.MaxPower) ? (*this) : s;
		Sum.BitField = BitField|s.BitField;
	return Sum;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	
	TSet Sum(*this);
	Sum.InsElem(Elem);

	return Sum;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet Raz(*this);
	Raz.DelElem(Elem);
	return Raz;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet Per = BitField&s.BitField;
	return Per;
}

TSet TSet::operator~(void) // дополнение
{
	
	return ~BitField;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int a;
	int len = s.MaxPower;
	for (int i = 0; i < len; i++)

	{

		istr >> a;
		if (a == 1)
			s.InsElem(i);
		if (a == 0)
			s.DelElem(i);
		else throw ("Check set member");
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int len = s.MaxPower;
	for (int i = 0; i< len; i++)
		ostr << s.IsMember(i);
	return ostr;
}
