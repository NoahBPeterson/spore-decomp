// s00adaad0 -- EA Simulator ArgScript command objects: the message builders that
// dispatch a 0x40 RefObj through cAppState::AddMessage, plus the viewer/hashtable
// helpers of the same module (Sim:: lookups, camera transform, ribbon commands).

typedef unsigned int u32;

void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern void __cdecl operator_delete_array(void* p);          // 0xf47380
extern "C" long __cdecl _InterlockedExchange(volatile long*, long);
#pragma intrinsic(_InterlockedExchange)

class cArguments {
public:
    const char** MainArguments(int n);                            // 0x838320
    const char** MainArguments(int* pCount, int min, int max);    // 0x838020
    const char** OptionArguments(const char* name, int n);        // 0x838330
    bool HasFlag(const char* name);                               // 0x8380b0
};

extern unsigned int __cdecl FNV1_String8(const char* s, unsigned int seed, int flag);  // 0x932e80

// ---- message object (0x40): RefBase primary base (vtable +0, refcount +4),
//      MsgData secondary base at +8, flags at +0x38 ------------------------------
struct MsgData {
    int f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c, tag;
    MsgData() : tag(0) {}
};

struct RefBase {                              // vtable 0x13eb90c
    virtual void v0();
    virtual void AddRef();                    // slot 1
    virtual void Release();                   // slot 2
    long rc;                                  // +0x04
    RefBase() { _InterlockedExchange(&rc, 0); }
};

struct Msg : MsgData, RefBase {               // vtable 0x13eb844
    int f34;                                  // +0x34
    int flags;                                // +0x38
    int f3c;                                  // +0x3c
    Msg() : MsgData(), flags(0) {}
};

struct cAppState {
    char pad[0xc];
    void AddMessage(cArguments* args, Msg* msg, char c);   // 0x7e4190
};

static inline cAppState* STATE(void* self) { return *(cAppState**)((char*)self + 0xc); }

// ArgScript argument parser reached through *(void**)(self+4).
struct Parser {
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
    virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
    virtual void s36(); virtual void s37();
    virtual float ParseF(const char* s);              // 0x98
    virtual void  s39();
    virtual int   ParseI(const char* s);              // 0xa0
    virtual void  s41();
    virtual void* ParseV(void* out, const char* s);   // 0xa8
};

static inline Parser* PARSER(void* self) { return *(Parser**)((char*)self + 4); }

// ---- eastl hashtable accessors (this in ecx, callee cleans the stack args) -----
struct Iter { void* node; void* bucket; };

struct HTbl {                                              // eastl hashtable
    char pad0[4];                                          // +0
    unsigned int* arr;                                     // +4  bucket array
    unsigned int  count;                                   // +8  bucket count
    Iter* Find(Iter* out, const void* key);                // 0xad91a0
    void* findKey(void* out, const void* key);             // 0xad9310
    void* find(void* out, const void* key);                // 0xdb4780
};
struct HTKeyFind {                                         // hashtable find (audio)
    void* find(void* out, const void* key);                // 0xad9310
};
struct HTEqualRange {                                      // hashtable equal_range
    void* equal_range(void* out, const void* key);         // 0x9a6dd0
};
struct HTCursorFind {                                      // ImageCursorProvider find
    void* find(void* out, const void* key);                // 0xdb4780
};

extern void* __stdcall FUN_006859b0(void* out, Iter node);  // 0x6859b0  eastl hashtable iterator advance (out, iterator by value)

// ---- refcounted object helper --------------------------------------------------
struct RefObj {
    virtual void AddRef();                 // slot 0
    virtual void Release();                // slot 1
};

static inline void SetRef(void** slot, RefObj* nu)
{
    RefObj* old = (RefObj*)*slot;
    if (nu != old) {
        if (nu) nu->AddRef();
        *slot = nu;
        if (old) old->Release();
    }
}

// ---- viewer / audio / transform stubs ------------------------------------------
struct Mat3 {
    float m[9];
    Mat3(const Mat3& src);                 // 0x41cb40 (out-of-line copy ctor; ecx = this)
};
struct Quat { float x, y, z, w; };

struct XForm {
    unsigned short a;      // +0x00
    unsigned short b;      // +0x02
    float x, y, z, w;      // +0x04
    Mat3  m;               // +0x14
    Mat3* Matrix() { return &m; }
};

struct EMat {                                   // object at self+0x168
    void SetFlag(int v);                        // 0xeb3c70
    void SetXForm(XForm xf);                    // 0xeb4400
    void SetValue(float v);                     // 0xeb30a0
    void Update();                              // 0xeb3190
    void SetRotation(Quat q);                   // 0xeb30d0
};

struct Viewer13C {                              // object at self+0x13c
    virtual void v00(); virtual void v01(unsigned int id, const void* p);
    virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05();
    virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void* v14();            // 0x38
    virtual void* v15();            // 0x3c
};

struct cViewer {                                // object at self+0x40
    float GetFieldOfView();                     // 0x7c4050
    void  GetTransform(XForm* out);             // 0x7c40f0
};

struct IEntry {                                 // hash payload at +0x10
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void* s3(unsigned int id);          // 0x0c
};

struct Cursor {                                 // object returned by s3()
    char Method(unsigned int v);                // 0xad94c0
};

struct Sim {
    int  Lookup(unsigned int key1, unsigned int key2);      // 0xadb250
    void sendXform(void* p, int n);                         // 0xad89b0
};

struct AudioSys {
    virtual void a00(); virtual void a01(); virtual void a02(); virtual void a03();
    virtual void a04(); virtual void a05(); virtual void a06(); virtual void a07();
    virtual void a08(); virtual void a09(); virtual void a10();
    virtual void a11(unsigned int v);                            // 0x2c
    virtual void a12(); virtual void a13();
    virtual void a14(unsigned int id);                           // 0x38
    virtual void a15();
    virtual void a16(unsigned int id, unsigned int v);           // 0x40
    virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20();
    virtual void a21();
    virtual void a22();                                          // 0x58
};

struct ResKey { int f0, f4, f8; };

// ---- external helpers / globals -------------------------------------------------
extern unsigned int __stdcall FUN_00b3d230(unsigned int hash);      // 0xb3d230
extern void __fastcall FUN_00b5cde0(void* p);                       // 0xb5cde0
extern void __stdcall FUN_00ad9010(void* p);                        // 0xad9010
extern AudioSys* __cdecl FUN_00a206f0();                            // 0xa206f0
extern void __cdecl FUN_011e0744(void* dst, const char* src, int count);   // 0x11e0744
extern void* __cdecl FUN_0093c6d0(void* out, const void* in);              // 0x93c6d0
extern bool __cdecl SPKeyFromName(ResKey* key, const char* name, unsigned int a, unsigned int b);  // 0x68d5a0
extern Quat* __cdecl QuaternionFromMatrix33(Quat* out, const Mat3* m);     // 0x472b80

extern void* g_vtbl_145b2f8;    // 0x145b2f8
extern void* g_vtbl_145b2ec;    // 0x145b2ec
extern void* g_vtbl_13eb938;    // 0x13eb938
extern void* g_vtbl_13ef094;    // 0x13ef094

extern char g_emptyString16[];  // 0x1667bac  (eastl::gEmptyString16)
extern const char g_allocator_file[];  // 0x13ebb38
extern const char g_hide[];            // 0x145b804
extern const float g_167a548;          // 0x167a548
extern const float g_167a54c;          // 0x167a54c
extern const float g_167a550;          // 0x167a550
extern const float g_167a5a4;          // 0x167a5a4
extern const float g_167a5a8;          // 0x167a5a8
extern const float g_167a5ac;          // 0x167a5ac
extern const float g_1485720;          // 0x1485720
extern const float g_145b2d4;          // 0x145b2d4
extern Mat3 g_167a5d8;                 // 0x167a5d8
extern Mat3 g_167a5b0;                 // 0x167a5b0

// ================================================================================
// command objects
// ================================================================================

// @ 0x00adaad0
void __fastcall FUN_00adaad0(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x0476ad30;
    const char** av = args->MainArguments(1);
    const char* s = av[0];
    m->f08 = (int)FNV1_String8(s, 0x811c9dc5, 1);
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00adac70
void __fastcall FUN_00adac70(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x04cea5ff;
    const char** av = args->MainArguments(2);
    const char* s = av[0];
    m->f08 = (int)FNV1_String8(s, 0x811c9dc5, 1);
    *(float*)&m->f10 = PARSER(self)->ParseF(av[1]);
    int flags = 0;
    if (args->OptionArguments("objects", 0))  flags = 1;
    if (args->OptionArguments("animals", 0))  flags |= 2;
    if (args->OptionArguments("snap", 0))     flags |= 4;
    if (args->OptionArguments("citizens", 0)) flags |= 8;
    m->f18 = flags;
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// ================================================================================
// Sim:: viewer/camera command (0xadad70)
// ================================================================================

// @ 0x00adad70
void __fastcall FUN_00adad70(void* self, int /*edx*/)
{
    char* s = (char*)self;
    if (*(char*)(s + 0x2a) != 0) return;

    Viewer13C* v13c = *(Viewer13C**)(s + 0x13c);
    *(unsigned int*)(s + 0x144) = (unsigned int)v13c->v15();

    FUN_00b5cde0((void*)FUN_00b3d230(0x8916f92d));

    SetRef((void**)(s + 0x168), (RefObj*)v13c->v14());
    char* e = *(char**)(s + 0x168);
    e[0x10b] = 1;
    e[0x108] = 0;
    e[0x10a] = 1;
    ((EMat*)e)->SetFlag(4);

    XForm xf = { 0, 0, g_167a548, g_167a54c, g_167a550, g_1485720, Mat3(g_167a5d8) };

    cViewer* viewer = *(cViewer**)(s + 0x40);
    viewer->GetTransform(&xf);
    ((EMat*)e)->SetXForm(xf);
    ((EMat*)e)->SetValue(0.0f);
    ((EMat*)e)->Update();

    Quat q;
    QuaternionFromMatrix33(&q, &xf.m);
    ((EMat*)e)->SetRotation(q);

    XForm xf2 = { 0, 0, g_167a5a4, g_167a5a8, g_167a5ac, g_1485720, Mat3(g_167a5b0) };

    float ox = xf.x * xf2.w;
    float oy = xf.y * xf2.w;
    float oz = xf.z * xf2.w;
    xf2.x += xf2.m.m[0] * ox + xf2.m.m[3] * oy + xf2.m.m[6] * oz;
    xf2.y += xf2.m.m[1] * ox + xf2.m.m[4] * oy + xf2.m.m[7] * oz;
    xf2.z += xf2.m.m[2] * ox + xf2.m.m[5] * oy + xf2.m.m[8] * oz;
    xf2.a |= 4;
    xf2.b = (unsigned short)(xf2.b + 1);
    ((Sim*)self)->sendXform(&xf2.x, 0x10);

    float fov = viewer->GetFieldOfView() * g_145b2d4;
    v13c->v01(0x109d352, &fov);

    *(char*)(s + 0x2a) = 1;
}

// ================================================================================
// Sim:: audio / hashtable helpers
// ================================================================================

// @ 0x00adb0b0
void __fastcall FUN_00adb0b0(void* self, int /*edx*/, unsigned int wanted)
{
    char* s = (char*)self;
    void** base = *(void***)(s + 0xf4);
    char* it = (char*)base[0];
    void** bucket = base;
    if (!it) {
        ++bucket;
        while (*bucket == 0) ++bucket;
        it = (char*)*bucket;
    }
    char* end = (char*)base[*(unsigned int*)(s + 0xf8)];

    Iter local;
    while (it != end) {
        unsigned int value = *(unsigned int*)(it + 4);
        if (*(int*)(it + 8) == (int)wanted) {
            Iter in;
            in.node = it;
            in.bucket = bucket;
            Iter* r = (Iter*)FUN_006859b0(&local, in);
            it = (char*)r->node;
            bucket = (void**)r->bucket;

            AudioSys* a1 = FUN_00a206f0();
            if (a1) {
                a1->a14(0x347536b);
                a1->a16(0x3475385, value);
                a1->a16(0x34753a0, 0);
                a1->a22();
            }
            AudioSys* a2 = FUN_00a206f0();
            if (a2) a2->a11(value);
        } else {
            it = *(char**)(it + 0xc);
            if (!it) {
                do { ++bucket; it = (char*)*bucket; } while (!it);
            }
        }
    }
}

// @ 0x00adb1b0
char __fastcall FUN_00adb1b0(void* self, int /*edx*/, unsigned int key, unsigned int* out)
{
    char* s = (char*)self;
    unsigned int local[2];
    HTbl* h = (HTbl*)(s + 0x90);
    h->Find((Iter*)local, &key);
    if (local[0] != h->arr[h->count]) {
        *out = *(unsigned int*)(local[0] + 0x10);
        return 1;
    }
    HTbl* h2 = (HTbl*)(s + 0xb0);
    unsigned int* r = (unsigned int*)h2->Find((Iter*)local, &key);
    if (r[0] != h2->arr[h2->count]) {
        *out = *(unsigned int*)(r[0] + 0x10);
        return 1;
    }
    *out = 0;
    return 0;
}

// @ 0x00adb250
int __fastcall FUN_00adb250(void* self, int /*edx*/, unsigned int key, unsigned int wanted)
{
    unsigned int local[4];
    HTEqualRange* h = (HTEqualRange*)((char*)self + 0x5c);
    unsigned int* r = (unsigned int*)h->equal_range(local, &key);
    unsigned int it = r[0];
    unsigned int bucket = r[1];
    unsigned int end = r[2];
    while (it != end) {
        unsigned int v = *(unsigned int*)(it + 4);
        if (*(unsigned int*)(v + 4) == wanted) return (int)v;
        it = *(unsigned int*)(it + 8);
        while (it == 0) {
            it = *(unsigned int*)(bucket + 4);
            bucket += 4;
        }
    }
    return 0;
}

// @ 0x00adb2a0
char __fastcall FUN_00adb2a0(void* self, int /*edx*/, unsigned int a, unsigned int b)
{
    char* s = (char*)self;
    unsigned int keys[2];
    keys[0] = *(unsigned int*)(s + 0x148);
    keys[1] = 0;
    for (int i = 0; i < 2; ++i) {
        void* r = (void*)((Sim*)self)->Lookup(0x4474369, keys[i]);
        if (!r) continue;
        IEntry* obj = (IEntry*)r;
        void* payload = obj->s3(0x446e39c);
        if (!payload) continue;
        char* p = (char*)payload;
        unsigned int local[2];
        HTbl* h = (HTbl*)(p + 0x10);
        h->findKey(local, &a);
        if (local[0] != h->arr[h->count]) {
            FUN_00ad9010((void*)(local[0] + 4));
            return 1;
        }
    }
    char (__cdecl *fn)(unsigned int, unsigned int) =
        *(char (__cdecl **)(unsigned int, unsigned int))(s + 0x20);
    if (fn) return fn(a, b);
    return 0;
}

// @ 0x00adb360
char __fastcall FUN_00adb360(void* self, int /*edx*/, unsigned int a)
{
    char* s = (char*)self;
    unsigned int keys[2];
    keys[0] = *(unsigned int*)(s + 0x148);
    keys[1] = 0;
    for (int i = 0; i < 2; ++i) {
        void* r = (void*)((Sim*)self)->Lookup(0x4474369, keys[i]);
        if (!r) continue;
        IEntry* obj = (IEntry*)r;
        Cursor* c = (Cursor*)obj->s3(0x446e39c);
        if (!c) continue;
        if (c->Method(a)) return 1;
    }
    return 0;
}

// @ 0x00adb3d0
char __fastcall FUN_00adb3d0(void* self, int /*edx*/, unsigned int a, unsigned int* out)
{
    char* s = (char*)self;
    unsigned int keys[2];
    keys[0] = *(unsigned int*)(s + 0x148);
    keys[1] = 0;
    for (int i = 0; i < 2; ++i) {
        void* r = (void*)((Sim*)self)->Lookup(0x477df4b, keys[i]);
        if (!r) continue;
        IEntry* obj = (IEntry*)r;
        void* payload = obj->s3(0x477e049);
        if (!payload) continue;
        unsigned int local[2];
        HTbl* h = (HTbl*)((char*)payload + 0x10);
        h->find(local, &a);
        if (local[0] != h->arr[h->count]) {
            out[0] = *(unsigned int*)(local[0] + 4);
            out[1] = *(unsigned int*)(local[0] + 8);
            out[2] = *(unsigned int*)(local[0] + 0xc);
            return 1;
        }
    }
    return 0;
}

// @ 0x00adb680
void __stdcall FUN_00adb680(void* list, unsigned int count)
{
    char** arr = (char**)list;
    for (unsigned int i = 0; i < count; ++i) {
        char* p = arr[i];
        while (p) {
            char* next = *(char**)(p + 0x38);
            *(void**)(p + 4) = &g_vtbl_145b2f8;
            *(void**)(p + 0xc) = &g_vtbl_145b2ec;
            void* q = *(void**)(p + 0x10);
            if (q) ((RefObj*)q)->Release();
            *(void**)(p + 0xc) = &g_vtbl_13eb938;
            *(void**)(p + 4) = &g_vtbl_13ef094;
            operator_delete_array(p);
            p = next;
        }
        arr[i] = 0;
    }
}

// ================================================================================
// ribbon static commands (0xadb700 / 0xadb8d0 / 0xadbaa0)
// ================================================================================

// @ 0x00adb700
void __fastcall FUN_00adb700(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    if (args->HasFlag(g_hide)) {
        m->tag = 0x05b70e8b;
    } else {
        m->tag = 0x04448b85;
        int n = 0;
        const char** av = args->MainArguments(&n, 1, 2);
        const char* src = av[0];
        int len = 0;
        while (src[len] != 0) ++len;
        char* p;
        char* end;
        if (len + 1 < 2) {
            p = g_emptyString16;
            end = g_emptyString16 + 1;
        } else {
            p = (char*)operator new(len + 1, "Simulator", 0, 0, g_allocator_file, 0xd1);
            end = p + len + 1;
        }
        FUN_011e0744(p, src, len);
        p[len] = 0;

        ResKey key;
        key.f0 = -1; key.f4 = -1; key.f8 = -1;
        void* w[4];
        FUN_0093c6d0(w, &p);
        if (n >= 2) SPKeyFromName(&key, av[1], 0, 0);
        m->f08 = key.f8;
        m->f10 = key.f0;

        if (((int)(end - p) & ~1) > 2 && p) operator_delete_array(p);
        if ((int)((char*)w[1] - (char*)w[0]) > 1 && w[0]) operator_delete_array(w[0]);
    }
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00adb8d0
void __fastcall FUN_00adb8d0(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    if (args->HasFlag(g_hide)) {
        m->tag = 0x07982226;
    } else {
        m->tag = 0x0798207d;
        int n = 0;
        const char** av = args->MainArguments(&n, 1, 2);
        const char* src = av[0];
        int len = 0;
        while (src[len] != 0) ++len;
        char* p;
        char* end;
        if (len + 1 < 2) {
            p = g_emptyString16;
            end = g_emptyString16 + 1;
        } else {
            p = (char*)operator new(len + 1, "Simulator", 0, 0, g_allocator_file, 0xd1);
            end = p + len + 1;
        }
        FUN_011e0744(p, src, len);
        p[len] = 0;

        ResKey key;
        key.f0 = -1; key.f4 = -1; key.f8 = -1;
        void* w[4];
        FUN_0093c6d0(w, &p);
        if (n >= 2) SPKeyFromName(&key, av[1], 0, 0);
        m->f08 = key.f8;
        m->f10 = key.f0;

        if (((int)(end - p) & ~1) > 2 && p) operator_delete_array(p);
        if ((int)((char*)w[1] - (char*)w[0]) > 1 && w[0]) operator_delete_array(w[0]);
    }
    STATE(self)->AddMessage(args, m, 0);
    m->Release();
}

// @ 0x00adbaa0
void __fastcall FUN_00adbaa0(void* self, int /*edx*/, cArguments* args)
{
    Msg* m = new ("Simulator", 0, 0, 0, 0) Msg();
    if (m) m->AddRef();
    m->tag = 0x067a195b;
    int n = 0;
    const char** av = args->MainArguments(&n, 1, 2);
    const char* src = av[0];
    int len = 0;
    while (src[len] != 0) ++len;
    char* p;
    char* end;
    if (len + 1 < 2) {
        p = g_emptyString16;
        end = g_emptyString16 + 1;
    } else {
        p = (char*)operator new(len + 1, "Simulator", 0, 0, g_allocator_file, 0xd1);
        end = p + len + 1;
    }
    FUN_011e0744(p, src, len);
    p[len] = 0;

    ResKey key;
    key.f0 = -1; key.f4 = -1; key.f8 = -1;
    void* w[4];
    FUN_0093c6d0(w, &p);
    if (n >= 2) SPKeyFromName(&key, av[1], 0, 0);

    float duration = 2.0f;
    const char** d = args->OptionArguments("duration", 1);
    if (d) duration = PARSER(self)->ParseF(d[0]);

    m->f08 = key.f8;
    m->f10 = key.f0;
    *(float*)&m->f18 = duration;

    STATE(self)->AddMessage(args, m, 0);

    if (((int)(end - p) & ~1) > 2 && p) operator_delete_array(p);
    if ((int)((char*)w[1] - (char*)w[0]) > 1 && w[0]) operator_delete_array(w[0]);
    m->Release();
}
