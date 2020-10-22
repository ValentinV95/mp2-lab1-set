// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
    int i;
    if (len < 1)
    {
        throw(len);
    }
    if (constanta == 4) deg = 2;
    if (constanta == 8) deg = 3;
    if (constanta == 16) deg = 4;
    if (constanta == 32) deg = 5;
    if (constanta == 64) deg = 6;
    //больше не знаю, как исправить чтобы было быстрее
    BitLen = len;
    MemLen = (len + (constanta-1)) >> deg;//int имеет 32 бита, но один бит знаковый
    pMem = new TELEM[MemLen]; // выделили память под это кол-во битов
    if (pMem != NULL)
        for (i = 0; i < MemLen; i++)
            pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    int i;
    MemLen = bf.MemLen;
    BitLen = bf.BitLen;
    pMem = new TELEM[MemLen];
    if (pMem != NULL)
        for (i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    return  n >> deg ;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    return 1 << (n & (constanta-1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return 0;
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if ((n < 0) || (n >= BitLen))
    {
        throw(n);
    }
    pMem[GetMemIndex(n)] |= GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if ((n < 0) || (n >= BitLen))
    {
        throw(n);
    }
        pMem[GetMemIndex(n)] &= ~GetMemMask(n);

}

int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n >= BitLen))
  {
      throw(n);
  }
  return(pMem[GetMemIndex(n)] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    int i;
    BitLen = bf.BitLen;
    if (MemLen == bf.MemLen)
    {
        MemLen = bf.MemLen;
        for (i = 0; i<MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    else
    {
        MemLen = bf.MemLen;
        delete[] pMem;
        pMem = new TELEM[MemLen];
        if (pMem != NULL)
        {
            for (i = 0; i<MemLen; i++)
                pMem[i] = bf.pMem[i];
        }
    }

    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int log = 1;
  if (BitLen != bf.BitLen)   log = 0;
  for (int i = 0; i<MemLen; i++)
  {
      if (pMem[i] != bf.pMem[i])
      {
          return log = 0;
      }
  }
  return log;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (*this ==  bf) return 0;
  else return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    int i;
    int len = BitLen;
    if (len < bf.BitLen)
    {
        len = bf.BitLen;
    }
    TBitField pr(len);
        for (i = 0; i < MemLen; i++)
        {
            pr.pMem[i] = pMem[i];
        }
        for (i = 0; i < bf.MemLen; i++)
        {
            pr.pMem[i] |= bf.pMem[i]; // "|=" - битовая операция "или" с присваиванием
        }
    return pr;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    int i;
    int len = BitLen;
    if (len < bf.BitLen)
    {
        len = bf.BitLen;
    }
    TBitField pr(len);
    for (i = 0; i<MemLen; i++)
    {
        pr.pMem[i] = pMem[i];
    }
    for (i = 0; i<bf.MemLen; i++)
    {
        pr.pMem[i] &= bf.pMem[i]; // "&=" - битовая операция "и" с присваиванием
    }
    return pr;
}

TBitField TBitField::operator~(void) // отрицание
{
    int i;
    TBitField pr(BitLen);
        /*for (i = 0; i < pr.MemLen; i++)
            pr.pMem[i] = ~pMem[i];*///побитовая операция "~" отрицание 1->0; 0->1;
        for (i = 0; i <BitLen; i++)
        {
            if (GetBit(i) == 1) pr.ClrBit(i);
            if (GetBit(i) == 0) pr.SetBit(i);
            
        }
    return pr;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    int i;
    char k;
    for (i = 0; i < bf.BitLen; i++)
    {
        printf("<%d> = ", i+1);
        cin >> k;
        if (k == '1')
        {
            bf.SetBit(i);
        }
        else
        {
            bf.ClrBit(i);
        }
    }
    
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    int len = bf.BitLen;
    int i;
    for (i = 0; i < len; i++)
    {
        if (bf.GetBit(i) == 0) cout << ' ' << 0;
        else cout<<' '<< 1;
    }
    return ostr;
}
