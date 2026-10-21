// src/game/SPEngine/SPAppMode.cpp -- migrated from slice(s) s007d85b0, s007d76d0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppMode.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <string.h>

// ---- items of slice s007d76d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define ALLOC_NAME "App"
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void* operator new(size_t, void* p) { return p; }
void ea_free(void* p);
void* Sub_7d5d50(void* p);                 // ctor
void* GetMessageServer();   // 0x0067dcc0 (equiv t2)
void* CheatManager();   // 0x0067de20 (equiv t2)
void* CreateCameraManager();   // 0x007c7700 (equiv t2)
void  SlotMessageDestruct(void* msg);   // 0x00421cf0 (equiv t2)
namespace SP {
struct cAppModeInfo {                 // size 0x18
    void*    mpMode;                  // +0x00  AutoRefCount<cIAppMode>
    unsigned mID;                     // +0x04
    char*    mNameBegin;              // +0x08
    char*    mNameEnd;                // +0x0c
    char*    mNameCapacity;           // +0x10
    int      mNameAlloc;              // +0x14
};
}
namespace SP {
class cApp;
}
namespace SP {
struct IHandlerRC {
    void** vftable;                   // +0x00
    bool HandleMessage(int msg, void* data);
};
}
namespace SP {
class cApp { public:
    void** mIAppVtbl;                 // +0x00
    void** mHandlerVtbl;              // +0x04 (IHandlerRC vtable)
    char   pad08[8];                  // +0x08
    bool   mInitialized;              // +0x10
    char   pad11[3];
    cAppModeInfo* mAppModesBegin;     // +0x14
    cAppModeInfo* mAppModesEnd;       // +0x18
    cAppModeInfo* mAppModesCapacity;  // +0x1c
    int    pad20;                     // +0x20
    int    pad24;                     // +0x24
    int    mModeIndex;                // +0x28
    void*  mViewer;                   // +0x2c
    void*  mMainViewer;               // +0x30
    char   pad34[0x8c];

    int  AppModeCount() const { return (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18; }
    bool Init();
    bool PreInitAppModes();
    bool InitAppModes();
    void* AppMode(unsigned id);
    void* AppMode();
    unsigned AppModeID();
    bool SetAppModeByName(const char* name);
    void* AppModeID(int index);
    unsigned AppModeName(int index);
    void SetMainViewer(void* v);
    bool SwitchMode();
};
}
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007d76d0 end

// ---- items of slice s007d85b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
    void ea_free(...); // 0x00f47380
typedef unsigned int size_type;
void* GetServer883860();
void  ErrorNoSuchMode(const char* fmt);                  // cError ctor/throw site
int  Sub_7d8890(void* first, void* last, void* dest);    // uninitialized copy
void Sub_7d90a0(void* value);                            // add to vector
struct cAppModeInfo_s007d_85b0;
struct Str16 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
    void assign(const char* begin, const char* end);   // @ 0x00454cb0 (thiscall)
};
struct cAppModeInfo_s007d_85b0 {                 // size 0x18
    void*    mpMode;                  // +0x00 AutoRefCount<cIAppMode>
    unsigned mID;                     // +0x04
    Str16    mName;                   // +0x08

    cAppModeInfo_s007d_85b0* operator=(const cAppModeInfo_s007d_85b0& x);       // @ 0x007d8830
};
inline void ModeInfoRelease(void* obj) {
    if (obj) ((void(__thiscall*)(void*))(*(void***)obj)[1])(obj);
}
inline void ModeInfoAddRef(void* obj) {
    if (obj) ((void(__thiscall*)(void*))(*(void***)obj)[0])(obj);
}
inline bool ModeInfoFreeName(cAppModeInfo_s007d_85b0* e) {
    if ((int)(e->mName.mpCapacity - e->mName.mpBegin) > 1 && e->mName.mpBegin != 0) {
        ea_free(e->mName.mpBegin);
        return true;
    }
    return false;
}
inline void ModeInfoDestroy(cAppModeInfo_s007d_85b0* e) {
    ModeInfoFreeName(e);
    ModeInfoRelease(e->mpMode);
}
void* __cdecl Memmove_11e0744(void* dst, const void* src, unsigned n);   // 0x011e0744 (static CRT)
struct RefInit {
    void* p;
    RefInit(void* q) : p(q) { ModeInfoAddRef(p); }
};
struct StrD {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAlloc;
    StrD() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~StrD() { if ((int)(mpCapacity - mpBegin) > 1 && mpBegin != 0) ea_free(mpBegin); }
    void RangeInitialize(unsigned n);   // @ 0x00475ab0 (thiscall)
};
struct cAppModeInfoC {
    RefInit  mpMode;
    unsigned mID;
    StrD     mName;
    cAppModeInfoC(const cAppModeInfoC& src);   // @ 0x007d8740
};
namespace SP {
struct cApp_s007d_85b0;
}
namespace SP {
struct cApp_s007d_85b0 {
    void** mIAppVtbl;                 // +0x00
    void** mHandlerVtbl;              // +0x04
    char   pad08[8];                  // +0x08
    bool   mInitialized;              // +0x10
    char   pad11[3];
    cAppModeInfo_s007d_85b0* mAppModesBegin;     // +0x14
    cAppModeInfo_s007d_85b0* mAppModesEnd;       // +0x18
    cAppModeInfo_s007d_85b0* mAppModesCapacity;  // +0x1c
    int    pad20;                     // +0x20
    int    pad24;                     // +0x24
    int    mModeIndex;                // +0x28
    void*  mViewer;                   // +0x2c
    void*  mMainViewer;               // +0x30

    void ApplyAppMode(int index);                            // @ 0x007d85b0
    bool SetAppMode(unsigned id);                            // @ 0x007d8c30
    bool SetAppModeByIndex(int index);                       // @ 0x007d8c80
    bool AddAppMode(void* mode, unsigned id, const char* name); // @ 0x007d9260
    void InsertAppMode(cAppModeInfo_s007d_85b0* position, const cAppModeInfo_s007d_85b0& value); // @ 0x007d8e40
    bool RemoveAppMode(unsigned id);                         // @ 0x007d8ff0
    bool Shutdown();                                         // @ 0x007d9120
};
}
namespace SP {
struct cAppModeCheat {
    char pad00[4];
    void* mOutput;                    // +0x04
    char pad08[8];
    void* mManager;                   // +0x10
    void Execute(void* args);         // @ 0x007d8ab0
};
}
// ---- items of slice s007d85b0 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
cAppModeInfo_s007d_85b0* cAppModeInfoAssignRange(cAppModeInfo_s007d_85b0* first, cAppModeInfo_s007d_85b0* last, cAppModeInfo_s007d_85b0* dest);  // 0x007d8980 (stays in the slice: not this object's)
cAppModeInfo_s007d_85b0* cAppModeInfoAssignBackward(cAppModeInfo_s007d_85b0* first, cAppModeInfo_s007d_85b0* last, cAppModeInfo_s007d_85b0* dest);  // 0x007d8a10 (stays in the slice: not this object's)

// @ 0x007d8060
bool SP::cApp::Init()
{
    if (mInitialized)
        return false;
    mInitialized = true;
    void* mgr = CreateCameraManager();
    void* old = mViewer;
    if (mgr != old) {
        if (mgr != 0)
            ((void(__thiscall*)(void*))(*(void***)mgr)[2])(mgr);
        mViewer = mgr;
        if (old != 0)
            ((void(__thiscall*)(void*))(*(void***)old)[3])(old);
    }
    if (mViewer != 0)
        ((void(__thiscall*)(void*, const char*))(*(void***)mViewer)[4])(mViewer, "camera");
    if (CheatManager() != 0) {
        void* cmd = operator new(0x14, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        if (cmd != 0) {
            Sub_7d5d50(cmd);                       // cCommandBase ctor
            *(void**)cmd = (void*)0x014124e8;      // cAppModeCheat vtable (masked)
            *(void**)((char*)cmd + 0x10) = this;
        }
    }
    void* handler = (char*)this + 4;
    void* server = GetMessageServer();
    ((void(__thiscall*)(void*, void*, int))(*(void***)server)[8])(server, handler, 0xd3c602);
    server = GetMessageServer();
    ((void(__thiscall*)(void*, void*, int))(*(void***)server)[8])(server, handler, 0xe11332);
    server = GetMessageServer();
    ((void(__thiscall*)(void*, void*, int))(*(void***)server)[8])(server, handler, 0xe11333);
    return true;
}

// @ 0x007d8180
bool SP::IHandlerRC::HandleMessage(int msg, void* data)
{
    SP::cApp* app = (SP::cApp*)((char*)this - 4);
    void** vt = app->mIAppVtbl;
    if (msg == 0xd3c602) {
        ((void(__thiscall*)(void*, void*))vt[0x40 / 4])(app, *(void**)((char*)data + 8));
        return true;
    }
    if (msg == 0xe11332) {
        ((void(__thiscall*)(void*, void*))vt[0x28 / 4])(app, *(void**)((char*)data + 8));
        return true;
    }
    if (msg == 0xe11333) {
        void* p = *(void**)((char*)data + 8);
        int v = *(int*)((char*)p + 0xc);
        if (v != 0)
            ((void(__thiscall*)(void*, int))vt[0x4c / 4])(app, v);
        return true;
    }
    return false;
}

// @ 0x007d81f0
bool SP::cApp::PreInitAppModes()
{
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    if (n > 0) {
        SP::cAppModeInfo* p = mAppModesBegin;
        for (int i = 0; i < n; ++i, ++p) {
            void* mode = p->mpMode;
            void** vt = *(void***)mode;
            ((void(__thiscall*)(void*))vt[0x0c / 4])(mode);
        }
    }
    return true;
}

// @ 0x007d8230
bool SP::cApp::InitAppModes()
{
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    if (n > 0) {
        SP::cAppModeInfo* p = mAppModesBegin;
        for (int i = 0; i < n; ++i, ++p) {
            void* mode = p->mpMode;
            void** vt = *(void***)mode;
            ((void(__thiscall*)(void*, void*))vt[0x10 / 4])(mode, this);
        }
    }
    return true;
}

// @ 0x007d8270
void* SP::cApp::AppMode(unsigned id)
{
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    SP::cAppModeInfo* p = mAppModesBegin;
    for (int i = 0; i < n; ++i, ++p) {
        if (p->mID == id)
            return p->mpMode;
    }
    return 0;
}

// @ 0x007d82c0
void* SP::cApp::AppMode()
{
    if (mModeIndex >= 0) {
        if (mModeIndex < (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
            return mAppModesBegin[mModeIndex].mpMode;
    }
    return 0;
}

// @ 0x007d8300
unsigned SP::cApp::AppModeID()
{
    if (mModeIndex >= 0) {
        if (mModeIndex < (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
            return mAppModesBegin[mModeIndex].mID;
    }
    return 0;
}

// @ 0x007d8360
bool SP::cApp::SetAppModeByName(const char* name)
{
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    SP::cAppModeInfo* p = mAppModesBegin;
    for (int i = 0; i < n; ++i, ++p) {
        if (p->mNameBegin != p->mNameEnd) {
            if (_stricmp(p->mNameBegin, name) == 0) {
                void** vt = mIAppVtbl;
                ((void(__thiscall*)(void*, int))vt[0x40 / 4])(this, i);
                return true;
            }
        }
    }
    return false;
}

// @ 0x007d83d0
void* SP::cApp::AppModeID(int index)
{
    if (index < 0)
        return 0;
    if (index >= (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
        return 0;
    return mAppModesBegin[index].mpMode;
}

// @ 0x007d8410
unsigned SP::cApp::AppModeName(int index)
{
    if (index < 0)
        return 0;
    if (index >= (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
        return 0;
    return mAppModesBegin[index].mID;
}

// @ 0x007d8450
void SP::cApp::SetMainViewer(void* v)
{
    mMainViewer = v;
    void* viewer = mViewer;
    void** vt = *(void***)viewer;
    ((void(__thiscall*)(void*, void*))vt[0x18 / 4])(viewer, v);
}

// @ 0x007d8470
bool SP::cApp::SwitchMode()
{
    int index = mModeIndex;
    if (index < 0 || index >= (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
        return false;
    SP::cAppModeInfo* info = mAppModesBegin + index;
    ((void(__thiscall*)(void*))(*(void***)info->mpMode)[0x1c / 4])(info->mpMode);
    void* server = GetMessageServer();
    if (server != 0) {
        char msg[0x30];
        *(int*)(msg + 0x00) = 0;
        *(int*)(msg + 0x04) = 0;
        *(void**)(msg + 0x08) = (void*)0x013eb844;
        *(int*)(msg + 0x0c) = 0;
        *(int*)(msg + 0x14) = 0;
        *(unsigned*)(msg + 0x18) = info->mID;
        void** vt = *(void***)server;
        ((void(__thiscall*)(void*, int, void*, int))vt[0x14 / 4])(server, 0x212d3e7, msg, 0);
        ((void(__thiscall*)(void*, int, void*, int))vt[0x14 / 4])(server, 0x22d1adc, msg, 0);
        SlotMessageDestruct(msg);
    }
    mModeIndex = -1;
    return true;
}

// @ 0x007d8580
void __fastcall VectorOwnerDestroy(void** self)
{
    int begin = (int)self[2];
    int end = (int)self[4];
    if (end - begin > 1 && begin != 0)
        ea_free((void*)begin);
    int obj = (int)self[0];
    if (obj != 0) {
        void** vt = *(void***)obj;
        ((void(__thiscall*)(void*))vt[1])((void*)obj);
    }
}

// @ 0x007d85b0
void SP::cApp_s007d_85b0::ApplyAppMode(int index)
{
    int old = mModeIndex;
    if (index == old)
        return;
    unsigned prevID = 0;
    if (old >= 0 && old < (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18) {
        void* mode = mAppModesBegin[old].mpMode;
        ((void(__thiscall*)(void*))(*(void***)mode)[0x1c / 4])(mode);
        prevID = mAppModesBegin[old].mID;
    }
    mModeIndex = index;
    void* server = GetServer883860();
    if (server != 0) {
        char msg[0x30];
        *(int*)(msg + 0x00) = 0;
        *(int*)(msg + 0x04) = 0;
        *(void**)(msg + 0x08) = (void*)0x013eb844;
        *(int*)(msg + 0x0c) = 0;
        *(int*)(msg + 0x10) = 0;
        *(unsigned*)(msg + 0x14) = mAppModesBegin[mModeIndex].mID;
        *(int*)(msg + 0x18) = 0;
        *(unsigned*)(msg + 0x1c) = prevID;
        void** vt = *(void***)server;
        ((void(__thiscall*)(void*, int, void*, int))vt[0x14 / 4])(server, 0x212d3e7, msg, 0);
        SlotMessageDestruct(msg);
    }
    {
        void* mode = mAppModesBegin[mModeIndex].mpMode;
        ((void(__thiscall*)(void*))(*(void***)mode)[0x18 / 4])(mode);
    }
    if (server != 0) {
        char msg[0x30];
        *(int*)(msg + 0x00) = 0;
        *(int*)(msg + 0x04) = 0;
        *(void**)(msg + 0x08) = (void*)0x013eb844;
        *(int*)(msg + 0x0c) = 0;
        *(int*)(msg + 0x10) = 0;
        *(unsigned*)(msg + 0x14) = mAppModesBegin[mModeIndex].mID;
        *(int*)(msg + 0x18) = 0;
        *(unsigned*)(msg + 0x1c) = prevID;
        void** vt = *(void***)server;
        ((void(__thiscall*)(void*, int, void*, int))vt[0x14 / 4])(server, 0x22d1adc, msg, 0);
        SlotMessageDestruct(msg);
    }
}

// @ 0x007d8740
cAppModeInfoC::cAppModeInfoC(const cAppModeInfoC& src)
: mpMode(src.mpMode.p), mID(src.mID) {
    StrD* t = &mName;
    const char* sb = src.mName.mpBegin;
    const char* se = src.mName.mpEnd;
    unsigned n = se - sb;
    t->RangeInitialize(n + 1);
    char* d = t->mpBegin;
    Memmove_11e0744(d, sb, n);
    t->mpEnd = d + (se - sb);
    *t->mpEnd = 0;
}

// @ 0x007d87e0
void __stdcall cAppModeInfoDestroyRange(cAppModeInfo_s007d_85b0* first, cAppModeInfo_s007d_85b0* last)
{
    for (; first < last; ++first)
        ModeInfoDestroy(first);
}

// @ 0x007d8920
cAppModeInfo_s007d_85b0* cAppModeInfoDestroyMove(cAppModeInfo_s007d_85b0* first, cAppModeInfo_s007d_85b0* last, cAppModeInfo_s007d_85b0* dest)
{
    for (; first != last; ++first, ++dest)
        ModeInfoDestroy(first);
    return dest;
}

// @ 0x007d8ab0
void SP::cAppModeCheat::Execute(void* args)
{
    void* argv = 0;
    int argc = 0;
    void* list = ((void*(__thiscall*)(void*, void**, int, int))0x838020)(args, &argv, 0, 1);
    void** mvt = *(void***)mManager;
    int n = ((int(__thiscall*)(void*))mvt[0x3c / 4])(mManager);
    if (argc > 0) {
        for (int i = 0; i < n; ++i) {
            const char* s = ((const char*(__thiscall*)(void*, int))mvt[0x48 / 4])(mManager, i);
            if (s != 0 && _stricmp(s, *(const char**)list) == 0) {
                ((void(__thiscall*)(void*, int))mvt[0x40 / 4])(mManager, i);
                return;
            }
        }
        ErrorNoSuchMode("no such mode");
        return;
    }
    int hasList = ((int(__thiscall*)(void*, const char*))mvt[0x38 / 4])(mManager, "list");
    if (hasList) {
        for (int i = 0; i < n; ++i) {
            const char* s = ((const char*(__thiscall*)(void*, int))mvt[0x48 / 4])(mManager, i);
            if (s != 0)
                ((void(__cdecl*)(void*, const char*, const char*))0x841000)(mOutput, "  %s\n", s);
        }
        return;
    }
    unsigned cur = ((unsigned(__thiscall*)(void*))mvt[0x38 / 4])(mManager);
    for (int i = 0; i < n; ++i) {
        unsigned id = ((unsigned(__thiscall*)(void*, int))mvt[0x34 / 4])(mManager, i);
        if (id == cur) {
            const char* s = ((const char*(__thiscall*)(void*, int))mvt[0x48 / 4])(mManager, i);
            if (s != 0) {
                ((void(__cdecl*)(void*, const char*, const char*))0x841000)(mOutput, "Current mode: %s\n", s);
                return;
            }
            break;
        }
    }
    ((void(__cdecl*)(void*, const char*, unsigned))0x841000)(mOutput, "Current mode: 0x%08x\n", cur);
}

// @ 0x007d8c30
bool SP::cApp_s007d_85b0::SetAppMode(unsigned id)
{
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    for (int i = 0; i < n; ++i) {
        if (mAppModesBegin[i].mID == id) {
            ApplyAppMode(i);
            return true;
        }
    }
    return false;
}

// @ 0x007d8c80
bool SP::cApp_s007d_85b0::SetAppModeByIndex(int index)
{
    if (index >= 0 && index < (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18) {
        ApplyAppMode(index);
        return true;
    }
    return false;
}

// @ 0x007d8d40
void AppDestructor(SP::cApp_s007d_85b0* self)
{
    *(void**)self = (void*)0x01412598;
    *(void**)((char*)self + 4) = (void*)0x01412584;
    *(void**)((char*)self + 8) = (void*)0x01412580;
    if (self->mViewer != 0)
        ((void(__thiscall*)(void*))(*(void***)self->mViewer)[3])(self->mViewer);
    cAppModeInfoDestroyRange(self->mAppModesBegin, self->mAppModesEnd);
    if (self->mAppModesBegin != 0 && ((int*)self->mAppModesBegin)[-1] != 0)
        ea_free(self->mAppModesBegin);
    *(void**)((char*)self + 8) = (void*)0x013ef094;
    *(void**)((char*)self + 4) = (void*)0x013eb394;
    *(void**)self = (void*)0x013eb938;
}

// @ 0x007d8dc0
SP::cApp_s007d_85b0* CreateApp()
{
    SP::cApp_s007d_85b0* p = (SP::cApp_s007d_85b0*)operator new[](0x34, ALLOC_NAME, 0, 0, 0, 0);
    if (p != 0) {
        *(void**)((char*)p + 4) = (void*)0x013eb384;
        *(void**)((char*)p + 0x0c) = 0;
        *(void**)((char*)p + 0x08) = (void*)0x013ef094;
        p->mInitialized = false;
        p->mIAppVtbl = (void**)0x01412598;
        p->mHandlerVtbl = (void**)0x01412584;
        *(void**)((char*)p + 0x08) = (void*)0x01412580;
        p->mAppModesBegin = 0;
        p->mAppModesEnd = 0;
        p->mAppModesCapacity = 0;
        p->mModeIndex = -1;
        p->mViewer = 0;
        p->mMainViewer = 0;
        return p;
    }
    return 0;
}

// @ 0x007d8e40
void SP::cApp_s007d_85b0::InsertAppMode(cAppModeInfo_s007d_85b0* position, const cAppModeInfo_s007d_85b0& value)
{
    if (mAppModesEnd != mAppModesCapacity) {
        const cAppModeInfo_s007d_85b0* p = &value;
        if ((char*)&value >= (char*)position && (char*)&value < (char*)mAppModesEnd)
            p = (const cAppModeInfo_s007d_85b0*)((char*)&value + 0x18);
        if (mAppModesEnd != 0)
            new (mAppModesEnd) cAppModeInfoC(*(cAppModeInfoC*)(mAppModesEnd - 1));
        cAppModeInfoAssignBackward(position, mAppModesEnd - 1, mAppModesEnd);
        position->operator=(*p);
        mAppModesEnd = mAppModesEnd + 1;
    } else {
        int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
        int newCap = (n != 0) ? (2 * n) : 1;
        cAppModeInfo_s007d_85b0* newBuf = (cAppModeInfo_s007d_85b0*)operator new[](newCap * 0x18, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        size_type posIndex = (size_type)((char*)position - (char*)mAppModesBegin);
        cAppModeInfo_s007d_85b0* mid = (cAppModeInfo_s007d_85b0*)Sub_7d8890(mAppModesBegin, position, newBuf);
        cAppModeInfoDestroyRange(mAppModesBegin, position);
        new (mid) cAppModeInfoC(*(const cAppModeInfoC*)&value);
        cAppModeInfo_s007d_85b0* end = (cAppModeInfo_s007d_85b0*)Sub_7d8890(position, mAppModesEnd, mid + 1);
        cAppModeInfoDestroyRange(position, mAppModesEnd);
        if (mAppModesBegin != 0 && ((int*)mAppModesBegin)[-1] != 0)
            ea_free(mAppModesBegin);
        mAppModesBegin = newBuf;
        mAppModesEnd = end;
        mAppModesCapacity = (cAppModeInfo_s007d_85b0*)((char*)newBuf + newCap * 0x18);
        (void)posIndex;
    }
}

// @ 0x007d8ff0
bool SP::cApp_s007d_85b0::RemoveAppMode(unsigned id)
{
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    for (int i = 0; i < n; ++i) {
        if (mAppModesBegin[i].mID == id) {
            void* mode = mAppModesBegin[i].mpMode;
            ((void(__thiscall*)(void*))(*(void***)mode)[0x14 / 4])(mode);
            cAppModeInfo_s007d_85b0* remove = mAppModesBegin + i;
            if (remove + 1 < mAppModesEnd)
                cAppModeInfoAssignRange(remove + 1, mAppModesEnd, remove);
            mAppModesEnd = mAppModesEnd - 1;
            ModeInfoDestroy(mAppModesEnd);
            return true;
        }
    }
    return false;
}

// @ 0x007d9120
bool SP::cApp_s007d_85b0::Shutdown()
{
    if (!mInitialized)
        return false;
    mInitialized = false;
    void* handler = (char*)this + 4;
    void* server = GetMessageServer();
    ((void(__thiscall*)(void*, void*, int, int))(*(void***)server)[0x2c / 4])(server, handler, 0xd3c602, 0xffffd8f1);
    server = GetMessageServer();
    ((void(__thiscall*)(void*, void*, int, int))(*(void***)server)[0x2c / 4])(server, handler, 0xe11332, 0xffffd8f1);
    server = GetMessageServer();
    ((void(__thiscall*)(void*, void*, int, int))(*(void***)server)[0x2c / 4])(server, handler, 0xe11333, 0xffffd8f1);
    if (mModeIndex >= 0)
        ((void(__thiscall*)(void*))mIAppVtbl[0x1c / 4])(this);
    void* cheat = CheatManager();
    if (cheat != 0)
        ((void(__thiscall*)(void*, void*))(*(void***)cheat)[0x1c / 4])(cheat, *(void**)0x0153de4c);
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    for (int i = 0; i < n; ++i) {
        void* mode = mAppModesBegin[i].mpMode;
        ((void(__thiscall*)(void*))(*(void***)mode)[0x14 / 4])(mode);
    }
    cAppModeInfoDestroyRange(mAppModesBegin, mAppModesEnd);
    mAppModesEnd = mAppModesBegin;
    mModeIndex = -1;
    if (mViewer != 0) {
        ((void(__thiscall*)(void*))(*(void***)mViewer)[0x14 / 4])(mViewer);
        void* v = mViewer;
        if (v != 0) {
            mViewer = 0;
            ((void(__thiscall*)(void*))(*(void***)v)[3])(v);
        }
    }
    mMainViewer = 0;
    return true;
}

// @ 0x007d9260
bool SP::cApp_s007d_85b0::AddAppMode(void* mode, unsigned id, const char* name)
{
    if (mode == 0)
        return false;
    if (mInitialized)
        ((void(__thiscall*)(void*))(*(void***)mode)[3])(mode);
    cAppModeInfo_s007d_85b0 info;
    info.mpMode = 0;
    info.mName.mpBegin = 0;
    info.mName.mpEnd = 0;
    info.mName.mpCapacity = 0;
    info.mName.mAlloc = 0;
    ((void(__thiscall*)(void*))(*(void***)mode)[0])(mode);
    info.mpMode = mode;
    info.mID = id;
    info.mName.assign(name, name + strlen(name));
    Sub_7d90a0(&info);
    ModeInfoFreeName(&info);
    ModeInfoRelease(info.mpMode);
    return true;
}
