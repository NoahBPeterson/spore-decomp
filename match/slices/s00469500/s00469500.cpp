// s00469500 -- functions 00469500 00469550 00469590 004696d0 00469790 00469920
// /Od /Ob1 region.

struct S45sub {
    // 4-byte subobject constructed by FUN_00401b80(caller this+0x10, arg)
    S45sub(int);
};

// 00469500: 4 int members + a subobject at +0x10 constructed from the 5th arg.
struct S45a {
    int a, b, c, d;
    S45sub sub;
    S45a(int, int, int, int, int);
};

// @ 0x00469500
S45a::S45a(int a_, int b_, int c_, int d_, int e_)
    : a(a_), b(b_), c(c_), d(d_), sub(e_)
{
    int hole_;
    (void)hole_;
}

// 00469550: 5 int members.
struct S45b {
    int a, b, c, d, e;
    S45b* init(int, int, int, int, int);
};

// @ 0x00469550
S45b* S45b::init(int a_, int b_, int c_, int d_, int e_)
{
    a = a_;
    b = b_;
    c = c_;
    d = d_;
    e = e_;
    return this;
}

// 004696d0: copy-assignment; 7 members of 0x14 bytes, each assigned via its own
// out-of-line operator=.
struct M45 {
    char pad[0x14];
    M45& operator=(const M45&);
};

struct S45c {
    M45 m0, m1, m2, m3, m4, m5, m6;
    S45c& operator=(const S45c&);
};

// @ 0x004696d0
S45c& S45c::operator=(const S45c& o)
{
    m0 = o.m0;
    m1 = o.m1;
    m2 = o.m2;
    m3 = o.m3;
    m4 = o.m4;
    m5 = o.m5;
    m6 = o.m6;
    return *this;
}

// ---- not yet reproduced -----------------------------------------------------

// @ 0x00469590
void F_00469590() {}

// @ 0x00469790
void F_00469790() {}

// @ 0x00469920
void F_00469920() {}
