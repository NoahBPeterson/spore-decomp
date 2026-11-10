// Flags: /O2 /MD /Gy /TP
struct Base14 {
    char m00[0x14];
    Base14& operator=(const Base14& o); // 0x00c1b790
};
struct Int15 { int m[15]; };
struct LocoCopy : Base14 {
    Int15 mArr;                 // +0x14
    int m50, m54, m58, m5c;
    float m60, m64, m68, m6c;
    int m70;
    LocoCopy& operator=(const LocoCopy& o);
};

// @ 0x00c43de0
LocoCopy& LocoCopy::operator=(const LocoCopy& o)
{
    Base14::operator=(o);
    mArr = o.mArr;
    m50 = o.m50;
    m54 = o.m54;
    m58 = o.m58;
    m5c = o.m5c;
    m60 = o.m60;
    m64 = o.m64;
    m68 = o.m68;
    m6c = o.m6c;
    m70 = o.m70;
    return *this;
}
