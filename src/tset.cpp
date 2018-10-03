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

int TSet::IsMember(const int Elem) const // элемент множества
{
	if ((Elem >= MaxPower) || (Elem < 0))
		throw ("Индекс бита отрицателен(или равен нулю) или превышает размер битового поля");
	else
		return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem >= MaxPower) || (Elem < 0))
		throw ("Индекс бита отрицателен(или равен нулю) или превышает размер битового поля");
	else
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem >= MaxPower) || (Elem < 0))
		throw ("Индекс бита отрицателен(или равен нулю) или превышает размер битового поля");
	else
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
	return  (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return  (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet ts(s.MaxPower);
	ts.BitField = BitField | s.BitField;
	return ts;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower)
	{
		throw ("Индекс бита отрицателен(или равен нулю) или превышает размер битового поля");
	}
	else
	{
		TSet ts(MaxPower);
		BitField.SetBit(Elem);
		ts.BitField = BitField;
		return ts;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem < 0) || (Elem > MaxPower - 1))
		throw ("Индекс бита отрицателен(или равен нулю) или превышает размер битового поля");
	else {
		TSet SL(BitField);
		SL.BitField.ClrBit(Elem);
		return SL;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet result(BitField & s.BitField);
	return result;
}

TSet TSet::operator~(void) // дополнение
{
	TSet result(~BitField);
	return result;
}

// перегрузка ввода/вывода

istream &operator >> (istream &istr, TSet &s) // ввод
{
	int n;
	for (int i = 0; i < s.MaxPower; i++) {
		istr >> n;
		s.InsElem(n);
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