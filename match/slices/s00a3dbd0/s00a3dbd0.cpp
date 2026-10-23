// Slice s00a3dbd0: the EAPd "pixie" object (SP::Audio::Pixie) XML reader
// (Pixie::Read / Pixie::ReadSlot / pixie_free / the EAPd read method), the
// PixieSlot copy ctor, and the eastl vector<PixieSlot> / vector<tItem> element
// helpers.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int u32;

// math.h with a plain (non-dllimport) floor(): calls go through the CRT thunk 0x011e0906.
#define _CRTIMP
#include <math.h>

extern "C" __declspec(dllimport) long   __cdecl _wtol(const wchar_t* s);            // 0x013cc4ec
extern "C" __declspec(dllimport) double __cdecl strtod(const char* s, char** end);  // 0x013cc4b0
extern "C" int __cdecl wcscmp(const wchar_t*, const wchar_t*);
#pragma intrinsic(wcscmp)

void operator delete(void*);
void operator delete[](void*);
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();

#define kEastlFile \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---- external callees / constants (masked relocations) -----------------------
extern char    kEastlTag[];       // 0x013f2150 "EASTL"
extern wchar_t gEmptyString16[];  // 0x01667bac eastl::gEmptyString16

extern int DAT_0166eedc;          // 0x0166eedc "list" selector symbol
extern int DAT_0166eee0;          // 0x0166eee0 "list" selector symbol

extern float _DAT_01485378;       // 0x01485378  0.0f
extern float _DAT_01485720;       // 0x01485720  1.0f

void* __cdecl EAAllocate(u32 n, const char* tag, int a, int b, int file, int line);  // 0x00f473a0
void* __cdecl MemCopyRange(void* dst, const void* src, unsigned n);                  // 0x011e0744 (memcpy thunk)

void* __cdecl FUN_00a3d810(void** out, void* first, void* last, void* dst, void* src);  // 0x00a3d810
u32*  __cdecl FUN_00a3d8a0(u32* first, u32* last, int acc);                             // 0x00a3d8a0
u32*  __cdecl FUN_00a3f4d0(u32* first, u32* last, u32* dst);                            // 0x00a3f4d0
void* __cdecl FUN_00a3e040(void* first, void* last, void* dst);                         // 0x00a3e040
int   __cdecl FUN_00a3d920(int* str, int* out);                                         // 0x00a3d920

struct VecTItem;

namespace EA {
namespace Audio {
namespace Eapd {
void* __cdecl gensym(void* out, const void* name);                             // 0x00a675f0
void  __cdecl freebytes(void* p, int n);                                       // 0x00a49650
void  __cdecl outlet_list(void* o, int a, int b, int n, void* list);           // 0x00a49e40
void  __cdecl outlet_bang(void* o);                                            // 0x00a49da0
struct PdObj;
namespace Debug { PdObj* __cdecl ObjectError(void); }                          // 0x008de1a0
}}}

// A small symbol pair returned by gensym.
struct tSymbol { int a; int b; };

// eastl::basic_string<char,eastl::allocator> -> 0x10 bytes
struct TeString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c  (uninitialised by the copy ctor, as in the original)
    void Assign(char* first, char* last);    // 0x00454cb0
    void RangeInit(int n);                   // 0x00475ab0 (eastl RangeInitialize)
    TeString() {}
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

// eastl::basic_string<wchar_t,...> -> 0x10 bytes (the Pixie::Read local).
// The original never destroys this object automatically: every exit path makes
// exactly one explicit release call, so the type is left without a destructor.
struct WString16 {
    wchar_t* mpBegin;    // +0x00
    wchar_t* mpEnd;      // +0x04
    wchar_t* mpCapacity; // +0x08
    int      mAlloc;     // +0x0c
    void DeallocateSelf();      // 0x00933960
};

// ---- the EAPd atom -----------------------------------------------------------
union tAtomValue { int i; float f; void* p; };
struct Atom {           // 0xc
    int        a_type;  // +0x00
    tAtomValue w0;      // +0x04
    tAtomValue w1;      // +0x08
};

// eastl::vector<Atom,eastl::sp_vector_allocator> member of tItem -> 0x14 bytes.
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

// eastl::vector<tItem,eastl::sp_vector_allocator> -> 0x14 bytes
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
    TeString mName;     // +0x18
    PixieSlot(int number, const char* name);              // 0x00a3d630
    PixieSlot(const PixieSlot& src);
};

// eastl::vector<PixieSlot,eastl::sp_vector_allocator> -> 0x14 bytes
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
    TeString  mResourceName;  // +0x10
    VecPixieSlot mSlots;      // +0x20
    PixieSlot* FindByIndex(int key);   // 0x00a3d430
    PixieSlot* FindByName(int key);    // 0x00a3d480
    bool ReadSlot(struct XmlReader* r);
    bool Read();                       // 0x00a3e930
    ~Pixie() throw() {
        mSlots.~VecPixieSlot();
        mResourceName.~TeString();
    }
};

// ---- XML reader -------------------------------------------------------------
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

// ---- EAPd objects reached through a vtable ---------------------------------
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
void* __cdecl ConvertToString8(void* out, const void* s);                     // 0x0093c570
}

// =============================================================================
// @ 0x00a3dbd0
void pixie_read(int self, int sym, int b, int argc, int* argv) {
    (void)sym; (void)b;
    if (argc < 1 || argc == 2) return;
    if (argv[0] != 1 && argv[0] != 2) return;
    if (argc > 1) {
        if ((argv[3] != 1 && argv[3] != 2) || argv[6] != 1) return;
    }
    Pixie* px = *(Pixie**)(self + 0x28);
    PixieSlot* slotA = 0;
    PixieSlot* slotB = 0;
    float frac = 0.0f;
    if (argv[0] == 1) {
        float a = *(float*)&argv[1];
        float fl = (float)floor((double)a);
        slotA = px->FindByIndex((int)fl);
        if (fl != a) {
            frac = a - fl;
            slotB = px->FindByIndex((int)fl + 1);
        }
    } else {
        slotA = px->FindByName(argv[2]);
    }
    if (argc > 1 && slotB == 0 && frac == _DAT_01485378) {
        if (argv[3] == 1) {
            slotB = px->FindByIndex((int)(float)floor((double)*(float*)&argv[4]));
        } else {
            slotB = px->FindByName(argv[5]);
        }
        frac = *(float*)&argv[7];
    }
    if (slotA == 0 && slotB == 0) return;
    if (slotA != 0 && slotB != 0) {
        if (frac == _DAT_01485378) {
            slotB = 0;
        } else if (frac == _DAT_01485720) {
            slotA = slotB;
            slotB = 0;
        }
    }
    if (slotA == 0) {
        EA::Audio::Eapd::outlet_bang(*(void**)(self + 0x30));
        return;
    }
    if (slotB == 0) {
        for (tItem* it = slotA->mItems.mpBegin; it != slotA->mItems.mpEnd; ++it) {
            EA::Audio::Eapd::outlet_list(*(void**)(self + 0x2c), DAT_0166eedc, DAT_0166eee0,
                                         (int)(it->v.mpEnd - it->v.mpBegin), it->v.mpBegin);
        }
    } else {
        int nA = (int)(slotA->mItems.mpEnd - slotA->mItems.mpBegin);
        int nB = (int)(slotB->mItems.mpEnd - slotB->mItems.mpBegin);
        if (nA != nB) return;
        VecAtom out;
        out.mpBegin = 0; out.mpEnd = 0; out.mpCapacity = 0;
        tItem* bIt = slotB->mItems.mpBegin;
        for (tItem* aIt = slotA->mItems.mpBegin; aIt != slotA->mItems.mpEnd; ++aIt, ++bIt) {
            int nAtomsA = (int)(aIt->v.mpEnd - aIt->v.mpBegin);
            int nAtomsB = (int)(bIt->v.mpEnd - bIt->v.mpBegin);
            if (nAtomsA != nAtomsB) {
                out.~VecAtom();
                return;
            }
            out.erase(out.mpBegin, out.mpEnd);
            int cnt = nAtomsA > 2 ? nAtomsA : 2;
            out.resize(cnt);
            Atom* o = out.mpBegin;
            Atom* pa = aIt->v.mpBegin;
            Atom* pb = bIt->v.mpBegin;
            for (; pa != aIt->v.mpEnd; ++pa, ++pb, ++o) {
                if (pa->a_type != pb->a_type) {
                    out.~VecAtom();
                    return;
                }
                o->a_type = pa->a_type;
                o->w0 = pa->w0;
                o->w1 = pa->w1;
                if (pa->a_type == 1)
                    o->w0.f = pa->w0.f + (pb->w0.f - pa->w0.f) * frac;
            }
            EA::Audio::Eapd::outlet_list(*(void**)(self + 0x2c), DAT_0166eedc, DAT_0166eee0,
                                         cnt, out.mpBegin);
        }
        out.~VecAtom();
    }
    EA::Audio::Eapd::outlet_bang(*(void**)(self + 0x30));
}

// @ 0x00a3dfa0
PixieSlot::PixieSlot(const PixieSlot& src) : mItems(src.mItems), mNumber(src.mNumber), mName(src.mName) {
}

// @ 0x00a3e0d0
void FUN_00a3e0d0(int self) {
    Pixie* px = *(Pixie**)(self + 0x28);
    px->mSlots.~VecPixieSlot();
    px->mResourceName.~TeString();
    EA::Audio::Eapd::freebytes(*(void**)(self + 0x28), 0x34);
}

// @ 0x00a3e130
VecTItem* VecTItem::AssignItems(const VecTItem* x) {
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
PixieSlot* FUN_00a3e220(PixieSlot* first, PixieSlot* last, PixieSlot* dst) {
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

// @ 0x00a3e280
void VecPixieSlot::DoInsertValue(PixieSlot* pos, const PixieSlot& value) {
    PixieSlot* end = mpEnd;
    if (end != mpCapacity) {
        const PixieSlot* v = &value;
        if (pos <= v && v < end) v += 1;
        if (end) new ((void*)end) PixieSlot(*(PixieSlot*)((char*)end - 0x28));
        FUN_00a3e220(pos, end - 1, end);
        pos->mItems.AssignItems(&v->mItems);
        pos->mNumber = v->mNumber;
        if (&pos->mName != &v->mName)
            pos->mName.Assign(v->mName.mpBegin, v->mName.mpEnd);
        mpEnd = end + 1;
        return;
    }
    int cnt = (int)(end - mpBegin);
    int newSize = cnt == 0 ? 1 : cnt * 2;
    PixieSlot* nd;
    if (newSize == 0) {
        nd = 0;
    } else {
        nd = (PixieSlot*)EAAllocate(newSize * 0x28, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    }
    PixieSlot* pe = (PixieSlot*)FUN_00a3e040(mpBegin, pos, nd);
    FUN_00a3d8a0((u32*)mpBegin, (u32*)pos, (int)nd);
    if (pe) new ((void*)pe) PixieSlot(value);
    PixieSlot* ne = (PixieSlot*)FUN_00a3e040(pos, mpEnd, pe + 1);
    FUN_00a3d8a0((u32*)pos, (u32*)mpEnd, (int)(pe + 1));
    PixieSlot* ob = mpBegin;
    if (ob != 0 && ((int*)ob)[-1] != 0) operator delete(ob);
    mpEnd = ne;
    mpBegin = nd;
    mpCapacity = (PixieSlot*)((char*)nd + newSize * 0x28);
}

// @ 0x00a3e4c0
bool Pixie::ReadSlot(XmlReader* r) {
    const wchar_t* pNum = r->GetAttr(L"number");
    const wchar_t* pName = r->GetAttr(L"name");
    if (!r->Read()) return false;
    int number = (int)_wtol(pNum);
    {
        TeString str8;
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
                TeString sName;
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
                TeString sValue;
                EA::ConvertToString8Impl(&sValue, pv, 0xffffffff);
                TeString out16;
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
bool Pixie::Read() {
    EA::Audio::Eapd::PdObj* node = EA::Audio::Eapd::Debug::ObjectError();
    if (!node) return false;
    WString16 s16;
    s16.mpBegin = gEmptyString16;
    s16.mpEnd = gEmptyString16;
    s16.mpCapacity = (wchar_t*)((char*)gEmptyString16 + 2);
    node->Slot31(this, &s16);
    {
        TeString str8;
        TeString* s = (TeString*)EA::ConvertToString8(&str8, &s16);
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
