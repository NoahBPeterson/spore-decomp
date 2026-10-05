// w1g1 slice s004ea310 -- editor validity key writer + flag helper.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

struct FlagWord {
    unsigned int a : 8;
    unsigned int b : 8;
    unsigned int c : 8;
    unsigned int d : 6;
    unsigned int e : 2;
};
struct DeclareParam { int key; int a; int b; };
struct Vec { void push_back(const DeclareParam& v); };
struct Iface { virtual void v0(); virtual void Release(); }; // Release at +4
struct PaletteMgr {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void GetConfig(int cfg, int key, int* out); // +0x2c
};

int GetConfigFromModelType(int id);      // 0x00432f10
void* PropertyManager();                 // 0x0067de30
bool GetPropertyAsKey(void* holder, int key, void* out);
extern int g_15daa00;

// ===========================================================================
// @ 0x004ea720  (MATCH)
// Packs a model type + paint flag byte into the validity flag word.
// ===========================================================================
FlagWord FUN_004ea720(int p1, int p2)
{
    FlagWord f = {0};
    f.e = 1;
    f.c = p1;
    f.b = p2;
    return f;
}

// ===========================================================================
// @ 0x004ea780  (complete; not byte-exact)
// Recursively remaps a model-type id through the paint-key chain, then appends
// the tag property of the resulting config to `out`.  (PDB candidate:
// SP::EditorValidity::WriteKeysToFile.)
// ===========================================================================
void FUN_004ea780(int id, int tag, Vec* out, int param4)
{
    int v22;
    int v14;
    int v3, v1, p20;
    int idx;
    int t33;
    int t28, n36;
    void* n32;
    switch (id) {
    case 0x4178b8e8: FUN_004ea780(0x65672ade, tag, out, param4); break;
    case 0x65672ade: FUN_004ea780(0xccc35c46, tag, out, param4); break;
    case 0xccc35c46: FUN_004ea780(0x372e2c04, tag, out, param4); break;
    case 0x372e2c04: FUN_004ea780(0x9ea3031a, tag, out, param4); break;
    }
    if (tag == 0x7a926123 && id == 0x9ea3031a && param4 != 0x5bf8f774)
        FUN_004ea780(0xdfad9f51, tag, out, param4);
    v14 = 0;
    v22 = GetConfigFromModelType(id);
    if (param4 != 0)
        v22 = param4;
    n32 = PropertyManager();
    if (v14)
        ((Iface*)v14)->Release();
    ((PaletteMgr*)n32)->GetConfig(v22, g_15daa00, &v14);
    if (v14) {
        p20 = 0;
        v1 = 0;
        v3 = 0;
        t33 = v14;
        if (GetPropertyAsKey((void*)t33, tag, &p20))
            out->push_back(*(DeclareParam*)&p20);
    }
    if (v14)
        ((Iface*)v14)->Release();
}

// ===========================================================================
// @ 0x004ea310  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004ea310(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// ===========================================================================
// @ 0x004ea920  (INCOMPLETE skeleton)
// ===========================================================================
void FUN_004ea920(void* a, void* b, void* c, void* d)
{
    (void)a; (void)b; (void)c; (void)d;
}
