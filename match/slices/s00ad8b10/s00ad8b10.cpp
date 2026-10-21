// Slice s00ad8b10 -- SP UI/behavior state helpers, cViewer/state copy-assign,
// SpHash node insertion helpers and argument-script behavior-message builders.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// ------------------------------------------------------------------ data globals
extern const char  DAT_013f09b4[];   // "Simulator" (allocator name)
extern const char  DAT_013ebb38[];   // EASTL allocator.h path string
extern char        DAT_013ec468[];
extern const char  DAT_013f5f24[];   // "off"
extern const char  DAT_013f5f28[];   // (second off flag)
extern const char  DAT_0145b690[];   // "speech"
extern const char  DAT_0145b688[];   // "thought"
extern const char  DAT_0145b680[];   // "caption"
extern const char  DAT_0145b678[];   // "radio"
extern const char  DAT_0141249c[];   // "camera"
extern const char  DAT_01412cec[];   // "radius"
extern const char  DAT_0145b6a0[];   // "types"
extern const char  DAT_0145b698[];   // "actors"
extern const char  DAT_0145b004[];   // "switchToExitState"

extern void*       PTR_vtbl_RefBaseA22;   // 0x013eb90c ??_7RefBaseA22@@6B@
extern void*       PTR_vtbl_BehaviorMsg;  // 0x013eb844 (derived vtable)

// ------------------------------------------------------------------ external helpers
void* EAAllocate(u32 size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  operator delete(void* p);

void* SP_MessageServer(void);     // 0x0067dcc0
void* SP_App(void);               // 0x0067dd10
void* SP_EffectsManager(void);    // 0x0067ddd0
void* SP_MovieSystem(void);       // 0x0067cb10
void* SP_BehaviorManager(void);   // 0x00b3d260
void* GetTriggerMgr(void);        // 0x00b3d4d0
void* EA_Audio_GetSystemAT(void); // 0x00a206f0

bool  FUN_00685520(int a);                    // 0x00685520  world flag test
void  FUN_00921440(void* out, int n, int cap, int one);  // 0x00921440
void  FUN_00ea97d0(int n);                    // 0x00ea97d0
void  FUN_00b3f1b0(int n);                    // 0x00b3f1b0
void  FUN_00b3f4c0();                         // (placeholder, unused)
u32   FUN_00ad7200(const char* s);            // 0x00ad7200 type hash
void* FUN_00ad81b0(void* a, void* b, void* c, void* d); // 0x00ad81b0 remove_copy_if
u32   FUN_00932e80(const char* s, u32 hash, int b);     // 0x00932e80 FNV1_String8
void* FUN_007e4190(void* args, void* msg, int b);       // 0x007e4190 cAppState::AddMessage

void  SPUIHelpers_BeginModal(void* a, int b, int c);    // 0x008099a0
void  SPUIHelpers_EndModal(void* a, int b, int c);      // 0x00809c50
void  SP_cSPUISpace_KillSetiEffects(u32 id, void* a);   // 0x00435ed0
void  FUN_00832d50(void* a, float f, int b, int c, int d); // 0x00832d50 cSPUISubtitles::Set

// ------------------------------------------------------------------ thiscall helper types
struct CArgs {                                   // EA::ArgScript::cArguments
    char** MainArguments(int* out, int a, int b);            // 0x00838020
    char** OptionArguments(const char* name, int a);         // 0x00838330
    char** OptionArgumentsN(const char* name, int* out, int a, int b); // 0x00838130
    char   HasFlag(const char* name);                        // 0x008380b0
};

struct SPUILayout {                              // cSPUILayout
    char SetVisibility(char v);                             // 0x00810590
};

struct Viewer {                                  // SP::cViewer
    char Copy(void* src, char b, void* c);                  // 0x007c50b0
};

typedef void (__thiscall *VFn0)(void*);
typedef u32  (__thiscall *VFnU)(void*);
typedef void (__thiscall *VFnII)(void*, int, int);
typedef char (__thiscall *VFnC)(void*);
typedef int  (__thiscall *VFnIII)(void*, int, int, int);

// ------------------------------------------------------------------ functions

// @ 0x00ad8b10
// ------------------------------------------------------------------ thiscall shims
struct Self {
    void FUN_00ad8b10(char a, int b);
    void* FUN_00ad8e80(void* other);
    void FUN_00ad8f20(void* name);
    void FUN_00ad8f90();
    void* FUN_00ad9010(void* other);
    void FUN_00ad9090(void* out, void* key);
    void FUN_00ad9160();
    char* FUN_00ad9200(void* out, void* key);
    void FUN_00ad9370(void* out, void* key);
    char FUN_00ad94c0(int key);
    char FUN_00ad9520(int a, char* msg);
    void FUN_00ad95c0(CArgs* ca);
    void FUN_00ad97c0(CArgs* ca);
    void FUN_00ad9860(CArgs* ca);
};

// ------------------------------------------------------------------ functions

void Self::FUN_00ad8b10(char a, int b)
{
    void* self = this;
    char* s = (char*)self;
    (void)b;
    char* vp = *(char**)(s + 0x140);
    void* vt = *(void**)vp;
    u32   n  = (*(u32(__thiscall**)(void*))((char*)vt + 0x3c))(vp);
    u32   r  = (*(u32(__thiscall**)(void*, u32))((char*)vt + 0x38))(vp, n);
    *(u32*)(s + 0x14c) = r;

    {
        void* ms = SP_MessageServer();
        (*(VFnIII*)((char*)*(void**)ms + 0x14))(ms, (int)0xd33b6aa2, 0, 0);
    }
    s[0x2a] = 0;

    {
        void* app = SP_App();
        *(u32*)(s + 0x158) = (*(VFnU*)((char*)*(void**)app + 0x38))(app);
    }
    void* o;
    o = *(void**)((char*)*(void**)(s + 0x44) + 0x14);
    (*(void(__thiscall**)(void*, void*))((char*)*(void**)o + 0x80))(o, DAT_013ec468);
    o = *(void**)((char*)*(void**)(s + 0x44) + 0x14);
    (*(VFnII*)((char*)*(void**)o + 0x7c))(o, 1, 0);
    {
        void* ui = *(void**)(s + 0x44);
        if (FUN_00685520(2)) {
            o = *(void**)((char*)ui + 0x18);
            (*(void(__thiscall**)(void*, void*))((char*)*(void**)o + 0x80))(o, DAT_013ec468);
        }
    }
    {
        void* ui = *(void**)(s + 0x44);
        if (FUN_00685520(2)) {
            o = *(void**)((char*)ui + 0x18);
            (*(VFnII*)((char*)*(void**)o + 0x7c))(o, 1, 0);
        }
    }
    o = *(void**)((char*)*(void**)(s + 0x44) + 0x1c);
    (*(VFnII*)((char*)*(void**)o + 0x7c))(o, 1, 0);
    {
        float one = 1.0f;
        o = *(void**)((char*)*(void**)(s + 0x44) + 0x50);
        FUN_00832d50(o, one, 0, 1, 0);
    }
    {
        void* g = *(void**)(s + 0x16c);
        if (g != 0) {
            *(u32*)(s + 0x16c) = 0;
            (*(VFn0*)((char*)*(void**)g + 4))(g);
        }
    }
    {
        void* h = *(void**)(s + 0x168);
        if (h != 0) {
            (*(VFn0*)((char*)*(void**)h + 0x58))(h);
        }
    }
    {
        char* ui = *(char**)(s + 0x44);
        s[0x3d] = 0;
        s[0x15e] = a;
        if (a != 0) {
            SPUIHelpers_BeginModal(*(void**)(ui + 0x4c), 0, 0);
            ui[0x54] = 1;
        } else {
            if (ui[0x54] != 0) {
                SPUIHelpers_EndModal(*(void**)(ui + 0x4c), 0, 0);
                ui[0x54] = 0;
            }
        }
    }
    {
        void* ui = *(void**)(s + 0x44);
        void* o34 = *(void**)((char*)ui + 0x34);
        if ((*(VFnC*)((char*)*(void**)o34 + 0x28))(o34) & 1) {
            ui = *(void**)(s + 0x44);
            void* o30 = *(void**)((char*)ui + 0x30);
            (*(VFnII*)((char*)*(void**)o30 + 0x7c))(o30, 1, 0);
            o34 = *(void**)((char*)ui + 0x34);
            (*(VFnII*)((char*)*(void**)o34 + 0x7c))(o34, 1, 0);
        }
    }
    {
        void* ui = *(void**)(s + 0x44);
        if (FUN_00685520(2)) {
            void* o38 = *(void**)((char*)ui + 0x38);
            if ((*(VFnC*)((char*)*(void**)o38 + 0x28))(o38) & 1) {
                ui = *(void**)(s + 0x44);
                if (FUN_00685520(2)) {
                    void* o30 = *(void**)((char*)ui + 0x30);
                    (*(VFnII*)((char*)*(void**)o30 + 0x7c))(o30, 1, 0);
                    void* o34 = *(void**)((char*)ui + 0x34);
                    (*(VFnII*)((char*)*(void**)o34 + 0x7c))(o34, 1, 0);
                    o38 = *(void**)((char*)ui + 0x38);
                    (*(VFnII*)((char*)*(void**)o38 + 0x7c))(o38, 1, 0);
                }
            }
        }
    }
    {
        void* ui = *(void**)(s + 0x44);
        if (FUN_00685520(2)) {
            void* o3c = *(void**)((char*)ui + 0x3c);
            if ((*(VFnC*)((char*)*(void**)o3c + 0x28))(o3c) & 1) {
                ui = *(void**)(s + 0x44);
                if (FUN_00685520(2)) {
                    void* o30 = *(void**)((char*)ui + 0x30);
                    (*(VFnII*)((char*)*(void**)o30 + 0x7c))(o30, 1, 0);
                    void* o34 = *(void**)((char*)ui + 0x34);
                    (*(VFnII*)((char*)*(void**)o34 + 0x7c))(o34, 1, 0);
                    o3c = *(void**)((char*)ui + 0x3c);
                    (*(VFnII*)((char*)*(void**)o3c + 0x7c))(o3c, 1, 0);
                }
            }
        }
    }
    {
        void* ui = *(void**)(s + 0x44);
        if (FUN_00685520(2)) {
            void* o40 = *(void**)((char*)ui + 0x40);
            if ((*(VFnC*)((char*)*(void**)o40 + 0x28))(o40) & 1) {
                ui = *(void**)(s + 0x44);
                if (FUN_00685520(2)) {
                    void* o30 = *(void**)((char*)ui + 0x30);
                    (*(VFnII*)((char*)*(void**)o30 + 0x7c))(o30, 1, 0);
                    void* o34 = *(void**)((char*)ui + 0x34);
                    (*(VFnII*)((char*)*(void**)o34 + 0x7c))(o34, 1, 0);
                    o40 = *(void**)((char*)ui + 0x40);
                    (*(VFnII*)((char*)*(void**)o40 + 0x7c))(o40, 1, 0);
                }
            }
        }
    }
    {
        void* ui = *(void**)(s + 0x44);
        if (FUN_00685520(2)) {
            void* o44 = *(void**)((char*)ui + 0x44);
            if ((*(VFnC*)((char*)*(void**)o44 + 0x28))(o44) & 1) {
                ui = *(void**)(s + 0x44);
                if (FUN_00685520(2)) {
                    void* o30 = *(void**)((char*)ui + 0x30);
                    (*(VFnII*)((char*)*(void**)o30 + 0x7c))(o30, 1, 0);
                    void* o34 = *(void**)((char*)ui + 0x34);
                    (*(VFnII*)((char*)*(void**)o34 + 0x7c))(o34, 1, 0);
                    o44 = *(void**)((char*)ui + 0x44);
                    (*(VFnII*)((char*)*(void**)o44 + 0x7c))(o44, 1, 0);
                }
            }
        }
    }
    {
        o = *(void**)((char*)*(void**)(s + 0x44) + 0x24);
        (*(VFnII*)((char*)*(void**)o + 0x7c))(o, 1, 1);
    }
    {
        void* ui = *(void**)(s + 0x44);
        void* o20 = *(void**)((char*)ui + 0x20);
        (*(VFnII*)((char*)*(void**)o20 + 0x7c))(o20, 1, 0);
        void* o2c = *(void**)((char*)ui + 0x2c);
        (*(VFnII*)((char*)*(void**)o2c + 0x7c))(o2c, 1, 0);
    }
    {
        void* ui = *(void**)(s + 0x44);
        void* o28 = *(void**)((char*)ui + 0x28);
        (*(VFnII*)((char*)*(void**)o28 + 0x7c))(o28, 1, 0);
        void* o2c = *(void**)((char*)ui + 0x2c);
        (*(VFnII*)((char*)*(void**)o2c + 0x7c))(o2c, 1, 0);
    }
    {
        o = *(void**)((char*)*(void**)(s + 0x44) + 0x48);
        (*(VFnII*)((char*)*(void**)o + 0x7c))(o, 1, 0);
    }
    {
        void* lay = *(void**)((char*)*(void**)(s + 0x44) + 0x10);
        ((SPUILayout*)lay)->SetVisibility(1);
    }
    {
        void* app = SP_App();
        void* src = (*(void*(__thiscall**)(void*, int, int))((char*)*(void**)app + 0x58))(app, 0, 0);
        ((Viewer*)*(void**)(s + 0x40))->Copy(src, 0, 0);
    }
    {
        void* bm = SP_BehaviorManager();
        (*(VFn0*)((char*)*(void**)bm + 0x28))(bm);
    }
    *(u32*)(s + 0x160) = 0;
}

// @ 0x00ad8e80  cViewer/state copy-assign (refcounted ptr at +0xc, POD tail)
void* Self::FUN_00ad8e80(void* other)
{
    void* self = this;
    char* s = (char*)self;
    char* o = (char*)other;
    void* a = *(void**)(o + 0xc);
    void* b = *(void**)(s + 0xc);
    if (a != b) {
        if (a != 0) (*(VFn0*)((char*)*(void**)a + 0))(a);
        *(void**)(s + 0xc) = a;
        if (b != 0) (*(VFn0*)((char*)*(void**)b + 4))(b);
    }
    *(u32*)(s + 0x10) = *(u32*)(o + 0x10);
    *(u32*)(s + 0x14) = *(u32*)(o + 0x14);
    *(u32*)(s + 0x18) = *(u32*)(o + 0x18);
    *(u32*)(s + 0x1c) = *(u32*)(o + 0x1c);
    *(u32*)(s + 0x20) = *(u32*)(o + 0x20);
    *(u32*)(s + 0x24) = *(u32*)(o + 0x24);
    *(u8*)(s + 0x28) = *(u8*)(o + 0x28);
    *(u8*)(s + 0x29) = *(u8*)(o + 0x29);
    *(u8*)(s + 0x2a) = *(u8*)(o + 0x2a);
    *(u8*)(s + 0x2b) = *(u8*)(o + 0x2b);
    *(u8*)(s + 0x2c) = *(u8*)(o + 0x2c);
    *(u8*)(s + 0x2d) = *(u8*)(o + 0x2d);
    *(u8*)(s + 0x2e) = *(u8*)(o + 0x2e);
    *(u32*)(s + 0x30) = *(u32*)(o + 0x30);
    return self;
}

// @ 0x00ad8f20  (re)create the named effect on the effects manager
void Self::FUN_00ad8f20(void* name)
{
    void* self = this;
    char* s = (char*)self;
    void* em = SP_EffectsManager();
    if (em == 0) return;

    char* slot = s + 0x164;
    void* old = *(void**)slot;
    if (old != 0) {
        *(u32*)slot = 0;
        (*(VFn0*)((char*)*(void**)old + 4))(old);
    }
    char ok = (*(char(__thiscall**)(void*, void*, int, void*))((char*)*(void**)em + 0x2c))(em, name, 0, slot);
    if (ok != 0) {
        void* eff = *(void**)slot;
        (*(void(__thiscall**)(void*, int))((char*)*(void**)eff + 8))(eff, 0);
        void* ms = SP_MessageServer();
        (*(VFnIII*)((char*)*(void**)ms + 0x14))(ms, (int)0x5b07bda, 0, 0);
    }
}

// @ 0x00ad8f90  leave the current app/sim state, enter exit state
void Self::FUN_00ad8f90()
{
    void* self = this;
    char* s = (char*)self;
    if (s[0x3a] != 0) {
        char* ui = *(char**)(s + 0x44);
        s[0x38] = 0;
        s[0x3a] = 0;
        s[0x3b] = 0;
        s[0x3c] = 0;
        if (s[0x15e] != 0) {
            SPUIHelpers_BeginModal(*(void**)(ui + 0x4c), 0, 0);
            ui[0x54] = 1;
        } else {
            if (ui[0x54] != 0) {
                SPUIHelpers_EndModal(*(void**)(ui + 0x4c), 0, 0);
                ui[0x54] = 0;
            }
        }
        {
            void* lay = *(void**)((char*)*(void**)(s + 0x44) + 0x10);
            ((SPUILayout*)lay)->SetVisibility(1);
        }
    }
    {
        char* o = *(char**)(s + 0x140);
        *(u32*)(s + 0x150) = (*(u32(__thiscall**)(char*, const char*))((char*)*(void**)o + 0x38))(o, DAT_0145b004);
    }
    s[0x15d] = 1;
    s[0x3d] = 1;
}

// @ 0x00ad9010  copy-assign (11 dwords, refcounted ptr at +0x2c)
void* Self::FUN_00ad9010(void* other)
{
    void* self = this;
    char* s = (char*)self;
    char* o = (char*)other;
    *(u32*)(s + 0x00) = *(u32*)(o + 0x00);
    *(u32*)(s + 0x04) = *(u32*)(o + 0x04);
    *(u32*)(s + 0x08) = *(u32*)(o + 0x08);
    *(u32*)(s + 0x0c) = *(u32*)(o + 0x0c);
    *(u32*)(s + 0x10) = *(u32*)(o + 0x10);
    *(u32*)(s + 0x14) = *(u32*)(o + 0x14);
    *(u32*)(s + 0x18) = *(u32*)(o + 0x18);
    *(float*)(s + 0x1c) = *(float*)(o + 0x1c);
    *(float*)(s + 0x20) = *(float*)(o + 0x20);
    *(float*)(s + 0x24) = *(float*)(o + 0x24);
    *(float*)(s + 0x28) = *(float*)(o + 0x28);
    void* a = *(void**)(o + 0x2c);
    void* b = *(void**)(s + 0x2c);
    if (a != b) {
        if (a != 0) (*(VFn0*)((char*)*(void**)a + 0xbc))(a);
        *(void**)(s + 0x2c) = a;
        if (b != 0) (*(VFn0*)((char*)*(void**)b + 0xc0))(b);
    }
    return self;
}

// @ 0x00ad9090  SpHash find-or-insert helper (0xc-byte nodes, refcounted +4)
void Self::FUN_00ad9090(void* out, void* key)
{
    void* self = this;
    char* s = (char*)self;
    char local[4];
    int  cap;

    FUN_00921440(local, *(int*)(s + 8), *(int*)(s + 0xc), 1);
    if (local[0] != 0) {
        FUN_00b3f1b0(cap);
    }

    u32 bucket = *(u32*)key % *(u32*)(s + 8);

    char* node = (char*)EAAllocate(0xc, DAT_013f09b4, 0, 0, DAT_013ebb38, 0xd1);
    if (node != 0) {
        *(u32*)(node + 0) = *(u32*)key;
        void* p = *(void**)((char*)key + 4);
        *(void**)(node + 4) = p;
        if (p != 0) (*(VFn0)*(void**)p)(p);
    }
    *(u32*)(node + 8) = 0;

    u32   idx  = bucket * 4;
    char* base = *(char**)(s + 4);
    char* head = *(char**)(base + idx);
    char* cur  = head;
    if (cur != 0) {
        while (*(u32*)cur != *(u32*)key) {
            cur = *(char**)(cur + 8);
            if (cur == 0) goto notfound;
        }
        *(u32*)(node + 8) = *(u32*)(cur + 8);
        *(char**)(cur + 8) = node;
        goto done;
    }
notfound:
    *(u32*)(node + 8) = (u32)(size_t)head;
    *(char**)(base + idx) = node;
done:
    ++*(u32*)(s + 0xc);
    *(char**)out = node;
    *(char**)((char*)out + 4) = base + idx;
}

// @ 0x00ad9160  SpHash destroy: release each bucket node, then free the array
void Self::FUN_00ad9160()
{
    void* self = this;
    char* s = (char*)self;
    char* begin = *(char**)s;
    char* end   = *(char**)(s + 4);
    for (char* p = begin; p < end; p += 4) {
        void* v = *(void**)p;
        if (v != 0) {
            void* t = (char*)v + 8;
            (*(VFn0*)((char*)*(void**)t + 4))(t);
        }
    }
    void* b = *(void**)s;
    if (b != 0 && ((int*)b)[-1] != 0)
        operator delete(b);
}

// @ 0x00ad9200  SpHash insert helper (0x10-byte nodes, POD payload)
char* Self::FUN_00ad9200(void* out, void* key)
{
    void* self = this;
    char* s = (char*)self;
    char local[4];
    int  cap;

    FUN_00921440(local, *(int*)(s + 8), *(int*)(s + 0xc), 1);
    if (local[0] != 0) {
        FUN_00b3f1b0(cap);
    }

    u32 bucket = *(u32*)key % *(u32*)(s + 8);

    char* node = (char*)EAAllocate(0x10, DAT_013f09b4, 0, 0, DAT_013ebb38, 0xd1);
    if (node != 0) {
        *(u32*)(node + 0) = *(u32*)key;
        *(u32*)(node + 4) = *(u32*)((char*)key + 4);
        *(u32*)(node + 8) = *(u32*)((char*)key + 8);
    }
    *(u32*)(node + 0xc) = 0;

    u32   idx  = bucket * 4;
    char* base = *(char**)(s + 4);
    char* head = *(char**)(base + idx);
    char* cur  = head;
    if (cur != 0) {
        while (*(u32*)cur != *(u32*)key) {
            cur = *(char**)(cur + 0xc);
            if (cur == 0) goto notfound;
        }
        *(u32*)(node + 0xc) = *(u32*)(cur + 0xc);
        *(char**)(cur + 0xc) = node;
        goto done;
    }
notfound:
    *(u32*)(node + 0xc) = (u32)(size_t)head;
    *(char**)(base + idx) = node;
done:
    ++*(u32*)(s + 0xc);
    *(char**)out = node;
    *(char**)((char*)out + 4) = base + idx;
    return (char*)out;
}

// @ 0x00ad9370  SpHash::operator[]: find-or-insert {node, bucketPtr, inserted}
void Self::FUN_00ad9370(void* out, void* key)
{
    void* self = this;
    char* s = (char*)self;
    u32   k = *(u32*)key;
    u32   bucket = k % *(u32*)(s + 8);
    char* base = *(char**)(s + 4);
    char* bp   = base + bucket * 4;
    char* cur  = *(char**)bp;
    while (cur != 0) {
        if (k == *(u32*)cur) {
            *(char**)out = cur;
            *(char**)((char*)out + 4) = bp;
            *((char*)out + 8) = 0;
            return;
        }
        cur = *(char**)(cur + 0x10);
    }

    char local[4];
    FUN_00921440(local, *(int*)(s + 8), *(int*)(s + 0xc), 1);

    char* node = (char*)EAAllocate(0x14, DAT_013f09b4, 0, 0, DAT_013ebb38, 0xd1);
    if (node != 0) {
        *(u32*)(node + 0) = *(u32*)key;
        *(u32*)(node + 4) = *(u32*)((char*)key + 4);
        *(u32*)(node + 8) = *(u32*)((char*)key + 8);
        *(u32*)(node + 0xc) = *(u32*)((char*)key + 0xc);
    }
    *(u32*)(node + 0x10) = 0;

    if (local[0] != 0) {
        u32 nb = k % (u32)*(int*)(local + 0);
        FUN_00ea97d0(*(int*)(local + 0));
        bucket = nb;
    }

    base = *(char**)(s + 4);
    bp   = base + bucket * 4;
    node = node;
    *(u32*)(node + 0x10) = *(u32*)bp;
    *(char**)bp = node;

    ++*(u32*)(s + 0xc);
    *(char**)out = node;
    *((char*)out + 8) = 1;
    *(char**)((char*)out + 4) = base + bucket * 4;
}

// @ 0x00ad9470  remove_copy_if front-end over a 4-byte-stride range
void* FUN_00ad9470(void** first, void** last, char (*pred)(void*))
{
    void** f = first;
    for (;;) {
        if (f == last) return f;
        if (pred(*f) != 0) break;
        ++f;
    }
    if (f == last) return f;
    return FUN_00ad81b0(f + 1, last, f, (void*)pred);
}

// @ 0x00ad94c0  SpHash lookup by key at node+0x30
char Self::FUN_00ad94c0(int key)
{
    void* self = this;
    char* s = (char*)self;
    u32* blk = *(u32**)(s + 0x14);
    u32  e = *blk;
    if (e == 0) {
        do { ++blk; e = *blk; } while (e == 0);
    }
    for (;;) {
        if (e == *(u32*)(*(int*)(s + 0x14) + *(int*)(s + 0x18) * 4)) return 0;
        if (*(int*)((size_t)e + 0x30) == key) break;
        e = *(u32*)((size_t)e + 0x34);
        while (e == 0) {
            ++blk;
            e = *blk;
        }
    }
    return 1;
}

// @ 0x00ad9520  behavior-message handler for trigger/UI state transitions
char Self::FUN_00ad9520(int a, char* msg)
{
    void* self = this;
    (void)a;
    int id = *(int*)(msg + 0xc);
    if (id != -0xe) {
        if (id != 0x445c99d && id != 0x62ef353) return 0;
        if (*(int*)(msg + 8) == 0x287259f6) {
            void* au = EA_Audio_GetSystemAT();
            if (au != 0) {
                (*(VFn0*)((char*)*(void**)au + 0x20))(au);
            }
            SP_cSPUISpace_KillSetiEffects(0xdb42c11a, 0);
            void* ms = SP_MessageServer();
            (*(VFnIII*)((char*)*(void**)ms + 0x14))(ms, 0x445f729, 0, 0);
        }
        return 1;
    }
    if (*(int*)(msg + 8) == 0x287259f6) {
        void* t = GetTriggerMgr();
        if (*(char*)((char*)t + 0x2b) == 0) {
            void* t2 = GetTriggerMgr();
            ((Self*)t2)->FUN_00ad8f90();
            void* mv = SP_MovieSystem();
            (*(VFn0*)((char*)*(void**)mv + 0x24))(mv);
        }
    }
    return 1;
}

// @ 0x00ad95c0  "narration/speech" behavior message builder
void Self::FUN_00ad95c0(CArgs* ca)
{
    void* self = this;
    char* s = (char*)self;
    char* msg = (char*)EAAllocate(0x40, DAT_013f09b4, 0, 0, DAT_013ebb38, 0xd1);
    if (msg != 0) {
        *(u32*)(msg + 0x30) = 0;
        *(void**)(msg + 0x00) = (void*)&PTR_vtbl_RefBaseA22;
        *(int*)(msg + 4) = 0;
        *(void**)(msg + 0x00) = (void*)&PTR_vtbl_BehaviorMsg;
        *(u32*)(msg + 0x38) = 0;
        (*(VFn0*)((char*)*(void**)msg + 4))(msg);
    }
    {
        int n = 0;
        if (ca->HasFlag(DAT_013f5f24)) {
            *(u32*)(msg + 0x30) = 0x4448cb4;
        } else if (ca->HasFlag(DAT_013f5f28)) {
            *(u32*)(msg + 0x30) = 0x4448b7a;
        }
        if (ca->HasFlag(DAT_0145b690))      n = 1;
        else if (ca->HasFlag(DAT_0145b688)) n = 2;
        else if (ca->HasFlag(DAT_0145b680)) n = 3;
        else if (ca->HasFlag(DAT_0145b678)) n = 4;
        *(int*)(msg + 8) = n;
    }
    FUN_007e4190(*(void**)(s + 0xc), msg, 0);
    (*(VFn0*)((char*)*(void**)msg + 8))(msg);
}

// @ 0x00ad97c0  "cinematic/off" behavior message builder
void Self::FUN_00ad97c0(CArgs* ca)
{
    void* self = this;
    char* s = (char*)self;
    char* msg = (char*)EAAllocate(0x40, DAT_013f09b4, 0, 0, DAT_013ebb38, 0xd1);
    if (msg != 0) {
        *(u32*)(msg + 0x30) = 0;
        *(void**)(msg + 0x00) = (void*)&PTR_vtbl_RefBaseA22;
        *(int*)(msg + 4) = 0;
        *(u32*)(msg + 0x38) = 0;
        *(void**)(msg + 0x00) = (void*)&PTR_vtbl_BehaviorMsg;
        (*(VFn0*)((char*)*(void**)msg + 4))(msg);
    }
    *(u32*)(msg + 0x30) = 0x5dbc9c4;
    if (ca->HasFlag(DAT_013f5f24)) {
        *(u32*)(msg + 0x30) = 0x5dbc9c8;
    } else if (ca->HasFlag(DAT_013f5f28)) {
        *(u32*)(msg + 0x30) = 0x5dbc9c4;
    }
    FUN_007e4190(*(void**)(s + 0xc), msg, 0);
    (*(VFn0*)((char*)*(void**)msg + 8))(msg);
}

// @ 0x00ad9860  behavior message builder with positional/radius/type/actor args
void Self::FUN_00ad9860(CArgs* ca)
{
    void* self = this;
    char* s = (char*)self;
    char* msg = (char*)EAAllocate(0x40, DAT_013f09b4, 0, 0, DAT_013ebb38, 0xd1);
    if (msg != 0) {
        *(u32*)(msg + 0x30) = 0;
        *(void**)(msg + 0x00) = (void*)&PTR_vtbl_RefBaseA22;
        *(int*)(msg + 4) = 0;
        *(void**)(msg + 0x00) = (void*)&PTR_vtbl_BehaviorMsg;
        *(u32*)(msg + 0x38) = 0;
        (*(VFn0*)((char*)*(void**)msg + 4))(msg);
    }
    *(u32*)(msg + 0x30) = 0x636bf2d;

    int   n = 0;
    char** av = ca->MainArguments(&n, 0, 1000);
    if (n < 1) {
        (*(VFn0*)((char*)*(void**)msg + 8))(msg);
        return;
    }
    (*(void(__thiscall**)(void*, void*))((char*)*(void**)*(void**)(s + 4) + 0x94))(*(void**)(s + 4), av[0]);

    bool  cam = ca->HasFlag(DAT_0141249c) != 0;
    float radius = 0.0f;
    {
        char** rv = ca->OptionArguments(DAT_01412cec, 1);
        if (rv != 0) {
            float f = (*(float(__thiscall**)(void*, void*))((char*)*(void**)*(void**)(s + 4) + 0x98))(*(void**)(s + 4), rv[0]);
            radius = f;
        }
    }
    u32 types = 0;
    {
        int tn = 0;
        char** tv = ca->OptionArgumentsN(DAT_0145b6a0, &tn, 1, 10);
        if (tv != 0) {
            for (int i = 0; i < tn; ++i)
                types |= FUN_00ad7200(tv[i]);
        }
    }
    u32 actors = 0;
    {
        int an = 0;
        char** av2 = ca->OptionArgumentsN(DAT_0145b698, &an, 1, 2);
        int cnt = an;
        if (cnt > 1) cnt = 2;
        if (av2 != 0) {
            for (int i = 0; i < cnt; ++i)
                (&actors)[i] = FUN_00932e80(av2[i], 0x811c9dc5, 1);
        }
    }
    if (cam || actors != 0) {
        *(u32*)(msg + 8) = types;
        *(float*)(msg + 0x10) = radius;
        *(u32*)(msg + 0x18) = cam ? 1 : 0;
        *(u32*)(msg + 0x20) = actors;
        *(u32*)(msg + 0x28) = 0;
        FUN_007e4190(*(void**)(s + 0xc), msg, 0);
    }
    (*(VFn0*)((char*)*(void**)msg + 8))(msg);
}
