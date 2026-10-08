// SP::cTerrainStateMgr::StaticInit @ 0x00fba330
#include "types.h"

struct IRef {
    virtual void AddRef();
    virtual void Release();
};

struct ResourceKey {
    uint32_t instance, type, group;
};

struct IResMan {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const ResourceKey* key, IRef** out, int, int, int, int);   // 0x0c
};

struct IImageSrc {   // object returned by FUN_0067dd60
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual IRef* GetImage(uint32_t id, int, int);   // 0x20
};

// refcounted smart pointer global (inline AutoRefCount assignment)
struct AutoRef {
    IRef* p;
    AutoRef& operator=(IRef* n) {
        IRef* old = p;
        if (n != old) {
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
        return *this;
    }
};

// cAtomicRefPtr-style global: assignment is the out-of-line helper at 0x576650
struct AtomicRef {
    IRef* p;
    void Assign(IRef* n);   // 0x576650
};

IImageSrc* GetImageSrc();   // 0x67dd60
IResMan* GetManager();      // 0x67dcd0

extern AutoRef g16d6ab8, g16d6ab4, g16d6abc, g16d6ac0, g16d6ac4, g16d6ac8;
extern AtomicRef g16d6aa8, g16d6aa0, g16d6a78, g16d6a7c, g16d6a80, g16d6a8c, g16d6a90, g16d6a94,
    g16d6a98, g16d6a9c, g16d6a84, g16d6a88, g16d6aa4;
extern AutoRef g16d6ab0, g16d698c, g16d6990, g16d6994, g16d6998, g16d6974, g16d6acc;
extern AutoRef g16d6d30[16], g16d6d70[16];

inline ResourceKey MakeKey(uint32_t a, uint32_t b, uint32_t c) {
    ResourceKey k; k.instance = a; k.type = b; k.group = c; return k;
}
static inline void SetB(AutoRef& g, IRef* n) {
    if (n != g.p) {
        IRef* old = g.p;
        if (n) n->AddRef();
        g.p = n;
        if (old) old->Release();
    }
}
struct TmpRef {
    IRef* p;
    void Reset() {
        if (p) { IRef* t = p; p = 0; t->Release(); }
    }
};

namespace SP {
struct cTerrainStateMgr { static void StaticInit(); };
}

// @ 0x00fba330
void SP::cTerrainStateMgr::StaticInit()
{
    IImageSrc* src = GetImageSrc();
    TmpRef r;
    r.p = 0;
    ResourceKey key;
    key.instance = 0x2ec45f93; key.type = 0x3e421ed; key.group = 0;
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    SetB(g16d6ab8, r.p);
    key.instance = 0x362ac39e;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ab4 = r.p;
    key.instance = 0x7c6b9fd9;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6abc = r.p;
    key.instance = 0x88566056;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ac0 = r.p;
    key.instance = 0xf30d0a76;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ac4 = r.p;
    key.instance = 0xc71ef96a;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    SetB(g16d6ac8, r.p);

    g16d6aa8.Assign(src->GetImage(0xdef55713, 0, 0));
    g16d6aa0.Assign(src->GetImage(0x9d64f524, 0, 0));
    g16d6a78.Assign(src->GetImage(0x9d8d0398, 0, 0));
    g16d6a7c.Assign(src->GetImage(0x11b5ee6f, 0, 0));
    g16d6a80.Assign(src->GetImage(0x11b5ee6e, 0, 0));
    g16d6a8c.Assign(src->GetImage(0x08c05ad9, 0, 0));
    g16d6a90.Assign(src->GetImage(0xa3973ea2, 0, 0));
    g16d6a94.Assign(src->GetImage(0xa5ab24f5, 0, 0));
    g16d6a98.Assign(src->GetImage(0x3cef83d5, 0, 0));
    g16d6a9c.Assign(src->GetImage(0x3c9c0255, 0, 0));
    g16d6a84.Assign(src->GetImage(0x84613ac8, 0, 0));
    g16d6a88.Assign(src->GetImage(0xc66c3fcd, 0, 0));
    g16d6aa4.Assign(src->GetImage(0x3f05c913, 0, 0));

    key.instance = 0xc5d262e4; key.type = 0x3e421ec;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6ab0 = r.p;
    key.instance = 0xe2e599a0; key.type = 0x3e421ed;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d698c = r.p;
    key.instance = 0xc74bc5b0;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6990 = r.p;
    key.instance = 0x9c751f5e;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6994 = r.p;
    key.instance = 0xd1830e14;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6998 = r.p;
    key.instance = 0x54633685;
    r.Reset();
    GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0);
    g16d6974 = r.p;

    for (uint32_t i = 0; i < 16; i++) {
        key.instance = 0x5359c50 + i;
        r.Reset();
        if (GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0))
            g16d6d30[i] = r.p;
        else
            g16d6d30[i] = g16d698c.p;
    }
    for (uint32_t i = 0; i < 16; i++) {
        key.instance = 0x536dd50 + i;
        r.Reset();
        if (GetManager()->GetResource(&key, &r.p, 0, 0, 0, 0))
            g16d6d70[i] = r.p;
        else
            g16d6d70[i] = g16d6974.p;
    }

    key = MakeKey(0x1fa9ab84, 0x2cb4f2f, 0);
    IResMan* mgr = GetManager();
    r.Reset();
    if (mgr->GetResource(&key, &r.p, 0, 0, 0, 0))
        g16d6acc = r.p;
    if (r.p) r.p->Release();
}
