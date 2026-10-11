// Slice s00969e30 -- EA::UTFWinControls::ConsoleWindow (scrollable console text control)
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "types.h"

extern "C" uint32_t __cdecl FNV1_String8(const char*, uint32_t, uint32_t);  // 0x932e80

struct Sub {                                   // sub-objects inside ConsoleWindow
    void m_967690();                           // 0x967690
    void m_9676f0(void*, int);                 // 0x9676f0
};

struct CW {
    void InvalidateLayout();                   // 0x9609b0  Window::InvalidateLayout
    void m_969d40();                           // 0x969d40
    int  BaseDoMessage(int);                   // 0x950bb0  Window::DoMessage
    __declspec(noinline) void Refresh(char);   // 0x969e30
    void ResetLayout();                        // 0x969ed0
    int  DoMessageProc(int);                   // 0x969f00
    int  Scroll(int, int, char, int);          // 0x969f80
    int  Init();                               // 0x96a670
    void Clear();                              // 0x96ab30
    void Find(int*, void**);                   // 0x96ab90
    void Destroy();                            // 0x96ac10
    void SetRegion(void*);                     // 0x96acd0
};

// @ 0x96a620
void* __cdecl DoFindNode(void* node, void** pkey, uint32_t)
{
    if (node == 0)
        return 0;
    const char* key = (const char*)*pkey;
    for (;;) {
        const char* s = *(const char**)node;
        int r;
        for (;;) {
            unsigned char x = (unsigned char)s[0];
            unsigned char y = (unsigned char)key[0];
            if (x != y) { r = (x < y) ? -1 : 1; break; }
            if (x == 0) { r = 0; break; }
            x = (unsigned char)s[1];
            y = (unsigned char)key[1];
            if (x != y) { r = (x < y) ? -1 : 1; break; }
            s += 2;
            key += 2;
            if (x == 0) { r = 0; break; }
        }
        if (r == 0)
            return node;
        node = *(void**)((char*)node + 8);
        if (node == 0)
            return 0;
    }
}

// @ 0x969e30
void CW::Refresh(char force)
{
    if (*(int*)((char*)this + 0x864) != 0) {
        float dx = ((*(float*)((char*)this + 0x94) - *(float*)((char*)this + 0x8c))
                  - *(float*)((char*)this + 0x850)) - *(float*)((char*)this + 0x858);
        int iVar2 = (int)dx;
        int iVar1 = *(int*)((char*)this + 0x228);
        int* p = *(int**)((char*)this + 0x864);
        (*(void(__thiscall**)(int*, int, int))((char*)*p + 0x34))(p, iVar1, 1);
        (*(void(__thiscall**)(int*, int, int))((char*)*p + 0x3c))(p, iVar2, 1);
        (*(void(__thiscall**)(int*, int, int))((char*)*p + 0x24))(p, (iVar1 - iVar2) - *(int*)((char*)this + 0x224), 0);
    }
    if (force != 0) {
        void* p2 = (char*)this + 4;
        (*(void(__thiscall**)(void*))((char*)*(void**)p2 + 0x90))(p2);
    }
}

// @ 0x969ed0
void CW::ResetLayout()
{
    ((CW*)this)->InvalidateLayout();
    CW* base = (CW*)((char*)this - 4);
    base->m_969d40();
    base->Refresh(0);
    *(char*)((char*)this + 0x85d) = 1;
}

// @ 0x969f00
int CW::DoMessageProc(int msg)
{
    if (*(int*)(msg + 8) != (int)0x8ef0c8dd)
        return BaseDoMessage(msg);
    if (*(char*)((char*)this + 0x868) != 0) {
        int* p = *(int**)((char*)this + 0x864);
        int iVar3 = (*(int(__thiscall**)(int*))((char*)*p + 0x28))(p);
        int iVar4 = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p);
        iVar4 -= iVar3;
        iVar4 -= (*(int(__thiscall**)(int*))((char*)*p + 0x40))(p);
        *(int*)((char*)this + 0x224) = iVar4;
        if (iVar4 < 0)
            *(int*)((char*)this + 0x224) = 0;
        void* p2 = (char*)this + 4;
        (*(void(__thiscall**)(void*))((char*)*(void**)p2 + 0x90))(p2);
    }
    return 1;
}

// @ 0x969f80
int CW::Scroll(int, int, char flags, int amount)
{
    int* p = *(int**)((char*)this + 0x864);
    int iVar2 = (*(int(__thiscall**)(int*))((char*)*p + 0x40))(p);
    int iVar3 = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p);
    if (iVar2 < iVar3) {
        int v = amount;
        if (flags & 1) v += v;
        if (flags & 2) v += v;
        if (flags & 4) v += v;
        int q = *(int*)((char*)this + 0x228) / *(int*)((char*)this + 0x234);
        float prod = (float)(unsigned)q * (float)v * *(float*)0x13eb960;
        int add = (int)prod;
        *(int*)((char*)this + 0x224) += add;

        float dx = ((*(float*)((char*)this + 0x94) - *(float*)((char*)this + 0x8c))
                  - *(float*)((char*)this + 0x850)) - *(float*)((char*)this + 0x858);
        int iVar4 = (int)dx;
        if (*(int*)((char*)this + 0x224) < 0) {
            *(int*)((char*)this + 0x224) = 0;
            ((CW*)this)->Refresh(1);
            return 1;
        }
        int lim = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p) - iVar4;
        if (*(int*)((char*)this + 0x224) > lim) {
            int lim2 = (*(int(__thiscall**)(int*))((char*)*p + 0x38))(p) - iVar4;
            *(int*)((char*)this + 0x224) = lim2;
        }
        ((CW*)this)->Refresh(1);
    }
    return 1;
}

// @ 0x96ab30
void CW::Clear()
{
    void** base = (void**)((char*)this + 0x22c);
    void** p = (void**)*(void**)((char*)this + 0x22c);
    while (p != base) {
        void** n = (void**)*p;
        p[1] = 0;
        *p = 0;
        p = n;
    }
    base[1] = base;
    base[0] = base;
    ((Sub*)((char*)this + 0x20c))->m_967690();
    *(int*)((char*)this + 0x228) = 0;
    *(int*)((char*)this + 0x224) = 0;
    *(int*)((char*)this + 0x234) = 0;
    ((CW*)this)->Refresh(1);
}

// @ 0x96ab90
void CW::Find(int* out, void** pkey)
{
    uint32_t h = FNV1_String8((const char*)*pkey, 0x811c9dc5, 0);
    uint32_t nbuckets = *(uint32_t*)((char*)this + 8);
    int* buckets = *(int**)((char*)this + 4);
    int* slot = buckets + (h % nbuckets);
    int found = (int)DoFindNode((void*)*slot, pkey, h);
    int v0, v1;
    if (found != 0) {
        v0 = found;
        v1 = (int)slot;
    } else {
        int* endslot = buckets + nbuckets;
        v0 = *endslot;
        v1 = (int)endslot;
    }
    out[0] = v0;
    out[1] = v1;
}

// @ 0x96acd0
void CW::SetRegion(void* p)
{
    ((CW*)this)->Clear();
    *(void**)((char*)this + 0x220) = p;
    ((Sub*)((char*)this + 0x20c))->m_9676f0(p, 0);
}

// @ 0x96ac10  (best-effort destructor)
void CW::Destroy()
{
    *(void**)this = (void*)0x1441c18;
    *(void**)((char*)this + 4) = (void*)0x1441af8;
    ((CW*)this)->Clear();
    void* sm = ((void*(__cdecl*)(int))0x885bd0)(1);
    if (sm != 0)
        (*(void(__thiscall**)(void*, uint32_t))((char*)*(void**)sm + 0))(sm, 0xefe945b2);
    int* p = *(int**)((char*)this + 0x864);
    if (p != 0)
        (*(void(__thiscall**)(int*))((char*)*p + 4))(p);
    ((Sub*)((char*)this + 0x788))->m_967690();
    ((Sub*)((char*)this + 0x258))->m_967690();
    ((Sub*)((char*)this + 0x238))->m_9676f0(*(void**)((char*)this + 0x240), *(int*)((char*)this + 0x23c));
    ((Sub*)((char*)this + 0x22c))->m_967690();
    ((Sub*)((char*)this + 0x20c))->m_967690();
    ((CW*)this)->m_969d40();
}

// @ 0x96a670  (approximate)
int CW::Init()
{
    return 0;
}

// @ 0x96a790  (approximate)
int __cdecl FUN_0096a790(int, int, int, int)
{
    return 0;
}

// @ 0x96a0a0  (approximate)
int __cdecl FUN_0096a0a0(int, int, int, int)
{
    return 0;
}

// @ 0x96a860  (approximate)
int __cdecl FUN_0096a860(int, int, int)
{
    return 0;
}

// @ 0x96a9b0  (approximate)
int __cdecl FUN_0096a9b0(int, int, int)
{
    return 0;
}
