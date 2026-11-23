// Same shape as s0042a220's DequeIter::operator+ (0x0042a870); the copy ctor stays
// 0x00420050 and the += goes to 0x0056a270 here (donor: 0x0042d5c0).
// Flags: /Od /Ob1 /MD /Gy /TP

// @ 0x00569eb0
struct DequeIter_00569eb0 {
    unsigned a, b, c, d;
    DequeIter_00569eb0(const DequeIter_00569eb0& o);              // 0x00420050
    DequeIter_00569eb0(const DequeIter_00569eb0& o, int);
    DequeIter_00569eb0& operator+=(int n);                        // 0x0056a270
    DequeIter_00569eb0 operator+(int n) const;
};

DequeIter_00569eb0 DequeIter_00569eb0::operator+(int n) const
{
    return DequeIter_00569eb0(DequeIter_00569eb0(*this) += n);
}
