// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <algorithm>
#include <string>

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
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if (Elem < 0 && Elem >= MaxPower)
	{
		throw "Out of range";
	}
	else
	{
		return this->BitField.GetBit(Elem);
	}
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0 && Elem >= MaxPower)
	{
		throw "Out of range";
	}
	else
	{
		return this->BitField.SetBit(Elem);
	}
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0 && Elem >= MaxPower)
	{
		throw "Out of range";
	}
	else
	{
		return this->BitField.ClrBit(Elem);
	}
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
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return  BitField != s.BitField;;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet a(max(MaxPower, s.MaxPower));
	a.BitField = BitField | s.BitField;
	return a;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 && Elem >= MaxPower)
	{
		throw "Out of range";
	}
	else
	{
		TSet a(*this);
		a.BitField.SetBit(Elem);
		return a;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 && Elem >= MaxPower)
	{
		throw "Out of range";
	}
	else
	{
		TSet a(*this);
		a.BitField.ClrBit(Elem);
		return a;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet a(max(MaxPower, s.MaxPower));
	a.BitField = BitField & s.BitField;
	return a;
}

TSet TSet::operator~(void) // дополнение
{
	TSet a(*this);
	a.BitField = ~a.BitField;
	return a;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	string a;
	char buff[100];
	int number_temp,current_pos = 0;
	int count = 0;
	getline(istr, a);
	for (int i = 0;i < a.size();i++)
	{
		current_pos = i;
		count = 0;
		while (a[current_pos] != ' ' && current_pos < a.size())
		{
			current_pos++;
			count++;
		}
		for (int j = 0;j < count;j++)
		{
			buff[j] = a[i + j];
		}
		number_temp = atoi(buff);
		if (number_temp < 0 && number_temp >= s.MaxPower)
		{
			throw "One of the elements is out of range";
		}
		else
		{
			s.BitField.SetBit(number_temp);
		}
		i = current_pos;
		for (int j = 0;j < 100;j++)
		{
			buff[j] = 0;
		}
	}
	s.MaxPower = s.BitField.GetLength();
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0;i < s.MaxPower;i++)
	{
		if (s.IsMember(i) == 1)
		{
			cout << i << " ";
		}
	}
	return ostr;
}
