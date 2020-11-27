#include "TSet.h"

TSet::TSet(int mp) : MaxPower(mp + 1), BitField(MaxPower) {}


TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField) {}


TSet::TSet(const TBitField& bf) : BitField(bf) { MaxPower = bf.GetLength() - 1; }

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem)
{
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem)
{
    BitField.ClrBit(Elem);
}



int TSet::operator==(const TSet& s) const
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const
{
    return BitField != s.BitField;
}

TSet& TSet::operator=(const TSet& s){
    if (this != &s) {
        MaxPower = s.MaxPower;
        BitField = s.BitField;
    }
    return *this;
}

TSet TSet::operator+(const TSet& s)
{
    TSet res(BitField | (s.BitField));
    return res;
}

TSet TSet::operator+(const int Elem)
{
    TSet res(*this);

    res.BitField.SetBit(Elem);

    return res;
}

TSet TSet::operator-(const int Elem)
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


istream& operator>>(istream& istr, TSet& s)
{
    int N;
    istr >> N;

    if (N <= 0)
        throw exception("Uncorrect N!");

    for (int i = 0; i < N; i++) {
        int n;
        istr >> n;
        s.BitField.SetBit(n);
    }

    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s)
{
    for (int i = 0; i < s.BitField.GetLength(); i++)
        if (s.BitField.GetBit(i))
            ostr << i << ' ';

    return ostr;
}
