// Batch w1g5 slice s0069f950: SP::cCOMSerializer serializable write/read helpers,
// the cObjectDatabase ctor, and SP::GetPropertyAsVector2/3/4.
// Region is /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast /GS-.
#include "types.h"
#include <new>

typedef void* VP;

struct Vec2 { float x, y; };
struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };

// EA::Variant as seen by the property getters.
struct Variant {
    VP mPtr;                // +0
    int mField4;            // +4
    int mCount;             // +8
    int mFieldC;            // +0xc
    unsigned short mFlags;  // +0x10
    unsigned short mTypeId; // +0x12
    Vec2* asVector2();
    Vec3* asVector3();
    Vec4* asVector4();
};

extern "C" void* EASTL_allocator_allocate(unsigned size, const char* name, int, int, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p);
extern "C" void  FUN_0093a780(void*, void*, int, int);
extern "C" void  FUN_0093aa70(void*, void*, int, int);
extern "C" void  FUN_00920090();
extern "C" void  FUN_00571f40(void*);
extern "C" void  FUN_0069e880(void*);
extern "C" bool  FUN_006a0110(void* self, void*, void*);
extern "C" char  loadSingleObject_thunk(void* self, unsigned, void*, void*);
extern "C" void  FUN_0069ec20(void*, void*, void*);

extern char g_vtbl_1408750[];
extern char g_vtbl_1408728[];
extern char g_vtbl_14095cc[];
extern char g_vtbl_13eb938[];
extern char g_vtbl_13ec458[];
extern char g_vtbl_14085f0[];
extern char g_vtbl_1408500[];
extern char g_vtbl_13f1ab0[];
extern char g_vtbl_14084f0[];
extern char g_vtbl_14086e8[];
extern char g_vtbl_1408698[];
extern char g_vtbl_1408688[];
extern char g_vtbl_1408678[];

// ===========================================================================
// SP::GetPropertyAsVector2 / 3 / 4
// ===========================================================================
// @ 0x006a10c0
extern "C" bool GetPropertyAsVector2(Variant* v, int prop)
{
    if (!v)
        return false;
    Variant tmp;
    if (!((char(__thiscall*)(void*, int, Variant*))(*(void***)v)[0x24 / 4])(v, prop, &tmp))
        return false;
    if (tmp.mTypeId != 0x30)
        return false;
    Vec2* src = tmp.asVector2();
    *(Vec2*)v = *src;
    return true;
}

// @ 0x006a1110
extern "C" bool GetPropertyAsVector3(Variant* v, int prop)
{
    if (!v)
        return false;
    Variant tmp;
    if (!((char(__thiscall*)(void*, int, Variant*))(*(void***)v)[0x24 / 4])(v, prop, &tmp))
        return false;
    if (tmp.mTypeId != 0x31)
        return false;
    Vec3* src = tmp.asVector3();
    *(Vec3*)v = *src;
    return true;
}

// @ 0x006a1160
extern "C" bool GetPropertyAsVector4(Variant* v, int prop)
{
    if (!v)
        return false;
    Variant tmp;
    if (!((char(__thiscall*)(void*, int, Variant*))(*(void***)v)[0x24 / 4])(v, prop, &tmp))
        return false;
    if (tmp.mTypeId != 0x33)
        return false;
    Vec4* src = tmp.asVector4();
    *(Vec4*)v = *src;
    return true;
}

// ===========================================================================
// Serializer helpers (behaviour-only reconstructions).
// ===========================================================================
struct cCOMSerializer {
    VP vt0;                 // +0
    int mRefCount;          // +4
    VP vt8;                 // +8
    unsigned char flag_c;   // +0xc
    char pad0[3];
    char trees[0x38];       // +0x10 .. +0x48
    int mode48;             // +0x48
    unsigned char b4c;      // +0x4c
    unsigned char b4d;      // +0x4d
    char pad1[2];
    void* p50;              // +0x50
    void* p54;              // +0x54
    void* p58;              // +0x58
    void* p5c;              // +0x5c

    bool writeSerializable(void* p, void* q);   // 0x6a05f0
    bool readSerializable(void* p, void* q, char deep); // 0x6a06a0
    bool onSetSPSerializable(void* a, void* b); // 0x6a0110
    bool loadSingleObject(unsigned off, void* a, void* b); // 0x6a0360
    bool saveClassObjects();                    // 0x69fb90
};

// @ 0x006a05f0
bool cCOMSerializer::writeSerializable(void* p, void* q)
{
    if (mode48 == 0)
        return false;
    void* pi = ((void*(__thiscall*)(void*))(*(void***)p)[0x20 / 4])(p);
    void* io = ((void*(__thiscall*)(void*))(*(void***)pi)[0x18 / 4])(pi);
    void* qv = 0;
    if (q)
        qv = ((void*(__thiscall*)(void*))(*(void***)q)[0x20 / 4])(q);
    unsigned v1 = (unsigned)(unsigned long)p;
    FUN_0093aa70(io, &v1, 1, 0);
    if (q) {
        unsigned v2 = (unsigned)(unsigned long)qv;
        FUN_0093aa70(io, &v2, 1, 0);
        if (!FUN_006a0110((char*)this - 8, q, qv))
            return false;
    }
    if (!((char(__thiscall*)(void*))(*(void***)p)[0x1c / 4])(p))
        return false;
    return true;
}

// @ 0x006a06a0
bool cCOMSerializer::readSerializable(void* p, void* q, char deep)
{
    if (mode48 == 0)
        return false;
    void* pi = ((void*(__thiscall*)(void*))(*(void***)p)[0x20 / 4])(p);
    void* io = ((void*(__thiscall*)(void*))(*(void***)pi)[0x18 / 4])(pi);
    int a = 0;
    FUN_0093a780(io, &a, 1, 0);
    if (a == 0) {
        *(int*)q = 0;
    } else {
        int b = 0;
        FUN_0093a780(io, &b, 1, 0);
        if (!((cCOMSerializer*)((char*)this - 8))->onSetSPSerializable(q, (void*)a))
            return false;
        if (deep)
            loadSingleObject_thunk((char*)this - 8, *(unsigned*)q, (void*)a, (void*)b);
    }
    if (!((char(__thiscall*)(void*))(*(void***)p)[0x1c / 4])(p))
        return false;
    return true;
}

// @ 0x006a0110
bool cCOMSerializer::onSetSPSerializable(void*, void*)
{
    // rbtree find/insert of cClassInfo and cIDInfo; summarised.
    return true;
}

// @ 0x006a0360
bool cCOMSerializer::loadSingleObject(unsigned, void*, void*)
{
    return false;
}

// @ 0x69fb90
bool cCOMSerializer::saveClassObjects()
{
    return true;
}

// ===========================================================================
// cObjectDatabase constructor
// ===========================================================================
struct cObjectDatabase {
    VP vt0; VP vt4; VP vt8; VP pad_c; VP vt10; void* p14;
    void* p18; void* p1c; float f20;
    cObjectDatabase* ctor(void* database);   // 0x69fa60
};

// @ 0x0069fa60
cObjectDatabase* cObjectDatabase::ctor(void* database)
{
    vt0 = g_vtbl_14085f0;
    vt8 = g_vtbl_13f1ab0;
    vt4 = g_vtbl_1408500;
    vt8 = g_vtbl_14084f0;
    p18 = 0;   // (+0xc)
    vt10 = g_vtbl_13ec458;
    p14 = 0;
    vt0 = g_vtbl_14086e8;
    vt4 = g_vtbl_1408698;
    vt8 = g_vtbl_1408688;
    vt10 = g_vtbl_1408678;
    p18 = 0;
    p1c = 0;
    f20 = 0.0f;
    void* pc = EASTL_allocator_allocate(0x68, "App", 0, 0, 0, 0);
    void* sub = pc ? ((char*)pc + 8) : 0;
    void* old = p1c;
    if (sub != old) {
        if (sub) ((void(__thiscall*)(void*))(*(void***)sub)[0])(sub);
        p1c = sub;
        if (old) ((void(__thiscall*)(void*))(*(void***)old)[4 / 4])(old);
    }
    old = p18;
    if (database != old) {
        if (database) ((void(__thiscall*)(void*))(*(void***)database)[0])(database);
        p18 = database;
        if (old) ((void(__thiscall*)(void*))(*(void***)((char*)old + 4))[4 / 4])((char*)old + 4);
    }
    return this;
}

// ===========================================================================
// eastl::map operator[] (summarised)
// ===========================================================================
// @ 0x0069f950
extern "C" void* mapClassInfoOperatorIndex(void* map, int* key)
{
    return (char*)0 + 0x14;   // placeholder
}

// @ 0x006a0920
extern "C" bool GetPropertyAsIntFlag(void* obj, int prop, int* out)
{
    if (!obj)
        return false;
    Variant tmp;
    if (!((char(__thiscall*)(void*, int, Variant*))(*(void***)obj)[0x24 / 4])(obj, prop, &tmp))
        return false;
    if (tmp.mTypeId != 0x30)
        return false;
    if ((tmp.mFlags & 0x10) == 0)
        return false;
    if (tmp.mFlags & 0x30)
        *out = *(int*)&tmp.mPtr;
    else
        *out = 1;
    if (tmp.mFlags & 0x30)
        *out = *(int*)&tmp.mPtr;
    else
        *out = (tmp.mTypeId != 0) ? (int)(long)&tmp : 0;
    return true;
}
