// Slice s00eaffc0 : SP::Audio::cPlayerCityMusic::Read -- clears the three per-layer
// note/id vectors and the event list, then runs a cVarListSerializer over itself.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-.
#include "types.h"

// ------------------------------------------------------------------ helpers
void  __cdecl operator_delete(void* p);                                  // 0xf47380
void* __cdecl memcpy_(void* dst, const void* src, unsigned int n);       // 0x11e0744

// SP::cVarListSerializer: ctor at 0x692f90, Serialize (read direction) at 0x693e10.
// Both are __thiscall members (this in ecx), so model them as methods.
struct CVarListSerializer {
    void ctor(void* owner, void* sig, int flags);   // 0x692f90
    bool Serialize(void* stream);                   // 0x693e10
};

// Range-move used by the inlined vector clear: copies the (possibly empty) span
// [first, last) down to dst.  first/last are distinct parameters so cl keeps the
// runtime `last - first` count instead of folding it away.
static void* move_range(void** dst, void** first, void** last)
{
    memcpy_(dst, first, (unsigned int)((char*)last - (char*)first));
    return dst;
}

// The three "layer" vectors are plain 4-byte-element pointer ranges.  clear() is the
// eastl DoClear shape: move the (empty) tail down, then pull mpEnd back onto mpBegin.
struct PtrRange {
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCapacity;   // +0x08
    void clear() {
        void** end = mpEnd;
        void** begin = mpBegin;
        move_range(begin, end, end);
        mpEnd += begin - end;
    }
};

// The event list at +0x1b8 is an eastl intrusive circular list: the sentinel holds
// mpNext/mpPrev pointing at itself when empty.
struct EventNode {
    EventNode* mpNext;   // +0x00
    EventNode* mpPrev;   // +0x04
};
struct EventList {
    EventNode mSentinel; // +0x00  mpNext / mpPrev
    void clear() {
        EventNode* sentinel = &mSentinel;
        EventNode* p = sentinel->mpNext;
        while (p != sentinel) {
            EventNode* next = p->mpNext;
            operator_delete(p);
            p = next;
        }
        sentinel->mpNext = sentinel;
        sentinel->mpPrev = sentinel;
    }
};

struct cPlayerCityMusic {
    char       pad0[0x10c];
    int        m10c;         // +0x10c  "loaded" flag gating Reset
    char       pad1[0x198 - 0x110];
    PtrRange   m198;         // +0x198  layer note range  (begin/end/cap)
    char       pad2[0x1b8 - 0x1a4];
    EventList  m1b8;         // +0x1b8  event list sentinel
    char       pad3[0x1cc - 0x1c0];
    PtrRange   m1cc;         // +0x1cc  layer id range
    char       pad4[0x1e0 - 0x1d8];
    PtrRange   m1e0;         // +0x1e0  layer aux range

    void Reset(char full);                                   // 0xead1a0
    void FUN_00eb05a0();                                     // 0xeb05a0
    bool Read(int stream);                                   // 0xeb0a60
};

// @ 0xeb0a60
bool cPlayerCityMusic::Read(int stream)
{
    if (m10c != 0)
        Reset(0);

    m198.clear();
    m1b8.clear();
    m1cc.clear();
    m1e0.clear();

    char buf[0xa14];
    CVarListSerializer* ser = (CVarListSerializer*)buf;
    ser->ctor(this, (void*)0x15a9198, 0x1a80d26);
    bool ok = ser->Serialize((void*)stream);
    FUN_00eb05a0();
    if (m10c != 0)
        Reset(1);
    return ok;
}

// =================================================================================================
// gold7 worker 19: the remaining 15 VAs of slice s00eaffc0 (00eaffc0 .. 00eb0df0).
// SP::Audio::cPlayerCityMusic melody/note generator plus the eastl container helpers it uses
// (ring_buffer<cResourceCityMusic>, vector<cResourceCityMusic>, vector<bool>).
//
// No exact PDB match (a few caller-scored candidates only); the class layout is taken from the
// disassembly byte offsets through the local stub type below and helpers are named by role.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// -------------------------------------------------------------------------------------------------
#pragma warning(disable : 4100)

typedef unsigned int   u32;
typedef unsigned char  u8;
typedef unsigned short u16;
typedef          int   s32;

// ---- retail callees (declared with the ABI observed at the call sites) --------------------------
void  __fastcall FUN_00eae540(void* self, int, void* src);                                   // 0xeae540
void  __fastcall FUN_00eaeef0(void* self, int, void* first, void* last, void* owner);        // 0xeaeef0
void  __fastcall FUN_00eaefa0(void* self, int, void* a, void* b, void* c, void* d);          // 0xeaefa0
void* __cdecl    FUN_00eaf410(void* first, void* last, void* dest);                          // 0xeaf410
void  __fastcall FUN_00eaf510(void* self, int, void* out);                                   // 0xeaf510 AddNote
void  __fastcall FUN_00eae610(void* self, int, u32 idx);                                     // 0xeae610 RemoveNote
void  __fastcall FUN_00ead1a0(void* self, int, u8 flag);                                     // 0xead1a0 Reset
void  __fastcall FUN_00eb0230(void* self, int, u32 n);                                       // 0xeb0230
void  __fastcall FUN_00eb1460(void* self, int, u32 count, void* tmp);                        // 0xeb1460
void  __fastcall FUN_00eb1d70(void* self);                                                   // 0xeb1d70 cResourceCityMusic ctor
void  __fastcall FUN_00ead6a0(void* self);                                                   // 0xead6a0 cResourceCityMusic dtor
void  __fastcall FUN_00ead660(void* self);                                                   // 0xead660 cResourceCityMusic vector dtor
void  __fastcall FUN_00b93c60(void* out, int, u32 n, void* allocator);                       // 0xb93c60
u32   __fastcall FUN_00a68fb0(void* self, int, u32 n);                                       // 0xa68fb0 RandomUint32Uniform
u32   __cdecl    FUN_005e8ec0(void* rng, u32 count, u32 hi);                                 // 0x5e8ec0 WeightedChoice
void* __cdecl    FUN_00f473a0(u32 size, const char* name, u32 a, u32 b, const char* alloc, u32 line); // operator new
void  __cdecl    FUN_00f47380(void* p);                                                      // operator delete
void  __fastcall FUN_00eadee0(void* self, int, void* first, void* last, void* owner);        // 0xeadee0 cList assign
void  __cdecl    FUN_00da1e70(void* first, void* last, void* owner);                         // 0xda1e70
void* __fastcall FUN_00973d10(void* head, int, void* a, void* b);                            // 0x973d10 ListErase
void  __fastcall FUN_00eadab0(void* self, int, u32 count, void* tmp);                        // 0xeadab0
void* __cdecl    FUN_0067dcc0(void);                                                         // 0x67dcc0 MessageServer
void  __cdecl    FUN_00eaf310(void* a, void* b, void* c, void* d, void* e);                  // 0xeaf310
void  __cdecl    FUN_00eaf350(void* first, void* last, void* value);                         // 0xeaf350 fill
void* __cdecl    FUN_00eaf3d0(void* first, void* last, void* dest);                          // 0xeaf3d0
void  __cdecl    FUN_00eacfb0(void* first, void* last, void* dest);                          // 0xeacfb0
void  __cdecl    FUN_00eaf490(void* first, void* last, void* dest);                          // 0xeaf490
void  __cdecl    FUN_00eaff90(void* dest, u32 count, void* value);                           // 0xeaff90 fill
void  __fastcall FUN_00eaf190(void* self, int, void* src);                                   // 0xeaf190 cResourceCityMusic copy ctor

// ---- this slice --------------------------------------------------------------------------------
void* __cdecl    FUN_00eaffc0(void* cont, char* cur, void* cont2, char* last, char* dest);
void  __cdecl    FUN_00eb0050(void** out, void* sCont, char* sCur, void* sCont2, char* sLast, void* dCont, char* dCur);
void  __fastcall FUN_00eb0120(void* self);
void  __fastcall FUN_00eb0290(void* self, int, u32 n, u32* value);
u8    __fastcall FUN_00eb0390(void* self, int, void* out);
void  __fastcall FUN_00eb0460(void* self);
void  __fastcall FUN_00eb05a0(void* self);
void* __fastcall FUN_00eb0810(void* vec, int, char* first, char* last);
void  __fastcall FUN_00eb0870(void* vec, int, void* pos, u32 count, void* value);
u8    __fastcall FUN_00eb0b70(void* self, int, void* in);
void  __fastcall FUN_00eb0c30(void* self);
void  __fastcall FUN_00eb0c70(void* self);
void  __fastcall FUN_00eb0cb0(void* self, int, void* out, void* dCont, char* dCur, void* sCont, char* sCur);
void  __fastcall FUN_00eb0d60(void* vec, int, u32 n);
void  __fastcall FUN_00eb0df0(void* self, int, u32 n);

// ---- local stub layout for SP::Audio::cPlayerCityMusic (retail byte offsets) ---------------------
struct CityMusic
{
    u8     pad_000[0x10];
    u32    mNumAmbiences;    // 0x10  bound passed to RandomUint32Uniform
    u32    mNumRhythms;      // 0x14
    u32    mNumInstruments;  // 0x18
    u32    mNumLayers;       // 0x1c
    u32    mMinNotes;        // 0x20
    u32    mMaxNotes;        // 0x24
    u32    mWeightHi;        // 0x28
    u8     pad_02c[0x54 - 0x2c];
    u32*   mVec54Begin;      // 0x54
    u32*   mVec54End;        // 0x58
    u8     pad_05c[0x68 - 0x5c];
    u32    mDegreeBase;      // 0x68
    u8     pad_06c[0x74 - 0x6c];
    u32*   mDegreeTable;     // 0x74  degree lookup (7 entries)
    u8     pad_078[0x94 - 0x78];
    void** mppSuggestions;   // 0x94  array indexed by the previous note's degree
    u8     pad_098[0x104 - 0x98];
    u8     mRng[0xc];        // 0x104 RandomLinearCongruential (0x104..0x10f)
    u32    mNumActive;       // 0x110
    u32*   mActiveBegin;     // 0x114
    u8     pad_118[0x128 - 0x118];
    u32*   mVecABegin;       // 0x128
    u32*   mVecAEnd;         // 0x12c
    u8     pad_130[0x13c - 0x130];
    u32*   mVecBBegin;       // 0x13c
    u32*   mVecBEnd;         // 0x140
    u8     pad_144[0x150 - 0x144];
    float  mTotalDuration;   // 0x150
    u32    mSomeValue;       // 0x154
    u8     pad_158[0x198 - 0x158];
    u32*   mVecCBegin;       // 0x198
    u32*   mVecCEnd;         // 0x19c
    u8     pad_1a0[0x1b8 - 0x1a0];
    void*  mListHead;        // 0x1b8  list sentinel: [0]=prev, [1]=next
    void*  mListTail;        // 0x1bc
    u8     pad_1c0[0x1c4 - 0x1c0];
    u32    mRandomA;         // 0x1c4
    u32    mRandomB;         // 0x1c8
    u32*   mVecDBegin;       // 0x1cc
    u32*   mVecDEnd;         // 0x1d0
    u8     pad_1d4[0x1e0 - 0x1d4];
    u32*   mVecEBegin;       // 0x1e0
    u32*   mVecEEnd;         // 0x1e4
};

// eastl vector<bool> clear(): move the (empty) tail down, then pull mpEnd back onto mpBegin.
static void ClearBoolVec(void** pBegin, void** pEnd)
{
    char* begin = (char*)*pBegin;
    char* end   = (char*)*pEnd;
    memcpy_(begin, end, 0);
    s32 d = (s32)((end - begin) >> 2);
    *pEnd = end + (-d) * 4;
}

// @ 0x00eaffc0
void* __cdecl FUN_00eaffc0(void* cont, char* cur, void* cont2, char* last, char* dest)
{
    if (cur == last)
        return dest;
    do
    {
        *(u32*)(dest + 8)    = *(u32*)(cur + 8);
        *(u32*)(dest + 0xc)  = *(u32*)(cur + 0xc);
        *(u32*)(dest + 0x10) = *(u32*)(cur + 0x10);
        *(u32*)(dest + 0x14) = *(u32*)(cur + 0x14);
        *(u32*)(dest + 0x18) = *(u32*)(cur + 0x18);
        FUN_00eae540(dest + 0x1c, 0, cur + 0x1c);
        FUN_00eae540(dest + 0x30, 0, cur + 0x30);
        FUN_00eae540(dest + 0x44, 0, cur + 0x44);
        FUN_00eae540(dest + 0x58, 0, cur + 0x58);
        cur  += 0x6c;
        dest += 0x6c;
        if (cur == *(char**)((char*)cont + 4))
            cur = *(char**)cont;
    } while (cur != last);
    return dest;
}

// @ 0x00eb0050
void __cdecl FUN_00eb0050(void** out, void* sCont, char* sCur, void* sCont2, char* sLast, void* dCont, char* dCur)
{
    if (sCur != sLast)
    {
        do
        {
            *(u32*)(dCur + 8)    = *(u32*)(sCur + 8);
            *(u32*)(dCur + 0xc)  = *(u32*)(sCur + 0xc);
            *(u32*)(dCur + 0x10) = *(u32*)(sCur + 0x10);
            *(u32*)(dCur + 0x14) = *(u32*)(sCur + 0x14);
            *(u32*)(dCur + 0x18) = *(u32*)(sCur + 0x18);
            FUN_00eae540(dCur + 0x1c, 0, sCur + 0x1c);
            FUN_00eae540(dCur + 0x30, 0, sCur + 0x30);
            FUN_00eae540(dCur + 0x44, 0, sCur + 0x44);
            FUN_00eae540(dCur + 0x58, 0, sCur + 0x58);
            dCur += 0x6c;
            if (dCur == *(char**)((char*)dCont + 4))
                dCur = *(char**)dCont;
            sCur += 0x6c;
            if (sCur == *(char**)((char*)sCont + 4))
                sCur = *(char**)sCont;
        } while (sCur != sLast);
    }
    out[1] = dCur;
    out[0] = dCont;
}

// @ 0x00eb0120
void __fastcall FUN_00eb0120(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    u32 choice = FUN_005e8ec0(self->mRng, (self->mMaxNotes - self->mMinNotes) + 1, self->mWeightHi);
    u32 n      = choice + self->mMinNotes;
    self->mSomeValue = FUN_00a68fb0(self->mRng, 0, (u32)(self->mVec54End - self->mVec54Begin));
    ClearBoolVec((void**)&self->mVecDBegin, (void**)&self->mVecDEnd);
    ClearBoolVec((void**)&self->mVecBBegin, (void**)&self->mVecBEnd);
    ClearBoolVec((void**)&self->mVecEBegin, (void**)&self->mVecEEnd);
    ClearBoolVec((void**)&self->mVecABegin, (void**)&self->mVecAEnd);
    self->mTotalDuration = 0.0f;
    u32 local[3];
    for (u32 k = n; k != 0; --k)
        FUN_00eaf510(self, 0, local);
}

// @ 0x00eb0290
void __fastcall FUN_00eb0290(void* self_, int, u32 n, u32* value)
{
    u32** self = (u32**)self_;
    u32*  begin = self[0];
    if ((u32)(self[2] - begin) >> 2 < n)
    {
        u32 tmp[3];
        FUN_00b93c60(tmp, 0, n, (char*)self_ + 0xc);
        u32 fill = *value;
        u32* nb  = (u32*)tmp[0];
        for (u32 k = n; k != 0; --k)
            *nb++ = fill;
        u32* old = self[0];
        self[0] = (u32*)tmp[0];
        self[1] = (u32*)tmp[0] + n;
        self[2] = (u32*)tmp[2];
        if (old)
            FUN_00f47380(old);
        return;
    }
    u32* end = self[1];
    if ((u32)((char*)end - (char*)begin) >> 2 < n)
    {
        u32 fill = *value;
        for (u32* p = begin; p != end; ++p)
            *p = fill;
        u32 extra = n - (u32)(self[1] - self[0]);
        u32* e = self[1];
        for (u32 k = extra; k != 0; --k)
            *e++ = fill;
        self[1] = self[1] + (n - (u32)(self[1] - self[0]));
        return;
    }
    u32 fill = *value;
    for (u32 k = n; k != 0; --k)
        *begin++ = fill;
    u32* _Src = self[1];
    u32* _Dst = self[0] + n;
    memcpy_(_Dst, _Src, 0);
    s32 delta = -((s32)((char*)_Src - (char*)_Dst) >> 2) * 4;
    self[1] = (u32*)((char*)self[1] + delta);
}

// @ 0x00eb0390
u8 __fastcall FUN_00eb0390(void* self_, int, void* out_)
{
    CityMusic* self = (CityMusic*)self_;
    char*      out  = (char*)out_;
    *(u32*)(out + 0x14) = self->mRandomA;
    *(u32*)(out + 0x18) = self->mRandomB;
    FUN_00eaeef0(out + 0x1c, 0, self->mVecDBegin, self->mVecDEnd, out);
    FUN_00eaeef0(out + 0x30, 0, self->mVecEBegin, self->mVecEEnd, out);
    ClearBoolVec((void**)(out + 0x44), (void**)(out + 0x48));
    char* head  = (char*)self + 0x1b8;
    void* head0 = *(void**)head;
    FUN_00eaefa0(out + 0x44, 0, out + 0x44, head0, head, out);
    FUN_00eaeef0(out + 0x58, 0, self->mVecCBegin, self->mVecCEnd, out);
    return 1;
}

// @ 0x00eb0460
void __fastcall FUN_00eb0460(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    FUN_00ead1a0(self, 0, 0);
    char* head = (char*)self + 0x1b8;
    for (char* p = *(char**)head; p != head; )
    {
        char* nxt = *(char**)p;
        FUN_00f47380(p);
        p = nxt;
    }
    *(char**)head = head;
    *(char**)(head + 4) = head;
    u32 tmp = 0;
    FUN_00eb1460(&self->mActiveBegin, 0, self->mNumLayers, &tmp);
    self->mNumActive = 0;
    for (u32 i = 0; i < self->mNumLayers; ++i)
    {
        u32 v;
        if (i == 0)
            v = FUN_00a68fb0(self->mRng, 0, self->mNumAmbiences) + 1;
        else
            v = FUN_00a68fb0(self->mRng, 0, self->mNumAmbiences + 1);
        if (v != 0)
        {
            char* e = *(char**)head;
            while (e != head && *(u32*)(e + 8) != v)
                e = *(char**)e;
            if (e == head)
            {
                self->mActiveBegin[i] = v;
                char* node = (char*)FUN_00f473a0(0xc, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
                if (node + 8)
                    *(u32*)(node + 8) = v;
                *(void**)node = head;
                *(void**)(node + 4) = *(void**)(head + 4);
                *(void**)(*(void**)(head + 4)) = node;
                *(void**)(head + 4) = node;
                ++self->mNumActive;
            }
            else
                self->mActiveBegin[i] = 0;
        }
        else
            self->mActiveBegin[i] = 0;
    }
    self->mRandomA = FUN_00a68fb0(self->mRng, 0, self->mNumRhythms) + 1;
    self->mRandomB = FUN_00a68fb0(self->mRng, 0, self->mNumInstruments) + 1;
    FUN_00eb0120(self);
    FUN_00ead1a0(self, 0, 1);
}

// @ 0x00eb0810
void* __fastcall FUN_00eb0810(void* vec, int, char* first, char* last)
{
    char* end    = *(char**)((char*)vec + 4);
    char* newEnd = (char*)FUN_00eaf410(last, end, first);
    for (char* p = newEnd; p < end; p += 0x6c)
        (*(void (__thiscall**)(char*, int))(*(char**)p + 8))(p, 0);
    s32 delta = (s32)((first - last) / 0x6c) * 0x6c;
    *(char**)((char*)vec + 4) = end + delta;
    return first;
}

// @ 0x00eb0b70
u8 __fastcall FUN_00eb0b70(void* self_, int, void* in_)
{
    CityMusic* self = (CityMusic*)self_;
    char*      in   = (char*)in_;
    FUN_00ead1a0(self, 0, 0);
    self->mRandomA = *(u32*)(in + 0x14);
    self->mRandomB = *(u32*)(in + 0x18);
    FUN_00eaeef0((char*)self + 0x1cc, 0, *(void**)(in + 0x1c), *(void**)(in + 0x20), in);
    FUN_00eaeef0((char*)self + 0x1e0, 0, *(void**)(in + 0x30), *(void**)(in + 0x34), in);
    FUN_00eadee0((char*)self + 0x1b8, 0, *(void**)(in + 0x44), *(void**)(in + 0x48), in);
    if ((((*(u32*)(in + 0x5c) - *(u32*)(in + 0x58)) ^
          (*(u32*)((char*)self + 0x19c) - *(u32*)((char*)self + 0x198))) & 0xfffffffcU) == 0)
        FUN_00da1e70(*(void**)(in + 0x58), *(void**)(in + 0x5c), in);
    FUN_00eb05a0(self);
    FUN_00ead1a0(self, 0, 1);
    return 1;
}

// @ 0x00eb0c30
void __fastcall FUN_00eb0c30(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    if (*(u32*)((char*)self + 0xec) == *(u32*)((char*)self + 0xfc))
        return;
    u32* p = *(u32**)((char*)self + 0xf8);
    if (*(u32*)((char*)self + 0xfc) == p[0])
        *(u32*)((char*)self + 0xfc) = p[1];
    *(u32*)((char*)self + 0xfc) -= 0x6c;
    FUN_00eb0b70(self, 0, *(void**)((char*)self + 0xfc));
}

// @ 0x00eb0c70
void __fastcall FUN_00eb0c70(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    if (*(u32*)((char*)self + 0xf0) == *(u32*)((char*)self + 0xfc))
        return;
    u32* p = *(u32**)((char*)self + 0xf8);
    *(u32*)((char*)self + 0xfc) += 0x6c;
    if (*(u32*)((char*)self + 0xfc) == p[1])
        *(u32*)((char*)self + 0xfc) = p[0];
    FUN_00eb0b70(self, 0, *(void**)((char*)self + 0xfc));
}

// @ 0x00eb0cb0
void __fastcall FUN_00eb0cb0(void* self_, int, void** out, void* dCont, char* dCur, void* sCont, char* sCur)
{
    u32** self = (u32**)self_;
    u32   count = 0;
    if (dCur != sCur)
    {
        char* p = dCur;
        do
        {
            p += 0x6c;
            ++count;
            if (p == *(char**)((char*)dCont + 4))
                p = *(char**)dCont;
        } while (p != sCur);
    }
    char local[8];
    FUN_00eb0050((void**)local, sCont, sCur, self, (char*)self[6], dCont, dCur);
    if (count != 0)
    {
        char* p = (char*)self[6];
        u32   n = (u32)self[7];
        do
        {
            --count;
            if (p == (char*)self[0])
                p = (char*)self[1];
            p -= 0x6c;
            --n;
        } while (count != 0);
        self[6] = (u32*)p;
        self[7] = (u32*)n;
    }
    out[0] = dCont;
    out[1] = dCur;
}

// @ 0x00eb0d60
void __fastcall FUN_00eb0d60(void* vec_, int, u32 n)
{
    u32** vec   = (u32**)vec_;
    char* begin = (char*)vec[0];
    char* end   = (char*)vec[1];
    if (n > (u32)((end - begin) / 0x6c))
    {
        char local[0x6c];
        FUN_00eb1d70(local);
        u32 size = (u32)(((char*)vec[1] - (char*)vec[0]) / 0x6c);
        FUN_00eb0870(vec, 0, (char*)vec[1], n - size, local);
        FUN_00ead6a0(local);
        return;
    }
    FUN_00eb0810(vec, 0, begin + n * 0x6c, end);
}

// @ 0x00eb0df0
void __fastcall FUN_00eb0df0(void* self_, int, u32 n)
{
    u32** self = (u32**)self_;
    u32   cap  = (u32)(((char*)self[1] - (char*)self[0]) / 0x6c);
    if (cap - 1 < n)
    {
        u32* local[3] = {0, 0, 0};
        FUN_00eb0d60(local, 0, n + 1);
        FUN_00eaffc0(self, (char*)self[5], self, (char*)self[6], (char*)local[0]);
        u32* n0 = local[0];
        u32* n1 = local[1];
        u32* n2 = local[2];
        u32* o0 = self[0];
        u32* o1 = self[1];
        u32* o2 = self[2];
        self[0] = n0;
        self[1] = n1;
        self[2] = n2;
        self[5] = self[0];
        self[6] = (u32*)((char*)self[0] + (u32)self[7] * 0x6c);
        local[0] = o0;
        local[1] = o1;
        local[2] = o2;
        FUN_00ead660(local);
    }
}

// @ 0x00eb0870
void __fastcall FUN_00eb0870(void* vec_, int, char* pos, u32 count, void* value)
{
    u32** vec   = (u32**)vec_;
    char* begin = (char*)vec[0];
    char* end   = (char*)vec[1];
    char* cap   = (char*)vec[2];
    if (count > (u32)((cap - end) / 0x6c))
    {
        u32   size   = (u32)((end - begin) / 0x6c);
        u32   newCap = size * 2;
        if (size == 0)
            newCap = 1;
        u32 need = size + count;
        if (need < newCap)
            need = newCap;
        char* mem;
        if (need == 0)
            mem = 0;
        else
            mem = (char*)FUN_00f473a0(need * 0x6c, "Simulator", 0, 0, (const char*)0x13ebb38, 0xd1);
        char* a = (char*)FUN_00eaf3d0(begin, pos, mem);
        FUN_00eacfb0(begin, pos, mem);
        FUN_00eaff90(a, count, value);
        a += count * 0x6c;
        char* b = (char*)FUN_00eaf3d0(pos, end, a);
        FUN_00eacfb0(pos, end, a);
        if (begin)
            FUN_00f47380(begin);
        vec[0] = (u32*)mem;
        vec[1] = (u32*)b;
        vec[2] = (u32*)(mem + need * 0x6c);
        return;
    }
    if (count == 0)
        return;
    char local[0x6c];
    FUN_00eaf190(local, 0, value);
    u32 avail = (u32)((end - pos) / 0x6c);
    if (count < avail)
    {
        char  scratch = 0;
        char* m       = end - count * 0x6c;
        FUN_00eaf310(&scratch, m, end, end, &scratch);
        vec[1] = (u32*)(end + count * 0x6c);
        FUN_00eaf490(pos, m, end);
        FUN_00eaf350(pos, m, local);
    }
    else
    {
        FUN_00eaff90(end, count - avail, local);
        vec[1] = (u32*)(end + (count - avail) * 0x6c);
        FUN_00eaf310(local, pos, end, vec[1], local);
        vec[1] = (u32*)((char*)vec[1] + avail * 0x6c);
        FUN_00eaf350(pos, end, local);
    }
    FUN_00ead6a0(local);
}

// @ 0x00eb05a0
void __fastcall FUN_00eb05a0(void* self_)
{
    CityMusic* self = (CityMusic*)self_;
    if (self->mRandomA > self->mNumRhythms)
        self->mRandomA = FUN_00a68fb0(self->mRng, 0, self->mNumRhythms) + 1;
    if (self->mRandomB > self->mNumInstruments)
        self->mRandomB = FUN_00a68fb0(self->mRng, 0, self->mNumInstruments) + 1;

    u32*   vecB = (u32*)((char*)self + 0x13c);
    u32*   vecA = (u32*)((char*)self + 0x128);
    float* vecE = (float*)((char*)self + 0x1e0);

    u32 dCount = (u32)(self->mVecDEnd - self->mVecDBegin);
    u32 eCount = (u32)(self->mVecEEnd - self->mVecEBegin);
    if (eCount == dCount && dCount != 0)
    {
        FUN_00eb0230(vecB, 0, dCount);
        FUN_00eb0230(vecA, 0, dCount);
        self->mTotalDuration = 0.0f;
        for (u32 i = 0; i < dCount; ++i)
        {
            u32  rem = (self->mVecDBegin[i] - self->mDegreeBase) % 12;
            s32  idx = -1;
            u32* tbl = self->mDegreeTable;
            for (u32 k = 0; k < 7; ++k)
            {
                if (tbl[k] == rem)
                {
                    idx = (s32)k;
                    break;
                }
            }
            vecB[i] = (u32)idx;
            u32 deg = vecB[i];
            u32 v;
            if (deg == 0xffffffffU)
                v = 2;
            else if (i == 0)
                v = 0;
            else
            {
                u32  prev = vecB[i - 1];
                u32* sug  = (u32*)self->mppSuggestions[prev];
                v = (sug[deg] == 0) ? 1 : 0;
            }
            vecA[i] = v;
            self->mTotalDuration += vecE[i];
        }
        if (dCount < self->mMinNotes)
        {
            u32 tmp[3];
            do
            {
                FUN_00eaf510(self, 0, tmp);
                ++dCount;
            } while (dCount < self->mMinNotes);
        }
        if (dCount > self->mMaxNotes)
        {
            do
            {
                --dCount;
                FUN_00eae610(self, 0, dCount);
            } while (dCount > self->mMaxNotes);
        }
    }
    else
        FUN_00eb0120(self);

    char* sent  = (char*)self + 0x1b8;
    u32   count = 0;
    for (char* p = *(char**)sent; p != sent; p = *(char**)p)
        ++count;
    u32 lim = count;
    if (count > self->mNumLayers)
        lim = self->mNumLayers;
    char* cur    = *(char**)sent;
    u32   walked = 0;
    while (cur != sent && walked < lim)
    {
        cur = *(char**)cur;
        ++walked;
    }
    u32 local = 0;
    if (walked == lim)
        FUN_00973d10(sent, 0, cur, &local);
    else
        FUN_00eadab0(sent, 0, lim - walked, &local);

    FUN_00eb0290((char*)self + 0x114, 0, self->mNumLayers, &local);

    self->mNumActive = 0;
    for (char* p = *(char**)sent; p != sent; )
    {
        u32 val = *(u32*)(p + 8);
        if (val > self->mNumAmbiences)
        {
            char* nxt = *(char**)p;
            char* x   = *(char**)(nxt + 4);
            char* xn  = *(char**)(x + 4);
            char* xp  = *(char**)x;
            *(char**)xn = xp;
            *(char**)(xp + 4) = xn;
            FUN_00f47380(x);
            p = nxt;
        }
        else
        {
            u32 i = self->mNumActive;
            self->mNumActive = i + 1;
            (*(u32**)((char*)self + 0x114))[i] = val;
            p = *(char**)p;
        }
    }
    void* ms = FUN_0067dcc0();
    (*(void (__thiscall**)(void*, u32, void*, int))(*(char**)ms + 0x14))(ms, 0x510b72f, self, 0);
}
