// src/game/UTFSpore_Win32/XHTMLFrameSet.cpp -- migrated from slice(s) s00996f10 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/XHTMLFrameSet.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"
#include "EA/UTFWinExtras/WinXHTML.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void* FUN_009512c0(void);                                    // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void  FUN_00993390(void* self);                              // 0x993390
extern "C" void* FUN_008fe480(void);                                    // XHTML::Resource::GetResourceProvider
extern "C" void  FUN_00992e60(void* a);                                // 0x992e60 (thiscall, see casts)
extern "C" void  FUN_00992ea0(void* a);                                // 0x992ea0
extern "C" void  FUN_00997720(void);                                   // job callback
extern "C" void* WinXHTML_ctor(void* mem);                             // 0x993c10 thiscall
extern "C" void  FUN_009968f0(void);                                 // 0x9968f0
extern "C" int   FUN_00932f30(const wchar_t* s, unsigned seed, int a);   // FNV1_String16
extern "C" void* FUN_00d01260(void* a, void* b, void* c, void* d); // lower_bound (d = empty compare object by value)
extern "C" void  FUN_009970e0(void* a, void* b, void* c);               // vector<map pair>::insert
extern "C" void FUN_00996460(void* p);                                  // 0x996460 deque::clear
extern "C" int g_listNodeOffset;                        // 0x1440aec
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---- items of slice s00996f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_009512c0(void);                                    // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void  FUN_00993390(void* self);                              // 0x993390
extern "C" void* FUN_008fe480(void);                                    // XHTML::Resource::GetResourceProvider
extern "C" void  FUN_00992e60(void* a);                                // 0x992e60 (thiscall, see casts)
extern "C" void  FUN_00992ea0(void* a);                                // 0x992ea0
extern "C" void  FUN_00997720(void);                                   // job callback
extern "C" void* WinXHTML_ctor(void* mem);                             // 0x993c10 thiscall
extern "C" void  FUN_009968f0(void);                                 // 0x9968f0
extern "C" int   FUN_00932f30(const wchar_t* s, unsigned seed, int a);   // FNV1_String16
extern "C" void* FUN_00d01260(void* a, void* b, void* c, void* d); // lower_bound (d = empty compare object by value)
extern "C" void  FUN_009970e0(void* a, void* b, void* c);               // vector<map pair>::insert
extern "C" void FUN_00996460(void* p);                                  // 0x996460 deque::clear
#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])
struct DqIter {
    char* cur; char* begin; char* end; char** arr;
    DqIter* __thiscall plus_assign(int n);                                  // 0x9964c0
    void __thiscall move_backward(DqIter* first, DqIter* last, DqIter* out);// 0x996b40
    void __thiscall move_forward(DqIter* tmp, DqIter* next, DqIter* e, DqIter* out); // 0x996ad0
};
struct JobDeque {
    void* a0; void* a4;
    DqIter b;   // +8
    DqIter e;   // +0x18
    DqIter* __thiscall erase(DqIter* out, DqIter pos);
};
struct FrameSetJobs {                   // cXHTMLFrameSet viewed from its job-cleanup method
    bool ClearJobs();
};
struct FrameMessage {                    // UTFWin message block passed to the window's +0x114 handler
    int mPad0[2];
    int mID;        // +8
    int mSource;    // +0xc
    int mPad10[2];
    int mValue;     // +0x18
    FrameMessage(int id, int source, int value) { mID = id; mSource = source; mValue = value; }
};
struct XHTMLDocument {
    void FUN_008e3600(bool flag);                                        // 0x8e3600
};
struct IWindowMsg {                      // WinXHTML's interface at +4; slot 0x114 handles a message
    virtual void s00();
    virtual void s04();
    virtual void s08();
    virtual void s0c();
    virtual void s10();
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void s24();
    virtual void s28();
    virtual void s2c();
    virtual void s30();
    virtual void s34();
    virtual void s38();
    virtual void s3c();
    virtual void s40();
    virtual void s44();
    virtual void s48();
    virtual void s4c();
    virtual void s50();
    virtual void s54();
    virtual void s58();
    virtual void s5c();
    virtual void s60();
    virtual void s64();
    virtual void s68();
    virtual void s6c();
    virtual void s70();
    virtual void s74();
    virtual void s78();
    virtual void s7c();
    virtual void s80();
    virtual void s84();
    virtual void s88();
    virtual void s8c();
    virtual void s90();
    virtual void s94();
    virtual void s98();
    virtual void s9c();
    virtual void sa0();
    virtual void sa4();
    virtual void sa8();
    virtual void sac();
    virtual void sb0();
    virtual void sb4();
    virtual void sb8();
    virtual void sbc();
    virtual void sc0();
    virtual void sc4();
    virtual void sc8();
    virtual void scc();
    virtual void sd0();
    virtual void sd4();
    virtual void sd8();
    virtual void sdc();
    virtual void se0();
    virtual void se4();
    virtual void se8();
    virtual void sec();
    virtual void sf0();
    virtual void sf4();
    virtual void sf8();
    virtual void sfc();
    virtual void s100();
    virtual void s104();
    virtual void s108();
    virtual void s10c();
    virtual void s110();
    virtual void HandleMessage(FrameMessage* msg);
};
struct WinXHTML {
    void* mpVtbl0;
    IWindowMsg mWindow;                   // +4
    void SetDocument(XHTMLDocument* doc);                                // 0x994b00
};
struct cXHTMLFrameSet {
    WinXHTML* GetJobInfo(void* key, bool* outFlag);
    void LoadRequestCallback(int* p);
};
struct FrameMapPair { unsigned hash; void* win; };
struct FrameMapVM {                      // vector_map<hash, WinXHTML*> part of cXHTMLFrameSet
    bool insert(void* win, const wchar_t* name);
};
extern "C" int g_listNodeOffset;                        // 0x1440aec
struct FrameSetExt {
    bool __thiscall AddFrameEntry(void* win, const wchar_t* name); // 0x997350
};
struct FrameSet {
    void* CreateFrame(void* src);                                         // 0x9973e0
    bool HandleLocationChange(int* p, void* a3, wchar_t* name, int flag); // 0x997730
    bool FindFrames(void* root, int id);                                  // 0x9979f0
    bool Bind(int** a1, int id, int* a3);                                 // 0x997bf0
};
struct JobEntry { void* a; void* win; unsigned char flag; };
struct FixedWString96 {                 // eastl::fixed_string<wchar_t, 96> on the stack
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAllocName; wchar_t* mpPoolBegin;
    wchar_t mBuffer[96];
};
struct WString { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCapacity; int mAlloc; };
// ---- items of slice s00996f10 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void  FUN_008e4b10(void* a, void* b);                        // 0x8e4b10
extern "C" void  FUN_008e4f00(void* a, void* b, void* c);               // 0x8e4f00
extern "C" void  FUN_00579a90(void* str, void* a, void* b, int c, int d, int e); // RangeInitialize
extern "C" void  FUN_00599bb0(void* str, void* src);                    // string operator+=

// @ 0x00996f10
DqIter* JobDeque::erase(DqIter* out, DqIter pos)
{
    DqIter next = pos;
    next.cur = pos.cur + 0xc;
    if (next.cur == pos.end) {
        next.arr = pos.arr + 1;
        next.begin = *next.arr;
        next.end = next.begin + 0xc0;
        next.cur = next.begin;
    }
    int idx = (int)(((pos.arr - b.arr)) * 16) + (int)((b.end - b.cur) / 0xc) + (int)((pos.cur - pos.begin) / 0xc) - 0x10;
    unsigned size = (unsigned)((((e.arr - b.arr) - 1) * 16) + (int)((e.cur - e.begin) / 0xc) + (int)((b.end - b.cur) / 0xc));
    if (idx < (int)(size >> 1)) {
        next.move_backward(&b, &pos, out);
        if (b.cur + 0xc == b.end) {
            if (b.begin)
                FUN_00f47380(b.begin);
            b.arr = b.arr + 1;
            b.begin = *b.arr;
            b.end = b.begin + 0xc0;
            b.cur = b.begin;
        } else {
            b.cur = b.cur + 0xc;
        }
    } else {
        DqIter tmp;
        pos.move_forward(&tmp, &next, &e, out);
        if (e.cur == e.begin) {
            if (e.begin)
                FUN_00f47380(e.begin);
            e.arr = e.arr - 1;
            e.begin = *e.arr;
            e.end = e.begin + 0xc0;
            e.cur = e.end - 0xc;
        } else {
            e.cur = e.cur - 0xc;
        }
    }
    DqIter t = b;
    DqIter* r = t.plus_assign(idx);
    *out = *r;
    return out;
}

// @ 0x00997140
bool FrameSetJobs::ClearJobs()
{
    char* self = (char*)this;
    char* piVar4 = (char*)FUN_008fe480();
    if (piVar4 != 0) {
        char* puVar1 = *(char**)(self + 0x3c);
        char* puVar6 = *(char**)(self + 0x2c);
        char* puVar2 = *(char**)(self + 0x34);
        char* iVar5 = *(char**)(self + 0x38);
        while (puVar6 != puVar1) {
            (*(void(__thiscall**)(char*, void*))((char*)*(void**)piVar4 + 8))(piVar4, *(void**)puVar6);
            puVar6 += 0x0c;
            if (puVar6 == puVar2) {
                puVar6 = *(char**)(iVar5 + 4);
                iVar5 += 4;
                puVar2 = puVar6 + 0xc0;
            }
        }
    }
    ((void(__thiscall*)(char*))FUN_00996460)(self + 0x24);
    char* iVar3 = *(char**)(self + 0x10);
    for (char* iVar5 = *(char**)(self + 0xc); iVar5 != iVar3; iVar5 += 8) {
        ((void(__thiscall*)(void*))FUN_00993390)(*(void**)(iVar5 + 4));
        (*(void(__thiscall**)(char*, char*))
            ((char*)*(void**)(*(int*)(iVar5 + 4) + 4) + 0x108))((char*)(*(int*)(iVar5 + 4) + 4), self);
    }
    char* end = *(char**)(self + 0x10);
    int n = (int)((end - *(char**)(self + 0xc)) >> 3);
    *(char**)(self + 0x10) = end + n * -8;
    return true;
}

// @ 0x00997210
WinXHTML* cXHTMLFrameSet::GetJobInfo(void* key, bool* outFlag)
{
    char* self = (char*)this;
    char* a = *(char**)(self + 0x2c);
    char* end = *(char**)(self + 0x3c);
    char* ebp = *(char**)(self + 0x34);
    char* esi = *(char**)(self + 0x30);
    char* edi = *(char**)(self + 0x38);
    while (a != end) {
        if (*(void**)a == key)
            break;
        a += 0x0c;
        if (a == ebp) {
            esi = *(char**)(edi + 4);
            edi += 4;
            ebp = esi + 0xc0;
            a = esi;
        }
    }
    if (a == end)
        return 0;
    WinXHTML* ret = *(WinXHTML**)(a + 4);
    *outFlag = *(bool*)(a + 8);
    DqIter found;
    found.cur = a; found.begin = esi; found.end = ebp; found.arr = (char**)edi;
    DqIter res;
    ((JobDeque*)(self + 0x24))->erase(&res, found);
    return ret;
}

// @ 0x009972a0
void cXHTMLFrameSet::LoadRequestCallback(int* p)
{
    if (*p == 4)
        return;
    bool flag;
    WinXHTML* win = GetJobInfo((void*)p[1], &flag);
    if (*p == 3) {
        FrameMessage msg(0x43b0aee, p[1], p[3]);
        win->mWindow.HandleMessage(&msg);
        return;
    }
    void* src;
    if (*p == 2 && (src = (void*)p[4]) != 0) {
        XHTMLDocument* q = (XHTMLDocument*)(*(void*(__thiscall**)(void*, int))((char*)*(void**)src + 0xc))(src, 0x2b29464);
        if (q) {
            (*(void(__thiscall**)(XHTMLDocument*))*(void**)q)(q);
            if (win) {
                q->FUN_008e3600(flag);
                win->SetDocument(q);
            }
            (*(void(__thiscall**)(XHTMLDocument*))((char*)*(void**)q + 4))(q);
        }
    }
}

// @ 0x00997350
bool FrameMapVM::insert(void* win, const wchar_t* name)
{
    char* self = (char*)this;
    FrameMapPair v;
    v.hash = (unsigned)FUN_00932f30(name, 0x811c9dc5, 0);
    v.win = win;
    char* end = *(char**)(self + 0x10);
    char* low = (char*)FUN_00d01260(*(void**)(self + 0xc), end, &v.hash, (void*)(unsigned)*(unsigned char*)(self + 0x20));
    if (low != end && *(unsigned*)low <= v.hash)
        return false;
    ((void(__thiscall*)(char*, void*, void*))FUN_009970e0)(self + 0xc, low, &v);
    char* iface = (char*)win + 4;
    (*(void(__thiscall**)(char*, char*))((char*)*(void**)iface + 0x104))(iface, self);
    return true;
}

// @ 0x009973e0
void* FrameSet::CreateFrame(void* src)
{
    char* self = (char*)this;
    char* win;
    typedef void* (__thiscall* FactoryFn)(char*);
    FactoryFn factory = *(FactoryFn*)(self + 0x50);
    if (factory == 0) {
        void* mem = FUN_009512d0(0xa8e8, 8, "XHTML/FrameSet/WinXHTML", FUN_009512c0());
        if (mem)
            win = (char*)((void*(__thiscall*)(void*))WinXHTML_ctor)(mem);
        else
            win = 0;
    } else {
        win = (char*)factory(self);
    }
    void* w2 = win + 4;
    void* slot60 = *(void**)((char*)*(void**)w2 + 0x60);
    VF(w2, 0x60, void(__thiscall*)(void*, int))(w2, VF(src, 0x34, int(__thiscall*)(void*))(src));
    VF(w2, 0xac, void(__thiscall*)(void*, int))(w2, VF(src, 0xa4, int(__thiscall*)(void*))(src));
    VF(w2, 0x50, void(__thiscall*)(void*, int))(w2, VF(src, 0x1c, int(__thiscall*)(void*))(src));
    VF(w2, 0x54, void(__thiscall*)(void*, int))(w2, VF(src, 0x20, int(__thiscall*)(void*))(src));
    (void)slot60;
    typedef unsigned (__thiscall* GetFlags)(void*);
    typedef void (__thiscall* SetFlag)(void*, int, int);
    static const struct { int mask; int shift; } bits[] = {
        {1, 0}, {2, 1}, {8, 3}, {0x10, 4}, {0x800, 0xb}, {0x400, 0xa},
        {0x40, 6}, {4, 2}, {0x80, 7}, {0x200, 9}
    };
    for (int i = 0; i < 10; i++) {
        unsigned f = VF(src, 0x28, GetFlags)(src);
        VF(w2, 0x7c, SetFlag)(w2, bits[i].mask, (f >> bits[i].shift) & 1);
    }
    const wchar_t* name = VF(src, 0x3c, const wchar_t*(__thiscall*)(void*))(src);
    ((FrameSetExt*)self)->AddFrameEntry(win, name);

    for (void* c = VF(src, 0x10c, void*(__thiscall*)(void*, void*))(src, 0); c;
         c = VF(src, 0x10c, void*(__thiscall*)(void*, void*))(src, c)) {
        if (VF(c, 0xc, void*(__thiscall*)(void*, unsigned))(c, 0xcf3df10b)) {
            VF(w2, 0x104, void(__thiscall*)(void*))(w2);
            break;
        }
    }

    int itEnd, itBeg;
    int* pe = VF(src, 0xd0, int*(__thiscall*)(void*, int*))(src, &itEnd);
    int* pb = VF(src, 0xcc, int*(__thiscall*)(void*, int*))(src, &itBeg);
    while (*pb != *pe) {
        int tmp;
        int* q = VF(src, 0xcc, int*(__thiscall*)(void*, int*))(src, &tmp);
        void* child = (void*)(*q + g_listNodeOffset);
        VF(child, 0, void(__thiscall*)(void*))(child);
        VF(src, 0xdc, void(__thiscall*)(void*, void*))(src, child);
        VF(w2, 0xd8, void(__thiscall*)(void*, void*))(w2, child);
        VF(child, 4, void(__thiscall*)(void*))(child);
        pe = VF(src, 0xd0, int*(__thiscall*)(void*, int*))(src, &itEnd);
        pb = VF(src, 0xcc, int*(__thiscall*)(void*, int*))(src, &itBeg);
    }

    void* parent = VF(src, 0x10, void*(__thiscall*)(void*))(src);
    VF(parent, 0xe0, void(__thiscall*)(void*, void*))(parent, src);
    VF(parent, 0xd8, void(__thiscall*)(void*, void*))(parent, w2);
    void* x = VF(win, 0xc, void*(__thiscall*)(void*, unsigned))(win, 0xeeee8218);
    VF(x, 0x94, void(__thiscall*)(void*))(x);
    return VF(win, 0xc, void*(__thiscall*)(void*, unsigned))(win, 0xeeee8218);
}

// @ 0x00997730
bool FrameSet::HandleLocationChange(int* p, void* a3, wchar_t* name, int flag)
{
    char* self = (char*)this;
    char* win;
    if (p != 0)
        win = (char*)VF(p, 0xc, void*(__thiscall*)(int*, unsigned))(p, 0x4d044f3);
    else
        win = 0;
    if (name != 0) {
        unsigned h = (unsigned)FUN_00932f30(name, 0x811c9dc5, 0);
        char* end = *(char**)(self + 0x10);
        char* it = (char*)FUN_00d01260(*(void**)(self + 0xc), end, &h, (void*)(unsigned)*(unsigned char*)(self + 0x20));
        if (it == end || h < *(unsigned*)it)
            it = end;
        else if (it == it + 8)
            it = end;
        if (it != end)
            win = *(char**)(it + 4);
    }
    void* prov = FUN_008fe480();
    if (win == 0 || prov == 0)
        return false;
    ((void(__thiscall*)(char*, int))FUN_00992e60)(win, *(int*)(self + 0x5c));
    ((void(__thiscall*)(char*, int))FUN_00992ea0)(win, *(int*)(self + 0x60));
    ((void(__thiscall*)(char*))FUN_00993390)(win);
    {
        char* cur = *(char**)(self + 0x2c);
        char* end = *(char**)(self + 0x3c);
        char* segEnd = *(char**)(self + 0x34);
        char** arr = *(char***)(self + 0x38);
        while (cur != end) {
            if (*(char**)(cur + 4) == win)
                VF(prov, 8, void(__thiscall*)(void*, void*))(prov, *(void**)cur);
            cur += 0xc;
            if (cur == segEnd) {
                cur = arr[1];
                arr++;
                segEnd = cur + 0xc0;
            }
        }
    }
    JobEntry je;
    je.win = win;
    je.flag = (unsigned char)flag;
    char* e = *(char**)(self + 0x3c);
    char* dq = self + 0x24;
    if (e + 0xc != *(char**)(dq + 0x20)) {
        *(char**)(dq + 0x18) = e + 0xc;
        if (e != 0)
            *(JobEntry*)e = je;
    } else {
        ((void(__thiscall*)(char*, JobEntry*))FUN_009968f0)(dq, &je);
    }
    char* cur = *(char**)(self + 0x3c);
    if (cur == *(char**)(self + 0x40))
        cur = *(char**)(*(char***)(self + 0x48) - 1) + 0xc0;
    VF(prov, 4, void(__thiscall*)(void*, char*, void*, void*, char*, int, int))(prov, cur - 0xc, a3, (void*)FUN_00997720, self, 0, flag);
    return true;
}

// @ 0x009978b0
bool EA::UTFWinExtras::cXHTMLFrameSet::HandleFormSubmit(EA::UTFWin::IWindow * p, EA::XHTML::DOM::Form * form)
{
    FixedWString96 fs;
    fs.mpBegin = fs.mBuffer;
    fs.mpEnd = fs.mBuffer;
    fs.mpCapacity = fs.mBuffer + 96;
    fs.mpPoolBegin = fs.mBuffer;
    fs.mBuffer[0] = 0;
    bool result = false;
    if (form != 0 && ((bool(__thiscall*)(void*, FixedWString96*))FUN_008e4b10)(form, &fs)
        && (fs.mpEnd - fs.mpBegin) != 0) {
        WString s;
        s.mpBegin = 0; s.mpEnd = 0; s.mpCapacity = 0;
        ((void(__thiscall*)(WString*, const wchar_t*))FUN_00579a90)(&s, fs.mpBegin);
        ((void(__thiscall*)(WString*, const void*))FUN_00599bb0)(&s, (const void*)0x1459c40);
        ((void(__thiscall*)(void*, void*, WString*))FUN_008e4f00)(form, (void*)0x996da0, &s);
        HandleLocationChange(p, s.mpBegin, 0, 0);
        if ((s.mpCapacity - s.mpBegin) > 1 && s.mpBegin)
            FUN_00f47380(s.mpBegin);
        result = true;
    }
    if ((fs.mpCapacity - fs.mpBegin) > 1 && fs.mpBegin && fs.mpBegin != fs.mpPoolBegin)
        FUN_00f47380(fs.mpBegin);
    return result;
}
