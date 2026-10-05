// SP::cSPEditorBlock — model-slot management (unoptimized /Od /Ob1 /arch:SSE).
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Matrix3 { float m[9]; Matrix3() {} Matrix3(const Matrix3&); };

// Slot objects held in the +0x154 array (indexed model part).
struct Blk {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void SetState(int a, int b);   // vtbl +0x30
};

struct Node { bool Check(); float F3adb80(); float F3adbc0(); };

struct cSPEditorBlock {
    char        pad00[0x10];
    void*       mModel;      // +0x10
    char        pad14[0x18 - 0x14];
    void*       p18;         // +0x18
    char        pad1c[0x28 - 0x1c];
    Node*       node;        // +0x28
    char        pad2c[0x154 - 0x2c];
    Blk*        slots[3];    // +0x154
    Blk*        slot160;     // +0x160
    char        pad164[0x1B0 - 0x164];
    int         f1b0;        // +0x1B0
    char        pad1b4[0x2BC - 0x1B4];
    int         f2bc;        // +0x2BC
    char        pad2c0[0x3EC - 0x2C0];
    void*       p3ec;        // +0x3EC
    char        pad3f0[0x6CC - 0x3F0];
    void**      vec6cc;      // +0x6CC
    void**      vec6d0;      // +0x6D0
    char        pad6d4[0xDC8 - 0x6D4];
    uint32_t    flags0;      // +0xDC8
    uint32_t    flags1;      // +0xDCC

    Blk* GetSlot(int i);                 // 0043CE00
    void F3cad0();                       // 0043CAD0
    void F3ce40();                       // 0043CE40
    void F3cfc0(int p2, char p3);        // 0043CFC0
    Vec3* F3d240(Vec3* out, char p3);    // 0043D240
    void F3d420();                       // 0043D420
};

void* Sub_401060();                       // 00401060 (app/manager singleton)
bool  Sub_4ADB80();                       // 004ADB80
bool  Sub_4ADBC0();                       // 004ADBC0
bool  Sub_4A6120(void* self);             // 004A6120
void  Sub_4A6660(void* self, uint8_t v);  // 004A6660
void  Sub_4A88D0(int id);                 // 004A88D0
void  GetBBox(void* self, void* out, int a, int b, int c);  // 0044AE00
void  BoundingBox_GetCenter(void* box);   // 00409B90
void  FUN_0040CE80(void* dst, const void* src);  // transform copy
void  Modifier_Accumulate(void* self, const void* m);  // 0040CCB0
void* Sub_41DCA0(void* out, void* table, const float* key);  // 0041DCA0

// @ 0x0043CE00
Blk* cSPEditorBlock::GetSlot(int i)
{
    if (i >= 0 && i < 3) {
        Blk* p = slots[i];
        return p;
    }
    return 0;
}

// @ 0x0043CAD0
void cSPEditorBlock::F3cad0()
{
    bool f6 = false, f5 = false;
    if (node != 0) {
        f6 = Sub_4ADB80() ? true : false;
        f5 = Sub_4ADBC0() ? true : false;
    }
    bool changed = false;
    if (!f6) F3ce40();
    if ((flags0 & 0x2000000u) == 0) {
        for (int i = 0; i < 3; i++) {
            Blk* b = slots[i];
            if (b != 0 && (*(uint8_t*)((char*)b + 0x92) == 0 || f6)) {
                b->SetState(3, 1);
                changed = true;
            }
        }
        if (slot160 != 0 && (*(uint8_t*)((char*)slot160 + 0x5D) == 0 || f6)) {
            slot160->SetState(3, 1);
            changed = true;
        }
    }
    if ((flags0 & 0x1000000u) == 0) {
        int skip = -1;
        if ((flags0 & 0x800u) != 0 && !f5) skip = f1b0;
        int count = (int)(vec6d0 - vec6cc);
        for (int i = 0; i < count; i++) {
            Blk* b = *(Blk**)((char*)vec6cc + i * 4);
            if (i != skip && (*(uint8_t*)((char*)b + 0x1D4) == 0 || f6)) {
                b->SetState(3, 1);
                changed = true;
            }
        }
    }
    if (changed) Sub_4A88D0(0xD0A55625);
}

// @ 0x0043CE40
void cSPEditorBlock::F3ce40()
{
    if (Sub_401060() == 0) return;
    for (int i = 0; i < 3; i++) {
        Blk* b = slots[i];
        if (b != 0 && *(uint8_t*)((char*)b + 0x92) != 0) b->SetState(1, 1);
    }
    if (slot160 != 0 && *(uint8_t*)((char*)slot160 + 0x5D) != 0) slot160->SetState(1, 1);
    int count = (int)(vec6d0 - vec6cc);
    for (int i = 0; i < count; i++) {
        Blk* b = *(Blk**)((char*)vec6cc + i * 4);
        if (*(uint8_t*)((char*)b + 0x1D4) != 0) b->SetState(1, 1);
    }
}

// @ 0x0043CFC0
void cSPEditorBlock::F3cfc0(int p2, char p3)
{
    if (Sub_401060() == 0) return;
    if ((flags0 & 0x2000000u) == 0) {
        for (int i = 0; i < 3; i++) {
            Blk* b = slots[i];
            if (b != 0 && (void*)b != (void*)p2) b->SetState(1, 1);
        }
        if (slot160 != 0 && (void*)slot160 != (void*)p2) slot160->SetState(1, 1);
    }
    if (p3 != 0 && Sub_4A6120(this)) {
        uint8_t d = 0;
        if (p2 != 0 && (void*)p2 == p3ec) d = 1;
        Sub_4A6660(this, d);
    }
    if ((flags0 & 0x1000000u) == 0) {
        int count = (int)(vec6d0 - vec6cc);
        for (int i = 0; i < count; i++) {
            void* e = *(void**)((char*)vec6cc + i * 4);
            if ((void*)p2 != e) ((Blk*)e)->SetState(1, 1);
        }
    }
}

// @ 0x0043D240
Vec3* cSPEditorBlock::F3d240(Vec3* out, char p3)
{
    void* mdl = mModel;
    uint8_t large = ((uint32_t)mdl & 0x400000) != 0;
    if (large) {
        if (p3 == 0) {
            float key = *(float*)((char*)mdl + 0x18);
            Vec3* r = (Vec3*)0;
            r = (Vec3*)Sub_41DCA0(out, (char*)this + 0x2FC, &key);
            out->x = r->x; out->y = r->y; out->z = r->z;
        } else {
            out->x = out->y = out->z = 0.0f;
        }
    } else if (p3 == 0) {
        GetBBox(this, out, 1, 0, 0);
        BoundingBox_GetCenter(out);
    } else {
        GetBBox(this, out, 0, 0, 0);
        BoundingBox_GetCenter(out);
    }
    return out;
}

// @ 0x0043D420
void cSPEditorBlock::F3d420()
{
    if (mModel == 0) return;
    if ((flags1 & 0x80u) == 0) return;
    if (f2bc == -1) return;
}

} // namespace SP
