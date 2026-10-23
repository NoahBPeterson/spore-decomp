// Slice s00f22d50 (batch gold5) -- SP drama-event / EP1 powerup-spawner helpers.
// Module "Spore" (VS2008 SP1, cl 15.00.30729.01).  Flags: /O2 /MD /Gy /TP /arch:SSE2 /fp:fast
//
// Virtual-slot model recovered from the call sites:
//   +0x04 GetNoun()        -> int*
//   +0x08 GetOwner()       -> int*
//   +0x0c GetComponent(id) -> void*
//   +0x24 GetProperty(key, void**) -> char
//   +0x28 (void* out, int tag)
//   +0x2c GetPosition()    -> float*   (also PropertyManager slot: Find(hash, tag, out))
//   +0x30 GetOrientation() -> float*
//   +0x34 GetScale()       -> float
//   +0x38/+0x3c set vector3, +0x40 set float
//   +0x44 (void*,void*)    +0x48 (void*,float,void*,int,int,int)
//   +0x54 (int)            +0x6c bbox(void*) -> float*
//   +0xdc (void*)          +0xec vec()
// `ev[6]` == *(int*)(ev + 0x18) is the owning object of property lookups.

#include "types.h"

typedef unsigned int uint;

// Plain 3-float vector used for aggregate temporaries.
struct V3f { float x, y, z; };

// ------------------------------------------------------------------ callees
extern "C" {
unsigned int DAT_016c7aa4;      // 0x016c7aa4  Simulator singleton
unsigned int DAT_016c8318;      // 0x016c8318  drama-event multimap
unsigned int DAT_016c8328;      // 0x016c8328  component key (data)
unsigned int DAT_016c83a4;      // key
unsigned int DAT_016c83b0;      // key
unsigned int DAT_016c83b4;      // key
unsigned int DAT_016c83c0;      // key
unsigned int DAT_016c83c4;      // key
unsigned int DAT_016c83d0;      // key
float        DAT_015d9c6c;      // 0.0f default
int          DAT_0164dc58;      // 0 default
float        DAT_015ada7c;      // float[4] {0,0,1,3.4e38}
float        DAT_01471064;      // 0.5f
float        DAT_01470f1c;      // 2.0f
unsigned int DAT_018c88e4;      // noun type id
char         DAT_0148c398[];    // "EP1_powerup_spawnerReincarnate"
}

float SP_GetPropertyT_float(void* owner, unsigned int key, float def);  // 0x004e1c70
void* FUN_00ac8fa0(void* owner, unsigned int key, int d);               // 0x00ac8fa0
char  FUN_00f203c0(void* noun, float v, void* cb);                      // 0x00f203c0
char  FUN_00f20350(void* noun, float v, void* cb);                      // 0x00f20350
void  FUN_00f21d30(void* pos, void* orient, float scale, unsigned int spid); // 0x00f21d30
void  FUN_00f22630(void* noun, void* spid);                             // 0x00f22630
void* SP_NounManager(void);                                             // 0x00b3d300
void* FUN_00b3d240(void);                                               // 0x00b3d240
void  FUN_00f21080(void* a, void* b, float c, float d, float e);        // 0x00f21080
void  FUN_00f20a60(void* out, void* in);                                // 0x00f20a60
void  FUN_00f20be0(void* out, void* a, unsigned int b, unsigned int c,
                   unsigned int d, unsigned int e);                     // 0x00f20be0
void  FUN_00f20cb0(void* a, void* b);                                   // 0x00f20cb0
char  FUN_00f21310(void* ev, void* pos, void* orient);                  // 0x00f21310
int*  FUN_00f213f0(void* a, void* b, int c);                            // 0x00f213f0
float* FUN_0059aed0(void* out, void* a, void* b);                       // 0x0059aed0
unsigned int FNV1_String8(const char* s, unsigned int basis, int flags); // 0x00932e80
void* SP_PropertyManager(void);                                         // 0x0067de30
void* SP_App(void);                                                     // 0x0067dd10
void  FUN_00d25e00(void* o);                                            // 0x00d25e00
void  FUN_00f47380(void* p);                                            // 0x00f47380  operator delete
void  FUN_00f20590(void);                                               // callback
void  FUN_00f205d0(void);                                               // callback
void  FUN_00f20b60(void);                                               // callback
void  FUN_00f20b20(void);                                               // callback

// thiscall callees: modelled as member functions of an opaque object so that
// `self` lands in ECX and the callee cleans its stack arguments (ret N).
struct Fns {
    void   c0d0c0(unsigned a, int b);            // 0x00c0d0c0  CCB::d0c0
    void   c41d60(void* key);                    // 0x00c41d60
    void   c12310(unsigned id, int a, int b);    // 0x00c12310  InterruptAnimation
    void   c446d0(void* v, int n);               // 0x00c446d0  ApplyImpulse
    void   c6f770(int a, int b);                 // 0x00c6f770
    void   c15d50(void* info, int a, int b);     // 0x00c15d50
    float* d20610();                             // 0x00d20610  GetVelocity
    int*   f3f950(void* noun);                   // 0x00f3f950
    int*   b18530();                             // 0x00b18530  cGameData accessor
    int**  b1f9c0();                             // 0x00b1f9c0  item list begin/end
    void   b225d0(void* n);                      // 0x00b225d0  RemoveNoun
    void*  b20c60(void* type);                   // 0x00b20c60  CreateNoun
    void   f1be10(void* a, void* b);             // 0x00f1be10  AddObj
    void   f1b260(void* a, void* b, void* c);    // 0x00f1b260  q3
    void   f1c4b0();                             // 0x00f1c4b0  End
    void   d00f80(void** out, void* key);        // 0x00d00f80  tree find
    void   d25e00();                             // 0x00d25e00
};

// ------------------------------------------------------------------ vtables
struct Evt {
    virtual void  v00();
    virtual int*  v04();
    virtual int*  v08();
    virtual void* v0c(unsigned int id);
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  v1c();
    virtual void  v20();
    virtual char  v24(unsigned int key, void** out);
    virtual void  v28(void* out, int tag);
    virtual float* v2c();
    virtual float* v30();
    virtual float v34();
    virtual void  v38(void* v);
    virtual void  v3c(void* v);
    virtual void  v40(float f);
    virtual void  v44(void* a, void* b);
    virtual void  v48(void* a, float f, void* b, int x, int y, int z);
    virtual void  v4c();
    virtual void* v50();
    virtual void  v54(int v);
    virtual void  v58();
    virtual void  v5c(unsigned int id);
    virtual void  v60();
    virtual void  v64();
    virtual void  v68();
    virtual float* v6c(void* out);
    virtual void  v70();
    virtual void  v74();
    virtual void  v78();
    virtual void  v7c();
    virtual void  v80();
    virtual void  v84();
    virtual void  v88();
    virtual void  v8c();
    virtual void  v90();
    virtual void  v94();
    virtual void  v98();
    virtual void  v9c();
    virtual void  va0();
    virtual void  va4();
    virtual void  va8();
    virtual void  vac();
    virtual void  vb0();
    virtual void  vb4();
    virtual void  vb8();
    virtual void  vbc();
    virtual void  vc0();
    virtual void  vc4();
    virtual void  vc8();
    virtual void  vcc();
    virtual void  vd0();
    virtual void  vd4();
    virtual void  vd8();
    virtual void  vdc(void* v);
    virtual void  ve0();
    virtual void  ve4();
    virtual void  ve8();
    virtual void  vec();
};

// PropertyManager: slot +0x2c is a 3-argument finder.
struct PropMgr : Evt {
    void* v2c(unsigned int a, unsigned int b, void** out);
};

// 0x74-byte Simulator::cLocomotionRequest
struct LocomotionRequest {
    void* mpData;
    int   pad[28];
    LocomotionRequest();                 // 0x00ac9850
};

// tiny 3-pointer engine vector (eastl::vector/sp_fixed_vector); its dtor is
// called at scope exit by the original.
struct VecObj {
    void* a;
    void* b;
    void* c;
    void* pad0;
    void* pad1;
    ~VecObj();                           // 0x00ad92d0
};

// ------------------------------------------------------------------ getters
static float GetPropF(void* p, unsigned int key, void** out)
{
    float v;
    if (p != 0 && (*(char(__thiscall**)(void*, unsigned int, void**))((char*)*(void**)p + 0x24))(
                       p, key, out) != 0) {
        void* q = *out;
        unsigned short t = *(unsigned short*)((char*)q + 0x12);
        float* pv;
        if (t != 0xd && t != 0x10)
            pv = (float*)0x015d9c6c;
        else if (*(uint8_t*)((char*)q + 0x10) & 0x30)
            pv = (float*)*(int*)q;
        else
            pv = (float*)((t != 0 ? -1 : 0) & (int)q);
        v = *pv;
    } else
        v = 0.0f;
    return v;
}

static int GetPropI(void* p, unsigned int key, void** out)
{
    int v;
    if (p != 0 && (*(char(__thiscall**)(void*, unsigned int, void**))((char*)*(void**)p + 0x24))(
                       p, key, out) != 0) {
        void* q = *out;
        unsigned short t = *(unsigned short*)((char*)q + 0x12);
        int* pv;
        if (t != 0xa && t != 0x10)
            pv = (int*)0x0164dc58;
        else if (*(uint8_t*)((char*)q + 0x10) & 0x30)
            pv = (int*)*(int*)q;
        else
            pv = (int*)((t != 0 ? -1 : 0) & (int)q);
        v = *pv;
    } else
        v = 0;
    return v;
}

// --------------------------------------------------------- forward decls
void FUN_00f232a0(void* ev, unsigned int spid);
void FUN_00f23300(int* ev, int* noun, void* pos, void* orient, char flag);
void FUN_00f239f0(int* ev);

// ================================================================== 0x00f23c80
// int FUN_00f23c80(int a, int b)
// @ 0x00f23c80
int FUN_00f23c80(int a, int b)
{
    unsigned int key[2];
    key[0] = (unsigned int)a;
    key[1] = (unsigned int)b;
    void* m = (void*)DAT_016c8318;
    void* out;
    ((Fns*)((char*)m + 0x1c))->d00f80(&out, key);
    if (out != (void*)((char*)m + 0x20))
        return *(int*)((char*)out + 0x18);
    return -1;
}

// ================================================================== 0x00f23220
// void FUN_00f23220(int* a, void* b, float c, float d, float e)
// @ 0x00f23220
void FUN_00f23220(int* a, void* b, float c, float d, float e)
{
    VecObj vec;
    vec.a = 0;
    vec.b = 0;
    vec.c = 0;
    void* w = FUN_00b3d240();
    ((Evt*)w)->v48(b, d, &vec, 0, 0, 0);
    FUN_00f21080(a, &vec, c, d, e);
}

// ================================================================== 0x00f232a0
// void FUN_00f232a0(void* ev, unsigned int spid)
// @ 0x00f232a0
void FUN_00f232a0(void* ev, unsigned int spid)
{
    float local[3];
    ((Evt*)((char*)ev + 0x5a8))->v28(local, -1);
    Evt* c = (Evt*)((char*)ev + 0xc0);
    FUN_00f21d30(local, c->v30(), c->v34(), spid);
}

// ================================================================== 0x00f23300
// void FUN_00f23300(int* ev, int* noun, void* pos, void* orient, char flag)
// @ 0x00f23300
void FUN_00f23300(int* ev, int* noun, void* pos, void* orient, char flag)
{
    struct V3 { float x, y, z; } local;
    FUN_00f20a60(&local, pos);
    Evt* c = (Evt*)((char*)noun + 0xc0);
    c->v44(&local, orient);
    *(char*)((char*)noun + 0x137) = 0;
    ((Fns*)c)->c41d60(&DAT_016c8328);
    c->vec();
    int* gd = ((Fns*)((Evt*)ev)->v04())->b18530();
    if (*(int*)((char*)gd + 0x48) == 0) {
        void* o = (void*)ev[6];
        if (flag) FUN_00f232a0(noun, (uint)FUN_00ac8fa0(o, DAT_016c83b0, 0));
        else      FUN_00f232a0(noun, (uint)FUN_00ac8fa0(o, DAT_016c83b4, 0));
    }
}

// ================================================================== 0x00f22d50
// void FUN_00f22d50(int* ev, int* noun)
// @ 0x00f22d50
void FUN_00f22d50(int* ev, int* noun)
{
    void* o1 = (void*)ev[6];
    float a = SP_GetPropertyT_float(o1, DAT_016c83c4, 0.0f);
    void* o2 = (void*)ev[6];
    float b = SP_GetPropertyT_float(o2, DAT_016c83c0, 0.0f);
    *(float*)((char*)noun + 0xb14) = a;
    *(char*)((char*)noun + 0xb10) = 1;
    FUN_00f203c0(noun, b, (void*)FUN_00f20590);

    int* r1 = ((Evt*)ev)->v08();
    int* r2 = ((Evt*)ev)->v08();
    int* r3 = ((Evt*)ev)->v08();
    void* o3 = (void*)ev[6];
    FUN_00f21d30(((Evt*)r3)->v2c(), ((Evt*)r2)->v30(), ((Evt*)r1)->v34(),
                 (unsigned int)FUN_00ac8fa0(o3, DAT_016c83a4, 0));
    void* o4 = (void*)ev[6];
    FUN_00f22630(noun, (void*)FUN_00ac8fa0(o4, DAT_016c83b0, 0));

    int** it = ((Fns*)SP_NounManager())->b1f9c0();
    int* p = it[0];
    int* last = it[1];
    for (; p != last; ++p) {
        int* item = (int*)*p;
        void* s1; void* s2; void* s3;
        float c = GetPropF((void*)ev[6], DAT_016c83c4, &s1);
        float d = GetPropF((void*)ev[6], DAT_016c83c0, &s2);
        *(char*)((char*)item + 0xb10) = 1;
        *(float*)((char*)item + 0xb14) = c;
        FUN_00f203c0(item, d, (void*)FUN_00f20590);
        FUN_00f22630(item, (void*)GetPropI((void*)ev[6], DAT_016c83b0, &s3));
    }

    void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x78);
    ((Fns*)mgr)->f1be10(((Evt*)ev)->v04(), noun);
    ((Fns*)SP_NounManager())->b225d0(((Evt*)ev)->v04());
    ((Fns*)(*(void**)((char*)DAT_016c7aa4 + 0x78)))->f1c4b0();
}

// ================================================================== 0x00f23000
// void FUN_00f23000(int* ev, int* noun)
// @ 0x00f23000
void FUN_00f23000(int* ev, int* noun)
{
    void* o0 = (void*)ev[6];
    float f = SP_GetPropertyT_float(o0, DAT_016c83c0, 0.0f);
    ((Fns*)noun)->c0d0c0(7, 1);
    FUN_00f203c0(noun, f, (void*)FUN_00f205d0);

    int* r1 = ((Evt*)ev)->v08();
    int* r2 = ((Evt*)ev)->v08();
    int* r3 = ((Evt*)ev)->v08();
    void* o1 = (void*)ev[6];
    FUN_00f21d30(((Evt*)r3)->v2c(), ((Evt*)r2)->v30(), ((Evt*)r1)->v34(),
                 (unsigned int)FUN_00ac8fa0(o1, DAT_016c83a4, 0));
    void* o2 = (void*)ev[6];
    FUN_00f22630(noun, (void*)FUN_00ac8fa0(o2, DAT_016c83b0, 0));

    int** it = ((Fns*)SP_NounManager())->b1f9c0();
    int* p = it[0];
    int* last = it[1];
    for (; p != last; ++p) {
        int* item = (int*)*p;
        void* s1; void* s2;
        float c = GetPropF((void*)ev[6], DAT_016c83c0, &s1);
        ((Fns*)item)->c0d0c0(7, 1);
        FUN_00f203c0(item, c, (void*)FUN_00f205d0);
        FUN_00f22630(item, (void*)GetPropI((void*)ev[6], DAT_016c83b0, &s2));
    }

    void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x78);
    ((Fns*)mgr)->f1be10(((Evt*)ev)->v04(), noun);
    ((Fns*)SP_NounManager())->b225d0(((Evt*)ev)->v04());
    ((Fns*)(*(void**)((char*)DAT_016c7aa4 + 0x78)))->f1c4b0();
}

// ================================================================== 0x00f233b0
// void FUN_00f233b0(int* ev, int* noun)
// @ 0x00f233b0
void FUN_00f233b0(int* ev, int* noun)
{
    if (*(char*)((char*)noun + 0xe60) == 1)
        return;
    if ((char)(*(unsigned int*)((char*)noun + 0xb58) >> 8) & 1)
        return;

    void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x78);
    ((Fns*)mgr)->f1be10(((Evt*)ev)->v04(), noun);

    float pos[3];
    float orient[4];
    if (FUN_00f21310(ev, pos, orient) == 0)
        return;

    float* np = ((Evt*)((char*)noun + 0xc0))->v2c();
    float d[3];
    d[0] = pos[0] - np[0];
    d[1] = pos[1] - np[1];
    d[2] = pos[2] - np[2];

    int* gd = ((Fns*)((Evt*)ev)->v04())->b18530();
    if (*(int*)((char*)gd + 0x24) == 0) {
        int* r1 = ((Evt*)ev)->v08();
        int* r2 = ((Evt*)ev)->v08();
        int* r3 = ((Evt*)ev)->v08();
        void* o = (void*)ev[6];
        FUN_00f21d30(((Evt*)r3)->v2c(), ((Evt*)r2)->v30(), ((Evt*)r1)->v34(),
                     (unsigned int)FUN_00ac8fa0(o, DAT_016c83a4, 0));
    }

    char flag = (char)((*(unsigned int*)((char*)noun + 0xb58) >> 9) & 1);
    FUN_00f23300(ev, noun, pos, orient, flag);

    if (flag) {
        void* a = SP_App();
        void* b = (*(void*(__thiscall**)(void*))((char*)*(void**)a + 0x50))(a);
        void* c = (*(void*(__thiscall**)(void*))((char*)*(void**)b + 0x38))(b);
        if (c) {
            void* dd = (*(void*(__thiscall**)(void*, unsigned int))((char*)*(void**)c + 0x0c))(
                           c, 0x2a7ecd2);
            if (dd)
                ((Fns*)dd)->d25e00();
        }
    }

    float v = DAT_01470f1c;
    *(char*)((char*)noun + 0xe60) = 1;
    FUN_00f20350(noun, v, (void*)FUN_00f20b60);

    int** it = ((Fns*)SP_NounManager())->b1f9c0();
    int* p = it[0];
    int* last = it[1];
    for (; p != last; ++p) {
        int* item = (int*)*p;
        float* ip = ((Evt*)((char*)item + 0xc0))->v2c();
        V3f a;
        a.x = ip[0] + d[0];
        a.y = ip[1] + d[1];
        a.z = ip[2] + d[2];
        float pt[3] = { a.x, a.y, a.z };
        FUN_00f23300(ev, item, pt, orient, 0);
    }
}

// ================================================================== 0x00f235e0
// void FUN_00f235e0(int* ev, int* noun)
// @ 0x00f235e0
void FUN_00f235e0(int* ev, int* noun)
{
    void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x78);
    ((Fns*)mgr)->f1be10(((Evt*)ev)->v04(), noun);
    if (*(char*)((char*)noun + 0xe61) == 1)
        return;

    float tmp[3];
    float* dp = FUN_0059aed0(tmp, &DAT_015ada7c,
                             ((Evt*)((Evt*)ev)->v08())->v30());
    float d0 = dp[0];
    float d1 = dp[1];
    float d2 = dp[2];

    int* sub = ev - 0xd;
    void* rr = sub ? (void*)((Evt*)sub)->v0c(0x1186577) : 0;

    float bb[6];
    float* q = ((Evt*)((char*)noun + 0xc0))->v6c(bb);
    V3f mm;
    mm.x = (q[0] + q[3]) * 0.5f;
    mm.y = (q[4] + q[1]) * 0.5f;
    mm.z = (q[5] + q[2]) * 0.5f;
    tmp[0] = mm.x;
    tmp[1] = mm.y;
    tmp[2] = mm.z;

    float* pp = ((Evt*)rr)->v2c();
    float dot = (tmp[1] - pp[1]) * d1 + (tmp[2] - pp[2]) * d2 + (tmp[0] - pp[0]) * d0;
    if (0.0f > dot)
        return;

    int* g = ((Fns*)*(void**)((char*)DAT_016c7aa4 + 0x74))->f3f950(((Evt*)ev)->v04());
    float speed = *(float*)((char*)g + 0x4a0) * DAT_01470f1c;
    float* vel = ((Fns*)((char*)noun + 0xc0))->d20610();
    float t = speed - (vel[1] * d1 + vel[2] * d2 + vel[0] * d0);
    float d2v[3];
    d2v[0] = d0 * t;
    d2v[1] = d1 * t;
    d2v[2] = d2 * t;

    if (((*(unsigned int*)((char*)noun + 0xb58) >> 9) & 1) != 0) {
        LocomotionRequest req;
        ((Evt*)((char*)noun + 0xc0))->vdc(&req);
        if (req.mpData && *(int*)((char*)req.mpData - 4) != 0)
            FUN_00f47380(req.mpData);
    }

    ((Fns*)((char*)noun + 0xc0))->c446d0(d2v, 0);
    ((Fns*)noun)->c12310(0x7b5063e, -1, 0);
    float v = DAT_01471064;
    *(char*)((char*)noun + 0x137) = 0;
    *(int*)((char*)noun + 0x2b0) = 3;
    *(char*)((char*)noun + 0x164) = 1;
    *(char*)((char*)noun + 0xe61) = 1;
    FUN_00f20350(noun, v, (void*)FUN_00f20b20);

    int* r1 = ((Evt*)ev)->v08();
    int* r2 = ((Evt*)ev)->v08();
    int* r3 = ((Evt*)ev)->v08();
    FUN_00f21d30(((Evt*)r3)->v2c(), ((Evt*)r2)->v30(), ((Evt*)r1)->v34(),
                 (unsigned int)FUN_00ac8fa0((void*)ev[6], DAT_016c83a4, 0));
    FUN_00f22630(noun, (void*)FUN_00ac8fa0((void*)ev[6], DAT_016c83b0, 0));
}

// ================================================================== 0x00f238e0
// void* FUN_00f238e0(int* arg)
// @ 0x00f238e0
void* FUN_00f238e0(int* arg)
{
    void* local = 0;
    unsigned int h = FNV1_String8(DAT_0148c398, 0x811c9dc5u, 1);
    void* pm = SP_PropertyManager();
    if (local) {
        void* t = local;
        local = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)t + 4))(t);
    }
    ((PropMgr*)pm)->v2c(h, 0xd87454e6u, &local);
    int* res = FUN_00f213f0(local, arg, *arg);

    if (*(int*)((char*)DAT_016c7aa4 + 0xcc) != 1) {
        void* x = res ? (void*)((Evt*)res)->v0c(0x175cdc9) : 0;
        (*(void(__thiscall**)(void*, int))((char*)*(void**)x + 0x54))(x, 0);
        *(int*)((char*)x + 0x3c) = 0;
        *(int*)((char*)x + 0x40) = 0;
        *(char*)((char*)x + 0xe5) = 0;
        *(int*)((char*)x + 0x44) = 0;
    }
    void* y = res ? (void*)((Evt*)res)->v0c(0x1186577) : 0;
    (*(void(__thiscall**)(void*, void*))((char*)*(void**)y + 0x38))(y, (char*)arg + 4);
    (*(void(__thiscall**)(void*, void*))((char*)*(void**)y + 0x3c))(y, (char*)arg + 0x10);
    (*(void(__thiscall**)(void*, float))((char*)*(void**)y + 0x40))(y, *(float*)((char*)arg + 0x20));
    if (local)
        (*(void(__thiscall**)(void*))((char*)*(void**)local + 4))(local);
    return res;
}

// ================================================================== 0x00f239f0
// void FUN_00f239f0(int* ev)
// @ 0x00f239f0
void FUN_00f239f0(int* ev)
{
    int* n = ((Evt*)ev)->v04();
    int p1c = *(int*)((char*)n + 0x1c);
    int p18 = *(int*)((char*)((Evt*)ev)->v04() + 0x18);
    int* gd = ((Fns*)((Evt*)ev)->v04())->b18530();

    float pos[3];
    float* sp = ((Evt*)((Evt*)ev)->v08())->v2c();
    pos[0] = sp[0];
    pos[1] = sp[1];
    pos[2] = sp[2];

    float scale = ((Evt*)((Evt*)ev)->v08())->v34();

    float orient[4];
    float* so = ((Evt*)((Evt*)ev)->v08())->v30();
    orient[0] = so[0];
    orient[1] = so[1];
    orient[2] = so[2];
    orient[3] = so[3];

    int u1c[3];
    FUN_00f20be0(u1c, (void*)ev[6], DAT_016c83d0, 0, 0, 0);
    unsigned int spid = (unsigned int)FUN_00ac8fa0((void*)ev[6], DAT_016c83a4, 0);
    ((Fns*)SP_NounManager())->b225d0(((Evt*)ev)->v04());
    FUN_00f21d30(pos, orient, scale, spid);

    if (*(int*)((char*)gd + 0x48) != 1) {
        void* nn = ((Fns*)SP_NounManager())->b20c60(&DAT_018c88e4);
        ((Fns*)nn)->c6f770(1, 0);
        if (*(int*)((char*)gd + 0x48) == 2) {
            *(int*)((char*)nn + 0x3c) = *(int*)((char*)gd + 0x50);
            *(int*)((char*)nn + 0x40) = *(int*)((char*)gd + 0x54);
            *(int*)((char*)nn + 0x44) = *(int*)((char*)gd + 0x58);
        } else {
            *(int*)((char*)nn + 0x3c) = u1c[0];
            *(int*)((char*)nn + 0x40) = u1c[1];
            *(int*)((char*)nn + 0x44) = u1c[2];
        }
        Evt* e70 = (Evt*)((char*)nn + 0x70);
        e70->v38(pos);
        e70->v3c(orient);
        e70->v40(scale);
        *(int*)((char*)nn + 0x18) = p18;
        *(int*)((char*)nn + 0x38) = 0xe;
        *(int*)((char*)nn + 0x1c) = p1c;
        FUN_00f20cb0(nn, (void*)((Evt*)ev)->v04());
    }
}

// ================================================================== 0x00f23be0
// void FUN_00f23be0(void* a, int* b, int* c)
// @ 0x00f23be0
void FUN_00f23be0(void* a, int* b, int* c)
{
    FUN_00f239f0(c);
    void* o = (void*)b[6];
    FUN_00f22630(a, (void*)FUN_00ac8fa0(o, DAT_016c83b0, 0));

    void* mgr = *(void**)((char*)DAT_016c7aa4 + 0x78);
    ((Fns*)mgr)->f1b260(((Evt*)c)->v04(), ((Evt*)b)->v04(), a);
    ((Fns*)a)->c15d50(((Evt*)b)->v08(), 1, 0);
    ((Fns*)SP_NounManager())->b225d0(((Evt*)b)->v04());
    ((Fns*)(*(void**)((char*)DAT_016c7aa4 + 0x78)))->f1c4b0();
}
