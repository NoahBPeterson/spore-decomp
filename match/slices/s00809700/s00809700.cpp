// Slice s00809700: SPUIHelpers modal/message-box helpers and misc small setters.
// The small accessors / simple members are byte-exact; the large modal and layout routines
// are only partially reconstructed.
#include "types.h"

// ================================================================== small state setters
struct AppInner { char pad[0x118]; int flag; };
struct AppOuter { char pad[0x3c]; AppInner* inner; };

extern AppOuter* g_app;              // 0x015fd918
extern uint8_t g_894, g_895, g_896;  // 0x0164c894/5/6
extern uint32_t g_898, g_89c, g_8a0;// 0x0164c898/9c/a0

// @ 0x008098b0
void set894(uint8_t v) { if (g_app->inner->flag != 0) g_894 = v; }
// @ 0x008098d0
void set898(uint32_t v) { if (g_app->inner->flag != 0) g_898 = v; }
// @ 0x008098f0
void set895(uint8_t v) { if (g_app->inner->flag != 0) g_895 = v; }
// @ 0x00809910
void set89c(uint32_t v) { if (g_app->inner->flag != 0) g_89c = v; }
// @ 0x00809930
void set896(uint8_t v) { if (g_app->inner->flag != 0) g_896 = v; }
// @ 0x00809950
void set8a0(uint32_t v) { if (g_app->inner->flag != 0) g_8a0 = v; }

// ================================================================== 0x00809970
struct WM {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13(); virtual void w14(); virtual void w15();
    virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20(); virtual void w21(); virtual void w22(); virtual void w23();
    virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27();
    virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31();
    virtual void w32();
    virtual int Fn84();      // +0x84 (index 33)
};
extern "C" WM* WindowManager();

int FUN_00809970()
{
    if (WindowManager() != 0) {
        if (WindowManager()->Fn84() != 0) {
            return 1;
        }
    }
    return 0;
}

// ================================================================== 0x00809fa0
struct ComObj {
    virtual void q0();
    virtual void Release();       // +4
};
struct Holder {
    void* a;                      // +0
    void* b;                      // +4
    ComObj* m8;                   // +8
    ComObj* mC;                   // +0xc
    Holder* DeleteThis(unsigned char flags);
};
extern "C" void efree(void* p);

// @ 0x00809fa0
Holder* Holder::DeleteThis(unsigned char flags)
{
    ComObj* p = mC;
    if (p) p->Release();
    ComObj* q = m8;
    if (q) q->Release();
    if (flags & 1)
        efree(this);
    return this;
}

// ================================================================== 0x0080a5f0
extern int g_15446cc, g_15446d0, g_15446d4;
extern char g_obj_15446c8;
struct G {
    char pad[8];
    void FUN_0080a4f0(int a, int b);
};

// @ 0x0080a5f0
void FUN_0080a5f0()
{
    ((G*)&g_obj_15446c8)->FUN_0080a4f0(g_15446cc, g_15446d0);
    g_15446d4 = 0;
}

// ================================================================== 0x0080a470
extern "C" void* dbgnew(unsigned size, const void* data, int a, int b, const char* file, int line);
extern char g_data_13f6b3c;

struct Blob {
    int i0, i1, i2, i3, i4, i5;
    float f0, f1, f2, f3;
    int i6, i7;
};

// @ 0x0080a470
void __stdcall FUN_0080a470(Blob* src)
{
    Blob* p = (Blob*)dbgnew(0x34, &g_data_13f6b3c, 0, 0,
                            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                            0xd1);
    if (p) {
        p->i0 = src->i0; p->i1 = src->i1; p->i2 = src->i2; p->i3 = src->i3;
        p->i4 = src->i4; p->i5 = src->i5;
        p->f0 = src->f0; p->f1 = src->f1; p->f2 = src->f2; p->f3 = src->f3;
        p->i6 = src->i6; p->i7 = src->i7;
    }
    *(int*)((char*)p + 0x30) = 0;
}

// ================================================================== 0x0080a320
// Enter/Esc message filter.  Byte-exact except the switch jump/byte tables (4 bytes).
struct Msg {
    int a, b;        // +0, +4
    int type;        // +8
    int fieldC;      // +0xc
    int key;         // +0x10
    int field14;     // +0x14
};
extern "C" void sOnEnterEscKeys(int a, int b, int c);

// @ 0x0080a320
bool __stdcall FUN_0080a320(void* a, Msg* m)
{
    switch (m->type) {
    case 1:
        if (m->fieldC == 0 && (m->key == 0x1b || m->key == 0xd) && m->field14 == 0)
            sOnEnterEscKeys(0, m->key, 0);
        return true;
    case 2:
    case 5:
        return true;
    case 10:
        return false;
    default:
        return false;
    }
}

// ================================================================== remaining (partial)
// @ 0x00809700
void FUN_00809700() { /* modal-window state machine; not reconstructed */ }

// @ 0x008099a0
void SPUIHelpers_BeginModal() { /* creates the modal window/message box; not reconstructed */ }

// @ 0x00809c50
void SPUIHelpers_EndModal() { /* tears down the modal window; not reconstructed */ }

// @ 0x00809db0
bool FUN_00809db0(void* a, void* b)
{
    // Creates a CalloutMessageBox, inits it and shows it with a text pair.
    (void)a; (void)b;
    return false;
}

// @ 0x00809e40
void FUN_00809e40(void* self) { (void)self; /* manager/window rebind; not reconstructed */ }

// @ 0x00809f40
void FUN_00809f40(void* self, void* a, void* b) { (void)self; (void)a; (void)b; }

// @ 0x00809ff0
void FUN_00809ff0(void* self) { (void)self; /* two window-scale updates; not reconstructed */ }

// @ 0x0080a0f0
void FUN_0080a0f0() { /* not reconstructed */ }

// @ 0x0080a1a0
void sOnEnterEscKeys() { /* not reconstructed */ }

// @ 0x0080a390
void FUN_0080a390() { /* not reconstructed */ }
