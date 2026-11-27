// src/game/SPEngine/SPGraphicsArenaUtils.cpp -- migrated from slice(s) s00e043c0, s006c1cd0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPGraphicsArenaUtils.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "rw/core/arena/Arena.h"

// unnamed retail callees and globals (address in the comment)
extern void* g_lightManager;                                  // 0x16c8b44
extern void* rwSectionInitCombined(void* out, int count, void* data, int a, int b);     // 0x011e4dd0
extern void* rwArenaSectionsInitialize(void* arr, int count, void* data, int a, int b); // 0x011e4e70
extern void  arenaFinalize(void* p);                                                    // 0x011e3ed0
extern void  ehVectorCtor(void* p, int elemSize, int count, void* ctorFn);              // 0x011e0b85
extern void  ehVectorDtor(void* p, int elemSize, int count, void* dtorFn);              // 0x011e0b22
extern void  sub_f47380(void* p);                                                       // 0x00f47380
#include <string.h>
#include "cSPUILayout.h"
#include "SP/cSPUINewProgressBar.h"
#include "SP/cString.h"

// ---- items of slice s006c1cd0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   u32;
typedef unsigned char  u8;
extern u32   sub_928a30(u32, u32, int,int,int,int,int,int);   // create render object
extern void* g_lightManager;                                  // 0x16c8b44
struct LightMgr {
    void Destroy(u32 p);
    u32 Create(u32 a, u32 b, int c, int d, int e, int f, int g, int h);
};
extern void  sub_11fb220(u32);                                // free
struct Arena {
    void Release();                                           // 0x011e40a0 (rw::core::arena::Arena::Release)
};
extern u32   sub_6c24b0(void*, void*, void*, int, int, int, const char*);
// editor resources: a base with a virtual interface (vtable 0x13eb938) and a reference to an object released through
// vtable slot 1; the destructors unwind through the reference member and the base, so they build EH frames
struct EditorResourceBase {
    virtual void Slot0();
    ~EditorResourceBase() {}
};
struct IEditorReleasable {
    virtual void Slot0();
    virtual void Release();
};
struct EditorResourceRef {
    IEditorReleasable* mp;
    ~EditorResourceRef() { if (mp != 0) mp->Release(); }
};
struct __declspec(novtable) EditorResource : EditorResourceBase {
    char pad04[0x14];
    void* field18;           // +0x18 arena
    EditorResourceRef field1c; // +0x1c
    ~EditorResource();
};
struct EditorResource2 : EditorResource {
    void* field20;           // +0x20
    u32   arr24[4];          // +0x24
    u32   arr34[4];          // +0x34
    ~EditorResource2();
};
extern "C" long __cdecl _InterlockedExchange(long volatile* target, long value);
#pragma intrinsic(_InterlockedExchange)
// the property list's constructor view: a reference-counted base (vtable 0x13ebcdc, count cleared atomically, fields zeroed; destroyed
// if the rest throws), then its own vtable and the owner reference at +0x1c taken through vtable slot 0
struct PropertyListBase {
    virtual void Slot0();
    volatile long field04;   // +0x04 (atomic reference count)
    u32   f08, f0c, f10, f14, f18; // +0x08
    PropertyListBase() { volatile long* r = &field04; _InterlockedExchange(r, 0); f08 = 0; f0c = 0; f10 = 0; f14 = 0; f18 = 0; }
    ~PropertyListBase() {}
};
struct IPropertyListOwner { virtual void AddRef(); virtual void Release(); };
struct PropertyListOwnerRef {
    IPropertyListOwner* mp;
    PropertyListOwnerRef(void* p) : mp((IPropertyListOwner*)p) { if (p != 0) mp->AddRef(); }
    ~PropertyListOwnerRef() { if (mp != 0) mp->Release(); }
};
struct PropertyListObj : PropertyListBase {
    PropertyListOwnerRef field1c;  // +0x1c
    PropertyListObj(void* p);
};
struct PropertyList {
    void* vtbl;              // +0x00
    volatile long field04;   // +0x04 (atomic reference count)
    u32   f08, f0c, f10, f14, f18; // +0x08
    void* field1c;           // +0x1c
};
typedef void  (__thiscall* FixedVectorInsertFn)(void* vec, int* pos, const int* value);
typedef void  (__thiscall* ArenaAddObjectFn)(void* arena, void* a, u32 handle, void* b);
extern void* rwSectionInitCombined(void* out, int count, void* data, int a, int b);     // 0x011e4dd0
extern void* rwArenaSectionsInitialize(void* arr, int count, void* data, int a, int b); // 0x011e4e70
extern void* arenaGetResourceDescriptor(void* out, int size, int a, u32 magic,
                                        void* sections, void* desc, void* mgr);         // 0x011e3190
extern void* arenaInitialize(void* arr, int size, int a, u32 magic,
                             void* sections, void* desc, void* mgr);                    // 0x011e3f20
extern void  arenaFinalize(void* p);                                                    // 0x011e3ed0
extern void  ehVectorCtor(void* p, int elemSize, int count, void* ctorFn);              // 0x011e0b85
extern void  ehVectorDtor(void* p, int elemSize, int count, void* dtorFn);              // 0x011e0b22
extern void* sub_f473a0(u32 size, const char* name, int a, int b, int c, int d);        // 0x00f473a0
extern void  sub_f47380(void* p);                                                       // 0x00f47380
struct BakedArenaResource : PropertyList {   // PropertyList = 0x20 bytes
    u32 field20;      // +0x20  sections
    u32 arr24[4];     // +0x24  resource render objects
    u32 arr34[4];     // +0x34  section render objects
};
struct BakedFrameRec {
    u32 d[14];   // 0x38 bytes
};
// ---- items of slice s006c1cd0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   sub_928a30(u32, u32, int,int,int,int,int,int);   // create render object
extern void  sub_11fb220(u32);                                // free
extern u32   sub_6c24b0(void*, void*, void*, int, int, int, const char*);
extern void* arenaGetResourceDescriptor(void* out, int size, int a, u32 magic,
                                        void* sections, void* desc, void* mgr);         // 0x011e3190
extern void* arenaInitialize(void* arr, int size, int a, u32 magic,
                             void* sections, void* desc, void* mgr);                    // 0x011e3f20
extern void* sub_f473a0(u32 size, const char* name, int a, int b, int c, int d);        // 0x00f473a0

// @ 0x006c2060
void CreateRenderObjects(u32* out, u32* in)
{    for (u32 i = 0; i < 4; ++i) {
        u32 a = in[i * 2];
        u32 b = in[i * 2 + 1];
        if (a > 0) {
            out[i] = ((LightMgr*)g_lightManager)->Create(a, b, 0, 0, 0, 0, 0, 0);
        } else {
            out[i] = 0;
        }
    }}

// @ 0x006c20b0
void DestroyRenderObjects(u32* arr)
{
    for (u32 i = 0; i < 4; ++i) {
        u32 p = arr[i];
        if (p != 0) {
            ((LightMgr*)g_lightManager)->Destroy(p);
            arr[i] = 0;
        }
    }
}

// @ 0x006c20e0
void DestroySomeRenderObjects(u32* arr)
{
    for (u32 i = 0; i < 4; ++i) {
        if (i == 1 || i == 3) {
            u32 p = arr[i];
            if (p != 0) {
                ((LightMgr*)g_lightManager)->Destroy(p);
                arr[i] = 0;
            }
        }
    }
}

// @ 0x006c2120
EditorResource::~EditorResource()
{
}

// @ 0x006c2170
EditorResource2::~EditorResource2()
{
    if (field18 != 0) {
        ((Arena*)field18)->Release();
    }
    DestroyRenderObjects(arr24);
    if (field20 != 0)
        sub_11fb220((u32)field20);
    DestroyRenderObjects(arr34);
}

// @ 0x006c2240
PropertyListObj::PropertyListObj(void* p)
    : field1c(p)
{
    f18 = 0;
}

// @ 0x006c22b0
void* BakeResourceCtor(void* self, void* p2, int count, void* frames, int unique, const char* name)
{
    BakedArenaResource* r = (BakedArenaResource*)self;

    // base PropertyList construction (inlined)
    r->vtbl = (void*)0x13ebcdc;
    r->field04 = 0;
    r->f08 = 0; r->f0c = 0; r->f10 = 0; r->f14 = 0;
    r->vtbl = (void*)0x140a5bc;
    r->field1c = p2;
    if (p2 != 0)
        ((void(__thiscall*)(void*))(*(void***)p2)[0])(p2);
    r->f18 = 0;

    r->vtbl = (void*)0x140a5a8;
    r->field20 = 0;
    for (int i = 0; i < 4; ++i) {
        r->arr24[i] = 0;
        r->arr34[i] = 0;
    }

    struct { void* vf; } mgr;
    mgr.vf = (void*)0x140a578;
    int mgrData = ((int(__cdecl*)(void*))*(void**)0x140a57c)(&mgr);

    u8 secBuffer[32];
    rwSectionInitCombined(secBuffer, unique, frames, 0, 0);
    CreateRenderObjects(r->arr34, (u32*)secBuffer);
    void* sections = rwArenaSectionsInitialize(r->arr34, unique, frames, 0, 0);
    r->field20 = (u32)sections;

    u32 descArgs[8];
    ehVectorCtor(descArgs, 8, 4, (void*)0x00c2e4e0);
    descArgs[0] = 0;
    descArgs[1] = 1;

    u8 descBuffer[32];
    arenaGetResourceDescriptor(descBuffer, count * 4, 1, 0xcafed00d,
                               (void*)r->field20, descArgs, (void*)(mgrData + 4));
    CreateRenderObjects(r->arr24, (u32*)descBuffer);
    void* arena = arenaInitialize(r->arr24, count * 4, 1, 0xcafed00d,
                                  (void*)r->field20, descArgs, (void*)(mgrData + 4));
    r->f18 = (u32)arena;
    arenaFinalize(arena);

    ehVectorDtor(descBuffer, 8, 4, (void*)0x00c2e4e0);
    ehVectorDtor(descArgs, 8, 4, (void*)0x00c2e4e0);
    ehVectorDtor(secBuffer, 8, 4, (void*)0x00c2e4e0);
    return self;
}

// @ 0x006c24b0
u32 sub_6c24b0(void* a, void* b, void* c, int count, int d, int e, const char* name)
{
    BakedFrameRec* recs = (BakedFrameRec*)c;

    struct BakedVec {
        int* begin;
        int* end;
        int* capEnd;
        int  buffer[18];
    } frames;
    frames.begin = frames.buffer;
    frames.end = frames.buffer;
    frames.capEnd = frames.buffer + 18;

    void* frameArg = (void*)d;
    int unique = e;

    if (e < 0) {
        for (int i = 0; i < count; ++i) {
            int value = (int)recs[i].d[0];
            bool found = false;
            for (int* it = frames.begin; it != frames.end; ++it) {
                if (*it == value) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                if (frames.end < frames.capEnd) {
                    if (frames.end != 0)
                        *frames.end = value;
                    ++frames.end;
                } else {
                    ((FixedVectorInsertFn)0x0060a600)(&frames, frames.end, &value);
                }
            }
        }
        unique = (int)(frames.end - frames.begin);
        frameArg = frames.begin;
    }

    BakedArenaResource* res = 0;
    void* mem = sub_f473a0(0x44, "Graphics", 0, 0, 0, 0);
    if (mem != 0)
        res = (BakedArenaResource*)BakeResourceCtor(mem, b, count, frameArg, unique, name);

    void* arena = (void*)res->f18;

    for (int i = 0; i < count; ++i) {
        u8 buf[0x38];
        memcpy(buf, &recs[i], 0x38);
        ((ArenaAddObjectFn)0x011e3300)(arena, buf + 8, *(u32*)buf, buf + 0x18);
        ehVectorDtor(buf + 0x18, 8, 4, (void*)0x00c2e4e0);
    }

    *(BakedArenaResource**)a = res;
    ((void(__thiscall*)(void*))(*(void***)res)[0])(res);

    if (frames.begin != 0 && frames.begin != frames.buffer)
        sub_f47380(frames.begin);

    return 0;
}

// @ 0x00e043c0
int __cdecl CivComm_GetStateIconName(int state)
{
    switch (state) {
    case 3:  return 0x10033;
    case 10: return 0x10031;
    case 9:  return 0x10035;
    case 11: return 0x10039;
    case 6:  return 0x1003b;
    case 0:  return 0x10037;
    case 4:  return 0x1003f;
    case 7:  return 0x10041;
    case 1:  return 0x1003d;
    case 5:  return 0x1006b;
    case 8:  return 0x1006d;
    case 2:
    default: return 0x1006f;
    }
}
