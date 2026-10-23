// Slice s00b68720: Spore UTFWin UI manager walk.  Names are Claude-coined from
// usage.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

typedef unsigned int uint;

// the window/object record walked by the manager
struct Obj {
    unsigned char pad0[4];
    int mField4;                        // 0x04
    unsigned char pad8[0x14];
    float m1c;                          // 0x1c
    float m24;                          // 0x24
    float m28;                          // 0x28
    float m2c;                          // 0x2c
    float m30;                          // 0x30
    float m38;                          // 0x38
    float m3c;                          // 0x3c
    float m40;                          // 0x40
    float m44;                          // 0x44
    float m48;                          // 0x48
    float m4c;                          // 0x4c
    int m50;                            // 0x50 (layout)
    int m54, m58, m5c;                  // 0x54..
    int m60, m64, m68, m6c, m70;
    int m74, m78, m7c, m80, m84, m88, m8c;
    int m90, m94, m98, m9c, ma0, ma4, ma8, mac, mb0, mb4;
    int mb8;                            // 0xb8
    int mFieldBC;                       // 0xbc
    unsigned char padc0[0x58];
    int m118;                           // 0x118
    float m11c;                         // 0x11c
    int m120;                           // 0x120
    int m124;                           // 0x124
    int m128;                           // 0x128
};

// the manager singleton at 0x01687348
struct Manager {
    int GetPriority();                          // 0x00e31100 (thiscall)
    Obj* Find(const int& key);                  // 0x00b72230 (thiscall, ret 4)
    int Alloc();                                // 0x00b72160 (thiscall)
    Obj* Make(int handle);                      // 0x00b72210 (thiscall, ret 4)
};

// cSPUILayout: only the members 00b68aa0 needs; the two-argument call shape is
// what the resolver matches against the original's call sequence (via 0x008105b0).
struct cSPUILayout {
    void* FindWindowByID(unsigned id, int a);   // 0x008105b0 (thiscall)
};

extern Manager* gManager;               // 0x01687348

extern float kColourZero;               // 0x01485378  0.0f
extern float kColourScale;              // 0x013f2100  255.0f

// helpers used by the register-ABI window routine @ 00b68910
extern char gVtbl13f94d4;               // 0x013f94d4  RTTI-ish token passed to slot 3
extern int  __cdecl FUN_00bfc480();     // 0x00bfc480
extern void* __cdecl cConnectionDialog_ctor(void*);          // 0x00810000
extern int   __cdecl cSPUILayout_Init(void* self, const wchar_t* name, int a, int b, unsigned c); // 0x00812160
extern void* __cdecl cSPUILayout_FindWindowByID(void* self, unsigned id, int a);                  // 0x008105b0
extern void  __cdecl cSPUILayout_Shutdown(void* self, unsigned a);                                // 0x00811ad0
extern void  __cdecl cSPUILayout_dtor(void* self);                                               // 0x00811fe0
extern void  __cdecl AnchorWindowToWindow(void* a, void* b, int c, int d);                        // 0x00807340
extern const wchar_t kRolloverInvulnName[];   // 0x01464990 L"Rollover_ScenarioInvulnerableImage"
extern float kOne_;                      // 0x01485720  1.0f
extern float kProbeLimit;                // 0x013eb1bc
extern float __cdecl Clamp01(float v);   // 0x005a6e00

// helpers used by the layout builder @ 00b68aa0
extern int  __cdecl FUN_00b687d0(int* value);          // 0x00b687d0 (FindOrCreate)
extern float __cdecl FUN_00b685e0(int* value);         // 0x00b685e0
extern void* __cdecl operator_new(unsigned n, const char* file, int a, int b, int c, int d);  // FUN_00f473a0
extern void* __cdecl SPUIHelpers_CenterWindowInRect(void* obj);   // FUN_00b5b800
extern void* __cdecl GetCurrentGameMode();              // FUN_00cd40b0
extern int   __cdecl TribeModeStrategyInstance();       // 0x00cd40b0 SP::cTribeModeStrategy::Instance
// Layout-name wide strings (VA in the original).  Their exact text is in rdata-literal.txt
// because the resolver's string search is unreliable for UTF-16 literals.
extern const wchar_t kLayout_TribeTool[];               // L"Rollover_TribeTool"          0x01464b2c
extern const wchar_t kLayout_TribeCitizen[];            // L"Rollover_TribeCitizen"       0x01464b54
extern const wchar_t kLayout_TribeHut[];                // L"Rollover_TribeHut"           0x01464b08
extern const wchar_t kLayout_TribeMinimap[];            // L"Rollover_Tribe_Minimap"      0x01464ad8
extern const wchar_t kLayout_ScenarioVehicle[];         // L"Rollover_ScenarioVehicle"    0x01464bcc
extern const wchar_t kLayout_CivVehicle[];              // L"Rollover_CivVehicle"         0x01464ba4
extern const wchar_t kLayout_CityMinimap[];             // L"RolloverCity_Minimap"        0x01464a48
extern const wchar_t kLayout_SpaceCity[];               // L"RolloverSpaceCity"           0x01464a24
extern const wchar_t kLayout_SharedHealthBar[];         // L"SharedHealthBar"             0x01464a04
extern const wchar_t kLayout_Building[];                // L"Rollover_Building"           0x01464b80
extern const wchar_t kLayout_UFO[];                     // L"RolloverUFO"                 0x01464ac0
extern const wchar_t kLayout_Creature[];                // L"Rollover_Creature"           0x01464a9c
extern const wchar_t kLayout_CRGMinimap[];              // L"Rollover_CRGMinimap"         0x01464a74
extern const wchar_t kLayout_FixedObject[];             // L"Rollover_FixedObject"        0x014649d8

// =============================================================================
// @ 0x00b68720  Walk the manager's window list, returning the first window whose
// mField4 is set and which matches the requested category bits (flags).
int __cdecl FindWindow(unsigned char flags)
{
    int key = gManager->GetPriority();
    Obj* o;
    while ((o = gManager->Find(key)) != 0) {
        if (o->mField4 != 0) {
            if ((flags & 8) != 0) {
                if (o->mFieldBC != 0)
                    return o->mField4;
            } else if ((flags & 2) != 0) {
                if (o->m50 != 0 && o->m44 == 0.0f)
                    return o->mField4;
            } else if ((flags & 4) != 0) {
                if (o->m50 != 0 && o->m44 != 0.0f)
                    return o->mField4;
            } else if ((flags & 0x10) != 0) {
                if (o->m120 != 0)
                    return o->mField4;
            }
        }
    }
    return 0;
}

// =============================================================================
// @ 0x00b687d0  Find a manager record whose +4 value is `value`; if none exists,
// allocate a fresh record, attach `value` (refcounted), reset its state fields,
// and return the record handle.
int __cdecl FindOrCreate(int* value)
{
    int key = gManager->GetPriority();
    int* o;
    while ((o = (int*)gManager->Find(key)) != 0) {
        if ((int*)o[1] == value)
            return *o;
    }

    int handle = gManager->Alloc();             // 0x00b72160
    if (handle == 0)
        return 0;
    Obj* rec = (Obj*)gManager->Make(handle);    // 0x00b72210
    int* old = (int*)rec->mField4;
    if (value != old) {
        if (value != 0)
            (*(void(__thiscall**)(int*))value[0])(value);            // slot 0
        rec->mField4 = (int)value;
        if (old != 0)
            (*(void(__thiscall**)(int*))(old[0] + 4))(old);          // slot 1
    }
    rec->m1c = 0.0f;
    rec->m30 = 0.0f;
    rec->m28 = 0.0f;
    rec->m24 = 0.0f;
    rec->m2c = 0.0f;
    rec->m38 = 0.0f;
    rec->m3c = 0.0f;
    rec->m40 = 0.0f;
    rec->m44 = 0.0f;
    rec->m48 = 0x7f7fffff;
    rec->m4c = 0x7f7fffff;
    int* p = (int*)rec->m50;
    if (p != 0) {
        rec->m50 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 8))(p);                  // slot 2
    }
    rec->m118 = 0x075f3ea8;
    p = (int*)rec->mb8;
    if (p != 0) {
        rec->mb8 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 8))(p);                  // slot 2
    }
    rec->m11c = 0.0f;
    p = (int*)rec->m120;
    if (p != 0) {
        rec->m120 = 0;
        (*(void(__thiscall**)(int*))(p[0] + 4))(p);                  // slot 1
    }
    rec->m124 = 0;
    rec->m128 = 0;
    return handle;
}

// =============================================================================
// @ 0x00b693b0  Register-ABI helper (incoming ecx = window, esi = the record):
// sets the record's colour from the window rect delta * param_2 (a float on the
// stack), then toggles visibility.  Expressed as a naked function because the
// record arrives in esi, which MSVC's C ABI cannot express.
__declspec(naked) void FUN_00b693b0()
{
    __asm {
        sub     esp, 0x10
        mov     eax, dword ptr [ecx]
        mov     edx, dword ptr [eax + 0x34]
        call    edx
        movss   xmm2, dword ptr [eax]
        movss   xmm3, dword ptr [eax + 4]
        movss   xmm0, dword ptr [eax + 8]
        movss   xmm1, dword ptr [eax + 0x0c]
        mov     eax, dword ptr [esi]
        xorps   xmm4, xmm4
        mov     edx, dword ptr [eax + 0x60]
        lea     ecx, [esp]
        subss   xmm0, xmm2
        mulss   xmm0, dword ptr [esp + 0x14]
        push    ecx
        subss   xmm1, xmm3
        mov     ecx, esi
        movss   dword ptr [esp + 4], xmm4
        movss   dword ptr [esp + 8], xmm4
        movss   dword ptr [esp + 0x0c], xmm0
        movss   dword ptr [esp + 0x10], xmm1
        call    edx
        movss   xmm0, dword ptr [esp + 0x18]
        ucomiss xmm0, dword ptr [kColourZero]
        lahf
        test    ah, 0x44
        jp      l_colour
        mov     eax, dword ptr [esi]
        mov     edx, dword ptr [eax + 0x7c]
        push    0
        push    1
        mov     ecx, esi
        call    edx
        add     esp, 0x10
        ret
    l_colour:
        mulss   xmm0, dword ptr [kColourScale]
        movss   dword ptr [esp + 0x14], xmm0
        cvtss2si eax, dword ptr [esp + 0x14]
        mov     edx, dword ptr [esi]
        shl     eax, 0x18
        or      eax, 0xffffff
        push    eax
        mov     eax, dword ptr [edx + 0x5c]
        mov     ecx, esi
        call    eax
        mov     edx, dword ptr [esi]
        mov     eax, dword ptr [edx + 0x7c]
        push    1
        push    1
        mov     ecx, esi
        call    eax
        add     esp, 0x10
        ret
    }
}

// =============================================================================
// @ 0x00b69460  Register-ABI helper (incoming esi = an object, edi = a mode):
// optionally fetches a sub-object through the object's slot-3 method, toggles the
// sub-object's slot-0x7c method, and for a real mode forwards to the object's
// slot-0x14 method.  Naked for the same esi/edi reason.
__declspec(naked) void FUN_00b69460()
{
    __asm {
        test    esi, esi
        je      l_null
        mov     eax, dword ptr [esi]
        mov     edx, dword ptr [eax + 0x0c]
        push    0xeeee8218
        mov     ecx, esi
        call    edx
        mov     ecx, eax
        jmp     l_have
    l_null:
        xor     ecx, ecx
    l_have:
        mov     eax, dword ptr [ecx]
        mov     edx, dword ptr [eax + 0x7c]
        cmp     edi, -1
        jne     l_two
        push    0
        push    1
        call    edx
        ret
    l_two:
        push    1
        push    1
        call    edx
        mov     eax, dword ptr [esi]
        mov     edx, dword ptr [eax + 0x14]
        push    edi
        mov     ecx, esi
        call    edx
        ret
    }
}

// =============================================================================
// @ 0x00b68910  Register-ABI window routine (incoming ecx = an object whose
// slot-3 method yields a window, edi = the record/self).  Creates a
// Rollover_ScenarioInvulnerableImage layout, finds its window, positions and
// anchors it, then shuts the layout down.  Naked as the record arrives in edi.
__declspec(naked) void FUN_00b68910()
{
    __asm {
        sub     esp, 0x1c
        test    ecx, ecx
        je      l_nullwin
        mov     eax, dword ptr [ecx]
        mov     edx, dword ptr [eax + 0x0c]
        push    0x13f94d4
        call    edx
        jmp     l_havewin
    l_nullwin:
        xor     eax, eax
    l_havewin:
        mov     byte ptr [edi + 0x34], 0
        test    eax, eax
        je      l_done
        mov     ecx, eax
        call    FUN_00bfc480
        test    al, al
        je      l_done
        mov     ecx, dword ptr [edi + 0x64]
        mov     byte ptr [edi + 0x34], 1
        test    ecx, ecx
        je      l_s2
        mov     eax, dword ptr [ecx]
        mov     edx, dword ptr [eax + 0x7c]
        push    0
        push    1
        call    edx
    l_s2:
        mov     ecx, dword ptr [edi + 0x68]
        test    ecx, ecx
        je      l_s3
        mov     eax, dword ptr [ecx]
        mov     edx, dword ptr [eax + 0x7c]
        push    0
        push    1
        call    edx
    l_s3:
        mov     ecx, dword ptr [edi + 0x6c]
        test    ecx, ecx
        je      l_s4
        mov     eax, dword ptr [ecx]
        mov     edx, dword ptr [eax + 0x7c]
        push    0
        push    1
        call    edx
    l_s4:
        mov     ecx, dword ptr [edi + 0x74]
        test    ecx, ecx
        je      l_layout
        mov     eax, dword ptr [ecx]
        mov     edx, dword ptr [eax + 0x7c]
        push    0
        push    1
        call    edx
    l_layout:
        lea     ecx, [esp + 4]
        call    cConnectionDialog_ctor
        push    0x5b598fa
        push    0
        push    0x40464100
        push    offset kRolloverInvulnName
        lea     ecx, [esp + 0x14]
        call    cSPUILayout_Init
        test    al, al
        je      l_dtor
        push    esi
        push    1
        push    0x26e0df3
        lea     ecx, [esp + 0x10]
        call    cSPUILayout_FindWindowByID
        mov     esi, eax
        test    esi, esi
        je      l_nowin
        mov     eax, dword ptr [esi]
        mov     edx, dword ptr [eax]
        mov     ecx, esi
        call    edx
    l_nowin:
        mov     eax, dword ptr [esi]
        mov     edx, dword ptr [eax + 0x10]
        mov     ecx, esi
        call    edx
        test    eax, eax
        je      l_shutdown
        mov     eax, dword ptr [esi]
        mov     edx, dword ptr [eax + 0x10]
        mov     ecx, esi
        call    edx
        mov     edx, dword ptr [eax]
        mov     ecx, eax
        mov     eax, dword ptr [edx + 0xdc]
        push    esi
        call    eax
    l_shutdown:
        push    1
        lea     ecx, [esp + 0x0c]
        call    cSPUILayout_Shutdown
        mov     ecx, dword ptr [edi + 0x70]
        mov     edx, dword ptr [ecx]
        mov     eax, dword ptr [edx + 0xd8]
        push    esi
        call    eax
        fldz
        mov     edx, dword ptr [esi]
        mov     eax, dword ptr [edx + 0x70]
        sub     esp, 8
        fst     dword ptr [esp + 4]
        mov     ecx, esi
        fstp    dword ptr [esp]
        call    eax
        mov     ecx, dword ptr [edi + 0x70]
        mov     edx, dword ptr [ecx]
        mov     eax, dword ptr [edx + 0x38]
        call    eax
        fld     dword ptr [eax + 0x0c]
        fsub    dword ptr [eax + 4]
        mov     ecx, dword ptr [edi + 0x70]
        mov     edx, dword ptr [ecx]
        mov     eax, dword ptr [edx + 0x38]
        fstp    dword ptr [esp + 4]
        call    eax
        movss   xmm0, dword ptr [eax + 8]
        fld     dword ptr [esp + 4]
        mov     edx, dword ptr [esi]
        subss   xmm0, dword ptr [eax]
        mov     eax, dword ptr [edx + 0x74]
        sub     esp, 8
        fstp    dword ptr [esp + 4]
        mov     ecx, esi
        movss   dword ptr [esp], xmm0
        call    eax
        mov     ecx, dword ptr [edi + 0x70]
        push    0
        push    0x300
        push    esi
        push    ecx
        call    AnchorWindowToWindow
        mov     edx, dword ptr [esi]
        mov     eax, dword ptr [edx + 4]
        add     esp, 0x10
        mov     ecx, esi
        call    eax
        pop     esi
    l_dtor:
        lea     ecx, [esp + 4]
        call    cSPUILayout_dtor
    l_done:
        add     esp, 0x1c
        ret
    }
}

// =============================================================================
// @ 0x00b69010  Register-ABI health-bar/decay updater (incoming esi = the record,
// two floats on the stack at [esp+0x18]/[esp+0x1c]).  Eases the record's bar
// towards its target, clamps sub-values through Clamp01 (0x005a6e00), and returns
// whether the current value (record+0x38) is positive.  Naked for the esi ABI.
__declspec(naked) void FUN_00b69010()
{
    __asm {
        sub     esp, 0x14
        mov     eax, dword ptr [gManager]
        movss   xmm2, dword ptr [eax + 0x24]
        movss   xmm1, dword ptr [esp + 0x1c]
        movss   xmm0, dword ptr [esi + 0x44]
        lea     ecx, [esi + 0x44]
        mulss   xmm2, xmm1
        subss   xmm0, xmm2
        movss   xmm2, dword ptr [kOne_]
        movss   dword ptr [ecx], xmm0
        movss   dword ptr [esp + 4], xmm0
        movss   dword ptr [esp], xmm2
        xorps   xmm0, xmm0
        maxss   xmm0, dword ptr [esp + 4]
        minss   xmm0, dword ptr [esp]
        movss   dword ptr [esp + 4], xmm0
        movss   xmm0, dword ptr [esp + 4]
        movss   dword ptr [ecx], xmm0
        movss   xmm0, dword ptr [esp + 0x18]
        comiss  xmm0, dword ptr [esi + 0x1c]
        movss   dword ptr [esi + 0x20], xmm0
        jbe     l_b1
        movss   dword ptr [esi + 0x28], xmm0
        movss   dword ptr [esi + 0x30], xmm0
    l_b1:
        movss   xmm3, dword ptr [esi + 0x1c]
        ucomiss xmm3, dword ptr [kProbeLimit]
        lahf
        test    ah, 0x44
        jp      l_b2
        movss   dword ptr [esi + 0x1c], xmm0
    l_b2:
        movss   xmm3, dword ptr [esi + 0x40]
        xorps   xmm5, xmm5
        comiss  xmm3, xmm5
        jbe     l_b3
        subss   xmm3, xmm1
        movss   dword ptr [esi + 0x40], xmm3
        jmp     l_afterpop
    l_b3:
        movss   xmm3, dword ptr [esi + 0x38]
        comiss  xmm2, xmm3
        push    edi
        lea     edi, [esi + 0x38]
        jbe     l_b4
        movss   xmm4, dword ptr [esi + 0x1c]
        ucomiss xmm4, xmm0
        lahf
        test    ah, 0x44
        jnp     l_b4
        mov     edx, dword ptr [gManager]
        movss   xmm0, dword ptr [edx + 0x28]
        mulss   xmm0, xmm1
        addss   xmm0, xmm3
        movss   dword ptr [edi], xmm0
        movss   dword ptr [esp + 8], xmm0
        movss   dword ptr [esp + 0x20], xmm2
        xorps   xmm0, xmm0
        maxss   xmm0, dword ptr [esp + 8]
        minss   xmm0, dword ptr [esp + 0x20]
        movss   dword ptr [esp + 8], xmm0
        movss   xmm0, dword ptr [esp + 8]
        movss   dword ptr [edi], xmm0
        jmp     l_cmp
    l_b4:
        movss   xmm4, dword ptr [esi + 0x1c]
        comiss  xmm0, xmm4
        jbe     l_b5
        movss   xmm0, dword ptr [esi + 0x24]
        comiss  xmm0, xmm5
        jbe     l_b6
        mov     eax, dword ptr [gManager]
        movss   xmm3, dword ptr [eax + 0x28]
        mulss   xmm3, xmm1
        subss   xmm0, xmm3
        movss   dword ptr [esi + 0x24], xmm0
        movss   dword ptr [esp + 8], xmm0
        movss   dword ptr [esp + 0x20], xmm2
        xorps   xmm0, xmm0
        maxss   xmm0, dword ptr [esp + 8]
        minss   xmm0, dword ptr [esp + 0x20]
        movss   dword ptr [esp + 8], xmm0
        movss   xmm0, dword ptr [esp + 8]
        movss   dword ptr [esi + 0x24], xmm0
    l_b6:
        movss   xmm3, dword ptr [esi + 0x2c]
        comiss  xmm2, xmm3
        jbe     l_b7
        mov     ecx, dword ptr [gManager]
        movss   xmm0, dword ptr [ecx + 0x28]
        mulss   xmm0, xmm1
        addss   xmm0, xmm3
        movss   dword ptr [esi + 0x2c], xmm0
        movss   dword ptr [esp + 8], xmm0
        movss   dword ptr [esp + 0x20], xmm2
        xorps   xmm0, xmm0
        maxss   xmm0, dword ptr [esp + 8]
        minss   xmm0, dword ptr [esp + 0x20]
        movss   dword ptr [esp + 8], xmm0
        movss   xmm0, dword ptr [esp + 8]
        movss   dword ptr [esi + 0x2c], xmm0
        jmp     l_epi
    l_b7:
        mov     edx, dword ptr [gManager]
        movss   xmm0, dword ptr [edx + 0x2c]
        mulss   xmm0, xmm1
        addss   xmm0, dword ptr [esi + 0x1c]
        movss   xmm1, dword ptr [esi + 0x20]
        comiss  xmm0, xmm1
        movss   dword ptr [esi + 0x1c], xmm0
        jb      l_epi
        movss   dword ptr [esi + 0x1c], xmm1
        jmp     l_epi
    l_b5:
        comiss  xmm4, xmm0
        jbe     l_b8
        movss   xmm0, dword ptr [esi + 0x2c]
        comiss  xmm0, xmm5
        mov     al, 1
        jbe     l_b9
        mov     eax, dword ptr [gManager]
        movss   xmm2, dword ptr [eax + 0x28]
        mulss   xmm2, xmm1
        subss   xmm0, xmm2
        movss   dword ptr [esp + 0x1c], xmm0
        fld     dword ptr [esp + 0x1c]
        push    ecx
        fstp    dword ptr [esp]
        movss   dword ptr [esi + 0x2c], xmm0
        call    Clamp01
        fstp    dword ptr [esi + 0x2c]
        movss   xmm1, dword ptr [esp + 0x24]
        xorps   xmm5, xmm5
        movss   xmm2, dword ptr [kOne_]
        add     esp, 4
        xor     al, al
    l_b9:
        movss   xmm3, dword ptr [esi + 0x24]
        comiss  xmm2, xmm3
        jbe     l_b10
        movss   xmm0, dword ptr [esi + 0x28]
        comiss  xmm0, dword ptr [esi + 0x1c]
        jbe     l_b10
        mov     ecx, dword ptr [gManager]
        movss   xmm0, dword ptr [ecx + 0x28]
        mulss   xmm0, xmm1
        addss   xmm0, xmm3
        movss   dword ptr [esp + 0x20], xmm0
        fld     dword ptr [esp + 0x20]
        movss   dword ptr [esi + 0x24], xmm0
        jmp     l_b11
    l_b10:
        movss   dword ptr [esi + 0x24], xmm2
        test    al, al
        je      l_epi
        mov     edx, dword ptr [gManager]
        movss   xmm2, dword ptr [edx + 0x2c]
        movss   xmm0, dword ptr [esi + 0x1c]
        mulss   xmm2, xmm1
        movss   xmm1, dword ptr [esi + 0x20]
        subss   xmm0, xmm2
        comiss  xmm1, xmm0
        movss   dword ptr [esi + 0x1c], xmm0
        jb      l_epi
        movss   dword ptr [esi + 0x1c], xmm1
        jmp     l_epi
    l_b8:
        ucomiss xmm4, xmm0
        lahf
        test    ah, 0x44
        jp      l_epi
        movss   xmm3, dword ptr [esi + 0x24]
        comiss  xmm3, xmm5
        jbe     l_b12
        movss   xmm6, dword ptr [esi + 0x28]
        comiss  xmm6, xmm4
        jbe     l_b12
        subss   xmm3, xmm1
        movss   dword ptr [esp + 0x20], xmm3
        fld     dword ptr [esp + 0x20]
        movss   dword ptr [esi + 0x24], xmm3
    l_b11:
        push    ecx
        fstp    dword ptr [esp]
        call    Clamp01
        xorps   xmm5, xmm5
        fstp    dword ptr [esi + 0x24]
        add     esp, 4
        jmp     l_epi
    l_b12:
        movss   dword ptr [esi + 0x28], xmm0
        movss   dword ptr [esi + 0x30], xmm0
        movss   xmm0, dword ptr [esi + 0x3c]
        comiss  xmm0, xmm5
        jbe     l_b13
        movss   xmm3, dword ptr [edi]
        comiss  xmm2, xmm3
        jbe     l_b14
        mov     eax, dword ptr [gManager]
        movss   xmm0, dword ptr [eax + 0x28]
        mulss   xmm0, xmm1
        addss   xmm0, xmm3
        movss   dword ptr [esp + 0x20], xmm0
        fld     dword ptr [esp + 0x20]
        push    ecx
        fstp    dword ptr [esp]
        movss   dword ptr [edi], xmm0
        call    Clamp01
        xorps   xmm5, xmm5
        add     esp, 4
        jmp     l_b15
    l_b14:
        subss   xmm0, xmm1
        movss   dword ptr [esi + 0x3c], xmm0
        jmp     l_epi
    l_b13:
        mov     edx, dword ptr [gManager]
        movss   xmm0, dword ptr [edx + 0x28]
        mulss   xmm0, xmm1
        movss   xmm1, dword ptr [edi]
        subss   xmm1, xmm0
        movss   dword ptr [edi], xmm1
    l_cmp:
        movss   xmm0, dword ptr [ecx]
        comiss  xmm0, dword ptr [edi]
        ja      l_b16
        mov     ecx, edi
    l_b16:
        fld     dword ptr [ecx]
    l_b15:
        fstp    dword ptr [edi]
    l_epi:
        pop     edi
    l_afterpop:
        comiss  xmm5, dword ptr [esi + 0x38]
        jb      l_ret1
        xor     al, al
        add     esp, 0x14
        ret
    l_ret1:
        mov     al, 1
        add     esp, 0x14
        ret
    }
}

// =============================================================================
// @ 0x00b68aa0  SP::sFindOrCreateUI.  Looks the record up (creating it if
// needed), and if its layout slot (+0x50) is still empty, builds the appropriate
// rollover layout for the requested category and caches every window handle the
// other helpers use.  Faithful C; the switch/string ordering keeps this from
// being byte-exact.
int __cdecl sFindOrCreateUI(int* param_1, int param_2, float param_3)
{
    int handle = FUN_00b687d0(param_1);
    Obj* rec = gManager->Make(handle);
    if (rec->m50 != 0)
        return (int)rec;

    if (param_3 == -1.0f)
        param_3 = FUN_00b685e0(param_1);

    rec->m1c = param_3;
    rec->m30 = param_3;
    rec->m28 = param_3;

    int* nw = (int*)operator_new(0x18, "Simulator/HealthBar", 0, 0, 0, 0);
    int* win = 0;
    if (nw != 0)
        win = (int*)SPUIHelpers_CenterWindowInRect(nw);

    int* old = (int*)rec->m50;
    if (win != old) {
        if (win != 0)
            (*(void(__thiscall**)(int*))(win[0] + 4))(win);      // slot 1
        rec->m50 = (int)win;
        if (old != 0)
            (*(void(__thiscall**)(int*))(old[0] + 8))(old);      // slot 2
    }

    void* mode = GetCurrentGameMode();
    unsigned flags;
    const wchar_t* name;
    switch (param_2) {
    case 2:  flags = 0xe9f70df9; name = kLayout_TribeTool;        break;
    case 3:  flags = 0xe9f70df9; name = kLayout_TribeCitizen;     break;
    case 4:  flags = 0xe9f70df9; name = kLayout_TribeHut;         break;
    case 5:  flags = 0x5b598f6;  name = kLayout_TribeMinimap;     break;
    case 6:
        flags = 0xe9f70df9;
        name = (mode == (void*)0x01654c10) ? kLayout_ScenarioVehicle : kLayout_CivVehicle;
        break;
    case 7:
        if (mode != (void*)0x01654c05)
            goto default_case;
        flags = 0x5b598f6;  name = kLayout_CityMinimap;           break;
    case 8:
        flags = 0xe9f70df9;
        name = (mode == (void*)0x01654c05) ? kLayout_SpaceCity : kLayout_SharedHealthBar;
        break;
    case 9:  flags = 0xe9f70df9; name = kLayout_Building;         break;
    case 11: flags = 0xe9f70df9; name = kLayout_UFO;              break;
    case 12:
        if (mode != (void*)0x01654c01 && mode != (void*)0x01654c10)
            goto default_case;
        flags = 0xe9f70df9;  name = kLayout_Creature;             break;
    case 14: flags = 0x5b598f6;  name = kLayout_CRGMinimap;       break;
    case 16: flags = 0xe9f70df9; name = kLayout_FixedObject;      break;
    default:
    default_case:
        flags = 0xe9f70df9;  name = kLayout_SharedHealthBar;      break;
    }

    cSPUILayout_Init((void*)rec->m50, name, 0x40464100, 1, flags);

    cSPUILayout* lay = (cSPUILayout*)rec->m50;
    if (lay != 0)
        (*(void(__thiscall**)(cSPUILayout*, int))(*(int*)lay + 0x7c))(lay, 1);  // SetVisibility

    rec->m54 = (int)lay->FindWindowByID(0x93310e4a, 1);
    rec->m58 = (int)lay->FindWindowByID(0x933103eb, 1);
    rec->m5c = (int)lay->FindWindowByID(0x31e94d0, 1);
    rec->m60 = (int)lay->FindWindowByID(0x933103ea, 1);
    rec->m64 = (int)lay->FindWindowByID(0x26e0df0, 1);
    rec->m68 = (int)lay->FindWindowByID(0x26e0df1, 1);
    rec->m6c = (int)lay->FindWindowByID(0x26e0df2, 1);
    rec->m70 = (int)lay->FindWindowByID(0x26e0df3, 1);
    rec->m74 = (int)lay->FindWindowByID(0x46adf86, 1);
    rec->m78 = (int)lay->FindWindowByID(0x3caf1f4, 1);
    rec->m7c = (int)lay->FindWindowByID(0x2b0e0f6, 1);
    rec->m80 = (int)lay->FindWindowByID(0x3f8a0d2, 1);
    rec->m84 = (int)lay->FindWindowByID(0x4c1f3a0, 1);
    rec->m88 = (int)lay->FindWindowByID(0x5d2a1b9, 1);
    rec->m8c = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* w90 = (int*)lay->FindWindowByID(0x4d039a8, 1);
    if (w90 != 0) {
        int* p = w90;
        int* r = 0;
        if (w90 != 0)
            r = (int*)(*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);
        rec->m90 = (int)r;
    }
    rec->m94 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->m98 = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* w74 = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->m74 = (int)w74;
    if (w74 != 0) {
        unsigned vis = *((unsigned char*)gManager + 0x30);
        (*(void(__thiscall**)(int*, unsigned, int))(*(int*)w74 + 0x7c))(w74, vis, 1);
    }
    FUN_00b68910();
    rec->m9c = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma0 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma4 = (int)lay->FindWindowByID(0x4d039a8, 1);
    rec->ma8 = (int)lay->FindWindowByID(0x4d039a8, 1);

    int* wac = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mac = (int)wac;
    if (wac != 0 && GetCurrentGameMode() == (void*)0x01654c02) {
        int gm = (*(int(__thiscall**)(int*))(*param_1 + 0x38))(param_1);
        if (gm == 0xee02c7) {
            int inst = TribeModeStrategyInstance();
            void* arg = (inst == 0) ? 0 : (void*)(inst + 4);
            (*(void(__thiscall**)(int*, void*))(wac[0] + 0x104))(wac, arg);
        }
    }

    int* p = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mb0 = (p == 0) ? 0 : (*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);
    p = (int*)lay->FindWindowByID(0x4d039a8, 1);
    rec->mb4 = (p == 0) ? 0 : (*(int(__thiscall**)(int*, int))(p[0] + 0x0c))(p, 0x105a93d);

    return (int)rec;
}
