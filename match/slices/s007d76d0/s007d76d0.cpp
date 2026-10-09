// Slice s007d76d0 (batch w2g5): SP::cGameModelEffect split handling, a small
// creature-ability command class, and SP::cApp mode/message methods.
// Retail module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <string.h>

typedef unsigned int size_type;
typedef int ptrdiff_t;

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
#define ALLOC_NAME "App"

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line)
{ return operator new[](size, pName, flags, debugFlags, file, line); }
inline void operator delete(void*, const char*, int, unsigned, const char*, int) {}
void operator delete(void* p);
inline void* operator new(size_t, void* p) { return p; }
void ea_free(void* p);

// helpers defined elsewhere (masked relocations)
void* Sub_7d5d50(void* p);                 // ctor
void  Sub_572680(void* refcountHolder, void* obj);
void* Sub_7d6380(void* p);                 // ctor
void* Sub_7d6440(void* p);                 // ctor
void* Sub_7d55e0(void* p);                 // cEffectParams ctor
void  Sub_7d6b00(void* dst, const void* src); // cEffectParams::operator=
void  Sub_7d4620(void* params, int slot);  // cEffectParams::UnknownStore
void* Sub_7d5240(const void* src);         // build some record
void  Sub_7d7000(void* dst, void* src);
int   Sub_79ab90(int a, void* b, void* c, int d);
void* Sub_7df780(void* p);
void  Sub_4e3260(void* pos, void* value);  // vector<AutoRefCount>::DoInsertValue
void  Sub_4e0e80(void* vec, void* value);  // vector<AutoRefCount>::push_back
void* RBTreeIncrement(void* node);         // eastl::RBTreeIncrement   // 0x00921580 (equiv t2)
void  Sub_538000(void* out, const void* src); // cSPTransform copy ctor
void  Sub_5387f40();
void  Sub_537f40(void* dst);
void  Matrix3_Assign(void* dst, const void* src);
void* ModelManager();
void* GetMessageServer();   // 0x0067dcc0 (equiv t2)
void* CheatManager();   // 0x0067de20 (equiv t2)
void* CreateCameraManager();   // 0x007c7700 (equiv t2)
int   Sub_a826c0(int n, void** outPtr, int* outCount);
void* GetServer883860();
void  SlotMessageDestruct(void* msg);   // 0x00421cf0 (equiv t2)
void  AddSplitInstanceRaw(void* mgr, void* xform, int id, int flag); // 0x007d7640 (slice s007d67e0)
void* Sub_67de00();                        // 0x0067de00

struct IUnknownBase { void** vftable; };

// ---------------------------------------------------------------------------
// SP::cApp
// ---------------------------------------------------------------------------
namespace SP {

struct cAppModeInfo {                 // size 0x18
    void*    mpMode;                  // +0x00  AutoRefCount<cIAppMode>
    unsigned mID;                     // +0x04
    char*    mNameBegin;              // +0x08
    char*    mNameEnd;                // +0x0c
    char*    mNameCapacity;           // +0x10
    int      mNameAlloc;              // +0x14
};

struct cApp;

struct IHandlerRC {
    void** vftable;                   // +0x00
    bool HandleMessage(int msg, void* data);
};

struct cApp {
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

} // namespace SP

using namespace SP;

// @ 0x007d81f0
bool cApp::PreInitAppModes() {
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    if (n > 0) {
        cAppModeInfo* p = mAppModesBegin;
        for (int i = 0; i < n; ++i, ++p) {
            void* mode = p->mpMode;
            void** vt = *(void***)mode;
            ((void(__thiscall*)(void*))vt[0x0c / 4])(mode);
        }
    }
    return true;
}

// @ 0x007d8230
bool cApp::InitAppModes() {
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    if (n > 0) {
        cAppModeInfo* p = mAppModesBegin;
        for (int i = 0; i < n; ++i, ++p) {
            void* mode = p->mpMode;
            void** vt = *(void***)mode;
            ((void(__thiscall*)(void*, void*))vt[0x10 / 4])(mode, this);
        }
    }
    return true;
}

// @ 0x007d8270
void* cApp::AppMode(unsigned id) {
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    cAppModeInfo* p = mAppModesBegin;
    for (int i = 0; i < n; ++i, ++p) {
        if (p->mID == id)
            return p->mpMode;
    }
    return 0;
}

// @ 0x007d82c0
void* cApp::AppMode() {
    if (mModeIndex >= 0) {
        if (mModeIndex < (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
            return mAppModesBegin[mModeIndex].mpMode;
    }
    return 0;
}

// @ 0x007d8300
unsigned cApp::AppModeID() {
    if (mModeIndex >= 0) {
        if (mModeIndex < (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
            return mAppModesBegin[mModeIndex].mID;
    }
    return 0;
}

// @ 0x007d8360
bool cApp::SetAppModeByName(const char* name) {
    int n = (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18;
    cAppModeInfo* p = mAppModesBegin;
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
void* cApp::AppModeID(int index) {
    if (index < 0)
        return 0;
    if (index >= (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
        return 0;
    return mAppModesBegin[index].mpMode;
}

// @ 0x007d8410
unsigned cApp::AppModeName(int index) {
    if (index < 0)
        return 0;
    if (index >= (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
        return 0;
    return mAppModesBegin[index].mID;
}

// @ 0x007d8450
void cApp::SetMainViewer(void* v) {
    mMainViewer = v;
    void* viewer = mViewer;
    void** vt = *(void***)viewer;
    ((void(__thiscall*)(void*, void*))vt[0x18 / 4])(viewer, v);
}

// @ 0x007d8180  (this is the IHandlerRC subobject of a cApp, so this = cApp + 4)
bool IHandlerRC::HandleMessage(int msg, void* data) {
    cApp* app = (cApp*)((char*)this - 4);
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

// @ 0x007d8060
bool cApp::Init() {
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

// @ 0x007d8470
bool cApp::SwitchMode() {
    int index = mModeIndex;
    if (index < 0 || index >= (int)((char*)mAppModesEnd - (char*)mAppModesBegin) / 0x18)
        return false;
    cAppModeInfo* info = mAppModesBegin + index;
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

// ---------------------------------------------------------------------------
// Small creature-ability command class (factory at 0x007d7ed0, size 0x28)
// ---------------------------------------------------------------------------
struct cAbilityCmd {
    void** mBaseVtbl;     // +0x00
    void** mAbilityVtbl;  // +0x04
    int    mUnk08;        // +0x08
    void*  mDesc;         // +0x0c
    void*  mIface;        // +0x10
    unsigned char mActive;// +0x14
    char   pad15[3];
    float  mx, my, mz;    // +0x18,+0x1c,+0x20
    int    mId;           // +0x24

    void Destroy();
    void SetIface(int, int, int);
    void Activate(int);
    void Deactivate(int);
    void SetTransform(void* xformA, const unsigned char* desc);
};

// @ 0x007d7ce0
bool __stdcall FilterAbilityType(int type, int, int) {
    switch (type) {
        case 4: return true;
        case 5: return true;
        default: return false;
    }
}

// @ 0x007d7d00  (destructor body: restore vtables and release member +0x10)
void cAbilityCmd::Destroy() {
    mBaseVtbl = (void**)0x01412458;
    mAbilityVtbl = (void**)0x01412454;
    if (mIface != 0) {
        void** vt = *(void***)mIface;
        ((void(__thiscall*)(void*))vt[1])(mIface);
    }
    mAbilityVtbl = (void**)0x013ef094;
    mBaseVtbl = (void**)0x013f21d4;
}

// @ 0x007d7d70
void cAbilityCmd::SetIface(int, int, int) {
    void* iface = Sub_67de00();                          // some manager
    void** vt = *(void***)iface;
    void* result = ((void*(__thiscall*)(void*))vt[0x9c / 4])(iface);
    void* old = mIface;
    if (result != old) {
        if (result != 0)
            ((void(__thiscall*)(void*))(*(void***)result)[0])(result);
        mIface = result;
        if (old != 0)
            ((void(__thiscall*)(void*))(*(void***)old)[1])(old);
    }
}

// @ 0x007d7dc0
void cAbilityCmd::Activate(int arg) {
    if (mActive == 0 && mIface != 0) {
        void* desc = mDesc;
        mActive = 1;
        float scale = *(float*)0x01488874;
        if (*(char*)((char*)desc + 0xc) == 4)
            scale = **(float**)((char*)desc + 0x40);
        void* v = *(void**)((char*)desc + 0x18);
        float ax = *(float*)v;
        float ay = *(float*)((char*)v + 4);
        float az = *(float*)((char*)v + 8);
        float px = mx;
        float py = my;
        float pz = mz;
        void** vt = *(void***)mIface;
        int r = ((int(__thiscall*)(void*, float*, float*, void*, float))
                 vt[0xc / 4])(mIface, &px, &ax, *(void**)((char*)desc + 0x2c), scale);
        mId = r;
    }
}

// @ 0x007d7e80
void cAbilityCmd::Deactivate(int) {
    if (mActive != 0) {
        mActive = 0;
        if (mId != -1) {
            void** vt = *(void***)mIface;
            ((void(__thiscall*)(void*, int))vt[0x14 / 4])(mIface, mId);
            mId = -1;
        }
    }
}

// @ 0x007d7ed0
cAbilityCmd* AbilityCmdNew(void* arg) {
    cAbilityCmd* p = (cAbilityCmd*)operator new[](0x28, "Swarm", 0, 0, 0, 0);
    if (p != 0) {
        p->mAbilityVtbl = (void**)0x013ef094;
        p->mUnk08 = 0;
        p->mBaseVtbl = (void**)0x01412458;
        p->mAbilityVtbl = (void**)0x01412454;
        p->mDesc = arg;
        p->mIface = 0;
        p->mActive = 0;
        p->mx = 0.0f;
        p->my = 0.0f;
        p->mz = 0.0f;
        p->mId = -1;
        return p;
    }
    return 0;
}

// @ 0x007d7f40  (static registration)
void AbilityRegister() {
    *(void**)0x01675ff8 = (void*)0x007d7ed0;
    *(void**)0x01675ff0 = 0;
}

// @ 0x007d7f60
void cAbilityCmd::SetTransform(void* xformA, const unsigned char* desc) {
    unsigned short flags = *(unsigned short*)desc;
    unsigned short modCount = *(unsigned short*)(desc + 2);
    float tx = *(float*)(desc + 4);
    float ty = *(float*)(desc + 8);
    float tz = *(float*)(desc + 0xc);
    float scale = *(float*)(desc + 0x10);
    float rot[9];
    Matrix3_Assign(rot, desc + 0x14);
    Sub_537f40(xformA);
    (void)flags; (void)modCount; (void)scale;
    if (mx != tx || my != ty || mz != tz) {
        mx = tx;
        my = ty;
        mz = tz;
        if (mId != -1) {
            float p[3];
            p[0] = mx; p[1] = my; p[2] = mz;
            void** vt = *(void***)mIface;
            ((void(__thiscall*)(void*, int, float*))vt[0x10 / 4])(mIface, mId, p);
        }
    }
}

// @ 0x007d8580  (destroy a vector-like owner: free range then release an object)
void __fastcall VectorOwnerDestroy(void** self) {
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

// ---------------------------------------------------------------------------
// SP::cGameModelEffect
// ---------------------------------------------------------------------------
struct cGameModelEffect {
    char   pad00[0xc];
    void*  mModelDesc;       // +0x0c
    void*  mUnk10;           // +0x10
    char   pad14[4];
    int    mUnk18;           // +0x18
    int    mUnk1c;           // +0x1c
    int    mUnk20;           // +0x20
    int    mUnk24;           // +0x24
    int    mUnk28;           // +0x28
    float  mUnk2c;           // +0x2c
    float  mUnk30;           // +0x30
    char   pad34[0xa];
    unsigned short mCount3e; // +0x3e
    char   pad40[0xc];
    float  mUnk4c;           // +0x4c
    char   pad50[0x54];
    void*  mParamsObj;       // +0xa4
    void*  mSplitManager;    // +0xa8
    char*  mVecB0;           // +0xac
    char*  mVecB4;           // +0xb0
    void*  mModelManager;    // +0xc0
    void*  mUnkC4;           // +0xc4

    bool HandleSplitCommand(int a, void* desc, int value, int index, int count);
    void Init(int a, void* desc, int value);
};

// @ 0x007d76d0
bool cGameModelEffect::HandleSplitCommand(int a, void* desc, int value, int index, int count) {
    char* rec = (char*)(index * 0x68 + *(int*)(*(int*)((char*)mModelDesc + 0x58)));
    unsigned char kind = (unsigned char)rec[0];
    if (kind == 0) {
        if (count < *(int*)(rec + 4))
            return false;
        void* obj = operator new[](0x28, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        if (obj != 0) {
            if (obj != 0)
                obj = Sub_7d6380(obj);
        }
        if (obj != 0)
            *(int*)((char*)obj + 4) += 1;
        Sub_4e0e80((char*)mParamsObj + 0xc, &obj);
        if (obj != 0) {
            int rc = *(int*)((char*)obj + 4) - 1;
            *(int*)((char*)obj + 4) = rc;
            if (rc == 0) {
                *(int*)((char*)obj + 4) = 1;
                ((void(__thiscall*)(void*))*(void**)*(void**)obj)(obj);
            }
        }
    } else if (kind == 1) {
        if (mSplitManager == 0) {
            void* mgr = operator new[](0x54, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
            if (mgr != 0)
                mgr = Sub_7d5d50(mgr);
            Sub_572680(&mSplitManager, mgr);
        }
        void* elem = operator new[](0x38, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        void* built = 0;
        if (elem != 0)
            built = Sub_7d6440(elem);
        if (built != 0)
            ((void(__thiscall*)(void*))*(void**)*(void**)built)(built);
        void* params = operator new[](0xd8, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        if (params != 0)
            params = Sub_7d55e0(params);
        if (value != 0)
            Sub_7d6b00(params, (void*)value);
        Sub_7d4620(params, 5);
        void** dvt = *(void***)desc;
        ((void(__thiscall*)(void*, int, int, int, int))dvt[0x70 / 4])(desc, 2, *(int*)(rec + 4), (int)mUnk10, (int)mUnk10);
        void* rec2 = Sub_7d5240(params);
        Sub_7d7000((char*)mSplitManager + 0xac, rec2);
        if (built != 0)
            ((void(__thiscall*)(void*))(*(void***)built)[0x38 / 4])(built);
        void* list = *(void**)(mVecB0 - 4);
        ((void(__thiscall*)(void*, void*, void*, void*))(*(void***)list)[0])(list, (void*)a, desc, params);
        void* list2 = *(void**)(mVecB0 - 4);
        ((void(__thiscall*)(void*, int))(*(void***)list2)[0x28 / 4])(list2, (int)(unsigned char)rec[5] /* placeholder */);
        if (built != 0)
            ((void(__thiscall*)(void*))(*(void***)built)[1])(built);
    } else if (kind == 2) {
        if (mSplitManager == 0) {
            void* mgr = operator new[](0x54, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
            if (mgr != 0)
                mgr = Sub_7d5d50(mgr);
            Sub_572680(&mSplitManager, mgr);
        }
        if (*(void**)(rec + 0x54) != rec + 0x50) {
            void* node = *(void**)(rec + 0x54);
            do {
                AddSplitInstanceRaw(mSplitManager, rec + 8, *(int*)((char*)node + 0x10), 2);
                node = RBTreeIncrement(node);
            } while (node != rec + 0x50);
            return true;
        }
    }
    return true;
}

// @ 0x007d7a10
void cGameModelEffect::Init(int a, void* desc, int value) {
    int descObj = *(int*)((char*)mModelDesc + 0x0c);
    (void)descObj;
    void* base = (void*)((char*)mModelDesc);
    int* vecBegin = (int*)((char*)base + 0x44);
    int* vecEnd = (int*)((char*)base + 0x48);
    if (vecBegin[0] != vecEnd[0]) {
        void* holder = operator new[](0x20, ALLOC_NAME, 0, 0, ALLOC_FILE, 0xd1);
        if (holder != 0) {
            *(int*)((char*)holder + 4) = 0;
            *(int*)((char*)holder + 8) = 4;
            *(int*)((char*)holder + 0xc) = 0;
            *(int*)((char*)holder + 0x10) = 0;
            *(int*)((char*)holder + 0x14) = 0;
            *(void**)holder = (void*)0x013ebc50;
        }
        void* old = mParamsObj;
        if (holder != old) {
            if (holder != 0)
                *(int*)((char*)holder + 4) += 1;
            mParamsObj = holder;
            if (old != 0) {
                int rc = *(int*)((char*)old + 4) - 1;
                *(int*)((char*)old + 4) = rc;
                if (rc == 0) {
                    *(int*)((char*)old + 4) = 1;
                    ((void(__thiscall*)(void*))*(void**)*(void**)old)(old);
                }
            }
        }
        int nDesc = (*(int*)((char*)base + 0x5c) - *(int*)((char*)base + 0x58)) / 0x68;
        int nCmd = (*(int*)((char*)base + 0x48) - *(int*)((char*)base + 0x44)) >> 3;
        int i = 0;
        for (int cmd = 0; cmd < nCmd; ++cmd) {
            while (i < nDesc && HandleSplitCommand(a, desc, value, i, cmd))
                ++i;
            int entry = *(int*)((char*)base + 0x44) + cmd * 8;
            void* comp = ((void*(__thiscall*)(void*, int, void*, void*))
                          (*(void***)desc)[0x74 / 4])(desc, 0x10, *(void**)(entry), mUnk10);
            void* made = Sub_7df780((char*)comp + 8);
            void* ref = (void*)Sub_79ab90((int)*(char*)(entry + 4), made, comp, (int)*(char*)(entry + 5));
            if (ref != 0)
                *(int*)((char*)ref + 4) += 1;
            void* pobj = mParamsObj;
            void** slot = *(void***)((char*)pobj + 0x10);
            if (slot < *(void***)((char*)pobj + 0x14)) {
                *(void***)((char*)pobj + 0x10) = slot + 1;
                if (slot != 0) *slot = ref;
            } else {
                Sub_4e3260(slot, &ref);
            }
            if (ref != 0) {
                int rc = *(int*)((char*)ref + 4) - 1;
                *(int*)((char*)ref + 4) = rc;
                if (rc == 0) {
                    *(int*)((char*)ref + 4) = 1;
                    ((void(__thiscall*)(void*))*(void**)*(void**)ref)(ref);
                }
            }
            ea_free(made);
        }
        for (; i < nDesc; ++i)
            HandleSplitCommand(a, desc, value, i, 0x7fffffff);
    }
    mUnk18 = *(int*)((char*)base + 0x24);
    mUnk1c = *(int*)((char*)base + 0x28);
    if (value != 0) {
        void* outPtr;
        int outCount;
        if (Sub_a826c0(6, &outPtr, &outCount)) {
            mUnk18 = *(int*)outPtr;
            if (outCount > 1)
                mUnk1c = *(int*)((char*)outPtr + 4);
        }
    }
    mUnk20 = *(int*)((char*)base + 0x14);
    mUnk24 = *(int*)((char*)base + 0x18);
    mUnk28 = *(int*)((char*)base + 0x1c);
    mUnk2c = *(float*)((char*)base + 0x20);
    float s = *(float*)((char*)base + 0x10);
    mUnk30 = s;
    mCount3e += 1;
    mUnk4c = s;
    void* mm = ModelManager();
    mModelManager = mm;
    int m = *(int*)((char*)base + 0x2c);
    if (m == 0)
        mUnkC4 = ((void*(__thiscall*)(void*))(*(void***)mm)[0x20 / 4])(mm);
    else
        mUnkC4 = ((void*(__thiscall*)(void*, int))(*(void***)mm)[0x1c / 4])(mm, m);
}
// --- equivalence checker address annotations
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
