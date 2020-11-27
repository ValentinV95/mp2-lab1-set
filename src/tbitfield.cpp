#include "tbitfield.h"

TBitField::TBitField(int len)
{
    if (len <= 0)
        throw exception("Uncorrect BitLen!");

    BitLen = len;

    MemLen = (BitLen) / (sizeof(TELEM) * 8);
    if ((BitLen) % (sizeof(TELEM) * 8) != 0)
        MemLen++;

    pMem = new TELEM[MemLen];

    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = NULL;
    BitLen = MemLen = 0;
}

int TBitField::GetMemIndex(const int n) const
{
    if (n >= BitLen)
        throw exception("Uncorrect bit number!");

    return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const
{
    if (n >= BitLen)
        throw exception("Uncorrect bit number!");

    return (1u << ((sizeof(TELEM) * 8) - 1 - n % (sizeof(TELEM) * 8)));
}



int TBitField::GetLength(void) const
{
    return BitLen;
}

void TBitField::SetBit(const int n)
{
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n)
{
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const
{
    return pMem[GetMemIndex(n)] & GetMemMask(n);
}



TBitField& TBitField::operator=(const TBitField& bf)
{
    if (this != &bf) {
        if (MemLen != bf.MemLen) {
            MemLen = bf.MemLen;
            delete[] pMem;
            pMem = new TELEM[MemLen];
        }

        BitLen = bf.BitLen;

        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField& bf) const
{
    if (BitLen != bf.BitLen)
        return false;

    for (int i = 0; i < MemLen && i < bf.MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return false;

    return true;
}

int TBitField::operator!=(const TBitField& bf) const
{
    if (BitLen != bf.BitLen)
        return true;

    for (int i = 0; i < MemLen && i < bf.MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return true;

    return false;
}

TBitField TBitField::operator|(const TBitField& bf)
{
    if (BitLen != bf.BitLen)
        throw exception("Mismatch BitLen!");

    TBitField result(*this);

    for (int i = 0; i < MemLen; i++)
        result.pMem[i] |= bf.pMem[i];

    return result;
}

TBitField TBitField::operator&(const TBitField& bf)
{
    if (BitLen != bf.BitLen)
        throw exception("Mismatch BitLen!");

    TBitField result(*this);

    for (int i = 0; i < MemLen && i < bf.MemLen; i++)
        result.pMem[i] &= bf.pMem[i];

    return result;
}
{
    TBitField res(*this);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = ~res.pMem[i];

    return res;
}



istream& operator>>(istream& istr, TBitField& bf)
{
    istr >> bf.BitLen;

    if (bf.BitLen <= 0)
        throw exception("Uncorrect BitLen!");

    TBitField res(bf.BitLen);

    for (int i = 0; i < bf.BitLen; i++) {
        bool bit;
        istr >> bit;
        if (bit)
            res.SetBit(i);
        else
            res.GetBit(i);
    }

    delete[] bf.pMem;

    bf.pMem = res.pMem;

    res.pMem = NULL;

    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf)
{
    for (int i = 0; i < bf.BitLen; i++)
        ostr << bool(bf.pMem[bf.GetMemIndex(i)] & bf.GetMemMask(i)) << ' ';

    return ostr;
}
