// s00d3f9e0 -- avatar-death scenario / pooled-list slice (retail Spore).
// Offsets and call sequences come from work/match/scratch_s00d3f9e0_cards.txt.
// Every function has exactly one `// @ 0x<VA>` marker above it.

typedef void  (__thiscall* TFnV)(void*);
typedef void  (__thiscall* TFnVI)(void*, int);
typedef void  (__thiscall* TFnVII)(void*, int, int);
typedef void  (__thiscall* TFnVIII)(void*, int, int, int);
typedef void  (__thiscall* TFnVP)(void*, void*);
typedef void  (__thiscall* TFnVPP)(void*, void*, void*);
typedef void  (__thiscall* TFnVPPP)(void*, void*, void*, void*);
typedef void  (__thiscall* TFnVIP)(void*, int, void*, int);
typedef int   (__thiscall* TFnI)(void*);
typedef int   (__thiscall* TFnII)(void*, int);
typedef int   (__thiscall* TFnIIP)(void*, int, int, void*);
typedef int   (__thiscall* TFnIP)(void*, void*);
typedef float (__thiscall* TFnF)(void*);
typedef float (__thiscall* TFnFI)(void*, int);
typedef void* (__thiscall* TFnPU)(void*);
typedef void* (__thiscall* TFnPUP)(void*, void*);

// explicit thiscall shapes for helpers reached through raw addresses
typedef void  (__thiscall* TC_V)(void*);
typedef void  (__thiscall* TC_VI)(void*, int);
typedef void  (__thiscall* TC_VII)(void*, int, int);
typedef void  (__thiscall* TC_VF)(void*, float);
typedef void  (__thiscall* TC_VIFIIII)(void*, int, float, int, int, int, int);
typedef void  (__thiscall* TC_VP)(void*, void*);
typedef void  (__thiscall* TC_VPP)(void*, void*, void*);
typedef void  (__thiscall* TC_VIPIIII)(void*, const char*, int, int, int, int, int);
typedef void* (__thiscall* TC_P)(void*);
typedef void* (__thiscall* TC_PP)(void*, void*);
typedef void* (__thiscall* TC_PPP)(void*, void*, void*);
typedef int   (__thiscall* TC_I)(void*);
typedef int   (__thiscall* TC_II)(void*, int);

#define VT(o, off) (*(void***)(o))[(off) / 4]

// ---------------------------------------------------------------------------
// small math / message types

struct V3 { float x, y, z; };

struct M33 { float m[9]; };

// 0x14-byte cSPVector3 list payload of a Vec18 (allocator piggybacks in the header).
struct Vec20B {
    int mBegin;      // +0x00
    int mEnd;        // +0x04
    int mCap;        // +0x08
    int mPoolA;      // +0x0c
    int mPoolB;      // +0x10

    void* __thiscall Ctor(const Vec20B* src);   // 0x00473460
    void  __thiscall Assign(const Vec20B* src); // 0x00473500
};

// 0x18-byte element: a weight and a cSPVector3 list.
struct Vec18 {
    float  mWeight;    // +0x00
    Vec20B mVectors;   // +0x04
};

struct Vec18Vec {
    Vec18* mpBegin;    // +0x00
    Vec18* mpEnd;      // +0x04
    Vec18* mpCap;      // +0x08

    void __thiscall InsertN(Vec18* pos, unsigned n, const Vec18* val); // 0x00d3fa90
};

// Transformation message understood by cSPTransformOps (0x38 bytes).
struct TransformMsg {
    unsigned short mFlags0;      // +0x00 (bit 2 = translation present)
    unsigned short mCount0;      // +0x02
    V3             mTranslation; // +0x04
    unsigned short mFlags1;      // +0x10 (bit 2 = rotation present)
    unsigned short mCount1;      // +0x12
    M33            mRotation;    // +0x14
};

// 0x3c-byte transform (same message layout plus a scale).
struct cSPTransform {
    TransformMsg mT;             // +0x00
    float        mScale;         // +0x38

    void* __thiscall Assign(const void* msg);  // 0x00537dc0
};

// ---------------------------------------------------------------------------
// pooled node lists (00d3f9e0)

struct NodeBuf {
    int*  mpData;    // +0x00 (new[]-allocated, element count at mpData[-1])
    int   miCount;   // +0x04

    void __thiscall Reset(int* data, int count);  // 0x00d3b320
};

struct Node {
    void*   mpFirst;   // +0x000
    void*   mpRef;     // +0x004 (refcounted, vtable slot 1 = Release)
    NodeBuf mBuf;      // +0x008
    char    pad0[0x184 - 0x010];
    Node*   mpNext;    // +0x184
};

struct NodePool {
    char   pad0[0x1c];
    Node*  mpFreeList;   // +0x1c
    char   pad1[4];
    Node*  mpPoolBegin;  // +0x24
    Node*  mpPoolEnd;    // +0x28
    char   pad2[4];
    Node*  mpSentinel;   // +0x30

    void __thiscall FreeLists(Node** arr, unsigned count);  // 0x00d3f9e0
};

// ---------------------------------------------------------------------------
// managers (this = the manager singletons)

struct NounVec {
    int    mUnk0;      // +0x00
    void** mpBegin;    // +0x04
    void** mpEnd;      // +0x08
};

struct NounMgr {
    void*    __thiscall GetAvatar();                       // 0x00b1fdb0
    void*    __thiscall GetCurrentTerrainSphere();         // 0x00f67d90
    NounVec* __thiscall GetGameDataVector(int a, int b, int c, int d, int e); // 0x00b21340
};

struct TriggerMgr {
    char pad0[0x2c];
    int  miState;      // +0x2c
};

extern "C" NounMgr*    __cdecl SP_NounManager();        // 0x00b3d300
extern "C" TriggerMgr* __cdecl SP_GetTriggerMgr();      // 0x00b3d4d0
extern "C" void*       __cdecl SP_EffectsManager();     // 0x0067ddd0
extern "C" void*       __cdecl SP_MessageServer();      // 0x0067dcc0
extern "C" void*       __cdecl SP_PlanetModel();        // 0x00b3d350
extern "C" void*       __cdecl SP_PosseSimulatorInstance(); // 0x00d539d0
extern "C" void*       __cdecl FUN_00b3d480(int);       // 0x00b3d480
extern "C" void*       __cdecl FUN_00401090();          // 0x00401090 GetSetting9
extern "C" void*       __cdecl FUN_00d2b6e0(int, int);  // 0x00d2b6e0
extern "C" int         __cdecl FUN_00d38800(int);       // 0x00d38800 cCreatureLevelUpScenario::EvaluateEvent
extern "C" void        __cdecl FUN_00ba5e10(void*, int); // 0x00ba5e10
extern "C" void*       __cdecl FUN_00c0bc00(void*, void*, void*); // 0x00c0bc00
extern "C" void        __cdecl FUN_00f924e0(float);     // 0x00f924e0
extern "C" void        __cdecl FUN_00e39710(int, void*); // 0x00e39710
extern "C" int         __cdecl FUN_0040cf10(void*, unsigned, void*); // GetPropertyT<int>
extern "C" void*       __cdecl FUN_004a9b40(void*, void*); // QuaternionToMatrix
extern "C" void*       __cdecl FUN_00472b80(void*, void*, float); // QuaternionFromMatrix33
extern "C" float       __cdecl FUN_011e08c2(float);     // 0x011e08c2 float helper
extern "C" float       __cdecl FUN_00c0b440(int);       // 0x00c0b440 (float result in st0)
extern "C" float       __cdecl FUN_00d2e350();          // 0x00d2e350
extern "C" float       __cdecl FUN_00d2e380(int);       // 0x00d2e380
extern "C" float       __cdecl FUN_00d2e480(float);     // 0x00d2e480
extern "C" void        __cdecl FUN_00d2e720();          // 0x00d2e720
extern "C" float       __cdecl FUN_00d2e800(int);       // 0x00d2e800
extern "C" int         __cdecl FUN_00d2e830();          // 0x00d2e830

extern "C" void* __cdecl op_new(unsigned, const char*, int, int, const char*, int);
extern "C" void  __cdecl op_delete_array(void*);

// EASTL range helpers used by the vector insert (opaque here).
extern "C" void* __cdecl FUN_00b96900(void* first, void* last, void* dst); // 0x00b96900
extern "C" void  __cdecl FUN_00b93d80(void* first, void* last, void* dst); // 0x00b93d80
extern "C" void  __cdecl FUN_00b97500(void* first, void* last, void* dst); // 0x00b97500
extern "C" void  __cdecl FUN_00d3b920(void* p1, void* p2, void* p3, void* p4, void* p5); // 0x00d3b920
extern "C" void  __cdecl FUN_00d3b970(void* dst, unsigned n, const void* val, void* p4);   // 0x00d3b970

// scenario object (cAvatarDeathScenario): vtable at +0, state at +8, timer float at +0xc,
// effect AutoRef at +0x10 and the scenario tag at +0x14.
struct Scenario {
    void*  mpVtbl;      // +0x00
    int    miUnk4;      // +0x04
    int    miState;     // +0x08
    float  mfTimer;     // +0x0c
    void*  mpEffect;    // +0x10
    int    miTag;       // +0x14

    void __thiscall StartDeathCutScreen(int tag);        // 0x00d38e60
    bool __thiscall EvalTrigger(int event, int* ctx);    // 0x00d400e0
    int  __thiscall EvaluateEvent(float dt);             // 0x00d40230
    int  __thiscall Finish();                            // 0x00d40640
};

// ===========================================================================
// @ 0x00d3f9e0
void NodePool::FreeLists(Node** arr, unsigned count)
{
    for (unsigned i = 0; i < count; ++i) {
        Node* n = arr[i];
        if (n != 0) {
            do {
                Node* cur = n;
                n = n->mpNext;
                NodeBuf* buf = &cur->mBuf;
                buf->Reset(buf->mpData, buf->miCount);
                if (buf->mpData != 0 && *(int*)((char*)buf->mpData - 4) != 0)
                    op_delete_array(buf->mpData);
                if (cur->mpRef != 0)
                    ((TFnV)VT(cur->mpRef, 4))(cur->mpRef);
                if (cur != this->mpSentinel) {
                    if (cur < this->mpPoolBegin || cur >= this->mpPoolEnd)
                        op_delete_array(cur);
                    else {
                        *(Node**)cur = this->mpFreeList;
                        this->mpFreeList = cur;
                    }
                }
            } while (n != 0);
        }
        arr[i] = 0;
    }
}

// ===========================================================================
// @ 0x00d3fa90
void Vec18Vec::InsertN(Vec18* pos, unsigned n, const Vec18* val)
{
    unsigned have = (unsigned)(this->mpEnd - this->mpBegin);
    if (n > have) {
        unsigned size = have;
        unsigned cap = size * 2;
        if (size == 0)
            cap = 1;
        unsigned want = size + n;
        if (want < cap)
            want = cap;
        Vec18* buf = 0;
        if (want != 0)
            buf = (Vec18*)op_new(want * 0x18, "Simulator", 0, 0, (const char*)0x013ebb38, 0xd1);
        Vec18* dst = (Vec18*)FUN_00b96900(this->mpBegin, pos, buf);
        FUN_00b93d80(this->mpBegin, pos, buf);
        FUN_00d3b970(dst, n, val, dst);
        Vec18* tailDst = dst + n;
        Vec18* oldEnd = this->mpEnd;
        void* newEnd = FUN_00b96900(pos, oldEnd, tailDst);
        FUN_00b93d80(pos, oldEnd, tailDst);
        if (this->mpBegin != 0 && *(int*)((char*)this->mpBegin - 4) != 0)
            op_delete_array(this->mpBegin);
        this->mpBegin = buf;
        this->mpEnd = (Vec18*)newEnd;
        this->mpCap = buf + want;
        return;
    }

    if (n == 0)
        return;

    void* raw = pos;
    unsigned off = (unsigned)(pos - this->mpBegin);
    unsigned avail = have - off;
    Vec18 tmp;
    tmp.mWeight = val->mWeight;
    tmp.mVectors.Ctor(&val->mVectors);

    if (n < avail) {
        FUN_00d3b920(&raw, this->mpEnd - n, this->mpEnd, this->mpEnd, 0);
        this->mpEnd += n;
        FUN_00b97500(pos, this->mpEnd - n, this->mpEnd);
        for (Vec18* e = pos; e != pos + n; ++e) {
            e->mWeight = tmp.mWeight;
            e->mVectors.Assign(&tmp.mVectors);
        }
    } else {
        FUN_00d3b970(this->mpEnd, n - avail, &tmp, this->mpEnd);
        this->mpEnd += n - avail;
        FUN_00d3b920(&raw, pos, this->mpEnd - n + avail, this->mpEnd, 0);
        this->mpEnd += avail;
        for (Vec18* e = pos; e != pos + n; ++e) {
            e->mWeight = tmp.mWeight;
            e->mVectors.Assign(&tmp.mVectors);
        }
    }
    if (tmp.mVectors.mBegin != 0 && *(int*)(tmp.mVectors.mBegin - 4) != 0)
        op_delete_array((void*)tmp.mVectors.mBegin);
}

// ===========================================================================
// @ 0x00d3fcf0
// Avatar death sequence: freeze the sim, find the nearest creature, park the camera on the
// corpse, then fire the matching CRG_BrainUpgrade trigger.
void __cdecl FUN_00d3fcf0()
{
    SP_NounManager()->GetCurrentTerrainSphere();
    void* av = SP_NounManager()->GetAvatar();
    FUN_00d2e380(-1);

    int level = ((TFnI)VT(av, 0xd8))(av);
    int mode = FUN_00d2e830();
    ((TFnVI)VT(av, 0xdc))(av, mode);

    void* ms = SP_MessageServer();
    ((TFnVIII)VT(ms, 0x14))(ms, 0x6579712, 0x24947c07, 0);

    void* ps = SP_PosseSimulatorInstance();
    if (ps != 0) {
        unsigned l = (unsigned)((TFnI)VT(av, 0xd8))(av);
        int* slot = (int*)((char*)ps + 0x18);
        if (l > *(unsigned*)slot)
            *slot = (int)l;
    }

    float fa = FUN_00c0b440(mode);
    float fb = FUN_00c0b440(level);
    float fc = FUN_00d2e800(0);
    FUN_00d2e720();
    float fd = FUN_00d2e800(0);
    float scale = (fa / fb) / fc * fd;

    NounVec* vec = SP_NounManager()->GetGameDataVector(0x00cd7d10, 0x00d3d420, 0x00ace0f0,
                                                       0x00b1e500, 0x018eb45e);
    unsigned num = (unsigned)(vec->mpEnd - vec->mpBegin);
    for (unsigned i = 0; i < num; ++i) {
        char* n = (char*)vec->mpBegin[i];
        if (n == 0 || n[0x135] == 0)
            continue;
        if (*(int*)(n + 0xb20) != *(int*)((char*)av + 0xb20))
            continue;
        if (n == (char*)av)
            continue;
        float f = ((TFnF)VT(n + 0x5a8, 0x58))(n + 0x5a8);
        FUN_00f924e0(f);
        char* obj = n + 0xc0;
        float a = ((TFnF)VT(obj, 0x34))(obj);
        ((TFnVI)VT(obj, 0x40))(obj, a * scale);
        ((TC_V)0x00c0bbe0)(n);
    }

    char* body = (char*)av + 0x5a8;
    float f0 = ((TFnF)VT(body, 0x58))(body);
    FUN_00f924e0(f0);
    ((TC_VF)0x00c0b9d0)(av, *(float*)0x01687a00);

    ((TC_VIFIIII)0x00c03190)(av, 0x1000, *(float*)0x0147aaa8, level, 0, 0, 0);

    char* obj = (char*)av + 0xc0;
    float f1 = ((TFnFI)VT(av, 0x80))(av, 0);
    ((TFnVI)VT(obj, 0x40))(obj, f1);
    ((TC_V)0x00c0bbe0)(av);

    if (mode != 0) {
        void** it = *(void***)(mode + 0xbc);
        void** end = *(void***)(mode + 0xc0);
        for (; it != end; ++it)
            ((TFnVI)VT(*it, 0x18))(*it, 0x49b56d7);
        if (*(int*)(mode + 0x68) != 0) {
            FUN_00d2b6e0(0x6455b55, 0);
            FUN_00d2b6e0(0x652a628, 0);
        }
    }

    FUN_00ba5e10(av, 7);

    struct { int a, b, c; } m1 = { 0, 0, 0 };
    struct { int a, b, c; } m2 = { 0, 0, 0 };
    void* res = 0;
    void* msg = FUN_00c0bc00(&res, &m1, &m2);
    FUN_00e39710(0xf00048a9, msg);

    const char* trigger = 0;
    switch (level) {
    case 1: trigger = (const char*)0x0147ab14; break;   // "CRG_BrainUpgrade1"
    case 2: trigger = (const char*)0x0147ab00; break;   // "CRG_BrainUpgrade2"
    case 3: trigger = (const char*)0x0147aaec; break;   // "CRG_BrainUpgrade3"
    case 4: trigger = (const char*)0x0147aad8; break;   // "CRG_BrainUpgrade4"
    }
    ((TC_VIPIIII)0x00ae0930)(SP_GetTriggerMgr(), trigger, 1, 1, 0, 0, 0);
}

// ===========================================================================
// @ 0x00d400e0
bool Scenario::EvalTrigger(int event, int* ctx)
{
    bool isAvatar = false;
    if (ctx[0] != 0) {
        void* av = SP_NounManager()->GetAvatar();
        isAvatar = (ctx[0] == (int)(size_t)av);
    }

    int value;
    if (event == 0x053f0369) {
        value = 2;
        void* av = SP_NounManager()->GetAvatar();
        if (av != 0) {
            int level = ((TFnI)VT(av, 0xd8))(av);
            bool atMax = (level == 4);
            value = 1;
            if (!atMax)
                value = 2;
        }
    } else if (event == 0x055a7128) {
        void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
        void* av = SP_NounManager()->GetAvatar();
        if (av == 0 || sphere == 0)
            return false;
        int level = ((TFnI)VT(av, 0xd8))(av);
        if (level <= 0)
            return false;
        int r = FUN_00d38800(level);
        if (((TC_II)0x00ad7db0)(SP_GetTriggerMgr(), r) != ctx[2])
            return false;
        if (level != 4)
            return false;
        value = 1;
        isAvatar = true;
    } else if (event == 0x533535dd) {
        if (*(char*)(0x0169e294 + 0xde) == 0) {
            value = 2;
        } else {
            FUN_00d3fcf0();
            void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
            ((TC_VII)0x00c79f00)(sphere, 0x03a8d77c, 3);
            return true;
        }
    } else {
        return false;
    }

    void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
    if (sphere != 0 && isAvatar)
        ((TC_VII)0x00c79f00)(sphere, 0x03a8d77c, value);
    return true;
}

// ===========================================================================
// @ 0x00d40230
int Scenario::EvaluateEvent(float dt)
{
    void* av = SP_NounManager()->GetAvatar();
    if (av == 0) {
        ((TFnV)VT(this, 0x14))(this);
        return 0;
    }

    if (this->miState == 1) {
        if ((*(unsigned*)((char*)av + 0x110) & 0x100) == 0 &&
            *(int*)(*(int*)((char*)av + 0xb4c) + 0x1d8) != 0x03845d9d) {
            this->StartDeathCutScreen(this->miTag);

            SP_NounManager()->GetAvatar();
            float prop = 1.0f;
            FUN_0040cf10(*(void**)(0x0169e294 + 0xb4), 0x57ae947d, &prop);
            float t = FUN_00d2e350() * prop;
            FUN_00d2e480(t);

            void* sphere = SP_NounManager()->GetCurrentTerrainSphere();
            float one = *(float*)0x01485720;               // 1.0f
            FUN_0040cf10(*(void**)(0x0169e294 + 0xb4), 0x98c83c48, &one);
            float cur = *(float*)((char*)sphere + 0x10f0);
            float d = FUN_011e08c2(one);
            *(float*)((char*)sphere + 0x10f0) = cur - d;
        }
    } else if (this->miState == 2) {
        TriggerMgr* tm = SP_GetTriggerMgr();
        if (tm->miState == 2)
            this->miState = 3;
    } else if (this->miState == 3) {
        TriggerMgr* tm = SP_GetTriggerMgr();
        if (tm->miState != 1 && tm->miState != 2)
            ((TFnV)VT(this, 0x14))(this);
    }

    int st = ((TFnI)VT(av, 0xa4))(av);
    if ((unsigned)(st - 4) <= 1) {
        float old = this->mfTimer;
        this->mfTimer = old - dt;
        if (old - dt < 0.0f) {
            this->mfTimer = *(float*)0x01486110;           // 5.0f

            V3* from = (V3*)((TFnPU)VT((char*)av + 0xc0, 0x2c))((char*)av + 0xc0);
            float best = *(float*)0x0147aaa8;              // FLT_MAX
            float bestObj = 0.0f;
            void* setting = FUN_00401090();
            ((TC_V)0x004df420)(setting);
            NounVec* vec = (NounVec*)((TC_P)0x00bc0710)(SP_NounManager());
            void** it = vec->mpBegin;
            void** end = vec->mpEnd;
            if (it != end) {
                do {
                    char* n = (char*)*it;
                    if (n[0xa9] != 0) {
                        V3* p = (V3*)((TFnPU)VT(n + 0x34, 0x2c))(n + 0x34);
                        float dx = from->x - p->x;
                        float dy = from->y - p->y;
                        float dz = from->z - p->z;
                        float d2 = (dz * dz + dy * dy) + dx * dx;
                        if (d2 < best && ((TC_I)0x00c6aa50)(n) != 0) {
                            best = d2;
                            bestObj = (float)(size_t)n;
                        }
                    }
                    ++it;
                } while (it != end);

                if (bestObj != 0.0f) {
                    char* target = (char*)(size_t)bestObj;
                    TransformMsg msg;
                    ((TC_V)0x00434040)(&msg);

                    V3* tpos = (V3*)((TFnPU)VT(target + 0x34, 0x2c))(target + 0x34);
                    ((TC_VPP)0x00d3b0c0)((void*)0x0169e294, &msg.mTranslation, tpos);

                    msg.mFlags0 |= 4;
                    msg.mCount0 += 1;

                    void* rot = ((TFnPU)VT(target + 0x34, 0x30))(target + 0x34);
                    void* m = ((TC_PP)0x0059c190)(&msg.mRotation, rot);
                    for (int k = 0; k < 9; ++k)
                        msg.mRotation.m[k] = ((float*)m)[k];

                    msg.mFlags1 |= 2;
                    msg.mCount1 += 1;

                    if (this->mpEffect != 0) {
                        ((TFnVP)VT(this->mpEffect, 0x18))(this->mpEffect, &msg);
                        return 1;
                    }

                    int flag = *(int*)(*(int*)((char*)av + 0xb20) + 0x618);
                    void* fx = SP_EffectsManager();
                    if (this->mpEffect != 0) {
                        void* oldFx = this->mpEffect;
                        this->mpEffect = 0;
                        ((TFnV)VT(oldFx, 4))(oldFx);
                    }
                    int effectId = (-(int)(flag == 0) & 0x8c9af24f) + 0xbed2ad51;
                    int ok = ((TFnIIP)VT(fx, 0x2c))(fx, effectId, 0, &this->mpEffect);
                    if (ok != 0) {
                        ((TFnVIP)VT(this->mpEffect, 0x44))(this->mpEffect, 5,
                                                           (char*)av + 0xb20 + 0x4ec, 3);
                        ((TFnVP)VT(this->mpEffect, 0x18))(this->mpEffect, &msg);
                        ((TFnVI)VT(this->mpEffect, 8))(this->mpEffect, 0);
                        return 1;
                    }
                }
            }
        }
    } else if (this->mpEffect != 0) {
        void* oldFx = this->mpEffect;
        ((TFnVI)VT(oldFx, 0xc))(oldFx, 1);
        if (this->mpEffect != 0) {
            this->mpEffect = 0;
            ((TFnV)VT(oldFx, 4))(oldFx);
        }
    }
    return 1;
}

// ===========================================================================
// @ 0x00d40640
int Scenario::Finish()
{
    if (this->mpEffect != 0) {
        void* oldFx = this->mpEffect;
        ((TFnVI)VT(oldFx, 0xc))(oldFx, 1);
        if (this->mpEffect != 0) {
            this->mpEffect = 0;
            ((TFnV)VT(oldFx, 4))(oldFx);
        }
    }

    if (this->miState == 3) {
        void* editor = ((TC_P)0x00ac84d0)(FUN_00b3d480(1));
        void* planet = SP_PlanetModel();
        NounVec* vec = SP_NounManager()->GetGameDataVector(0x00cd7d10, 0x00d3d420, 0x00accc30,
                                                           0x00b1e500, 0x01be418e);
        void** it = vec->mpBegin;
        void** end = vec->mpEnd;
        while (it != end) {
            char* n = (char*)*it;
            if (((TC_I)0x00c6a020)(n) != 0 && *(int*)(n + 0x15c) != 9) {
                TransformMsg msg;
                msg.mFlags0 = 0;
                msg.mCount0 = 0;
                msg.mTranslation.x = *(float*)0x0169e298;
                msg.mTranslation.y = *(float*)0x0169e29c;
                msg.mTranslation.z = *(float*)0x0169e2a0;
                msg.mFlags1 = 0;
                msg.mCount1 = 0;
                ((TC_VP)0x0041cb40)(&msg.mRotation, (void*)0x0169e3c0);

                cSPTransform xf;
                xf.mT.mFlags0 = 0;
                xf.mT.mCount0 = 0;
                xf.mT.mTranslation.x = *(float*)0x0169e298;
                xf.mT.mTranslation.y = *(float*)0x0169e29c;
                xf.mT.mTranslation.z = *(float*)0x0169e2a0;
                xf.mT.mFlags1 = 0;
                xf.mT.mCount1 = 0;
                xf.mT.mRotation = msg.mRotation;
                xf.mScale = *(float*)0x01485720;           // 1.0f

                V3* pos = (V3*)((TC_P)0x00c6acc0)(n);
                msg.mTranslation = *pos;
                msg.mFlags0 |= 4;
                msg.mCount0 += 1;

                void* ori = ((TC_PPP)0x00b7f190)(planet, &xf.mT.mRotation, ((TC_P)0x00c6acc0)(n));
                void* q = FUN_004a9b40(&xf.mT.mRotation, ori);
                msg.mFlags1 |= 2;
                msg.mCount1 += 1;
                xf.Assign(&msg);

                int num = (int)((*(char**)(n + 0x44) - *(char**)(n + 0x40)) / 4);
                for (int i = 0; i < num; ++i) {
                    char* sub = *(char**)(*(char**)(n + 0x40) + i * 4);
                    ((TFnVI)VT(sub + 0x5a8, 0x2c))(sub + 0x5a8, 1);
                    if (((TFnI)VT(sub, 0xd0))(sub) != 0)
                        continue;
                    ((TFnVPPP)VT(editor, 0x10))(editor, &msg, &xf, &msg);
                    void* qq = FUN_00472b80(&xf.mT.mRotation, &xf.mT.mTranslation, 0.0f);
                    M33 m;
                    for (int k = 0; k < 9; ++k)
                        m.m[k] = ((float*)qq)[k];
                    ((TFnVP)VT(sub + 0xc0, 0x44))(sub + 0xc0, &m);
                }
            }
            ++it;
        }
    }

    this->miState = 0;
    this->mfTimer = 0.0f;
    return 1;
}
