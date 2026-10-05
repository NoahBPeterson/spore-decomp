// w1g1 slice s00508400 -- anim container teardown plus a tiny two-float setter.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (movss for the float stores).

typedef unsigned int uint32_t;

// @ 0x00508780
struct TwoFloats {
    float a, b;
    TwoFloats* Set(float x, float y);
};
TwoFloats* TwoFloats::Set(float x, float y)
{
    a = x;
    b = y;
    return this;
}

// ---------------------------------------------------------------------------
// Helpers used by the 0x508400 teardown (all masked relocations).
// ---------------------------------------------------------------------------
void DestroyKeyRange(void* begin, void* end);        // eastl::copy_impl do_copy
void DestroyPairRange(void* begin, void* end);       // vector<pair<int,float>>::erase
void DestroyRangeA(void* begin, void* end);          // 0x0050e690
void DestroyRangeB(void* begin, void* end);          // 0x004769b0 (DwordVector::erase)

struct BigContainer {
    char pad[0x200];

    int Count() const { return (*(int*)((char*)this + 0xe8) - *(int*)((char*)this + 0xe4)) >> 2; }
    int* At(int i) const { return *(int**)((char*)this + 0xe4) + i; }
    void* Sub(int off) const { return *(void**)((char*)this + off); }
    void Clear();    // 0x00508400
    void* Ctor();    // 0x005087b0
};

// @ 0x00508400  (container teardown)
void BigContainer::Clear()
{
    char* b = (char*)this;
    DestroyKeyRange(b + 8, b + 0xc);
    DestroyKeyRange(b + 0x1c, b + 0x20);
    DestroyPairRange(b + 0x30, b + 0x34);
    DestroyRangeA(b + 0x44, b + 0x48);
    DestroyRangeB(b + 0x58, b + 0x5c);
    DestroyRangeB(b + 0x6c, b + 0x70);
    DestroyRangeB(b + 0x80, b + 0x84);
    DestroyRangeB(b + 0x94, b + 0x98);
    DestroyRangeB(b + 0xa8, b + 0xac);
    DestroyRangeB(b + 0xbc, b + 0xc0);
    DestroyRangeB(b + 0x110, b + 0x114);
    DestroyRangeB(b + 0x138, b + 0x13c);
    DestroyPairRange(b + 0x124, b + 0x128);
    for (int i = 0; i < Count(); ++i) {
        int* p = At(i);
        if (p) { /* destroy *p then free */ DestroyRangeB(p, p); }
        *At(i) = 0;
    }
}

// ---------------------------------------------------------------------------
// @ 0x005087b0  (PARTIAL skeleton)
// Large constructor/builder for the same container (2 KB); not reproduced.
// ---------------------------------------------------------------------------
void* BigContainer::Ctor()
{
    return this;
}
