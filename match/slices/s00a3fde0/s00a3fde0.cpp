// Slice s00a3fde0: eastl vector<TrackEntry>/vector<Track> insert/assign helpers plus
// SP::Audio::Trixie XML loading (0xa3fde0-0xa40cca).
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-
#include "types.h"

typedef unsigned int u32;
typedef unsigned int size_type;

void* __cdecl EAAllocate(unsigned int n, const char* tag, int a, int b, int file, int line); // 0x00f473a0
void operator delete(void*);
void operator delete[](void*);
inline void* operator new(unsigned int, void* p) { return p; }
inline void operator delete(void*, void*) {}

// ---- external data / constants (masked relocations) --------------------------
extern char  kEastlFile[];      // 0x013ebb38 "...EASTL/allocator.h"
extern char  kEastlTag[];       // 0x013f2150 "EASTL"
extern char  gEmptyString16[];  // 0x01667bac  eastl gEmptyString16 (shared empty string base)
extern float _DAT_01485720;     // 0x01485720  1.0f

extern "C" int    wcscmp(const wchar_t*, const wchar_t*);
extern "C" double atof(const char*);

// ---- external helpers (masked relocations) -----------------------------------
u32* __cdecl FUN_00a3fcd0(u32* first, u32* last, u32* dst);   // backward range assign, 0x24 stride
u32* __cdecl FUN_00a3fd20(u32* first, u32* last, u32* dst);   // forward  range assign, 0x24 stride
void* __cdecl FUN_00a3f660(void** out, void* first, void* last, void* dst, void* d); // uninit copy, 0x24
void* __cdecl FUN_00a3f6e0(void* first, void* last, void* dst); // uninit copy, 0x24, returns dst
int   __cdecl FUN_00a3f3f0(u32* first, u32* last, int acc);    // destroy range, 0x24
void* __cdecl FUN_00a3fc40(void* first, void* last, void* dst); // uninit copy, 0x38
int   __cdecl FUN_00a3f840(u32* first, u32* last, int acc);    // destroy range, 0x38
int*  __cdecl gensym(void* out, const char* name);             // 0x00a675f0
void* __cdecl ConvertToString8Impl(void* out, const void* in, unsigned n); // 0x0093c440
void* __cdecl ConvertToString8(void* out, const void* in);     // 0x0093c570
bool  __cdecl wcscmpEq_(const wchar_t* a, const wchar_t* b);   // placeholder (unused)

namespace EA { namespace Audio { namespace Eapd { namespace Debug {
int* __cdecl ObjectError();                                    // 0x008de1a0
}}}}

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define VP virtual void CAT(pad_, __COUNTER__)();

// ---- pod string shaped exactly like eastl::basic_string<char> (0x10) ----------
// Used for locals whose lifetime is managed by hand in the original code.
struct RawStr {
    char* b;        // +0x00
    char* e;        // +0x04
    char* c;        // +0x08
    int   a;        // +0x0c
};

// ---- retail container element types -----------------------------------------
// eastl::basic_string<char,eastl::allocator> -> 0x10
struct TeString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
    void  Assign(char* first, char* last);   // 0x00454cb0 (ret 8)
    TeString& operator=(const TeString& x) {
        if (&x != this) Assign(x.mpBegin, x.mpEnd);
        return *this;
    }
    ~TeString() throw() {
        char* p = mpBegin;
        if (1 < (int)(mpCapacity - p) && p != 0) operator delete(p);
    }
};

// eastl::basic_string<wchar_t,eastl::allocator> -> 0x10
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

// SP::Audio::PixieSlot::_atom -> 0x0c
struct _atom {
    int a_type;             // +0x00
    union {
        float f;            // +0x04
        int   sym[2];       // +0x04,+0x08
    };
};

// eastl::vector<_atom,eastl::sp_vector_allocator> -> 0x14
struct tAtomVec {
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

struct tItem {          // 0x20 (3 dwords + vector<_atom>)
    u32 a, b, c;
    tAtomVec v;         // +0x0c
};

// eastl::vector<tItem,eastl::sp_vector_allocator> -> 0x14
struct VecTItem {
    tItem* mpBegin;     // +0x00
    tItem* mpEnd;       // +0x04
    tItem* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    tItem* back() { return mpEnd - 1; }
    void DestroyItems(tItem* first, tItem* last);        // 0x00bdc770
    void Assign(const VecTItem& s);                      // 0x00a3e130
    void DoInsertAtom(tItem* pos, const tItem* value);   // 0x00a3f880
    void PushBackDefault();                              // 0x00a3fb00
    VecTItem() {}
    VecTItem(const VecTItem& s);                         // 0x00a3db50
    ~VecTItem() throw() {
        DestroyItems(mpBegin, mpEnd);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};

struct TrackEntry {     // 0x24
    TeString mName;     // +0x00
    VecTItem mItems;    // +0x10
    TrackEntry() {}
    TrackEntry(const TrackEntry& src);   // 0x00a3f5d0
    ~TrackEntry() throw();               // 0x00a3f3a0
};

// eastl::vector<TrackEntry,eastl::sp_vector_allocator> -> 0x14
struct VecTE {
    TrackEntry* mpBegin;    // +0x00
    TrackEntry* mpEnd;      // +0x04
    TrackEntry* mpCapacity; // +0x08
    int         mA1;        // +0x0c
    int         mA2;        // +0x10
    TrackEntry* back() { return mpEnd - 1; }
    void DestroyRange(TrackEntry* first, TrackEntry* last);   // 0x00a3f520
    TrackEntry* Allocate(int n, TrackEntry* first, TrackEntry* last); // 0x00a3f7e0
    VecTE() {}
    VecTE& operator=(const VecTE& src);
    void DoInsertValue(TrackEntry* pos, const TrackEntry& value);
    void PushBackDefault();
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
    Track() {}
    Track(const Track& src);             // 0x00a3fb90
    ~Track() throw();                    // 0x00a3f770
};

// eastl::vector<Track,eastl::sp_vector_allocator> -> 0x14
struct VecTrack {
    Track* mpBegin;     // +0x00
    Track* mpEnd;       // +0x04
    Track* mpCapacity;  // +0x08
    int    mA1;         // +0x0c
    int    mA2;         // +0x10
    Track* back() { return mpEnd - 1; }
    void DoInsertValue(Track* pos, const Track& value);
    void PushBackDefault();
    ~VecTrack() throw() {
        Track* p = mpBegin;
        Track* e = mpEnd;
        for (; p < e; p += 1) p->~Track();
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0) operator delete(mpBegin);
    }
};

// ---- XML reader / handle / object reached through vtables --------------------
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

// SP::Audio::Trixie -> 0x34
struct Trixie {
    int      mKey0;          // +0x00
    int      mKey1;          // +0x04
    int      mKey2;          // +0x08
    void*    mpObject;       // +0x0c
    TeString mResourceName;  // +0x10
    VecTrack mTracks;        // +0x20
    bool ReadTrack(XmlReader* r);
    bool Read();
};

// =============================================================================
// @ 0x00a3fde0
void VecTE::DoInsertValue(TrackEntry* pos, const TrackEntry& value) {
    TrackEntry* end = mpEnd;
    if (end != mpCapacity) {
        const TrackEntry* v = &value;
        if (pos <= v && v < end) v += 1;
        if (end)
            ::new ((void*)end) TrackEntry(*(end - 1));
        FUN_00a3fcd0((u32*)pos, (u32*)(end - 1), (u32*)end);
        if (v != pos)
            pos->mName.Assign((char*)v->mName.mpBegin, (char*)v->mName.mpEnd);
        pos->mItems.Assign(v->mItems);
        mpEnd = end + 1;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    TrackEntry* nd;
    if (n == 0) {
        n = 1;
        nd = (TrackEntry*)EAAllocate(n * 0x24, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    } else {
        n = n * 2;
        if (n == 0) nd = 0;
        else nd = (TrackEntry*)EAAllocate(n * 0x24, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    }
    TrackEntry* oldBegin = mpBegin;
    TrackEntry* endp = (TrackEntry*)FUN_00a3f6e0(oldBegin, pos, nd);
    FUN_00a3f3f0((u32*)oldBegin, (u32*)pos, (int)nd);
    if (endp)
        ::new ((void*)endp) TrackEntry(value);
    TrackEntry* oldEnd = mpEnd;
    TrackEntry* ni = (TrackEntry*)FUN_00a3f6e0(pos, oldEnd, endp + 1);
    FUN_00a3f3f0((u32*)pos, (u32*)oldEnd, (int)(endp + 1));
    if (oldBegin != 0 && ((int*)oldBegin)[-1] != 0) operator delete(oldBegin);
    mpEnd = ni;
    mpBegin = nd;
    mpCapacity = nd + n;
}

// @ 0x00a3ffa0
VecTE& VecTE::operator=(const VecTE& src) {
    if (&src == this) return *this;
    size_type n = (size_type)(src.mpEnd - src.mpBegin);
    if (n > (size_type)(mpCapacity - mpBegin)) {
        TrackEntry* nd = Allocate((int)n, src.mpBegin, src.mpEnd);
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
        TrackEntry* out;
        FUN_00a3f660((void**)&out,
                     src.mpBegin + (size_type)(mpEnd - mpBegin),
                     src.mpEnd, mpEnd, src.mpEnd);
        mpEnd = mpBegin + n;
        return *this;
    }
    TrackEntry* e = (TrackEntry*)FUN_00a3fd20((u32*)src.mpBegin, (u32*)src.mpEnd, (u32*)mpBegin);
    DestroyRange(e, mpEnd);
    mpEnd = mpBegin + n;
    return *this;
}

// @ 0x00a400f0
void VecTE::PushBackDefault() {
    TrackEntry* e = mpEnd;
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
    TrackEntry local;
    local.mName.mpBegin = gEmptyString16;
    local.mName.mpEnd = gEmptyString16;
    local.mName.mpCapacity = gEmptyString16 + 1;
    local.mItems.mpBegin = 0;
    local.mItems.mpEnd = 0;
    local.mItems.mpCapacity = 0;
    DoInsertValue(e, local);
}

// @ 0x00a401d0
Track* FUN_00a401d0(Track* first, Track* last, Track* dst) {
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
void VecTrack::DoInsertValue(Track* pos, const Track& value) {
    Track* end = mpEnd;
    if (end != mpCapacity) {
        const Track* v = &value;
        if (pos <= v && v < end) v += 1;
        if (end)
            ::new ((void*)end) Track(*(end - 1));
        FUN_00a401d0(pos, end - 1, end);
        if (v != pos)
            pos->mName.Assign((char*)v->mName.mpBegin, (char*)v->mName.mpEnd);
        pos->mShufflers = v->mShufflers;
        pos->mRythms = v->mRythms;
        mpEnd = end + 1;
        return;
    }
    int n = (int)(mpEnd - mpBegin);
    Track* nd;
    if (n == 0) {
        n = 1;
        nd = (Track*)EAAllocate(n * 0x38, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    } else {
        n = n * 2;
        if (n == 0) nd = 0;
        else nd = (Track*)EAAllocate(n * 0x38, kEastlTag, 0, 0, (int)kEastlFile, 0xd1);
    }
    Track* oldBegin = mpBegin;
    Track* endp = (Track*)FUN_00a3fc40(oldBegin, pos, nd);
    FUN_00a3f840((u32*)oldBegin, (u32*)pos, (int)nd);
    if (endp)
        ::new ((void*)endp) Track(value);
    Track* oldEnd = mpEnd;
    Track* ni = (Track*)FUN_00a3fc40(pos, oldEnd, endp + 1);
    FUN_00a3f840((u32*)pos, (u32*)oldEnd, (int)(endp + 1));
    if (oldBegin != 0 && ((int*)oldBegin)[-1] != 0) operator delete(oldBegin);
    mpEnd = ni;
    mpBegin = nd;
    mpCapacity = nd + n;
}

// @ 0x00a40410
void VecTrack::PushBackDefault() {
    Track* e = mpEnd;
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
    Track local;
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
bool Trixie::ReadTrack(XmlReader* r) {
    const void* name = r->GetAttr(L"name");
    if (!r->Next()) return false;
    mTracks.PushBackDefault();
    Track* tr = mTracks.back();
    {
        RawStr t;
        ConvertToString8Impl(&t, name, 0xffffffff);
        tr->mName.Assign(t.b, t.e);
        if (1 < (int)(t.c - t.b) && t.b != 0) operator delete(t.b);
    }
    for (;;) {
        while (r->NodeType() == 1) {
            TrackEntry* entry;
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
                tItem* it = entry->mItems.back();
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
bool Trixie::Read() {
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
        if ((TeString*)&s != &mResourceName) mResourceName.Assign(s.b, s.e);
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
