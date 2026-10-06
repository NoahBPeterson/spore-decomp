// Slice s007d85b0 (batch w2g5): SP::cApp app-mode management (apply/add/remove/
// shutdown), cAppModeInfo range helpers, the cAppModeCheat command, and the
// CreateApp factory / cApp destructor.
// Retail module flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"
#include <string.h>

typedef unsigned int size_type;
typedef int ptrdiff_t;

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define ALLOC_NAME "App"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }
void ea_free(void* p);

void* GetMessageServer();
void* GetServer883860();
void* CheatManager();
void  SlotMessageDestruct(void* msg);
void  ErrorNoSuchMode(const char* fmt);                  // cError ctor/throw site

// helpers defined elsewhere (masked)
int  Sub_7d8890(void* first, void* last, void* dest);    // uninitialized copy
void Sub_7d90a0(void* value);                            // add to vector

struct cAppModeInfo;
cAppModeInfo* Sub_7d8740(cAppModeInfo* self, const cAppModeInfo* src);

// eastl::basic_string<char,allocator> (3 pointers + allocator word)
struct Str16 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mAlloc;       // +0x0c
    void assign(const char* begin, const char* end);   // @ 0x00454cb0 (thiscall)
};

struct cAppModeInfo {                 // size 0x18
    void*    mpMode;                  // +0x00 AutoRefCount<cIAppMode>
    unsigned mID;                     // +0x04
    Str16    mName;                   // +0x08

    cAppModeInfo* operator=(const cAppModeInfo& x);       // @ 0x007d8830
};

inline void ModeInfoRelease(void* obj) {
    if (obj) ((void(__thiscall*)(void*))(*(void***)obj)[1])(obj);
}
inline void ModeInfoAddRef(void* obj) {
    if (obj) ((void(__thiscall*)(void*))(*(void***)obj)[0])(obj);
}
inline bool ModeInfoFreeName(cAppModeInfo* e) {
    if ((int)(e->mName.mpCapacity - e->mName.mpBegin) > 1 && e->mName.mpBegin != 0) {
        ea_free(e->mName.mpBegin);
        return true;
    }
    return false;
}
inline void ModeInfoDestroy(cAppModeInfo* e) {
    ModeInfoFreeName(e);
    ModeInfoRelease(e->mpMode);
}

// @ 0x007d8830
cAppModeInfo* cAppModeInfo::operator=(const cAppModeInfo& x) {
    void* s = x.mpMode;
    void* d = mpMode;
    if (s != d) {
        ModeInfoAddRef(s);
        mpMode = s;
        ModeInfoRelease(d);
    }
    mID = x.mID;
    if (&x.mName != &mName)
        mName.assign(x.mName.mpBegin, x.mName.mpEnd);
    return this;
}

// @ 0x007d87e0
void __stdcall cAppModeInfoDestroyRange(cAppModeInfo* first, cAppModeInfo* last) {
    for (; first < last; ++first)
        ModeInfoDestroy(first);
}

// @ 0x007d8920
cAppModeInfo* cAppModeInfoDestroyMove(cAppModeInfo* first, cAppModeInfo* last, cAppModeInfo* dest) {
    for (; first != last; ++first, ++dest)
        ModeInfoDestroy(first);
    return dest;
}

// @ 0x007d8980
cAppModeInfo* cAppModeInfoAssignRange(cAppModeInfo* first, cAppModeInfo* last, cAppModeInfo* dest) {
    for (; first != last; ++first, ++dest)
        dest->operator=(*first);
    return dest;
}

// @ 0x007d8a10
cAppModeInfo* cAppModeInfoAssignBackward(cAppModeInfo* first, cAppModeInfo* last, cAppModeInfo* dest) {
    while (last != first) {
        --last;
        --dest;
        dest->operator=(*last);
    }
    return dest;
}

namespace SP {

struct cApp;

struct cApp {
    void** mIAppVtbl;                 // +0x00
    void** mHandlerVtbl;              // +0x04
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

    void ApplyAppMode(int index);                            // @ 0x007d85b0
    bool SetAppMode(unsigned id);                            // @ 0x007d8c30
    bool SetAppModeByIndex(int index);                       // @ 0x007d8c80
    bool AddAppMode(void* mode, unsigned id, const char* name); // @ 0x007d9260
    void InsertAppMode(cAppModeInfo* position, const cAppModeInfo& value); // @ 0x007d8e40
    bool RemoveAppMode(unsigned id);                         // @ 0x007d8ff0
    bool Shutdown();                                         // @ 0x007d9120
};

struct cAppModeCheat {
    char pad00[4];
    void* mOutput;                    // +0x04
    char pad08[8];
    void* mManager;                   // +0x10
    void Execute(void* args);         // @ 0x007d8ab0
};

} // namespace SP
using namespace SP;

// @ 0x007d85b0
void cApp::ApplyAppMode(int index) {
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

// @ 0x007d8c30
bool cApp::SetAppMode(unsigned id) {
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
bool cApp::SetAppModeByIndex(int index) {
    if (index >= 0 && index < (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18) {
        ApplyAppMode(index);
        return true;
    }
    return false;
}

// @ 0x007d8e40
void cApp::InsertAppMode(cAppModeInfo* position, const cAppModeInfo& value) {
    if (mAppModesEnd != mAppModesCapacity) {
        const cAppModeInfo* p = &value;
        if ((char*)&value >= (char*)position && (char*)&value < (char*)mAppModesEnd)
            p = (const cAppModeInfo*)((char*)&value + 0x18);
        if (mAppModesEnd != 0)
            Sub_7d8740(mAppModesEnd, mAppModesEnd - 1);
        cAppModeInfoAssignBackward(position, mAppModesEnd - 1, mAppModesEnd);
        position->operator=(*p);
        mAppModesEnd = mAppModesEnd + 1;
    } else {
        int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
        int newCap = (n != 0) ? (2 * n) : 1;
        cAppModeInfo* newBuf = (cAppModeInfo*)operator new[](newCap * 0x18, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        size_type posIndex = (size_type)((char*)position - (char*)mAppModesBegin);
        cAppModeInfo* mid = (cAppModeInfo*)Sub_7d8890(mAppModesBegin, position, newBuf);
        cAppModeInfoDestroyRange(mAppModesBegin, position);
        Sub_7d8740(mid, &value);
        cAppModeInfo* end = (cAppModeInfo*)Sub_7d8890(position, mAppModesEnd, mid + 1);
        cAppModeInfoDestroyRange(position, mAppModesEnd);
        if (mAppModesBegin != 0 && ((int*)mAppModesBegin)[-1] != 0)
            ea_free(mAppModesBegin);
        mAppModesBegin = newBuf;
        mAppModesEnd = end;
        mAppModesCapacity = (cAppModeInfo*)((char*)newBuf + newCap * 0x18);
        (void)posIndex;
    }
}

// @ 0x007d9260
bool cApp::AddAppMode(void* mode, unsigned id, const char* name) {
    if (mode == 0)
        return false;
    if (mInitialized)
        ((void(__thiscall*)(void*))(*(void***)mode)[3])(mode);
    cAppModeInfo info;
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

// @ 0x007d8ff0
bool cApp::RemoveAppMode(unsigned id) {
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    for (int i = 0; i < n; ++i) {
        if (mAppModesBegin[i].mID == id) {
            void* mode = mAppModesBegin[i].mpMode;
            ((void(__thiscall*)(void*))(*(void***)mode)[0x14 / 4])(mode);
            cAppModeInfo* remove = mAppModesBegin + i;
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
bool cApp::Shutdown() {
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

// @ 0x007d8ab0
void cAppModeCheat::Execute(void* args) {
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

struct cAppToggleHandler {
    char pad00[0x10];
    bool mFlag;            // +0x10
    bool Handle(int msg, int data);   // @ 0x007d9350
};

struct cAppHasState {
    char pad00[0x18];
    bool Check();                     // @ 0x007d9380
};

// @ 0x007d9350
bool cAppToggleHandler::Handle(int msg, int data) {
    if (msg == 0x4d && data == 0) {
        mFlag = (mFlag == 0);
        return true;
    }
    return false;
}

// @ 0x007d9380
bool cAppHasState::Check() {
    int i = 0;
    int* p = (int*)((char*)this + 0x18);
    for (; i < 3; ++i, ++p) {
        if (*p == 0x1c)
            return true;
    }
    return false;
}

// @ 0x007d8dc0
cApp* CreateApp() {
    cApp* p = (cApp*)operator new[](0x34, ALLOC_NAME, 0, 0, 0, 0);
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

// @ 0x007d8d40
void AppDestructor(cApp* self) {
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

// @ 0x007d93a0
void SomeBaseDestructor(void* self) {
    *(void**)self = (void*)0x014128a8;
    *(void**)((char*)self + 4) = (void*)0x01412894;
    *(void**)((char*)self + 8) = (void*)0x01412890;
    void* p = *(void**)((char*)self + 0x24);
    if (p != 0)
        ((void(__thiscall*)(void*))(*(void***)p)[1])(p);
    *(void**)((char*)self + 8) = (void*)0x013ef094;
    *(void**)((char*)self + 4) = (void*)0x013eb394;
    *(void**)self = (void*)0x013eb938;
}
