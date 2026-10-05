// SP::cSPEditorBlock::F3AC40 — pick/selection state application switch.
// Unoptimized module: /Od /Ob1 /arch:SSE.
#include "types.h"

namespace SP {

struct Model;

// Single-dword flag word used through the model objects' +4 field.
struct BitField {
    uint32_t m;
    bool Get(int i) const {
        if (i < 32) return (m & (1u << (i % 32))) != 0;
        return false;
    }
    void Set(int i, bool v) {
        if (i < 32) {
            if (v) m |= (1u << (i % 32));
            else   m &= ~(1u << (i % 32));
        }
    }
};

struct Model {
    char     pad0[4];
    BitField flags;      // +0x04
    char     pad8[0x5C - 8];
    uint8_t  state;      // +0x5C
};

// Editor-model object whose virtual slot 10 (vtbl+0x28) receives (flag,state).
struct ModelState {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual void s8(); virtual void s9();
    virtual void SetState(int flag, int state);   // vtbl +0x28
};

struct State {
    uint8_t  a;      // +0
    uint8_t  b;      // +1
    uint16_t pad;    // +2
    int32_t  type;   // +4
};                   // size 8

struct cSPEditorBlock {
    char        pad00[0x10];
    Model*      mModel;      // +0x10
    char        pad14[0x38 - 0x14];
    State       cur;         // +0x38
    State       prev;        // +0x40
    char        pad48[0x3EC - 0x48];
    ModelState* p3ec;        // +0x3EC
    Model*      p3f0;        // +0x3F0

    bool F3AC40(int type, uint8_t a, uint8_t b);
};

// @ 0x0043AC40
bool cSPEditorBlock::F3AC40(int type, uint8_t a, uint8_t b)
{
    cur.type = type;
    bool same = prev.a == cur.a && prev.b == cur.b && prev.type == cur.type;
    if (same && b == 0) {
        return false;
    }
    prev = cur;
    switch (cur.type) {
    case 0:
        if (cur.b == 0 || cur.a == 0) {
            if (cur.b == 0) {
                if (cur.a == 0) {
                    if (p3ec != 0) p3ec->SetState(0, 10);
                    if (p3f0 != 0) p3f0->flags.Set(3, false);
                    if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 10; }
                } else {
                    if (p3ec != 0) p3ec->SetState(1, 5);
                    if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 5; }
                    if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 5; }
                }
            } else {
                if (p3ec != 0) p3ec->SetState(1, 7);
                if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 7; }
                if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 7; }
            }
        } else {
            if (p3ec != 0) p3ec->SetState(1, 8);
            if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 8; }
        }
        break;
    case 1:
        if (p3ec != 0) p3ec->SetState(1, 6);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 6; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 6; }
        break;
    case 2:
        if (p3ec != 0) p3ec->SetState(1, 9);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 9; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 9; }
        break;
    case 4:
        if (p3ec != 0) p3ec->SetState(1, 0xB);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 0xB; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 0xB; }
        break;
    case 5:
        if (p3ec != 0) p3ec->SetState(1, 0xC);
        if (p3f0 != 0) { p3f0->flags.Set(3, true); p3f0->state = 0xC; }
        if (mModel != 0) { mModel->flags.Set(3, true); mModel->state = 0xC; }
        break;
    }
    return true;
}

} // namespace SP
