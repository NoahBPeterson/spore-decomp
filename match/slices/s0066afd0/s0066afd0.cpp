// Slice s0066afd0: SP::cSPUIFeedListItem-adjacent helpers: layout colour config,
// refcounted-vector push, map initialisation and the feed-item comparators.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef int   (__thiscall *FnIntV)(void*);
typedef void* (__thiscall *FnPtrV)(void*);
typedef char  (__thiscall *FnChrIP)(void*, int, void*);
typedef void* (__thiscall *FnPtrI)(void*, unsigned);
#define VT(p) (*(void***)(p))

struct RefObj {
    virtual void v0();       // +0x00 AddRef
    virtual int  Release();  // +0x04
    virtual void Release2(); // +0x08
    virtual void v3();       // +0x0c
};

struct IWindow {
    virtual void AddRef();                     // 0x00
    virtual int  Release();                    // 0x04
    virtual void v02();                        // 0x08
    virtual IWindow* FindWindow(unsigned id);  // 0x0c
};

struct cSPUILayout {
    virtual void s0();
    virtual void s1();
    virtual int  Release();
    IWindow* FindWindowByID(unsigned id, int flag);   // 0x008105b0
};

void* __cdecl SP_AssetBrowser();                   // 0x00401030
struct Prop { float* GetFloat(); };                // 0x0041ea70
void  __cdecl FUN_005c8480(void* a, void* b);      // 0x005c8480
void  __cdecl FUN_005c8480_g(void* a, void* b);    // placeholder

extern float gF13eb960;   // 0x013eb960
extern float gF13ef580;   // 0x013ef580
extern int   gVt140075c;  // 0x0140075c
extern void* gVecEnd;     // 0x015fb124
extern void* gVecCap;     // 0x015fb128
extern void* gVecObj;     // 0x015fb120

struct MapU {
    unsigned* operator[](const unsigned& k);
};
extern MapU gMapU;        // 0x01527b8c

struct Elem { int a; int b; };
struct ObjA { char pad0[0xc]; void* c; };
struct ObjB { char pad0[0xc]; void* c; };

// -----------------------------------------------------------------------------
// @ 0x0066afd0  comparator over the object at +0xc via a map lookup
// -----------------------------------------------------------------------------
int __cdecl FUN_0066afd0(ObjA* a, ObjB* b) {
    void* ca = a->c;
    if (ca) {
        if (b->c) {
            unsigned ka = ((FnIntV)VT(ca)[9])(ca);
            unsigned va = *gMapU[ka];
            unsigned kb = ((FnIntV)VT(b->c)[9])(b->c);
            unsigned vb = *gMapU[kb];
            if (va == vb) return 0;
            return (va < vb) ? -1 : 1;
        }
        return -1;
    }
    return b->c != 0;
}

// -----------------------------------------------------------------------------
// @ 0x0066b050  push a refcounted object onto the global vector
// -----------------------------------------------------------------------------
void __cdecl FUN_0066b050(void* p) {
    if (p) ((RefObj*)p)->v0();
    if (gVecEnd < gVecCap) {
        void** slot = (void**)gVecEnd;
        gVecEnd = (char*)gVecEnd + 4;
        if (slot) {
            *slot = p;
            if (p) ((RefObj*)p)->v0();
        }
    } else {
        FUN_005c8480(gVecEnd, &p);
    }
    if (p) ((RefObj*)p)->Release2();
}

// -----------------------------------------------------------------------------
// @ 0x0066b0c0  reset the layout map and reindex it from a vector of keys
// -----------------------------------------------------------------------------
extern void* gTreeHead;    // 0x01527b90
extern void* gTreeHead2;   // 0x01527b94
extern void* gTreeRoot;    // 0x01527b98
extern uint8_t gB9c;       // 0x01527b9c
extern uint32_t gBA0;      // 0x01527ba0
void __cdecl DoNukeSubtreeStub(void* p);

void __cdecl FUN_0066b0c0(int* vec) {
    DoNukeSubtreeStub(gTreeRoot);
    gTreeHead = &gTreeHead;
    gTreeHead2 = &gTreeHead;
    gTreeRoot = 0;
    gB9c = 0;
    gBA0 = 0;
    unsigned n = (unsigned)((vec[1] - vec[0]) >> 2);
    for (unsigned i = 0; i < n; ++i) {
        unsigned key = *(unsigned*)(vec[0] + i * 4);
        *gMapU[key] = i;
    }
}

void __cdecl DoNukeSubtreeStub(void* p);

// -----------------------------------------------------------------------------
// @ 0x0066bd40  zero-initialising constructor
// -----------------------------------------------------------------------------
void __fastcall FUN_0066bd40(void* self) {
    float v0 = gF13eb960;
    ((uint32_t*)self)[1] = 0;
    *(void**)self = &gVt140075c;
    ((uint32_t*)self)[2] = 0;
    ((uint32_t*)self)[3] = 0;
    ((uint32_t*)self)[4] = 0;
    ((uint32_t*)self)[5] = 0;
    *(float*)((char*)self + 0x18) = v0;
    *(float*)((char*)self + 0x1c) = gF13ef580;
}

// -----------------------------------------------------------------------------
// @ 0x0066bf20  release the four child windows
// -----------------------------------------------------------------------------
void __fastcall FUN_0066bf20(void* self) {
    void* p;
    p = *(void**)((char*)self + 8);
    if (p) { *(void**)((char*)self + 8) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0xc);
    if (p) { *(void**)((char*)self + 0xc) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0x10);
    if (p) { *(void**)((char*)self + 0x10) = 0; ((RefObj*)p)->Release(); }
    p = *(void**)((char*)self + 0x14);
    if (p) { *(void**)((char*)self + 0x14) = 0; ((RefObj*)p)->Release(); }
}

// -----------------------------------------------------------------------------
// @ 0x0066bd80  layout colour/height configuration
// -----------------------------------------------------------------------------
struct ColourCfg {
    void FUN_0066bd80(cSPUILayout* layout);
};

void ColourCfg::FUN_0066bd80(cSPUILayout* layout) {
    void* b = SP_AssetBrowser();
    if (b) {
        void* pi = *(void**)((char*)b + 0x18);
        if (pi) {
            void* prop;
            char c = ((FnChrIP)VT(pi)[9])(pi, 0xc97f8ee9, &prop);
            if (c && *(int16_t*)((char*)prop + 0x12) == 0xd) {
                float* f = ((Prop*)prop)->GetFloat();
                *(float*)((char*)this + 0x18) = *f;
            }
            c = ((FnChrIP)VT(pi)[9])(pi, 0x2034014d, &prop);
            if (c && *(int16_t*)((char*)prop + 0x12) == 0xd) {
                float* f = ((Prop*)prop)->GetFloat();
                *(float*)((char*)this + 0x1c) = *f;
            }
        }
    }
    if (!layout) return;
    {
        IWindow* w = layout->FindWindowByID(0x4cab570, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 8);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 8) = child;
                if (old) old->Release();
            }
        }
    }
    {
        IWindow* w = layout->FindWindowByID(0x4cab571, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 0xc);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 0xc) = child;
                if (old) old->Release();
            }
        }
    }
    {
        IWindow* w = layout->FindWindowByID(0x4cab56f, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 0x10);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 0x10) = child;
                if (old) old->Release();
            }
        }
    }
    {
        IWindow* w = layout->FindWindowByID(0x4cab56e, 1);
        if (w) {
            IWindow* child = w->FindWindow(0x8ed27e7a);
            IWindow* old = *(IWindow**)((char*)this + 0x14);
            if (child != old) {
                if (child) child->AddRef();
                *(IWindow**)((char*)this + 0x14) = child;
                if (old) old->Release();
            }
        }
    }
}

// -----------------------------------------------------------------------------
// @ 0x0066b130 / @ 0x0066b480  (large; PARTIAL - see partial.txt)
// -----------------------------------------------------------------------------
void __fastcall FUN_0066b130(void* self) {
    (void)self;   // large layout/animation builder omitted
}

void __fastcall FUN_0066b480(void* self) {
    (void)self;   // large layout/animation builder omitted
}
