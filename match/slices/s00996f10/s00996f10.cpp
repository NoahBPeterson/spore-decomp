// Slice s00996f10 -- EA::UTFWinExtras XHTML frame set, frame map, HitMask tools.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---------------------------------------------------------------- externs
extern "C" void* FUN_009512c0(void);                                    // 0x9512c0
extern "C" void* FUN_009512d0(int size, int align, const char* name, void* alloc); // 0x9512d0
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, int c, int d);
extern "C" void* FUN_011e0744(void* dst, void* src, unsigned n);        // vector<bool>::DoInsertValue
extern "C" void  FUN_00996b40(void* a, void* b, void* c);               // deque push_front helper
extern "C" void  FUN_00996ad0(void* a, void* b, void* c, void* d);      // deque push_back helper
extern "C" void  FUN_00993390(void* self);                              // 0x993390
extern "C" void  FUN_0098e3600(void* a);                                // 0x8e3600
extern "C" void* FUN_008fe480(void);                                    // XHTML::Resource::GetResourceProvider
extern "C" void  FUN_00992e60(void* a);                                // 0x992e60 (thiscall, see casts)
extern "C" void  FUN_00992ea0(void* a);                                // 0x992ea0
extern "C" void  FUN_00997720(void);                                   // job callback
extern "C" void* WinXHTML_ctor(void* mem);                             // 0x993c10 thiscall
extern "C" void  FUN_009968f0(void);                                 // 0x9968f0
extern "C" void  FUN_008e4b10(void* a, void* b);                        // 0x8e4b10
extern "C" void  FUN_008e4f00(void* a, void* b, void* c);               // 0x8e4f00
extern "C" void  FUN_00579a90(void* str, void* a, void* b, int c, int d, int e); // RangeInitialize
extern "C" void  FUN_00599bb0(void* str, void* src);                    // string operator+=
extern "C" void  FUN_0087cde0(void* a);                                 // 0x87cde0
extern "C" char  FUN_0087ce00(void* a);                                 // 0x87ce00
extern "C" char  FUN_0087d0b0(void* a, void* b);                        // 0x87d0b0
extern "C" void* FUN_0087ced0(int a);                                   // 0x87ced0
extern "C" char  FUN_0087cf00(void* a, void* b, int c);                 // 0x87cf00
extern "C" void  FUN_0087cef0(void* a);                                 // gfree
extern "C" void  FUN_0087d070(void);                                    // 0x87d070
extern "C" void  FUN_00957300(void* a, int b, void* c);                 // 0x957300
extern "C" void  FUN_00957230(void* a, int b, void* c);                 // 0x957230
extern "C" void* FUN_00904b00(void* a, void* b);                        // WinXHTML::SetDocument 0x994b00
extern "C" int   FUN_00932f30(const wchar_t* s, unsigned seed, int a);   // FNV1_String16
extern "C" void* FUN_00d01260(void* a, void* b, void* c, void* d); // lower_bound (d = empty compare object by value)
extern "C" void  FUN_009970e0(void* a, void* b, void* c);               // vector<map pair>::insert
extern "C" void  FUN_00992e60_(void* a);
extern "C" unsigned g_frameMapTypes[];                                 // 0x1446868
extern "C" void FUN_00996460(void* p);                                  // 0x996460 deque::clear

// helper struct with thiscall callees
struct Ext33 {
    void FUN_00996f10_(int a, int b, int c, int d);
    void FUN_00997140_();
    void FUN_00997b10_(void* v);
    void FUN_00997ba0_();
};

#define VF(o, off, sig) ((sig)(*(void***)(o))[(off) / 4])

struct DqIter {
    char* cur; char* begin; char* end; char** arr;
    DqIter* __thiscall plus_assign(int n);                                  // 0x9964c0
    void __thiscall move_backward(DqIter* first, DqIter* last, DqIter* out);// 0x996b40
    void __thiscall move_forward(DqIter* tmp, DqIter* next, DqIter* e, DqIter* out); // 0x996ad0
};

// eastl::deque<JobEntry,16>::erase (this = deque; begin iterator at +8, end iterator at +0x18)
struct JobDeque {
    void* a0; void* a4;
    DqIter b;   // +8
    DqIter e;   // +0x18
    DqIter* __thiscall erase(DqIter* out, DqIter pos);
};

// ---------------------------------------------------------------- 00997140
// @ 0x00997140
void FUN_00997140(char* self)
{
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
    FUN_00996460(self + 0x24);
    char* iVar3 = *(char**)(self + 0x10);
    for (char* iVar5 = *(char**)(self + 0xc); iVar5 != iVar3; iVar5 += 8) {
        FUN_00993390(*(void**)(iVar5 + 4));
        (*(void(__thiscall**)(char*, char*))
            ((char*)*(void**)(*(int*)(iVar5 + 4) + 4) + 0x108))((char*)(*(int*)(iVar5 + 4) + 4), self);
    }
    int n = (int)((iVar3 - *(char**)(self + 0xc)) >> 3);
    *(int*)(self + 0x10) = (int)iVar3 + n * -8;
}

// ---------------------------------------------------------------- 00997210 GetJobInfo
// @ 0x00997210
void* GetJobInfo(char* self, void* key, unsigned char* outFlag)
{
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
    void* ret = *(void**)(a + 4);
    *outFlag = *(unsigned char*)(a + 8);
    DqIter found;
    found.cur = a; found.begin = esi; found.end = ebp; found.arr = (char**)edi;
    DqIter res;
    ((JobDeque*)(self + 0x24))->erase(&res, found);
    return ret;
}

// ---------------------------------------------------------------- 009972a0 LoadRequestCallback
// @ 0x009972a0
void FUN_009972a0(char* self, int* p)
{
    if (*p == 4)
        return;
    unsigned char flag;
    void* win = GetJobInfo(self, (void*)p[1], &flag);
    if (*p == 3) {
        int a = p[3];
        int b = p[1];
        int local[3];
        local[0] = 0x43b0aee;
        local[1] = b;
        local[2] = a;
        (*(void(__thiscall**)(char*, int*))((char*)*(void**)((char*)win + 4) + 0x114))((char*)win + 4, local);
        return;
    }
    if (*p == 2 && p[4] != 0) {
        char* q = (char*)(*(void*(__thiscall**)(int, int))((char*)*(void**)p[4] + 0xc))(p[4], 0x2b29464);
        if (q) {
            (*(void(__thiscall**)(char*))*(void**)q)(q);
            if (win) {
                FUN_0098e3600((void*)0);
                FUN_00904b00(win, q);
            }
            (*(void(__thiscall**)(char*))((char*)*(void**)q + 4))(q);
        }
    }
}

// ---------------------------------------------------------------- 00997350 vector_map::insert
// @ 0x00997350
bool FUN_00997350(char* self, int key, const wchar_t* name)
{
    unsigned hash = (unsigned)FUN_00932f30(name, 0x811c9dc5, 0);
    char* end = *(char**)(self + 0x10);
    char* low = (char*)FUN_00d01260(*(void**)(self + 0xc), end, &hash, (void*)(unsigned)*(unsigned char*)(self + 0x20));
    if (low != end && *(unsigned*)low <= hash)
        return false;
    FUN_009970e0(low, &key, &hash);
    (*(void(__thiscall**)(int, char*))((char*)*(void**)(key + 4) + 0x104))(key, self);
    return true;
}

// ---------------------------------------------------------------- 00996f10 deque::erase
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

extern "C" void  __fastcall FUN_00993c10(void* self);   // WinXHTML::WinXHTML (thiscall)
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

// ---------------------------------------------------------------- 009973e0 CreateFrameFromWindow
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

// ---------------------------------------------------------------- 00997730 HandleLocationChange
struct JobEntry { void* a; void* win; unsigned char flag; };

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

// ---------------------------------------------------------------- 009978b0 HandleFormSubmit
// @ 0x009978b0
bool HandleFormSubmit(char* self, void* form)
{
    if (!form)
        return false;
    unsigned short buf[4];
    buf[0] = 0;
    int local[4];
    local[0] = 0;
    local[1] = 0;
    local[2] = 0;
    char ok = 0;
    FUN_008e4b10(form, &ok);
    if (ok == 0)
        return false;
    // build string and iterate params
    FUN_00579a90(local, 0, 0, 0, 0, 0);
    FUN_00599bb0(local, (void*)0x1459c40);
    int outStr = 0;
    FUN_008e4f00(form, (void*)0x996da0, &outStr);
    ((FrameSet*)self)->HandleLocationChange(0, 0, 0, outStr);
    if (outStr) FUN_00f47380((void*)outStr);
    (void)buf;
    return true;
}

// ---------------------------------------------------------------- 009979f0 FindOrCreateFrames
struct PtrStack {
    void** b; void** e; void** c;
    void __thiscall DoInsertValue(void** pos, void** v);   // 0x630b30
    void push_back(void* v)
    {
        void** p = e;
        if (p < c) {
            e = p + 1;
            if (p) *p = v;
        } else {
            DoInsertValue(p, &v);
        }
    }
};

// @ 0x009979f0
bool FrameSet::FindFrames(void* root, int id)
{
    char* self = (char*)this;
    if (root) {
        PtrStack st;
        st.b = 0; st.e = 0; st.c = 0;
        st.DoInsertValue(0, &root);
        while (st.b != st.e) {
            void* w = *--st.e;
            if (VF(w, 0x1c, int(__thiscall*)(void*))(w) == id)
                w = ((FrameSet*)self)->CreateFrame(w);
            int end;
            VF(w, 0xcc, void(__thiscall*)(void*, void**))(w, &root);
            VF(w, 0xd0, void(__thiscall*)(void*, int*))(w, &end);
            for (; (int)root != end; root = *(void**)root)
                st.push_back((void*)((int)root + g_listNodeOffset));
        }
        if (st.b && ((int*)st.b)[-1])
            FUN_00f47380(st.b);
    }
    return *(int*)(self + 0xc) != *(int*)(self + 0x10);
}

// ---------------------------------------------------------------- 00997b10 push_back
struct VecPB {
    char pad[4];
    unsigned* mEnd;     // +4
    unsigned* mCap;     // +8
    __declspec(noinline) void push_back(unsigned* v);
    void DoInsertValue(unsigned* pos, unsigned* v);     // 0xa80dd0 (thiscall on the vector)
};

// @ 0x00997b10
void VecPB::push_back(unsigned* v)
{
    unsigned* p = mEnd;
    if (p < mCap) {
        mEnd = p + 1;
        if (p != 0)
            *p = *v;
        return;
    }
    DoInsertValue(p, v);
}

// ---------------------------------------------------------------- 00997b60 ctor
struct Obj33 {
    char pad[0x18];
    void ctor();                                   // 0x997b60
    void clear();                                  // 0x997ba0
    void* ScalarDtor(unsigned flags);              // 0x997cc0
    int  GetSupportedTypes(unsigned* out, unsigned n); // 0x997d40
    bool CanConvert(int a, int id);                // 0x997d80
    int  Release();                                // 0x997d90
    void* ctor2();                                 // 0x997f30
};

// @ 0x00997b60
void Obj33::ctor()
{
    *(void**)((char*)this + 4) = (void*)0x13ef094;
    *(unsigned*)((char*)this + 8) = 0;
    *(void**)((char*)this + 0) = (void*)0x1446838;
    *(void**)((char*)this + 4) = (void*)0x1446834;
    *(unsigned*)((char*)this + 0xc) = 0;
    *(unsigned*)((char*)this + 0x10) = 0;
    *(unsigned*)((char*)this + 0x14) = 0;
}

// ---------------------------------------------------------------- 00997ba0 clear
// @ 0x00997ba0
void Obj33::clear()
{
    unsigned* p = *(unsigned**)((char*)this + 0xc);
    unsigned* end = *(unsigned**)((char*)this + 0x10);
    for (; p != end; p++) {
        void* o = (void*)*p;
        if (o)
            (*(void(__thiscall**)(void*))((char*)*(void**)o + 4))(o);
    }
    unsigned* a = *(unsigned**)((char*)this + 0xc);
    unsigned* b = *(unsigned**)((char*)this + 0x10);
    FUN_011e0744(a, b, 0);
    int n = (int)((char*)b - (char*)a) >> 2;
    n = -n;
    n = n + n;
    n = n + n;
    *(int*)((char*)this + 0x10) = (int)b + n;
}

// ---------------------------------------------------------------- 00997cc0 scalar deleting dtor
// @ 0x00997cc0
void* Obj33::ScalarDtor(unsigned flags)
{
    *(void**)((char*)this + 0) = (void*)0x1446838;
    *(void**)((char*)this + 4) = (void*)0x1446834;
    clear();
    int p = *(int*)((char*)this + 0xc);
    if (p != 0 && *(int*)(p - 4) != 0)
        FUN_00f47380((void*)p);
    *(void**)((char*)this + 4) = (void*)0x13ef094;
    *(void**)((char*)this + 0) = (void*)0x13eb938;
    if (flags & 1)
        FUN_00f47380(this);
    return this;
}

// ---------------------------------------------------------------- 00997d40 GetSupportedTypes
// @ 0x00997d40
int Obj33::GetSupportedTypes(unsigned* out, unsigned n)
{
    unsigned i = 0;
    if (n > 0) {
        do {
            if (i >= 6)
                break;
            out[i] = g_frameMapTypes[i];
            i++;
        } while (i < n);
    }
    return 6;
}

// ---------------------------------------------------------------- 00997d80 CanConvert
// @ 0x00997d80
bool Obj33::CanConvert(int a, int id)
{
    (void)a;
    return id == 0x19aef76;
}

// ---------------------------------------------------------------- 00997d90 Release
// @ 0x00997d90
int Obj33::Release()
{
    char* p = (char*)this + 0x28;
    volatile long* rc = (volatile long*)(p + 4);
    int n = _InterlockedExchangeAdd(rc, -1) - 1;
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        if (p != 0)
            (*(void(__thiscall**)(void*, int))((char*)*(void**)p + 8))(p, 1);
    }
    return n;
}

// ---------------------------------------------------------------- 00997dc0 ReadResource
// @ 0x00997dc0
bool ReadResource(char* self, char* p2, void* p3)
{
    int i2 = (*(int(__thiscall**)(char*))((char*)*(void**)self + 0x10))(self);
    unsigned ebx = *(unsigned*)(i2 + 4) - 0x2f7d0000;
    if (p2 == 0)
        return false;
    char* ebp = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)p2 + 0xc))(p2, 0xf074e1c8);
    if (ebp == 0)
        return false;
    int q = (*(int(__thiscall**)(char*))((char*)*(void**)self + 0x10))(self);
    int ca = *(int*)(q + 0);
    int cb = *(int*)(q + 4);
    int cc = *(int*)(q + 8);
    *(int*)(p2 + 8) = ca;
    *(int*)(p2 + 0xc) = (int)p3;
    *(int*)(p2 + 0x10) = cc;
    int local[2];
    FUN_0087cde0(local);
    int u = (*(int(__thiscall**)(char*))((char*)*(void**)self + 0x18))(self);
    if (!FUN_0087ce00((void*)u))
        return false;
    if (!FUN_0087d0b0((void*)(ebx + 0x0), local))
        return false;
    char* img = (char*)FUN_0087ced0(0);
    if (img == 0) {
        FUN_0087d070();
        return true;
    }
    int w = *(int*)(img + 0x10);
    int row = ((*(int*)(img + 0x18) + (*(int*)(img + 0x18) >> 31 & 7)) >> 3) * w;
    int h = *(int*)(img + 0x14);
    unsigned char* buf = (unsigned char*)FUN_00f473a0(h * row, "UTFWin/HitMaskImage", 0, 0, 0, 0);
    if (FUN_0087cf00(img, buf, row)) {
        if (*(int*)(img + 0x18) == 0x20)
            FUN_00957300(local, w, buf);
        else if (*(int*)(img + 0x18) == 8)
            FUN_00957230(local, w, buf);
    }
    FUN_00f47380(buf);
    FUN_0087cef0(img);
    FUN_0087d070();
    (void)cb;
    return true;
}

// ---------------------------------------------------------------- 00997f30 ctor
// @ 0x00997f30
void* Obj33::ctor2()
{
    unsigned char* p = (unsigned char*)this;
    *(void**)p = (void*)0x13effa8;
    _InterlockedExchange((volatile long*)(p + 4), 0);
    *(void**)p = (void*)0x1446894;
    return this;
}

extern "C" void* FUN_008de1a0(void);   // 0x8de1a0

// ---------------------------------------------------------------- 00997bf0 HitMaskBinder::Bind
// @ 0x00997bf0
bool FrameSet::Bind(int** a1, int id, int* a3)
{
    char* self = (char*)this;
    if (id == 0x3ff) {
        short* hdr = (short*)a1[0];
        if (*hdr == 0x13 && *(int*)(hdr + 2) == (int)0xf074e1c8) {
            void* o = FUN_008de1a0();
            int r = VF(o, 0x48, int(__thiscall*)(void*, int, int))(o, a3[1], 0x19aef76);
            if (r != 0) {
                struct Req { int a, b, c; };
                Req req = *(Req*)a3;
                req.b = 0x19aef76;
                int out = 0;
                char ok = VF(o, 0xc, char(__thiscall*)(void*, int*, int*, int, int, int, Req*))(o, a3, &out, 0, 0, r, &req);
                if (ok) {
                    *a1[1] = out;
                    unsigned v = (unsigned)out;
                    ((VecPB*)(self + 0xc))->push_back(&v);
                    return true;
                }
            }
        }
    }
    return false;
}
