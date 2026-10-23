// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Slice s00e48bb0: SPUI space / editor verb-icon panel support code.
//   shutdown, recursive init, property load, child layout, panel refresh,
//   and the small block-vector helpers around it.
#include "types.h"

// ---------------------------------------------------------------- types
typedef uint32_t u32;
typedef unsigned char u8;

struct Key3 { u32 a, b, c; };
struct V2 { float x, y; };

// cSPUILayout: refcount at vtable +0/+4/+8 plus layout services.
struct CSpuiLayout {
    void Shutdown(u32 flag);                                     // 0x811ad0
    bool Init(const Key3* k, int a, u32 b);                      // 0x8120d0
    bool SetParentWin(void* w, int a, u32 b);                    // 0x8121b0
    void SetReloadCallback(void (*fn)(void*, void*), void* self); // 0x810090
};

struct LayoutRef { CSpuiLayout* p; void Set(CSpuiLayout*); };    // 0x572620

// generic virtual-call helpers
typedef void   (__thiscall *VF0)(void*);
typedef void   (__thiscall *VF1)(void*, int);
typedef void   (__thiscall *VF2)(void*, int, int);
typedef void   (__thiscall *VF3)(void*, int, int, int);
typedef char   (__thiscall *VFC2)(void*, int, void*);
typedef char   (__thiscall *VFC3)(void*, int, void*, void*);
typedef float* (__thiscall *VFR0)(void*);

#define VTP(p) (*(void***)(p))
#define CALL0(p, i)           ((VF0)VTP(p)[(i)])((void*)(p))
#define CALL1(p, i, a)        ((VF1)VTP(p)[(i)])((void*)(p), (int)(a))
#define CALL2(p, i, a, b)     ((VF2)VTP(p)[(i)])((void*)(p), (int)(a), (int)(b))
#define CALL3(p, i, a, b, c)  ((VF3)VTP(p)[(i)])((void*)(p), (int)(a), (int)(b), (int)(c))
#define CALLG2(p, i, a, b)    ((VFC2)VTP(p)[(i)])((void*)(p), (int)(a), (void*)(b))
#define CALLG3(p, i, a, b, c) ((VFC3)VTP(p)[(i)])((void*)(p), (int)(a), (void*)(b), (void*)(c))
#define CALLR0(p, i)          ((VFR0)VTP(p)[(i)])((void*)(p))

// A plain pointer slot that can release its value through vtable slot 1.
struct PtrSlot {
    void* p;
    void Release()
    {
        if (p) {
            void* q = p;
            p = 0;
            CALL0(q, 1);
        }
    }
};

struct PtrVec { void* begin; void* end; void* cap; void Erase(void*, void*); };  // 0xe25bd0
struct SpVecF { float* begin; float* end; float* cap; void resize(int); };      // 0x4afc80

// ---------------------------------------------------------------- externals
void* __cdecl EAAllocate(u32 size, const char* name, int a, int b,
                         const char* file, int line);            // 0xf473a0
void  __cdecl operator_delete(void* p);                          // 0xf47380
void* __cdecl VecInsert(void* dst, const void* src, u32 n);      // 0x11e0744
void* __cdecl memmove_(void* d, const void* s, u32 n);
void* __cdecl PropertyManager();                                 // 0x67de30
void* __cdecl MessageServer();                                   // 0x67dcc0
void* __cdecl GetGlobal();                                       // 0xb3d410
void* __fastcall LayoutCtor(void* p);                             // 0x810000
void  __cdecl FillKey(void* a, int b, void* out);                // 0xe39420
void  __cdecl SetImageOnWin(void* w, void* img, int idx);        // 0x8068d0
bool  __cdecl GetPropertyAsKeyInstance(void* p, u32 id, void* out); // 0x6a12a0
bool  __cdecl GetPropertyAsText(void* p, u32 id, void* out);     // 0x6a1360
void  __cdecl FormatNum(double v, void* buf, int n, const wchar_t* fmt, int x); // 0x8822e0
void  __cdecl ReloadCB(void* a, void* b);                        // 0xe48da0

extern "C" u32 g_015a5b30;

struct Prop {
    float* GetFloat();                                           // 0x41ea70
    u32*   GetUInt();                                            // 0x41ea00
    int*   GetInt();                                             // 0x41e990
};
struct CString {
    u32 d[5];
    void ctor();                                                 // 0x6b5060
    void dtor();                                                 // 0x6b5240
    const wchar_t* GetText();                                    // 0x6b55c0
};
struct Timeline {
    void FUN_00e46600(void* key, int a, int b, int c);           // 0xe46600
    void FUN_00e46d80(float a, float b, int c, float d, float e, int f); // 0xe46d80
};
struct TexWrap {
    int GetWidth(int h);                                         // 0x8332a0
    int GetHeight(float a, float b, float c, float d, int e);    // 0x8332d0
};
struct ImageObj {
    void* Construct(void* src, int w, int h);                    // 0x9579f0
};
struct ImageBase {
    ImageBase* Construct(void* parent);                          // 0x8333b0
};
struct AbilHost {
    void SetVehicle(Key3 k);                                     // 0x59ece0
    void LayoutAbilitiesCompact(void* obj, int b, void* out);    // 0x5a1920
};
struct KeyMgr { void* Resolve(void* key); };                     // 0xe3ec20
struct LayoutObj { void* GetF1(void* out, void* child); };       // 0xe40010

struct C;

struct C {
    void Shutdown();                                             // 0xe48bb0
    void Setup();                                                // 0xe48dc0
    void Load(int a, int b, int c, int d);                       // 0xe48eb0
    void SetOwner(int a, int b, int c, int d);                   // 0xe48f30
    void ShutdownRecursive();                                    // 0xe48f60
    void LayoutChildren(void* v2, int a, int b, float f);        // 0xe48fa0
    void Close();                                                // 0xe492d0
    void SetX(void* p);                                          // 0xe49360
    void RefreshBig(int a, int b, int c);                        // 0xe493c0
    void LoadParams();                                           // 0xe496d0
    void RefreshUI();                                            // 0xe47930
    void SetVisibleRecursive(u8 vis);                            // 0xe46020
};

// ======================================================================
// 0xe48bb0   cSPUISpace::Shutdown
// ======================================================================
// @ 0x00e48bb0 C::Shutdown
void C::Shutdown()
{
    *(u8*)((char*)this + 0x6d) = 0;

    void* p = *(void**)((char*)this + 0x98);
    if (p) {
        CALL0(p, 8);
        if (*(void**)((char*)this + 0x98)) {
            *(void**)((char*)this + 0x98) = 0;
            CALL0(p, 1);
        }
    }

    p = *(void**)((char*)this + 0x9c);
    if (p) {
        CALL0(p, 2);
        p = *(void**)((char*)this + 0x9c);
        if (p) {
            *(void**)((char*)this + 0x9c) = 0;
            CALL0((char*)p + 0x10, 1);
        }
    }

    p = *(void**)((char*)this + 0xa4);
    if (p) {
        CALL0(p, 10);
        if (*(void**)((char*)this + 0xa4)) {
            *(void**)((char*)this + 0xa4) = 0;
            CALL0(p, 1);
        }
    }

    p = *(void**)((char*)this + 0xa0);
    if (p) {
        CALL0(p, 5);
        if (*(void**)((char*)this + 0xa0)) {
            *(void**)((char*)this + 0xa0) = 0;
            CALL0(p, 1);
        }
    }

    p = *(void**)((char*)this + 0x20);
    if (p) {
        CALL1(p, 0x42, this);
        if (*(void**)((char*)this + 0x20)) {
            *(void**)((char*)this + 0x20) = 0;
            CALL0(p, 1);
        }
    }

    CSpuiLayout* lay = *(CSpuiLayout**)((char*)this + 0x10);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0x10);
        if (lay) {
            *(void**)((char*)this + 0x10) = 0;
            CALL0(lay, 2);
        }
    }

    lay = *(CSpuiLayout**)((char*)this + 0x14);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0x14);
        if (lay) {
            *(void**)((char*)this + 0x14) = 0;
            CALL0(lay, 2);
        }
    }

    lay = *(CSpuiLayout**)((char*)this + 0xc);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0xc);
        if (lay) {
            *(void**)((char*)this + 0xc) = 0;
            CALL0(lay, 2);
        }
    }

    int n = (*(int**)((char*)this + 0x40) - *(int**)((char*)this + 0x3c));
    for (int i = 0; i < n; i++) {
        void* e = (void*)(*(int**)((char*)this + 0x3c))[i];
        CALL0(e, 9);
    }
    {
        PtrVec* v = (PtrVec*)((char*)this + 0x3c);
        v->Erase(v->begin, v->end);
    }
    {
        PtrVec* v = (PtrVec*)((char*)this + 0x28);
        v->Erase(v->begin, v->end);
    }

    // Re-append the 12-byte triple vector to itself (matches the inlined copy).
    {
        char* b = *(char**)((char*)this + 0x50);
        char* e = *(char**)((char*)this + 0x54);
        char* d = b;
        char* s = e;
        if (s != e) {
            do {
                *(int*)(d + 0) = *(int*)(s + 0);
                *(int*)(d + 4) = *(int*)(s + 4);
                *(int*)(d + 8) = *(int*)(s + 8);
                d += 12; s += 12;
            } while (s != e);
        }
        int cnt = (int)(e - b) / 12;
        *(char**)((char*)this + 0x54) = e + cnt * 12;
    }

    int n2 = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    for (int i = 0; i < n2; i++) {
        C* child = (C*)(*(int**)((char*)this + 0xc0))[i];
        child->Shutdown();
    }
}

// ======================================================================
// 0xe48dc0   build the layout, then recurse into children
// ======================================================================
// @ 0x00e48dc0 C::Setup
void C::Setup()
{
    if (!*(u8*)((char*)this + 0x6d)) {
        if (*(void**)((char*)this + 0x1c) && *(void**)((char*)this + 0x18)) {
            void* mem = EAAllocate(0x18, (const char*)0x13f6b3c, 0, 0, 0, 0);
            CSpuiLayout* lay = mem ? (CSpuiLayout*)LayoutCtor(mem) : 0;
            ((LayoutRef*)((char*)this + 0xc))->Set(lay);

            Key3 k;
            k.a = *(u32*)((char*)this + 0x18);
            k.b = 0x510a95b;
            k.c = g_015a5b30;
            (*(CSpuiLayout**)((char*)this + 0xc))->Init(&k, 1, 0x5b598fa);
            (*(CSpuiLayout**)((char*)this + 0xc))->SetParentWin(
                *(void**)((char*)this + 0x1c), 1, 0x5b598fa);
            (*(CSpuiLayout**)((char*)this + 0xc))->SetReloadCallback(&ReloadCB, this);
            RefreshUI();
        }
        *(u8*)((char*)this + 0x6d) = 1;
    }

    int n = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    for (int i = 0; i < n; i++) {
        C* child = (C*)(*(int**)((char*)this + 0xc0))[i];
        child->Setup();
    }
    SetVisibleRecursive(*(u8*)((char*)this + 0x6c));
}

// ======================================================================
// 0xe48eb0   load a property list and forward to the timeline
// ======================================================================
// @ 0x00e48eb0 C::Load
void C::Load(int a, int b, int c, int d)
{
    void* pm = PropertyManager();
    void** slot = (void**)((char*)this + 0x64);
    void* old = *slot;
    if (old) {
        *slot = 0;
        CALL0(old, 1);
    }
    CALLG3(pm, 11, b, (int)0xe1d7164f, slot);
    GetPropertyAsKeyInstance(*slot, 0x91ad064, (void*)((char*)this + 0xe4));
    void* k = *(void**)((KeyMgr*)a)->Resolve((void*)((char*)this + 0xe4));
    ((Timeline*)this)->FUN_00e46600(k, b, c, d);
}

// ======================================================================
// 0xe48f30   set the owner key, then reload properties
// ======================================================================
// @ 0x00e48f30 C::SetOwner
void C::SetOwner(int a, int b, int c, int d)
{
    *(int*)((char*)this + 0xa8) = b;
    if (b) {
        b = *(int*)(*(int*)(b + 0xc));
        *(int*)((char*)this + 0x68) = b;
        Load(a, b, c, d);
        return;
    }
}

// ======================================================================
// 0xe48f60   recursive shutdown
// ======================================================================
// @ 0x00e48f60 C::ShutdownRecursive
void C::ShutdownRecursive()
{
    Shutdown();
    int n = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    for (int i = 0; i < n; i++) {
        C* child = (C*)(*(int**)((char*)this + 0xc0))[i];
        child->ShutdownRecursive();
    }
}

// ======================================================================
// 0xe48fa0   lay the children out along the panel edge
// ======================================================================
// @ 0x00e48fa0 C::LayoutChildren
void C::LayoutChildren(void* v2, int a, int b, float f)
{
    int count = (*(int**)((char*)this + 0xc4) - *(int**)((char*)this + 0xc0));
    if (count <= 0)
        return;
    if (!GetGlobal())
        return;

    float limit = *(float*)((char*)this + 0x70) + f;
    float pos = f;
    float avail = 0.0f;
    if (*(void**)((char*)this + 0x1c)) {
        float* r = CALLR0(*(void**)((char*)this + 0x1c), 14);
        avail = r[3] - r[1];
    }

    int used1 = 0, used2 = 0;

    SpVecF vec;
    vec.begin = 0;
    vec.end = 0;
    vec.cap = 0;
    vec.resize(count);

    if (count > 0) {
        int i = 0;
        do {
            C* ch = (C*)(*(int**)((char*)this + 0xc0))[i];
            float off = 0.0f;
            if (*(u32*)((char*)ch + 0x68) != 0x6701aff5 && *(void**)((char*)ch + 0xa8)) {
                Key3 kk;
                kk.a = kk.b = kk.c = 0;
                FillKey(*(void**)((char*)ch + 0xa8), 0x10, &kk);

                void* props = 0;
                void* pm = PropertyManager();
                if (props) { props = 0; CALL0(props, 1); }
                CALLG3(pm, 11, kk.a, kk.c, &props);

                int kind = 0;
                if (props) {
                    void* pr = 0;
                    if (CALLG2(props, 9, 0x1ef3be2, &pr) &&
                        *(short*)((char*)pr + 0x12) == 9) {
                        kind = *((Prop*)pr)->GetInt();
                    }
                }

                V2 sz;
                sz.x = sz.y = 0.0f;
                ((LayoutObj*)GetGlobal())->GetF1(&sz, ch);
                float s = sz.y;

                if (kind == 1) {
                    float t = (float)used1 + 0.5f;
                    used1++;
                    limit = (float)used1 * s + *(float*)((char*)this + 0x70) + f;
                    off = t * s + *(float*)((char*)this + 0x70) * 0.5f;
                } else {
                    off = (*(float*)((char*)this + 0x70) * -0.5f - s * 0.5f) - (float)used2 * s;
                    used2++;
                    pos = f - (float)used2 * s;
                }

                if (props) CALL0(props, 1);
            }
            vec.begin[i] = off;
            i++;
        } while (i < count);
    }

    float delta = 0.0f;
    if (!(0.0f <= pos)) {
        delta = -pos;
    } else if (limit > avail) {
        delta = avail - limit;
    }

    if (count > 0) {
        int i = 0;
        do {
            C* ch = (C*)(*(int**)((char*)this + 0xc0))[i];
            float o = vec.begin[i] + delta;
            ((Timeline*)ch)->FUN_00e46d80(((V2*)v2)->x, ((V2*)v2)->y,
                                          b, 0.0f, o, 1);
            i++;
        } while (i < count);
    }

    if (vec.begin && ((int*)vec.begin)[-1])
        operator_delete(vec.begin);
}

// ======================================================================
// 0xe492d0   close the space / detach from the message server
// ======================================================================
// @ 0x00e492d0 C::Close
void C::Close()
{
    void* ms = MessageServer();
    CALL3(ms, 11, this, 0xf62def, 0xffffd8f1);

    void* p = *(void**)((char*)this + 0x90);
    if (p) {
        CALL1(p, 0, 1);
        *(void**)((char*)this + 0x90) = 0;
    }

    p = *(void**)((char*)this + 0x14);
    if (p) {
        CALL0(p, 5);
        p = *(void**)((char*)this + 0x14);
        if (p) {
            *(void**)((char*)this + 0x14) = 0;
            CALL0(p, 2);
        }
    }

    CSpuiLayout* lay = *(CSpuiLayout**)((char*)this + 0x10);
    if (lay) {
        lay->Shutdown(1);
        lay = *(CSpuiLayout**)((char*)this + 0x10);
        if (lay) {
            *(void**)((char*)this + 0x10) = 0;
            CALL0(lay, 2);
        }
    }
}

// ======================================================================
// 0xe49360   assign the +0x18 interface and track visibility
// ======================================================================
// @ 0x00e49360 C::SetX
void C::SetX(void* p)
{
    if (!p) {
        void* o = *(void**)((char*)this + 0x18);
        if (o) {
            *(void**)((char*)this + 0x18) = 0;
            CALL0(o, 1);
        }
        *(u8*)((char*)this + 0xc) = 1;
        return;
    }
    void* o = *(void**)((char*)this + 0x18);
    if (p != o) {
        CALL0(p, 0);
        *(void**)((char*)this + 0x18) = p;
        if (o)
            CALL0(o, 1);
    }
    *(u8*)((char*)this + 0xc) = 0;
}

// ======================================================================
// 0xe493c0   big panel refresh
// ======================================================================
// @ 0x00e493c0 C::RefreshBig
void C::RefreshBig(int p2, int p3, int p4)
{
    void* mem = EAAllocate(0x14, (const char*)0x13f6b3c, 0, 0, 0, 0);
    ImageBase* base = mem ? ((ImageBase*)mem)->Construct(*(void**)((char*)this + 0x1c)) : 0;

    mem = EAAllocate(0x2c, "UI/Image", 0, 0, 0, 0);
    ImageObj* img = 0;
    if (mem) {
        int h = ((TexWrap*)base)->GetHeight(0.0f, 0.0f, 1.0f, 1.0f, 0);
        int w = ((TexWrap*)base)->GetWidth(h);
        img = (ImageObj*)((ImageObj*)mem)->Construct(base, w, h);
        if (img)
            CALL0(img, 0);
    }
    SetImageOnWin(*(void**)((char*)this + 0x2c), img, -1);

    void* props = 0;
    void* pm = PropertyManager();
    if (props) { props = 0; CALL0(props, 1); }
    CALLG3(pm, 11, p2, p4, &props);

    if (props) {
        if (*(void**)((char*)this + 0x24)) {
            CString s;
            s.ctor();
            GetPropertyAsText(props, 0x8f6fc401, &s);
            void* w = *(void**)((char*)this + 0x24);
            CALL1(w, 0x20, s.GetText());
            s.dtor();
        }
        if (*(void**)((char*)this + 0x28)) {
            int n = 0;
            void* pr = 0;
            if (CALLG2(props, 9, 0x2166464, &pr) &&
                *(short*)((char*)pr + 0x12) == 9) {
                n = *((Prop*)pr)->GetInt();
            }
            wchar_t buf[0x30];
            *(short*)buf = 0;
            if (n != 0)
                FormatNum((double)n, buf, 0x28, L"%-F%-p", 0x268b);
            CALL1(*(void**)((char*)this + 0x28), 0x20, buf);
        }
        CALL1(*(void**)((char*)this + 0x30), 0x1b, (char*)this + 0x64);

        Key3 k;
        k.a = (u32)p2;
        k.b = (u32)p3;
        k.c = (u32)p4;
        ((AbilHost*)*(void**)((char*)this + 0x14))->SetVehicle(k);

        u32 out = 0;
        ((AbilHost*)*(void**)((char*)this + 0x14))->LayoutAbilitiesCompact(
            *(void**)((char*)this + 0x30), 0, &out);

        bool flag = *(u32*)((char*)this + 0xa0) < out;
        CALL2(*(void**)((char*)this + 0x34), 0x1f, 1, flag);

        float* r = CALLR0(*(void**)((char*)this + 0x30), 14);
        float y0 = *(float*)((char*)this + 0x78);
        float x0 = *(float*)((char*)this + 0x74);
        float y1 = *(float*)((char*)this + 0x7c);
        float rx = (r[2] - r[0]) + *(float*)((char*)this + 0x84);
        if (y1 - x0 < rx)
            y1 = rx + x0;
        float ry = ((r[3] - r[1]) -
                    (*(float*)((char*)this + 0x70) - *(float*)((char*)this + 0x68))) +
                   (*(float*)((char*)this + 0x80) - *(float*)((char*)this + 0x78)) + y0;
        float box[4] = { x0, y0, y1, ry };
        if (*(void**)((char*)this + 0x20))
            CALL1(*(void**)((char*)this + 0x20), 0x1b, &box[0]);
    }
    if (img)
        CALL0(img, 1);
}

// ======================================================================
// 0xe496d0   load per-panel float parameters
// ======================================================================
// @ 0x00e496d0 C::LoadParams
void C::LoadParams()
{
    void* props = 0;
    void* pm = PropertyManager();
    ((PtrSlot*)&props)->Release();
    char ok = CALLG2(pm, 12, 0x5c770db7, &props);
    if (ok) {
        if (props) {
            void* pr;
            if (CALLG2(props, 9, 0x332d8d35, &pr) &&
                *(short*)((char*)pr + 0x12) == 0xd) {
                *(float*)((char*)this + 0x94) = *((Prop*)pr)->GetFloat();
            }
            if (props) {
                if (CALLG2(props, 9, (int)0xe451b420, &pr) &&
                    *(short*)((char*)pr + 0x12) == 0xd) {
                    *(float*)((char*)this + 0x98) = *((Prop*)pr)->GetFloat();
                }
                if (props) {
                    if (CALLG2(props, 9, (int)0xdc26347c, &pr) &&
                        *(short*)((char*)pr + 0x12) == 0xd) {
                        *(float*)((char*)this + 0x9c) = *((Prop*)pr)->GetFloat();
                    }
                    if (props) {
                        if (CALLG2(props, 9, 0x925d9d2, &pr) &&
                            *(short*)((char*)pr + 0x12) == 0xa) {
                            *(u32*)((char*)this + 0xa0) = *((Prop*)pr)->GetUInt();
                        }
                    }
                }
            }
        }
        if (*(void**)((char*)this + 0x14))
            *(u32*)(*(char**)((char*)this + 0x14) + 0x64) = *(u32*)((char*)this + 0xa0);
    }
    if (props)
        CALL0(props, 1);
}

// ======================================================================
// 0xe49820   block-vector range insert
// ======================================================================
struct BlkVec {
    int   base;
    u32   cap;
    int   pad08;
    int   firstObj;
    int   firstEnd;
    int   cur;
    int   pad18;
    int   lastObj;
    int   lastEnd;
    int   end;
    void InsertRange(u32 n, int atEnd);
    void Init(u32 n);
};

template <class T> const T& maxref(const T& a, const T& b)
{
    return a < b ? b : a;
}

// @ 0x00e49820 BlkVec::InsertRange
void BlkVec::InsertRange(u32 n, int atEnd)
{
    char* curp = *(char**)((char*)this + 0x14);
    char* endp = *(char**)((char*)this + 0x24);
    int bytes = (int)(endp - curp);
    int slots = (bytes >> 2) + 1;
    int total = slots + (int)n;
    u32 capv = *(u32*)((char*)this + 4);
    int* dst;

    if (capv <= (u32)(total * 2)) {
        u32 base = maxref(*(u32*)((char*)this + 4), n);
        u32 at = atEnd ? 0 : n;
        u32 newcap = base + *(u32*)((char*)this + 4) + 2;
        int* nb = (int*)EAAllocate(newcap * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
        int* src = *(int**)((char*)this + 0x14);
        dst = (int*)((char*)nb + ((((int)src - *(int*)this) >> 2) + (int)at) * 4);
        if (*(int*)this)
            VecInsert(dst, src, (*(int*)((char*)this + 0x24) - (int)src) + 4);
        if (*(int*)this)
            operator_delete(*(void**)this);
        *(int*)this = (int)nb;
        *(u32*)((char*)this + 4) = newcap;
    } else {
        u32 extra = atEnd ? 0 : n;
        dst = (int*)(*(int*)this + (((capv - (u32)total) >> 1) + extra) * 4);
        if ((char*)dst < curp) {
            VecInsert(dst, curp, bytes + 4);
        } else {
            memmove_(dst + (slots - ((bytes + 4) >> 2)),
                     curp, bytes + 4);
        }
    }

    *(int**)((char*)this + 0x14) = dst;
    int v = *dst;
    *(int*)((char*)this + 0xc) = v;
    *(int*)((char*)this + 0x10) = v + 0xc0;
    int* last = dst + slots - 1;
    *(int**)((char*)this + 0x24) = last;
    v = *last;
    *(int*)((char*)this + 0x1c) = v;
    *(int*)((char*)this + 0x20) = v + 0xc0;
}

// ======================================================================
// 0xe49950   block-vector constructor
// ======================================================================
// @ 0x00e49950 BlkVec::Init
void BlkVec::Init(u32 n)
{
    int cnt = (int)(n >> 4) + 1;
    u32 want = (u32)cnt + 2;
    u32 eight = 8;
    u32 capv = maxref(want, eight);
    *(u32*)((char*)this + 4) = capv;

    int* buf = (int*)EAAllocate(*(u32*)((char*)this + 4) * 4, "Simulator", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    int* start = (int*)((char*)buf +
        (((*(u32*)((char*)this + 4) - (u32)cnt) >> 1)) * 4);
    int* end = start + cnt;
    *(int*)this = (int)buf;

    for (int* p = start; p < end; p++) {
        *p = (int)EAAllocate(0xc0, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    }

    *(int**)((char*)this + 0x14) = start;
    int v = *start;
    *(int*)((char*)this + 0xc) = v;
    *(int*)((char*)this + 0x10) = v + 0xc0;
    *(int*)((char*)this + 8) = *(volatile int*)((char*)this + 0xc);
    *(int**)((char*)this + 0x24) = end - 1;
    v = end[-1];
    *(int*)((char*)this + 0x1c) = v;
    *(int*)((char*)this + 0x20) = v + 0xc0;
    *(int*)((char*)this + 0x18) =
        *(volatile int*)((char*)this + 0x1c) + (int)(n & 0xf) * 0xc;
}
