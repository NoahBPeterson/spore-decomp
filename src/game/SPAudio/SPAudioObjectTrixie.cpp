// src/game/SPAudio/SPAudioObjectTrixie.cpp -- migrated from slice(s) s00a3fde0, s00a3ec00, s00a40cd0 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioObjectTrixie.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/ResponseCurve.h"
#include "EA/Audio/Sound.h"
#include "EA/Variant.h"
#include "SP/Audio/cAudioPreferences.h"

// unnamed retail callees and globals (address in the comment)
extern int s_trixie, DAT_0166ef44, DAT_0166ef24, DAT_0166ef28, DAT_0166ef14, DAT_0166ef18;
extern int DAT_01667bac, DAT_01667bad;
extern int DAT_0166ef2c, DAT_0166ef30, DAT_0166ef0c, DAT_0166ef10, DAT_0166ef1c, DAT_0166ef20;
extern int DAT_0166ef3c, DAT_0166ef40, DAT_0166ef04, DAT_0166ef08, DAT_0166ef34, DAT_0166ef38;
extern char DAT_01409070[], DAT_01453aac[], DAT_01453a40[], DAT_01453aa4[], DAT_01453b84[];
extern char DAT_01453b7c[], DAT_01453b90[];

// ---- items of slice s00a40cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void operator delete(void*);
void operator delete[](void*);
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();
#define VP4  VP VP VP VP
#define VP8  VP4 VP4
#define VP16 VP8 VP8
namespace EA {
int* ConvertToString16(int* out, int str, int len);              // 0x0093c5a0
}
namespace EA {
namespace Audio {
namespace Eapd {
struct Trixie;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void Read(Trixie* self);                                         // 0x00a40a00
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   pd_new(int klass);                                         // 0x00a49390
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int size, const char* tag);                       // 0x00a49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   outlet_new(int self, int a, int b);                        // 0x00a49d30
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int*  gensym(void* out, const char* name);                       // 0x00a675f0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int   class_new(int a, int b, void* ctor, void* dtor, int size, int x, int y, int z);  // 0x00a48ea0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  class_addmethod(int klass, void* fn, int a, int b, int c, int d);                 // 0x00a48a80
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
struct EapdObj {
    VP16 VP8 VP4 VP VP                          // slots 0..29
    virtual char Slot30(void* desc, int str, int a, int b);   // +0x78
};
}
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
namespace Debug {
EapdObj* ObjectError();                          // 0x008de1a0
}
}
}
}
extern int s_trixie, DAT_0166ef44, DAT_0166ef24, DAT_0166ef28, DAT_0166ef14, DAT_0166ef18;
extern int DAT_01667bac, DAT_01667bad;
extern int DAT_0166ef2c, DAT_0166ef30, DAT_0166ef0c, DAT_0166ef10, DAT_0166ef1c, DAT_0166ef20;
extern int DAT_0166ef3c, DAT_0166ef40, DAT_0166ef04, DAT_0166ef08, DAT_0166ef34, DAT_0166ef38;
extern char DAT_01409070[], DAT_01453aac[], DAT_01453a40[], DAT_01453aa4[], DAT_01453b84[];
extern char DAT_01453b7c[], DAT_01453b90[];
void FUN_00a3f090(void);
void FUN_00a3fdc0(void);
// ---- items of slice s00a40cd0 end

// ---- items of slice s00a3ec00 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char kEastlFile[];                 // 0x013ebb38 "...EASTL/allocator.h"
extern char kEastlTag[];                  // 0x013f2150 "EASTL"
extern "C" void* __cdecl MemCopyRange(void* dst, const void* src, unsigned n);  // 0x011e0744 (memcpy thunk)
typedef unsigned int u32;
void* __cdecl EAAllocate(unsigned int n, const char* tag, int a, int b, int file, int line); // 0x00f473a0
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}
void* __cdecl FUN_00a3f660(void** out, void* first, void* last, void* dst, void* src);
void* __cdecl FUN_00bda890(void* dst, void* first, void* last);
struct TeString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
    void  Assign(char* first, char* last);   // 0x00454cb0
    void  RangeInit(int n);                  // 0x00475ab0 (eastl RangeInitialize)
    TeString(const TeString& s) {
        mpBegin = 0; mpEnd = 0; mpCapacity = 0;
        int n = (int)(s.mpEnd - s.mpBegin);
        RangeInit(n + 1);
        MemCopyRange(mpBegin, s.mpBegin, n);
        mpEnd = mpBegin + n;
        *mpEnd = 0;
    }
    ~TeString() throw() {
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
struct tItem {          // 0x20 (3 dwords + vector<_atom>)
    u32 a, b, c;
    tAtomVec v;         // +0x0c
};
struct VecTItem {
    tItem* mpBegin;     // +0x00
    tItem* mpEnd;       // +0x04
    tItem* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    void DestroyItems(tItem* first, tItem* last);        // 0x00bdc770 (destroy range<tItem>)
    void Assign(const VecTItem& s);                      // 0x00a3e130 (vector<tItem>::operator=)
    void DoInsertAtom(tItem* pos, const tItem* value);   // 0x00a3f880
    void PushBackDefault();                              // 0x00a3fb00
    VecTItem(const VecTItem& s);                         // 0x00a3db50
    ~VecTItem() throw() {
        DestroyItems(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct TrackEntry {     // 0x24
    TeString mName;     // +0x00
    VecTItem mItems;    // +0x10
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
    TeString mName;     // +0x00
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
struct Pixie {          // 0x34
    int       mKey0;          // +0x00
    int       mKey1;          // +0x04
    int       mKey2;          // +0x08
    void*     mpObject;       // +0x0c
    TeString  mResourceName;  // +0x10
    VecTrack  mSlots;         // +0x20
    void Read();              // 0x00a3e930
    ~Pixie() throw();         // 0x00a3fd70
};
// ---- items of slice s00a3ec00 end

// ---- items of slice s00a3fde0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char  gEmptyString16[];  // 0x01667bac  eastl gEmptyString16 (shared empty string base)
extern "C" int    wcscmp(const wchar_t*, const wchar_t*);
extern "C" double atof(const char*);
typedef unsigned int size_type;
u32* __cdecl FUN_00a3fcd0(u32* first, u32* last, u32* dst);   // backward range assign, 0x24 stride
u32* __cdecl FUN_00a3fd20(u32* first, u32* last, u32* dst);   // forward  range assign, 0x24 stride
void* __cdecl FUN_00a3f6e0(void* first, void* last, void* dst); // uninit copy, 0x24, returns dst
int   __cdecl FUN_00a3f3f0(u32* first, u32* last, int acc);    // destroy range, 0x24
void* __cdecl FUN_00a3fc40(void* first, void* last, void* dst); // uninit copy, 0x38
int   __cdecl FUN_00a3f840(u32* first, u32* last, int acc);    // destroy range, 0x38
int*  __cdecl gensym(void* out, const char* name);             // 0x00a675f0
void* __cdecl ConvertToString8Impl(void* out, const void* in, unsigned n); // 0x0093c440
void* __cdecl ConvertToString8(void* out, const void* in);     // 0x0093c570
struct RawStr {
    char* b;        // +0x00
    char* e;        // +0x04
    char* c;        // +0x08
    int   a;        // +0x0c
};
struct TeString_s00a3_fde0 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
    void  Assign(char* first, char* last);   // 0x00454cb0 (ret 8)
    TeString_s00a3_fde0& operator=(const TeString_s00a3_fde0& x) {
        if (&x != this) Assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    ~TeString_s00a3_fde0() throw() {
        char* p = mpBegin;
        if (1 < (int)(mpCapacity - p) && p != 0) operator delete(p);
    }
};
struct WString {
    wchar_t* mpBegin;      // +0x00
    wchar_t* mpEnd;        // +0x04
    wchar_t* mpCapacity;   // +0x08
    int      mAlloc;       // +0x0c
    void DeallocateSelf(); // 0x00933960
    ~WString() throw() {
        if (mpBegin != 0 && ((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2)
            operator delete(mpBegin);
    }
};
struct _atom {
    int a_type;             // +0x00
    union {
        float f;            // +0x04
        int   sym[2];       // +0x04,+0x08
    };
};
struct tAtomVec_s00a3_fde0 {
    _atom* mpBegin;     // +0x00
    _atom* mpEnd;       // +0x04
    _atom* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    _atom* back() { return mpEnd - 1; }
    void DoInsertValue(_atom* pos, const _atom* value);   // 0x00a3d6e0
    void PushBackDefault() {
        _atom* e = mpEnd;
        if (e < mpCapacity) {
            mpEnd = e + 1;
            if (e) { e->a_type = 0; e->sym[0] = 0; e->sym[1] = 0; }
            return;
        }
        _atom local;
        local.a_type = 0; local.sym[0] = 0; local.sym[1] = 0;
        DoInsertValue(e, &local);
    }
};
struct tItem_s00a3_fde0 {          // 0x20 (3 dwords + vector<_atom>)
    u32 a, b, c;
    tAtomVec_s00a3_fde0 v;         // +0x0c
};
struct VecTItem_s00a3_fde0 {
    tItem_s00a3_fde0* mpBegin;     // +0x00
    tItem_s00a3_fde0* mpEnd;       // +0x04
    tItem_s00a3_fde0* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    tItem_s00a3_fde0* back() { return mpEnd - 1; }
    void DestroyItems(tItem_s00a3_fde0* first, tItem_s00a3_fde0* last);        // 0x00bdc770
    void Assign(const VecTItem_s00a3_fde0& s);                      // 0x00a3e130
    void DoInsertAtom(tItem_s00a3_fde0* pos, const tItem_s00a3_fde0* value);   // 0x00a3f880
    void PushBackDefault();                              // 0x00a3fb00
    VecTItem_s00a3_fde0() {}
    VecTItem_s00a3_fde0(const VecTItem_s00a3_fde0& s);                         // 0x00a3db50
    ~VecTItem_s00a3_fde0() throw() {
        DestroyItems(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct TrackEntry_s00a3_fde0 {     // 0x24
    TeString_s00a3_fde0 mName;     // +0x00
    VecTItem_s00a3_fde0 mItems;    // +0x10
    TrackEntry_s00a3_fde0() {}
    TrackEntry_s00a3_fde0(const TrackEntry_s00a3_fde0& src);   // 0x00a3f5d0
    ~TrackEntry_s00a3_fde0() throw();               // 0x00a3f3a0
};
struct VecTE_s00a3_fde0 {
    TrackEntry_s00a3_fde0* mpBegin;    // +0x00
    TrackEntry_s00a3_fde0* mpEnd;      // +0x04
    TrackEntry_s00a3_fde0* mpCapacity; // +0x08
    int         mA1;        // +0x0c
    int         mA2;        // +0x10
    TrackEntry_s00a3_fde0* back() { return mpEnd - 1; }
    void DestroyRange(TrackEntry_s00a3_fde0* first, TrackEntry_s00a3_fde0* last);   // 0x00a3f520
    TrackEntry_s00a3_fde0* Allocate(int n, TrackEntry_s00a3_fde0* first, TrackEntry_s00a3_fde0* last); // 0x00a3f7e0
    VecTE_s00a3_fde0() {}
    VecTE_s00a3_fde0& operator=(const VecTE_s00a3_fde0& src);
    void DoInsertValue(TrackEntry_s00a3_fde0* pos, const TrackEntry_s00a3_fde0& value);
    void PushBackDefault();
    VecTE_s00a3_fde0(const VecTE_s00a3_fde0& src);                                  // 0x00a3fa50
    ~VecTE_s00a3_fde0() throw() {
        DestroyRange(mpBegin, mpEnd);  // 0x00a3f520 (VecTE::DestroyRange)
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct Track_s00a3_fde0 {          // 0x38
    TeString_s00a3_fde0 mName;     // +0x00
    VecTE_s00a3_fde0    mShufflers;// +0x10
    VecTE_s00a3_fde0    mRythms;   // +0x24
    Track_s00a3_fde0() {}
    Track_s00a3_fde0(const Track_s00a3_fde0& src);             // 0x00a3fb90
    ~Track_s00a3_fde0() throw();                    // 0x00a3f770
};
struct VecTrack_s00a3_fde0 {
    Track_s00a3_fde0* mpBegin;     // +0x00
    Track_s00a3_fde0* mpEnd;       // +0x04
    Track_s00a3_fde0* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    Track_s00a3_fde0* back() { return mpEnd - 1; }
    void DoInsertValue(Track_s00a3_fde0* pos, const Track_s00a3_fde0& value);
    void PushBackDefault();
    ~VecTrack_s00a3_fde0() throw() {
        Track_s00a3_fde0* p = mpBegin;
        Track_s00a3_fde0* e = mpEnd;
        for (; p < e; p += 1) p->~Track_s00a3_fde0();
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};
struct Handle;
struct XmlReader;
struct Obj {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 0..19
    VP VP                                                          // 20..21
    virtual Handle* M_58(void* owner);                             // +0x58
    VP VP VP VP VP VP VP VP                                        // +0x5c..0x78
    virtual void    M_7c(void* owner, void* name);                 // +0x7c
};
struct Handle {
    VP VP                                                     // +0x00,+0x04
    virtual void  Release();                                  // +0x08
    VP VP VP                                                  // +0x0c..0x14
    virtual void* M_18(int a);                                // +0x18
    VP VP                                                     // +0x1c,0x20
    virtual void  M_24();                                     // +0x24
    VP VP VP                                                  // +0x28..0x30
    virtual bool  Open(void* owner, void** out, int a, int b, int c, int d); // +0x34
};
struct XmlReader {
    VP VP VP                                                  // +0x00..0x08
    virtual bool Next();                                      // +0x0c
    void Ctor(int a);                                         // 0x00900b30
    void Dtor();                                              // 0x00900b70
    int  NodeType();                                          // 0x00900660
    const wchar_t* Name();                                    // 0x00900690
    int  AttrCount();                                         // 0x009006a0
    const wchar_t* AttrName(int i);                           // 0x009006c0
    const wchar_t* AttrValue(int i);                          // 0x009006f0
    const void* GetAttr(const wchar_t* n);                    // 0x00900720
    bool M_9013e0();                                          // 0x009013e0
    void M_901440(void* v);                                   // 0x00901440
};
struct Trixie_s00a3_fde0 {
    int      mKey0;          // +0x00
    int      mKey1;          // +0x04
    int      mKey2;          // +0x08
    void*    mpObject;       // +0x0c
    TeString_s00a3_fde0 mResourceName;  // +0x10
    VecTrack_s00a3_fde0 mTracks;        // +0x20
    bool ReadTrack(XmlReader* r);  // 0x00a404d0 (Trixie::ReadTrack)
    bool Read();  // 0x00a40a00 (Trixie::Read)
};
// ---- items of slice s00a3fde0 end

// @ 0x00a3f300
tItem* FUN_00a3f300(tItem* first, tItem* last, tItem* dst)
{
    if (first != last) {
        do {
            ::new ((void*)dst) tItem(*first);
            first += 1;
            dst += 1;
        } while (first != last);
    }
    return dst;
}

// @ 0x00a3f3a0
TrackEntry::~TrackEntry() throw()
{
}

// @ 0x00a3f3f0
int FUN_00a3f3f0(u32* first, u32* last, int acc)
{
    if (first != last) {
        do {
            u32 e = first[5];
            for (u32 i = first[4]; i < e; i += 0x20) {
                u32 j = *(u32*)(i + 0xc);
                if (j != 0 && *(int*)(j - 4) != 0) operator delete((void*)j);
            }
            u32 b = first[4];
            if (b != 0 && *(int*)(b - 4) != 0) operator delete((void*)b);
            u32 a = first[0];
            if (1 < (int)(first[2] - a) && a != 0) operator delete((void*)a);
            first += 9;
            acc += 0x24;
        } while (first != last);
    }
    return acc;
}

// @ 0x00a3f480
u32* FUN_00a3f480(u32* first, u32* last, u32* dst)
{
    if (last != first) {
        do {
            last -= 8;
            dst -= 8;
            dst[0] = last[0];
            dst[1] = last[1];
            dst[2] = last[2];
            ((tAtomVec*)(dst + 3))->Assign(*(tAtomVec*)(last + 3));
        } while (last != first);
    }
    return dst;
}

// @ 0x00a3f4d0
u32* FUN_00a3f4d0(u32* first, u32* last, u32* dst)
{
    if (first != last) {
        do {
            dst[0] = first[0];
            dst[1] = first[1];
            dst[2] = first[2];
            ((tAtomVec*)(dst + 3))->Assign(*(tAtomVec*)(first + 3));
            first += 8;
            dst += 8;
        } while (first != last);
    }
    return dst;
}

// @ 0x00a3f520
void VecTE::DestroyRange(TrackEntry* first, TrackEntry* last)
{
    for (; first < last; first += 1) {
        tItem* e = first->mItems.mpEnd;
        tItem* it = first->mItems.mpBegin;
        for (; it < e; it += 1) {
            void* j = it->v.mpBegin;
            if (j != 0 && ((int*)j)[-1] != 0) operator delete(j);
        }
        tItem* b = first->mItems.mpBegin;
        if (b != 0 && ((int*)b)[-1] != 0) operator delete(b);
        char* q = first->mName.mpBegin;
        if (1 < (int)(first->mName.mpCapacity - q) && q != 0) operator delete(q);
    }
}

// @ 0x00a3f5d0
TrackEntry::TrackEntry(const TrackEntry& src)
: mName(src.mName), mItems(src.mItems) {
}

// @ 0x00a3f770
Track::~Track() throw()
{
}

// @ 0x00a3f880
void VecTItem::DoInsertAtom(tItem* pos, const tItem* value)
{
    tItem* end = mpEnd;
    if (end != mpCapacity) {
        const char* v = (const char*)value;
        if ((char*)pos <= v && v < (char*)end) v += 0x20;
        if (end) {
            tItem* prev = end - 1;
            end->a = prev->a;
            end->b = prev->b;
            end->c = prev->c;
            end->v.CopyCtor(prev->v);
        }
        FUN_00a3f480((u32*)pos, (u32*)(mpEnd - 1), (u32*)mpEnd);
        tItem* d = pos;
        const tItem* s = (const tItem*)v;
        d->a = s->a;
        d->b = s->b;
        d->c = s->c;
        d->v.Assign(s->v);
        mpEnd = mpEnd + 1;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    tItem* nd;
    if (n == 0) {
        n = 1;
        nd = (tItem*)EAAllocate(n << 5, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    } else {
        n = n * 2;
        if (n == 0) nd = 0;
        else nd = (tItem*)EAAllocate(n << 5, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    }
    tItem* p = mpBegin;
    tItem* endp = FUN_00a3f300(p, pos, nd);
    FUN_00bda890(p, pos, nd);
    if (endp) {
        endp->a = value->a;
        endp->b = value->b;
        endp->c = value->c;
        endp->v.CopyCtor(value->v);
    }
    tItem* save = mpEnd;
    tItem* ni = FUN_00a3f300(pos, save, endp + 1);
    FUN_00bda890(pos, save, endp + 1);
    tItem* ob = mpBegin;
    if (ob != 0 && ((int*)ob)[-1] != 0) operator delete(ob);
    mpBegin = nd;
    mpEnd = ni;
    mpCapacity = (tItem*)((char*)nd + (n << 5));
}

// @ 0x00a3fa50
VecTE::VecTE(const VecTE& src)
{
    int n = (int)(src.mpEnd - src.mpBegin);
    TrackEntry* p = 0;
    if (n != 0)
        p = (TrackEntry*)EAAllocate(n * 0x24, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    mpBegin = p;
    mpEnd = p;
    mpCapacity = (TrackEntry*)((char*)p + n * 0x24);
    TrackEntry* out = 0;
    try {
        FUN_00a3f660((void**)&out, src.mpBegin, src.mpEnd, p, (void*)&src);
    } catch (...) {
        if (p != 0) operator delete(p);
        throw;
    }
    mpEnd = out;
}

// @ 0x00a3fb00
void VecTItem::PushBackDefault()
{
    tItem* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = mpEnd + 1;
        if (e) {
            e->v.mpBegin = 0;
            e->v.mpEnd = 0;
            e->v.mpCapacity = 0;
        }
        return;
    }
    tItem local;
    local.v.mpBegin = 0;
    local.v.mpEnd = 0;
    local.v.mpCapacity = 0;
    DoInsertAtom(e, &local);
    void* lb = local.v.mpBegin;
    if (lb != 0 && ((int*)lb)[-1] != 0) operator delete(lb);
}

// @ 0x00a3fb90
Track::Track(const Track& src)
: mName(src.mName), mShufflers(src.mShufflers), mRythms(src.mRythms) {
}

// @ 0x00a3fcd0
u32* FUN_00a3fcd0(u32* first, u32* last, u32* dst)
{
    if (last != first) {
        do {
            last -= 9;
            dst -= 9;
            if (last != dst)
                ((TeString*)dst)->Assign((char*)last[0], (char*)last[1]);
            ((VecTItem*)(dst + 4))->Assign(*(VecTItem*)(last + 4));
        } while (last != first);
    }
    return dst;
}

// @ 0x00a3fd20
u32* FUN_00a3fd20(u32* first, u32* last, u32* dst)
{
    if (first != last) {
        do {
            if (first != dst)
                ((TeString*)dst)->Assign((char*)first[0], (char*)first[1]);
            ((VecTItem*)(dst + 4))->Assign(*(VecTItem*)(first + 4));
            first += 9;
            dst += 9;
        } while (first != last);
    }
    return dst;
}

// @ 0x00a3fd70
Pixie::~Pixie() throw()
{
}

// @ 0x00a3fde0
void VecTE_s00a3_fde0::DoInsertValue(TrackEntry_s00a3_fde0* pos, const TrackEntry_s00a3_fde0& value)
{
    TrackEntry_s00a3_fde0* end = mpEnd;
    if (end != mpCapacity) {
        const TrackEntry_s00a3_fde0* v = &value;
        if (pos <= v && v < end) v += 1;
        if (end)
            ::new ((void*)end) TrackEntry_s00a3_fde0(*(end - 1));
        FUN_00a3fcd0((u32*)pos, (u32*)(end - 1), (u32*)end);
        if (v != pos)
            pos->mName.Assign((char*)v->mName.mpBegin, (char*)v->mName.mpEnd);
        pos->mItems.Assign(v->mItems);
        mpEnd = end + 1;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    TrackEntry_s00a3_fde0* nd;
    if (n == 0) {
        n = 1;
        nd = (TrackEntry_s00a3_fde0*)EAAllocate(n * 0x24, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    } else {
        n = n * 2;
        if (n == 0) nd = 0;
        else nd = (TrackEntry_s00a3_fde0*)EAAllocate(n * 0x24, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    }
    TrackEntry_s00a3_fde0* oldBegin = mpBegin;
    TrackEntry_s00a3_fde0* endp = (TrackEntry_s00a3_fde0*)FUN_00a3f6e0(oldBegin, pos, nd);
    FUN_00a3f3f0((u32*)oldBegin, (u32*)pos, (int)nd);
    if (endp)
        ::new ((void*)endp) TrackEntry_s00a3_fde0(value);
    TrackEntry_s00a3_fde0* oldEnd = mpEnd;
    TrackEntry_s00a3_fde0* ni = (TrackEntry_s00a3_fde0*)FUN_00a3f6e0(pos, oldEnd, endp + 1);
    FUN_00a3f3f0((u32*)pos, (u32*)oldEnd, (int)(endp + 1));
    if (oldBegin != 0 && ((int*)oldBegin)[-1] != 0) operator delete(oldBegin);
    mpEnd = ni;
    mpBegin = nd;
    mpCapacity = nd + n;
}

// @ 0x00a3ffa0
VecTE_s00a3_fde0& VecTE_s00a3_fde0::operator=(const VecTE_s00a3_fde0& src)
{
    if (&src == this) return *this;
    size_type n = (size_type)(src.mpEnd - src.mpBegin);
    if (n > (size_type)(mpCapacity - mpBegin)) {
        TrackEntry_s00a3_fde0* nd = Allocate((int)n, src.mpBegin, src.mpEnd);
        DestroyRange(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
        mpCapacity = nd + n;
        mpBegin = nd;
        mpEnd = nd + n;
        return *this;
    }
    if (n > (size_type)(mpEnd - mpBegin)) {
        FUN_00a3fd20((u32*)src.mpBegin,
                     (u32*)(src.mpBegin + (size_type)(mpEnd - mpBegin)),
                     (u32*)mpBegin);
        TrackEntry_s00a3_fde0* out;
        FUN_00a3f660((void**)&out,
                     src.mpBegin + (size_type)(mpEnd - mpBegin),
                     src.mpEnd, mpEnd, src.mpEnd);
        mpEnd = mpBegin + n;
        return *this;
    }
    TrackEntry_s00a3_fde0* e = (TrackEntry_s00a3_fde0*)FUN_00a3fd20((u32*)src.mpBegin, (u32*)src.mpEnd, (u32*)mpBegin);
    DestroyRange(e, mpEnd);
    mpEnd = mpBegin + n;
    return *this;
}

// @ 0x00a400f0
void VecTE_s00a3_fde0::PushBackDefault()
{
    TrackEntry_s00a3_fde0* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e) {
            e->mName.mpBegin = gEmptyString16;
            e->mName.mpEnd = gEmptyString16;
            e->mName.mpCapacity = gEmptyString16 + 1;
            e->mItems.mpBegin = 0;
            e->mItems.mpEnd = 0;
            e->mItems.mpCapacity = 0;
        }
        return;
    }
    TrackEntry_s00a3_fde0 local;
    local.mName.mpBegin = gEmptyString16;
    local.mName.mpEnd = gEmptyString16;
    local.mName.mpCapacity = gEmptyString16 + 1;
    local.mItems.mpBegin = 0;
    local.mItems.mpEnd = 0;
    local.mItems.mpCapacity = 0;
    DoInsertValue(e, local);
}

// @ 0x00a401d0
Track_s00a3_fde0* FUN_00a401d0(Track_s00a3_fde0* first, Track_s00a3_fde0* last, Track_s00a3_fde0* dst)
{
    if (last != first) {
        do {
            last -= 1;
            dst -= 1;
            if (last != dst)
                dst->mName.Assign(last->mName.mpBegin, last->mName.mpEnd);
            dst->mShufflers = last->mShufflers;
            dst->mRythms = last->mRythms;
        } while (last != first);
    }
    return dst;
}

// @ 0x00a40230
void VecTrack_s00a3_fde0::DoInsertValue(Track_s00a3_fde0* pos, const Track_s00a3_fde0& value)
{
    Track_s00a3_fde0* end = mpEnd;
    if (end != mpCapacity) {
        const Track_s00a3_fde0* v = &value;
        if (pos <= v && v < end) v += 1;
        if (end)
            ::new ((void*)end) Track_s00a3_fde0(*(end - 1));
        FUN_00a401d0(pos, end - 1, end);
        if (v != pos)
            pos->mName.Assign((char*)v->mName.mpBegin, (char*)v->mName.mpEnd);
        pos->mShufflers = v->mShufflers;
        pos->mRythms = v->mRythms;
        mpEnd = end + 1;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    Track_s00a3_fde0* nd;
    if (n == 0) {
        n = 1;
        nd = (Track_s00a3_fde0*)EAAllocate(n * 0x38, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    } else {
        n = n * 2;
        if (n == 0) nd = 0;
        else nd = (Track_s00a3_fde0*)EAAllocate(n * 0x38, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    }
    Track_s00a3_fde0* oldBegin = mpBegin;
    Track_s00a3_fde0* endp = (Track_s00a3_fde0*)FUN_00a3fc40(oldBegin, pos, nd);
    FUN_00a3f840((u32*)oldBegin, (u32*)pos, (int)nd);
    if (endp)
        ::new ((void*)endp) Track_s00a3_fde0(value);
    Track_s00a3_fde0* oldEnd = mpEnd;
    Track_s00a3_fde0* ni = (Track_s00a3_fde0*)FUN_00a3fc40(pos, oldEnd, endp + 1);
    FUN_00a3f840((u32*)pos, (u32*)oldEnd, (int)(endp + 1));
    if (oldBegin != 0 && ((int*)oldBegin)[-1] != 0) operator delete(oldBegin);
    mpEnd = ni;
    mpBegin = nd;
    mpCapacity = nd + n;
}

// @ 0x00a40410
void VecTrack_s00a3_fde0::PushBackDefault()
{
    Track_s00a3_fde0* e = mpEnd;
    if (e < mpCapacity) {
        mpEnd = e + 1;
        if (e) {
            e->mName.mpBegin = gEmptyString16;
            e->mName.mpEnd = gEmptyString16;
            e->mName.mpCapacity = gEmptyString16 + 1;
            e->mShufflers.mpBegin = 0;
            e->mShufflers.mpEnd = 0;
            e->mShufflers.mpCapacity = 0;
            e->mRythms.mpBegin = 0;
            e->mRythms.mpEnd = 0;
            e->mRythms.mpCapacity = 0;
        }
        return;
    }
    Track_s00a3_fde0 local;
    local.mName.mpBegin = gEmptyString16;
    local.mName.mpEnd = gEmptyString16;
    local.mName.mpCapacity = gEmptyString16 + 1;
    local.mShufflers.mpBegin = 0;
    local.mShufflers.mpEnd = 0;
    local.mShufflers.mpCapacity = 0;
    local.mRythms.mpBegin = 0;
    local.mRythms.mpEnd = 0;
    local.mRythms.mpCapacity = 0;
    DoInsertValue(e, local);
}

// @ 0x00a404d0
bool Trixie_s00a3_fde0::ReadTrack(XmlReader* r)
{
    const void* name = r->GetAttr(L"name");
    if (!r->Next()) return false;
    mTracks.PushBackDefault();
    Track_s00a3_fde0* tr = mTracks.back();
    {
        RawStr t;
        ConvertToString8Impl(&t, name, 0xffffffff);
        tr->mName.Assign(t.b, t.e);
        if (1 < (int)(t.c - t.b) && t.b != 0) operator delete(t.b);
    }
    for (;;) {
        while (r->NodeType() == 1) {
            TrackEntry_s00a3_fde0* entry;
            if (wcscmp(r->Name(), L"shuffler") == 0) {
                tr->mShufflers.PushBackDefault();
                entry = tr->mShufflers.back();
            } else if (wcscmp(r->Name(), L"rhythm") == 0) {
                tr->mRythms.PushBackDefault();
                entry = tr->mRythms.back();
            } else {
                return false;
            }
            int n = r->AttrCount();
            for (int i = 0; i < n; i++) {
                const wchar_t* nm = r->AttrName(i);
                const wchar_t* val = r->AttrValue(i);
                entry->mItems.PushBackDefault();
                tItem_s00a3_fde0* it = entry->mItems.back();
                it->a = 2;
                {
                    RawStr t1;
                    ConvertToString8Impl(&t1, nm, 0xffffffff);
                    int sym[2];
                    gensym(sym, t1.b);
                    it->b = sym[0];
                    it->c = sym[1];
                    if (1 < (int)(t1.c - t1.b) && t1.b != 0) operator delete(t1.b);
                }
                it->v.PushBackDefault();
                {
                    _atom* a0 = it->v.back();
                    a0->a_type = (int)it->a;
                    a0->sym[0] = (int)it->b;
                    a0->sym[1] = (int)it->c;
                }
                RawStr t2;
                ConvertToString8Impl(&t2, val, 0xffffffff);
                bool numeric = true;
                {
                    const char* q = t2.b;
                    char c = *q;
                    while (c != 0) {
                        if (c != '.' && c != '-' && (c < '0' || c > '9')) { numeric = false; break; }
                        c = q[1];
                        q++;
                    }
                }
                if (numeric) {
                    it->v.PushBackDefault();
                    _atom* a = it->v.back();
                    a->a_type = 1;
                    a->f = (float)atof(t2.b);
                } else if (wcscmp(nm, L"beats") == 0) {
                    const char* q = t2.b;
                    do {
                        it->v.PushBackDefault();
                        _atom* a = it->v.back();
                        a->a_type = 1;
                        a->f = (*q == '.') ? 0.0f : 1.0f;
                        q++;
                    } while (*q != 0);
                } else {
                    const char* base = t2.b;
                    const char* e = t2.e;
                    if (e != base) {
                        const char* q = e;
                        for (;;) {
                            q--;
                            if (*q == '/') {
                                if (q != base) base = q + 1;
                                break;
                            }
                            if (q <= base) break;
                        }
                    }
                    it->v.PushBackDefault();
                    _atom* a = it->v.back();
                    a->a_type = 2;
                    gensym(&a->sym[0], base);
                }
                if (1 < (int)(t2.c - t2.b) && t2.b != 0) operator delete(t2.b);
            }
            if (!r->Next()) return false;
        }
        if (r->NodeType() == 2) {
            if (wcscmp(r->Name(), L"track") == 0) { r->Next(); return true; }
            r->Next();
            continue;
        }
        if (!r->Next()) return false;
    }
}

// @ 0x00a40a00
bool Trixie_s00a3_fde0::Read()
{
    Obj* obj = (Obj*)EA::Audio::Eapd::Debug::ObjectError();
    if (!obj) return false;
    WString name;
    name.mpBegin = (wchar_t*)gEmptyString16;
    name.mpEnd = (wchar_t*)gEmptyString16;
    name.mpCapacity = (wchar_t*)gEmptyString16 + 1;
    obj->M_7c(this, &name);
    {
        RawStr s;
        ConvertToString8(&s, &name);
        if ((TeString_s00a3_fde0*)&s != &mResourceName) mResourceName.Assign(s.b, s.e);
        if (1 < (int)(s.c - s.b) && s.b != 0) operator delete(s.b);
    }
    Handle* h = obj->M_58(this);
    if (!h) return false;
    Handle* handle = 0;
    if (!h->Open(this, (void**)&handle, 1, 6, 1, 0)) {
        if (handle) handle->Release();
        return false;
    }
    int readerMem[0x88 / 4];
    XmlReader* rd = (XmlReader*)readerMem;
    rd->Ctor(0);
    rd->M_901440(h->M_18(0));
    rd->M_9013e0();
    bool result = false;
    if (rd->NodeType() == 1 && wcscmp(rd->Name(), L"tracks") == 0) {
        rd->M_9013e0();
        result = true;
        for (;;) {
            if (rd->NodeType() == 1) {
                if (wcscmp(rd->Name(), L"track") != 0) { result = false; break; }
                if (!ReadTrack(rd)) { result = false; break; }
            } else {
                if (rd->NodeType() == 2) break;
                if (!rd->M_9013e0()) break;
            }
        }
    }
    h->M_24();
    rd->Dtor();
    if (handle) handle->Release();
    return result;
}

// @ 0x00a40cd0
void trixie_use(int self, int unused, int str)
{
    EA::Audio::Eapd::Debug::EapdObj* obj = EA::Audio::Eapd::Debug::ObjectError();
    if (!obj) return;
    int desc[3];
    desc[0] = 0;
    desc[1] = 0;
    desc[2] = 0;
    int s16[2];
    int* s = EA::ConvertToString16(s16, str, -1);
    char ok = obj->Slot30(desc, *s, 0, 0);
    if (s16[0] != 0 && (2 < ((s16[1] - s16[0]) & 0xfffffffe))) operator delete[]((void*)s16[0]);
    if (ok) {
        if (desc[2] == 0 || desc[2] == -1) desc[2] = 0x21407ee;
        if (desc[1] == 0 || desc[1] == -1) desc[1] = 0x330a65e;
        int* t = *(int**)(self + 0x28);
        t[0] = desc[0];
        t[1] = desc[1];
        t[2] = desc[2];
        EA::Audio::Eapd::Read(*(EA::Audio::Eapd::Trixie**)(self + 0x28));
    }
}

// @ 0x00a40dd0
int trixie_new(int a, int b, int arg3, int arg4)
{
    int self = EA::Audio::Eapd::pd_new(DAT_0166ef44);
    int* p = (int*)EA::Audio::Eapd::getbytes(0x34, "EAPd/Trixie");
    *(int**)(self + 0x28) = p;
    if (p != 0) {
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        p[3] = self;
        int base = (int)&DAT_01667bac;
        p[4] = base;
        p[5] = base;
        p[6] = 0x1667bad;
        p[8] = 0;
        p[9] = 0;
        p[10] = 0;
    } else {
        p = 0;
    }
    int u3 = DAT_0166ef28;
    int u4 = DAT_0166ef24;
    *(int**)(self + 0x28) = p;
    u3 = EA::Audio::Eapd::outlet_new(self, u4, u3);
    *(int*)(self + 0x2c) = u3;
    u4 = DAT_0166ef14;
    u3 = EA::Audio::Eapd::outlet_new(self, u4, DAT_0166ef18);
    *(int*)(self + 0x30) = u3;
    if (arg3 == 1) {
        trixie_use(self, *(int*)(arg4 + 4), *(int*)(arg4 + 8));
    }
    return self;
}

// @ 0x00a40e80
int SP_Audio_Trixie_Register()
{
    int buf[2];
    int* g;
    g = EA::Audio::Eapd::gensym(buf, DAT_01409070);
    DAT_0166ef2c = g[0];
    DAT_0166ef30 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453b90);
    DAT_0166ef0c = g[0];
    DAT_0166ef10 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453aac);
    DAT_0166ef1c = g[0];
    DAT_0166ef20 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453a40);
    DAT_0166ef3c = g[0];
    DAT_0166ef40 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01409070);
    DAT_0166ef24 = g[0];
    DAT_0166ef28 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453aa4);
    DAT_0166ef14 = g[0];
    DAT_0166ef18 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453b84);
    DAT_0166ef04 = g[0];
    DAT_0166ef08 = g[1];
    g = EA::Audio::Eapd::gensym(buf, DAT_01453b7c);
    DAT_0166ef34 = g[0];
    DAT_0166ef38 = g[1];
    DAT_0166ef44 = EA::Audio::Eapd::class_new(DAT_0166ef0c, DAT_0166ef10,
                                              (void*)trixie_new, (void*)FUN_00a3fdc0,
                                              0x38, 0, 9, 0);
    EA::Audio::Eapd::class_addmethod(DAT_0166ef44, (void*)FUN_00a3f090,
                                     DAT_0166ef1c, DAT_0166ef20, 9, 0);
    EA::Audio::Eapd::class_addmethod(DAT_0166ef44, (void*)trixie_use,
                                     DAT_0166ef3c, DAT_0166ef40, 2, 0);
    return 1;
}
