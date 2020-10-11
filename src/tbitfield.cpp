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
    memset(pMem, 0, MemLen);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[((bf.BitLen + sizeof(TELEM) * 8) + 1) / (sizeof(TELEM) * 8)];
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
    if ((n >= BitLen) || (n < 0)) {
        throw n;
    }
    pMem[GetMemIndex(n)] |= (1 << (n % (sizeof(TELEM) * 8)));
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n >= BitLen) || (n < 0)) {
        throw n;
    }
    pMem[GetMemIndex(n)] |= (1 >> (n % (sizeof(TELEM) * 8)));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n >= BitLen)
        throw std::logic_error("n >= BitLen ");
    if (n < 0)
        throw std::logic_error("n < 0 ");
    return pMem[GetMemIndex(n)] & GetMemMask(n);
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    BitLen = bf.BitLen;
    if (MemLen != bf.MemLen) {
        MemLen = bf.MemLen;
        if (pMem != NULL)
            delete pMem;
        pMem = new TELEM[MemLen];
    }
    if (pMem != NULL)
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    return *this;
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
    int len = bf.BitLen;
    if (BitLen > len) len = BitLen;
    TBitField tmp(len);
    for (int i = 0; i < MemLen; i++) tmp.pMem[i] = pMem[i];
    for (int i = 0; i < bf.MemLen; i++) tmp.pMem[i] &= bf.pMem[i];
    return tmp;
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
            ostr << i << " ";
        }
    return ostr;
}
