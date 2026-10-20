// Slice s00a04d20 (gold3 batch) — SP::cAnimatingCreature animation helpers
// plus the rigid-body closest-shape query (00a04d20), the anim-world region
// bookkeeping, the goal fade updater and the anim-property accessors.
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Layouts are read straight off the disassembly (retail offsets).  Names are
// the dev-PDB ones where the card carried a real symbol, otherwise coined here.
#include "types.h"
#include <math.h>

typedef unsigned int uint;

double __cdecl FUN_011e08f0(double v);   // 0x011e08f0 (x87 pow helper, cdecl)

// --------------------------------------------------------------------------- math value types
struct Vector3 {
    float x, y, z;
};
struct Vector4 {
    float x, y, z, w;
};

// One 700-byte (0x2bc) rigid-body shape record; the local offset of the shape
// lives at +0x10..+0x18 and the pre-rotated block starts at +0x18.
struct BodyShapeEntry {
    uint32_t f00;
    uint32_t f04;
    uint32_t f08;
    uint32_t f0c;
    float    off[3];        // +0x10 local offset of this sub-shape
    float    pad1c[0x2bc - 0x1c];
};

// The object this slice reads and writes at (this+0x17c).  It owns the shape
// vector at +0x2e4..+0x2e8 and carries position (+0x18) and quaternion (+0x3c).
struct RigidBody {
    uint8_t  pad00[0x18];
    float    pos[3];        // +0x18 world position
    uint8_t  pad24[0x3c - 0x24];
    float    quat[4];       // +0x3c w,x,y,z
    uint8_t  pad4c[0x2e0 - 0x4c];
    uint8_t  dirtyFlag;     // +0x2e0
    uint8_t  pad2e1[0x2e4 - 0x2e1];
    BodyShapeEntry* begin;  // +0x2e4
    BodyShapeEntry* end;    // +0x2e8
};

// --------------------------------------------------------------------------- forward decls
struct AnimGoalInfo;
struct queued_blender;
struct AnimWorld;

// nSPCreatureAnim::creature_static_data — refcounted; only the counters matter.
struct CreatureStaticData {
    long AddRef() const;    // 0x009b3450
    long Release() const;   // 0x009c26a0
};

// A refcounted slot: 0x00a056f0 swaps the pointer it holds.
struct StaticDataSlot {
    CreatureStaticData* p;              // +0x00
    void** SwapStaticData(CreatureStaticData** src);   // 0x00a056f0
};

// Queue entry returned by 0x9ff750/0x9ff6f0; only the fields this slice uses.
struct AnimGoalInfo {
    AnimGoalInfo* p0;       // +0x00 (a goal pointer whose target we touch)
    uint8_t  pad04[0x10 - 0x04];
    float    local10;       // +0x10
    float    local14;       // +0x14
    float    local18;       // +0x18
    uint8_t  pad1c[0x6c - 0x1c];
    uint32_t flag6c;        // +0x6c (00a051c0 tests this)
    uint8_t  pad70[0xa8 - 0x70];
    double   timeA8;        // +0xa8
    uint32_t fB0;           // +0xb0
    double   vB8;           // +0xb8 (double)
    uint32_t zeroC0;        // +0xc0
    uint8_t  padC4[0xd8 - 0xc4];
    uint32_t fD8;           // +0xd8
};

// Viewer object referenced at (this+0x190): +0x20 holds the last region.
struct AnimViewer {
    void**   vtbl;          // +0x00
    uint8_t  pad04[0x20 - 0x04];
    uint32_t region;        // +0x20
};

// --------------------------------------------------------------------------- cAnimatingCreature
struct cAnimatingCreature {
    void**   vtbl;              // +0x000
    uint8_t  pad004[0x178 - 0x04];
    uint32_t mWorldRegion;      // +0x178
    RigidBody* mRegionObj;      // +0x17c (body / object; +0x2e0 flag)
    uint8_t  pad180[0x184 - 0x180];
    queued_blender* mBlender;   // +0x184
    uint32_t mCurGoal;          // +0x188
    uint32_t mPrevGoal;         // +0x18c
    AnimViewer* mViewer;        // +0x190
    uint8_t  pad194[0x198 - 0x194];
    int32_t  mRefCount;         // +0x198
    uint8_t  pad19c[0x1d8 - 0x19c];
    uint8_t  mFlag1d8;          // +0x1d8

    bool  ClosestBodyPosition(const Vector3& query, Vector3& out); // 0x00a04d20
    void  GetCurrentAnimation(uint32_t* outIdx, float* outTime, int* outValue, int* outFlags); // 0x00a05150
    bool  GetGoalTimes(uint32_t handle, float* outTime, float* outValue);      // 0x00a051c0
    void  MarkWorldRegion(bool force);                                         // 0x00a05220
    int   Release();                                                           // 0x00a05270
    void  UpdateGoalFade();                                                    // 0x00a05360
    void  ApplyAnimState(uint32_t mode);                                       // 0x00a05a70
};

// --------------------------------------------------------------------------- WrappedAnim
// COM-like wrapper: +0x1c is an owner exposing an interface at +0x50, and the
// flags live far away at +0x3038.
struct WrappedAnim {
    void**   vtbl;          // +0x00
    uint8_t  pad04[0x1c - 0x04];
    void*    mOwner;        // +0x1c (its +0x50 is a property interface)
    uint8_t  pad20[0x44 - 0x20];
    void*    mAttachments;  // +0x44
    uint8_t  f48;           // +0x48
    uint8_t  pad49[0x5c - 0x49];
    uint32_t mCount0;       // +0x5c
    uint32_t mCount1;       // +0x60
    uint32_t mChosen;       // +0x64
    uint8_t  pad68[0x3038 - 0x68];
    uint8_t  mFlag3038;     // +0x3038
    uint8_t  mFlag3039;     // +0x3039
    uint8_t  mFlag303a;     // +0x303a

    char SetFlagFromProperty(bool value);   // 0x00a054a0
    bool InitThing(void* attachments, uint8_t a, uint32_t b, uint8_t c, uint8_t d); // 0x00a05510
};

// --------------------------------------------------------------------------- AnimPimpl
// Thin forwarding wrappers around a pimpl reached through (this+4).
struct AnimPimpl {
    void**   vtbl;      // +0x00
    void*    impl;      // +0x04

    int GetStateA();                    // 0x00a055a0
    int GetStateB(int a1, int a2);      // 0x00a055c0
    int GetStateC(int a1, int a2);      // 0x00a055e0
    int GetStateD();                    // 0x00a05610
};

// --------------------------------------------------------------------------- goal selection
// The selector: slot counts at +0x50 (indexable), usage counters at +0x5c.
struct GoalList {
    uint8_t  pad00[0x50];
    int      mSlots[8];     // +0x50
    int      mCounts[8];    // +0x5c .. overlaps; classic overlapping-array trick

    int SelectFor(void* owner, int index, char useIndex); // 0x00a05660
};

// --------------------------------------------------------------------------- EA::Variant
struct var_t {
    void*    value;     // +0x00
    uint8_t  pad04[0x0c];
    uint16_t flags;     // +0x10
    uint16_t type;      // +0x12
};

// --------------------------------------------------------------------------- callees
void   FUN_009bd340(RigidBody* o);                              // 0x009bd340
float  FUN_009d3530(void* o);                                   // 0x009d3530
void   FUN_009b3920(const float* a, const float* b);            // 0x009b3920 Set@TargetFrame
AnimGoalInfo* FUN_009ff750(queued_blender* b);                  // 0x009ff750
AnimGoalInfo* FUN_009ff6f0(queued_blender* b, uint handle);     // 0x009ff6f0
int    FUN_009fef90(queued_blender* b, AnimGoalInfo* g);        // 0x009fef90
void   FUN_009fef50(AnimGoalInfo* g, float v);                  // 0x009fef50 (ret 4)
void   FUN_009fef20(AnimGoalInfo* b, AnimGoalInfo* g);          // 0x009fef20
void   FUN_009edb70(Vector4* out, const float* a, const float* b, uint32_t p4, uint32_t p5); // 0x009edb70
int    FUN_009b3450(CreatureStaticData* d);          // 0x009b3450 AddRef
int    FUN_009c26a0(CreatureStaticData* d);          // 0x009c26a0 Release
void   FUN_00c373d0();                                          // 0x00c373d0
void*  FUN_00f473a0(uint size, const char* a, int b, int c, const char* d, int e); // 0x00f473a0
void*  SP_PropertyManager();                                    // 0x0067de30
bool   SP_GetPropertyAsUint32Array(void* a, uint32_t k, uint32_t** out, uint32_t* count); // 0x006a0840
void*  Sim_GetPoliticalID(void* gameData);                      // 0x0097e850
void   Variant_SetU32(var_t* v, uint32_t value);                // 0x00422eb0
void   Variant_Destruct(var_t* v, bool b);                      // 0x0093db80
void   FUN_00a02d80(void* p);                                   // 0x00a02d80

extern float g_maxFloat;    // 0x01448a84 = FLT_MAX
extern float g_two;         // 0x01470f1c = 2.0f
extern float g_one;         // 0x01485720 = 1.0f
extern float g_tiny;        // 0x01551a8c = 0.001f
extern float g_negZero;     // 0x013eb8b0 = -0.0f
extern float g_piOver2;     // 0x01447a08 = 1.5707964f
extern int   g_thingFlag;   // 0x01551a7c (nonzero => a global object exists)
extern uint8_t g_thingData; // 0x01551a68

// 00a052e0 receives its receiver in ESI (register ABI in the original), so it is
// declared as an ordinary function taking the object pointer explicitly.
float AnimProgress(void* animObj);

// --------------------------------------------------------------------------- 0x00a04d20
// Walk the shape vector of the body at (this+0x17c), transform each sub-shape
// offset by the body quaternion and a factor of two, and keep the one closest to
// the query point.  Returns true and writes the world position of the winner.
// @ 0x00a04d20
bool cAnimatingCreature::ClosestBodyPosition(const Vector3& query, Vector3& out) {
    RigidBody* body = mRegionObj;
    BodyShapeEntry* b = body->begin;
    BodyShapeEntry* e = body->end;
    BodyShapeEntry* best = 0;
    float bestDist = g_maxFloat;
    if (b != e) {
        float qw = body->quat[0];
        float qx = body->quat[1];
        float qy = body->quat[2];
        float qz = body->quat[3];
        float px = body->pos[0];
        float py = body->pos[1];
        float pz = body->pos[2];
        for (;;) {
            float ox = b->off[0];
            float oy = b->off[1];
            float oz = b->off[2];
            float dx = query.x - (px +
                        ((ox * (-(qy * qy) - (qx * qx)) + oy * (qx * qw - qy * qz)) +
                         oz * (qy * qw + qx * qz)) * g_two + ox);
            float dz = query.z - (pz +
                        ((ox * (qy * qw - qx * qz) + oy * (qy * qx + qw * qz)) +
                         oz * (-(qx * qx) - (qw * qw))) * g_two + oz);
            float dy = query.y - (py +
                        ((ox * (qx * qw + qy * qz) + oy * (-(qy * qy) - (qw * qw))) +
                         oz * (qy * qx - qw * qz)) * g_two + oy);
            float d = (dy * dy + dz * dz) + dx * dx;
            if (best == 0 || d < bestDist) {
                best = b;
                bestDist = d;
            }
            b = (BodyShapeEntry*)((char*)b + 0x2bc);
            if (b == e) break;
        }
        if (best != 0) {
            RigidBody* body2 = mRegionObj;
            float qw2 = body2->quat[0];
            float qx2 = body2->quat[1];
            float qy2 = body2->quat[2];
            float qz2 = body2->quat[3];
            float sx = best->off[0];
            float sy = best->off[1];
            float sz = best->off[2];
            out.x = ((sx * (-(qy2 * qy2) - (qx2 * qx2)) +
                      sz * (qy2 * qw2 + qx2 * qz2) +
                      sy * (qx2 * qw2 - qy2 * qz2)) * g_two + sx) + body2->pos[0];
            out.y = ((sx * (qx2 * qw2 + qy2 * qz2) +
                      sy * (-(qy2 * qy2) - (qw2 * qw2)) +
                      sz * (qy2 * qx2 - qw2 * qz2)) * g_two + sy) + body2->pos[1];
            out.z = ((sx * (qy2 * qw2 - qx2 * qz2) +
                      sy * (qy2 * qx2 + qw2 * qz2) +
                      sz * (-(qx2 * qx2) - (qw2 * qw2))) * g_two + sz) + body2->pos[2];
            return true;
        }
    }
    return false;
}

// @ 0x00a05150
void cAnimatingCreature::GetCurrentAnimation(uint32_t* outIdx, float* outTime, int* outValue, int* outFlags) {
    AnimGoalInfo* g = FUN_009ff750(mBlender);
    if (g == 0) return;
    if (outIdx != 0) *outIdx = g->fD8;
    if (outFlags != 0) *outFlags = FUN_009fef90(mBlender, g);
    if (g->p0 != 0) {
        if (outTime != 0) *outTime = (float)g->timeA8;
        if (outValue != 0) *outValue = (int)g->fB0;
    }
}

// @ 0x00a051c0
bool cAnimatingCreature::GetGoalTimes(uint32_t handle, float* outTime, float* outValue) {
    AnimGoalInfo* g = FUN_009ff6f0(mBlender, handle);
    if (g == 0) return false;
    if (g->flag6c != 0) return false;
    if (outTime != 0) *outTime = (float)g->p0->vB8;
    if (outValue != 0) *outValue = (float)g->timeA8;
    return true;
}

// @ 0x00a05220
void cAnimatingCreature::MarkWorldRegion(bool force) {
    if (force || mWorldRegion < mViewer->region) {
        if (mRegionObj != 0) {
            FUN_009bd340(mRegionObj);
            mRegionObj->dirtyFlag = 1;
        }
        mWorldRegion = mViewer->region;
    }
}

// @ 0x00a05270
int cAnimatingCreature::Release() {
    int n = mRefCount - 1;
    int z = 0;
    int* p = (n > 0) ? &n : &z;
    int v = *p;
    mRefCount = v;
    if (v > 0) return v;
    mRefCount = 1;
    if (mRegionObj != 0) {
        AnimViewer* vw = mViewer;
        if (vw != 0) {
            ((void(__thiscall*)(void*, cAnimatingCreature*))((*(void***)vw)[0x3c / 4]))(vw, this);
        }
    }
    ((void(__thiscall*)(cAnimatingCreature*, int))vtbl[0x7c / 4])(this, 1);
    return 0;
}

// --------------------------------------------------------------------------- helpers
// @ 0x00a052e0 — eased progress of the current animation, in 0..1.
// The original receives its receiver in ESI; see nonmatching.txt.
float AnimProgress(void* animObj) {
    float raw = FUN_009d3530((char*)animObj + 0x15b8);
    float frac = raw / *(float*)(*(char**)animObj + 0x3ec);
    if (!(frac > 0.0f)) frac = 0.0f;
    if (frac > 1.0f) frac = 1.0f;
    float p = (float)FUN_011e08f0((double)frac);
    float s = (float)sin(p * g_piOver2);
    if (!(s > g_tiny)) return 0.0f;
    return s;
}

// @ 0x00a056e0
void* GetGlobalThing() {
    return g_thingFlag ? (void*)&g_thingData : 0;
}

// @ 0x00a05360
void cAnimatingCreature::UpdateGoalFade() {
    AnimGoalInfo* prev = 0;
    AnimGoalInfo* cur = 0;
    if (mPrevGoal != 0) {
        prev = FUN_009ff6f0(mBlender, mPrevGoal);
        if (prev != 0) FUN_009fef50(prev, 0.0f);
    }
    if (mCurGoal != 0) {
        cur = FUN_009ff6f0(mBlender, mCurGoal);
        if (cur != 0) FUN_009fef50(cur, 1.0f);
    }
    if (mCurGoal != mPrevGoal && cur != 0 && prev != 0 && cur->zeroC0 != 0) {
        float t = AnimProgress(mRegionObj);
        FUN_009fef50(cur, 1.0f - t);
        FUN_009fef50(prev, t);
        AnimGoalInfo* g = prev->p0;
        if (g != 0) {
            void* gd = (void*)((char*)mRegionObj + 0x15b8);
            void* pol = Sim_GetPoliticalID(gd);
            FUN_00c373d0();
            float f = 0.0f;   // result of the above is in st0 in the original
            g->fB0 = (uint32_t)(f * g->vB8);
        }
        FUN_009fef20(prev, cur);
    }
}

// --------------------------------------------------------------------------- accessor wrappers
// @ 0x00a054a0
char WrappedAnim::SetFlagFromProperty(bool value) {
    char old = mFlag3038;
    void* iface = *(void**)((char*)mOwner + 0x50);
    var_t* var = (var_t*)(*(void*(__thiscall**)(void*, uint32_t))(*(void***)iface + 10))(iface, 0xf0a16bfc);
    char* p;
    uint16_t ty = var->type;
    if (ty == 1 || ty == 0x10) {
        if ((var->flags & 0x30) != 0) p = *(char**)var;
        else p = (ty != 0) ? (char*)var : 0;
    } else {
        p = (char*)0x15d115d;
    }
    if (*p != 0) {
        mFlag3038 = value;
        return old;
    }
    mFlag3038 = 1;
    return old;
}

// @ 0x00a05510
bool WrappedAnim::InitThing(void* attachments, uint8_t a, uint32_t b, uint8_t c, uint8_t d) {
    void* old = mAttachments;
    if (attachments != old) {
        if (attachments != 0) ((void(__thiscall**)(void*))*(void***)attachments)[0](attachments);
        mAttachments = attachments;
        if (old != 0) ((void(__thiscall**)(void*))*(void***)old)[1](old);
    }
    f48 = a;
    mCount0 = 0;
    mCount1 = 0;
    mChosen = 0;
    mFlag3039 = c;
    mFlag303a = d;
    return true;
}

// @ 0x00a055a0
int AnimPimpl::GetStateA() {
    void* p = impl;
    if (p != 0) return ((int(__thiscall**)(void*, int))*(void***)p)[0x24 / 4](p, 0);
    return -1;
}

// @ 0x00a055c0
int AnimPimpl::GetStateB(int a1, int a2) {
    void* p = impl;
    if (p != 0) return ((int(__thiscall**)(void*, int, int))*(void***)p)[0x30 / 4](p, a1, a2);
    return -1;
}

// @ 0x00a055e0
int AnimPimpl::GetStateC(int a1, int a2) {
    void* p = impl;
    if (p != 0) {
        if (((bool(__thiscall**)(void*, int, int))*(void***)p)[0x38 / 4](p, a1, a2)) return a2;
    }
    return -1;
}

// @ 0x00a05610
int AnimPimpl::GetStateD() {
    void* p = impl;
    if (p != 0) return ((int(__thiscall**)(void*))*(void***)p)[0x2c / 4](p);
    return -1;
}

// @ 0x00a05660
int GoalList::SelectFor(void* owner, int index, char useIndex) {
    char* o = (char*)owner;
    int chosen = 0;
    if (useIndex) {
        *(int*)(o + 0x54) = index;
        ++mCounts[index];
        chosen = index;
    }
    if (index >= 0) {
        int* slot = &mSlots[index];
        for (;;) {
            if (slot[3] < *slot || index == 0) {
                *(int*)(o + 0x50) = index;
                if (!useIndex) {
                    ++mCounts[index];
                    chosen = *(int*)(o + 0x50);
                }
                break;
            }
            --index;
            --slot;
            if (index < 0) break;
        }
    }
    if (chosen != 0 && chosen != *(int*)(o + 0x58)) {
        char* rb = *(char**)(o + 0x17c);
        FUN_009b3920((const float*)(rb + 0x18), (const float*)(rb + 0x3c));
    }
    *(int*)(o + 0x58) = chosen;
    return chosen;
}

// @ 0x00a056f0
void** StaticDataSlot::SwapStaticData(CreatureStaticData** src) {
    CreatureStaticData* nv = *src;
    CreatureStaticData* ov = p;
    if (nv != ov) {
        if (nv != 0) nv->AddRef();
        p = nv;
        if (ov != 0) ov->Release();
    }
    return (void**)this;
}
// --------------------------------------------------------------------------- EASTL rbtree helpers
// Node: +0x00 left, +0x04 right, +0x10 key.lo, +0x14 key.hi.  Header +4 is the
// end() sentinel; the root pointer lives at header+0xc.
struct RBTreeHead {
    uint8_t  pad00[0xc];
    char*    root;      // +0x0c

    void* FindLower(void** outNode, uint32_t* key);   // 0x00a05730
    void* FindRaw(void** outNode, uint32_t* key);     // 0x00a057f0
};

// @ 0x00a05730
void* RBTreeHead::FindLower(void** outNode, uint32_t* key) {
    char* sentinel = (char*)this + 4;
    char* pos = sentinel;
    char* node = root;
    if (node != 0) {
        uint32_t klo = key[0];
        uint32_t khi = key[1];
        for (;;) {
            uint32_t nhi = *(uint32_t*)(node + 0x14);
            uint32_t nlo;
            if (nhi < khi) {
                node = *(char**)node;
            } else if (nhi > khi) {
                pos = node;
                node = *(char**)(node + 4);
            } else if ((nlo = *(uint32_t*)(node + 0x10)) < klo) {
                node = *(char**)node;
            } else {
                pos = node;
                node = *(char**)(node + 4);
            }
            if (node == 0) break;
        }
    }
    char* result = sentinel;
    if (pos != sentinel) {
        uint32_t klo = key[0];
        uint32_t khi = key[1];
        uint32_t phi = *(uint32_t*)(pos + 0x14);
        if (khi > phi || (khi == phi && klo >= *(uint32_t*)(pos + 0x10))) {
            *outNode = pos;
            return outNode;
        }
    }
    *outNode = result;
    return outNode;
}

// @ 0x00a057f0
void* RBTreeHead::FindRaw(void** outNode, uint32_t* key) {
    char* sentinel = (char*)this + 4;
    char* pos = sentinel;
    char* node = root;
    if (node != 0) {
        uint32_t klo = key[0];
        uint32_t khi = key[1];
        for (;;) {
            uint32_t nhi = *(uint32_t*)(node + 0x14);
            if (nhi < khi) {
                node = *(char**)node;
            } else if (nhi > khi) {
                pos = node;
                node = *(char**)(node + 4);
            } else if (*(uint32_t*)(node + 0x10) < klo) {
                node = *(char**)node;
            } else {
                pos = node;
                node = *(char**)(node + 4);
            }
            if (node == 0) break;
        }
    }
    *outNode = pos;
    return outNode;
}

// A callback pair holder: +0x20 argument, +0x24 function pointer.
struct CallbackPair {
    uint8_t  pad00[0x20];
    void*    arg;       // +0x20
    void*    fn;        // +0x24

    bool SetCallbackPair(void* newObj);   // 0x00a057a0
};

// @ 0x00a057a0
bool CallbackPair::SetCallbackPair(void* newObj) {
    void (*oldFn)(void*);
    void* oldArg;
    if (newObj != 0) {
        void** vt = *(void***)newObj;
        ((void(__thiscall*)(void*))vt[1])(newObj);
        oldFn = *(void(**)(void*))((char*)this + 0x24);
        oldArg = *(void**)((char*)this + 0x20);
        *(void**)((char*)this + 0x20) = newObj;
        *(void**)((char*)this + 0x24) = (void*)FUN_00a02d80;
    } else {
        oldFn = *(void(**)(void*))((char*)this + 0x24);
        oldArg = *(void**)((char*)this + 0x20);
        *(void**)((char*)this + 0x20) = 0;
        *(void**)((char*)this + 0x24) = 0;
    }
    if (oldFn != 0) oldFn(oldArg);
    return true;
}

// The 0x1c-stride vector header at (this): +0x00 begin, +0x04 end, +0x08 cap.
struct Vec28 {
    void*  begin;       // +0x00
    void*  end;         // +0x04
    void*  cap;         // +0x08

    Vec28* Construct(int count, int unused);   // 0x00a05830
};

// @ 0x00a05830
Vec28* Vec28::Construct(int count, int unused) {
    (void)unused;
    void* p = 0;
    if (count != 0) {
        p = FUN_00f473a0(count * 0x1c, "EASTL", 0, 0,
                         "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                         0xd1);
    }
    this->begin = p;
    this->end = p;
    this->cap = (char*)p + count * 0x1c;
    return this;
}

// @ 0x00a05890
void* RotationAtoBWrap(void* out, float* a, float* b, uint32_t p4, uint32_t p5) {
    float nb[3];
    nb[0] = a[0]; nb[1] = a[1]; nb[2] = a[2];
    float lb = (float)sqrt((double)(nb[2] * nb[2] + nb[1] * nb[1] + nb[0] * nb[0]));
    if (lb != 0.0f) {
        float inv = g_one / lb;
        nb[0] *= inv; nb[1] *= inv; nb[2] *= inv;
    }
    float na[3];
    na[0] = b[0]; na[1] = b[1]; na[2] = b[2];
    float la = (float)sqrt((double)(na[2] * na[2] + na[1] * na[1] + na[0] * na[0]));
    if (la != 0.0f) {
        float inv = g_one / la;
        na[0] *= inv; na[1] *= inv; na[2] *= inv;
    }
    FUN_009edb70((Vector4*)out, nb, na, p4, p5);
    return out;
}

// --------------------------------------------------------------------------- preload list
// @ 0x00a059d0
void DoAnimationPreload() {
    uint32_t* obj = 0;
    void* pm = SP_PropertyManager();
    (*(void(__thiscall**)(void*, uint32_t, int, uint32_t**))(*(void***)pm + 0x2c / 4))(pm, 0x5de9bcff, 0, &obj);
    if (obj == 0) return;
    uint32_t* data = 0;
    uint32_t count = 0;
    if (SP_GetPropertyAsUint32Array(obj, 0xacdab823, &data, &count)) {
        for (int i = 0; i < (int)count; ++i) {
            (*(void(__thiscall**)(void*, uint32_t))(*(void***)obj + 0x44 / 4))(obj, data[i]);
        }
    }
    (*(void(__thiscall**)(void*))(*(void***)obj + 1))(obj);
}

// --------------------------------------------------------------------------- variant setter
// @ 0x00a05a70
void cAnimatingCreature::ApplyAnimState(uint32_t mode) {
    (void)mode;
    if (mViewer == 0) return;
    void* iface = *(void**)((char*)mViewer + 0x50);
    if (iface == 0) return;

    var_t* var = (var_t*)(*(void*(__thiscall**)(void*, uint32_t))(*(void***)iface + 10))(iface, 0xc2dafabb);
    uint16_t ty = var->type;
    char* p;
    if (ty == 9 || ty == 0x10) {
        if ((var->flags & 0x30) != 0) p = *(char**)var;
        else p = (ty != 0) ? (char*)var : 0;
    } else {
        p = (char*)0x15d9c68;
    }
    int32_t cur = *(int32_t*)p;

    if (cur == 1) {
        var_t v1;
        Variant_SetU32(&v1, 0);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xc2dafabb, &v1);
        if ((v1.flags & 4) != 0) Variant_Destruct(&v1, false);
        var_t v2;
        Variant_SetU32(&v2, 0);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xda61d1c, &v2);
        if ((v2.flags & 4) != 0) Variant_Destruct(&v2, false);
    } else {
        var_t v1;
        Variant_SetU32(&v1, 1);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xc2dafabb, &v1);
        if ((v1.flags & 4) != 0) Variant_Destruct(&v1, false);
        var_t v2;
        Variant_SetU32(&v2, 0xffffffff);
        (*(void(__thiscall**)(void*, uint32_t, var_t*))(*(void***)iface + 5))(iface, 0xda61d1c, &v2);
        if ((v2.flags & 4) != 0) Variant_Destruct(&v2, false);
    }
}
