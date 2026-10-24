// Slice s00dff790 (batch bfs1 #38).  Galaxy/simulator input strategies.
// 32-bit MSVC 2008 SP1, /O2 /arch:SSE.
//
// The large inlined functions are stubbed (see partial.txt).

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" void* __cdecl operator_new(int size, const char* name, int a, int b, int c, int d);
extern "C" void* __cdecl SP_AssetBrowser();
extern "C" void* __cdecl SP_SporeGuide();
extern "C" void* __cdecl SP_MessageServer();
extern "C" void* __cdecl SP_MovieSystem();
extern "C" void* __cdecl SP_GetCurrentGameMode();
extern "C" void* __cdecl SP_ResourceMan_GetManager();
extern "C" void  __cdecl sub_644b10(void*);
extern "C" void  __cdecl sub_644b60(void*);
extern "C" void  __cdecl sub_e02040(void*);
extern "C" void  __cdecl sub_ec5a60(void*, int, int);
struct EC { char sub_ec4320(); };
struct GObj { char pad_00[0x108]; int field108; char pad_10c[0x270 - 0x10c]; u8 b270; void sub_de52d0(); };

// ===========================================================================
//  0x00e00630  base-class ctor (vtable + one flag byte)
// ===========================================================================
struct VBase {
    void** vftable;              // +0x00
    u8     b4;                   // +0x04
    VBase();
};
// @ 0x00e00630
VBase::VBase() {
    vftable = (void**)0x147dba8;
    b4 = 0;
}

// ===========================================================================
//  0x00e00560  conditional helper call
// ===========================================================================
struct Thisc { int m(); };
// @ 0x00e00560
void __stdcall e00560(int dummy) {
    (void)dummy;
    void* ab = SP_AssetBrowser();
    GObj* g = *(GObj**)0x16a1344;
    if (g->field108 == 7 &&
        *(char*)((char*)ab + 0x1c) == 0 &&
        g->b270 == 0) {
        int* mm = *(int**)0x16c7aa4;
        EC* ec = *(EC**)((char*)mm + 0x1c);
        if (!ec->sub_ec4320()) {
            (*(GObj**)0x16a1344)->sub_de52d0();
        }
    }
}

// ===========================================================================
//  0x00e005b0  open Sporepedia if in the right game mode
// ===========================================================================
// @ 0x00e005b0
void __cdecl e005b0() {
    char buf[0x48];
    sub_644b10(buf);
    if ((int)SP_GetCurrentGameMode() == 0x2ccd1d2) {
        int* p = (int*)operator_new(0x14, "Sporepedia", 0, 0, 0, 0);
        if (p) {
            int* g = *(int**)0x16a1344;
            p[1] = 0x13ec458;
            p[2] = 0;
            p[0] = 0x147dc04;
            p[1] = 0x149bad8;
            p[3] = (int)g;
            *(u8*)(p + 4) = 0;
        }
        sub_e02040(buf);
    }
    sub_644b60(buf);
}

// ===========================================================================
//  0x00e00670  key dispatch (this + 2 args)
// ===========================================================================
struct KeyObj { char pad[0x44]; int key44(); void Dispatch(int, int); };
// @ 0x00e00670
void KeyObj::Dispatch(int param2, int param3) {
    KeyObj* self = this;
    if (param3 == 0) {
        if (param2 == 0x48) goto joined;
    } else {
        if (param3 != 1) goto after;
    }
joined:
    if (param2 != 0xbf) goto after;
    {
        void* sg = SP_SporeGuide();
        int* ms;
        int msg;
        if (*(char*)((char*)sg + 0x1c) == 0) { ms = (int*)SP_MessageServer(); msg = 0x5120263; }
        else                                  { ms = (int*)SP_MessageServer(); msg = 0x5b9ba6c; }
        ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, msg, 0, 0);
    }
after:
    if (param2 != 0x42 || param3 != 0) return;
    if (*(char*)(*(int**)0x16a1344 + 0xef) != 0) return;
    {
        int* mv = (int*)SP_MovieSystem();
        char c = ((char(__thiscall*)(void*))(*(void***)mv)[0x14 / 4])(mv);
        if (c) return;
    }
    if (*(int*)(*(char**)0x16a1344 + 0x1ec) == 1) return;
    {
        void* ab = SP_AssetBrowser();
        if (*(char*)((char*)ab + 0x1c) != 0) {
            int* ms = (int*)SP_MessageServer();
            ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, 0x574f0a6, 0, 0);
            return;
        }
        if (self->key44()) {
            int* ms = (int*)SP_MessageServer();
            ((void(__thiscall*)(void*, int, int, int))(*(void***)ms)[0x14 / 4])(ms, 0x5120264, 0, 0);
        }
    }
}

// ===========================================================================
//  The large inlined bodies below call module-local helpers with the original
//  ABIs.  A helper symbol embeds its own address (sub_<hex> / a member named
//  sub_<hex>) so difftest can map the call to the retail function.
// ===========================================================================

// --- cdecl helpers ---------------------------------------------------------
extern "C" void* __cdecl sub_67dcd0();                       // EA::ResourceMan::GetManager
extern "C" int   __cdecl sub_dfa370();
extern "C" void* __cdecl sub_ef19f0();
extern "C" int   __cdecl sub_b3d410();                       // *(int*)0x167eb28
extern "C" int   __cdecl sub_dd9190();                       // *(int*)0x16a0b08
extern "C" int   __cdecl sub_401090();                       // GetSetting9
extern "C" int   __cdecl sub_eed920(void*, void*);           // SetIntProperty(key, wstr)
extern "C" int   __cdecl sub_de3f00(void*, void*, int);
extern "C" void* __cdecl sub_dff2b0(void* src, void* srcEnd, void* dst);
extern "C" void* __cdecl sub_dff2f0(void* src, void* srcEnd, void* dst);
extern "C" void* __cdecl sub_dff4a0(void** slot, void* src, void* srcEnd, void* dst, void* extra);
extern "C" void* __cdecl sub_dff4e0(void** slot, void* src, void* srcEnd, void* dst, void* extra);
extern "C" void  __cdecl sub_f47380(void* p);                // operator delete

// --- vtable helper ---------------------------------------------------------
static inline void releaseHandle(void* p) {
    if (p) ((void (__thiscall*)(void*))(*(void***)p)[1])(p);  // handle->vtable[4]
}

// --- stand-ins for helpers that run on foreign objects ---------------------
struct Eco {                                     // *(void**)(*(int*)0x16c7aa4 + 0x1c)
    char sub_ec4320();
    char sub_ec5a60(int* key, int a, int b);
};
struct Ctx39 {                                   // *(int*)0x16a1344 + 0x3c
    void sub_de9dc0(int* ev);
};
struct GObj2 {                                   // *(int*)0x16a1344
    void sub_de86d0(int a, int b);
    void sub_de5470(int a);
};
struct X19 {                                     // sub_ef19f0() result
    int f00, f04, f08;
    u8  pad0c[0x0c];
    int f18, f1c, f20;
};
struct Timeline {                                // sub_b3d410() result
    void sub_e3e350(int a, int* key, int b);
};
struct Item {                                    // resource item
    void* sub_414e10();                          // GetName
};
struct ClsA { void sub_dda0d0(int v); };
struct ClsB { void sub_ddb760(); };
struct SpeciesMgr { void* sub_4df550(int* key); };
struct Species { void sub_4da330(void* wstr); };

// --- sub-objects of PropBaseA22 --------------------------------------------
struct WString {
    void* b; void* e; void* c;
    void sub_423650(void* first, void* last);    // basic_string<wchar_t>::assign
    WString& operator=(const WString& o) {
        if (this != &o) sub_423650(o.b, o.e);
        return *this;
    }
};
struct CStr47a0 {
    u8 raw[0x14];
    int* sub_6b5430(const CStr47a0* src);
    CStr47a0& operator=(const CStr47a0& o) { sub_6b5430(&o); return *this; }
};
struct Pair18 {
    u8 raw[0x38];
    int sub_dfca50(const Pair18* src);
    Pair18& operator=(const Pair18& o) { sub_dfca50(&o); return *this; }
};
struct Buf178 {
    void* begin; void* end; void* cap; u8 raw[0xb4];
    int* sub_dfb720(const Buf178* src);
    Buf178& operator=(const Buf178& o) { sub_dfb720(&o); return *this; }
};
struct Blob23c {
    u8 raw[0x19b8];
    int* sub_dff650(const Blob23c* src);
    Blob23c& operator=(const Blob23c& o) { sub_dff650(&o); return *this; }
};
struct Sub14 {
    u8 raw[0x14];
    int* sub_dff330(const Sub14* src);
    Sub14& operator=(const Sub14& o) { sub_dff330(&o); return *this; }
};
struct G2c10 { Sub14 s; u32 f14; u32 f18; };
struct VecFloatSound {
    void* begin; void* end; void* cap; u8 raw[0x0c];
    int* sub_eae540(const VecFloatSound* src);
    VecFloatSound& operator=(const VecFloatSound& o) { sub_eae540(&o); return *this; }
};
struct KeyVec {
    u8 raw[0x14];
    int* sub_6609a0(const KeyVec* src);
    KeyVec& operator=(const KeyVec& o) { sub_6609a0(&o); return *this; }
};
struct PropGroup {
    CStr47a0 cs; WString w14; u32 gap20; u32 f24; u32 f28; WString w2c; u32 gap38;
};
struct Layout {
    u8 raw[0x34];
    void* sub_8105b0(int id, int flag);          // cSPUILayout::FindWindowByID
};

// ===========================================================================
//  0x00dff790  eastl::vector<elem 0x27e0>::operator=
// ===========================================================================
struct Vec27e0 {
    void* begin; void* end; void* cap; u8 pad[0x08];
    void* sub_dff590(unsigned n, void* first, void* last);
    void  sub_dfdf70(void* first, void* last);
    Vec27e0& sub_dff790(const Vec27e0& x);
};
// @ 0x00dff790
Vec27e0& Vec27e0::sub_dff790(const Vec27e0& x) {
    if (&x != this) {
        unsigned n = (unsigned)(((char*)x.end - (char*)x.begin) / 0x27e0);
        if ((unsigned)(((char*)cap - (char*)begin) / 0x27e0) < n) {
            void* p = sub_dff590(n, x.begin, x.end);
            sub_dfdf70(begin, end);
            if (begin != 0 && *(int*)((char*)begin - 4) != 0)
                sub_f47380(begin);
            begin = p;
            end = (char*)p + n * 0x27e0;
            cap = (char*)p + n * 0x27e0;
            return *this;
        }
        unsigned cur = (unsigned)(((char*)end - (char*)begin) / 0x27e0);
        if (cur < n) {
            sub_dff2b0(x.begin, (char*)x.begin + cur * 0x27e0, begin);
            void* slot = x.end;
            sub_dff4a0(&slot, (char*)x.begin + cur * 0x27e0, x.end, end, x.end);
            end = (char*)begin + n * 0x27e0;
        } else {
            void* dstEnd = sub_dff2b0(x.begin, x.end, begin);
            sub_dfdf70(dstEnd, end);
            end = (char*)begin + n * 0x27e0;
        }
    }
    return *this;
}

// ===========================================================================
//  0x00dff8e0  eastl::vector<elem 0x27e8>::operator=
// ===========================================================================
struct Vec27e8 {
    void* begin; void* end; void* cap; u8 pad[0x08];
    void* sub_dff5f0(unsigned n, void* first, void* last);
    void  sub_dfe910(void* first, void* last);
    Vec27e8& sub_dff8e0(const Vec27e8& x);
};
// @ 0x00dff8e0
Vec27e8& Vec27e8::sub_dff8e0(const Vec27e8& x) {
    if (&x != this) {
        unsigned n = (unsigned)(((char*)x.end - (char*)x.begin) / 0x27e8);
        if ((unsigned)(((char*)cap - (char*)begin) / 0x27e8) < n) {
            void* p = sub_dff5f0(n, x.begin, x.end);
            sub_dfe910(begin, end);
            if (begin != 0)
                sub_f47380(begin);
            begin = p;
            end = (char*)p + n * 0x27e8;
            cap = (char*)p + n * 0x27e8;
            return *this;
        }
        unsigned cur = (unsigned)(((char*)end - (char*)begin) / 0x27e8);
        if (cur < n) {
            sub_dff2f0(x.begin, (char*)x.begin + cur * 0x27e8, begin);
            void* slot = x.end;
            sub_dff4e0(&slot, (char*)x.begin + cur * 0x27e8, x.end, end, x.end);
            end = (char*)begin + n * 0x27e8;
        } else {
            void* dstEnd = sub_dff2f0(x.begin, x.end, begin);
            sub_dfe910(dstEnd, end);
            end = (char*)begin + n * 0x27e8;
        }
    }
    return *this;
}

// ===========================================================================
//  0x00dffa30  PropBaseA22::operator=  (memberwise copy)
// ===========================================================================
struct PropBaseA22 {
    u8  pad00[0x08];                    // +0x00 (vftable + ...)
    u32 f08;                            // +0x08
    u32 f0c;                            // +0x0c
    u32 f10;                            // +0x10
    u32 f14;                            // +0x14
    Pair18 p18;                         // +0x18
    float f50;                          // +0x50
    float f54;                          // +0x54
    float f58;                          // +0x58
    u8  f5c;                            // +0x5c
    u8  pad5d[0x03];
    float f60;                          // +0x60
    u8  f64;                            // +0x64
    u8  pad65[0x03];
    u32 f68;                            // +0x68
    u32 f6c;
    u32 f70;
    u32 f74;
    u32 f78;                            // +0x78
    PropGroup g7c;                      // +0x7c
    PropGroup gb8;                      // +0xb8
    PropGroup gf4;                      // +0xf4
    u32 blk130[8];                      // +0x130
    u32 f150;                           // +0x150
    u32 f154;
    u32 f158;
    u32 f15c;
    u32 f160;
    u32 f164;
    u32 f168;                           // +0x168
    float f16c;                         // +0x16c
    float f170;                         // +0x170
    u8  f174;                           // +0x174
    u8  f175;                           // +0x175
    u8  pad176[0x02];
    Buf178 b178;                        // +0x178
    u32 f238;                           // +0x238
    Blob23c b23c;                       // +0x23c
    Vec27e8 v2bf4;                      // +0x2bf4
    u8  f2c08;                          // +0x2c08
    u8  pad2c09[0x03];
    u32 f2c0c;                          // +0x2c0c
    G2c10 g2c10;                        // +0x2c10
    u8  f2c2c;                          // +0x2c2c
    u8  f2c2d;                          // +0x2c2d
    u8  pad2c2e[0x02];
    u32 f2c30;                          // +0x2c30
    u32 f2c34;
    u32 f2c38;
    u32 f2c3c;
    u32 f2c40;
    u32 f2c44;
    u32 f2c48;                          // +0x2c48
    float f2c4c;                        // +0x2c4c
    u32 f2c50;                          // +0x2c50
    VecFloatSound v2c54;                // +0x2c54
    Vec27e0 v2c6c;                      // +0x2c6c
    KeyVec k2c80;                       // +0x2c80
    u32 f2c94;                          // +0x2c94
    u32 f2c98;
    u32 f2c9c;
    u32 f2ca0;
    u32 f2ca4;
    u32 f2ca8;                          // +0x2ca8

    void sub_f2e7d0();                  // ctor
    void sub_f2b3d0();
    void sub_dfef70();                  // dtor
    PropBaseA22& sub_dffa30(const PropBaseA22& x);
};
// @ 0x00dffa30
PropBaseA22& PropBaseA22::sub_dffa30(const PropBaseA22& x) {
    f08 = x.f08;
    f0c = x.f0c;
    f10 = x.f10;
    f14 = x.f14;
    p18 = x.p18;
    f50 = x.f50;
    f54 = x.f54;
    f58 = x.f58;
    f5c = x.f5c;
    f60 = x.f60;
    f64 = x.f64;
    f68 = x.f68;
    f6c = x.f6c;
    f70 = x.f70;
    f74 = x.f74;
    f78 = x.f78;
    g7c.cs = x.g7c.cs;
    g7c.w14 = x.g7c.w14;
    g7c.f24 = x.g7c.f24;
    g7c.f28 = x.g7c.f28;
    g7c.w2c = x.g7c.w2c;
    gb8.cs = x.gb8.cs;
    gb8.w14 = x.gb8.w14;
    gb8.f24 = x.gb8.f24;
    gb8.f28 = x.gb8.f28;
    gb8.w2c = x.gb8.w2c;
    gf4.cs = x.gf4.cs;
    gf4.w14 = x.gf4.w14;
    gf4.f24 = x.gf4.f24;
    gf4.f28 = x.gf4.f28;
    gf4.w2c = x.gf4.w2c;
    for (int i = 0; i < 8; i++) blk130[i] = x.blk130[i];
    f150 = x.f150; f154 = x.f154; f158 = x.f158; f15c = x.f15c;
    f160 = x.f160; f164 = x.f164; f168 = x.f168;
    f16c = x.f16c; f170 = x.f170;
    f174 = x.f174; f175 = x.f175;
    b178 = x.b178;
    f238 = x.f238;
    b23c = x.b23c;
    v2bf4 = x.v2bf4;
    f2c08 = x.f2c08;
    f2c0c = x.f2c0c;
    g2c10.s = x.g2c10.s;
    g2c10.f14 = x.g2c10.f14;
    g2c10.f18 = x.g2c10.f18;
    f2c2c = x.f2c2c;
    f2c2d = x.f2c2d;
    f2c30 = x.f2c30; f2c34 = x.f2c34; f2c38 = x.f2c38; f2c3c = x.f2c3c;
    f2c40 = x.f2c40; f2c44 = x.f2c44; f2c48 = x.f2c48;
    f2c4c = x.f2c4c;
    f2c50 = x.f2c50;
    v2c54 = x.v2c54;
    v2c6c = x.v2c6c;
    k2c80 = x.k2c80;
    f2c94 = x.f2c94; f2c98 = x.f2c98; f2c9c = x.f2c9c;
    f2ca0 = x.f2ca0; f2ca4 = x.f2ca4; f2ca8 = x.f2ca8;
    return *this;
}

// ===========================================================================
//  Editor-mode UI (Simulator::cEditorModeUI): mode dispatch + message handling
// ===========================================================================
struct EditorEntry {
    u32 f00; u32 f04; u32 f08; u8 pad0c[0x14]; u32 f20; u8 pad24[0x14];  // 0x38
};
struct cEditorModeUI {
    u8  pad00[0x0c];
    int* p0c;                           // +0x0c
    u8  pad10[0x10];                    // +0x10
    int mode;                           // +0x20
    int prevMode;                       // +0x24
    int f28;                            // +0x28
    int f2c;                            // +0x2c
    int count;                          // +0x30
    u8  pad34[0x14];                    // +0x34
    Layout layout;                      // +0x48
    u8  b7c;                            // +0x7c
    u8  b7d;                            // +0x7d
    u8  b7e;                            // +0x7e
    u8  b7f;                            // +0x7f
    u8  pad80[0x04];
    void* p84;                          // +0x84
    u8  pad88[0x04];
    int keyA[3];                        // +0x8c
    int keyB[3];                        // +0x98
    int keyC[3];                        // +0xa4
    u8  padb0[0x10];
    EditorEntry entries[3];             // +0xc0
    WString wstr;                       // +0x168

    void sub_e000a0(int* key);
    void sub_e001a0(int* ev);
    bool sub_e002b0(int msg, int* params);
    void sub_dffda0();

    void sub_dfab20(int enabled);       // SetModeEnabled
    void sub_df9dc0(unsigned i, int v);
    void sub_df9c80(int v);
    void sub_df9d20(int* ev);
    void sub_dfaca0(int* ev);           // EnterMode8
    void sub_dfad50(int* ev);           // EnterMode9
    void sub_dfa710(int v);             // TogglePodPanel1
    void sub_dfb0d0(void* buf);         // Update
    void sub_df98f0();
};

// @ 0x00dffda0
void cEditorModeUI::sub_dffda0() {
    void* local = 0;
    void* rm = sub_67dcd0();
    if (local) { void* t = local; local = 0; releaseHandle(t); }
    char ok = ((char (__thiscall*)(void*, void*, void**, int, int, int, int))
               (*(void***)rm)[3])(rm, keyA, &local, 0, 0, 0, 0);
    if (ok) {
        PropBaseA22 tmp;
        tmp.sub_f2e7d0();
        tmp.sub_dffa30(*(const PropBaseA22*)local);
        tmp.sub_f2b3d0();
        ((Ctx39*)(*(int*)0x16a1344 + 0x3c))->sub_de9dc0(keyA);
        if (tmp.f175 == 0) {
            keyC[0] = 0; keyC[1] = 0; keyC[2] = 0;
            b7c = 1;
            if (wstr.b != wstr.e) { *(u16*)wstr.b = 0; wstr.e = wstr.b; }
            b7f = 1;
        } else {
            b7c = 0;
            b7f = 0;
            if (wstr.b != wstr.e) { *(u16*)wstr.b = 0; wstr.e = wstr.b; }
            keyC[0] = tmp.blk130[0];
            keyC[1] = tmp.blk130[1];
            keyC[2] = tmp.blk130[2];
            if (!sub_eed920(keyC, &wstr)) {
                void* prof = ((SpeciesMgr*)sub_401090())->sub_4df550(keyC);
                if (prof) ((Species*)prof)->sub_4da330(&wstr);
            }
        }
        sub_df98f0();
        int n = (int)(((char*)tmp.b178.end - (char*)tmp.b178.begin) / 0x38);
        b7d = (n != 0);
        count = n;
        if (n > 0) {
            u32* dst = (u32*)entries;
            u32* src = (u32*)tmp.b178.begin;
            for (int i = 0; i < n; i++)
                for (int w = 0; w < 14; w++)
                    dst[i * 14 + w] = src[i * 14 + w];
        }
        void* w1 = layout.sub_8105b0(0x7ca3288, 1);
        if (w1) {
            ((void (__thiscall*)(void*, int, int))(*(void***)w1)[0x7c / 4])(w1, 1, 1);
            int k4[4];
            k4[0] = keyA[0]; k4[1] = 0x2f7d0004; k4[2] = keyA[2]; k4[3] = 0;
            sub_de3f00(w1, k4, 0);
        }
        void* w2 = layout.sub_8105b0(0x7ccdc3b, 1);
        if (w2) {
            int k2[3];
            k2[0] = keyA[0]; k2[1] = 0x30bdee3; k2[2] = keyA[2];
            void* h = 0;
            void* rm2 = sub_67dcd0();
            ((char (__thiscall*)(void*, void*, void**, int, int, int, int))
             (*(void***)rm2)[3])(rm2, k2, &h, 0, 0, 0, 0);
            if (h) {
                void* item = ((void* (__thiscall*)(void*, int))(*(void***)h)[3])(h, 0x30bdee3);
                if (item) {
                    ((void (__thiscall*)(void*))(*(void***)item)[0])(item);
                    void* nm = ((Item*)item)->sub_414e10();
                    ((void (__thiscall*)(void*, void*))(*(void***)w2)[0x80 / 4])(w2, nm);
                    ((void (__thiscall*)(void*))(*(void***)item)[1])(item);
                }
                releaseHandle(h);
            }
        }
        void* w3 = layout.sub_8105b0(0x7e0bb68, 1);
        if (w3) {
            ((void (__thiscall*)(void*, int, int))(*(void***)w3)[0x7c / 4])(w3, 1, b7f);
        }
        tmp.sub_dfef70();
    }
    if (local) { void* t = local; local = 0; releaseHandle(t); }
}

// @ 0x00e000a0
void cEditorModeUI::sub_e000a0(int* key) {
    void* local = 0;
    void* rm = sub_67dcd0();
    if (local) { void* t = local; local = 0; releaseHandle(t); }
    char ok = ((char (__thiscall*)(void*, void*, void**, int, int, int, int))
               (*(void***)rm)[3])(rm, key, &local, 0, 0, 0, 0);
    if (ok) {
        keyB[0] = key[0];
        keyB[1] = key[1];
        keyB[2] = key[2];
        void* ec = *(void**)(*(int*)0x16c7aa4 + 0x1c);
        if (!((Eco*)ec)->sub_ec5a60(keyB, 0, 0)) {
            keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
        } else if (((Eco*)ec)->sub_ec4320()) {
            sub_dfab20(0);
            prevMode = mode;
            mode = 8;
        } else {
            keyA[0] = keyB[0]; keyA[1] = keyB[1]; keyA[2] = keyB[2];
            keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
            sub_dffda0();
        }
    }
    if (local) { void* t = local; local = 0; releaseHandle(t); }
}

// @ 0x00e001a0
void cEditorModeUI::sub_e001a0(int* ev) {
    if (ev[0] == 0) {
        if (mode == 5 || mode == 7) {
            mode = 0;
            sub_dfab20(1);
        }
    } else if (ev[1] == 0x366a930d) {
        ((Ctx39*)(*(int*)0x16a1344 + 0x3c))->sub_de9dc0(ev);
        unsigned i = 0;
        do {
            entries[i].f00 = 0;
            entries[i].f04 = 0;
            entries[i].f08 = 0;
            entries[i].f20 = 0;
            sub_df9dc0(i, 0);
            i++;
        } while (i < 3);
        int m = mode;
        if (m == 7) sub_dfaca0(ev);
        else if (m == 5) sub_dfad50(ev);
        else if (m == 1) sub_e000a0(ev);
    } else if (ev[1] == 0x2b978c46) {
        sub_df9d20(ev);
    }
    if (mode > 0 && (mode <= 2 || mode == 4)) {
        void* ec = *(void**)(*(int*)0x16c7aa4 + 0x1c);
        if (!((Eco*)ec)->sub_ec4320()) {
            sub_dfab20(1);
            sub_df9c80(p0c[f2c * 9]);
        }
    }
    b7e = 1;
}

// @ 0x00e002b0
bool cEditorModeUI::sub_e002b0(int msg, int* params) {
    if (msg == 0x04249453) {
        u8 buf[12];
        sub_dfb0d0(buf);
        return true;
    }
    if (msg == 0x07be7df5) {
        int a = params[2];
        if (a == 4) {
            ((GObj2*)*(int*)0x16a1344)->sub_de86d0(2, 0);
            return true;
        }
        if (a == 3) {
            void* r = (void*)sub_dd9190();
            ((ClsA*)r)->sub_dda0d0(0);
            if (p84) {
                ((void (__thiscall*)(void*, int))(*(void***)p84)[3])(p84, 1);
                if (p84) {
                    void* t = p84;
                    p84 = 0;
                    ((void (__thiscall*)(void*))(*(void***)t)[1])(t);
                }
            }
            return true;
        }
        if (a == 0) {
            void* r = (void*)sub_dd9190();
            ((ClsA*)r)->sub_dda0d0(2);
            sub_dfa710(1);
            return true;
        }
        if (a == 2) {
            mode = 0;
            ((GObj2*)*(int*)0x16a1344)->sub_de5470(0);
            return true;
        }
        if (a == 5) {
            void* r = (void*)sub_dd9190();
            ((ClsB*)r)->sub_ddb760();
            return true;
        }
        if (a == 1) {
            sub_dfa370();
            sub_dfab20(1);
            return true;
        }
        return true;
    }
    if (msg == 0xcc0bf723) {
        if (mode == 8 && params != 0) {
            int x = params[0];
            if (x == 1 || x == 3) {
                int pm = prevMode;
                if (pm == 1) {
                    mode = 1;
                    b7e = 1;
                    keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
                } else if (pm == 9) {
                    keyA[0] = 0; keyA[1] = 0; keyA[2] = 0;
                    mode = 0;
                    keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
                }
                sub_dfab20(1);
                b7e = 1;
                return true;
            }
            if (x == 2) {
                keyA[0] = keyB[0]; keyA[1] = keyB[1]; keyA[2] = keyB[2];
                keyB[0] = 0; keyB[1] = 0; keyB[2] = 0;
                mode = prevMode;
                if (mode == 1) {
                    sub_dffda0();
                    b7e = 1;
                    sub_dfab20(1);
                    b7e = 1;
                    return true;
                }
                if (mode == 9) {
                    X19* e = (X19*)sub_ef19f0();
                    e->f00 = keyA[0]; e->f04 = keyA[1]; e->f08 = keyA[2];
                    e->f18 = 0; e->f1c = 0; e->f20 = 0;
                    ((Timeline*)sub_b3d410())->sub_e3e350(1, (int*)0x1654c10, 1);
                    f28 = 0xa;
                    return true;
                }
            }
        }
        return true;
    }
    return false;
}
