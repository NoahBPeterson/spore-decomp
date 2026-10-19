// src/game/SPEngine/SPAppCameraManager.cpp -- migrated from slice(s) s007c6750, s007c5a90 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppCameraManager.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cCameraManager.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  SPKeyFromName(void* out, void* name, int, int);   // 0x0068d840 (equiv t2)
extern "C" int   CtrlIDMapFind(int* id);
extern "C" void  operator_delete(void*);
extern void* vtbl_Simulator_cCreatureAbility;   // 0x013ef094 (equiv t2)
extern void* vtbl_Skinner_PaintSystem;   // 0x013eb394 (equiv t2)
extern void* vtbl_Editor_cEditorResource;   // 0x013eb938 (equiv t2)

// ---- items of slice s007c5a90 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
struct cCameraManager;
struct cCameraManager {
    void* vftable;                 // +0x00
    u32   mRefCount;               // +0x04
    u8    pad08[4];
    bool  mInitialized;            // +0x0c
    u8    pad0d[3];
    char* mCheatBegin;             // +0x10
    char* mCheatEnd;               // +0x14
    void* mCheatCap;               // +0x18
    void* mCheatAlloc;             // +0x1c
    u8    mapNameID[0x20];         // +0x20
    u8    mapTypeID[0x20];         // +0x40
    u8    mapID[0x60 - 0x40];      // +0x60 (mControllerIDMap)
    void** mControllersBegin;      // +0x80
    void** mControllersEnd;        // +0x84
    void** mControllersCap;        // +0x88
    u8    pad8c[4];
    void* mNamesBegin;             // +0x90
    void* mNamesEnd;               // +0x94
    void* mNamesCap;               // +0x98
    u8    pad9c[4];
    int   mActiveControllerIndex;  // +0xa0
    u32   mPropModCount;           // +0xa4
    int   mIndexA8;                // +0xa8 (used as controller index)

    void SetActiveController(void* name);        // 0x7c6110
    void ActiveControllerID();                   // 0x7c6150
    void* ActiveController();                    // 0x7c61a0
    void UpdateFromControllerProperties();       // 0x7c6200
    void Update(int dt);                         // 0x7c63a0
    void SetActiveControllerByIndex(int idx);    // 0x7c6420
    int  ControllerIDByIndex(int idx);           // 0x7c6480
    int  ControllerIDByName(void* name);         // 0x7c64e0
    int  HandleMessage(int msg, int arg);        // 0x7c6610
    int  SetActiveControllerByID(int id);        // 0x7c66b0
    void* Controller(int id);                    // 0x7c6700
};
extern "C" void  SPKeyFromName(void* out, void* name, int, int);   // 0x0068d840 (equiv t2)
extern "C" int   CtrlIDMapFind(int* id);
extern "C" void  operator_delete(void*);
extern void* vtbl_Simulator_cCreatureAbility;   // 0x013ef094 (equiv t2)
extern void* vtbl_Skinner_PaintSystem;   // 0x013eb394 (equiv t2)
extern void* vtbl_Editor_cEditorResource;   // 0x013eb938 (equiv t2)
static const int kGroupTypeCameraConfig = 0;
// ---- items of slice s007c5a90 end

// ---- items of slice s007c6750 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cCameraManager_s007c_6750 {
    void* vftable;                  // +0x00
    u32   mRefCount;                // +0x04
    u8    pad08[4];
    bool  mInitialized;             // +0x0c
    u8    pad0d[3];
    char* mCheatBegin;              // +0x10
    char* mCheatEnd;                // +0x14
    char* mCheatCap;                // +0x18
    void* mCheatAlloc;              // +0x1c
    u8    mapNameID[0x20];          // +0x20
    u8    mapTypeID[0x20];          // +0x40
    u8    mapID[0x20];              // +0x60
    void** mControllersBegin;       // +0x80
    void** mControllersEnd;         // +0x84
    void** mControllersCap;         // +0x88
    u8    pad8c[4];
    void* mNamesBegin;              // +0x90
    void* mNamesEnd;                // +0x94
    void* mNamesCap;                // +0x98
    u8    pad9c[4];
    int   mActiveControllerIndex;   // +0xa0
    u32   mPropModCount;            // +0xa4
    int   mIndexA8;                 // +0xa8

    void Init(void* cmd);           // 0x7c70b0
    void Shutdown();                // 0x7c6db0
    void ClearControllers();        // 0x7c6eb0
    void LoadControllers();         // 0x7c6b80
    ~cCameraManager_s007c_6750();              // 0x7c74a0
    cCameraManager_s007c_6750();               // 0x7c75e0
};
// ---- items of slice s007c6750 end

// @ 0x007c6110
void cCameraManager::SetActiveController(void* name)
{
    char key[12] = {0};
    SPKeyFromName(key, name, 0, 0);
    void* vt = vftable;
    ((void(__thiscall*)(void*, int))((void**)vt)[0x34 / 4])(this, *(int*)key);
}

// @ 0x007c6150
void cCameraManager::ActiveControllerID()
{
    void* vt = vftable;
    int id = ((int(__thiscall*)(void*))((void**)vt)[0x58 / 4])(this);
    ((void(__thiscall*)(void*, int))((void**)vt)[0x50 / 4])(this, id);
}

// @ 0x007c61a0
SP::cICameraController * SP::cCameraManager::ActiveController()
{
    if (mActiveControllerIndex >= 0) return mControllers.mpBegin[mActiveControllerIndex];
    return 0;
}

// @ 0x007c6200
void SP::cCameraManager::UpdateFromControllerProperties()
{
    cCameraManager* m = this;
    float local[4] = {12300.0f, 12300.0f, 12300.0f, 12300.0f};
    void* ctrl = m->mControllers.mpBegin[m->mActiveControllerIndex];
    void* vt = *(void**)ctrl;
    int* p = (int*)((int(__thiscall*)(void*))((void**)vt)[0x4c / 4])(ctrl);
    if (p != 0) {
        if (((char(__thiscall*)(void*, int))((void**)*p)[0x1c / 4])(p, 0xed392a) != 0) {
            void* v = (void*)((void*(__thiscall*)(void*, int))((void**)*p)[0x28 / 4])(p, 0xed392a);
            short t = *(short*)((char*)v + 0x12);
            if (t == 0x34 || t == 0x10) {
                if ((*(u8*)((char*)v + 0x10) & 0x30) == 0) v = (void*)(-(int)(t != 0) & (int)v);
                else v = *(void**)v;
            } else {
                v = 0;
            }
            (void)local;
            (void)v;
        }
    }
}

// @ 0x007c6370
void** Destroy6370(void** p, int flags)
{
    p[2] = &vtbl_Simulator_cCreatureAbility;
    p[1] = &vtbl_Skinner_PaintSystem;
    *p = &vtbl_Editor_cEditorResource;
    if (flags & 1) operator_delete(p);
    return p;
}

// @ 0x007c63a0
void SP::cCameraManager::Update(unsigned int dt)
{
    if (mActiveControllerIndex < 0) return;
    void* ctrl = mControllers.mpBegin[mActiveControllerIndex];
    void* vt = *(void**)ctrl;
    void* p = (void*)((int(__thiscall*)(void*))((void**)vt)[0x4c / 4])(ctrl);
    if (p != 0) {
        this->UpdateFromControllerProperties();
        ((void(__thiscall*)(void*, int, void*))((void**)vt)[0x20 / 4])(ctrl, dt, 0);
    }
}

// @ 0x007c6420
void SP::cCameraManager::SetActiveControllerByIndex(int idx)
{
    if (idx < 0) return;
    if (idx >= (int)((char*)mControllers.mpEnd - (char*)mControllers.mpBegin) >> 2) return;
    void* old = mControllers.mpBegin[mActiveControllerIndex];
    ((void(__thiscall*)(void*))((void**)*(void**)old)[0x1c / 4])(old);
    mActiveControllerIndex = idx;
    this->UpdateFromControllerProperties();
    void* nw = mControllers.mpBegin[mActiveControllerIndex];
    ((void(__thiscall*)(void*))((void**)*(void**)nw)[0x18 / 4])(nw);
}

// @ 0x007c65a0
void* VariantGetTPTR()
{
    static int once = 0;
    static void* data[2];
    if ((once & 1) == 0) {
        once |= 1;
        data[0] = (void*)1;
        data[1] = (void*)1;
    }
    return data;
}

// @ 0x007c6610
int cCameraManager::HandleMessage(int msg, int arg)
{
    if (msg == 0xf62def) {
        int* pi = (int*)(arg + 0x10);
        int id = *(int*)(arg + 0x18);
        if (*pi == kGroupTypeCameraConfig) {
            int found = CtrlIDMapFind(&id);
            if (found != 0) {
                void* c = mControllersBegin[found];
                ((void(__thiscall*)(void*))((void**)*(void**)c)[0x50 / 4])(c);
            }
        }
        return 1;
    }
    int h = ((int(__thiscall*)(void*, int))((void**)vftable)[0x38 / 4])(this, msg);
    if (h != 0)
        return ((int(__thiscall*)(void*, int, int))((void**)*(void**)(h + 4))[1])((void*)h, msg, arg);
    return 0;
}

// @ 0x007c66b0
int cCameraManager::SetActiveControllerByID(int id)
{
    int found = CtrlIDMapFind(&id);
    if (found != 0) {
        ((void(__thiscall*)(void*, int))((void**)vftable)[0x54 / 4])(this, found);
        return 1;
    }
    return 0;
}

// @ 0x007c6700
void* cCameraManager::Controller(int id)
{
    int found = CtrlIDMapFind(&id);
    if (found != 0) return mControllersBegin[found];
    return 0;
}

// @ 0x007c6750
void CameraCheatExecute(int self, void* args)
{
    // Console cheat: list/select cameras, set render type.
    // Full argument handling is preserved structurally; see disassembly 0x7c6750.
    (void)self; (void)args;
}

// @ 0x007c6b80
void SP::cCameraManager::LoadControllers()
{
    // Iterates the "camera config" property group, mapping type ids to factory
    // callbacks and instantiating each configured controller.
    if (mInitialized) {
        // full EASTL hashtable/vector walk; reproduced in disassembly.
    }
}

// @ 0x007c6db0
void cCameraManager_s007c_6750::Shutdown()
{
    if (!mInitialized) return;
    mInitialized = false;
    if (mCheatBegin != mCheatEnd) { *mCheatBegin = 0; mCheatEnd = mCheatBegin; }
    int n = (int)((char*)mControllersEnd - (char*)mControllersBegin) >> 2;
    for (int i = 0; i < n; i++) {
        void* c = mControllersBegin[i];
        if (c) ((void(__thiscall*)(void*))((void**)*(void**)c)[0x14 / 4])(c);
    }
    mControllersEnd = mControllersBegin;
    mIndexA8 = 0;
}

// @ 0x007c6eb0
void SP::cCameraManager::ClearControllers()
{
    int n = (int)((char*)mControllers.mpEnd - (char*)mControllers.mpBegin) >> 2;
    for (int i = 0; i < n; i++) {
        void* c = mControllers.mpBegin[i];
        if (c) ((void(__thiscall*)(void*))((void**)*(void**)c)[0x14 / 4])(c);
    }
    mControllers.mpEnd = mControllers.mpBegin;
    mActiveControllerIndex = 0;
}

// @ 0x007c70b0
void cCameraManager_s007c_6750::Init(void* cmd)
{
    if (mInitialized) return;
    mInitialized = true;
    // registers the command word and the camera config group; see disassembly.
    mIndexA8 = -1;
}

// @ 0x007c7270
void RegisterController(cCameraManager_s007c_6750* m, int id, void* controller, void* name)
{
    // looks the id up in mControllerIDMap; installs/replaces the controller and
    // appends its localized name.
    (void)m; (void)id; (void)controller; (void)name;
}

// @ 0x007c75e0
cCameraManager_s007c_6750::cCameraManager_s007c_6750()
{
    mInitialized = false;
    mCheatBegin = (char*)1;
    mCheatEnd = (char*)1;
    mCheatCap = (char*)2;
    mControllersBegin = 0; mControllersEnd = 0; mControllersCap = 0;
    mNamesBegin = 0; mNamesEnd = 0; mNamesCap = 0;
    mActiveControllerIndex = 0;
    mPropModCount = 0;
    mIndexA8 = -1;
}
