// slice s00645620: cSPUIAssetBrowser dialog/publish helpers.
#include "../s00636320/s00636320.h"

// --- reference-counted element types (0x14-byte element) ---
struct cBase0 { virtual void b0(); char pad[0xc]; };              // size 0x10
struct cRefCountA { virtual void AddRef(); virtual void Release(); };        // slots 0,1 at +0
struct cRefCountB { virtual void AddRef(); virtual void Release(); };        // slots 0,1 at +0x10
struct cRefB : cBase0, cRefCountB {};                             // refcount base at +0x10
struct Elem {
    uint32_t a, b, c;   // +0x00
    cRefCountA* p;      // +0x0C
    cRefB*      q;      // +0x10
};

// --- external helpers ---
struct cAssetBrowser2 { int FUN_00645cc0(); };   // 0x00645CC0
cAssetBrowser2* GetAssetBrowser2();              // 0x00401030

struct IAuthMgr {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4();
    virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8();
    virtual bool a9();                               // +0x24
    virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14();
    virtual void a15(); virtual void a16();
    virtual void a17();                              // +0x44
    virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21();
    virtual bool a22();                              // +0x58
};
IAuthMgr* GetAuthMgr();                              // 0x00607A60

struct cSPUIAssetBrowser {
    char pad04[0x4];
    char pad1c0[0x1c0 - 0x4];
    int  mField1c0;            // +0x1C0
    char pad230[0x230 - 0x1c4];
    int  mField230;            // +0x230
    char pad24d[0x24d - 0x234];
    bool mb24d;                // +0x24D
    bool mb24e;                // +0x24E

    int  FUN_00645d90();                                  // 0x00645D90
    void FUN_00645db0(Elem* other);                       // 0x00645DB0
    void FUN_00645e20();                                  // 0x00645E20
    static Elem* FUN_00646030(Elem* first, Elem* last, uint32_t* key);   // 0x00646030
    static void FUN_006460b0(Elem* first, Elem* last, Elem* src);        // 0x006460B0
    static Elem* FUN_00646140(Elem* first, Elem* last, Elem* dst);       // 0x00646140
    static Elem* FUN_006461d0(Elem* first, Elem* last, Elem* dst);       // 0x006461D0
    void FUN_00646260();                                  // 0x00646260
    void FUN_006462b0(void* p);                           // 0x006462B0
    void FUN_00645620();
    void FUN_00645bf0();
    void FUN_00645cc0_();
};

// @ 0x00645D90
int cSPUIAssetBrowser::FUN_00645d90()
{
    int r = mField1c0;
    if (r == 0) {
        r = GetAssetBrowser2()->FUN_00645cc0();
        if (r == 0)
            r = -1;
    }
    return r;
}

// @ 0x00645FF0
void __stdcall FUN_00645ff0(Elem* first, Elem* last)
{
    for (; first < last; first = (Elem*)((char*)first + 0x14)) {
        cRefB* q = first->q;
        if (q)
            q->Release();
        cRefCountA* p = first->p;
        if (p)
            p->Release();
    }
}

// @ 0x00646260
void cSPUIAssetBrowser::FUN_00646260()
{
    mb24d = true;
    IAuthMgr* auth = GetAuthMgr();
    if (auth->a22() && !auth->a9()) {
        FUN_00645e20();
        return;
    }
    GetAuthMgr()->a17();
    mField230 = 0;
}

// @ 0x00645620  PARTIAL
void cSPUIAssetBrowser::FUN_00645620() {}
// @ 0x00645BF0  PARTIAL
void cSPUIAssetBrowser::FUN_00645bf0() {}
// @ 0x00645CC0  PARTIAL
void cSPUIAssetBrowser::FUN_00645cc0_() {}
// @ 0x00645DB0  PARTIAL
void cSPUIAssetBrowser::FUN_00645db0(Elem* other) { other->a = 0; }
// @ 0x00645E20  PARTIAL (noinline so 00646260 keeps its tail jmp)
extern void gPartialCall3();
__declspec(noinline) void cSPUIAssetBrowser::FUN_00645e20() { gPartialCall3(); }
// @ 0x00646030  PARTIAL
Elem* cSPUIAssetBrowser::FUN_00646030(Elem* first, Elem* last, uint32_t* key) { (void)last; (void)key; return first; }
// @ 0x006460B0
void cSPUIAssetBrowser::FUN_006460b0(Elem* first, Elem* last, Elem* src)
{
    for (; first != last; first = (Elem*)((char*)first + 0x14)) {
        first->a = src->a;
        first->b = src->b;
        first->c = src->c;
        cRefCountA* newp = src->p;
        cRefCountA* oldp = first->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            first->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = src->q;
        cRefB* oldq = first->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            first->q = newq;
            if (oldq) oldq->Release();
        }
    }
}

// @ 0x00646140
Elem* cSPUIAssetBrowser::FUN_00646140(Elem* first, Elem* last, Elem* dst)
{
    while (first != last) {
        dst->a = first->a;
        dst->b = first->b;
        dst->c = first->c;
        cRefCountA* newp = first->p;
        cRefCountA* oldp = dst->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            dst->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = first->q;
        cRefB* oldq = dst->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            dst->q = newq;
            if (oldq) oldq->Release();
        }
        first = (Elem*)((char*)first + 0x14);
        dst = (Elem*)((char*)dst + 0x14);
    }
    return dst;
}

// @ 0x006461D0
Elem* cSPUIAssetBrowser::FUN_006461d0(Elem* first, Elem* last, Elem* dst)
{
    while (last != first) {
        last = (Elem*)((char*)last - 0x14);
        dst = (Elem*)((char*)dst - 0x14);
        dst->a = last->a;
        dst->b = last->b;
        dst->c = last->c;
        cRefCountA* newp = last->p;
        cRefCountA* oldp = dst->p;
        if (newp != oldp) {
            if (newp) newp->AddRef();
            dst->p = newp;
            if (oldp) oldp->Release();
        }
        cRefB* newq = last->q;
        cRefB* oldq = dst->q;
        if (newq != oldq) {
            if (newq) newq->AddRef();
            dst->q = newq;
            if (oldq) oldq->Release();
        }
    }
    return dst;
}
// @ 0x006462B0  PARTIAL
void cSPUIAssetBrowser::FUN_006462b0(void* p) { (void)p; }
