// cCameraManager methods and related helpers, 0x007c5a90-0x007c6700.
// Reconstructed from retail disassembly + Ghidra decompile; layout from the
// 2008 dev PDB class SP::cCameraManager.

typedef unsigned char  u8;
typedef unsigned short u16;
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
    void Update(int dt);                         // 0x7c63a0
    void SetActiveControllerByIndex(int idx);    // 0x7c6420
    int  ControllerIDByIndex(int idx);           // 0x7c6480
    int  ControllerIDByName(void* name);         // 0x7c64e0
    int  HandleMessage(int msg, int arg);        // 0x7c6610
    int  SetActiveControllerByID(int id);        // 0x7c66b0
    void* Controller(int id);                    // 0x7c6700
};

struct FILE;
extern "C" FILE* fopen(const char*, const char*);
extern "C" int   fclose(FILE*);
extern "C" unsigned int fwrite(const void*, unsigned int, unsigned int, FILE*);

extern "C" void  SPKeyFromName(void* out, void* name, int, int);
extern "C" int   FUN_007c5820(void);
extern "C" int   FUN_007c5920(void);
extern "C" int   IsType1Or9(int);
extern "C" int   IsType9to11(int);
extern "C" int   CtrlIDMapFind(int* id);

extern "C" int   GetVersionExW(void*);
extern "C" int   GlobalMemoryStatusEx(void*);
extern "C" unsigned int GetSystemDirectoryW(wchar_t*, unsigned int);
extern "C" int   GetFileVersionInfoW(const wchar_t*, unsigned int, unsigned int, void*);
extern "C" int   VerQueryValueW(void*, const wchar_t*, void**, unsigned int*);
extern "C" void  operator_delete(void*);
extern "C" void* operator_new(unsigned int);

extern void* vtbl_Simulator_cCreatureAbility;
extern void* vtbl_Skinner_PaintSystem;
extern void* vtbl_Editor_cEditorResource;

static const int kGroupTypeCameraConfig = 0;

// ===========================================================================
// @ 0x007c5a90
int WriteScan(FILE* f, const u8* d, u8* base) {
    u32 px = (u32)(d[0x12] >> 3);
    u16 row = 0;
    if (*(const u16*)(d + 0xe) == 0) return 0;
    do {
        int cmp = FUN_007c5820();
        u8 n = (u8)FUN_007c5920();
        u8 tag = (u8)(n - 1);
        if (cmp == 1) tag |= 0x80;
        if (fwrite(&tag, 1, 1, f) != 1) return 3;
        u32 sz = px;
        if (cmp != 1) sz = (u32)n * px;
        if (fwrite(base + (u32)row * px, sz, 1, f) != 1) return 3;
        row = (u16)(row + n);
    } while (row < *(const u16*)(d + 0xe));
    return 0;
}

// ===========================================================================
// @ 0x007c5b90
u32 WriteImage(FILE* f, const u8* d) {
    u32 local;
    if (fwrite(d, 1, 1, f) != 1) return 3;
    if (d[1] != 0 && d[1] != 1) return 4;
    if (fwrite(d + 1, 1, 1, f) != 1) return 3;
    u8 fmt = d[2];
    if (fmt == 0) return 6;
    if (fmt != 1 && fmt != 2 && fmt != 3 && fmt != 9 && fmt != 10 && fmt != 11)
        return 5;
    if (fwrite(d + 2, 1, 1, f) != 1) return 3;

    int t = IsType1Or9((int)d);
    if (t != 0 && d[1] == 0) return 7;
    if (t == 0) {
        if (d[1] == 1) return 8;
    } else if (d[1] == 1) {
        if (*(const u16*)(d + 6) == 0) return 9;
        u8 bd = d[8];
        if (bd != 0x10 && bd != 0x18 && bd != 0x20) return 10;
    }

    local = *(const u16*)(d + 4);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    local = *(const u16*)(d + 6);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    if (fwrite(d + 8, 1, 1, f) != 1) return 3;
    local = *(const u16*)(d + 10);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    local = *(const u16*)(d + 0xc);
    if (fwrite(&local, 2, 1, f) != 1) return 3;

    if (*(const u16*)(d + 0xe) == 0 || *(const u16*)(d + 0x10) == 0) return 0xb;
    local = *(const u16*)(d + 0xe);
    if (fwrite(&local, 2, 1, f) != 1) return 3;
    local = *(const u16*)(d + 0x10);
    if (fwrite(&local, 2, 1, f) != 1) return 3;

    u8 bpp = d[0x12];
    if (bpp != 8) {
        if (bpp != 0x10 && bpp != 0x18 && bpp != 0x20) return 0xc;
        if (IsType1Or9((int)d) != 0) return 0xc;
    }
    if (fwrite(d + 0x12, 1, 1, f) != 1) return 3;
    if (fwrite(d + 0x13, 1, 1, f) != 1) return 3;

    if (d[0] != 0 && fwrite(d + 0x14, d[0], 1, f) != 1) return 3;
    if (d[1] == 1) {
        void* p = (void*)(((int)((u32)*(const u16*)(d + 4) * d[8]) >> 3) + *(const int*)(d + 0x18));
        u32 n = (u32)((int)((u32)*(const u16*)(d + 6) * d[8]) >> 3);
        if (fwrite(p, n, 1, f) != 1) return 3;
    }

    if (IsType9to11((int)d) == 0) {
        int n = (int)((u32)*(const u16*)(d + 0x10) * *(const u16*)(d + 0xe) * d[0x12]);
        if (fwrite(*(void**)(d + 0x1c), (u32)((n + (n >> 0x1f & 7)) >> 3), 1, f) != 1)
            return 3;
    } else {
        u32 i = 0;
        if (*(const u16*)(d + 0x10) != 0) {
            do {
                u32 r = WriteScan(f, d, 0);
                if (r != 0) return r;
                i++;
            } while ((u16)i < *(const u16*)(d + 0x10));
        }
    }
    static const char trailer[0x1a] = {0};
    if (fwrite(trailer, 0x1a, 1, f) != 1) return 3;
    return 0;
}

// ===========================================================================
// @ 0x007c5f00
int WriteImageFile(char* path, void* desc) {
    FILE* f = fopen(path, "wb");
    if (f == 0) return 1;
    int r = (int)WriteImage(f, (const u8*)desc);
    fclose(f);
    return r;
}

// ===========================================================================
// @ 0x007c5f50
unsigned int IsVistaKB940105Required() {
    struct { u32 dwLength; u32 a, b, c; wchar_t more[100]; } osvi;
    operator_new(0x114);
    osvi.dwLength = 0x114;
    unsigned int r = (unsigned int)GetVersionExW(&osvi);
    if (osvi.a == 6 && osvi.b == 0 && osvi.c < 0x1771) {
        struct { u32 dwLength; u32 pad; unsigned long long a, b, c, d; } ms;
        ms.dwLength = 0x40;
        GlobalMemoryStatusEx(&ms);
        if (((u32)(ms.c >> 32) == 0) && (u32)ms.c < 0xfffe0000) {
            wchar_t sysdir[260];
            GetSystemDirectoryW(sysdir, 0x208);
            const wchar_t* suffix = L"\\drivers\\dxgkrnl.sys";
            int n = 0; while (sysdir[n]) n++;
            for (int i = 0; suffix[i]; i++) sysdir[n + i] = suffix[i];
            unsigned char data[2048];
            if (GetFileVersionInfoW(sysdir, 0, 0x800, data) != 0) {
                void* val = 0; unsigned int len = 0;
                r = (unsigned int)VerQueryValueW(data, L"\\", &val, &len);
                if (r != 0 && len == 0x34 && *(int*)val == -0x110fb43) {
                    u32 ver = *(u32*)((char*)val + 8);
                    if (ver < 0x60001 &&
                        (ver != 0x60000 || *(u32*)((char*)val + 0xc) < 0x177050a8))
                        return 1;
                }
            }
        }
    }
    return r & 0xffffff00;
}

// ===========================================================================
// @ 0x007c6110
void cCameraManager::SetActiveController(void* name) {
    char key[12] = {0};
    SPKeyFromName(key, name, 0, 0);
    void* vt = vftable;
    ((void(__thiscall*)(void*, int))((void**)vt)[0x34 / 4])(this, *(int*)key);
}

// ===========================================================================
// @ 0x007c6150
void cCameraManager::ActiveControllerID() {
    void* vt = vftable;
    int id = ((int(__thiscall*)(void*))((void**)vt)[0x58 / 4])(this);
    ((void(__thiscall*)(void*, int))((void**)vt)[0x50 / 4])(this, id);
}

// ===========================================================================
// @ 0x007c61a0
void* cCameraManager::ActiveController() {
    if (mIndexA8 >= 0) return mControllersBegin[mIndexA8];
    return 0;
}

// ===========================================================================
// @ 0x007c6200
void UpdateFromControllerProperties(cCameraManager* m) {
    float local[4] = {12300.0f, 12300.0f, 12300.0f, 12300.0f};
    void* ctrl = m->mControllersBegin[m->mIndexA8];
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

// ===========================================================================
// @ 0x007c6370
void** Destroy6370(void** p, int flags) {
    p[2] = &vtbl_Simulator_cCreatureAbility;
    p[1] = &vtbl_Skinner_PaintSystem;
    *p = &vtbl_Editor_cEditorResource;
    if (flags & 1) operator_delete(p);
    return p;
}

// ===========================================================================
// @ 0x007c63a0
void cCameraManager::Update(int dt) {
    if (mIndexA8 < 0) return;
    void* ctrl = mControllersBegin[mIndexA8];
    void* vt = *(void**)ctrl;
    void* p = (void*)((int(__thiscall*)(void*))((void**)vt)[0x4c / 4])(ctrl);
    if (p != 0) {
        UpdateFromControllerProperties(this);
        ((void(__thiscall*)(void*, int, void*))((void**)vt)[0x20 / 4])(ctrl, dt, 0);
    }
}

// ===========================================================================
// @ 0x007c6420
void cCameraManager::SetActiveControllerByIndex(int idx) {
    if (idx < 0) return;
    if (idx >= (int)((char*)mControllersEnd - (char*)mControllersBegin) >> 2) return;
    void* old = mControllersBegin[mIndexA8];
    ((void(__thiscall*)(void*))((void**)*(void**)old)[0x1c / 4])(old);
    mIndexA8 = idx;
    UpdateFromControllerProperties(this);
    void* nw = mControllersBegin[mIndexA8];
    ((void(__thiscall*)(void*))((void**)*(void**)nw)[0x18 / 4])(nw);
}

// ===========================================================================
// @ 0x007c6480
int cCameraManager::ControllerIDByIndex(int idx) {
    return CtrlIDMapFind(&idx);
}

// ===========================================================================
// @ 0x007c64e0
int cCameraManager::ControllerIDByName(void* name) {
    (void)name;
    return 0;
}

// ===========================================================================
// @ 0x007c65a0
void* VariantGetTPTR() {
    static int once = 0;
    static void* data[2];
    if ((once & 1) == 0) {
        once |= 1;
        data[0] = (void*)1;
        data[1] = (void*)1;
    }
    return data;
}

// ===========================================================================
// @ 0x007c6610
int cCameraManager::HandleMessage(int msg, int arg) {
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

// ===========================================================================
// @ 0x007c66b0
int cCameraManager::SetActiveControllerByID(int id) {
    int found = CtrlIDMapFind(&id);
    if (found != 0) {
        ((void(__thiscall*)(void*, int))((void**)vftable)[0x54 / 4])(this, found);
        return 1;
    }
    return 0;
}

// ===========================================================================
// @ 0x007c6700
void* cCameraManager::Controller(int id) {
    int found = CtrlIDMapFind(&id);
    if (found != 0) return mControllersBegin[found];
    return 0;
}
