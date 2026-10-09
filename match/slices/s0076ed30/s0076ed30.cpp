// Slice s0076ed30 (batch w2g3, slice 40).
// SP::cRTTManager (shutdown/erase) + render-target job records and their copy/sort helpers.
// Default flags + /arch:SSE2.
#include "types.h"
#include <xmmintrin.h>

extern "C" void* EASTL_allocator_allocate(uint32_t n, const char* name, int a, int b, const char* f, int line); // 0x00f473a0
extern "C" void  EASTL_allocator_deallocate(void* p);   // 0x00f47380

// ------------------------------------------------------------------ the 0xa8 job record (float flavour)
// @ 0x0076f7c0  copy constructor (x87 float copies + movaps blocks).
struct __declspec(align(16)) JobRecordF {
    char  c;            // +0x00
    float a, b, d;      // +0x04
    __m128 v[8];        // +0x10
    float x, y, z, w, p, q;  // +0x90
    JobRecordF(const JobRecordF& o);
};
JobRecordF::JobRecordF(const JobRecordF& o)
{
    c = o.c; a = o.a; b = o.b; d = o.d;
    for (int i = 0; i < 8; ++i) v[i] = o.v[i];
    x = o.x; y = o.y; z = o.z; w = o.w; p = o.p; q = o.q;
}

// integer flavour (f580, not byte-exact; kept as complete source)
struct __declspec(align(16)) JobRecordI {
    char c; int a, b, d; __m128 v[8]; int x, y, z, w, p, q;
    JobRecordI(const JobRecordI& o);
};
JobRecordI::JobRecordI(const JobRecordI& o)
{
    c = o.c; a = o.a; b = o.b; d = o.d;
    for (int i = 0; i < 8; ++i) v[i] = o.v[i];
    x = o.x; y = o.y; z = o.z; w = o.w; p = o.p; q = o.q;
}

// ------------------------------------------------------------------ 0x30-byte element copy helpers
struct __declspec(align(16)) Elem30 {
    __m128 v;        // +0x00
    float  f[6];     // +0x10
    Elem30& operator=(const Elem30& o);
};
Elem30& Elem30::operator=(const Elem30& o)
{
    v = o.v;
    for (int i = 0; i < 6; ++i) f[i] = o.f[i];
    return *this;
}

// @ 0x0076f920  uninitialized copy with null-destination check.
void __cdecl CopyElem30(Elem30* first, Elem30* last, Elem30* out)
{
    for (; first != last; ++first, ++out)
        if (out) *out = *first;
}

// @ 0x0076f990  in-place copy.
void __cdecl CopyElem30InPlace(Elem30* first, Elem30* last, Elem30* out)
{
    for (; first != last; ++first, ++out)
        *out = *first;
}

// @ 0x0076fa70  copy backwards.
void __cdecl CopyElem30Back(Elem30* first, Elem30* last, Elem30* out)
{
    while (last != first) {
        --last; --out;
        *out = *last;
    }
}

// ------------------------------------------------------------------ comparator
struct Key29 { int pad0; int a; int b; int c; };
// @ 0x0076f540  lexicographic less-than over three ints at +4/+8/+0xc.
bool __cdecl LessPage(const Key29& x, const Key29& y)
{
    if (x.a < y.a) return true;
    if (x.a > y.a) return false;
    if (x.b < y.b) return true;
    if (x.b > y.b) return false;
    if (x.c < y.c) return true;
    return false;
}

// ------------------------------------------------------------------ insertion sorts over 0x14-byte keys
// @ 0x0076f640  insertion sort (forward, shifting), key compare passed by function pointer.
void __cdecl InsertionSort20(void* base, void* last, bool (__cdecl* less)(const void*, const void*))
{
    (void)base; (void)last; (void)less;   // skeleton (see partial.txt)
}

// @ 0x0076f700  insertion sort variant.
void __cdecl InsertionSort20b(void* base, void* last, bool (__cdecl* less)(const void*, const void*))
{
    (void)base; (void)last; (void)less;   // skeleton (see partial.txt)
}

// @ 0x0076f880  sift-up / push-heap helper.
void __cdecl SiftUp20(void* base, int pos, int count, const void* value,
                      bool (__cdecl* less)(const void*, const void*))
{
    (void)base; (void)pos; (void)count; (void)value; (void)less;   // skeleton (see partial.txt)
}

// ------------------------------------------------------------------ cRTTManager shutdown / erase
struct PageInfo { char pad[0x3c]; };
PageInfo* MoveRange76(PageInfo* first, PageInfo* last, PageInfo* out);   // cdecl (0x76e900)
struct PageVec {
    PageInfo* mBegin;
    PageInfo* mEnd;
    PageInfo* mCap;
    void destroyRange(PageInfo* first, PageInfo* last);   // thiscall (0x76e3b0)
    PageInfo* erase(PageInfo* first, PageInfo* last);     // @ 0x0076ed90
};
struct cRTTManager {
    char      pad[4];
    char      mField04[0xc];  // +0x04
    bool      mInitialized;   // +0x10
    char      pad11[7];
    PageVec   mTexturePages;  // +0x18
    bool Shutdown();          // @ 0x0076f210
};

// @ 0x0076ed90
PageInfo* PageVec::erase(PageInfo* first, PageInfo* last)
{
    PageInfo* newEnd = MoveRange76(last, mEnd, first);
    destroyRange(newEnd, mEnd);
    mEnd -= last - first;
    return first;
}

struct Cheat {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6();
    virtual void RemoveProperty(const char* name);   // slot 7 (+0x1c)
};
struct MsgSrv {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void Send(void* base, int id, int val);  // slot 0xb (+0x2c)
};
extern "C" Cheat* CheatManager();
extern "C" MsgSrv* MessageServer();

// @ 0x0076f210
bool cRTTManager::Shutdown()
{
    if (mInitialized) {
        mInitialized = false;
        mTexturePages.erase(mTexturePages.mBegin, mTexturePages.mEnd);
        Cheat* cheat = CheatManager();
        if (cheat) {
            cheat->RemoveProperty("RTT");
            cheat->RemoveProperty("RTTDump");
        }
        MsgSrv* srv = MessageServer();
        if (srv)
            srv->Send(&mField04, 0x3d037f1, 0xffffd8f1);
        return true;
    }
    return false;
}

// ------------------------------------------------------------------ cRTTCheat
struct ArgScriptOptionParser {
    char pad[0x10];
};
struct cCommandBase {
    char pad[4];
};
struct cRTTCheat {
    char pad[0x10];
    ArgScriptOptionParser mParser;   // +0x10
    void ScalarDelete();
};
void DestroyOptionParser(ArgScriptOptionParser* p);   // 0x00405050
void DestroyCommandBase(cCommandBase* p);             // 0x0083c750

// @ 0x0076ed30
void cRTTCheat::ScalarDelete()
{
    DestroyOptionParser(&mParser);
    DestroyCommandBase((cCommandBase*)this);
    EASTL_allocator_deallocate(this);
}

// ------------------------------------------------------------------ remaining large bodies
// @ 0x0076edf0
void __cdecl BigVecInsert(void* self, unsigned pos, unsigned value)
{
    (void)self; (void)pos; (void)value;   // skeleton: 0x3c-element insert with growth (see partial.txt)
}

// @ 0x0076f050
bool __cdecl RTTCheatInit(void* self)
{
    (void)self;   // skeleton: RTT page allocation + cheat registration (see partial.txt)
    return false;
}

// @ 0x0076f280
void __cdecl RTTBigJob(void* self)
{
    (void)self;   // skeleton: 703-byte job setup (see partial.txt)
}

// @ 0x0076fb10
void __cdecl BakeToArena(void* a, void* b)
{
    (void)a; (void)b;   // skeleton: cAnimationBaker::BakeToArena (see partial.txt)
}

// @ 0x0076fc20
bool __cdecl HelperFC20(int a, int b, int* c)
{
    (void)a; (void)b; (void)c;   // skeleton (see partial.txt)
    return false;
}

// @ 0x0076fc90
void __cdecl HelperFC90(void* a, void* b)
{
    (void)a; (void)b;   // skeleton (see partial.txt)
}
