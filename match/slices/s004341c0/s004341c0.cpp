// Scene light/effect controller start & stop (/Od /Ob1 /MD /Gy /TP /arch:SSE).
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

struct IRefObject {
    virtual void AddRef();       // +0
    virtual void Release();      // +4
    virtual void v2();
    virtual void Stop(int flag); // +0xc
};

struct IRenderer {
    virtual void p00(); virtual void p01(); virtual void p02(); virtual void p03();
    virtual void p04(); virtual void p05(); virtual void p06(); virtual void p07();
    virtual void p08(); virtual void p09(); virtual void p10(); virtual void p11();
    virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15();
    virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19();
    virtual void p1A(); virtual void p1B(); virtual void p1C(); virtual void p1D();
    virtual void p1E(); virtual void p1F0();
    virtual void SetOption(int handle, int id, int a, int b, int c); // +0x70
    virtual void SetParamA(int handle, int id, int a, int b);        // +0x74
    virtual void SetParamF(int handle, int id, float f, int b);      // +0x78
    virtual void GetRange(int handle, int id, float* a, float* b, int c); // +0x80
};

struct Owner {
    char pad0[0x10];
    int handle;     // +0x10
    int pad14;
    IRenderer* renderer; // +0x18
    void Refresh();      // FUN_0043d420
    void* GetKey();      // FUN_0043d220
};

struct IntrusivePtr {
    IRefObject* mp;
    __forceinline IRefObject* operator->() const { return mp; }
    __forceinline IRefObject* get() const { IRefObject* t = mp; return t; }
    __forceinline void Reset(IRefObject* p)
    {
        IRefObject* old = mp;
        if (p) p->AddRef();
        mp = p;
        if (old) old->Release();
    }
    __forceinline void Clear() { if (mp) Reset(0); }
};

struct Effect {
    int id;          // +0
    float length;    // +4
    float start;     // +8
    float speed;     // +0xc
    bool hasPos;     // +0x10
    bool active;     // +0x11
    void* source;    // +0x14
    Vec3 pos;        // +0x18
    unsigned char pad24[5];
    bool flag;       // +0x29
    unsigned char pad2a[2];
    Owner* owner;    // +0x2c
    IntrusivePtr instance; // +0x30

    bool IsActive();       // FUN_00434100
    void Stop();
    void Start(int newId, float newSpeed);
    bool Prepare();        // FUN_00434100 (inlined check)
};

void Reset(Effect* e);
// @ 0x004341c0
void Effect::Stop()
{
    if (instance.get()) {
        IRefObject* u;
        IRefObject* t = u;
        t = instance.mp;
        t->Stop(0);
        instance.Clear();
    }
    active = false;
    flag = false;
    IRenderer* r = owner->renderer;
    int h = owner->handle;
    r->SetParamF(h, id, 0.0f, 0);
    if (hasPos) {
        Vec4 v = { pos.x, pos.y, pos.z, 1.0f };
        extern void SetPosition(Owner*, Vec4);
        SetPosition(owner, v);
    }
    owner->Refresh();
}

// ---- Start support types (reconstructed) ----
struct Camera { char pad[0x4c]; Vec3 position; }; // +0x4c
struct Params {
    unsigned short flags;
    unsigned short count;
    unsigned key[4];
    unsigned body[10];
};
struct ParamBuilder {
    unsigned short flags;
    unsigned short count;
    unsigned key[3];
    float value;     // +0x10
    unsigned body[9];
    ParamBuilder();  // FUN_00434040
};
struct Factory { IRefObject* Create(void* src, int zero, ParamBuilder* pb, Effect* owner); }; // FUN_00401050 + FUN_0045ac20

extern Camera* GetCamera();                 // FUN_0047e680
extern void NotifyStart(Owner*);            // FUN_00448a80
extern void BuildKey(void* dst, void* k);   // FUN_0040ce80
extern void* CreateEffect(void* src, int zero, ParamBuilder* pb, Effect* e); // FUN_00401050
extern IRefObject* Wrap(void* p);           // FUN_0045ac20

// @ 0x004342f0
void Effect::Start(int newId, float newSpeed)
{
    if (IsActive()) {
        Stop();
    }
    if (GetCamera()) {
        hasPos = true;
        pos = *(Vec3*)((char*)GetCamera() + 0x4c);
    }
    NotifyStart(owner);
    id = newId;
    speed = newSpeed;
    {
        IRenderer* r = owner->renderer;
        int h = owner->handle;
        r->SetParamF(h, id, 1.0f, 0);
    }
    {
        IRenderer* r = owner->renderer;
        int h = owner->handle;
        r->SetOption(h, id, 3, 0, 0);
    }
    {
        IRenderer* r = owner->renderer;
        int h = owner->handle;
        r->SetParamA(h, id, 0, 0);
    }
    owner->Refresh();
    float lo = 0.0f, hi = 0.0f;
    {
        IRenderer* r = owner->renderer;
        int h = owner->handle;
        r->GetRange(h, id, &lo, &hi, 0);
    }
    length = hi - lo;
    start = 0.0f;
    if (source) {
        ParamBuilder pb;
        BuildKey(&pb, owner->GetKey());
        pb.flags |= 4;
        pb.flags |= 2;
        IRefObject* created = Wrap(CreateEffect(source, 0, &pb, this));
        IntrusivePtr* slot = &instance;
        if (created != slot->mp) {
            IRefObject* old = slot->mp;
            if (created) created->AddRef();
            slot->mp = created;
            if (old) old->Release();
        }
    }
    active = true;
}
