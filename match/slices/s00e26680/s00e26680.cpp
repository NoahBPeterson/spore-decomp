// Slice s00e26680 -- eastl vector/erase helpers and cSPUIPosseItem bits.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------------------
// callees (call targets are relocation-masked by the checker)
// ---------------------------------------------------------------------------
void* FUN_00e24290(void*, void*, void*);         // 0x00e24290  eastl range move
void FUN_00e24310(void*, void*, void*, void*, void*); // 0x00e24310
void FUN_00f47380(void*);                        // 0x00f47380  operator delete[]

// ---------------------------------------------------------------------------
// eastl::vector<T> header (16 bytes used here; pool tag at +0x10)
// ---------------------------------------------------------------------------
struct EaVec {
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void* mpCapacity;            // +0x08
    void* mpUnused0c;            // +0x0c
    void* mpPool;                // +0x10

    void  resize(size_t n);                                   // 0x00e26ba0
    void* eraseAt(void* pos);                                 // 0x00e26bf0
    void  insertAt(void* pos, size_t n, const void* val);     // 0x00e25c30
    void  eraseRange(void* first, void* last);                // 0x00e25bd0
};

// ===========================================================================
// @ 0x00e26ba0
// ===========================================================================
void EaVec::resize(size_t n)
{
    if (n > (size_t)((void**)mpEnd - (void**)mpBegin)) {
        void* zero = 0;
        insertAt(mpEnd, n - (size_t)((void**)mpEnd - (void**)mpBegin), &zero);
    } else {
        eraseRange((void**)mpBegin + n, mpEnd);
    }
}

// ===========================================================================
// eastl vector of 8-byte (two ref-counted pointer) elements
// ===========================================================================
struct EaPair {                  // 8-byte element (two ref-counted pointers)
    void* mFirst;                // +0x00
    void* mSecond;               // +0x04
};

struct EaVec8 {
    void* mpBegin;               // +0x00
    void* mpEnd;                 // +0x04
    void* mpCapacity;            // +0x08
    void* mpUnused0c;            // +0x0c
    void* mpPool;                // +0x10

    void* eraseAt(void* pos);                                 // 0x00e26bf0
    void  insertRange(EaPair* first, EaPair* last, void* extra); // 0x00e27170
    void  insert(EaPair* pos, const EaPair* value);           // 0x00e26c80
    void  insertN(EaPair* pos, size_t count, const EaPair* value); // 0x00e26e50
    void  commit(void* first, void* last);                    // 0x00e23870
    void* grow(size_t n, void* first, void* last);            // 0x00e25ee0
};

// ===========================================================================
// @ 0x00e26bf0
// ===========================================================================
void* EaVec8::eraseAt(void* pos)
{
    if ((char*)pos + 8 < (char*)mpEnd)
        FUN_00e24290((char*)pos + 8, mpEnd, pos);

    mpEnd = (char*)mpEnd - 8;
    void** p = (void**)mpEnd;
    void* q1 = p[1];
    if (q1 != 0)
        ((void(__thiscall*)(void*)) (*(void***)q1)[4 / 4])(q1);
    void* q0 = p[0];
    if (q0 != 0)
        ((void(__thiscall*)(void*)) (*(void***)q0)[4 / 4])(q0);

    return pos;
}

// ===========================================================================
// @ 0x00e27170
// ===========================================================================
void EaVec8::insertRange(EaPair* first, EaPair* last, void* extra)
{
    size_t n = (size_t)(last - first);

    if (n > (size_t)((EaPair*)mpCapacity - (EaPair*)mpBegin)) {
        EaPair* p = (EaPair*)grow(n, first, last);
        commit(mpBegin, mpEnd);
        if (mpBegin != 0 && mpBegin != mpPool)
            FUN_00f47380(mpBegin);
        EaPair* e = p + n;
        mpBegin = p;
        mpEnd = e;
        mpCapacity = e;
        return;
    }

    unsigned int size = (unsigned int)((EaPair*)mpEnd - (EaPair*)mpBegin);
    if (n <= size) {
        EaPair* moved = (EaPair*)FUN_00e24290(first, last, mpBegin);
        commit(moved, mpEnd);
        mpEnd = moved;
        return;
    }

    EaPair* mid = first + size;
    FUN_00e24290(first, mid, mpBegin);
    void* t;
    FUN_00e24310(&t, mid, last, mpEnd, last);
    mpEnd = t;

    (void)extra;
}

// ===========================================================================
// SPUI UI-space / layout helpers
// ===========================================================================
char     g_1654c02;              // 0x01654c02  game-mode tag compared by pointer
float    g_016ac288;             // 0x016ac288  minimum window height

void* SP_GetCurrentGameMode();               // 0x00b5b800
void* SP_cTribeModeStrategy_Instance();      // 0x00cd40b0
void  FUN_00cca0a0();                        // 0x00cca0a0  thiscall
char  FUN_00cca090();                        // 0x00cca090  thiscall, returns char
void  EA_Audio_GetSystem();                  // 0x00e23250  thiscall, returns uint

struct cSPUILayout {
    void* FindWindowByID(uint32_t id, int a3);      // 0x008105b0
};

struct cSPUISpace {
    char        _p000[0x0a4];
    void*       mpBeginA4;               // +0x0a4
    void*       mpEndA8;                 // +0x0a8
    char        _p0ac[0x1bc - 0x0ac];
    cSPUILayout mLayout;                 // +0x1bc
    char        _p1c0[0x1f0 - 0x1c0];
    int         m1f0;                    // +0x1f0  total count
    int         m1f4;                    // +0x1f4  current count
    void*       mp1f8;                   // +0x1f8  caption text begin
    void*       mp1fc;                   // +0x1fc  caption text end

    void ToggleSelectedButton(bool flag);       // 0x00e26a90
    void UpdateCaption();                       // 0x00e26680
};

void  FUN_004c0530(void*, const wchar_t*, ...);   // 0x004c0530  swprintf-style helper
void  FUN_0057cb80(void*);                        // 0x0057cb80  eastl::fixed_string<wchar_t,16,1> dtor
void  SPUIHelpers_AnchorWindowToWindow(void*, void*);  // 0x00807340

// ---------------------------------------------------------------------------
// eastl vector growth/insert helpers used below
// ---------------------------------------------------------------------------
void* FUN_00f473a0(size_t, const char*, int, int, const char*, int);  // 0x00f473a0  operator new
void* FUN_00e23900(void*, void*, void*);      // 0x00e23900  uninitialised move
void* FUN_00e23950(void*, void*, void*);      // 0x00e23950
void  FUN_00e24370(void*, void*, void*);      // 0x00e24370  move_backward
void  FUN_00e24220(void*, void*, void*);      // 0x00e24220  range fill
void  FUN_00e238b0(void*, int, void*, int);   // 0x00e238b0  uninitialised fill
void  FUN_00e23e80();                         // 0x00e23e80  EaPair assign (thiscall)
EaPair* FUN_00e264b0(EaPair*, EaPair*);       // 0x00e264b0  partition
void  FUN_00e26530(EaPair*, EaPair*, EaPair*, void*);   // 0x00e26530  insertion sort

void* FUN_00e23ee0(void*, void*, void*, int); // 0x00e23ee0  lower_bound on cControlValue map
void* FUN_00b97140();                         // 0x00b97140  map insert (thiscall)
double FUN_009360d0();                        // 0x009360d0  random double (thiscall)

double   g_randMul;              // 0x01480fe8  = 29.0
double   g_randMax;              // 0x0140ba0  = 30.0
char     g_randRng;              // 0x01601760  RandomLinearCongruential object

// ===========================================================================
// @ 0x00e26680
// ===========================================================================
void cSPUISpace::UpdateCaption()
{
    void* w1 = mLayout.FindWindowByID(0x064a90a0, 1);
    if (w1 != 0)
        w1 = (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w1)[0xc / 4])(w1, 0x0f15f4bd);
    else
        w1 = 0;

    void* w2 = mLayout.FindWindowByID(0x0649a840, 1);
    if (w2 != 0)
        w2 = (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w2)[0xc / 4])(w2, 0x0f15f4bd);
    else
        w2 = 0;

    if (w1 == 0 || w2 == 0)
        return;

    float textH = g_016ac288;
    if ((int)(((char*)mp1fc - (char*)mp1f8) >> 1) != 0) {
        void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
        ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x80 / 4])(o, mp1f8);
        ((void(__thiscall*)(void*, int)) (*(void***)w1)[0x14 / 4])(w1, 0);
        o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
        float* r = (float*)((uint32_t(__thiscall*)(void*)) (*(void***)o)[0x38 / 4])(o);
        textH = r[2] - r[0];
    }

    int cur = m1f4;
    int tot = m1f0;
    if (tot > 0 && cur >= 0) {
        wchar_t buf[128];
        buf[0] = 0;
        FUN_004c0530(buf, L"%i/%i", cur, tot);

        void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
        ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x80 / 4])(o, buf);
        ((void(__thiscall*)(void*, int)) (*(void***)w2)[0x14 / 4])(w2, 0);

        void* o3 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
        ((void(__thiscall*)(void*)) (*(void***)o3)[0x38 / 4])(o3);
        FUN_0057cb80(buf);      // scratch eastl::fixed_string<wchar_t,16,1> destroyed
    }

    float on  = (textH <= 0.0f) ? 0.0f : 1.0f;
    void* o4 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
    ((void(__thiscall*)(void*, int, float)) (*(void***)o4)[0x7c / 4])(o4, 1, on);

    float on2 = (textH <= 0.0f) ? 0.0f : 1.0f;
    void* o5 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
    ((void(__thiscall*)(void*, int, float)) (*(void***)o5)[0x7c / 4])(o5, 1, on2);

    // Vertical stacking: when the total height of the two label rows exceeds the
    // available height the counter row is folded away and re-anchored above the
    // caption row.
    float rowH = m1f4 >= 0 ? textH : textH;
    if (0.0f < rowH + textH) {
        void* w3 = mLayout.FindWindowByID(0x03dae412, 1);
        void* b3 = (w3 == 0) ? 0
                 : (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w3)[0xc / 4])(w3, 0x8ed27e7a);
        float* pr = (float*)((uint32_t(__thiscall*)(void*)) (*(void***)w3)[0x38 / 4])(w3);
        float f12 = pr[1];

        float qa, qb, qc, qd;
        ((void(__thiscall*)(void*, float*, float*, float*, void*)) (*(void***)b3)[0x50 / 4])(b3, &qa, &qb, &qc, &qd);
        ((void(__thiscall*)(void*, float*, float*)) (*(void***)b3)[0x58 / 4])(b3, &qa, &qb);

        f12 = ((f12 + rowH) + on) + qc;
        if (f12 < g_016ac288)
            f12 = g_016ac288;

        float hh = textH - (f12 - (on2 - textH));
        ((void(__thiscall*)(void*, float, float)) (*(void***)w3)[0x70 / 4])(w3, hh, on2);
        ((void(__thiscall*)(void*, float*, float)) (*(void***)w3)[0x74 / 4])(w3, &qa, on2 - on);

        if (0.0f < qa) {
            void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
            ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x28 / 4])(o, w3);
            void* o2 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w1)[0x10 / 4])(w1);
            ((void(__thiscall*)(void*, void*, int)) (*(void***)o2)[0x70 / 4])(o2, w3, 0);
            SPUIHelpers_AnchorWindowToWindow(w3, w1);
        }
        if (0.0f < qb) {
            void* o = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
            ((void(__thiscall*)(void*, void*)) (*(void***)o)[0x28 / 4])(o, w3);
            void* o2 = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)w2)[0x10 / 4])(w2);
            ((void(__thiscall*)(void*, void*, int)) (*(void***)o2)[0x70 / 4])(o2, w3, 0);
            SPUIHelpers_AnchorWindowToWindow(w3, w2);
        }
    }
}

// ===========================================================================
// @ 0x00e26a90
// ===========================================================================
void cSPUISpace::ToggleSelectedButton(bool flag)
{
    if (flag && SP_GetCurrentGameMode() == (void*)&g_1654c02) {
        void* s = SP_cTribeModeStrategy_Instance();
        if (((uint32_t(__thiscall*)(void*)) (*(void***)s)[0x6c / 4])(s) != 0) {
            void* s2 = SP_cTribeModeStrategy_Instance();
            void* r = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)s2)[0x6c / 4])(s2);
            ((void(__thiscall*)(void*)) FUN_00cca0a0)(r);
            return;
        }
    }

    void* w = mLayout.FindWindowByID(0x03dae412, 1);
    if (w == 0)
        return;

    void* b = (void*)((uint32_t(__thiscall*)(void*, uint32_t)) (*(void***)w)[0xc / 4])(w, 0x8ed27e7a);
    if (b == 0)
        return;

    char cond;
    if (SP_GetCurrentGameMode() == (void*)&g_1654c02) {
        void* s = SP_cTribeModeStrategy_Instance();
        if (((uint32_t(__thiscall*)(void*)) (*(void***)s)[0x6c / 4])(s) == 0)
            goto other;

        void* s2 = SP_cTribeModeStrategy_Instance();
        void* r = (void*)((uint32_t(__thiscall*)(void*)) (*(void***)s2)[0x6c / 4])(s2);
        cond = ((char(__thiscall*)(void*)) FUN_00cca090)(r);
    } else {
        uint32_t n = (uint32_t)(((char*)mpEndA8 - (char*)mpBeginA4) >> 3);
        cond = (char)(((uint32_t(__thiscall*)(void*)) EA_Audio_GetSystem)(this) == n);
    }

    if (cond) {
        if (((unsigned char(__thiscall*)(void*)) (*(void***)b)[0x20 / 4])(b) & 4)
            return;
        ((void(__thiscall*)(void*, int, int)) (*(void***)b)[0x28 / 4])(b, 4, 1);
    } else {
    other:
        if (!(((unsigned char(__thiscall*)(void*)) (*(void***)b)[0x20 / 4])(b) & 4))
            return;
        ((void(__thiscall*)(void*, int, int)) (*(void***)b)[0x28 / 4])(b, 4, 0);
    }

    UpdateCaption();
}

// ===========================================================================
// @ 0x00e26c80
// ===========================================================================
void EaVec8::insert(EaPair* pos, const EaPair* value)
{
    EaPair* end = (EaPair*)mpEnd;
    if (end != (EaPair*)mpCapacity) {
        if (pos <= value && value < end)
            value = value + 1;

        if (end != 0) {
            void* a = end[-1].mFirst;
            end[0].mFirst = a;
            if (a != 0)
                ((void(__thiscall*)(void*)) (*(void***)a)[0])(a);
            void* b = end[-1].mSecond;
            end[0].mSecond = b;
            if (b != 0)
                ((void(__thiscall*)(void*)) (*(void***)b)[0])(b);
        }

        FUN_00e24370(pos, (char*)end - 8, end);
        ((void(__thiscall*)(void*, const EaPair*)) FUN_00e23e80)(pos, value);
        mpEnd = (char*)mpEnd + 8;
        return;
    }

    size_t n = (size_t)((EaPair*)end - (EaPair*)mpBegin);
    size_t newCap;
    if (n == 0)
        newCap = 1;
    else
        newCap = n * 2;

    EaPair* alloc = 0;
    if (newCap != 0)
        alloc = (EaPair*)FUN_00f473a0(newCap * 8, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);

    EaPair* p = (EaPair*)FUN_00e23900(mpBegin, pos, alloc);
    FUN_00e23950(mpBegin, pos, alloc);

    if (p != 0) {
        void* a = value->mFirst;
        p->mFirst = a;
        if (a != 0)
            ((void(__thiscall*)(void*)) (*(void***)a)[0])(a);
        void* b = value->mSecond;
        p->mSecond = b;
        if (b != 0)
            ((void(__thiscall*)(void*)) (*(void***)b)[0])(b);
    }

    EaPair* e = (EaPair*)FUN_00e23900(pos, mpEnd, p + 1);
    FUN_00e23950(pos, mpEnd, p + 1);

    if (mpBegin != 0 && mpBegin != mpPool)
        FUN_00f47380(mpBegin);

    mpBegin = alloc;
    mpEnd = e;
    mpCapacity = (char*)alloc + newCap * 8;
}

// ===========================================================================
// @ 0x00e26e50
// ===========================================================================
void EaVec8::insertN(EaPair* pos, size_t count, const EaPair* value)
{
    if (count > (size_t)((EaPair*)mpCapacity - (EaPair*)mpEnd)) {
        // Grow the buffer, then insert against the new storage.
        size_t size   = (size_t)((EaPair*)mpEnd - (EaPair*)mpBegin);
        size_t newCap = size * 2;
        if (size <= 0)
            newCap = 1;
        size_t total = size + count;
        if (newCap < total)
            newCap = total;

        EaPair* alloc = 0;
        if (newCap != 0)
            alloc = (EaPair*)FUN_00f473a0(newCap * 8, "Simulator", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);

        EaPair* p = (EaPair*)FUN_00e23900(mpBegin, pos, alloc);
        FUN_00e23950(mpBegin, pos, alloc);
        FUN_00e238b0(p, (int)count, (void*)value, (int)count);

        EaPair* e = (EaPair*)FUN_00e23900(pos, mpEnd, p + count);
        FUN_00e23950(pos, mpEnd, p + count);

        if (mpBegin != 0 && mpBegin != mpPool)
            FUN_00f47380(mpBegin);

        mpBegin    = alloc;
        mpEnd      = e;
        mpCapacity = (char*)alloc + newCap * 8;
        return;
    }

    if (count == 0)
        return;

    // Ref-counted scratch copy of *value (guards against self-insertion).
    EaPair tmp;
    tmp.mFirst = value->mFirst;
    if (tmp.mFirst != 0)
        ((void(__thiscall*)(void*)) (*(void***)tmp.mFirst)[0])(tmp.mFirst);
    tmp.mSecond = value->mSecond;
    if (tmp.mSecond != 0)
        ((void(__thiscall*)(void*)) (*(void***)tmp.mSecond)[0])(tmp.mSecond);

    EaPair* end   = (EaPair*)mpEnd;
    size_t  after = (size_t)(end - pos);

    if (count < after) {
        size_t  n   = count * 8;
        EaPair* mid = (EaPair*)((char*)end - n);
        void*   t;
        FUN_00e24310(&t, mid, end, end, mid);
        mpEnd = (char*)mpEnd + n;
        FUN_00e24370(pos, mid, end);
        FUN_00e24220(pos, (char*)pos + n, &tmp);
    } else {
        size_t extra = count - after;
        FUN_00e238b0(end, (int)extra, &tmp, (int)extra);
        mpEnd = (char*)mpEnd + extra * 8;
        void* t;
        FUN_00e24310(&t, pos, end, mpEnd, (void*)extra);
        mpEnd = (char*)mpEnd + after * 8;
        FUN_00e24220(pos, end, &tmp);
    }

    if (tmp.mSecond != 0)
        ((void(__thiscall*)(void*)) (*(void***)tmp.mSecond)[4 / 4])(tmp.mSecond);
    if (tmp.mFirst != 0)
        ((void(__thiscall*)(void*)) (*(void***)tmp.mFirst)[4 / 4])(tmp.mFirst);
}

// ===========================================================================
// @ 0x00e27060
// ===========================================================================
void FUN_00e27060(EaPair* first, EaPair* last, int depth, char (*cmp)(const EaPair&, const EaPair&))
{
    size_t size = (size_t)((char*)last - (char*)first) & 0xfffffff8;

    for (;;) {
        if (size < 0xe1 || depth < 1) {
            if (depth == 0)
                FUN_00e26530(first, last, last, (void*)cmp);
            return;
        }

        EaPair* mid = first + (size / 8) / 2;
        EaPair* p;

        if (cmp(*first, *mid)) {
            if (cmp(*last, *(last - 1))) {
                p = mid;
            } else if (cmp(*first, *(last - 1))) {
                p = last - 1;
            } else {
                p = first;
            }
        } else {
            if (cmp(*first, *(last - 1)) == 0) {
                p = first;
            } else if (cmp(*mid, *(last - 1))) {
                p = last - 1;
            } else {
                p = mid;
            }
        }

        // Move the pivot out of the way (ref-counted copy into a temporary).
        EaPair tmp;
        tmp.mFirst = p->mFirst;
        if (tmp.mFirst != 0)
            ((void(__thiscall*)(void*)) (*(void***)tmp.mFirst)[0])(tmp.mFirst);
        tmp.mSecond = p->mSecond;
        if (tmp.mSecond != 0)
            ((void(__thiscall*)(void*)) (*(void***)tmp.mSecond)[0])(tmp.mSecond);

        EaPair* split = FUN_00e264b0(first, last);

        FUN_00e27060(split, last, depth - 1, cmp);

        last = split;
        size = (size_t)((char*)split - (char*)first) & 0xfffffff8;
        if (size <= 0xe0) {
            if (depth - 1 == 0)
                FUN_00e26530(first, last, last, (void*)cmp);
            return;
        }
    }
}

// ===========================================================================
// cSPUIPosseItem control-value map
// ===========================================================================
struct cControlValue {                 // value half of the map's pair<>
    float    value;                    // +0x04
    uint8_t  percentage;               // +0x08
    uint8_t  setDistress;              // +0x09
    char     _p0a[2];
    uint32_t updateTick;               // +0x0c
};

struct ControlValueMap {
    void*   mpBegin;                   // +0x00
    void*   mpEnd;                     // +0x04
    void*   mpCapacity;                // +0x08
    char    _p0c[0x14 - 0x0c];
    uint8_t mPoolTag;                  // +0x14
};

struct cSPUIPosseItem {
    char            _p000[0x0ac];
    int32_t         mDistress[3];      // +0x0ac
    char            _p0b8[0x124 - 0x0b8];
    ControlValueMap mControlValues;    // +0x124

    uint8_t SetControlValue(uint32_t id, float value, bool percentage, bool setDistress);  // 0x00e27230
};

// ===========================================================================
// @ 0x00e27230
// ===========================================================================
uint8_t cSPUIPosseItem::SetControlValue(uint32_t id, float value, bool percentage, bool setDistress)
{
    uint32_t key = id;
    void*    end = mControlValues.mpEnd;

    void* it = FUN_00e23ee0(mControlValues.mpBegin, end, &key, mControlValues.mPoolTag);
    if (it == end || id < *(uint32_t*)it)
        it = ((void*(__thiscall*)(ControlValueMap*, void*, uint32_t*)) FUN_00b97140)(&mControlValues, it, &key);

    cControlValue* cv = (cControlValue*)((char*)it + 4);
    cv->value       = value;
    cv->percentage  = percentage ? 1 : 0;
    cv->setDistress = setDistress ? 1 : 0;

    if (cv->updateTick == 0) {
        double r  = ((double(__thiscall*)(void*)) FUN_009360d0)(&g_randRng);
        double t  = r * g_randMul + 1.0;
        double mx = g_randMax;
        if (mx <= t)
            r = mx;
        else if (1.0 <= t)
            r = t;
        else
            r = 1.0;
        cv->updateTick = (uint32_t)(mDistress[2] + (int)(float)r);
    }

    return 1;
}