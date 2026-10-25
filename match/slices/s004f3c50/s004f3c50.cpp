// w22 slice s004f3c50 -- editor validity bitset intersection helper.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
struct Bits128 {
    uint32_t w[4];
    Bits128(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
    { w[0] = a; w[1] = b; w[2] = c; w[3] = d; }
};

inline bool AnyBit(const Bits128& x)
{
    for (unsigned int i = 0; i < 4; i++)
        if (x.w[i] != 0)
            return true;
    return false;
}

// ===========================================================================
// @ 0x004f3d60  (MATCH)
// Intersects two 4-word bit masks in place and reports whether the result is
// empty (all-zero).
// ===========================================================================
bool FUN_004f3d60(Bits128 a, Bits128 b)
{
    unsigned int i;
    for (i = 0; i < 4; i++)
        a.w[i] &= b.w[i];
    return !AnyBit(a);
}

// ---------------------------------------------------------------------------
// The resolved resource handle is a reference-counted object whose vtable slot
// 1 (+4) releases it. The model object behind it exposes a `CalculateValidity`
// thiscall member (0x4bac30) that forwards to the static validity engine
// 0x4f3de0.
// ---------------------------------------------------------------------------
struct RefCounted {
    void* vptr;              // +0
    virtual void Unk0();     // +0 (slot 0)
    virtual void Release();  // +4 (slot 1)
};

struct AutoRefCount {
    RefCounted* mp;                       // +0
    AutoRefCount() : mp(0) {}
    ~AutoRefCount()
    {
        if (mp)
            mp->Release();
    }
    void Reset()
    {
        if (mp) {
            RefCounted* p = mp;
            mp = 0;
            p->Release();
        }
    }
};

struct cEditorModel {
    // 0x4bac30: __thiscall returning a 16-byte Bits128 in eax; the hidden
    // return pointer is the caller's temporary.
    Bits128 CalculateValidity(Bits128 v, int b);   // 0x4bac30
};

struct ResourceMan {
    virtual void u0(); virtual void u1(); virtual void u2();
    virtual bool Find(int a, AutoRefCount* out, int, int, int, int);  // slot 3 (+0xc)
};

extern ResourceMan* GetManager();   // 0x67dcd0

// ===========================================================================
// @ 0x004f3c50
// Resolves the resource named by `a`, builds the 128-bit requested-validity
// mask from the four ids b,c,d,e, intersects it with the resource model's own
// validity mask and reports whether nothing survives the intersection.
// ===========================================================================
bool FUN_004f3c50(int a, int b, int c, int d, int e)
{
    ResourceMan* man = GetManager();
    AutoRefCount handle;
    if (man != 0) {
        handle.Reset();
        if (man->Find(a, &handle, 0, 0, 0, 0)) {
            Bits128 v((uint32_t)b, (uint32_t)c, (uint32_t)d, (uint32_t)e);
            return FUN_004f3d60(
                ((cEditorModel*)handle.mp)->CalculateValidity(v, 1), v);
        }
    }
    return false;
}
