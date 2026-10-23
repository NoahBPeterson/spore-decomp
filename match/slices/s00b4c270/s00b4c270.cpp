// s00b4c270 -- SP::Simulator / cGonzago sim update + event plumbing.
//
// Reconstructed from the disassembly in work/match/scratch_s00b4c270_cards.txt.
// MSVC 2008 SP1, /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-

typedef unsigned int  uint;
typedef unsigned char uchar;

// ---------------------------------------------------------------------------
// external data
// ---------------------------------------------------------------------------
extern float g_13f9428;         // 0x013f9428  per-tick scale (0.001f)
extern float g_13f4fd0;         // 0x013f4fd0  2^32, unsigned -> float fixup
extern float g_1485720;         // 0x01485720  1.0f
extern float g_1470f1c;         // 0x01470f1c  2.0f
extern float g_1569698;         // 0x01569698  force scale
extern float g_167eb8c;         // 0x0167eb8c  zero vector component x
extern float g_167eb90;         // 0x0167eb90  zero vector component y
extern float g_167eb94;         // 0x0167eb94  zero vector component z
extern uchar g_167eb74;         // 0x0167eb74
extern uchar g_167ece0;         // 0x0167ece0
extern int   g_167ecd0;         // 0x0167ecd0
extern void* g_164dc58;         // 0x0164dc58  pointer cell (dereferenced)
extern char  g_15d9c68;         // 0x015d9c68  default target constant address
extern char  g_13ebb38[];       // 0x013ebb38  allocator category string
extern char  g_13f09b4[];       // 0x013f09b4  "Simulator"

struct Iter { void* node; void* bucket; };

struct HT {                     // eastl hashtable header
    char  pad0[4];
    void** arr;                 // +0x04
    uint  count;                // +0x08
    void* f0c;                  // +0x0c

    Iter* find(Iter* out, const void* key);              // 0x00645ed0
    void  freePairs(void* arr, uint n);                  // 0x00961d60
};

// ---------------------------------------------------------------------------
// Every helper below is called as `ecx = receiver; <args>; call` with the callee
// popping the stack, i.e. __thiscall.  Declaring them as member functions of an
// opaque receiver gives MSVC the exact call sequence (a __fastcall declaration
// with a dummy second argument would additionally materialise edx).
// ---------------------------------------------------------------------------
struct Recv {
    void  FUN_00b41c80(void* src);                        //  0x00b41c80
    void  FUN_007611f0(void* arr, uint n);                //  0x007611f0
    void  FUN_00b41e20(void* arr, uint n);                //  0x00b41e20
    void* FUN_00b4b880(const void* key);                  //  0x00b4b880
    void  FUN_00b4c9a0(void* a, void* b, int c);          //  0x00b4c9a0
    void* FUN_00b21340(void* a, void* b, void* c, void* d, void* e);  // 0x00b21340
    void  FUN_00c01350(void* o);                          //  0x00c01350
    void  FUN_00c015e0(void* o);                          //  0x00c015e0
    void  FUN_00b57c40(uint param);                       //  0x00b57c40  SP::cGonzagoPhysics::UpdateHavok
    void  FUN_00b41390(void* obj);                        //  0x00b41390
    void  FUN_00b470b0(void* p);                          //  0x00b470b0
    void  FUN_00b45ca0(float dt);                         //  0x00b45ca0
    void* FUN_00b72230(void* it);                         //  0x00b72230
    void* FUN_00b815a0(void* out, void* in);              //  0x00b815a0  SP::cPlanetModel::DirectionToSurfacePosition
    void* FUN_00b6ff20(void* a, void* b);                 //  0x00b6ff20
};

// ---------------------------------------------------------------------------
// external functions
// ---------------------------------------------------------------------------
extern void* __cdecl FUN_01021260();                    // SP::cSPLivingUniverse::GetActivePlanet
extern void* __cdecl FUN_01021080();                    // SP::cSPLivingUniverse::GetUniverseContext
extern void* __cdecl FUN_01049a10();
extern float __fastcall FUN_01049c40(void* self);       // SP::cTerraformTuning::GetIceThreshold
extern float __fastcall FUN_00c70a20(void* self);
extern void  __cdecl FUN_00db90c0(float dt);
extern void  __cdecl FUN_00b54b80();
extern void  __fastcall FUN_00b48920(void* self);
extern void  __stdcall FUN_00b4a720(void* obj, uint param, uchar b30, int flag);
extern void  __cdecl FUN_00b47ee0(void* o);
extern void  __cdecl FUN_00b4c0e0(float dt);
extern void  __cdecl FUN_00b4b4a0();
extern void  __cdecl FUN_00b46d10(float dt);
extern void  __cdecl FUN_00b48ea0(float dt);
extern void* __fastcall FUN_00e31100(void* self);       // UTFWin::IWinProc::GetPriority
extern void* __fastcall FUN_00c41ec0(void* self);
extern void  __cdecl FUN_00b3dbb0(void* e);
extern void  __stdcall FUN_00b4b590(void* p);
extern void  __cdecl FUN_00b41020();
extern void  __cdecl FUN_00b4fd80(void* obj);
extern void* __fastcall FUN_0067de30();                 // SP::PropertyManager
extern void* __fastcall FUN_00b3d350();                 // SP::PlanetModel
extern void* __fastcall FUN_00b3d300();                 // SP::NounManager
extern void* __fastcall FUN_00d20610(void* self);       // SP::cLocomotiveObject::GetVelocity
extern uint  __cdecl FUN_00b3d700(uint a, uint b);
extern void  __cdecl FUN_00b57bf0(uint a, uint b, float c);
extern int   __cdecl FUN_00ac9310(void* a, void* b, char flag);
extern void  __fastcall FUN_00b515e0(void* self);
extern int   __cdecl FUN_00c0c2f0(void* t);
extern void  __cdecl FUN_00b48f20(void* a, float f);
extern int   __cdecl FUN_004e1c30(void* obj, uint id, int z);   // SP::cTribeTool::GetTutorialToolPrice
extern void  __fastcall FUN_004535d0(void* self);
extern void  __cdecl FUN_00b4d8c0();
extern void  __fastcall FUN_00b720e0(void* self);
extern void  __cdecl FUN_00bbb100(void* p);
extern void  __cdecl FUN_00b45170(void* p);
extern void  __fastcall FUN_00b5b9a0(void* self);
extern void  __fastcall FUN_00ad92d0(void* self);
extern void  __cdecl FUN_00f47380(void* p);             // operator delete[]
extern void* __cdecl FUN_00f473a0(uint sz, const char* cat, int a, int b, const char* c, int d);
extern void  __cdecl FUN_00b41b30(void* out, const void* key);

struct RefObj {
    virtual void  AddRef();     // slot 0 == byte offset 0x00
    virtual void  Release();    // slot 1 == byte offset 0x04
};

// A raw view of any object header whose vtable we index by byte offset.  The
// original code is a virtual call; the emitted sequence is identical.
struct IVtbl { void* slot[0x40]; };
#define VFN(obj, off) (((IVtbl*)*(void**)(obj))->slot[(off) / 4])

// The vcall at byte offset 0xb8 takes a task/message id and is used to obtain a
// secondary "brain" object; the one at 0x2c on a +0xc0 subobject yields a
// pointer, the one at 0x48 yields a fill of a caller-provided 8-byte buffer.
struct VObj24 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual char  v24(uint id, void** out);        // +0x24
};
struct VObj1C {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual char  v1c(uint id);                    // +0x1c
};
struct VSubC0 {
    virtual void  v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void  v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void  v20(); virtual void v24(); virtual void v28();
    virtual void* v2c();                           // +0x2c
};
struct VObjB8 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual void* vb8(uint id);                    // +0xb8
};
struct VSub34 {
    virtual void  v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void  v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void  v20(); virtual void v24(); virtual void v28();
    virtual void* v2c();                           // +0x2c
    virtual void  v30();
    virtual float v34();                           // +0x34
};
struct VSub34b {
    virtual void  v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void  v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void  v20(); virtual void v24(); virtual void v28();
    virtual void  v2c(); virtual void v30();
    virtual float v34(int a, float f);             // +0x34
};
struct VObj48 {
    virtual void  v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void  v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void  v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void  v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void  v40(); virtual void v44();
    virtual void* v48();                           // +0x48
};

// Property-manager object: slot 0x2c looks a value up by key, slot 0x48 fills a
// caller-provided vector header.
struct VObjPM {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual char v2c(uint a, uint b, void** out);  // +0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44();
    virtual void v48(uint key, void** out);        // +0x48
};

typedef void* (__fastcall* FnV0)(void* self, int edx);
typedef void* (__fastcall* FnV1)(void* self, int edx, uint a);
typedef char  (__fastcall* FnC0)(void* self, int edx);
typedef char  (__fastcall* FnC1)(void* self, int edx, uint a);
typedef char  (__fastcall* FnC1P)(void* self, int edx, uint a, void** out);
typedef char  (__fastcall* FnC2P)(void* self, int edx, uint a, void** out);
typedef char  (__fastcall* FnC3P)(void* self, int edx, uint a, uint b, void** out);
typedef float (__fastcall* FnF0)(void* self, int edx);
typedef float (__fastcall* FnF1I)(void* self, int edx, int a, float f);

// ---------------------------------------------------------------------------
// the world object behind *(void**)0x0167eb70
// ---------------------------------------------------------------------------
struct World70 {
    int    f0;                  // +0x00  tick counter
    void*  f4;                  // +0x04
    char   pad8[0x34];
    char   iter3c[0x1c];        // +0x3c  container walked by 0x00e31100 / 0x00b72230
    HT     ht58;                // +0x58
    char   pad68[0x10];
    HT     ht78;                // +0x78
};
extern World70* g_167eb70;      // 0x0167eb70

// The Simulator object these entry points operate on.
struct Sim {
    void  tick(uint param);                             // 0x00b4c270
    void  fwd(int unused, uint n);                      // 0x00b4c5e0
    void  cmd(uint key1, uint key2, float f);           // 0x00b4c600
    void* alloc(void* src);                             // 0x00b4c6d0
    void  cbf0(void* obj, int mode);                    // 0x00b4cbf0
    void* caf0(const void* key);                        // 0x00b4caf0
    void  ce30(void* obj);                              // 0x00b4ce30
    void  d140();                                       // 0x00b4d140
};

// ===========================================================================
// 0x00b4c270 -- Simulator tick driver.
// ===========================================================================
// @ 0x00b4c270
void Sim::tick(uint param)
{
    char* s = (char*)this;
    float dt = (float)param * g_13f9428;

    if (FUN_01021260() != 0) {
        float v = FUN_00c70a20((void*)FUN_01021260());
        float ice = FUN_01049c40((void*)FUN_01049a10());
        g_167eb74 = 1;
        if (ice <= v) g_167eb74 = 0;
    }

    if (*(int*)(s + 0x20) == 0 && g_167ecd0 != 0) FUN_00b54b80();

    if (*(char*)(s + 0x24) == 0) return;

    FUN_00db90c0(dt);

    switch (*(uint*)(s + 0x20)) {
    case 0:
        if (g_167ecd0 != 0) ((Recv*)this)->FUN_00b57c40(param);
        break;

    case 1: {
        World70* w = g_167eb70;
        ++w->f0;

        // 1. every live object that is not yet registered in ht58 gets added.
        {
            uint* it  = *(uint**)(s + 0x60);
            uint* end = *(uint**)(s + 0x64);
            for (; it != end; ++it) {
                void* o = (void*)*it;
                if (o != 0 && *(char*)((char*)o + 0x75) != 0) {
                    Iter r;
                    uint key = (uint)o;
                    w->ht58.find(&r, &key);
                    if (r.node == w->ht58.arr[w->ht58.count])
                        FUN_00b4a720(o, param, *(uchar*)(s + 0x30), 1);
                }
            }
        }

        // 2. sweep the +0x480 hashtable; flagged entries are retired once.
        {
            void**  base   = *(void***)(s + 0x480);
            char*   it     = (char*)base[0];
            void**  bucket = base;
            if (it == 0) { ++bucket; while (*bucket == 0) ++bucket; it = (char*)*bucket; }
            char* end = (char*)base[*(uint*)(s + 0x484)];
            for (; it != end; ) {
                char* o = *(char**)it;
                uint  flags = *(uint*)(o + 0x50);
                if ((flags & 1) && ((flags & 0x10) == 0 || (flags & 0x20) != 0)) {
                    FUN_00b47ee0(o);
                    *(uint*)(o + 0x50) &= ~1u;
                }
                it = *(char**)(it + 4);
                if (it == 0) { do { ++bucket; it = (char*)*bucket; } while (it == 0); }
            }
        }

        // 3. same retirement pass over the object vector.
        {
            uint* it  = *(uint**)(s + 0x60);
            uint* end = *(uint**)(s + 0x64);
            for (; it != end; ++it) {
                char* o = (char*)*it;
                uint  flags = *(uint*)(o + 0x50);
                if ((flags & 1) && ((flags & 0x10) == 0 || (flags & 0x20) != 0))
                    FUN_00b47ee0(o);
            }
        }

        // 4. the +0x3c container: drive every matching entry.
        {
            Recv*  ctr = (Recv*)((char*)g_167eb70 + 0x3c);
            uint   it[2];
            it[0] = (uint)FUN_00e31100(ctr);
            for (void* e = ctr->FUN_00b72230(it); e != 0; e = ctr->FUN_00b72230(it)) {
                char* pe = (char*)e;
                int   kind = *(int*)(pe + 4);
                int   ok;
                if (kind == 0 || kind == 1) {
                    char* o = *(char**)(pe + 0x40);
                    ok = *(char*)(o + 0x75) != 0 &&
                         (*(char*)(o + 0x70) != 0 || *(char*)(pe + 0x35) != 0);
                } else {
                    ok = (kind == 2);
                }
                if (ok == 0) continue;

                if (kind != 0) {
                    FUN_00b3dbb0(e);
                    ((Recv*)e)->FUN_00b45ca0(dt);
                    continue;
                }

                char* o = *(char**)(pe + 0x40);
                uchar b;
                void* t;
                if (o != 0 && (t = ((VObjB8*)o)->vb8(0xce9f6639)) != 0) {
                    if (*(char*)((char*)t + 0xf90) == 0) b = 1;
                    else                                  b = (FUN_00c0c2f0(t) == 0);
                } else {
                    b = (((VObj48*)o)->v48() == 0);
                }
                FUN_00b4a720(o, param, *(uchar*)(s + 0x30), (int)b);
                FUN_00b3dbb0(e);
                if (b == 0) ((Recv*)e)->FUN_00b45ca0(dt);
            }
        }

        FUN_00b4c0e0(dt);
        FUN_00b4b4a0();
        FUN_00b46d10(dt);
        FUN_00b48ea0(dt);
        break;
    }

    default: {
        uint* it  = *(uint**)(s + 0x60);
        uint* end = *(uint**)(s + 0x64);
        for (; it != end; ++it) {
            void* o = (void*)*it;
            if (o != 0 && *(char*)((char*)o + 0x75) != 0)
                FUN_00b4a720(o, param, *(uchar*)(s + 0x30), 1);
        }
        break;
    }
    }

    if (FUN_01021080() == 0) FUN_00b48920(this);
}

// ===========================================================================
// 0x00b4c5e0 -- two-argument adapter: forwards a count to the tick driver one
//               word below the object.
// ===========================================================================
// @ 0x00b4c5e0
void Sim::fwd(int /*unused*/, uint n)
{
    if (n > 0) ((Sim*)((char*)this - 4))->tick(n);
}

// ===========================================================================
// 0x00b4c600 -- Simulator command: (key1, key2, float value).
// ===========================================================================
// @ 0x00b4c600
void Sim::cmd(uint key1, uint key2, float f)
{
    char* s = (char*)this;

    if (*(int*)(s + 0x20) == 0) {
        FUN_00b57bf0(key1, key2, f);
        return;
    }
    if (*(int*)(s + 0x20) != 1) return;

    World70* w = g_167eb70;
    Iter i1, i2;
    w->ht58.find(&i1, &key1);
    w->ht58.find(&i2, &key2);
    if (i1.node == w->ht58.arr[w->ht58.count]) return;
    if (i2.node == w->ht58.arr[w->ht58.count]) return;

    key2 = FUN_00b3d700(*(uint*)(*(uint*)((char*)i1.node + 4)),
                        *(uint*)(*(uint*)((char*)i2.node + 4)));
    *(float*)((Recv*)&w->ht78)->FUN_00b4b880(&key2) = *(float*)&key2;
}

// ===========================================================================
// 0x00b4c6d0 -- allocate + copy a 0x2c-byte sim node.
// ===========================================================================
// @ 0x00b4c6d0
void* __stdcall FUN_00b4c6d0(void* src)
{
    char* node = (char*)FUN_00f473a0(0x2c, g_13f09b4, 0, 0, g_13ebb38, 0xd1);
    if (node != 0) {
        *(uint*)(node + 0)  = *(uint*)((char*)src + 0);
        void* p = *(void**)((char*)src + 4);
        *(void**)(node + 4) = p;
        if (p != 0) ((RefObj*)p)->AddRef();
        ((Recv*)(node + 8))->FUN_00b41c80((char*)src + 8);
    }
    *(uint*)(node + 0x28) = 0;
    return node;
}

// ===========================================================================
// 0x00b4c730 -- tell the Avoider collection about this object.
// ===========================================================================
// @ 0x00b4c730
void __cdecl FUN_00b4c730(void* obj)
{
    char* o = (char*)obj;
    void* t = *(void**)(o + 0x80);
    void* h;
    if (t != 0)
        h = ((VObjB8*)t)->vb8(0xce9f6639);
    else
        h = 0;

    void* nm  = FUN_00b3d300();
    void* vec = ((Recv*)nm)->FUN_00b21340((void*)0x00cd7d10, (void*)0x00d3d420,
                                          (void*)0x00acdff0, (void*)0x00b1e500, (void*)0x018c43e8);
    void* sub = (char*)h + 0xc0;
    void* p   = ((VSubC0*)sub)->v2c();
    char  flag = 0;
    char  fl   = flag;
    int   r   = FUN_00ac9310((char*)vec + 4, p, fl);
    if (r != 0) ((Recv*)r)->FUN_00c01350(obj);
}

// ===========================================================================
// 0x00b4c7c0 -- identical to 0x00b4c730 but for the Avoider::Avoid entry.
// ===========================================================================
// @ 0x00b4c7c0
void __cdecl FUN_00b4c7c0(void* obj)
{
    char* o = (char*)obj;
    void* t = *(void**)(o + 0x80);
    void* h;
    if (t != 0)
        h = ((VObjB8*)t)->vb8(0xce9f6639);
    else
        h = 0;

    void* nm  = FUN_00b3d300();
    void* vec = ((Recv*)nm)->FUN_00b21340((void*)0x00cd7d10, (void*)0x00d3d420,
                                          (void*)0x00acdff0, (void*)0x00b1e500, (void*)0x018c43e8);
    void* sub = (char*)h + 0xc0;
    void* p   = ((VSubC0*)sub)->v2c();
    char  flag = 0;
    char  fl   = flag;
    int   r   = FUN_00ac9310((char*)vec + 4, p, fl);
    if (r != 0) ((Recv*)r)->FUN_00c015e0(obj);
}

// ===========================================================================
// 0x00b4c850 -- moving objects push their neighbours away from each other.
// ===========================================================================
// @ 0x00b4c850
void __cdecl FUN_00b4c850(void* obj, void* arg2)
{
    char* o = (char*)obj;

    if (*(void**)(o + 0x80) == 0) return;
    void* t = ((VObjB8*) * (void**)(o + 0x80))->vb8(0xb033b403);
    if (t == 0) return;

    float* vel = (float*)FUN_00d20610(*(void**)(o + 0x80));
    if (vel[0] == g_167eb8c && vel[1] == g_167eb90 && vel[2] == g_167eb94)
        return;

    void* nm  = FUN_00b3d300();
    void* vec = ((Recv*)nm)->FUN_00b21340((void*)0x00cd7d10, (void*)0x00d3d420,
                                          (void*)0x00ad48b0, (void*)0x00b1e500, (void*)0x018ebadc);

    void** arr = (void**)((char*)vec + 4);
    int    n   = (int)((*(int*)((char*)vec + 8) - *(int*)((char*)vec + 4)) >> 2);

    for (int i = 0; i < n; ++i) {
        char* e = (char*)arr[i];
        if (e == 0 || e == (char*)t) continue;
        if (*(char*)(e + 0xa4) == 0) continue;
        if (*(char*)(e + 0xa9) == 0) continue;
        if ((*(uchar*)(e + 0x84) & 0x10) != 0) continue;

        char* subA = e + 0x34;
        int   a    = (int)((VSub34*)subA)->v2c();
        float f1   = ((VSub34*)subA)->v34() * g_1569698;

        char* subB = (char*)t + 0x34;
        float f2   = ((VSub34b*)subB)->v34(a, f1) * g_1569698;

        FUN_00b48f20(arg2, f2);
    }
}

// ===========================================================================
// 0x00b4ca60 -- free an array of intrusive list nodes.
// ===========================================================================
// @ 0x00b4ca60
void __fastcall FUN_00b4ca60(void* /*self*/, int /*edx*/, void** arr, uint n)
{
    for (uint i = 0; i < n; ++i) {
        char* next = (char*)arr[i];
        while (next != 0) {
            char* node = next;
            next = *(char**)(node + 0x28);
            HT*   ht   = (HT*)(node + 8);
            ht->freePairs(ht->arr, ht->count);
            ht->f0c = 0;
            if (ht->count > 1) FUN_00f47380(ht->arr);
            void* r = *(void**)(node + 4);
            if (r != 0) ((RefObj*)r)->Release();
            FUN_00f47380(node);
        }
        arr[i] = 0;
    }
}

// ===========================================================================
// 0x00b4caf0 -- hashtable insert-or-find; returns a pointer to the value slot.
// ===========================================================================
// @ 0x00b4caf0
void* Sim::caf0(const void* key)
{
    Iter it;
    FUN_00b41b30(&it, key);

    HT* ht = (HT*)this;
    if (it.node != ht->arr[ht->count]) return (char*)it.node + 4;

    // The value record stored for a new key: a 0x38-byte record whose last
    // member is the eastl hashtable of pending tool strategies.
    struct NodeVal {
        uint  f00;                      // +0x00
        uint  pad04[1];
        void* f08;                      // +0x08  0x0154df28
        uint  f0c;                      // +0x0c  1
        float f10;                      // +0x10  1.0f
        uint  pad14[1];
        float f18;                      // +0x18  2.0f
        uint  f1c;                      // +0x1c  0
        uint  pad20[1];
        uint  f24;                      // +0x24  key
        uint  f28;                      // +0x28  0
        char  ht[0x0c];                 // +0x2c  embedded hashtable header
    };
    NodeVal v;
    v.f00 = 0;
    v.f08 = (void*)0x0154df28;
    v.f0c = 1;
    v.f10 = g_1485720;
    v.f18 = g_1470f1c;
    v.f1c = 0;
    v.f24 = *(uint*)key;
    v.f28 = 0;
    ((Recv*)v.ht)->FUN_00b41c80(&v);

    Iter dummy;
    ((Recv*)this)->FUN_00b4c9a0(&dummy, &v, (int)((uint)key & 0xffffff00));

    HT*   nht = (HT*)((char*)it.node + 8);
    nht->freePairs(nht->arr, nht->count);
    nht->f0c = 0;
    if (nht->count > 1) FUN_00f47380(nht->arr);
    ((HT*)v.ht)->freePairs((void*)0x0154df28, 1);
    return (char*)it.node + 4;
}

// ===========================================================================
// 0x00b4cbf0 -- Simulator command dispatching on the target object's kind.
// ===========================================================================
// @ 0x00b4cbf0
void Sim::cbf0(void* obj, int mode)
{
    void* target = 0;
    if (obj != 0) {
        void* p;
        if (((VObj24*)obj)->v24(0x100e7b1c, &p)) {
            uint k = (unsigned short)*(unsigned short*)((char*)p + 0x12);
            if (k == 10 || k == 0x10) {
                if ((*(uchar*)((char*)p + 0x10) & 0x30) != 0) target = *(void**)p;
                else target = (void*)((uint)(-(int)k) & (uint)p);
            } else {
                target = g_164dc58;
            }
        }
    }
    if (target == 0) return;

    char* node = (char*)((Sim*)((char*)this + 0x14c8))->caf0(&target);

    if (mode == 1) { FUN_004535d0(node); return; }
    if (mode != 3) return;

    if (!((VObj1C*)obj)->v1c(0x2e8a5149)) return;

    int price = FUN_004e1c30(obj, 0x2e8a5149, 0);
    FUN_004535d0(((Recv*)(node + 4))->FUN_00b6ff20(&price, obj));
}

// ===========================================================================
// 0x00b4ccc0 -- destructor of the Simulator subsystem.
// ===========================================================================
// @ 0x00b4ccc0
void __fastcall FUN_00b4ccc0(void* self)
{
    char* s = (char*)self;

    *(uint*)(s + 0) = 0x1461230;
    *(uint*)(s + 4) = 0x14611e0;
    *(uint*)(s + 8) = 0x14611dc;

    FUN_00b4d8c0();

    if (g_167eb70 != 0) {
        World70* w = g_167eb70;
        FUN_00b720e0((char*)w + 0x3c);
        FUN_00b720e0((char*)w + 8);
        FUN_00bbb100(*(void**)((char*)g_167eb70 + 4));
        w = g_167eb70;
        if (w != 0) {
            FUN_00b45170(w);
            FUN_00f47380(w);
        }
        g_167eb70 = 0;
    }

    // hashtable at +0x14c8
    {
        HT* ht = (HT*)(s + 0x14c8);
        FUN_00b4ca60(ht, 0, ht->arr, ht->count);
        ht->f0c = 0;
        if (ht->count > 1) FUN_00f47380(ht->arr);
    }

    // hashtable at +0x47c
    {
        char* h = s + 0x47c;
        ((Recv*)h)->FUN_00b41e20(*(void**)(h + 4), *(uint*)(h + 8));
        void* p = *(void**)(h + 4);
        *(uint*)(h + 0xc) = 0;
        if (*(uint*)(h + 8) > 1 && p != *(void**)(h + 0x30)) {
            if (p < *(void**)(h + 0x24) || p >= *(void**)(h + 0x28)) {
                FUN_00f47380(p);
            } else {
                *(void**)p = *(void**)(h + 0x1c);
                *(void**)(h + 0x1c) = p;
            }
        }
    }

    FUN_00ad92d0(s + 0x60);             // ~eastl::vector

    // hashtable at +0x40
    {
        char* h = s + 0x40;
        ((Recv*)h)->FUN_007611f0(*(void**)(h + 4), *(uint*)(h + 8));
        *(uint*)(h + 0xc) = 0;
        if (*(uint*)(h + 8) > 1) FUN_00f47380(*(void**)(h + 4));
    }

    FUN_00b5b9a0(s + 4);                // ~SP::cGonzagoSubsystem

    *(uint*)(s + 0) = 0x13eb394;
}

// ===========================================================================
// 0x00b4ce30 -- forward a message to the target object according to its kind.
// ===========================================================================
// @ 0x00b4ce30
void Sim::ce30(void* obj)
{
    uint v;
    if (obj != 0) {
        void* p;
        if (!((VObj24*)obj)->v24(0xa55a5cee, &p)) {
            v = 1;
        } else {
            uint k = (unsigned short)*(unsigned short*)((char*)p + 0x12);
            if (k == 9 || k == 0x10) {
                if ((*(uchar*)((char*)p + 0x10) & 0x30) != 0) p = *(void**)p;
                else p = (void*)((uint)(-(int)k) & (uint)p);
            } else {
                p = &g_15d9c68;
            }
            v = *(uint*)p;
            if (v > 3) return;
        }
    } else {
        v = 1;
    }

    switch (v) {
    case 0:
        ((Recv*)this)->FUN_00b41390(obj);
        break;
    case 1:
        cbf0(obj, 1);
        break;
    case 2:
        FUN_00b4fd80(obj);
        break;
    case 3:
        cbf0(obj, 3);
        break;
    }
}

// ===========================================================================
// 0x00b4cee0 -- Simulator incoming-message handler.
//    __thiscall(this, unsigned int message, void* payload) -> bool
// ===========================================================================
// @ 0x00b4cee0
uchar __fastcall FUN_00b4cee0(void* self, int /*edx*/, uint msg, char* data)
{
    if (msg <= 0x1a0219e) {
        if (msg == 0x1a0219e) {
            void* p = *(void**)(data + 0x10);
            if (*(int*)(data + 8) == 3) FUN_00b4b590(p);
            if (*(int*)(data + 8) == 4) ((Recv*)self)->FUN_00b470b0(p);
        } else if (msg == 0xf62def) {
            uint key = *(uint*)(data + 0x10);
            uint val = *(uint*)(data + 0x18);
            if (key == 0x2a8cb47) {
                void* ref = 0;
                void* pmgr = FUN_0067de30();
                if (((FnC3P)VFN(pmgr, 0x2c))(pmgr, 0, val, 0x2a8cb47, &ref) != 0)
                    ((Sim*)self)->ce30(ref);
                if (ref != 0) {
                    void* r = ref;
                    ref = 0;
                    ((RefObj*)r)->Release();
                }
            } else if (key == 0 && val == 0x93e8e9b7) {
                FUN_00b41020();
            }
        } else if (msg == 0x182c582) {
            void* planet = FUN_00b3d350();
            if (planet != 0 && *(void**)((char*)planet + 0x24) != 0) {
                float* d = (float*)data;
                float x = d[2];
                float y = d[4];
                float z = d[6];
                if (!(g_13f9428 > x * x + z * z + y * y)) {
                    float dir[3];
                    float pos[3];
                    dir[0] = x;
                    dir[1] = y;
                    dir[2] = z;
                    ((Recv*)planet)->FUN_00b815a0(pos, dir);

                    float r2 = d[8] * d[8];
                    FUN_00b515e0(self);

                    uint* it  = *(uint**)((char*)self + 0x60);
                    uint* end = *(uint**)((char*)self + 0x64);
                    for (; it != end; ++it) {
                        char* o = (char*)FUN_00c41ec0((void*)*it);
                        if (*(int*)(o + 0x5c) != 0) {
                            float dx = *(float*)(o + 0x14) - pos[0];
                            float dy = *(float*)(o + 0x18) - pos[1];
                            float dz = *(float*)(o + 0x1c) - pos[2];
                            if (r2 > dx * dx + dy * dy + dz * dz) {
                                float tmp[3];
                                ((Recv*)planet)->FUN_00b815a0(tmp, o + 0x14);
                                *(float*)(o + 0x14) = tmp[0];
                                *(float*)(o + 0x18) = tmp[1];
                                *(float*)(o + 0x1c) = tmp[2];
                            }
                        }
                    }
                }
            }
        }
    } else if (msg == 0x25630b7 || msg == 0x31018b9) {
        g_167ece0 = 1;
    }
    return 0;
}

// ===========================================================================
// 0x00b4d140 -- flush every pending entry of the property manager's live list.
// ===========================================================================
// @ 0x00b4d140
void Sim::d140()
{
    char* s = (char*)this;

    if (*(int*)(s + 0x14d4) != 0) return;

    void* pmgr = FUN_0067de30();

    void* ref = 0;
    void* vec[3];
    vec[0] = 0; vec[1] = 0; vec[2] = 0;

    void* pm2 = FUN_0067de30();
    ((VObjPM*)pm2)->v48(0x2a8cb47, vec);                     // fills vec[0]/vec[1]

    for (uint* it = (uint*)vec[0], *last = (uint*)vec[1]; it != last; ++it) {
        void* elem = (void*)*it;
        void* in = ref;
        if (in != 0) {
            ref = 0;
            ((RefObj*)in)->Release();
        }
        if (((VObjPM*)pmgr)->v2c((uint)elem, 0x2a8cb47, &ref))
            ce30(ref);
    }

    void* hdr = vec[1];
    if (hdr != 0 && *(int*)((char*)hdr - 4) != 0) FUN_00f47380(hdr);
    if (ref != 0) ((RefObj*)ref)->Release();
}
