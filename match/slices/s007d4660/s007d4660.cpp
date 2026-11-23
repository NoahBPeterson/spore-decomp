// @ 0x007d4660
// tail-virtual-call forward: this->field_0x3c (an inner object), and if non-null jump to
// its vtable slot 14 (offset 0x38); otherwise return.
struct Inner_007d4660 {
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
    virtual void v13();
    virtual void Fwd_007d4660();          // slot 14, offset 0x38
};

struct W_007d4660 {
    char pad_0x3c[0x3c];
    Inner_007d4660* mInner;
    void FUN_007d4660();
};

void W_007d4660::FUN_007d4660() {
    Inner_007d4660* p = mInner;   // one read, kept in the register across the branch
    if (p)
        p->Fwd_007d4660();
}
