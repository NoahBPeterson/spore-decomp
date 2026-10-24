// Slice s00ebd220: Effects::PreUpdate (0x00ebd420, 2040 bytes) -- the spawn pass of the area-effect
// (weather / ambient pusher) manager.  Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /GS- (x87 sqrtf/1.0f/ chains,
// SSE scalar for the rest).
//
// __thiscall, ret 4 (the float argument -- the frame time -- is not used).  `this` is the effects manager
// that also owns Effects::Tick (0x00ebe3e0, which calls this first) and Effects::Update (0x00ebdc20):
//   +0x08 / +0x0c  begin / end of the active-entry vector (0x50-byte Entry records)
//   +0x1c          array of 0x20-byte cSPTimer, one per effect definition (spawn period timers)
// The effect definitions are a global table (0x015b84f0 + 0x18, 0x54-byte EffectDef records).
//
// What it does: if effects are enabled, the active planet record's two climate values (+0xb0, +0xb4) are
// classified against a hot / cold threshold (0.8 / 0.2) into a bit mask (temperature 1/2/4, humidity
// 0x20/0x40/0x80).  For every definition that has a type, whose mask contains those bits and whose period
// timer has run out, the timer is restarted and a candidate position is picked: the focus point plus a
// scaled offset, randomised on the planet and snapped to the surface.  The mask gets bit 8 (land) or
// 0x10 (water) from a water query and must still match.  Surface-type effects (type 2 / 3) on land are
// rejected when a noun (in the right game mode) is close to the point, when the 0x18-type object query
// finds something within the radius, or when the surface is steeper than ~45 degrees.  An accepted
// candidate becomes a new Entry: random tangent direction, speed from the definition, start timer, effect
// started through the effects manager and oriented to the surface; if the effect fails to start the new
// entry is dropped again.
#include "types.h"
#include <math.h>

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };
struct Matrix3 { float m[9]; };

struct Transform {                       // 0x38 bytes, out-of-line ctor 0x00434040
    uint16_t mnFlags;                    // +0x00
    uint16_t mnCount;                    // +0x02
    Vec3 mOffset;                        // +0x04
    float mfScale;                       // +0x10
    Matrix3 mRotation;                   // +0x14
    Transform();                         // 0x00434040
};

struct Timer {                           // cSPTimer, 0x20 bytes
    uint32_t pad[8];
    uint64_t GetElapsedTime() const;     // 0x00bc3190
    void Restart();                      // 0x00bc3130
    void Start();                        // 0x00bc30f0
};

struct EffectHandle {
    virtual void v0();
    virtual void Release();              // +4
    virtual void Stop(int);              // +8
    virtual void Destroy(int flags);      // +0x0c
    virtual void v4();
    virtual void v5();
    virtual void SetTransform(const Transform*);   // +0x18
};

struct EffectsManager {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual bool PlayEffect(uint32_t id, int flags, EffectHandle** out);   // +0x2c
};
EffectsManager* GetEffectsManager();     // 0x0067ddd0

struct PlanetRecord {
    uint8_t pad[0xb0];
    float humidity;                      // +0xb0
    float temperature;                   // +0xb4
};
PlanetRecord* GetActivePlanetRecord();   // 0x010212a0

struct EffectDef {                       // 0x54 bytes
    uint32_t effectId;                   // +0x00
    uint32_t pad04[3];
    uint32_t mask;                       // +0x10
    int type;                            // +0x14 : 1 = flying, 2 / 3 = surface bound
    float nounRadius;                    // +0x18
    float radiusOffset;                  // +0x1c
    float scale;                         // +0x20
    float period;                        // +0x24 (seconds)
    float focusScale;                    // +0x28
    float maxHeight;                     // +0x2c
    uint32_t pad30[7];
    float speed;                         // +0x48
    uint32_t pad4c[2];
};
struct EffectDefTable {
    uint32_t pad[6];
    EffectDef* begin;                    // +0x18
    EffectDef* end;                      // +0x1c
};
EffectDefTable* GetEffectDefTable();     // 0x010408b0

struct Entry {                           // 0x50 bytes
    EffectDef* def;                      // +0x00
    int state;                           // +0x04
    float radius;                        // +0x08
    Vec3 pos;                            // +0x0c
    Vec3 vel;                            // +0x18
    uint32_t pad24;
    Timer timer;                         // +0x28
    EffectHandle* effect1;               // +0x48
    EffectHandle* effect2;               // +0x4c
};
struct EntryVec {
    Entry* mpBegin;                      // +0
    Entry* mpEnd;                        // +4
    void Append();                       // 0x00ebd190 (grows by one uninitialised Entry)
    void PopBack();                      // 0x00ebbb10 (destroys the last Entry)
    void DestroyRange(Entry* begin, Entry* end);   // 0x00ebb820
};

struct PlanetModel {
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* in, float minHeight, float maxHeight);   // 0x00b81780 (ret 0x10)
    Vec3* SnapToSurface(Vec3* out, const Vec3* in);                                              // 0x00b81630 (ret 8)
    bool IsWater(const Vec3* pos);                                                               // 0x00b7e3e0 (ret 4)
    Vec3* GetUp(Vec3* out, const Vec3* pos);                                                     // 0x00b7e3b0 (ret 8)
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);                                   // 0x00b7f190 (ret 8)
};
PlanetModel* GetPlanetModel();           // 0x00b3d350

struct Noun {
    bool IsNear(const Vec3* pos, float radius);          // 0x00bd9c30 (ret 8)
};
struct NounList { Noun** mpBegin; Noun** mpEnd; };
struct NounManager {
    NounList* GetNouns();                // 0x00ace2c0
};
NounManager* GetNounManager();           // 0x00b3d300
unsigned GetCurrentGameMode();           // 0x00b5b800

struct ObjectQuery {
    uint8_t pad[4];
};
struct ObjectFinder {
    void Find(const Vec3* pos, void* outVec, int types, float radius, int a, int b);    // 0x00b79c30 (ret 0x18)
};
ObjectFinder* GetObjectFinder();         // 0x00b3d3c0

struct FoundVec {                        // eastl::vector<void*, sp allocator>: only begin / end / capacity are touched
    void** mpBegin; void** mpEnd; void** mpCapacity;
    FoundVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~FoundVec() { if (mpBegin) { if (((int*)mpBegin)[-1]) FreeBlock(mpBegin); } }
    static void FreeBlock(void* p);      // 0x00f47380
};

bool AreEffectsActive();                           // 0x00ebb8b0 (cdecl)
void GetFocusPoint(Vec3* focus, Vec3* axis);       // 0x00ebb980 (cdecl)
void RandomDiskPoint(float* out);                  // 0x00ebbb40 (cdecl)
const Vec3* OrthogonalVector(Vec3* out, const Vec3* in);   // 0x006985b0 (cdecl)
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quat* q);   // 0x0059c190 (cdecl)

struct Effects {
    uint32_t pad00[2];
    EntryVec mEntries;                   // +0x08
    uint32_t pad10[3];
    Timer* mTimers;                      // +0x1c

    void PreUpdate(float dt);            // 0x00ebd420
};

// @ 0x00ebd420
void Effects::PreUpdate(float dt)
{
    if (!AreEffectsActive())
        return;

    PlanetRecord* planet = GetActivePlanetRecord();
    uint32_t flags = planet->temperature > 0.8f ? 1 : (0.2f > planet->temperature ? 4 : 2);
    flags |= planet->humidity > 0.8f ? 0x20 : (0.2f > planet->humidity ? 0x80 : 0x40);

    EffectDefTable* table = GetEffectDefTable();
    EffectDef** defs = &table->begin;
    int count = (int)(table->end - table->begin);
    int timerOffset = 0;
    for (int i = 0; i < count; i++, timerOffset += sizeof(Timer))
    {
        EffectDef* def = &(*defs)[i];
        if (def->type == 0 || (flags & def->mask) != flags)
            continue;
        Timer* timer = (Timer*)((char*)mTimers + timerOffset);
        if (!(def->period < (float)timer->GetElapsedTime() * 0.001f))
            continue;
        timer->Restart();

        Vec3 focus;
        Vec3 axis;
        GetFocusPoint(&focus, &axis);
        Vec3 p;
        p.x = focus.x + def->focusScale * axis.x;
        p.y = focus.y + axis.y * def->focusScale;
        p.z = focus.z + axis.z * def->focusScale;
        Vec3 tmp;
        const Vec3* r = GetPlanetModel()->MakeRandomWorldPosition(&tmp, &p, 0.0f, def->maxHeight);
        p = *r;
        r = GetPlanetModel()->SnapToSurface(&tmp, &p);
        p = *r;
        bool water = GetPlanetModel()->IsWater(&p);

        uint32_t flags2 = flags | (water ? 0x10 : 8);
        if ((flags2 & def->mask) != flags2)
            continue;

        bool ok = true;
        if (!water && (def->type == 2 || def->type == 3))
        {
            if (GetCurrentGameMode() == 0x1654c05)
            {
                NounList* nouns = GetNounManager()->GetNouns();
                for (Noun** n = nouns->mpBegin; n != nouns->mpEnd; n++)
                {
                    if ((*n)->IsNear(&p, def->nounRadius))
                        goto next;
                }
            }
            {
                FoundVec found;
                GetObjectFinder()->Find(&p, &found, 0x18, 10.0f, 0, 0);
                if (found.mpBegin != found.mpEnd)
                    ok = false;
            }
            if (!ok)
                continue;
            float inv = 1.0f / sqrtf(p.z * p.z + p.y * p.y + p.x * p.x);
            Vec3 n;
            n.x = inv * p.x;
            n.y = p.y * inv;
            n.z = p.z * inv;
            Vec3 up;
            GetPlanetModel()->GetUp(&up, &p);
            if (0.707f > up.z * n.z + up.y * n.y + up.x * n.x)
                continue;
        }

        // spawn a new entry
        mEntries.Append();
        Entry* e = mEntries.mpEnd - 1;
        e->def = def;

        float inv = 1.0f / sqrtf(p.z * p.z + p.y * p.y + p.x * p.x);
        Vec3 n;
        n.x = inv * p.x;
        n.y = p.y * inv;
        n.z = p.z * inv;
        Vec3 otmp;
        const Vec3* o = OrthogonalVector(&otmp, &n);
        float inv1 = 1.0f / sqrtf(o->x * o->x + o->y * o->y + o->z * o->z);
        Vec3 t;
        t.x = o->x * inv1;
        t.y = inv1 * o->y;
        t.z = inv1 * o->z;
        Vec3 c;
        c.x = t.z * n.y - t.y * n.z;
        c.y = n.z * t.x - t.z * n.x;
        c.z = t.y * n.x - n.y * t.x;
        float inv2 = 1.0f / sqrtf(c.x * c.x + c.y * c.y + c.z * c.z);
        Vec3 b;
        b.x = inv2 * c.x;
        b.y = c.y * inv2;
        b.z = c.z * inv2;
        float disk[2];
        RandomDiskPoint(disk);
        Vec3 v;
        v.z = t.z * disk[0] + disk[1] * b.z;
        v.y = t.y * disk[0] + disk[1] * b.y;
        v.x = disk[0] * t.x + disk[1] * b.x;
        float inv3 = 1.0f / sqrtf(v.x * v.x + v.y * v.y + v.z * v.z + 1e-08f);
        float speed = def->speed;
        e->state = 0;
        e->vel.x = speed * (inv3 * v.x);
        e->vel.y = (v.y * inv3) * speed;
        e->vel.z = (v.z * inv3) * speed;
        e->radius = sqrtf(p.x * p.x + p.y * p.y + p.z * p.z) + def->radiusOffset;
        e->pos = p;
        e->timer.Start();

        EffectsManager* mgr = GetEffectsManager();
        EffectHandle** slot = &e->effect1;
        if (*slot)
        {
            EffectHandle* old = *slot;
            *slot = 0;
            old->Release();
        }
        if (!mgr->PlayEffect(def->effectId, 0, slot))
        {
            mEntries.PopBack();
        }
        else
        {
            Transform xf;
            xf.mfScale = def->scale;
            xf.mnFlags |= 4;
            xf.mOffset = p;
            xf.mnCount += 2;
            Quat qtmp;
            Quat* q = GetPlanetModel()->BuildSurfaceOrientation(&qtmp, &p);
            Matrix3 mtmp;
            xf.mRotation = *Matrix3FromQuaternion(&mtmp, q);
            xf.mnFlags |= 2;
            xf.mnCount++;
            (*slot)->SetTransform(&xf);
            (*slot)->Stop(0);
        }
    next:;
    }
}

// ---------------------------------------------------------------------------
// cAppModeCreatureAnimViewer helpers (0x00ebd220 / 0x00ebd340).
// ---------------------------------------------------------------------------

#define VPAD(n) virtual void vpad##n()

struct ShaderEntry { uint8_t m_pad[0x54]; };

struct ShaderData
{
    uint8_t m_pad0[0x18];                              // +0x00
    ShaderEntry* m_begin;                              // +0x18
    ShaderEntry* m_end;                                // +0x1c
    void RegisterShaderDataInfo();                     // 0x010414c0
};
ShaderData* FUN_010408b0();                            // 0x010408b0

struct TimerArray
{
    Timer* m_timers;                                   // +0x00
    void EnsureElementCount(int count);                // 0x00bf7760
};

struct cPropertyValue
{
    uint8_t m_pad0[0x12];                              // +0x00
    uint16_t m_type12;                                 // +0x12
    float* GetFloat();                                 // 0x0041ea70
};

struct PropertyOwner
{
    VPAD(0); VPAD(1); VPAD(2); VPAD(3); VPAD(4); VPAD(5); VPAD(6); VPAD(7); VPAD(8);
    virtual bool GetProperty(uint32_t id, cPropertyValue** out);   // +0x24
};

struct GameModeMgr
{
    PropertyOwner* GetPropertyOwner();                 // 0x00b1daf0
};
void* __stdcall FUN_00b3d320(uint32_t mode, int flags); // 0x00b3d320

struct RbNode
{
    uint32_t m_key;                                    // +0x00
    RbNode* m_next;                                    // +0x04
};

struct RbTree
{
    uint32_t m_pad0;                                   // +0x00
    uint32_t m_headKey;                                // +0x04
    RbNode* m_head;                                    // +0x08
    RbNode* m_root;                                    // +0x0c
    uint8_t m_flag;                                    // +0x10
    uint8_t m_pad11[3];                                // +0x11
    uint32_t m_alloc;                                  // +0x14
    void DoNukeSubtree(uint32_t key);                  // 0x009a9600
};
void __cdecl FreeNode(void* node);                     // 0x00f47380

struct cAnimViewer
{
    uint8_t m_pad0[8];                                 // +0x000
    EntryVec mEntries;                                 // +0x008
    uint8_t m_pad10[0xc];                              // +0x010
    TimerArray m_timers1c;                             // +0x01c
    uint8_t m_pad20[0x10];                             // +0x020
    RbTree mTree30;                                    // +0x030
    uint8_t m_pad48[8];                                // +0x048
    uint8_t m_tree50[0x20];                            // +0x050
    void FUN_00ebd220();
    void FUN_00ebd340();
    void FUN_00ebbf60();                               // 0x00ebbf60
};

extern float g_ebd220_0;                               // 0x015a95e8
extern float g_ebd220_1;                               // 0x015a95ec

// @ 0x00ebd220
void cAnimViewer::FUN_00ebd220()
{
    ShaderData* shaderData = FUN_010408b0();
    shaderData->RegisterShaderDataInfo();

    int count = (int)(shaderData->m_end - shaderData->m_begin);
    m_timers1c.EnsureElementCount(count);

    if (count > 0) {
        int offset = 0;
        do {
            Timer* timer = (Timer*)((char*)m_timers1c.m_timers + offset);
            timer->Restart();
            offset += 0x20;
            count--;
        } while (count != 0);
    }

    switch (GetCurrentGameMode()) {
    case 0x1654c05:
        g_ebd220_0 = 0.2f;
        g_ebd220_1 = 0.8f;
        break;

    case 0x1654c10: {
        GameModeMgr* manager = (GameModeMgr*)FUN_00b3d320(0x1654c10, 0);
        PropertyOwner* owner = manager->GetPropertyOwner();
        if (owner != 0) {
            cPropertyValue* value;
            if (owner->GetProperty(0x7a8f88b, &value) &&
                value->m_type12 == 0xd)
                g_ebd220_0 = *value->GetFloat();

            if (owner->GetProperty(0x7a8f88d, &value) &&
                value->m_type12 == 0xd)
                g_ebd220_1 = *value->GetFloat();
        }
        break;
    }
    }
}

// @ 0x00ebd340
void cAnimViewer::FUN_00ebd340()
{
    Entry* entry = mEntries.mpBegin;
    while (entry != mEntries.mpEnd) {
        if (entry->effect1 != 0)
            entry->effect1->Destroy(1);
        if (entry->effect2 != 0)
            entry->effect2->Destroy(1);
        entry += 1;
    }

    Entry* oldBegin = mEntries.mpBegin;
    Entry* oldEnd = mEntries.mpEnd;
    mEntries.DestroyRange(oldBegin, oldEnd);
    mEntries.mpEnd = (Entry*)((char*)mEntries.mpEnd +
                              ((char*)oldEnd - (char*)oldBegin));

    RbTree* tree = &mTree30;
    RbNode* node = tree->m_root;
    while (node != 0) {
        tree->DoNukeSubtree(node->m_key);
        RbNode* next = node->m_next;
        FreeNode(node);
        node = next;
    }

    tree->m_head = (RbNode*)&tree->m_headKey;
    tree->m_headKey = (uint32_t)(uintptr_t)&tree->m_headKey;
    tree->m_root = 0;
    tree->m_flag = 0;
    tree->m_alloc = 0;

    FUN_00ebbf60();
}
