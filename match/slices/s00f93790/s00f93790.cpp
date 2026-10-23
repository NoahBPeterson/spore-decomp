// Slice s00f93790 -- 0x0f9xxxx region (SP::cTerrainResourceManager TU, mixed with
// the EASTL fixed_vector / SpVector COMDATs it instantiates).
//
// Frozen batch gold5.  32-bit x86, MSVC 2008 SP1, flags /O2 /MD /Gy /TP /arch:SSE
// /fp:fast (default /GS on).

struct Vector3 {
    float x, y, z;
};

// ?erase@?$SpVector@UVector3@@@@QAEPAUVector3@@PAU2@0@Z (0x50f740): the terrain
// code's own SpVector<T> (begin/end/capacity + two bookkeeping pointers).
template <class T>
class SpVector {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    T* mpPool;
    T* mpStorage;
    T* erase(T* first, T* last);
};

// Object holding four SpVector<Vector3> members at +0x10 (stride 0x14) plus the
// "dirty" flag at +0x0c that FUN_00f93c00 clears.
class Self {
public:
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

private:
    char pad4[8];

public:
    char mFlag;
    SpVector<Vector3> mVec[4];
};

void* __cdecl EAAllocate(unsigned int size, const char* pFile, int a, int b, int c, int d);
extern int g_vtblGmeRefCount;
extern int g_rdata149015c;
extern int g_rdata1490158;

// The retail initialiser keeps two writes to the same field (+0x04) apart, which
// the /O2 store eliminator would otherwise collapse, so the constructor region is
// fenced with the no-code barrier intrinsic.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// @ 0x00f939b0 -- FUN_00f939b0
// Allocates the 0x68-byte terrain resource manager, then initialises it: the
// GmeRefCount base vtable and the two data words at +0/+4, the flag bytes at
// +0x0c and +0x60, and the first three pointers of each of the four
// SpVector<Vector3> members at +0x10 (stride 0x14).
void* __fastcall FUN_00f939b0() {
    int zero = 0;
    int* p = (int*)EAAllocate(0x68, "Terrain/ResourceManager/cTerrainResourceManager", zero, zero, zero, zero);
    if (p != 0) {
        p[2] = zero;
        p[1] = (int)&g_vtblGmeRefCount;
        _ReadWriteBarrier();
        *((char*)p + 0xc) = (char)zero;
        p[0] = (int)&g_rdata149015c;
        p[1] = (int)&g_rdata1490158;
        _ReadWriteBarrier();
        p[4] = zero;
        p[5] = zero;
        p[6] = zero;
        p[9] = zero;
        p[10] = zero;
        p[0xb] = zero;
        p[0xe] = zero;
        p[0xf] = zero;
        p[0x10] = zero;
        p[0x13] = zero;
        p[0x14] = zero;
        p[0x15] = zero;
        *((char*)p + 0x60) = (char)zero;
        p[0x19] = zero;
        return p;
    }
    return 0;
}

// @ 0x00f93c00 -- FUN_00f93c00 (__fastcall, this in ecx)
// If the dirty flag at +0x0c is set, clears it, drains each of the four
// SpVector<Vector3> members at +0x10 (stride 0x14) and notifies through the
// tenth virtual slot (+0x24).
bool __fastcall FUN_00f93c00(Self* self) {
    if (self->mFlag != 0) {
        self->mFlag = 0;
        SpVector<Vector3>* p = &self->mVec[0];
        int n = 4;
        do {
            p->erase(p->mpBegin, p->mpEnd);
            p = (SpVector<Vector3>*)((char*)p + 0x14);
            --n;
        } while (n != 0);
        self->v9();
    }
    return true;
}
