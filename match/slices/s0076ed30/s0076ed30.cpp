// Slice s0076ed30 (batch w2g3, slice 40).
// SP::cRTTManager (shutdown/erase) + render-target job records and their copy/sort helpers.
// Default flags + /arch:SSE /GS- (SSE: no SSE2 movq in the 0x14-byte key copies).
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
// @ 0x0076f580
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
struct Key20 { int w0, w1, w2, w3, w4; };

// @ 0x0076f640  insertion sort (forward, shifting), key compare passed by function pointer.
void __cdecl InsertionSort20(Key20* first, Key20* last, bool (__cdecl* less)(const Key20*, const Key20*))
{
    if (first != last) {
        for (Key20* i = first + 1; i != last; ++i) {
            Key20 value = *i;
            Key20* j = i;
            while (j != first) {
                Key20* p = j - 1;
                if (!less(&value, p))
                    break;
                *j = *p;
                --j;
            }
            *j = value;
        }
    }
}

// @ 0x0076f700  insertion sort variant (no lower bound; caller guarantees a sentinel).
void __cdecl InsertionSort20b(Key20* first, Key20* last, bool (__cdecl* less)(const Key20*, const Key20*))
{
    for (; first != last; ++first) {
        Key20 value = *first;
        Key20* j;
        Key20* p = first - 1;
        bool c = less(&value, p);
        j = first;
        while (c) {
            *j = *p;
            --p;
            --j;
            c = less(&value, p);
        }
        *j = value;
    }
}

// @ 0x0076f880  sift-up / push-heap helper (EASTL push_heap).
void __cdecl SiftUp20(Key20* first, int topIndex, int holeIndex, Key20 value,
                      bool (__cdecl* less)(const Key20*, const Key20*))
{
    int parent = (holeIndex - 1) >> 1;
    while (holeIndex > topIndex) {
        if (!less(&first[parent], &value))
            break;
        first[holeIndex] = first[parent];
        holeIndex = parent;
        parent = (holeIndex - 1) >> 1;
    }
    first[holeIndex] = value;
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
    void AppendPage(void* rec);                           // thiscall (0x76efd0)
};
struct cRTTManager {
    char      pad[4];
    char      mField04[0xc];  // +0x04
    bool      mInitialized;   // +0x10
    char      pad11[7];
    PageVec   mTexturePages;  // +0x18
    bool Shutdown();          // 0x0076f210
    bool AllocateNewPage(int a, int b, int c, int d, void* rec);   // thiscall (0x76e110)
    bool FindPage(int a, int b, int c, int* out);                  // thiscall (0x76ddb0)
    void CaptureJob(int* out);                                     // thiscall (0x76dee0)
    bool RTTCheatInit();      // 0x0076f050
    void RTTBigJob(int* out, int a3, int a4, int a5, uint32_t flags, int a7, int a8); // 0x0076f280
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
namespace EA { namespace ArgScript {
class cArgumentSpec { public:
    char pad[0x10];
    virtual ~cArgumentSpec();
};
class cCommandBase { public:
    char pad[0xc];
    virtual ~cCommandBase();
};
}}
// The compiler-generated scalar deleting destructor (??_G) at 0x0076ed30: member
// dtor (cArgumentSpec at +0x10) then base dtor (cCommandBase at +0), flag-guarded
// operator delete.
// @ 0x0076ed30
struct cRTTCheat : EA::ArgScript::cCommandBase {
    uint32_t pad04[3];                      // +0x04
    EA::ArgScript::cArgumentSpec mParser;   // +0x10
    virtual ~cRTTCheat() {}
};
void ForceDel(cRTTCheat* p) { delete p; }
void ForceDel2() { cRTTCheat* p = new cRTTCheat; delete p; }

// ------------------------------------------------------------------ the 0x3c page/job record
struct FloatVecRef  { void operator=(const void* o); };          // 0x0050d4e0
struct ImageRef     { void GetImageResource(const void* o); };   // 0x00576650
struct BigRec3c {
    void  CopyFrom(BigRec3c* src);        // 0x0076e750  thiscall(1)
    void  Assign(const BigRec3c* src);    // 0x0076e4b0  thiscall(1)
    char  pad00[0x14];
    FloatVecRef vec;                      // +0x14
    char  pad18[0x10];
    int   f28, f2c, f30, f34;             // +0x28
    ImageRef ref;                         // +0x38
};
BigRec3c* __cdecl CopyBigRecRange(BigRec3c* first, BigRec3c* last, BigRec3c* out);     // 0x0076e840
BigRec3c* __cdecl CopyBigRecRangeBack(BigRec3c* first, BigRec3c* last, BigRec3c* out); // 0x0076e9b0
void*     __cdecl DestroyRecRange(BigRec3c* first, BigRec3c* last, BigRec3c* out);     // 0x0076e320

static const char* const kAllocH =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

// @ 0x0076edf0  insert one 0x3c record at `position` (self = BigVec at +0).
struct BigVec { BigRec3c* mBegin; BigRec3c* mEnd; BigRec3c* mCap; void Insert(BigRec3c* position, BigRec3c* value); };
void BigVec::Insert(BigRec3c* position, BigRec3c* value)
{
    BigRec3c** v = (BigRec3c**)this;
    BigRec3c* end = v[1];
    if (end != v[2]) {
        if (position <= value && value < end)
            value = (BigRec3c*)((char*)value + 0x3c);
        if (end)
            end->CopyFrom(end - 1);
        CopyBigRecRangeBack(position, end - 1, end);
        position->Assign(value);
        position->vec = &value->vec;
        position->f28 = value->f28;
        position->f2c = value->f2c;
        position->f30 = value->f30;
        position->f34 = value->f34;
        position->ref.GetImageResource(&value->ref);
        v[1] = end + 1;
        return;
    }
    int count = (int)(end - v[0]);
    int newCap;
    BigRec3c* pNew;
    if (count == 0) {
        newCap = 1;
    } else {
        newCap = count * 2;
        if (newCap == 0) { pNew = 0; goto allocdone; }
    }
    pNew = (BigRec3c*)EASTL_allocator_allocate(newCap * 0x3c, "Graphics", 0, 0, kAllocH, 0xd1);
allocdone:
    {
        BigRec3c* first = v[0];
        BigRec3c* mid = CopyBigRecRange(first, position, pNew);
        DestroyRecRange(first, position, pNew);
        if (mid)
            mid->CopyFrom(value);
        BigRec3c* last = v[1];
        BigRec3c* newEnd = CopyBigRecRange(position, last, mid + 1);
        DestroyRecRange(position, last, mid + 1);
        if (v[0] && *(int*)((char*)v[0] - 4) != 0)
            EASTL_allocator_deallocate(v[0]);
        v[1] = newEnd;
        v[0] = pNew;
        v[2] = (BigRec3c*)((char*)pNew + newCap * 0x3c);
    }
}

// ------------------------------------------------------------------ RTT page record + helpers
struct RTTRec3c {
    void* f00;                                   // +0x00
    int   f04, f08, f0c, f10;
    void* f14;                                   // +0x14
    int   f18, f1c, f20, f24, f28, f2c, f30, f34;
    void* f38;                                   // +0x38
    void Init();      // 0x007b00d0 thiscall(0)
    RTTRec3c() { Init(); }
    ~RTTRec3c();      // 0x0076e2c0 thiscall(0)
};
struct cRTTCheatObj { void Construct(cRTTManager* mgr); };  // 0x0076ea60 thiscall(1)

namespace SP {
class cDirectPropertyList { public:
    virtual bool v0(); virtual bool v1(); virtual bool v2(); virtual bool v3();
    virtual bool v4(); virtual bool v5(); virtual bool v6();
    virtual bool HasProperty(uint32_t prop);      // slot 7 (+0x1c)
    int GetIntProperty(uint32_t prop) const;      // 0x006a2660
};
extern cDirectPropertyList* sAppProperties;       // 0x015fd918
}
struct MsgSrv2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Send(void* base, int id);        // slot 8 (+0x20)
};

// @ 0x0076f050
bool cRTTManager::RTTCheatInit()
{
    if (mInitialized)
        return false;
    mInitialized = true;
    int w = SP::sAppProperties->HasProperty(0x1132287)
                ? SP::sAppProperties->GetIntProperty(0x1132287) : 0x400;
    int n = SP::sAppProperties->HasProperty(0x11322a0)
                ? SP::sAppProperties->GetIntProperty(0x11322a0) : 2;
    for (int i = n; i != 0; --i) {
        RTTRec3c rec;
        AllocateNewPage(-1, w, w, 0x15, &rec);
        mTexturePages.AppendPage(&rec);
    }
    Cheat* cheat = CheatManager();
    if (cheat) {
        void* mem = EASTL_allocator_allocate(0xdc, "Graphics", 0, 0, 0, 0);
        if (mem)
            ((cRTTCheatObj*)mem)->Construct(this);
    }
    MsgSrv* srv = (MsgSrv*)MessageServer();
    if (srv)
        srv->Send(&mField04, 0x3d037f1, 0);
    return true;
}

// ------------------------------------------------------------------ the big render-target job
struct Dd50Obj { virtual void* v0(); virtual void* v1(); virtual void* v2();
                 virtual void* v3(); virtual void* v4(); virtual void* v5(); virtual void* v6();
                 virtual void* v7(); };
extern "C" Dd50Obj* Fn_67dd50();                        // 0x0067dd50
struct W1e70 { int f(void* a, void* b); };              // 0x007b1e70 thiscall(2)

// @ 0x0076f280
void cRTTManager::RTTBigJob(int* out, int a3, int a4, int a5, uint32_t flags, int a7, int a8)
{
    uint32_t f2 = flags & 2;
    uint32_t f4 = flags & 4;
    bool b1 = (flags & 1) != 0;
    PageVec* pages = &mTexturePages;
    int idx = 0;
    int local_4c = -1;
    int cnt = (pages->mBegin == pages->mEnd) ? 0 : (int)(pages->mEnd - pages->mBegin);
    int w = a4;
    BigRec3c* rec = 0;
    if ((f4 != 0 || f2 != 0) && cnt > 0) {
        for (;;) {
            rec = (BigRec3c*)((char*)pages->mBegin + idx * 0x3c);
            w = rec->f28;
            bool ok = (w < 0) || (w == a5) || (a5 == 0x16 && w == 0x15);
            int* pi = (int*)Fn_67dd50()->v7();
            w = a4;
            int matched;
            if ((short)f2 == 0)
                matched = ok && ((short)f4 == 0 || (rec->f2c == 0x400 && rec->f30 == 0x400));
            else
                matched = ok && (rec->f2c == pi[0] && rec->f30 == pi[1]);
            if (matched) {
                local_4c = ((W1e70*)rec)->f((void*)(a3 + a8 * 2), (void*)(a4 + a8 * 2));
                if (local_4c != -1) {
                    rec->f34 += 1;
                    break;
                }
            }
            if (++idx >= cnt)
                break;
        }
        if (local_4c != -1) {
            *out = idx;
            out[1] = local_4c;
            return;
        }
    }
    int idx2;
    int local_50 = -1;
    if ((flags & 8) == 0 && FindPage(a3, w, a5, &w)) {
        int pageIdx = w;
        rec = (BigRec3c*)((char*)pages->mBegin + pageIdx * 0x3c);
        int r = ((W1e70*)rec)->f((void*)a3, (void*)pageIdx);
        local_50 = pageIdx;
        rec->f34 = 1;
        if (b1)
            CaptureJob(&local_50);
        *out = pageIdx;
        out[1] = r;
        return;    }
    idx2 = -1;
    RTTRec3c rec2;
    if (AllocateNewPage(a7, a3, w, a5, &rec2)) {
        local_4c = ((W1e70*)&rec2)->f((void*)a3, (void*)w);
        if (local_4c != -1) {
            idx2 = (int)(pages->mEnd - pages->mBegin);
            local_50 = idx2;
        }
        pages->AppendPage(&rec2);
        if (b1)
            CaptureJob(&local_50);
    }
    *out = idx2;
    out[1] = local_4c;
}

// ------------------------------------------------------------------ cAnimationBaker::BakeToArena
struct BaseResourceDescriptor { int mRef; int mFlags; BaseResourceDescriptor(); ~BaseResourceDescriptor(); };
struct ExportedObj { int mType; int mValue; int pad[4]; };
struct Arena {
    int  GetNumExportedObjects();                       // 0x011e23a0
    void GetExportedObjectByIndex(int i, ExportedObj* out);  // 0x011e28e0
};
// @ 0x0076fb10
int __cdecl BakeToArena(int baker)
{
    if (baker == 0)
        return 0;
    Arena* arena = *(Arena**)(baker + 0x18);
    int n = arena->GetNumExportedObjects();
    for (int i = 0; i < n; ++i) {
        ExportedObj obj = { 0, 0, { 0, 0, 0, 0 } };
        BaseResourceDescriptor arr[4];
        arr[0].mRef = 0;
        arr[0].mFlags = 1;
        arena->GetExportedObjectByIndex(i, &obj);
        if (obj.mType == 0x7000c)
            return obj.mValue;
    }
    return 0;
}

// @ 0x0076fc20  per-element map/alias comparison (union-find style).
struct FC20A { int pad0; int* mMap; int pad8; int mCount; };
struct FC20B { int pad0; int* mMap; };
bool __cdecl HelperFC20(FC20A* a, FC20B* b, int** c)
{
    int i = 0;
    bool result = false;
    if (a->mCount < 1)
        return false;
    int* v = *c;
    do {
        int x = v[i];
        if (x >= 0) {
            int y = a->mMap[i];
            bool eq;
            result = true;
            if (y == -1) {
                eq = (b->mMap[x] == -1);
            } else {
                while (v[y] == -1) {
                    y = a->mMap[y];
                    if (y == -1)
                        return false;
                }
                if (y == -1)
                    return false;
                eq = (v[y] == b->mMap[x]);
            }
            if (!eq)
                return false;
        }
        ++i;
    } while (i < a->mCount);
    return result;
}

// ------------------------------------------------------------------ global registration + matrix setup
extern int A_1630b68;   // 0x01630b68
extern int A_1630b6c;   // 0x01630b6c
extern int A_1630b70;   // 0x01630b70
extern int A_1630b74;   // 0x01630b74
extern int A_1630b78;   // 0x01630b78
extern int A_1630b7c;   // 0x01630b7c
extern int A_1630b80;   // 0x01630b80
void __cdecl AllocB0(int self, int zero, int size);    // 0x011e073e

// @ 0x0076fc90
void __cdecl HelperFC90(int a1, int a2, int a3, int count, int a5, int a6, int a7)
{
    A_1630b68 = a1; A_1630b6c = a3; A_1630b70 = count; A_1630b74 = a2;
    A_1630b7c = a5; A_1630b80 = a6; A_1630b78 = a7;
    if (count <= 0)
        return;
    float m[13];
    m[0] = m[1] = m[2] = 0.0f;
    m[3] = m[4] = m[5] = m[6] = m[7] = m[8] = 1.0f;
    m[9] = m[10] = m[11] = 0.0f;
    m[12] = 1.0f;
    for (int i = count; i != 0; --i) {
        float* elem = (float*)((char*)a5 + 0x1c);
        elem[-7] = m[9]; elem[-6] = m[10]; elem[-5] = m[11]; elem[-4] = m[12];
        elem[-3] = m[0]; elem[-2] = m[1]; elem[-1] = m[2];
        elem[0] = m[3]; elem[1] = m[4]; elem[2] = m[5];
        char* obj = (char*)a6;
        AllocB0((int)obj, 0, 0xb0);
        *(float*)(obj + 0x90) = m[5];
        *(float*)(obj + 0x94) = m[6];
        *(float*)(obj + 0x98) = m[7];
        *obj = 0;
        a5 += 0x30;
        a6 += 0xb0;
    }
}
