// Sprite texture MIP baking helper. Built /Od /Ob1 /MD /Gy /EHsc /TP /arch:SSE.

void* operator new(unsigned size, const char* name, int, int, int, int);

struct IObject {
    virtual void Destroy();
    virtual void Release();
};

struct Service {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void Begin();   // +0x20
    virtual void End();     // +0x24
};

struct ObjectHeader {       // first base: vptr + 8 bytes
    virtual void AddRef();
    virtual void Release();
    int pad[2];
};

struct PtrVec {
    IObject** begin;
    IObject** end;
    IObject** cap;
    void __thiscall resize(int n);
    int size() { return (int)(end - begin); }
    IObject** at(int i) { return begin + i; }
};

struct BakeTarget : ObjectHeader, PtrVec {   // PtrVec at +0x0c
};

struct Graphics_BakeSprites : ObjectHeader, PtrVec {
    int pad2[2];
    Graphics_BakeSprites();
};

Service* GetServiceHost();
void Resolve(void* out, PtrVec* vec, int, int);
void BakeOne(void* src, void* slot, int level, int arg, int, int);

struct ServiceRef {
    Service* s;
    void Init(Service* x) { s = x; }
    void Begin() { s->Begin(); }
    void End() { s->End(); }
};

struct BakerRef {
    Graphics_BakeSprites* p;
    void AddRef() { p->AddRef(); }
    void Release() { p->Release(); }
};

// @ 0x00430CA0
void BakeSpriteTextureMips(void* out, int level, int arg, BakeTarget* target)
{
    ServiceRef svc;
    BakerRef baker;
    int n, i;
    if (level >= 0) {
        svc.Init(GetServiceHost());
        svc.Begin();
        baker.p = new ("Graphics/SpriteTextureMIPs", 0, 0, 0, 0) Graphics_BakeSprites();
        if (baker.p) baker.AddRef();
        Resolve(out, baker.p, 0, 0);
        target->resize(baker.p->size());
        for (i = 0, n = target->size(); i < n; ++i) {
            IObject** slot = target->at(i);
            if (*slot) {
                IObject* old = *slot;
                *slot = 0;
                old->Release();
            }
            BakeOne(*baker.p->at(i), slot, level, arg, 0, 0);
        }
        if (baker.p) baker.Release();
        svc.End();
    } else {
        Resolve(out, target, 0, 0);
    }
}
