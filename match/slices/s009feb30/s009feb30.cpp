// Slice s009feb30 -- nSPCreatureAnim::queued_blender animation-queue helpers plus the
// SPSkinPaint ArgScript command registration and small packed-handle utilities.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- masked externs
extern "C" void* __cdecl operator_new(unsigned int size, const char* name,
                                      int a, int b, int c, int d);   // 0x00f473a0
extern "C" void  __cdecl operator_delete__(void* p);                 // 0x00f47380
extern "C" void  __cdecl FUN_009a1ad0(void* p);                      // 0x009a1ad0


struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {} };
struct CreatureStatic { char pad[0x3f5]; char field_3f5; };
struct CreatureSub {
    int field_00;
    void FUN_009e3f70(int a, int b);                              // 0x009e3f70
    void FUN_009e4600(Vec3 v, int a, int b, int c, int d);        // 0x009e4600
};
struct CreatureInst {
    CreatureStatic* mStatic;       // +0x00
    char   pad_04[0x6c];
    float  mScale;                 // +0x70
    char   pad_74[0x1ec];
    char   field_260;              // +0x260
    char   pad_261[3];
    float  field_264;
    float  field_268;
    float  field_26c;
    char   pad_270[0x88];
    CreatureSub mSub;              // +0x2f8
    char   pad_2f8[0x1680 - 0x2f8 - 4 - 0];
    char   field_1680;
    char   pad_1681[0xb];
    char   field_168c;
    void FUN_009b8760(float dt);                                  // 0x009b8760
    void FUN_009b7b10(int a, int b);                              // 0x009b7b10
    void FUN_009b8720(float a);                                   // 0x009b8720
    void FUN_009b8d50(float dt);                                  // 0x009b8d50
    void FUN_009b8e40(float a);                                   // 0x009b8e40
    void FUN_009ba040(float dt, float a);                         // 0x009ba040
    void FUN_009c0680();                                          // 0x009c0680
    void FUN_009b8f40(float a);                                   // 0x009b8f40
    void UpdateWiggles(float dt, float a);                        // 0x009bb4f0
};
void __cdecl FUN_009bc580(CreatureInst* inst, float dt);        // 0x009bc580
void __cdecl FUN_0099d460(float a, CreatureInst* inst, int g, float b); // 0x0099d460
void __cdecl FUN_c2e4e0(CreatureInst* inst);                    // 0x00c2e4e0

extern bool  g_registered;          // 0x0166cbd0
extern void* g_resourceList[2];     // 0x0166c070
extern float g_maxAnimTime;         // 0x01550b84
extern void* g_timer;               // 0x015509f0

// ---------------------------------------------------------------- structs
struct AnimGoal {
    int      field_00;       // +0x00
    int      field_04;       // +0x04
    int      mChildren[24];  // +0x08  (8 slots * 3 dwords, stride 0x0c)
    int      mChildCount;    // +0x68
    int      field_6c;       // +0x6c  packed handle of the active child
    float    field_70;       // +0x70
    float    field_74;       // +0x74
    float    field_78;       // +0x78
    uint8_t  field_7c;       // +0x7c
    char     pad_7d[3];
    int      field_80;       // +0x80
    uint8_t  field_84;       // +0x84
    char     pad_85[3];
    float    field_88;       // +0x88
    float    field_8c;       // +0x8c
    char     pad_90[4];
    float    field_94;       // +0x94
    char     pad_98[8];
    float    field_a0;       // +0xa0
    char     pad_a4[4];
    double   field_a8;       // +0xa8
    char     pad_b0[4];
    uint32_t field_b4;       // +0xb4
    char     pad_b8[4];
    int      field_bc;       // +0xbc
    int      field_c0;       // +0xc0
    float    field_c4;       // +0xc4
    char     pad_c8[4];
    float    field_cc;       // +0xcc
    float    field_d0;       // +0xd0
    uint8_t  field_d4;       // +0xd4
    char     pad_d5[3];
    int      field_d8;       // +0xd8
    char     pad_dc[0xf0 - 0xdc];

    void Init();
    void CopyFiltersFrom(AnimGoal* o);
    int  IsActive();
};

struct QueuedBlender {
    char     pad_00[8];
    AnimGoal mGoals[16];     // +0x08, stride 0xf0
    char     pad_f08[4];
    uint32_t mActive[16];    // +0xf0c
    uint32_t mQueue[16];     // +0xf4c
    uint32_t field_f8c;      // +0xf8c
    char     pad_f90[0xc];
    int      field_f9c;      // +0xf9c  queue write cursor
    int      field_fa0;      // +0xfa0  queue read cursor
    uint32_t mCurrent;       // +0xfa4
    uint32_t mPending;       // +0xfa8
    uint8_t  field_fac;      // +0xfac
    char     pad_fad[3];
    float    field_fb0;      // +0xfb0
    float    field_fb4;      // +0xfb4
    char     pad_fb8[4];
    CreatureInst* field_fbc;  // +0xfbc

    int      Count();
    int      FindFreeSlot();            // FUN_009ff380
    void     TransitionToNextAnimation();  // FUN_009ff440
    void     UpdateGoals(float dt, char param_3);
    int      QueuedToActive();
};

// ---------------------------------------------------------------- small utilities

// @ 0x009FEF70
int __cdecl packHandle(int base, uint8_t index) {
    return (base << 8) + 1 + (int)index;
}

// @ 0x009FEF90
int __cdecl packGoalHandle(QueuedBlender* blender, AnimGoal* goal) {
    int result;
    if (goal != 0) {
        int idx = (int)((char*)goal - (char*)blender - 8) / 0xf0;
        result = (uint8_t)idx + 1 + (int)goal->field_b4 * 0x100;
    } else {
        result = 0;
    }
    return result;
}

// @ 0x009FEFD0
int QueuedBlender::Count() {
    uint32_t read = (uint32_t)field_fa0;
    int result = 0;
    if (read != 0xffffffff) {
        uint32_t write = (uint32_t)field_f9c;
        if (read <= write)
            result = (int)(write - read) + 1;
        else
            result = (int)(write + read) + 0x11;
    }
    return result;
}

// @ 0x009FEF20
void AnimGoal::CopyFiltersFrom(AnimGoal* o) {
    field_88 = o->field_88;
    field_78 = o->field_78;
    field_c4 = o->field_c4;
}

// @ 0x009FEE90
void AnimGoal::Init() {
    field_a8 = 0.0;
    field_70 = 0.0f;
    field_74 = -0.2f;
    field_d4 = 0;
    field_8c = 1.0f;
    field_a0 = 1.0f;
    field_78 = 0.2f;
    field_cc = -1.0f;
    field_d0 = 1.0f;
    field_bc = 0;
    field_d8 = 0;
    field_7c = 0;
    field_88 = 0.2f;
    field_80 = 1;
    field_84 = 0;
}

// @ 0x009FF020
int AnimGoal::IsActive() {
    if (field_00 == 0 && ((uint32_t)mChildCount >= 8 || mChildren[mChildCount * 3] == 0))
        return 0;
    return 1;
}

// @ 0x009FF6F0
AnimGoal* __cdecl FindGoalByHandle(QueuedBlender* blender, uint32_t handle) {
    if (handle != 0) {
        AnimGoal* g = (AnimGoal*)((char*)blender + (handle & 0xff) * 0xf0 - 0xe8);
        if (g->field_b4 == (handle >> 8)) {
            if (g->field_00 != 0)
                return g;
            uint32_t h2 = (uint32_t)g->field_6c;
            if (h2 != 0) {
                g = (AnimGoal*)((char*)blender + (h2 & 0xff) * 0xf0 - 0xe8);
                if (g->field_b4 == (h2 >> 8) && g->field_00 != 0)
                    return g;
            }
        }
    }
    return 0;
}

// @ 0x009FF7A0
int __cdecl FindGoalValue(QueuedBlender* blender, uint32_t handle) {
    AnimGoal* g = FindGoalByHandle(blender, handle);
    return g ? g->field_00 : 0;
}

// @ 0x009FF750
AnimGoal* __cdecl GetCurrentGoal(QueuedBlender* b) {
    uint32_t a = b->mCurrent;
    if (a < 0x10) {
        uint32_t idx = b->mActive[a];
        if (idx < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)b + idx * 0xf0 + 8);
            if (g->field_00 != 0)
                return g;
            uint32_t c = (uint32_t)g->mChildCount;
            if (c < 8 && g->mChildren[c * 3] != 0)
                return g;
        }
    }
    return 0;
}

// @ 0x009FF7C0
bool __cdecl FindGoalByID(QueuedBlender* b, int goalId, int* outHandle) {
    int i;
    for (i = 0; i < 16; ++i) {
        uint32_t v = b->mQueue[i];
        if (v < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)b + v * 0xf0 + 8);
            if (g->field_00 != 0 && g->field_d8 == goalId) {
                if (outHandle)
                    *outHandle = (uint8_t)b->mQueue[i] + 1 + (int)g->field_b4 * 0x100;
                return true;
            }
        }
    }
    for (i = 0; i < 16; ++i) {
        uint32_t v = b->mActive[i];
        if (v < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)b + v * 0xf0 + 8);
            if (g->field_00 != 0 && g->field_d8 == goalId) {
                if (outHandle)
                    *outHandle = (uint8_t)b->mActive[i] + 1 + (int)g->field_b4 * 0x100;
                return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------- queue management

// @ 0x009FF380
int QueuedBlender::FindFreeSlot() {
    int result = (int)mCurrent;
    if (mPending == 0xffffffff)
        return result;
    for (int k = 0; k < 16; ++k) {
        if (mActive[k] == mPending)
            mActive[k] = 0xffffffff;
    }
    uint32_t* p = mActive;
    int i;
    for (i = 0; i < 16; ++i, ++p) {
        uint32_t v = *p;
        if (v > 0x10)
            goto found;
        AnimGoal* a = (AnimGoal*)((char*)this + v * 0xf0 + 8);
        if (a->field_00 == 0 && ((uint32_t)a->mChildCount >= 8 || a->mChildren[a->mChildCount * 3] == 0))
            goto found;
    }
    return result;
found:
    AnimGoal* g = (AnimGoal*)((char*)this + mPending * 0xf0 + 8);
    if (g->field_00 != 0)
        FUN_009a1ad0((void*)g->field_00);
    g->field_c4 = 0.0f;
    g->field_c0 = 0;
    mActive[i] = mPending;
    return i;
}

// @ 0x009FF440
void QueuedBlender::TransitionToNextAnimation() {
    uint32_t old = (mCurrent < 0x10) ? mActive[mCurrent] : 0xffffffff;
    if (mCurrent >= 0x10)
        return;
    int next;
    if (field_fa0 != -1)
        next = QueuedToActive();
    else
        next = FindFreeSlot();
    mCurrent = (uint32_t)next;
    uint32_t cur = mActive[next];
    if (old == cur && cur < 0x10) {
        AnimGoal* g = (AnimGoal*)((char*)this + cur * 0xf0 + 8);
        if (g->field_c0 == 0)
            mCurrent = 0xffffffff;
    }
}

// @ 0x009FF4B0
void QueuedBlender::UpdateGoals(float dt, char param_3) {
    FUN_009bc580(field_fbc, dt);
    if (param_3 == 0)
        field_fbc->FUN_009b8760(dt);

    for (int i = 0; i < 16; ++i) {
        uint32_t v = mActive[i];
        if (v < 0x10) {
            AnimGoal* g = (AnimGoal*)((char*)this + v * 0xf0 + 8);
            if (g->field_c0 != 0 && field_fac != 0 && param_3 == 0)
                FUN_0099d460(g->field_94, field_fbc, g->field_00, field_fb0);
        }
    }

    if (param_3 == 0) {
        if (field_fbc->field_260 != 0 && 1e-06f < field_fb4) {
            if (field_fbc->mSub.field_00 == 0) {
                field_fbc->mSub.FUN_009e3f70(6, 4);
                field_fbc->FUN_009b7b10(0, 0);
            }
            CreatureInst* c = field_fbc;
            float inv = 1.0f / c->mScale;
            field_fbc->mSub.FUN_009e4600(Vec3(c->field_264 * inv, c->field_268 * inv, c->field_26c), 0, 0, 0, 0);
            field_fbc->FUN_009b8720(field_fb4);
            field_fbc->FUN_009b8d50(dt);
            field_fbc->FUN_009b8e40(field_fb4);
            if (field_fac != 0 && field_fbc->field_1680 != 0)
                field_fbc->FUN_009ba040(dt, field_fb4);
            if (g_timer != 0 && field_fbc->mStatic->field_3f5 == 0 && field_fbc->field_168c != 0)
                field_fbc->FUN_009c0680();
            field_fbc->FUN_009b8f40(field_fb4);
        }
        if (field_fac != 0)
            field_fbc->UpdateWiggles(dt, field_fb4);
    }
    FUN_c2e4e0(field_fbc);
}

static inline const float& clampMax(const float& a, const float& b) { return a < b ? b : a; }
static inline const float& clampMin(const float& a, const float& b) { return a < b ? a : b; }

// @ 0x009FF880
void __cdecl UpdateGoalWeight(int src, AnimGoal* g) {
    int state = g->field_c0;
    if (state == 0)
        return;
    if (state == 1) {
        float t = (g->field_88 > 1e-05f) ? g->field_c4 / g->field_88 : 0.0f;
        float lo = 0.0f, hi = 1.0f;
        const float& c = clampMin(clampMax(lo, t), hi);
        if (c < 0.99999f)
            g->field_78 = *(float*)(src + 0x88) / (1.0f - c);
        else
            g->field_78 = 0.0f;
    } else if (state == 3) {
        float t = (g->field_78 > 1e-05f) ? g->field_c4 / g->field_78 : 0.0f;
        float hi = 1.0f, lo = 0.0f;
        const float& c = clampMin(clampMax(lo, t), hi);
        if (c > 1e-05f)
            g->field_78 = *(float*)(src + 0x88) / c;
        else
            g->field_78 = 0.0f;
    } else {
        g->field_78 = *(float*)(src + 0x88);
    }
    g->field_c4 = *(float*)(src + 0x88);
    if (g->field_78 != 0.0f)
        g->field_c0 = 3;
    else
        g->field_c0 = 0;
}

// Ring-buffer index wrap that stays non-negative for negative inputs.
static inline int WrapIndex(int x) {
    if (x >= 0)
        return x % 16;
    int r = -x % 16;
    if (r != 0)
        r = 16 - r;
    return r;
}

// @ 0x009FF040
int QueuedBlender::QueuedToActive() {
    int result = -1;
    int i = 0;
    uint32_t* slot = mActive;
    for (; i < 16; ++i, ++slot) {
        if (result != -1)
            return result;
        uint32_t v = *slot;
        if (v <= 0x10) {
            AnimGoal* a = (AnimGoal*)((char*)this + v * 0xf0 + 8);
            if (a->field_00 != 0 || ((uint32_t)a->mChildCount < 8 && a->mChildren[a->mChildCount * 3] != 0))
                continue;
        }
        for (int j = 0; j < 16; ++j) {
            if (result != -1)
                break;
            if (field_fa0 == -1)
                break;
            uint32_t idx = mQueue[field_fa0];
            AnimGoal* g = (AnimGoal*)((char*)this + idx * 0xf0 + 8);
            if (g->field_00 != 0 ||
                ((uint32_t)g->mChildCount < 8 && g->mChildren[g->mChildCount * 3] != 0)) {
                *slot = idx;
                mQueue[field_fa0] = 0xffffffff;
                result = i;
            }
            if (field_fa0 == field_f9c) {
                field_fa0 = -1;
                field_f9c = -1;
            } else {
                field_fa0 = WrapIndex(field_fa0 + 1);
            }
        }
    }
    if (result == -1)
        result = (int)mCurrent;
    return result;
}

// ---------------------------------------------------------------- SPSkinPaint ArgScript registration

// Stub types for the ArgScript parser / resource manager vcalls (slot indexes from the vtable offsets).
struct ResKey3 { int instance; int type; int group; };

struct CmdBase {                                  // EA::ArgScript::cCommandBase, 0x10 bytes
    CmdBase();                                    // 0x0083c800
    virtual void Execute();
    char pad[12];
};
struct CmdProps : CmdBase { CmdProps(); char more[0x24]; };   // AppProps-style ctor, 0x34 bytes (0x0083cdd0)
struct PriCmd : CmdBase { virtual void Execute(); };          // vtbl 0x01448770
struct CapCmd : CmdBase { virtual void Execute(); };          // vtbl 0x01448788
struct AggCmd : CmdBase { virtual void Execute(); };          // vtbl 0x014487a0
struct RmpCmd : CmdBase { virtual void Execute(); };          // vtbl 0x014487b8
struct DefSpcBlkCmd : CmdProps { virtual void Execute(); };   // vtbl 0x014487d0

struct ParseOpts {                                // eastl::string-like source name + parser state
    int   id;                                     // 0x01ff0ee3
    int   a, b;
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   pad;
    float duration;                               // written by the parser
};

struct Stream {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void Seek(int a, int b);              // slot 10 (+0x28)
};
struct Record {                                   // object returned by the manager's lookup
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5();
    virtual Stream* GetStream();                  // slot 6 (+0x18)
    virtual void v7(); virtual void v8();
    virtual void Close();                         // slot 9 (+0x24)
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual char Open(ResKey3* key, Record** out, int a, int b, int c, int d);   // slot 13 (+0x34)
};
struct Parser {
    virtual void AddRef();                        // 0x00
    virtual void v1();                            // 0x04
    virtual void Reset();                         // 0x08
    virtual void v3();                            // 0x0c
    virtual void SetOptions(ParseOpts* o);        // 0x10
    virtual void AddCommand(const char* name, CmdBase* cmd);   // 0x14
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void SetMode(int a, int b);           // 0x28
    virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual void ParseStream(Stream* s);          // 0x4c
};
struct ResMan {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual int  GetKeys(ResKey3** outVec, void* filter, int flags);   // slot 14 (+0x38)
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21();
    virtual Record* Lookup(ResKey3* key);         // slot 22 (+0x58)
};
struct KeyFilter {                                // local filter object with a vtable and a type id
    virtual void Dummy();
    int   typeID;
    ResKey3* mpBegin;                             // result vector (begin,end,cap)
    ResKey3* mpEnd;
    ResKey3* mpCap;
};

extern "C" ResMan* __cdecl GetManager();                                  // 0x0067dcd0
extern "C" Parser* __cdecl CreateParser();                                // 0x008408d0
extern "C" int __cdecl ReadInt32(Stream* s, int* dst, int count, int bigEndian);  // 0x0093a780
extern "C" void __cdecl FUN_009fe6c0(Stream* s);                          // 0x009fe6c0
extern "C" void __cdecl FUN_009fe010(void* begin, void* end, void* cb);   // 0x009fe010
extern "C" void __cdecl FUN_009fc080();                                   // 0x009fc080 (callback)
extern const char* g_cmdPriName;   // 0x01551780
extern const char* g_cmdCapName;   // 0x01551770
extern const char* g_cmdAggName;   // 0x0155176c
extern const char* g_cmdRmpName;   // 0x01551784
extern const char* g_cmdDefName;   // 0x01551778
struct ResList { ResKey3* begin; ResKey3* end; };
extern ResList* g_resList;         // 0x0166c070

// @ 0x009FEB30
bool __cdecl RegisterSPSkinPaintCommands(void) {
    if (g_resList->begin != g_resList->end)
        return true;

    KeyFilter filter;
    filter.typeID = 0x7c19aa7a;
    filter.mpBegin = 0;
    filter.mpEnd = 0;
    filter.mpCap = 0;
    bool found = GetManager()->GetKeys(&filter.mpBegin, &filter, 0) > 0;
    if (found) {
        ParseOpts opts;
        opts.id = 0x1ff0ee3;
        opts.a = 0;
        opts.b = 0;
        opts.mpBegin = (char*)0x1667bac;
        opts.mpEnd = (char*)0x1667bac;
        opts.mpCapacity = (char*)0x1667bad;
        Parser* parser = CreateParser();
        if (parser)
            parser->AddRef();
        parser->Reset();
        parser->SetOptions(&opts);
        parser->SetMode(2, 4);

        parser->AddCommand(g_cmdPriName, new PriCmd);
        parser->AddCommand(g_cmdCapName, new CapCmd);
        parser->AddCommand(g_cmdAggName, new AggCmd);
        parser->AddCommand(g_cmdRmpName, new RmpCmd);
        parser->AddCommand(g_cmdDefName, new DefSpcBlkCmd);

        for (ResKey3* key = filter.mpBegin; key != filter.mpEnd; ++key) {
            Record* rec = GetManager()->Lookup(key);
            Record* opened = 0;
            if (rec) {
                if (rec->Open(key, &opened, 1, 6, 1, 0)) {
                    Stream* stream = opened->GetStream();
                    int tag;
                    ReadInt32(stream, &tag, 1, 0);
                    if (tag == 0x70637470) {
                        FUN_009fe6c0(stream);
                    } else {
                        stream->Seek(0, 0);
                        opts.duration = 0.0f;
                        parser->ParseStream(stream);
                        if (opts.duration > g_maxAnimTime)
                            g_maxAnimTime = opts.duration;
                    }
                    opened->Close();
                }
                if (opened)
                    ((CmdBase*)opened)->Execute();   // intrusive Release of the opened record
            }
        }
        FUN_009fe010(g_resList->begin, g_resList->end, (void*)FUN_009fc080);
        g_registered = true;
        parser->v3();
        parser->v1();
        if (opts.mpCapacity - opts.mpBegin > 1 && opts.mpBegin)
            operator_delete__(opts.mpBegin);
    }
    return found;
}
