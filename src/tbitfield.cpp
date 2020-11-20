// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"


TBitField::TBitField(int len)
{
    if (len < 0)
        throw "Wrong length";
    MemLen = len / (8 * sizeof(TELEM)) + 1;
    pMem = new TELEM[MemLen];
    BitLen = len;
    memset(pMem, 0, MemLen);
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    MemLen = bf.MemLen;
    BitLen - bf.BitLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
    {
        pMem[i] = bf.pMem[i];
    }
}

TBitField::~TBitField()
{
    delete [] pMem;
    pMem = NULL;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0 || n >= BitLen)
        throw "Error";
    return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0 || n >= BitLen)
        throw "Wrong bit";
    return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen))
        throw "Wrong bit";
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
        throw "Wrong bit";
    pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if ((n < 0) || (n > BitLen))
    {
        throw "Neg bit";
    }

    if ((pMem[GetMemIndex(n)] & GetMemMask(n)) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (this != &bf)
    {
        delete[]pMem;
        BitLen = bf.BitLen;
        MemLen = bf.MemLen;
        pMem = new TELEM[MemLen];
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
   }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return 0;
    }
    else
    {
        int flag = 1;
        for (int i = 0; (i < bf.MemLen) && (flag); i++)
        {
            if (pMem[i] != bf.pMem[i])
            {
                return 0;
            }
        }
        return 1;
    }
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.BitLen)
    {
        return 1;
    }
    else
    {
        int flag = 1;
        for (int i = 0; (i < bf.MemLen) && (flag); i++)
        {
            if (pMem[i] != bf.pMem[i])
            {
                return 1;
            }
        }
        return 0;
    }
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    if (BitLen < bf.BitLen)
    {
        TBitField a(bf);
        for (int i = 0; i < BitLen; i++)
        {
            if ((a.GetBit(i) | GetBit(i)) == 1)
            {
                a.SetBit(i);
            }
            else
            {
                a.ClrBit(i);
            }
        }
        return a;
    }
    else
    {
        TBitField b(*this);
        for (int i = 0; i < bf.BitLen; i++)
        {
            if ((b.GetBit(i) | b.GetBit(i)) == 1)
            {
                b.SetBit(i);
            }
            else
            {
                b.ClrBit(i);
            }
        }
        return b;
    }
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    if (BitLen > bf.BitLen)
    {
        TBitField g(BitLen);
        for (int i = 0; i < bf.MemLen; i++)
        {
            g.pMem[i] = pMem[i] & bf.pMem[i];
        }
        for (int i = bf.MemLen; i < g.MemLen; i++)
        {
            g.pMem[i] = 0;
        }
        return g;
    }
    else
    {
        TBitField g(bf.BitLen);
        for (int i = 0; i < MemLen; i++)
        {
            g.pMem[i] = pMem[i] & bf.pMem[i];
        }
        for (int i = MemLen; i < g.MemLen; i++)
        {
            g.pMem[i] = 0;
        }
        return g;
    }
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField g(BitLen);
    for (int i = 0; i < MemLen - 1; i++)
    {
        g.pMem[i] = ~pMem[i];
    }
    for (int i = ((MemLen - 1) * (sizeof(TELEM) * 8)); i < BitLen; i++)
    {
        if (GetBit(i) == 0)
        {
            g.SetBit(i);
        }
        else
        {
            g.ClrBit(i);
        }
    }
    return g;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string temp;
    istr >> temp;
    if (temp.size() != bf.GetLength())
        throw "Incorrect length";
    else
    {
        for (int i = 0; i < bf.GetLength(); i++)
        {
            if (temp[i] == '0')
                bf.ClrBit(i);
            else
                if (temp[i] == '1')
                    bf.SetBit(i);
                else
                    throw "Incorrect enter";
        }
        return istr;
    }
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        if (bf.GetBit(i))
            ostr << 1;
        else
            ostr << 0;
    }
    return ostr;
}
