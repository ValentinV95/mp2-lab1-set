#include "TSet.h"

TSet::TSet(size_t mp) : MaxPower(mp + 1), BitField(MaxPower) {}

TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}


TSet::TSet(const TBitField& bf) : BitField(bf) { MaxPower = bf.GetLength() - 1; }

TSet::operator TBitField()
{
    return BitField;
}

size_t TSet::GetMaxPower(void) const
{
    return MaxPower;
}

bool TSet::IsMember(const unsigned int Elem) const
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const unsigned int Elem)
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const unsigned int Elem)
{
    BitField.ClrBit(Elem);
}



bool TSet::operator==(const TSet& s) const
{
    return BitField == s.BitField;
}

bool TSet::operator!=(const TSet& s) const
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s)
{
    TSet res(BitField | (s.BitField));
    return res;
}

TSet TSet::operator+(const unsigned int Elem)
{
    TSet res(*this);

    res.BitField.SetBit(Elem);

    return res;
}

TSet TSet::operator-(const unsigned int Elem)
{
    TSet res(*this);

    res.BitField.ClrBit(Elem);

    return res;
}

TSet TSet::operator*(const TSet& s)
{
    TSet res(BitField & (s.BitField));
    return res;
}

TSet TSet::operator~(void)
{
    TSet res(~BitField);
    return res;
}

TSet TSet::operator^(const TSet& b) {
    TSet res(BitField ^ (b.BitField));
    return res;
}



istream& operator>>(istream& istr, TSet& s)
{
    size_t N;
    istr >> N;

    for (size_t i = 0; i < N; i++) {
        unsigned int n;
        istr >> n;
        s.BitField.SetBit(n);
    }

    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s)
{
    for (size_t i = 0; i < s.BitField.GetLength(); i++)
        if (s.BitField.GetBit(i))
            ostr << i << ' ';

    return ostr;
}

