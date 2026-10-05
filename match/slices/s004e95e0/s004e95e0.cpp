// w1g1 slice s004e95e0 -- editor "functional match" property collectors.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (frame pointer, no C++ EH,
// x87 for float args, SSE for float copies).  Stack-slot holes are the unused
// /Od locals left by the original's inlined helpers; they are reproduced with
// unused named locals.

typedef unsigned int uint32_t;

struct DeclareParam { int key; int a; int b; };

struct Manager {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21();
    virtual void* Find(int a, int b); // +0x58
};

struct Vec { void push_back(const DeclareParam& v); };

// ---- external helpers (relocations are masked) ------------------------------
void* GetMgr401010();                                            // 0x00401010
void* GetManager67dcd0();                                        // 0x0067dcd0
bool GetPropertyAsKey(void* holder, int key, void* out);         // 0x006a1250
bool GetPropertyAsKeyInstance(void* holder, int key, int* out);  // 0x006a12a0
bool GetPropertyAsKeyArray(void* holder, int key, int* count, void** array); // 0x006a0ae0
void* InterfaceCast(void** ref);                                 // 0x00421eb0-ish
void* Alloc(uint32_t size, const char* name, int, int, int, int); // 0x00f473a0
void* operator new(uint32_t size, const char* name, int, int, int, int); // 0x00f473a0

// Refcounted-object vtable shape used by the palette helpers (+4 AddRef, +8 Release).
struct Iface {
    virtual void v00();
    virtual void AddRef();   // +4
    virtual void Release();  // +8
};

// Palette double-buffered iterator helper (0x005c7b80).
struct PaletteIter : Iface {
    PaletteIter();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void SetPalette(void* p);              // 0x005c7bc0
    virtual void* GetFirst(int, int, int, int);    // 0x005c7e80
    virtual void* GetNext(int, int, int, int);     // 0x005c7e20
};

struct cSPPalette : Iface {
    cSPPalette();
    bool Init(void* a, int b, int c, int d, int e, int f, int g); // 0x005c6340
};

struct ResourceMgr {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void FindResource(void* key, void** out, int, int, int, int); // +0xc
};

struct PaletteMgr {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void GetPalette(int type, void* a, void* b); // +0x2c
};

extern DeclareParam g_15dacc8;
extern DeclareParam g_15dabcc;
void FUN_004e9ca0(Vec* out);

// ===========================================================================
// @ 0x004e9c40  (MATCH)
// ===========================================================================
void UpgradeParts(DeclareParam param, Vec* out)
{
    int hi;                       // ebp-0x14  manager
    int v9;                       // ebp-0x10  hole
    int key;                      // ebp-0xc   hole
    const int n28 = 0xf45f59d7;   // ebp-8     key constant
    int p30;                      // ebp-4     holder
    hi = (int)GetMgr401010();
    p30 = (int)((Manager*)hi)->Find(param.key, param.b);
    if (p30 != 0) {
        if (GetPropertyAsKey((void*)p30, 0xf45f59d7, &param))
            out->push_back(param);
    }
}

// ===========================================================================
// @ 0x004e9b40  (MATCH)
// ===========================================================================
void AddPaintKeys(DeclareParam param, Vec* out)
{
    int mid, elem, n17, p9;
    int owner, v8, n6, t33;
    void* p40;
    void* s;
    int n5;
    void* t2;
    int t23;
    int p1;
    n17 = 0x2196ad5;
    elem = 0xbd110a25;
    mid = 0xdee3d8a8;
    p9 = 0xb0e066a7;
    p40 = GetMgr401010();
    s = ((Manager*)p40)->Find(param.key, param.b);
    if (s != 0) {
        n5 = 0;
        if (GetPropertyAsKeyInstance(s, 0x2196ad5, &n5)) {
            if (n5 == 0xbd110a25) {
                out->push_back(param);
            } else if (n5 == (int)0xdee3d8a8) {
                t23 = 0;
                if (GetPropertyAsKeyArray(s, 0xb0e066a7, &t23, &t2)) {
                    for (p1 = 0; p1 < t23; p1++) {
                        if (*(int*)((char*)t2 + p1 * 0xc) != 0)
                            out->push_back(*(DeclareParam*)((char*)t2 + p1 * 0xc));
                    }
                }
            }
        }
    }
}

// ===========================================================================
// @ 0x004e9c40  (already above; kept order aligned with the slice listing)
// ===========================================================================

// ===========================================================================
// @ 0x004ea190  (complete; not byte-exact)
// Recursively adds the declare-param entries that a model-type id maps to.
// ===========================================================================
void FUN_004ea190(int id, Vec* out, int flag)
{
    DeclareParam d;
    switch (id) {
    case 0xdfad9f51:
        d.key = (int)0xc15cfa84;
        d.a = 0;
        d.b = (int)(0x40000000u | (0x61u << 16) | (0x60u << 8));
        out->push_back(d);
        break;
    case 0x372e2c04:
    case 0x9ea3031a:
    case 0xccc35c46:
    case 0x4178b8e8:
    case 0x65672ade:
        d.key = 0xd05c53a3;
        d.a = 0;
        d.b = (int)(0x40000000u | (0x62u << 16) | (0x60u << 8));
        out->push_back(d);
        out->push_back(g_15dacc8);
        out->push_back(g_15dabcc);
        if (flag != 0x5bf8f774)
            FUN_004e9ca0(out);
        break;
    }
}

// ===========================================================================
// @ 0x004e9950  (complete; not byte-exact)
// Walks a holder's property keys; when the "children" key is present it
// recurses into the editor resource's sub-objects.
// ===========================================================================
void Collect9950(DeclareParam param, Vec* out)
{
    void* mgr = GetMgr401010();
    void* holder = ((Manager*)mgr)->Find(param.key, param.b);
    if (holder == 0)
        return;
    if (GetPropertyAsKey(holder, 0x3a3b9d21, &param))
        out->push_back(param);
    if (GetPropertyAsKey(holder, 0x18c1dbe0, &param))
        out->push_back(param);
    if (GetPropertyAsKey(holder, 0xf48eb09, &param))
        out->push_back(param);
    if (!GetPropertyAsKey(holder, 0x22e8410, &param)) {
        out->push_back(param);
    } else {
        ResourceMgr* rm = (ResourceMgr*)GetManager67dcd0();
        void* ref = 0;
        if (ref)
            ((Iface*)ref)->Release();
        rm->FindResource(&param, &ref, 0, 0, 0, 0);
        if (ref) {
            void* res = InterfaceCast(&ref);
            if (res) {
                char* vec = (char*)res + 0x98;
                int begin = *(int*)vec;
                int count = (*(int*)(vec + 4) - begin) / 0x1d8;
                for (int i = 0; i < count; i++) {
                    DeclareParam d;
                    d.key = *(int*)(begin + i * 0x1d8 + 4);
                    d.a = param.a;
                    d.b = *(int*)(begin + i * 0x1d8);
                    Collect9950(d, out);
                }
            }
        }
        if (ref)
            ((Iface*)ref)->Release();
    }
}

// ===========================================================================
// @ 0x004e9fc0  (complete; not byte-exact)
// Builds a palette for one model type and dispatches each entry to the
// AddPaintKey/UpgradeParts collector chosen by `kind`.
// ===========================================================================
void FUN_004e9fc0(int modelType, Vec* out, int kind)
{
    cSPPalette* pal = new ("Editor", 0, 0, 0, 0) cSPPalette();
    if (pal != 0) {
        pal->AddRef();
        if (pal->Init((void*)modelType, -1, 0, 0, 0, 0, 0)) {
            PaletteIter* it = new ("Editor", 0, 0, 0, 0) PaletteIter();
            if (it != 0) {
                it->AddRef();
                it->SetPalette(pal);
                void* node = it->GetFirst(0, 0, 0, 0);
                while (node != 0) {
                    DeclareParam d;
                    d.key = *(int*)((char*)node + 0xc);
                    d.a = *(int*)((char*)node + 0x10);
                    d.b = *(int*)((char*)node + 0x14);
                    if (kind == 0)
                        Collect9950(d, out);
                    else if (kind == 1)
                        AddPaintKeys(d, out);
                    node = it->GetNext(0, 0, 0, 0);
                }
            }
            if (it != 0)
                it->Release();
        }
        pal->Release();
    }
}

// ===========================================================================
// @ 0x004e9ca0  (INCOMPLETE skeleton)
// 792-byte /Od enumator building a palette list for a model type.  Left as a
// skeleton; the allocation/refcount/interator sequence is not yet reproduced.
// ===========================================================================
void FUN_004e9ca0(Vec* out)
{
    (void)out;
}

// ===========================================================================
// @ 0x004e95e0  (INCOMPLETE skeleton)
// 868-byte /Od helper that composes a transform/validity blob from a preview
// object.  Left as a skeleton: it mixes several vector-math helpers whose
// exact inline expansions are not yet reproduced.
// ===========================================================================
void FUN_004e95e0(int* self, void* out1, void* out2)
{
    (void)self; (void)out1; (void)out2;
}
