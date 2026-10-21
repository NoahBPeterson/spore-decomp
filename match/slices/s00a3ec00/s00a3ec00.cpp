// Slice s00a3ec00: SP::Audio Pixie / SendGame EAPd objects plus the eastl
// vector<Track>/vector<TrackEntry>/vector<tItem> container helpers (0xa3ec00-0xa3fd70).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int u32;

void* __cdecl EAAllocate(unsigned int n, const char* tag, int a, int b, int file, int line); // 0x00f473a0
void operator delete(void*);
void operator delete[](void*);
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

// ---- external callees / constants (masked relocations) -----------------------
extern char kEastlFile[];                 // 0x013ebb38 "...EASTL/allocator.h"
extern char kEastlTag[];                  // 0x013f2150 "EASTL"
extern wchar_t gEmptyString16[];          // 0x01667bac eastl::gEmptyString16
extern char DAT_01409070[];               // 0x01409070 "list"
extern char DAT_01453a40[];               // 0x01453a40 "use"
extern char DAT_01453aa4[];               // 0x01453aa4 "bang"
extern char DAT_01453aac[];               // 0x01453aac "read"
extern char DAT_01453ab4[];               // 0x01453ab4 "pixie"
extern char DAT_01453b10[];               // 0x01453b10 "sendgame"
extern char DAT_01453a98[];               // 0x01453a98 "EAPd/Pixie"
extern float _DAT_01485720;               // 0x01485720  1.0f
extern float _DAT_013f4fd0;               // 0x013f4fd0  4294967296.0f

extern int  spPixieClass;                 // 0x0166eeb8
extern int  spSendGameClass;              // 0x0166eeec
extern int  DAT_0166eebc, DAT_0166eec0, DAT_0166eec4, DAT_0166eec8;
extern int  DAT_0166eecc, DAT_0166eed0, DAT_0166eed4, DAT_0166eed8;
extern int  DAT_0166eedc, DAT_0166eee0, DAT_0166eee4, DAT_0166eee8;
extern int  DAT_0167589c, DAT_016758c4, DAT_01675894, DAT_016758ac;
extern int  DAT_0167545c;                 // 0x0167545c  outlet nesting guard
extern int  DAT_0166ef04;                 // 0x0166ef04  "shuffler" symbol
extern int  DAT_0166ef34;                 // 0x0166ef34  "rythm" symbol
extern int  DAT_0166ef2c, DAT_0166ef30;   // 0x0166ef2c / 0x0166ef30 list selector symbols
extern char DAT_040fdf2f[];               // 0x040fdf2f  debug format
extern char DAT_040fdfd9[];               // 0x040fdfd9
extern char DAT_040fe010[];               // 0x040fe010
extern char DAT_040fdffb[];               // 0x040fdffb

// ---- EAPd (Pure Data port) runtime -------------------------------------------
namespace EA { namespace Audio { namespace Eapd {
int   __cdecl pd_new(void* cls);                                                     // 0x00a49390
void* __cdecl getbytes(int n, const char* tag);                                      // 0x00a49610
void  __cdecl freebytes(void* p, int n);                                             // 0x00a49650
int*  __cdecl gensym(void* out, const void* name);                                   // 0x00a675f0
int   __cdecl class_new(void* a, void* b, void* newfn, void* dtor,
                        int size, int a6, int a7, int a8);                           // 0x00a48ea0
void  __cdecl class_addmethod(int cls, void* fn, int a, int b, int c, int d);        // 0x00a48a80
bool  __cdecl class_addanything(void* cls, void* fn);                                // 0x00a47f90
int   __cdecl symbolinlet_new(void* self, void* s);                                  // 0x00a49ab0
int   __cdecl outlet_new(void* self, int a, int b);                                  // 0x00a49d30
void  __cdecl outlet_list(void* o, int a, int b, int n, void* list);                 // 0x00a49e40
void  __cdecl outlet_bang(void* o);                                                  // 0x00a49da0
void  __cdecl outlet_float(void* o, float f);                                        // 0x00a49570
namespace Debug { int* __cdecl ObjectError(void); }                                  // 0x008de1a0
}}}

namespace EA { namespace Audio {
int* __cdecl GetSystemAT(void);                                                      // 0x00a206f0
}}

void* __cdecl ConvertToString16Impl(void* out, const char* s, unsigned int n);       // 0x0093c5a0
bool  __cdecl KeyEq(const void* a, const void* b);                                   // 0x00555020 (eastl hashtable DoFindNode)

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();

// ---- external container helpers (masked relocations) ------------------------
extern "C" void* __cdecl MemCopyRange(void* dst, const void* src, unsigned n);  // 0x011e0744 (memcpy thunk)
void* __cdecl FUN_00a3f660(void** out, void* first, void* last, void* dst, void* src);
void* __cdecl FUN_00bda890(void* dst, void* first, void* last);
void  __cdecl FUN_00a3e0d0(void* self);   // 0x00a3e0d0 pixie class dtor
void  __cdecl FUN_00a3dbd0(void* self);   // 0x00a3dbd0 pixie "read" method

// ---- retail container element types -----------------------------------------
// eastl::basic_string<char,eastl::allocator>  -> 0x10 bytes
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

// eastl::vector<_atom,eastl::sp_vector_allocator> member of tItem -> 0x14 bytes.
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

// eastl::vector<tItem,eastl::sp_vector_allocator> -> 0x14 bytes
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

// eastl::vector<TrackEntry,eastl::sp_vector_allocator> -> 0x14 bytes
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

// eastl::vector<Track,eastl::sp_vector_allocator> -> 0x14 bytes
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

// 16-bit string local used by pixie_use (manual cleanup, no destructor).
struct TeStr16 {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
};

// vector<Track> owner used by trixie_read: { ctrl, ctrl, unknown, list, vec@0x20 }
struct TrackList {
    char    pad[0x20];
    Track*  mpBegin;     // +0x20
    Track*  mpEnd;       // +0x24
    Track*  FindByName(void* key);   // 0x00a3f050
};

// ---- Eapd objects reached through a vtable ---------------------------------
struct PdSys {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 0..19
    VP VP VP VP VP VP VP VP VP VP                                 // 20..29
    virtual char Slot78(void* key, void* name, int a, int b);     // +0x78
};

struct Sys2 {
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 0..19
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 20..39
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 40..59
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 60..79
    VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP VP   // 80..99
    VP VP VP VP VP VP VP                                          // 100..106
    virtual void* Slot1ac();                                      // +0x1ac
};

// debug-context object reached from GetSystemAT()->Slot1ac()
struct DbgCtx {
    void M_102e0(void* a);           // 0x00a102e0
    void M_10390(void* a, float f);  // 0x00a10390
    void M_103b0(void* a, int v);    // 0x00a103b0
    void M_0f940();                  // 0x00a0f940
};

// =============================================================================
// @ 0x00a3ec00
void pixie_use(int self, void* sym, const char* name) {
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
    Pixie* px = (Pixie*)*(int*)(self + 0x28);
    px->mKey0 = key[0];
    px->mKey1 = key[1];
    px->mKey2 = key[2];
    px->Read();
}

// @ 0x00a3ed00
int pixie_new(void* a, void* b, int argc, void* argv) {
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

// @ 0x00a3edb0
bool Pixie_Register(void) {
    int buf[2];
    int* p;
    p = EA::Audio::Eapd::gensym(buf, DAT_01409070);   // "list"
    DAT_0166eedc = p[0];
    DAT_0166eee0 = p[1];
    p = EA::Audio::Eapd::gensym(buf, DAT_01453ab4);   // "pixie"
    DAT_0166eec4 = p[0];
    DAT_0166eec8 = p[1];
    p = EA::Audio::Eapd::gensym(buf, DAT_01453aac);   // "read"
    DAT_0166eecc = p[0];
    DAT_0166eed0 = p[1];
    p = EA::Audio::Eapd::gensym(buf, DAT_01453a40);   // "use"
    DAT_0166eee4 = p[0];
    DAT_0166eee8 = p[1];
    p = EA::Audio::Eapd::gensym(buf, DAT_01409070);   // "list"
    DAT_0166eed4 = p[0];
    DAT_0166eed8 = p[1];
    p = EA::Audio::Eapd::gensym(buf, DAT_01453aa4);   // "bang"
    DAT_0166eebc = p[0];
    DAT_0166eec0 = p[1];
    int cls = EA::Audio::Eapd::class_new((void*)DAT_0166eec4, (void*)DAT_0166eec8,
                                         (void*)pixie_new, (void*)FUN_00a3e0d0,
                                         0x38, 0, 9, 0);
    spPixieClass = cls;
    EA::Audio::Eapd::class_addmethod(cls, (void*)FUN_00a3dbd0,
                                     DAT_0166eecc, DAT_0166eed0, 9, 0);
    EA::Audio::Eapd::class_addmethod(cls, (void*)pixie_use,
                                     DAT_0166eee4, DAT_0166eee8, 2, 0);
    return true;
}

// @ 0x00a3eef0
int sendgame_new(int a, int b) {
    int r = EA::Audio::Eapd::pd_new((void*)spSendGameClass);
    if (r) {
        int* p = (int*)(r + 0x28);
        p[0] = a;
        p[1] = b;
        EA::Audio::Eapd::symbolinlet_new((void*)r, (void*)p);
    }
    return r;
}

// @ 0x00a3ef30
void sendgame_anything(int self, int sym, int b, int argc, int* argv) {
    (void)b;
    Sys2* sys = (Sys2*)EA::Audio::GetSystemAT();
    if (!sys) return;
    DbgCtx* d = (DbgCtx*)sys->Slot1ac();
    d->M_102e0(DAT_040fdf2f);
    if (DAT_0167589c == *(int*)(self + 0x28)) {
        d->M_103b0(DAT_040fdfd9, sym);
    } else {
        d->M_103b0(DAT_040fdfd9, *(int*)(self + 0x28));
        if (DAT_016758c4 != sym && DAT_01675894 != sym && DAT_016758ac != sym) {
            d->M_103b0(DAT_040fe010, sym);
        }
    }
    if (argc > 0) {
        int* it = argv + 1;
        int n = argc;
        do {
            if (it[-1] == 1)
                d->M_10390(DAT_040fdffb, *(float*)it);
            else
                d->M_103b0(DAT_040fe010, *it);
            it += 3;
        } while (--n != 0);
    }
    d->M_0f940();
}

// @ 0x00a3f000
bool SendGame_Register(void) {
    int buf[2];
    int* p = EA::Audio::Eapd::gensym(buf, DAT_01453b10);   // "sendgame"
    int cls = EA::Audio::Eapd::class_new((void*)p[0], (void*)p[1],
                                         (void*)sendgame_new, 0, 0x30, 0, 6, 0);
    bool ok = cls != 0;
    spSendGameClass = cls;
    bool r = EA::Audio::Eapd::class_addanything((void*)cls, (void*)sendgame_anything);
    return r & ok;
}

// @ 0x00a3f050
Track* TrackList::FindByName(void* key) {
    Track* p = mpBegin;
    Track* end = mpEnd;
    for (;;) {
        if (p == end) return 0;
        if (KeyEq(p, key)) break;
        p += 1;
    }
    return p;
}

// @ 0x00a3f090
void trixie_read(int self, int sym, int b, int argc, int* argv) {
    (void)sym; (void)b;
    if (argc < 1) return;
    if (argc < 2) return;
    if (argv[0] != 2) return;
    if (argv[3] != 2) return;
    Track* tr = ((TrackList*)*(int*)(self + 0x28))->FindByName((void*)argv[2]);
    if (!tr) return;
    if (argc <= 2) {
        if (argv[4] == DAT_0166ef04) {
            u32 n = (u32)((int)((char*)tr->mShufflers.mpEnd - (char*)tr->mShufflers.mpBegin) / 0x24);
            float f = (float)n;
            int g = DAT_0167545c + 1;
            DAT_0167545c = g;
            if (g < 1000) {
                int* p = *(int**)(*(int*)(self + 0x2c) + 8);
                while (p) {
                    EA::Audio::Eapd::outlet_float((void*)p[1], f);
                    p = (int*)*p;
                }
            }
            DAT_0167545c = DAT_0167545c - 1;
            return;
        }
        if (argv[4] != DAT_0166ef34) return;
        {
            u32 n = (u32)((int)((char*)tr->mRythms.mpEnd - (char*)tr->mRythms.mpBegin) / 0x24);
            float f = (float)n;
            int g = DAT_0167545c + 1;
            DAT_0167545c = g;
            if (g < 1000) {
                int* p = *(int**)(*(int*)(self + 0x2c) + 8);
                while (p) {
                    EA::Audio::Eapd::outlet_float((void*)p[1], f);
                    p = (int*)*p;
                }
            }
            DAT_0167545c = DAT_0167545c - 1;
        }
        return;
    }
    int kind = argv[6];
    if (kind != 2 && kind != 1) return;
    TrackEntry* vec;
    if (argv[4] == DAT_0166ef04) vec = (TrackEntry*)((char*)tr + 0x10);
    else if (argv[4] == DAT_0166ef34) vec = (TrackEntry*)((char*)tr + 0x24);
    else return;
    int idx = 0;
    float fval = 0.0f;
    if (kind == 2) idx = argv[8];
    else fval = *(float*)&argv[7];
    TrackEntry* begin = (TrackEntry*)vec->mName.mpBegin;
    TrackEntry* end = (TrackEntry*)vec->mName.mpEnd;
    float acc = 0.0f;
    if (begin == end) return;
    for (;;) {
        if (idx != 0) {
            if (!KeyEq(begin, (void*)idx)) {
                acc = acc + _DAT_01485720;
                begin = (TrackEntry*)((char*)begin + 0x24);
                if (begin == end) return;
                continue;
            }
        } else {
            if (!(acc == fval)) {
                acc = acc + _DAT_01485720;
                begin = (TrackEntry*)((char*)begin + 0x24);
                if (begin == end) return;
                continue;
            }
        }
        break;
    }
    if (begin == 0) return;
    tItem* item = (tItem*)begin->mItems.mpBegin;
    tItem* itemEnd = (tItem*)begin->mItems.mpEnd;
    for (; item != itemEnd; item += 1) {
        EA::Audio::Eapd::outlet_list((void*)*(int*)(self + 0x2c), DAT_0166ef2c, DAT_0166ef30,
                                     (int)((char*)item->v.mpEnd - (char*)item->v.mpBegin) / 0xc,
                                     item->v.mpBegin);
    }
    EA::Audio::Eapd::outlet_bang((void*)*(int*)(self + 0x30));
}

// @ 0x00a3f300
tItem* FUN_00a3f300(tItem* first, tItem* last, tItem* dst) {
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
TrackEntry::~TrackEntry() throw() {
}

// @ 0x00a3f3f0
int FUN_00a3f3f0(u32* first, u32* last, int acc) {
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
u32* FUN_00a3f480(u32* first, u32* last, u32* dst) {
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
u32* FUN_00a3f4d0(u32* first, u32* last, u32* dst) {
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
void VecTE::DestroyRange(TrackEntry* first, TrackEntry* last) {
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
TrackEntry::TrackEntry(const TrackEntry& src) : mName(src.mName), mItems(src.mItems) {
}

// @ 0x00a3f770
Track::~Track() throw() {
}

// @ 0x00a3f880
void VecTItem::DoInsertAtom(tItem* pos, const tItem* value) {
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
VecTE::VecTE(const VecTE& src) {
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
void VecTItem::PushBackDefault() {
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
Track::Track(const Track& src) : mName(src.mName), mShufflers(src.mShufflers), mRythms(src.mRythms) {
}

// @ 0x00a3fcd0
u32* FUN_00a3fcd0(u32* first, u32* last, u32* dst) {
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
u32* FUN_00a3fd20(u32* first, u32* last, u32* dst) {
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
Pixie::~Pixie() throw() {
}
