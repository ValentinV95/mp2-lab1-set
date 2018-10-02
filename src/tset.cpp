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
	return TBitField (BitField);//TBitField объект класа TBitField
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if ((Elem < 0) || (Elem > MaxPower - 1))
		throw ("Элемент неположителен или значение элемента превышает размер множества");
	else {
		int k = BitField.GetBit(Elem);
		return k;//k=0-> элемент не принадлежит множеству, k=1-> элемент принадлежит множеству
	}
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem < 0) || (Elem > MaxPower - 1))
		throw ("Элемент неположителен или значение элемента превышает размер множества");
	else 
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem < 0) || (Elem > MaxPower - 1))
		throw ("Элемент неположителен или значение элемента превышает размер множества");
	else
		BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower=s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int res = (BitField == s.BitField);//res=1 равны
	return res;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int res = (BitField != s.BitField);//res=1 не равны
	return res;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int len;
	if (MaxPower > s.MaxPower)
		len = MaxPower;
	else
		len = s.MaxPower;
	TSet merger(len);
	merger.BitField = BitField | s.BitField;
	return merger;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if ((Elem < 0) || (Elem > MaxPower - 1))
		throw ("Элемент неположителен или значение элемента превышает размер множества");
	else {
		TSet mergerelem(BitField);
		mergerelem.BitField.SetBit(Elem);
		return mergerelem;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if ((Elem < 0) || (Elem > MaxPower - 1))
		throw ("Элемент неположителен или значение элемента превышает размер множества");
	else {
		TSet mergerelem(BitField);
		mergerelem.BitField.ClrBit(Elem);
		return mergerelem;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet crossing(BitField & s.BitField);
	return crossing;
}

TSet TSet::operator~(void) // дополнение
{
	TSet opposite(~BitField);
	return opposite;
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
		if (s.BitField.GetBit(i)==1)
			ostr << i<<' ';
	return ostr;
}
