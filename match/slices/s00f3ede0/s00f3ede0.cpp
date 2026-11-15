// Slice s00f3ede0: rule evaluation for a hashed (kind, sub) pair in the 0x00F3xxxx object-query region.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern char g_15acb40;                          // 0x015ACB40, debug/feature switch

// Result of the (kind, sub) classification of one handle (filled by Mgr::Classify, 0xF3ECB0).
struct KindInfo {
    int kind;                                   // +0x00 hashed kind id
    int sub;                                    // +0x04 hashed sub id
    uint8_t flag;                               // +0x08
    uint32_t mask;                              // +0x0c
};

// A rule row: rule[0] = kind id to test, rule[1] = sub id, rule[3] = mask of conditions it covers.
struct Rule {
    int kind;
    int sub;
    int unused;
    uint32_t mask;
};

struct Subject {
    char pad[0x50];
    uint32_t flags;                             // +0x50
};
struct Context {
    char pad[0x230];
    int result;                                 // +0x230
};

enum {
    kKindA = -0x1cb175a0,                       // 0xE34E8A60
    kKindB = -0x4ef1ad91,                       // 0xB10E526F
    kKindC = -0x30a9f666,                       // 0xCF56099A
    kKindD = -0x2c83efbb,                       // 0xD37C1045
    kKindE = 0x5b3d1d0d,
    kKindF = 0x6031c03a,
    kSub1 = -0x76808753,                        // 0x897F78AD
    kSub2 = 0x0b7e477a,
    kSub3 = 0x167b1f54,
    kOtherX = -0x1ec800f8,                      // 0xE137FF08
    kOtherY = 0x7998ce71
};

void* __cdecl FUN_00b18e00(void* handle);       // 0x00B18E00 (cdecl; virtual query of the handle)

struct Mgr {
    char pad[0x8c];
    int mNoHandle;                              // +0x8c
    void* FUN_00f3d780(int id);                 // 0x00F3D780 (thiscall, ret 4)
    void Classify(int id, void* handleInfo, KindInfo* out);     // 0x00F3ECB0 (thiscall, ret 0xC)
    bool TryApply(Subject* s, void* handleInfo, float f, int flag);  // 0x00F3C870 (thiscall, ret 0x10)
    int  Compute(Rule* rule, KindInfo* info, Context* ctx, int id);  // 0x00F3EDE0 (thiscall, ret 0x10)
    bool Evaluate(Subject* subject, Rule* rule, Context* ctx, int id, char useDebug);   // 0x00F3F110
};

// @ 0x00F3F110
bool Mgr::Evaluate(Subject* subject, Rule* rule, Context* ctx, int id, char useDebug)
{
    void* h = FUN_00f3d780(id);
    void* info = FUN_00b18e00(h);
    KindInfo ki;
    ki.mask = 0;
    Classify(id, h, &ki);
    bool isDE;
    if (ki.kind == kKindD || (isDE = false, ki.kind == kKindE))
        isDE = true;
    if ((rule->mask & ki.mask) == 0)
        return true;
    char flag;
    if (g_15acb40 != 0 && useDebug != 0 && (subject->flags & 0x2000) != 0)
        flag = 1;
    else
        flag = 0;
    bool r;
    switch (rule->kind) {
    case kKindA:
        if (ki.kind == kKindB) return true;
        if (ki.kind == kKindF && ki.sub == kSub3) return true;
        if (isDE) return true;
        if (ki.kind == kOtherX) return true;
        if (ki.kind == kOtherY) return true;
        if (ki.kind == kKindC) return true;
        if (ki.kind == kKindF) {
            if (ki.sub == kSub2) return true;
            if (ki.sub == kSub3) return true;
        }
        r = TryApply(subject, info, 0.0f, 0);
        if (!r) return true;
        if (ki.kind <= kKindE) {
            if (ki.kind == kKindE || ki.kind == kKindD) {
                ctx->result = 1;
                return false;
            }
            if (ki.kind == kKindA) {
                ctx->result = 3;
                return false;
            }
            return false;
        }
        if (ki.kind != kKindF) return false;
        if (ki.sub == kSub1)
            ctx->result = Compute(rule, &ki, ctx, id);
        return false;
    case kKindB:
        if (isDE) {
            r = TryApply(subject, info, 0.0f, 0);
            if (r) ctx->result = 8;
            return !r;
        }
        if (g_15acb40 == 0) return true;
        if (useDebug == 0) return true;
        if (ki.kind != kKindA) {
            if (ki.kind != kKindF) return true;
            if (ki.sub != kSub1) {
                if (ki.sub != kSub2) return true;
                r = TryApply(subject, info, 0.0f, flag);
                if (r) ctx->result = 10;
                return !r;
            }
            r = TryApply(subject, info, 0.0f, flag);
            if (r) ctx->result = 10;
            return !r;
        }
        r = TryApply(subject, info, 0.0f, flag);
        if (r) ctx->result = 9;
        return !r;
    case kKindC:
        if (!isDE) return true;
        r = TryApply(subject, info, 0.0f, 0);
        if (r) ctx->result = 0x1e;
        return !r;
    case kKindD:
    case kKindE:
        break;
    case kKindF:
        if (rule->sub == kSub1) {
            if (isDE) return true;
            if (ki.kind == kOtherX) return true;
            if (ki.kind == kOtherY) return true;
            if (ki.kind == kKindB) return true;
            if (ki.kind == kKindC) return true;
            if (ki.kind == kKindF && ki.sub == kSub3) return true;
            r = TryApply(subject, info, 0.0f, 0);
            if (r) {
                if (ki.kind <= kKindE) {
                    if (ki.kind != kKindE && ki.kind != kKindD && ki.kind != kKindA)
                        return !r;
                } else if (ki.kind != kKindF || (ki.sub != kSub1 && ki.sub != kSub2)) {
                    return !r;
                }
                ctx->result = Compute(rule, &ki, ctx, id);
            }
            return !r;
        }
        if (rule->sub == kSub2) {
            if (ki.kind != kKindF) return true;
            if (ki.sub != kSub2 && ki.sub != kSub1) return true;
            r = TryApply(subject, info, 0.0f, 0);
            if (!r || (ki.sub != kSub1 && ki.sub != kSub2))
                return !r;
            ctx->result = Compute(rule, &ki, ctx, id);
            return !r;
        }
        if (rule->sub != kSub3) return true;
        if (!isDE) {
            if (g_15acb40 == 0) return true;
            if (useDebug == 0) return true;
            if (ki.kind == kKindA) {
                r = TryApply(subject, info, 0.0f, flag);
                if (r) ctx->result = 0x14;
                return !r;
            }
            if (ki.kind != kKindF) return true;
            if (ki.sub == kSub1) {
                r = TryApply(subject, info, 0.0f, flag);
                if (r) ctx->result = 0;
                return !r;
            }
            if (ki.sub != kSub2) return true;
            r = TryApply(subject, info, 0.0f, flag);
            if (r) ctx->result = 0;
            return !r;
        }
        r = TryApply(subject, info, 0.0f, 0);
        if (!r) return true;
        if (ki.kind == kKindD || ki.kind == kKindE)
            ctx->result = Compute(rule, &ki, ctx, id);
        return false;
    default:
        return true;
    }

    // rule kind D or E
    if (ki.kind != kOtherX && ki.kind != kOtherY) {
        bool b;
        if (ki.kind == kKindF) {
            if (ki.sub == kSub2) goto L85e;
            b = (ki.sub == kSub1);
        } else {
            b = (ki.kind == kKindA);
        }
        if (!b) {
            r = TryApply(subject, info, 0.0f, 0);
            if (r) {
                if (ki.kind <= kKindD) {
                    if (ki.kind != kKindD) {
                        if (ki.kind == kKindB) { ctx->result = 0xc; return !r; }
                        if (ki.kind == kKindC) { ctx->result = 0x12; return !r; }
                        return !r;
                    }
                } else if (ki.kind != kKindE) {
                    if (ki.kind == kKindF && ki.sub == kSub3) {
                        ctx->result = Compute(rule, &ki, ctx, id);
                        return !r;
                    }
                    return !r;
                }
                ctx->result = 0xb;
            }
            return !r;
        }
    }
L85e:
    if (g_15acb40 != 0 && useDebug != 0) {
        if (ki.kind == kKindA) {
            r = TryApply(subject, info, 0.0f, flag);
            if (r) ctx->result = 0xd;
            return !r;
        }
        if (ki.kind == kKindF) {
            if (ki.sub == kSub1) {
                r = TryApply(subject, info, 0.0f, flag);
                if (r) ctx->result = 0x10;
                return !r;
            }
            if (ki.sub == kSub2) {
                r = TryApply(subject, info, 0.0f, flag);
                if (r) ctx->result = 0xf;
                return !r;
            }
        }
    }
    return true;
}

// ---- tutorial/scenario row lookup ------------------------------------------------------------
// Row of the simulation data table (out-of-slice builder 0x00F3E8A0 keyed by a slot reference).
struct SimRow {
    char pad[0x70];
    int mOffset;                                // +0x70 byte offset inside a per-tutorial block
};
// Slot reference handed in by the callers: only the key at +0x1c is read.
struct SlotRef {
    char pad[0x1c];
    void* mKey;                                 // +0x1c
};
// Tutorial bookkeeping hanging off the global singleton.
struct TutorialState {
    char pad[0xb8];
    int mActive;                                // +0xb8 currently active tutorial index
};
struct SimGlobals {
    char pad00[0x78];
    TutorialState* mTutorials;                  // +0x78
    char pad7c[0xcc - 0x7c];
    int mMode;                                  // +0xcc
    int GetTutorialRowOffset(SlotRef* slot);    // 0x00F3F950 (does not touch `this`)
};
extern SimGlobals* g_simGlobals;                // 0x016C7AA4
extern "C" SimRow* __stdcall FUN_00f3e8a0(void* key);    // 0x00F3E8A0
extern "C" int __cdecl ScenarioTutorials_GetActive();    // 0x00EFC520

// @ 0x00F3F950
int SimGlobals::GetTutorialRowOffset(SlotRef* slot)
{
    void* key = slot->mKey;
    SimRow* row = FUN_00f3e8a0(key);
    if (row) {
        if (g_simGlobals->mMode == 2) {
            TutorialState* tutorials = g_simGlobals->mTutorials;
            return tutorials->mActive * 0x4e0 + row->mOffset;
        }
        return ScenarioTutorials_GetActive() * 0x4e0 + row->mOffset;
    }
    return 0;
}

// ---- fixed-stride record array ---------------------------------------------------------------
// Every record is 0x44 bytes; the array keeps [begin, cur, end) like eastl::vector.
struct SimRecord {
    uint8_t mData[0x44];
};
struct SimArray {
    SimRecord* mBegin;                          // +0x00
    SimRecord* mCur;                            // +0x04
    SimRecord* mEnd;                            // +0x08
    SimArray* Assign(int count, const SimRecord* value, int unused);
};
// 0x00F473A0: Spore's debug-tagged block allocator (size, category, 0, 0, file, line).
void* __cdecl SimAllocBlock(int size, const char* category, int arg3, int arg4,
                            const char* file, int line);
// 0x00F09D70: fills `count` records with `value`.
void __cdecl SimFillRecords(SimRecord* dest, int count, const SimRecord* value, int valueCount);

// @ 0x00F3F9A0
SimArray* SimArray::Assign(int count, const SimRecord* value, int unused)
{
    SimRecord* p;
    if (count)
        p = (SimRecord*)SimAllocBlock(count * (int)sizeof(SimRecord), "Simulator", 0, 0,
                                      "SimData.cpp", 209);
    else
        p = 0;
    SimRecord* end = p + count;
    mBegin = p;
    mCur = p;
    mEnd = end;
    SimFillRecords(p, count, value, count);
    mCur = mBegin + count;
    return this;
}
