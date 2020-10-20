#include "TBitField.h"

TBitField::TBitField(size_t len) :BitLen(len)
{
    MemLen = (BitLen) / (sizeof(TELEM) * byte);
    if ((BitLen) % (sizeof(TELEM) * byte) != 0)
        MemLen++;

    pMem = new TELEM[MemLen];

    memset(pMem, 0, MemLen * sizeof(TELEM));
}


TBitField::TBitField(size_t memlen, size_t bitlen)
    :MemLen(memlen), BitLen(bitlen)
{
    pMem = new TELEM[MemLen];
    memset(pMem, 0, MemLen * sizeof(TELEM));
}

TBitField::TBitField(const TBitField& bf)
{
    BitLen = bf.BitLen;
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (size_t i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
    pMem = NULL;
    BitLen = MemLen = 0;
}

size_t TBitField::GetMemIndex(const int n) const
{
    return n / (sizeof(TELEM) * byte);
}

TELEM TBitField::GetMemMask(const int n) const
{
    return (1 << ((sizeof(TELEM) * byte) - 1 - n % (sizeof(TELEM) * byte)));
}


size_t TBitField::GetLength(void) const
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

bool TBitField::GetBit(const int n) const
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

        for (size_t i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

bool TBitField::operator==(const TBitField& bf) const
{
    for (size_t i = 0; i < MemLen && i < bf.MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return false;

    if (MemLen > bf.MemLen) {
        for (size_t i = bf.MemLen; i < MemLen; i++)
            if (pMem[i] != 0)
                return false;
    }
    else
        if (MemLen < bf.MemLen) {
            for (size_t i = MemLen; i < bf.MemLen; i++)
                if (bf.pMem[i] != 0)
                    return false;
        }

    return true;
}

bool TBitField::operator!=(const TBitField& bf) const
{
    for (size_t i = 0; i < MemLen && i < bf.MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return true;

    if (MemLen > bf.MemLen) {
        for (size_t i = bf.MemLen; i < MemLen; i++)
            if (pMem[i] != 0)
                return true;
    }
    else
        if (MemLen < bf.MemLen) {
            for (size_t i = MemLen; i < bf.MemLen; i++)
                if (bf.pMem[i] != 0)
                    return true;
        }

    return false;
}

TBitField TBitField::operator|(const TBitField& bf)
{
    size_t new_size = (MemLen > bf.MemLen) ? MemLen : bf.MemLen;
    size_t new_bitlen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;

    TBitField result(new_size, BitLen);

    for (size_t i = 0; i < MemLen && i < bf.MemLen; i++)
        result.pMem[i] = pMem[i] | bf.pMem[i];

    if (MemLen > bf.MemLen) {
        for (size_t i = bf.MemLen; i < MemLen; i++)
            result.pMem[i] = pMem[i];
    }
    else
        if (MemLen < bf.MemLen)
            for (size_t i = MemLen; i < bf.MemLen; i++)
                result.pMem[i] = bf.pMem[i];

    return result;
}

TBitField TBitField::operator&(const TBitField& bf)
{
    size_t new_size = (MemLen < bf.MemLen) ? MemLen : bf.MemLen;
    size_t new_bitlen = (BitLen < bf.BitLen) ? BitLen : bf.BitLen;

    TBitField result(new_size, BitLen);

    for (size_t i = 0; i < MemLen && i < bf.MemLen; i++)
        result.pMem[i] = pMem[i] & bf.pMem[i];

    return result;
}

TBitField TBitField::operator~(void)
{
    TBitField res(BitLen);
    for (int i = 0; i < MemLen; i++)
        res.pMem[i] = ~pMem[i];

    return res;
}

TBitField TBitField :: operator^(const TBitField& bf) {
    size_t new_size = (MemLen > bf.MemLen) ? MemLen : bf.MemLen;
    size_t new_bitlen = (BitLen > bf.BitLen) ? BitLen : bf.BitLen;

    TBitField result(new_size, BitLen);

    for (size_t i = 0; i < MemLen && i < bf.MemLen; i++)
        result.pMem[i] = pMem[i] ^ bf.pMem[i];

    if (MemLen > bf.MemLen) {
        for (size_t i = bf.MemLen; i < MemLen; i++)
            result.pMem[i] = ~pMem[i];
    }
    else
        if (MemLen < bf.MemLen)
            for (size_t i = MemLen; i < bf.MemLen; i++)
                result.pMem[i] = ~bf.pMem[i];

    return result;
}



istream& operator>>(istream& istr, TBitField& bf)
{
    istr >> bf.BitLen;

    TBitField res(bf.BitLen);

    delete[] bf.pMem;

    bf.pMem = res.pMem;

    res.pMem = NULL;

    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf)
{
    for (size_t i = 0; i < bf.BitLen; i++)
        ostr << bool(bf.pMem[bf.GetMemIndex(i)] & bf.GetMemMask(i)) << ' ';

    return ostr;
}

