// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len <= 0)
        throw std::logic_error("len arr <= 0");
    BitLen = len;
    MemLen = (len / (sizeof(TELEM) * 8)) + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++) {
        pMem[i] = 0;
    }
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < BitLen; i++) 
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = 0;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    int Pos = n % (sizeof(TELEM) * 8);
    TELEM tmp = 1;
    tmp = tmp << Pos;
    return tmp;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n >= BitLen) || (n < 0)) 
        throw n;
    int index = GetMemIndex(n);
    pMem[index] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n >= BitLen) || (n < 0)) {
        throw n;
    }
    int a = GetMemMask(n);
	TELEM Mask = ~GetMemMask(n);
	pMem[a] = pMem[a] & Mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0 || n >= BitLen)
        throw n;
    int x = pMem[GetMemIndex(n)] & GetMemMask(n);
    if (x > 0)
        return 1;
    return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this == &bf)
        return *this;

    delete[] pMem;
    pMem = 0;
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if(BitLen != bf.BitLen)
        return 0;
    else
    {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 0;
        return 1;
    }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
        return 1;
    else
    {
        for (int i = 0; i < MemLen; i++)
            if (pMem[i] != bf.pMem[i])
                return 1;
        return 0;
    }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int len = bf.BitLen;
    if (BitLen > len)
        len = BitLen;
    TBitField tmp(len);
    for (int i = 0; i < MemLen; i++) 
        tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++) 
        tmp.pMem[i] |= bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen >= bf.BitLen) {
        TBitField tmp(BitLen);
        for (size_t i = 0; i < bf.BitLen; i++) {
            if ((GetBit(i) == 1) && (bf.GetBit(i) == 1)) {
                tmp.SetBit(i);
            }
        }
        return tmp;
    }
    else {
        TBitField tmp(bf);
        for (size_t i = 0; i < MemLen; i++) {
            tmp.pMem[i] = tmp.pMem[i] & pMem[i];
        }
        return tmp;
    }

}

TBitField TBitField::operator~(void) // отрицание
{
    int i;
    int len = BitLen;
    TBitField tmp(len);
    for (i = 0; i < MemLen; i++)
        tmp.pMem[i] = ~pMem[i];
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int tmp;
    for (int i = 0; i < bf.BitLen; i++) {
        istr >> tmp;
        if (tmp == 1) bf.SetBit(i);
        else bf.ClrBit(i);
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
        if (bf.GetBit(i))
        {
            ostr << i;
        }
    return ostr;
}
