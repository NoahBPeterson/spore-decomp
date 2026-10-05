// s0046e450 -- /Od /Ob1 region.

struct Mgr {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(void*);
};

extern "C" Mgr* FUN_0067dd60();

struct Sf260 {
    int field0;
    unsigned char flags;
};

// @ 0x0046f260
int __fastcall FUN_0046f260(Sf260* p)
{
    if (!(p->flags & 1))
        FUN_0067dd60()->v13(p);
    return p->field0;
}

struct BaseDesc {
    virtual void v0();
};

struct Desc {
    int a, b;
    unsigned short c, d;
    BaseDesc* ref;
    Desc* init(int, int, BaseDesc*, int);
    Desc* init0();
};

// @ 0x0046f140
Desc* Desc::init(int a_, int b_, BaseDesc* r_, int)
{
    a = a_;
    b = b_;
    c = 4;
    d = 4;
    BaseDesc** local = &ref;
    *local = r_;
    if (*local)
        (*local)->v0();
    return this;
}

// @ 0x0046f1f0
Desc* Desc::init0()
{
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    BaseDesc** local = &ref;
    *local = 0;
    if (*local)
        (*local)->v0();
    return this;
}

// ---- not yet reproduced -----------------------------------------------------

// @ 0x0046e450
void F_0046e450() {}

// @ 0x0046eae0
void F_0046eae0() {}

// @ 0x0046f1b0
void F_0046f1b0() {}

