// Model animation/effect preload: spreads work over frames under a time budget.
#include "types.h"
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t*);
struct Item { char d[0x8c]; };
struct ItemVec { Item* begin; Item* end; int size() const { return (int)(end - begin); } };
struct ModelData { uint32_t pad[0x26]; ItemVec items; uint32_t pad2[0x12]; float* weights; };
struct Owner { uint32_t pad[2]; ModelData* data; ModelData* GetData() { return data; } uint32_t pad2[0x21]; uint32_t f90; };
struct SlotA { uint32_t p[5]; void __thiscall Reserve(int n); };
struct SlotB { uint32_t p[5]; void __thiscall Assign(uint32_t* src); };
struct SlotC { uint32_t p[5]; void __thiscall Reserve(int n); };
struct SlotD { uint32_t p[5]; void __thiscall Reserve(int n); };
struct SlotE { uint32_t p[5]; void __thiscall Reserve(int n); };
struct Task;
struct Request { uint32_t pad[7]; uint32_t f1c; void __thiscall Dispatch(Task* t); };
struct Task {
    uint32_t pad[9];
    Owner* owner;
    uint32_t pad2;
    uint32_t f2c;
    SlotA a; SlotB b; SlotC c; SlotC c2; SlotA a2; SlotD d; SlotE e;
    void __thiscall Prepare(Request* req);
};

// ---- 0x00419000: incremental loader ----
struct TimeBudget {
    uint32_t pad[6];
    int64_t deadline;                      // +0x18
    void __thiscall Init(int ms, int flag);   // 0x0093A560
    void __thiscall Arm(int a, int b);        // 0x0093A480
};
struct Transform { uint32_t pad[0x17]; void __thiscall Construct(); };   // 0x5C bytes with 4-byte header
struct SceneObj { uint32_t pad0; uint32_t state; uint16_t flags; uint16_t refCount; uint32_t f0c[3]; uint32_t f18; uint32_t f1c[9]; int refs; };
struct Engine {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual SceneObj* Lookup(uint32_t a, uint32_t b, int c);          // +0x0C
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22();
    virtual void Prepare(SceneObj* o);                                 // +0x58
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32();
    virtual void v33(); virtual void v34(); virtual void v35();
    virtual void SetA(SceneObj* o, int idx, float v, int z, int w);    // +0x70
    virtual void SetB(SceneObj* o, int idx, float v, int z);           // +0x74
    virtual void SetC(SceneObj* o, int idx, float v, int z);           // +0x78
    virtual void v40();
    virtual char Query(SceneObj* o, int idx, float* lo, float* hi, int z); // +0x80
    virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
    virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53();
    virtual void v54(); virtual void v55(); virtual void v56(); virtual void v57();
    virtual int Enumerate(SceneObj* o, Transform* out, int max);       // +0xE8
};
Engine* GetEngine();                                  // 0x00401010
void __fastcall ReleaseObj(SceneObj*);               // 0x0040f360 (thiscall)
void __fastcall PollLoader(void* self);              // 0x0041e6a0 (thiscall)
struct Finisher { char __thiscall Done(void* task); };   // 0x00422a30
extern uint32_t g_DefaultKey;                         // 0x015d126c
struct LoadTask {
    uint32_t pad[9];
    Owner* owner;          // +0x24
    uint32_t pad2[0x0a];
    SceneObj** objs;       // +0xBC
    SceneObj** objsEnd;    // +0xC0
    char Run(Finisher* fin);
};
// @ 0x00419000
char LoadTask::Run(Finisher* fin)
{
    Engine* eng = GetEngine();
    ModelData* md = owner->data;
    int count = md->items.size();
    TimeBudget budget;
    budget.Init(4, 0);
    budget.Arm(1, 1);
    for (int i = (int)(objsEnd - objs); i < count; ++i) {
        int64_t now;
        QueryPerformanceCounter(&now);
        if (budget.deadline - now < 0)
            return fin->Done(this);
        PollLoader(&objs);
        char* it = (char*)md->items.begin + i * 0x8c;
        if (*(uint16_t*)(it + 8) & 1) continue;
        SceneObj* o = eng->Lookup(*(uint32_t*)(it + 0x88), *(uint32_t*)(it + 0x84), 6);
        if (!o) o = eng->Lookup(0x4f5f8ce, g_DefaultKey, 6);
        if (!o) continue;
        SceneObj*& slot = objs[i];
        if (o != slot) {
            SceneObj* old = slot;
            if (o) o->refs++;
            slot = o;
            if (old) ReleaseObj(old);
        }
        o->f18 = *(uint32_t*)(it + 0x2c);
        o->refCount++;
        for (int k = 0; k < 9; ++k) o->f1c[k] = ((uint32_t*)(it + 0x30))[k];
        o->flags |= 2; o->refCount++;
        o->f0c[0] = *(uint32_t*)(it + 0x54); o->f0c[1] = *(uint32_t*)(it + 0x58); o->f0c[2] = *(uint32_t*)(it + 0x5c);
        o->flags |= 4; o->refCount++;
        if (!(o->state & 0x4000)) eng->Prepare(o);
        Transform xf[0x20];
        for (int k = 0; k < 0x20; ++k) xf[k].Construct();
        int n = eng->Enumerate(o, xf, 0x20);
        int lim = it[0x11];
        if (n < lim) lim = n;
        for (int j = 0; j < lim; ++j) {
            float lo = 0.0f, hi = 1.0f;
            if (eng->Query(o, ((int*)&xf[j])[0], &lo, &hi, 0)) {
                float v = lo + (hi - lo) * owner->data->weights[*(uint16_t*)(it + 0xe) + j];
                eng->SetA(o, ((int*)&xf[j])[0], 0, 3, 0);
                eng->SetB(o, ((int*)&xf[j])[0], v, 0);
                eng->SetC(o, ((int*)&xf[j])[0], 1.0f, 0);
            }
        }
    }
    return 1;
}

// @ 0x00419690
void __thiscall Task::Prepare(Request* req)
{
    f2c = 0;
    Owner* o = owner;
    SlotA* s = &a;
    ModelData* md = o->GetData();
    ItemVec* v = &md->items;
    int count = v->size();
    s->Reserve(count);
    b.Assign(&o->f90);
    c.Reserve(count);
    c2.Reserve(count);
    a2.Reserve(count);
    d.Reserve(count);
    e.Reserve(count);
    req->f1c = 0;
    req->Dispatch(this);
}
