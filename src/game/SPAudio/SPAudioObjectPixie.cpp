// src/game/SPAudio/SPAudioObjectPixie.cpp -- migrated from slice(s) s00a3ec00, s00a3dbd0, s00a3cbb0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioObjectPixie.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>

// ---- items of slice s00a3cbb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(unsigned int, const char*, int, int, int, int);
void* operator new(unsigned int, const char*, int, int, const char*, int);
void operator delete(void*);
void operator delete[](void*);
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
#define kEastlFile \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
void FUN_00a3d5b0(void* p);
int* FUN_00a11310(int* a, int* b, int* c);
void FUN_0061eba0(void);
void FUN_0061ec30(void);
int* FUN_00608310(int* out, int n);
void eastl_string_assign(char* a, char* b);
int* eastl_string_substr(char** out, int pos, int len);
struct TeString {
    void* mpBegin;     // +0x00
    void* mpEnd;       // +0x04
    void* mpCapacity;  // +0x08
    void RangeInitialize(const char* s);   // 0x0057cc10
    ~TeString();                            // external
};
struct TrackVec {
    int* mpBegin;    // +0x00
    int* mpEnd;      // +0x04
    int* mpCapacity; // +0x08
    char padC[8];
    int  m14;        // +0x14
    TeString mStr;   // +0x18
    TrackVec* Ctor(int a, const char* b);         // 0x00a3d630
    void DoInsertValue(int* pos, int* value);     // 0x00a3d6e0
    void Erase(int* a, int* b);                   // 0x011e0744 (eastl vector erase)
    void Dtor();                                  // 0x00a3d690
};
// ---- items of slice s00a3cbb0 end

// ---- items of slice s00a3dbd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) long   __cdecl _wtol(const wchar_t* s);            // 0x013cc4ec
extern "C" __declspec(dllimport) double __cdecl strtod(const char* s, char** end);  // 0x013cc4b0
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
extern wchar_t gEmptyString16[];  // 0x01667bac eastl::gEmptyString16
#pragma intrinsic(wcscmp)
typedef unsigned int u32;
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
void* __cdecl MemCopyRange(void* dst, const void* src, unsigned n);                  // 0x011e0744 (memcpy thunk)
void* __cdecl FUN_00a3d810(void** out, void* first, void* last, void* dst, void* src);  // 0x00a3d810
u32*  __cdecl FUN_00a3f4d0(u32* first, u32* last, u32* dst);                            // 0x00a3f4d0
int   __cdecl FUN_00a3d920(int* str, int* out);                                         // 0x00a3d920
struct VecTItem;
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl gensym(void* out, const void* name);                             // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  __cdecl freebytes(void* p, int n);                                       // 0x00a49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct PdObj;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
 PdObj* __cdecl ObjectError(void);   // 0x008de1a0
}
}
}
}
struct tSymbol { int a; int b; };
struct TeString_s00a3_dbd0 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c  (uninitialised by the copy ctor, as in the original)
    void Assign(char* first, char* last);    // 0x00454cb0
    void RangeInit(int n);                   // 0x00475ab0 (eastl RangeInitialize)
    TeString_s00a3_dbd0() {}
    TeString_s00a3_dbd0(const TeString_s00a3_dbd0& s) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        int n = (int)(s.mpEnd - s.mpBegin);
        RangeInit(n + 1);
        MemCopyRange(mpBegin, s.mpBegin, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~TeString_s00a3_dbd0() throw() {
        char* p = mpBegin;
        if (1 < (int)(mpCapacity - p) && p != 0) operator delete(p);
    }
};
struct WString16 {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
    int      mAlloc;     // +0x0c
    void DeallocateSelf();      // 0x00933960
};
union tAtomValue { int i; float f; void* p; };
struct Atom {           // 0xc
    int        a_type;  // +0x00
    tAtomValue w0;      // +0x04
    tAtomValue w1;      // +0x08
};
struct VecAtom {
    Atom* mpBegin;      // +0x00
    Atom* mpEnd;        // +0x04
    Atom* mpCapacity;   // +0x08
    int   mA1;          // +0x0c
    int   mA2;          // +0x10
    void  DoInsertValue(Atom* pos, const Atom* value);   // 0x00a3d6e0
    Atom* erase(Atom* first, Atom* last);                // 0x009e0480
    void  resize(int n);                                 // 0x00a6f010
    ~VecAtom() throw();                                  // 0x007a41a0
    void push_back(const Atom& value) {
        Atom* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            *e = value;
            return;
        }
        Atom tmp = value;
        DoInsertValue(e, &tmp);
    }
};
struct tItem {          // 0x20 (3 dwords + vector<Atom>)
    u32      a, b, c;
    VecAtom  v;         // +0x0c
};
struct VecTItem {
    tItem* mpBegin;     // +0x00
    tItem* mpEnd;       // +0x04
    tItem* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    tItem* AllocCopy(int n, tItem* first, tItem* last);   // 0x00a3daf0
    void   DestroyItems(tItem* first, tItem* last);       // 0x00bdc770
    VecTItem* AssignItems(const VecTItem* x);             // 0x00a3e130
    void   PushBackDefault();                             // 0x00a3fb00
    VecTItem(const VecTItem& s);                          // 0x00a3db50
    ~VecTItem() throw() {
        DestroyItems(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct PixieSlot {      // 0x28
    VecTItem mItems;    // +0x00
    int      mNumber;   // +0x14
    TeString_s00a3_dbd0 mName;     // +0x18
    PixieSlot(int number, const char* name);              // 0x00a3d630
    PixieSlot(const PixieSlot& src);
};
struct VecPixieSlot {
    PixieSlot* mpBegin;    // +0x00
    PixieSlot* mpEnd;      // +0x04
    PixieSlot* mpCapacity; // +0x08
    int        mA1;        // +0x0c
    int        mA2;        // +0x10
    void DestroyRange(u32* first, u32* last);                        // 0x00a3da70
    void DoInsertValue(PixieSlot* pos, const PixieSlot& value);      // 0x00a3e280
    void push_back(const PixieSlot& value);                          // 0x00a3e440
    ~VecPixieSlot() throw() {
        DestroyRange((u32*)mpBegin, (u32*)mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct Pixie {          // 0x34
    int       mKey0;          // +0x00
    int       mKey1;          // +0x04
    int       mKey2;          // +0x08
    void*     mpObject;       // +0x0c
    TeString_s00a3_dbd0  mResourceName;  // +0x10
    VecPixieSlot mSlots;      // +0x20
    PixieSlot* FindByIndex(int key);   // 0x00a3d430
    PixieSlot* FindByName(int key);    // 0x00a3d480
    bool ReadSlot(struct XmlReader* r);
    bool Read();                       // 0x00a3e930
    ~Pixie() throw() {
        mSlots.~VecPixieSlot();
        mResourceName.~TeString_s00a3_dbd0();
    }
};
struct XmlReader {
    VP VP VP
    virtual bool Read();                    // +0x0c
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP
    const wchar_t* GetAttr(const wchar_t* name);   // 0x00900720
    int            NodeType();                     // 0x00900660
    const wchar_t* Name();                         // 0x00900690
};
struct XmlTextReader : XmlReader {
    char mData[0x78];
    XmlTextReader(int a);              // 0x00900b30
    ~XmlTextReader();                  // 0x00900b70
    void SetSource(void* src);         // 0x00901440
    bool Read();                       // 0x009013e0
};
struct EA::Audio::Eapd::PdObj {
    VP VP                                        // slots 0..1
    virtual void Slot2();                        // +0x08
    VP VP VP                                     // slots 3..5
    virtual void* Slot6(int a);                  // +0x18
    VP VP                                        // slots 7..8
    virtual void Slot9();                        // +0x24
    VP VP VP                                     // slots 10..12
    virtual bool Slot13(void* self, void** out, int a, int b, int c, int d);  // +0x34
    VP VP VP VP VP VP VP VP                       // slots 14..21
    virtual PdObj* Slot22(void* self);           // +0x58
    VP VP VP VP VP VP VP VP                       // slots 23..30
    virtual void Slot31(void* self, void* s);    // +0x7c
};
namespace EA {
void* __cdecl ConvertToString8Impl(void* out, const wchar_t* s, unsigned n);  // 0x0093c440
}
namespace EA {
void* __cdecl ConvertToString8(void* out, const void* s);                     // 0x0093c570
}
// ---- items of slice s00a3dbd0 end

// ---- items of slice s00a3ec00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char DAT_01453a98[];               // 0x01453a98 "EAPd/Pixie"
extern int  spPixieClass;                 // 0x0166eeb8
extern int  DAT_0166eebc, DAT_0166eec0, DAT_0166eec4, DAT_0166eec8;
extern int  DAT_0166eecc, DAT_0166eed0, DAT_0166eed4, DAT_0166eed8;
namespace EA {
namespace Audio {
namespace Eapd {
int   __cdecl pd_new(void* cls);                                                     // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl getbytes(int n, const char* tag);                                      // 0x00a49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   __cdecl outlet_new(void* self, int a, int b);                                  // 0x00a49d30
}
}
}
void* __cdecl ConvertToString16Impl(void* out, const char* s, unsigned int n);       // 0x0093c5a0
struct TeString_s00a3_ec00 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
    void  Assign(char* first, char* last);   // 0x00454cb0
    void  RangeInit(int n);                  // 0x00475ab0 (eastl RangeInitialize)
    TeString_s00a3_ec00(const TeString_s00a3_ec00& s) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        int n = (int)(s.mpEnd - s.mpBegin);
        RangeInit(n + 1);
        MemCopyRange(mpBegin, s.mpBegin, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~TeString_s00a3_ec00() throw() {
        char* p = mpBegin;
        if (1 < (int)(mpCapacity - p) && p != 0) operator delete(p);
    }
};
struct tAtomVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    int   mA1;          // +0x0c
    int   mA2;          // +0x10
    tAtomVec() {}
    tAtomVec(const tAtomVec& s);         // 0x00a3d5b0 (vector<_atom> copy ctor)
    void CopyCtor(const tAtomVec& s);    // 0x00a3d5b0 (vector<_atom> copy ctor)
    void Assign(const tAtomVec& s);      // 0x00a6a6a0 (vector<_atom>::operator=)
};
struct tItem_s00a3_ec00 {          // 0x20 (3 dwords + vector<_atom>)
    u32 a, b, c;
    tAtomVec v;         // +0x0c
};
struct VecTItem_s00a3_ec00 {
    tItem_s00a3_ec00* mpBegin;     // +0x00
    tItem_s00a3_ec00* mpEnd;       // +0x04
    tItem_s00a3_ec00* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    void DestroyItems(tItem_s00a3_ec00* first, tItem_s00a3_ec00* last);        // 0x00bdc770 (destroy range<tItem>)
    void Assign(const VecTItem_s00a3_ec00& s);                      // 0x00a3e130 (vector<tItem>::operator=)
    void DoInsertAtom(tItem_s00a3_ec00* pos, const tItem_s00a3_ec00* value);   // 0x00a3f880
    void PushBackDefault();                              // 0x00a3fb00
    VecTItem_s00a3_ec00(const VecTItem_s00a3_ec00& s);                         // 0x00a3db50
    ~VecTItem_s00a3_ec00() throw() {
        DestroyItems(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct TrackEntry {     // 0x24
    TeString_s00a3_ec00 mName;     // +0x00
    VecTItem_s00a3_ec00 mItems;    // +0x10
    TrackEntry(const TrackEntry& src);   // 0x00a3f5d0
    ~TrackEntry() throw();               // 0x00a3f3a0
};
struct VecTE {
    TrackEntry* mpBegin;    // +0x00
    TrackEntry* mpEnd;      // +0x04
    TrackEntry* mpCapacity; // +0x08
    int         mA1;        // +0x0c
    int         mA2;        // +0x10
    void DestroyRange(TrackEntry* first, TrackEntry* last);   // 0x00a3f520
    VecTE(const VecTE& src);                                  // 0x00a3fa50
    ~VecTE() throw() {
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct Track {          // 0x38
    TeString_s00a3_ec00 mName;     // +0x00
    VecTE    mShufflers;// +0x10
    VecTE    mRythms;   // +0x24
    Track(const Track& src);             // 0x00a3fb90
    ~Track() throw();                    // 0x00a3f770
};
struct VecTrack {
    Track* mpBegin;     // +0x00
    Track* mpEnd;       // +0x04
    Track* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    ~VecTrack() throw() {
        Track* p = mpBegin;
        Track* e = mpEnd;
        for (; p < e; p += 1) p->~Track();
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct Pixie_s00a3_ec00 {          // 0x34
    int       mKey0;          // +0x00
    int       mKey1;          // +0x04
    int       mKey2;          // +0x08
    void*     mpObject;       // +0x0c
    TeString_s00a3_ec00  mResourceName;  // +0x10
    VecTrack  mSlots;         // +0x20
    void Read();              // 0x00a3e930
    ~Pixie_s00a3_ec00() throw();         // 0x00a3fd70
};
struct TeStr16 {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
};
struct PdSys {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 0..19
    VP VP VP VP VP VP VP VP VP VP                                 // 20..29
    virtual char Slot78(void* key, void* name, int a, int b);     // +0x78
};
// ---- items of slice s00a3ec00 end

// @ 0x00a3d630
TrackVec* TrackVec::Ctor(int a, const char* b)
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    m14 = a;
    mStr.mpBegin = 0;
    mStr.mpEnd = 0;
    mStr.mpCapacity = 0;
    mStr.RangeInitialize(b);
    return this;
}

// @ 0x00a3d6e0
void TrackVec::DoInsertValue(int* pos, int* value)
{
    int* v = (int*)this;
    int* end = (int*)v[1];
    if (end != (int*)v[2]) {
        if (pos <= value && value < end) value += 3;
        if (end) {
            end[0] = end[-3];
            end[1] = end[-2];
            end[2] = end[-1];
        }
        int* dst = (int*)v[1];
        int* src = (int*)v[1] - 3;
        if (src != pos) {
            do {
                src -= 3;
                dst -= 3;
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
            } while (src != pos);
        }
        pos[0] = value[0];
        pos[1] = value[1];
        pos[2] = value[2];
        v[1] = (int)((char*)v[1] + 0xc);
        return;
    }
    int n = ((int)end - v[0]) / 0xc;
    int* nd;
    if (n == 0) {
        n = 1;
        nd = (int*)::operator new(n * 0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
    } else {
        n = n * 2;
        if (n == 0) nd = 0;
        else nd = (int*)::operator new(n * 0xc, "EASTL", 0, 0, kEastlFile, 0xd1);
    }
    int* r = (int*)FUN_00a11310((int*)v[0], pos, nd);
    if (r) {
        r[0] = value[0];
        r[1] = value[1];
        r[2] = value[2];
    }
    int ni = (int)FUN_00a11310(pos, (int*)v[1], r + 3);
    if (v[0] != 0 && *(int*)(v[0] - 4) != 0) operator delete[]((void*)v[0]);
    v[0] = (int)nd;
    v[1] = ni;
    v[2] = (int)nd + n * 0xc;
}

// @ 0x00a3d810
int** FUN_00a3d810(int** out, int* first, int* last, int dst, int* src)
{
    *out = (int*)dst;
    for (; first != last; first += 8) {
        int* p = *out;
        if (p) {
            p[0] = first[0];
            p[1] = first[1];
            p[2] = first[2];
            FUN_00a3d5b0(first + 3);
        }
        *out = (int*)((char*)*out + 0x20);
    }
    return out;
}

// @ 0x00a3d8a0
int FUN_00a3d8a0(unsigned* first, unsigned* last, int acc)
{
    if (first != last) {
        do {
            unsigned u = first[6];
            if (1 < (int)(first[8] - u) && u != 0) operator delete[]((void*)u);
            unsigned e = first[1];
            for (unsigned i = *first; i < e; i += 0x20) {
                int j = *(int*)(i + 0xc);
                if (j != 0 && *(int*)(j - 4) != 0) operator delete[]((void*)j);
            }
            unsigned b = *first;
            if (b != 0 && *(int*)(b - 4) != 0) operator delete[]((void*)b);
            first += 10;
            acc += 0x28;
        } while (first != last);
    }
    return acc;
}

// @ 0x00a3d920
int FUN_00a3d920(int* str, int* out)
{
    if (str[1] == *str) return 0;
    FUN_0061eba0();
    FUN_0061ec30();
    char* pcVar1 = (char*)str[1];
    char* pcVar2 = (char*)*str;
    char* pcVar3;
    if (pcVar1 != pcVar2 && (pcVar3 = pcVar2, pcVar2 != pcVar1)) {
        do {
            if (*pcVar3 == ' ') break;
            pcVar3 = pcVar3 + 1;
        } while (pcVar3 != pcVar1);
        int iVar4 = (int)pcVar3 - (int)pcVar2;
        if (pcVar3 != pcVar1 && iVar4 != -1) {
            int local_2c[2];
            int* piVar5 = FUN_00608310(local_2c, iVar4);
            if (piVar5 != out) eastl_string_assign((char*)*piVar5, (char*)piVar5[1]);
            if (1 < local_2c[1] - local_2c[0] && local_2c[0] != 0) operator delete[]((void*)local_2c[0]);
            char* local_1c[2];
            piVar5 = eastl_string_substr(local_1c, iVar4, 0xffffffff);
            if (piVar5 != str) eastl_string_assign((char*)*piVar5, (char*)piVar5[1]);
            if (1 < (int)(local_1c[1] - local_1c[0]) && local_1c[0] != 0) operator delete[](local_1c[0]);
            return 1;
        }
    }
    if (str != out) eastl_string_assign(pcVar2, pcVar1);
    if ((char*)*str != (char*)str[1]) {
        *(char*)*str = 0;
        str[1] = *str;
    }
    return 1;
}

// @ 0x00a3da70
void __stdcall FUN_00a3da70(unsigned* first, unsigned* last)
{
    for (; first < last; first += 10) {
        unsigned u = first[6];
        if (1 < (int)(first[8] - u) && u != 0) operator delete[]((void*)u);
        unsigned e = first[1];
        for (unsigned i = *first; i < e; i += 0x20) {
            int j = *(int*)(i + 0xc);
            if (j != 0 && *(int*)(j - 4) != 0) operator delete[]((void*)j);
        }
        unsigned b = *first;
        if (b != 0 && *(int*)(b - 4) != 0) operator delete[]((void*)b);
    }
}

// @ 0x00a3dfa0
PixieSlot::PixieSlot(const PixieSlot& src)
: mItems(src.mItems), mNumber(src.mNumber), mName(src.mName) {
}

// @ 0x00a3e0d0
void FUN_00a3e0d0(int self)
{
    Pixie* px = *(Pixie**)(self + 0x28);
    px->mSlots.~VecPixieSlot();
    px->mResourceName.~TeString_s00a3_dbd0();
    EA::Audio::Eapd::freebytes(*(void**)(self + 0x28), 0x34);
}

// @ 0x00a3e130
VecTItem* VecTItem::AssignItems(const VecTItem* x)
{
    if (this == x) return this;
    unsigned n = (unsigned)(x->mpEnd - x->mpBegin);
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        tItem* pNewData = AllocCopy((int)n, x->mpBegin, x->mpEnd);
        DestroyItems(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + n;
        mpCapacity = pNewData + n;
        return this;
    }
    if (n <= (unsigned)(mpEnd - mpBegin)) {
        tItem* pNewEnd = (tItem*)FUN_00a3f4d0((u32*)x->mpBegin, (u32*)x->mpEnd, (u32*)mpBegin);
        DestroyItems(pNewEnd, mpEnd);
        mpEnd = mpBegin + n;
        return this;
    }
    tItem* position = x->mpBegin + (mpEnd - mpBegin);
    FUN_00a3f4d0((u32*)x->mpBegin, (u32*)position, (u32*)mpBegin);
    FUN_00a3d810((void**)&x, position, x->mpEnd, mpEnd, (void*)x);
    mpEnd = mpBegin + n;
    return this;
}

// @ 0x00a3e220
PixieSlot* FUN_00a3e220(PixieSlot* first, PixieSlot* last, PixieSlot* dst)
{
    if (last != first) {
        do {
            --last;
            --dst;
            dst->mItems.AssignItems(&last->mItems);
            dst->mNumber = last->mNumber;
            if (&last->mName != &dst->mName)
                dst->mName.Assign(last->mName.mpBegin, last->mName.mpEnd);
        } while (last != first);
    }
    return dst;
}

// @ 0x00a3e4c0
bool Pixie::ReadSlot(XmlReader* r)
{
    const wchar_t* pNum = r->GetAttr(L"number");
    const wchar_t* pName = r->GetAttr(L"name");
    if (!r->Read()) return false;
    int number = (int)_wtol(pNum);
    {
        TeString_s00a3_dbd0 str8;
        EA::ConvertToString8Impl(&str8, pName, 0xffffffff);
        PixieSlot slot(number, str8.mpBegin);
        mSlots.push_back(slot);
    }
    PixieSlot* sl = mSlots.mpEnd - 1;
    for (;;) {
        int type = r->NodeType();
        if (type == 1) {
            if (wcscmp(r->Name(), L"pattr") != 0) return false;
            const wchar_t* pn = r->GetAttr(L"name");
            const wchar_t* pv = r->GetAttr(L"value");
            sl->mItems.PushBackDefault();
            tItem* it = sl->mItems.mpEnd - 1;
            it->a = 2;
            {
                TeString_s00a3_dbd0 sName;
                EA::ConvertToString8Impl(&sName, pn, 0xffffffff);
                tSymbol sym;
                EA::Audio::Eapd::gensym(&sym, sName.mpBegin);
                it->b = sym.a;
                it->c = sym.b;
            }
            Atom zeroAtom;
            zeroAtom.a_type = 0;
            zeroAtom.w0.i = 0;
            zeroAtom.w1.i = 0;
            it->v.push_back(zeroAtom);
            Atom* last = it->v.mpEnd - 1;
            last->a_type = 2;
            last->w0.i = it->b;
            last->w1.i = it->c;
            {
                TeString_s00a3_dbd0 sValue;
                EA::ConvertToString8Impl(&sValue, pv, 0xffffffff);
                TeString_s00a3_dbd0 out16;
                out16.mpBegin = (char*)gEmptyString16;
                out16.mpEnd = (char*)gEmptyString16;
                out16.mpCapacity = (char*)gEmptyString16 + 1;
                while (FUN_00a3d920((int*)&sValue, (int*)&out16)) {
                    it->v.push_back(zeroAtom);
                    Atom* at = it->v.mpEnd - 1;
                    bool numeric = true;
                    for (char* p = out16.mpBegin; *p != 0; ++p) {
                        if ((*p < '0' || *p > '9') && *p != '.') { numeric = false; break; }
                    }
                    if (numeric) {
                        at->a_type = 1;
                        at->w0.f = (float)strtod(out16.mpBegin, 0);
                    } else {
                        at->a_type = 2;
                        tSymbol sym2;
                        EA::Audio::Eapd::gensym(&sym2, out16.mpBegin);
                        at->w0.i = sym2.a;
                        at->w1.i = sym2.b;
                    }
                }
                r->Read();
            }
            continue;
        }
        if (type == 2) {
            if (wcscmp(r->Name(), L"slot") == 0) {
                r->Read();
                return true;
            }
        }
        if (!r->Read()) return false;
    }
}

// @ 0x00a3e930
bool Pixie::Read()
{
    EA::Audio::Eapd::PdObj* node = EA::Audio::Eapd::Debug::ObjectError();
    if (!node) return false;
    WString16 s16;
    s16.mpBegin = gEmptyString16;
    s16.mpEnd = gEmptyString16;
    s16.mpCapacity = (wchar_t*)((char*)gEmptyString16 + 2);
    node->Slot31(this, &s16);
    {
        TeString_s00a3_dbd0 str8;
        TeString_s00a3_dbd0* s = (TeString_s00a3_dbd0*)EA::ConvertToString8(&str8, &s16);
        if (s != &mResourceName) mResourceName.Assign(s->mpBegin, s->mpEnd);
    }
    EA::Audio::Eapd::PdObj* obj = node->Slot22(this);
    if (obj) {
        EA::Audio::Eapd::PdObj* out = 0;
        if (obj->Slot13(this, (void**)&out, 1, 6, 1, 0)) {
            bool ok = false;
            {
                XmlTextReader reader(0);
                reader.SetSource(out->Slot6(0));
                reader.Read();
                if (reader.NodeType() == 1 && wcscmp(reader.Name(), L"pattrstorage") == 0) {
                    reader.Read();
                    ok = true;
                    for (;;) {
                        int type = reader.NodeType();
                        if (type == 1) {
                            if (wcscmp(reader.Name(), L"slot") != 0) { ok = false; break; }
                            if (!ReadSlot(&reader)) { ok = false; break; }
                        } else if (type == 2) {
                            break;
                        } else if (!reader.Read()) {
                            ok = false;
                            break;
                        }
                    }
                }
                out->Slot9();
            }
            if (out) out->Slot2();
            s16.DeallocateSelf();
            return ok;
        }
        if (out) out->Slot2();
    }
    s16.DeallocateSelf();
    return false;
}

// @ 0x00a3ec00
void pixie_use(int self, void* sym, const char* name)
{
    (void)sym;
    PdSys* obj = (PdSys*)EA::Audio::Eapd::Debug::ObjectError();
    if (!obj) return;
    int key[3];
    key[0] = 0; key[1] = 0; key[2] = 0;
    TeStr16 s16;
    s16.mpBegin = 0; s16.mpEnd = 0; s16.mpCapacity = 0;
    void** conv = (void**)ConvertToString16Impl(&s16, name, 0xffffffff);
    char ok = obj->Slot78(key, *conv, 0, 0);
    if ((((int)((char*)s16.mpEnd - (char*)s16.mpBegin)) & ~1) > 2 && s16.mpBegin != 0)
        operator delete(s16.mpBegin);
    if (!ok) return;
    if (key[2] == 0 || key[2] == -1) key[2] = 0x21407ee;
    if (key[1] == 0 || key[1] == -1) key[1] = 0x330a65e;
    Pixie_s00a3_ec00* px = (Pixie_s00a3_ec00*)*(int*)(self + 0x28);
    px->mKey0 = key[0];
    px->mKey1 = key[1];
    px->mKey2 = key[2];
    px->Read();
}

// @ 0x00a3ed00
int pixie_new(void* a, void* b, int argc, void* argv)
{
    (void)a; (void)b;
    int r = EA::Audio::Eapd::pd_new((void*)spPixieClass);
    int* m = (int*)EA::Audio::Eapd::getbytes(0x34, DAT_01453a98);
    *(int**)(r + 0x28) = m;
    if (m) {
        m[0] = 0;
        m[1] = 0;
        m[2] = 0;
        m[3] = r;
        m[4] = (int)gEmptyString16;
        m[5] = (int)gEmptyString16;
        m[6] = (int)(gEmptyString16 + 1);
        m[8] = 0;
        m[9] = 0;
        m[10] = 0;
    } else {
        m = 0;
    }
    *(int**)(r + 0x28) = m;
    int o1 = EA::Audio::Eapd::outlet_new((void*)r, DAT_0166eed4, DAT_0166eed8);
    *(int*)(r + 0x2c) = o1;
    int o2 = EA::Audio::Eapd::outlet_new((void*)r, DAT_0166eebc, DAT_0166eec0);
    *(int*)(r + 0x30) = o2;
    if (argc == 1) {
        int* av = (int*)argv;
        pixie_use(r, *(void**)((char*)av + 4), *(const char**)((char*)av + 8));
    }
    return r;
}
