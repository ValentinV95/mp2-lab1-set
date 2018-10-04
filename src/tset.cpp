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
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return TBitField(BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if ((Elem < 0) || (Elem >= MaxPower))
		throw("false Elem in case 1");
	else {
		int Temp = BitField.GetBit(Elem);
		return Temp;
	}
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem < 0) || (Elem >=MaxPower))
		throw("false Elem in case 2");
	else
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem < 0) || (Elem >= MaxPower))
		throw("false Elem in case 3");
	else
		BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField = s.BitField;
	MaxPower=s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (MaxPower != s.MaxPower)
		return 0;
	if (BitField != s.BitField)
		return 0;
	return 1;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (*this == s)
		return 0;
	return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int Power=((MaxPower<s.MaxPower)?s.MaxPower:MaxPower);
	TSet OR(Power);
	OR.BitField = BitField | s.BitField;
	return OR;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
		TSet ORELEM(MaxPower);
	//	BitField.SetBit(Elem);
		ORELEM.BitField.SetBit(Elem);
		return ORELEM;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem < 0) || (Elem >= MaxPower))
		throw("false Elem in case 4");
	else {
		TSet DIFF(BitField);
		DIFF.BitField.ClrBit(Elem);
		return DIFF;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int Power = (MaxPower <= s.MaxPower) ? s.MaxPower : MaxPower;
	TSet AND(Power);
	AND.BitField = BitField&s.BitField;
	return AND;
}

TSet TSet::operator~(void) // дополнение
{
	TSet ADDITION(MaxPower);
	ADDITION.BitField = ~BitField;
	return ADDITION;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int k;
	for (int i = 0; i < s.MaxPower; i++) {
		istr >> k;
		s.InsElem(k);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.BitField.GetBit(i) == 1)
			ostr << i << ' ';
	return ostr;
}
