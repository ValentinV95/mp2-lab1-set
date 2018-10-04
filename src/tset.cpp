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
	return TBitField (BitField);
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem >= MaxPower || Elem < 0)   
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
	else 
		return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem >= MaxPower || Elem < 0)
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
	else  
		BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem >= MaxPower || Elem < 0)
		throw ("Index previsil rasmer bitovogo poly or index nepologit");
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
	int len;
	if (MaxPower > s.MaxPower)
		len = MaxPower;
	else
		len = s.MaxPower;
	TSet a(len);
	a.BitField = BitField | s.BitField;
	return a;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem >= MaxPower || Elem < 0 )
		throw("Index previsil rasmer bitovogo poly or index nepologit");
	else {
		TSet a(BitField);
		a.BitField.SetBit(Elem);
		return a;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem >= MaxPower || Elem < 0 )
		throw("Index previsil rasmer bitovogo poly or index nepologit");
	else {
		TSet a(BitField);
		a.BitField.ClrBit(Elem);
		return a;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet rez(BitField & s.BitField); 
	return rez;
}

TSet TSet::operator~(void) // дополнение
{
	TSet rez(~BitField); 
	return rez;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
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
