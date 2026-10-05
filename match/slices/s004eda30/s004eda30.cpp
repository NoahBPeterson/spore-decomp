// w1g1 slice s004eda30 -- editor validity resource-entry accessors.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

struct Manager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual void* Find(int a, int b); // +0x58
};
void* GetMgr401010();

// ===========================================================================
// @ 0x004ee930  (MATCH)
// Looks up the model-type key pair of entry `index` in a resource's entry
// vector (stride 0x1d8); returns 0 when out of range.
// ===========================================================================
int FUN_004ee930(unsigned int index, int res)
{
    int p12, p15, v18, n35;
    p15 = res + 0x98;
    if (index >= (unsigned int)((*(int*)(p15 + 4) - *(int*)p15) / 0x1d8))
        return 0;
    n35 = (int)GetMgr401010();
    p12 = *(int*)p15 + (int)index * 0x1d8;
    v18 = *(int*)p15 + (int)index * 0x1d8;
    return (int)((Manager*)n35)->Find(*(int*)(v18 + 4), *(int*)p12);
}

// ===========================================================================
// @ 0x004edeb0  (complete; not byte-exact)
// Clears bit 16 of a flag word (the original keeps an unreachable set-bit
// branch that /Od did not fold away).
// ===========================================================================
bool FUN_004edeb0(int unused, unsigned int* p)
{
    (void)unused;
    if (p != 0)
        p[0] &= 0xfffeffff;
    return true;
}

// ===========================================================================
// @ 0x004eda30  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004eda30(void* a, void* b)
{
    (void)a; (void)b;
}

// ===========================================================================
// @ 0x004edf40  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004edf40(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004ee3b0  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004ee3b0(void* a, void* b)
{
    (void)a; (void)b;
}

// ===========================================================================
// @ 0x004ee560  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004ee560(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}
