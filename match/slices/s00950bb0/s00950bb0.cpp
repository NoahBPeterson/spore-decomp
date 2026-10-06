// Slice s00950bb0: EA::UTFWin UI window-proc dispatch + small value/pool helpers (MSVC 2008 SP1,
// /O2 /MD /Gy /EHsc /TP /arch:SSE). PDB names used where known.
#include "types.h"

extern "C" void  FUN_960410(void*, void*);                          // UTFWin::Window::DoMessage
extern "C" void* FUN_009289f0(unsigned, int, int, int, int, int);   // cSPMemPool::LockedAlloc
extern "C" void* FUN_00928a30(int, unsigned, int, int, int, int, int, int); // cSPMemPool::LockedAligned
extern "C" void  FUN_009276c0(void*, void*);
extern void* g_pMemPool16c8b44;

namespace EA { namespace UTFWin {

// vtable at +0, refcount at +0x1c.
struct CustomWinProc {
    virtual void slot0();
    virtual void slot1();
    virtual void slot2(int);
    char pad[0x18];
    unsigned int mnRefCount;    // +0x1c

    void* AsInterface(int typeId);   // 0x00950EB0
    void* AsInterfaceA(int typeId);  // 0x00951240
    int   Release();                 // 0x009514A0
};

// @ 0x00950EB0
void* CustomWinProc::AsInterface(int typeId) {
    if (typeId == 0x2f009dd0) return this;
    if (typeId == (int)0xee3f516e || typeId == (int)0xeec58382) {
        if (this) return (char*)this + 4;
    }
    return 0;
}

// @ 0x00951240
void* CustomWinProc::AsInterfaceA(int typeId) {
    if (typeId == 0x6ec581fd) return this;
    if (typeId == (int)0xee3f516e || typeId == (int)0xeec58382) {
        if (this) return (char*)this + 4;
    }
    return 0;
}

// @ 0x009514A0
int CustomWinProc::Release() {
    int n = (*(volatile int*)&mnRefCount += -1);
    if (n == 0) slot2(1);
    return n;
}

struct MultiHeapObject {
    static void operator_delete(void* p);
};

// @ 0x00951330  EA::UTFWin::MultiHeapObject::operator delete
struct MemPoolObj { void Free(void*); };
extern MemPoolObj* g_pool16c8b44;

void MultiHeapObject::operator_delete(void* p) {
    if (p) {
        int* alloc = *(int**)((char*)p - 8);
        p = (char*)p - 8;
        if (alloc) {
            ((void(__thiscall*)(void*, void*, int))((void**)*(void**)alloc)[3])(alloc, p, 0);
        } else {
            g_pool16c8b44->Free(p);
        }
    }
}

}} // namespace EA::UTFWin

using EA::UTFWin::CustomWinProc;

// ---------------------------------------------------------------------------------------------
// @ 0x00951D60  pool allocator
// ---------------------------------------------------------------------------------------------
struct MemPool {
    char pad0[0x40];
    int  free0;     // +0x40
    int  cur0;      // +0x44
    char pad1[0xc];
    int  free1;     // +0x54
    int  cur1;      // +0x58

    void* Alloc(unsigned size);
};

void* MemPool::Alloc(unsigned size) {
    if (size == 0) return 0;
    if (size < 0x80 && free0 != cur0) {
        void* v = *(void**)(cur0 - 4);
        cur0 -= 4;
        return v;
    }
    if (size < 0x800 && free1 != cur1) {
        void* v = *(void**)(cur1 - 4);
        cur1 -= 4;
        return v;
    }
    return FUN_009289f0(size, 0, 0, 0, 0, 0);
}

// ---------------------------------------------------------------------------------------------
// @ 0x009512D0  aligned pool alloc with vtable-allocator fallback
// ---------------------------------------------------------------------------------------------
void* AllocAligned(int base, int size, int, int* allocator) {
    unsigned n = (size - 1U | 7) + 1;
    void* p;
    if (allocator == 0) {
        p = FUN_00928a30(base + 8, n, 8, 0, 0, 0, 0, 0);
    } else {
        p = ((void*(__thiscall*)(void*, int, int, unsigned, int))((void**)*(void**)allocator)[1])(allocator, base + 8, 0, n, 8);
    }
    if (p == 0) return 0;
    *(void**)p = allocator;
    return (char*)p + 8;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00951DC0  iterator copy
// ---------------------------------------------------------------------------------------------
struct IterCopy {
    int f0, f1, f2, f3, f4, f5, f6, f7;
    IterCopy* Set(int* src);
};

IterCopy* IterCopy::Set(int* src) {
    f0 = (int)(size_t)src;
    f1 = src[1];
    f2 = src[2];
    int v = src[3];
    f3 = v;
    f4 = v;
    int v2 = src[5];
    f5 = v2;
    f6 = src[6];
    f7 = 0;
    if (v2 != f6) f7 = f3 + *(int*)(v2 + 4) * 0x14;
    return this;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00952100 / 0x00952130 / 0x00952160  bounds value
// ---------------------------------------------------------------------------------------------
struct Bounds {
    char pad0[0x10];
    char  mValid;       // +0x10
    char pad1[3];
    float mMinX;        // +0x14
    float mMinY;        // +0x18
    float mMaxX;        // +0x1c
    float mMaxY;        // +0x20

    char GetBounds(float* out);
    void SetBounds(char valid, const float* r);
    void UnionBounds(const float* r);
};

char Bounds::GetBounds(float* out) {
    out[0] = mMinX;
    out[1] = mMinY;
    out[2] = mMaxX;
    out[3] = mMaxY;
    return mValid;
}

void Bounds::SetBounds(char valid, const float* r) {
    mValid = valid;
    if (valid) {
        mMinX = r[0]; mMinY = r[1]; mMaxX = r[2]; mMaxY = r[3];
    }
}

void Bounds::UnionBounds(const float* r) {
    if (mValid == 0) {
        mValid = 1;
        mMinX = r[0]; mMinY = r[1]; mMaxX = r[2]; mMaxY = r[3];
        return;
    }
    if (mMaxX <= r[0] || r[2] <= mMinX || mMaxY <= r[1] || r[3] <= mMinY) {
        mMinX = 0; mMinY = 0; mMaxX = 0; mMaxY = 0;
        return;
    }
    if (r[0] > mMinX) mMinX = r[0];
    if (r[1] > mMinY) mMinY = r[1];
    if (r[2] < mMaxX) mMaxX = r[2];
    if (r[3] < mMaxY) mMaxY = r[3];
}

// ---------------------------------------------------------------------------------------------
// @ 0x009514D0
// ---------------------------------------------------------------------------------------------
bool ForwardCall514d0(int* a, int* b) {
    void* obj = *(void**)((char*)a + 4);
    ((void(__thiscall*)(void*, int, int))((void**)*(void**)obj)[0x24 / 4])(obj, b[1], b[2]);
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x009513D0 / 0x009514F0  vertex-elem array init (stride 8 / 0xc)
// ---------------------------------------------------------------------------------------------
bool InitArray8(int* out, int src, int, int* allocator) {
    int* obj = *(int**)(src + 4);
    int count = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    out[2] = count;
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, count * 8, 4);
    out[1] = (int)(size_t)p;
    out[0] = 0x1440200;
    if (count != 0) {
        if (p == 0) return false;
        ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, count);
    }
    return true;
}

bool InitArray12(int* out, int src, int, int* allocator) {
    int* obj = *(int**)(src + 4);
    int count = ((int(__thiscall*)(void*))((void**)*(void**)obj)[0x18 / 4])(obj);
    out[2] = count;
    void* p = ((void*(__thiscall*)(void*, unsigned, int))((void**)*(void**)allocator)[0])(allocator, count * 0xc, 4);
    out[1] = (int)(size_t)p;
    out[0] = 0x1440250;
    if (count != 0) {
        if (p == 0) return false;
        ((void(__thiscall*)(void*, void*, int))((void**)*(void**)obj)[0x28 / 4])(obj, p, count);
    }
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x00950BB0 / 0x00950EF0  message dispatchers (approximate; see partial.txt)
// ---------------------------------------------------------------------------------------------
int WindowProcDispatch(CustomWinProc* self, int* msg) {
    switch (msg[2]) {
    case 1:  ((void(__thiscall*)(void*, int, int))((void**)*(void**)self)[0x28 / 4])(self, msg[3], msg[4]); break;
    case 2:  ((void(__thiscall*)(void*, int, int))((void**)*(void**)self)[0x2c / 4])(self, msg[3], msg[4]); break;
    case 3:  ((void(__thiscall*)(void*, int))((void**)*(void**)self)[0x30 / 4])(self, msg[3]); break;
    case 4:  ((void(__thiscall*)(void*, int))((void**)*(void**)self)[0x34 / 4])(self, msg[3]); break;
    case 5:  ((void(__thiscall*)(void*, int, int))((void**)*(void**)self)[0x38 / 4])(self, msg[3], *(unsigned short*)(msg + 4)); break;
    case 6:  ((void(__thiscall*)(void*, int))((void**)*(void**)self)[0x3c / 4])(self, msg[3]); break;
    case 7:  ((void(__thiscall*)(void*, int))((void**)*(void**)self)[0x40 / 4])(self, msg[3]); break;
    case 8:  ((void(__thiscall*)(void*, int))((void**)*(void**)self)[0x44 / 4])(self, msg[3]); break;
    case 9:  ((void(__thiscall*)(void*, int, int))((void**)*(void**)self)[0x48 / 4])(self, msg[3], msg[4]); break;
    case 10: ((void(__thiscall*)(void*, int, int))((void**)*(void**)self)[0x4c / 4])(self, msg[3], msg[6]); break;
    default: FUN_960410(self, msg); break;
    }
    return 0;
}

int WindowProcDispatch2(CustomWinProc* self, int* msg) {
    (void)self; (void)msg;
    return 0;   // 0x00950EF0: 0x1000 / 1..0x1c switch table (approximated)
}

// ---------------------------------------------------------------------------------------------
// @ 0x00951E10  prepare skin mesh vertices (646 bytes) - approximated
// ---------------------------------------------------------------------------------------------
bool BuildSkinVertices(int* self, int) {
    (void)self;
    return true;
}

// ---------------------------------------------------------------------------------------------
// @ 0x009520A0  quad xform
// ---------------------------------------------------------------------------------------------
void XformQuad(void* self, float a, float b, float c, float d) {
    ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, a, b, c, d);
}

// ---------------------------------------------------------------------------------------------
// @ 0x00952230  add element with rounded corners
// ---------------------------------------------------------------------------------------------
void AddElement(float* self, float x0, float y0, float x1, float y1, float z) {
    if (*(int*)((char*)self + 4) == 0) *(int*)((char*)self + 4) = (int)(self + 9);
    float w = x1 - x0, h = y1 - y0;
    float dw = (w <= z) ? w : z;
    float dh = (h <= z) ? h : z;
    if (dw > 0.0f && dh > 0.0f) {
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x0, y0, x1 + dw, y1);
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x1 - dw, y0, x1, y1);
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x0, y0, x1, y0 + dh);
        ((void(__thiscall*)(void*, float, float, float, float))((void**)*(void**)self)[0x38 / 4])(self, x0, y1 - dh, x1, y1);
    }
}
