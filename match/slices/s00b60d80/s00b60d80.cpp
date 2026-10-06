// Slice s00b60d80 (batch big0) — 0x00b60d80, 10064 bytes.
//
// PARTIAL. Module Spore.  This is a compiler-generated one-time registration/init
// routine (`__fastcall`, arg in ECX, returns 1 if already run, 0 otherwise).  The
// PDB candidate `SP::cTribeTool::TakeHit` is wrong; the string pool it references
// (`:language`, `:locale`, `App/cAdventureLook`, `App/cAllSuperPowersCommand`,
// `App/cAntiAliasGIF`, ...) shows it registers the Simulator/App class factories
// and their tunings.
//
// Shape: ~150 repetitions of a guarded static-local initialisation, each using one
// bit of the shared guard dword at 0x016872d4:
//
//   if ((DAT_016872d4 & MASK) == 0) {
//       DAT_016872d4 |= MASK;
//       FUN_00692f60(0);                 // register the type description
//       DAT_<guard> = &<scalar deleting dtor>;   // vtable store
//       atexit(FUN_013c2b..);            // per-object destructor
//   }
//   if (FUN_00ab30c0() == 0) FUN_00692850();     // flush pending registration
//
// mixed with heap construction of the tunings objects through
// `operator_new`, `EA::Allocator::ZoneObject::operator_new` and
// `EA::ResourceMan::GetManager()->Register(...)`.  Reproducing it byte-exactly means
// reproducing the original static-local declaration order; the first block is shown
// for shape and the rest are summarised.
//
// @ 0x00b60d80

typedef unsigned char  u8;
typedef unsigned int   u32;
typedef int            i32;

extern "C" {
    void* __cdecl operator_new(u32 size, const char* alloc, int a, int b, int c, int d); // 0x011e06e0 (EA new)
    void* __cdecl ZoneObject_operator_new(u32 size, const char* alloc, int a, int b, int c, int d);
    int   __cdecl FUN_00692f60(int);                 // 0x00692f60
    int   __cdecl FUN_00692850(void);                // 0x00692850
    char  __cdecl FUN_00ab30c0(void);                // 0x00ab30c0
    void  __cdecl FUN_00ea8ad0(void);                // 0x00ea8ad0
    void  __cdecl FUN_013c2b60(void);                // 0x013c2b60 (atexit dtor)
    void* __cdecl EA_ResourceMan_GetManager(void);   // 0x00b47... (ResourceMan::GetManager)
    int   __cdecl atexit(void (__cdecl*)(void));
}
extern u32 _DAT_016872d4;        // shared one-time guard bits
extern void* _DAT_016872c0;      // vtable slots written for each static object
extern void* _DAT_016872ac, * _DAT_01687298, * _DAT_01687284, * _DAT_01687270;
extern void* _DAT_0168725c;

struct TakeHit_This {
    u8  pad0[0xd];
    u8  done;                    // +0xd
    u8  pad_e[0x1c - 0xe];
    void* p1c;                   // +0x1c   content-validation summariser
};

// @ 0x00b60d80
u32 __fastcall FUN_00b60d80(TakeHit_This* self)
{
    if (self->done)
        return 1;
    self->done = 1;

    // --- build the content-validation summariser and install it ----------------
    int* p = (int*)operator_new(0x10, "Audio", 0, 0, 0, 0);
    if (p) {
        p[1] = (int)&_DAT_016872c0;      // cContentValidationSummarizer vtable
        p[2] = 0;
        p[0] = (int)&_DAT_016872ac;
        p[1] = (int)&_DAT_01687298;
        p[3] = 0;
    }
    int* old = (int*)self->p1c;
    if (p != old) {
        if (p)   (*(void (__thiscall**)(void*))(*p))((void*)p);
        self->p1c = p;
        if (old) (*(void (__thiscall**)(void*))(*old))((void*)old);
    }

    FUN_00ea8ad0();

    // --- one resource factory registration -------------------------------------
    u32* r = (u32*)ZoneObject_operator_new(8, "Audio", 0, 0, 0, 0);
    if (r) {
        *r = (u32)&_DAT_01687284;
        r[1] = 0;
        *r = (u32)&_DAT_01687270;
    }
    int* rm = (int*)EA_ResourceMan_GetManager();
    (*(void (__thiscall**)(int*, int, u32*, int))(*(u32*)rm + 0x44))(rm, 1, r, 0);

    // --- guarded static-object initialisation (repeated ~150x) -----------------
    if ((_DAT_016872d4 & 1) == 0) {
        _DAT_016872d4 |= 1;
        FUN_00692f60(0);
        _DAT_016872c0 = &_DAT_016872c0;    // real vtable (&PTR__scalar_deleting_destructor__014624d0)
        atexit(FUN_013c2b60);
    }
    if (FUN_00ab30c0() == 0)
        FUN_00692850();

    /* TODO: the remaining registrations repeat this exact pattern with masks
     * 2,4,8,0x10,0x20,... and the class-specific vtables/dtors. Transcribe in
     * original declaration order to match. */

    return 0;
}
