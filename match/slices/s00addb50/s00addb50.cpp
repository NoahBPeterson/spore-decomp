// s00addb50 -- EA Simulator ArgScript / config-manager cluster:
//   cConfigManager::ParseConfigFile, the eastl-hashtable reset/erase helpers,
//   the cStringContext / camera-override map accessors, an eastl vector push,
//   the anonymous-namespace cMetaParticleForceCommand::Execute, and the
//   destructor of the simulator object at the end of the region.

typedef unsigned int u32;

// ------------------------------------------------------------------ thiscall vtable thunks
typedef void  (__thiscall *TC_v0)(void*);
typedef char  (__thiscall *TC_c0)(void*);
typedef void* (__thiscall *TC_p0)(void*);
typedef float (__thiscall *TC_f0)(void*);
typedef void  (__thiscall *TC_ii)(void*, int, int);
typedef void  (__thiscall *TC_pv)(void*, void*);
typedef void* (__thiscall *TC_ps)(void*, const char*);
typedef float (__thiscall *TC_fs)(void*, const char*);
typedef void* (__thiscall *TC_vps)(void*, void* out, const char* s);
typedef void  (__thiscall *TC_v4)(void*, unsigned int, unsigned int, void*, int);
typedef void* (__thiscall *TC_pii)(void*, int, int);

#define VFN(obj, off, T) ((T)(*(void***)(obj))[((off) >> 2)])

void* operator new(unsigned int size, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
extern void __cdecl operator_delete(void* p);                 // 0xf47380

extern unsigned int __cdecl FNV1_String8(const char* s, unsigned int seed, int flag);  // 0x932e80

// ---- ArgScript argument parser --------------------------------------------------
struct cArguments {
    const char** MainArguments(int n);                             // 0x838320
    const char** OptionArguments(const char* name, int n);         // 0x838330
    const char** OptionArguments(const char* name, int* count, int min, int max);  // 0x838130
    bool HasFlag(const char* name);                                // 0x8380b0
};

// cAppState::AddMessage(cArguments*, RefObj*, char) -- __thiscall.
struct cAppState {
    void AddMessage(cArguments* args, void* refobj, char flag);    // 0x7e4190
};

// ---- eastl hashtable (bucket array at +4, count at +8) --------------------------
struct Iter { void* node; void* bucket; };

struct HTbl {                                              // eastl hashtable
    char pad0[4];                                          // +0
    unsigned int* arr;                                     // +4  bucket array
    unsigned int  count;                                   // +8  bucket count
    Iter* Find(Iter* out, const void* key);                // 0xad91a0
    void* findKey(void* out, const void* key);             // 0xad9310
    void  DoFreeNodes(unsigned int* arr, unsigned int count);  // 0xadb680
    Iter* erase(Iter* out, Iter pos);                      // 0xadc970
    Iter* eraseA(Iter* out, Iter pos);                     // 0xadc9f0
};

extern void __stdcall FUN_00adb680(void* arr, unsigned int count);   // 0xadb680

// ---- refcounted payload ---------------------------------------------------------
struct RefObj { virtual void AddRef(); virtual void Release(); };

// ---- EditorRes payload (copy ctor 0xad7ca0, Release at vtable slot 1) -----------
struct EditorRes {                     // 0x34 bytes
    void* vt0;                         // +0x00
    int   f4;                          // +0x04
    void* vt8;                         // +0x08
    void* fC;                          // +0x0c
    float f10, f14, f18, f1c, f20, f24;// +0x10
    unsigned char b28, b29, b2a, b2b, b2c, b2d, b2e; // +0x28
    int   f30;                         // +0x30
    EditorRes* copyCtor(EditorRes*);   // 0x00ad7ca0
};

// Generic string-name table (used by cStringContext lookups); only the entry
// points this slice calls are declared.
struct NameTbl {
    void* Find(unsigned int hash, unsigned int key);                    // 0xadb250
    void  Insert(unsigned int hash, void* obj, unsigned int key);       // 0xadc890
    void* MapInsert(void* out, void* src, unsigned int flag);           // 0xadb4a0
    void* MapInsertB(void* out, void* src, bool flag);                  // 0xadb590
};
// 0x30-byte camera-info value stored in the map.
struct CamInfo {
    unsigned int f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c;
    CamInfo* assign(CamInfo* s);                                        // 0xad7f00
};
// Sub-object that owns a value slot; 0xadc900 fetches/creates the slot.
struct Sub10 {
    void* GetValue(void* out);                                          // 0xadc900
};
extern void* __cdecl FUN_004b5ad0(void* end, void* val);                                // 0x4b5ad0
extern void  __cdecl FUN_007e4190(cArguments* args, void* msg, int c);                  // 0x7e4190
extern void  __cdecl FUN_0103c4f0(void* a, void* b);                                    // 0x0103c4f0
extern void  __cdecl FUN_0092b690(void* out);                                           // 0x92b690
extern bool  __cdecl FUN_00685520(int n);                                               // 0x685520
extern void  __cdecl FUN_005d7450();                                                    // 0x5d7450
extern void  __cdecl FUN_00d2c940(void* a);                                             // 0xd2c940
extern void* __cdecl FUN_0093dc70(void* a, unsigned int n);                             // 0x93dc70
extern void  __cdecl FUN_00ad9160(void* a);                                             // 0xad9160
extern void  __stdcall EASTL_vector_dtor(void* a);                                      // 0xad92d0

// FUN_0103c4f0 is a __thiscall method of the sub-object at +0x7c that also takes
// the two pointer fields as stack arguments.
struct Sub7c { void* a; void* b; void reset(void* a, void* b); };  // 0x0103c4f0

// eastl vector growth entry point: __thiscall on the vector, (end, value).
struct VecGrow {
    void* begin;                                    // +0
    void* end;                                      // +4
    void* cap;                                      // +8
    void  grow(void* end, void** value);            // 0xadca90
};

// SpVector<Vector3>: __thiscall erase(begin, end).
struct SpVec3 {
    void* begin;                                    // +0
    void* end;                                      // +4
    void* cap;                                      // +8
    void* erase(void* begin, void* end);            // 0x50f740
    void  DoInsertValue(void* pos, const void* value);  // 0x4b5ad0
};

// ---- globals / vtables ----------------------------------------------------------
extern void* g_vtbl_145b38c;    // 0x145b38c
extern void* g_vtbl_145b380;    // 0x145b380
extern void* g_vtbl_13eb844;    // 0x13eb844
extern void* g_vtbl_145b8d0;    // 0x145b8d0
extern void* g_vtbl_145b880;    // 0x145b880
extern void* g_vtbl_145b87c;    // 0x145b87c
extern void* g_vtbl_145b81c;    // 0x145b81c
extern void* g_vtbl_145b80c;    // 0x145b80c
extern void* g_vtbl_145b2f8;    // 0x145b2f8
extern void* g_vtbl_145b2ec;    // 0x145b2ec
extern void* g_vtbl_13eb90c;    // 0x13eb90c

extern const char g_str_Simulator[];      // 0x13f09b4
extern const float g_15664a8;             // 0x15664a8
extern const float g_1471064;             // 0x1471064
extern const float g_140f7ac;             // 0x140f7ac
extern const float g_167a548;             // 0x167a548
extern const float g_167a54c;             // 0x167a54c
extern const float g_167a550;             // 0x167a550
extern const float g_1485720;             // 0x1485720
extern const float g_1470f1c;             // 0x1470f1c
extern void* g_vtbl_13ec458;    // 0x13ec458

// ================================================================================
// The `this`-based helpers, expressed as members of a small receiver so the
// compiler emits the __thiscall convention the original uses.
// ================================================================================

struct Cfg {
    char* s() { return (char*)this; }

    void ResetState();                                        // 0x00addb50
    void EraseRange();                                        // 0x00addc60
    void ParseConfigFile();                                   // 0x00addd20
    void ClearAll();                                          // 0x00addd90
    void EraseMatching(unsigned int id);                      // 0x00adde00
    void StringCtxLookup(unsigned int* p, unsigned int b, unsigned int c);  // 0x00adde90
    unsigned int MapFindInsertA(unsigned int* key);           // 0x00addfa0
    unsigned int MapFindInsertB(unsigned int* key);           // 0x00ade060
    void VecPush(void** val);                                 // 0x00ade190
};

// ================================================================================
// 0x00addb50
// ================================================================================
// @ 0x00addb50
void __fastcall FUN_00addb50(void* self, int /*edx*/)
{
    char* s = (char*)self;
    if (*(int*)(s + 0x168) != 0)
        *(char*)(*(int*)(s + 0x168) + 0x10b) = 1;

    char* o = *(char**)(s + 0x44);
    VFN(*(void**)(o + 0x20), 0x7c, TC_ii)(*(void**)(o + 0x20), 1, 0);
    VFN(*(void**)(o + 0x2c), 0x7c, TC_ii)(*(void**)(o + 0x2c), 1, 0);

    o = *(char**)(s + 0x44);
    VFN(*(void**)(o + 0x28), 0x7c, TC_ii)(*(void**)(o + 0x28), 1, 0);
    VFN(*(void**)(o + 0x2c), 0x7c, TC_ii)(*(void**)(o + 0x2c), 1, 0);

    *(float*)(s + 0x30) = g_15664a8;
    *(float*)(s + 0x34) = 0.0f;
    *(char*)(s + 0x3d) = 0;
    *(char*)(s + 0x38) = 0;
    *(char*)(s + 0x3a) = 0;
    *(char*)(s + 0x3b) = 0;
    *(char*)(s + 0x3c) = 0;

    ((Sub7c*)(s + 0x7c))->reset(((Sub7c*)(s + 0x7c))->a, ((Sub7c*)(s + 0x7c))->b);

    if (*(char*)(s + 0x15d) != 0) {
        void* p140 = *(void**)(s + 0x140);
        void* p150 = *(void**)(s + 0x150);
        *(char*)(s + 0x15d) = 0;
        if (VFN(p140, 0x24, TC_c0)(p140)) {
            VFN(*(void**)(s + 0x140), 0x28, TC_pv)(*(void**)(s + 0x140), p150);
            return;
        }
        void* h = VFN(*(void**)(s + 0x140), 0x38, TC_ps)(*(void**)(s + 0x140), "switchToExitState");
        VFN(*(void**)(s + 0x140), 0x28, TC_pv)(*(void**)(s + 0x140), h);
        return;
    }

    void* h = VFN(*(void**)(s + 0x140), 0x38, TC_ps)(*(void**)(s + 0x140), "stopCurrentCinematic");
    *(void**)(s + 0x150) = h;
    *(char*)(s + 0x15d) = 1;
    *(char*)(s + 0x3d) = 1;
}

// ================================================================================
// 0x00addc60 -- erase every element for which the predicate is true
// ================================================================================
// @ 0x00addc60
void __fastcall FUN_00addc60(void* self, int /*edx*/)
{
    char* s = (char*)self;
    HTbl* h = (HTbl*)(s + 0xd0);
    unsigned int* bucket = *(unsigned int**)(s + 0xd4);
    unsigned int node = *bucket;
    if (node == 0) {
        bucket = bucket + 1;
        node = *bucket;
        while (node == 0) {
            bucket = bucket + 1;
            node = *bucket;
        }
    }
    unsigned int end = h->arr[h->count];
    if (node == end)
        return;
    do {
        EditorRes ed;
        ed.copyCtor((EditorRes*)(node + 4));
        void* rc = ed.vt8;
        if (rc != 0 && VFN(rc, 0x10, TC_c0)(rc)) {
            Iter pos;
            pos.node = (void*)node;
            pos.bucket = bucket;
            Iter out;
            h->eraseA(&out, pos);
            node = (unsigned int)out.node;
            bucket = (unsigned int*)out.bucket;
        } else {
            node = *(unsigned int*)(node + 0x38);
            while (node == 0) {
                unsigned int* np = bucket + 1;
                bucket = bucket + 1;
                node = *np;
            }
        }
        if (rc != 0)
            VFN(rc, 4, TC_v0)(rc);
    } while (node != end);
}

// ================================================================================
// 0x00addd20 -- SP::cConfigManager::ParseConfigFile
// ================================================================================
struct CmdLineB { char pad[0x38]; void ctor(); void fini(); };   // 0x92b690 / 0x5d7450

// @ 0x00addd20
void __fastcall FUN_00addd20(void* self, int /*edx*/)
{
    char* s = (char*)self;
    char local[0x38];
    ((CmdLineB*)local)->ctor();

    VFN(*(void**)(s + 0x140), 0x1c, TC_v4)(*(void**)(s + 0x140),
        0xcecf5fdf, 0x40890200, local, 1);

    if (FUN_00685520(2)) {
        VFN(*(void**)(s + 0x140), 0x1c, TC_v4)(*(void**)(s + 0x140),
            0x4e059fe9, 0x40890200, local, 1);
    }
    ((CmdLineB*)local)->fini();
}

// ================================================================================
// 0x00addd90 -- clear all hashtable buckets
// ================================================================================
// @ 0x00addd90
void __fastcall FUN_00addd90(void* self, int /*edx*/)
{
    char* s = (char*)self;
    unsigned int* p = *(unsigned int**)(s + 0x60);
    unsigned int node = *p;
    if (node == 0) {
        p = p + 1;
        node = *p;
        while (node == 0) {
            p = p + 1;
            node = *p;
        }
        node = *p;
    }
    unsigned int end = *(unsigned int*)(*(int*)(s + 0x60) + *(int*)(s + 0x64) * 4);
    while (node != end) {
        unsigned int obj = *(unsigned int*)(node + 4);
        VFN((void*)obj, 0x10, TC_v0)((void*)obj);
        node = *(unsigned int*)(node + 8);
        while (node == 0) {
            unsigned int* np = p + 1;
            p = p + 1;
            node = *np;
        }
    }
    ((HTbl*)(s + 0x5c))->DoFreeNodes(*(unsigned int**)(s + 0x60), *(unsigned int*)(s + 0x64));
    *(unsigned int*)(s + 0x68) = 0;
}

// ================================================================================
// 0x00adde00 -- erase entries matching one id
// ================================================================================
// @ 0x00adde00
void __fastcall FUN_00adde00(void* self, int /*edx*/, unsigned int param_2)
{
    HTbl* h = (HTbl*)((char*)self + 0x5c);
    unsigned int* arr = *(unsigned int**)((char*)self + 0x60);
    unsigned int* bucket = arr;
    unsigned int node = *bucket;
    while (node == 0) {
        bucket = bucket + 1;
        node = *bucket;
    }
    unsigned int end = h->arr[h->count];
    while (node != end) {
        unsigned int obj = *(unsigned int*)(node + 4);
        unsigned int id = *(unsigned int*)(obj + 4);
        if (id != 0 && id != param_2) {
            node = *(unsigned int*)(node + 8);
            while (node == 0) {
                unsigned int* np = bucket + 1;
                bucket = bucket + 1;
                node = *np;
            }
        } else {
            VFN((void*)obj, 0x10, TC_v0)((void*)obj);
            Iter pos;
            pos.node = (void*)node;
            pos.bucket = bucket;
            Iter out;
            h->erase(&out, pos);
            node = (unsigned int)out.node;
            bucket = (unsigned int*)out.bucket;
        }
    }
}

// ================================================================================
// 0x00adde90 -- cStringContext lookup / insert
// ================================================================================
// @ 0x00adde90
void __fastcall FUN_00adde90(void* self, int /*edx*/, unsigned int* param_2, unsigned int param_3, unsigned int param_4)
{
    char* s = (char*)self;
    (void)param_3;
    if (param_4 == 0) {
        if (*(int*)(s + 0x118) == *(int*)(s + 0x128))
            param_4 = *(unsigned int*)(s + 0x148);
        else {
            unsigned int iVar5 = *(unsigned int*)(s + 0x128);
            if (iVar5 == *(unsigned int*)(s + 0x12c))
                iVar5 = *(unsigned int*)(*(int*)(s + 0x134) - 4) + 0x100;
            param_4 = *(unsigned int*)(iVar5 - 8);
        }
    }
    int* o = (int*)((NameTbl*)self)->Find(0x477df4b, param_4);
    if (o == 0) {
        o = (int*)operator new(0x30, "Simulator/cStringContext", 0, 0, 0, 0);
        if (o == 0) {
            o = 0;
        } else {
            float f0 = g_1485720;
            o[2] = (int)&g_vtbl_13ec458;
            o[3] = 0;
            o[0] = (int)&g_vtbl_145b81c;
            o[2] = (int)&g_vtbl_145b80c;
            *(float*)(o + 8) = f0;
            *(float*)(o + 9) = g_1470f1c;
            o[6] = 1;
            o[5] = 0x154df28;
            o[7] = 0;
            o[10] = 0;
        }
        ((NameTbl*)self)->Insert(0x477df4b, o, param_4);
        if (o == 0)
            return;
    }
    void* v = (void*)VFN(o, 0xc, TC_ps)(o, (const char*)0x477e049);
    if (v != 0) {
        unsigned int a0 = param_2[0];
        unsigned int a1 = param_2[1];
        unsigned int a2 = param_2[2];
        unsigned int out;
        void* p = ((Sub10*)((char*)v + 0x10))->GetValue(&out);
        *(unsigned int*)p = a0;
        ((unsigned int*)p)[1] = a1;
        ((unsigned int*)p)[2] = a2;
    }
}

// ================================================================================
// 0x00addfa0 -- map find-or-insert (EditorRes payload)
// ================================================================================
// @ 0x00addfa0
unsigned int __fastcall FUN_00addfa0(void* self, int /*edx*/, unsigned int* param_2)
{
    HTbl* h = (HTbl*)self;
    unsigned int local;
    h->Find((Iter*)&local, param_2);
    if (local != (unsigned int)h->arr[h->count])
        return local + 4;

    unsigned int key = *param_2;
    unsigned char tmp[0x6c];
    *(unsigned int*)(tmp + 0x00) = (unsigned int)&g_vtbl_145b2f8;
    *(unsigned int*)(tmp + 0x04) = 0;
    *(unsigned int*)(tmp + 0x08) = (unsigned int)&g_vtbl_145b2ec;
    *(unsigned int*)(tmp + 0x0c) = 0;
    *(unsigned int*)(tmp + 0x34) = key;

    EditorRes* ed = (EditorRes*)(tmp + 0x38);
    ed->copyCtor((EditorRes*)tmp);

    // The original reuses the (dead) Find-result slot for the 1-byte bool
    // argument, so the upper three bytes are the node pointer's. Reproduce the
    // exact stack word so the call argument matches; the callee only reads the
    // low byte (flag == false).
    unsigned int out;
    ((NameTbl*)self)->MapInsert(&out, (void*)(tmp + 0x34), local & 0xFFFFFF00u);
    void* r1 = *(void**)((char*)ed + 0x0c);
    if (r1 != 0)
        VFN(r1, 4, TC_v0)(r1);
    void* r2 = *(void**)(tmp + 0x0c);
    if (r2 != 0)
        VFN(r2, 4, TC_v0)(r2);
    return out + 4;
}

// ================================================================================
// 0x00ade060 -- map find-or-insert (camera info payload)
// ================================================================================
// @ 0x00ade060
unsigned int __fastcall FUN_00ade060(void* self, int /*edx*/, unsigned int* param_2)
{
    HTbl* h = (HTbl*)self;
    unsigned int out;
    h->findKey(&out, param_2);
    if (out != (unsigned int)h->arr[h->count])
        return out + 4;

    unsigned char tmp[0x78];
    CamInfo* src = (CamInfo*)(tmp + 0x18);
    src->f00 = *(unsigned int*)&g_167a548;
    src->f04 = *(unsigned int*)&g_167a54c;
    src->f08 = *(unsigned int*)&g_167a550;
    src->f0c = 0;
    src->f10 = 0;
    src->f14 = 0;
    src->f18 = 0;
    src->f1c = *(unsigned int*)&g_1485720;
    src->f20 = *(unsigned int*)&g_1485720;
    src->f24 = *(unsigned int*)&g_1485720;
    src->f28 = *(unsigned int*)&g_1485720;
    src->f2c = 0;

    *(unsigned int*)(tmp + 0x44) = 0;
    *(unsigned int*)(tmp + 0x48) = *param_2;

    CamInfo* dest = (CamInfo*)(tmp + 0x4c);
    dest->assign(src);

    bool flag = false;
    unsigned int res;
    ((NameTbl*)self)->MapInsertB(&res, (void*)(tmp + 0x48), flag);
    void* r1 = *(void**)(tmp + 0x78);
    if (r1 != 0)
        VFN(r1, 0xc0, TC_v0)(r1);
    void* r2 = *(void**)(tmp + 0x44);
    if (r2 != 0)
        VFN(r2, 0xc0, TC_v0)(r2);
    return res + 4;
}

// ================================================================================
// 0x00ade190 -- eastl vector<AutoRefCount>::push_back
// ================================================================================
// @ 0x00ade190
void __fastcall FUN_00ade190(void* self, int /*edx*/, void** param_2)
{
    void** p2 = param_2;
    unsigned int* v = (unsigned int*)self;
    unsigned int cur = v[1];
    if (cur < v[2]) {
        v[1] = cur + 4;
        if (cur != 0) {
            void* o = *p2;
            *(void**)cur = o;
            if (o != 0) {
                VFN((char*)o + 8, 0, TC_v0)((char*)o + 8);
                return;
            }
        }
    } else {
        ((VecGrow*)self)->grow((void*)cur, p2);
    }
}

// ================================================================================
// 0x00ade1d0 -- `anonymous namespace'::cMetaParticleForceCommand::Execute
// ================================================================================
extern void* __cdecl FUN_0050f740(void* self, void* begin, void* end);   // 0x50f740
extern const char** __cdecl FUN_00838130(cArguments* self, const char* name, int* count, int min, int max);  // 0x838130

// @ 0x00ade1d0
void __fastcall FUN_00ade1d0(void* self, int /*edx*/, cArguments* args)
{
    char* s = (char*)self;
    args->MainArguments(0);

    unsigned int* o = (unsigned int*)operator new(0x8c, "Simulator", 0, 0, 0, 0);
    if (o != 0) {
        o[1] = 0;
        unsigned int* sub = o + 2;                 // +8 sub-object
        *sub = (unsigned int)&g_vtbl_145b38c;      // dead store
        *o = (unsigned int)&g_vtbl_145b38c;
        *sub = (unsigned int)&g_vtbl_145b380;
        o[0x1b] = 0;
        o[0x1c] = 0;
        o[0x1d] = 0;
        VFN(sub, 0, TC_v0)(sub);
    } else {
        o = 0;
    }

    float zero = 0.0f;
    float k1471064 = g_1471064;
    *(float*)((char*)o + 0x80) = zero;
    *(float*)((char*)o + 0x84) = zero;
    *(float*)((char*)o + 0x88) = zero;
    *(float*)((char*)o + 0x14) = zero;
    *(float*)((char*)o + 0x18) = zero;
    *(float*)((char*)o + 0x60) = k1471064;
    *(float*)((char*)o + 0x1c) = zero;
    *(float*)((char*)o + 0x20) = zero;
    *(float*)((char*)o + 0x64) = g_140f7ac;
    *(float*)((char*)o + 0x24) = zero;
    *(float*)((char*)o + 0x28) = zero;
    o[0x10] = 3;
    *(char*)((char*)o + 0x3c) = 1;
    *(char*)((char*)o + 0x3e) = 0;
    o[4] = 0;
    *(char*)((char*)o + 0x44) = 0;
    *(float*)((char*)o + 0x54) = zero;
    *(float*)((char*)o + 0x58) = g_1485720;
    *(char*)((char*)o + 0x2c) = 0;
    *(char*)((char*)o + 0x3d) = 0;
    *(float*)((char*)o + 0x0c) = zero;
    *(char*)((char*)o + 0x5d) = 0;

    unsigned int* m = (unsigned int*)operator new(0x40, "Simulator", 0, 0, 0, 0);
    if (m != 0) {
        m[0xc] = 0;
        *m = (unsigned int)&g_vtbl_13eb90c;     // dead store
        m[1] = 0;
        m[0xe] = 0;
        *m = (unsigned int)&g_vtbl_13eb844;
        VFN(m, 4, TC_v0)(m);
    } else {
        m = 0;
    }

    unsigned int* r = o + 2;
    if ((m[0xe] & 1) != 0 && (unsigned int*)m[2] != 0)
        VFN((unsigned int*)m[2], 4, TC_v0)((unsigned int*)m[2]);
    m[2] = (unsigned int)r;
    if (r != 0)
        VFN(r, 0, TC_v0)(r);
    m[0xe] = m[0xe] | 1;
    m[0xc] = 0x04448b81;

    if (args->HasFlag("noWait"))
        *(char*)((char*)o + 0x3c) = 0;
    if (args->HasFlag("ease"))
        *(char*)((char*)o + 0x3e) = 1;

    const char** a;
    a = args->OptionArguments("target", 1);
    if (a != 0)
        o[4] = FNV1_String8(*a, 0x811c9dc5, 1);

    a = args->OptionArguments("pos", 1);
    if (a != 0) {
        unsigned int v[3];
        VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, *a);
        *(float*)((char*)o + 0x80) = *(float*)&v[0];
        *(float*)((char*)o + 0x84) = *(float*)&v[1];
        *(float*)((char*)o + 0x88) = *(float*)&v[2];
    }

    a = args->OptionArguments("targetOffset", 1);
    if (a != 0) {
        unsigned int v[3];
        VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, *a);
        *(float*)((char*)o + 0x14) = *(float*)&v[0];
        *(float*)((char*)o + 0x18) = *(float*)&v[1];
        *(float*)((char*)o + 0x1c) = *(float*)&v[2];
    }

    ((SpVec3*)((char*)o + 0x6c))->erase(*(void**)((char*)o + 0x6c), *(void**)((char*)o + 0x70));

    int count = 0;
    const char** e;
    e = args->OptionArguments("path", &count, 1, 1000);
    if (e != 0) {
        for (int i = 0; i < count; ++i) {
            unsigned int v[3];
            VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, e[i]);
            float x = *(float*)&v[0], y = *(float*)&v[1], z = *(float*)&v[2];
            float* dst = *(float**)((char*)o + 0x70);
            if ((char*)dst < *(char**)((char*)o + 0x74)) {
                *(float**)((char*)o + 0x70) = dst + 3;
                if (dst != 0) { dst[0] = x; dst[1] = y; dst[2] = z; }
            } else {
                ((SpVec3*)((char*)o + 0x6c))->DoInsertValue(dst, &x);
            }
        }
    } else {
        e = args->OptionArguments("pathEndStart", &count, 1, 1000);
        if (e != 0) {
            for (int i = 0; i < count; ++i) {
                unsigned int v[3];
                VFN(*(void**)(s + 4), 0xa8, TC_vps)(*(void**)(s + 4), v, e[i]);
                float x = *(float*)&v[0], y = *(float*)&v[1], z = *(float*)&v[2];
                float* dst = *(float**)((char*)o + 0x70);
                if ((char*)dst < *(char**)((char*)o + 0x74)) {
                    *(float**)((char*)o + 0x70) = dst + 3;
                    if (dst != 0) { dst[0] = x; dst[1] = y; dst[2] = z; }
                } else {
                    ((SpVec3*)((char*)o + 0x6c))->DoInsertValue(dst, &x);
                }
            }
            *(char*)((char*)o + 0x44) = 1;
        }
    }

    a = args->OptionArguments("fov", 1);
    if (a != 0)
        *(float*)((char*)o + 0x54) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);
    a = args->OptionArguments("nearClip", 1);
    if (a != 0)
        *(float*)((char*)o + 0x60) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);
    a = args->OptionArguments("farClip", 1);
    if (a != 0)
        *(float*)((char*)o + 0x64) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);
    a = args->OptionArguments("duration", 1);
    if (a != 0)
        *(float*)((char*)o + 0x58) = VFN(*(void**)(s + 4), 0x98, TC_fs)(*(void**)(s + 4), (const char*)*a);

    ((cAppState*)*(void**)(s + 0xc))->AddMessage(args, m, 0);
    VFN(m, 8, TC_v0)(m);
    VFN(r, 4, TC_v0)(r);
}

// ================================================================================
// 0x00ade680 -- destructor
// ================================================================================
// @ 0x00ade680
void __fastcall FUN_00ade680(void* self, int /*edx*/)
{
    unsigned int* p = (unsigned int*)self;
    p[0] = (unsigned int)&g_vtbl_145b8d0;
    p[1] = (unsigned int)&g_vtbl_145b880;
    p[2] = (unsigned int)&g_vtbl_145b87c;

    EASTL_vector_dtor((char*)p + 0x1ac);

    unsigned int v = p[0x60];
    if (v != 0 && v != p[0x64])
        operator_delete((void*)v);

    if (p[0x5b] != 0)
        (*(void(__thiscall**)(unsigned int))(*(unsigned int*)(p[0x5b] + 8) + 4))(p[0x5b] + 8);
    if ((unsigned int*)p[0x5a] != 0)
        (*(void(__thiscall**)(unsigned int*))(*(unsigned int*)p[0x5a] + 4))((unsigned int*)p[0x5a]);
    if ((unsigned int*)p[0x59] != 0)
        (*(void(__thiscall**)(unsigned int*))(*(unsigned int*)p[0x59] + 4))((unsigned int*)p[0x59]);
    if ((unsigned int*)p[0x50] != 0)
        (*(void(__thiscall**)(unsigned int*))(*(unsigned int*)p[0x50] + 4))((unsigned int*)p[0x50]);
    if ((unsigned int*)p[0x4f] != 0)
        (*(void(__thiscall**)(unsigned int*))(*(unsigned int*)p[0x4f] + 0xc))((unsigned int*)p[0x4f]);

    FUN_00d2c940((char*)p + 0xf0);
    FUN_0093dc70((void*)p[0x3d], p[0x3e]);
    p[0x3f] = 0;
    if (p[0x3e] > 1)
        operator_delete((void*)p[0x3d]);

    FUN_00adb680((void*)p[0x35], p[0x36]);
    p[0x37] = 0;
    if (p[0x36] > 1)
        operator_delete((void*)p[0x35]);

    FUN_00adb680((void*)p[0x2d], p[0x2e]);
    p[0x2f] = 0;
    if (p[0x2e] > 1)
        operator_delete((void*)p[0x2d]);

    FUN_00adb680((void*)p[0x25], p[0x26]);
    p[0x27] = 0;
    if (p[0x26] > 1)
        operator_delete((void*)p[0x25]);

    FUN_00ad9160((char*)p + 0x110);
    FUN_00adb680((void*)p[0x18], p[0x19]);
    p[0x1a] = 0;
    if (p[0x19] > 1)
        operator_delete((void*)p[0x18]);
}
