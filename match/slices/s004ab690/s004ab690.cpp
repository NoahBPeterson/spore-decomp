// Slice s004ab690 — cSPEditorModel teardown / block search helpers.
#include "types.h"

struct cSPEditorBlock {
    char pad0[0xdc8];
    uint32_t mFlags[4];  // +0xdc8
    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
};
struct cSPEditorModel;

extern void* g_vtbl_model_a;
extern void* g_vtbl_model_b;
extern void* g_vtbl_ability;

extern void FUN_004ad330();
extern void FUN_004fd940(void* p);
extern void WString_FreeBuffer(void* p);
extern void FUN_453540_Release(void* p);
extern void FUN_004453eb0_vector_dtor(void* p);

// @ 0x004aba00
void ModelDestructor(cSPEditorModel* self)
{
    *(void**)self = &g_vtbl_model_a;
    *(void**)((char*)self + 4) = &g_vtbl_model_b;
    FUN_004ad330();
    char* v = (char*)self + 0xc8;
    for (uint32_t i = *(uint32_t*)v; i < *(uint32_t*)(v + 4); i += 0x18) {
    }
    FUN_004fd940(v);
    WString_FreeBuffer((char*)self + 0x7c);
    WString_FreeBuffer((char*)self + 0x6c);
    WString_FreeBuffer((char*)self + 0x5c);
    void** rc = (void**)((char*)self + 0x30);
    if (*rc != 0) {
        FUN_453540_Release(*rc);
    }
    FUN_004453eb0_vector_dtor((char*)self + 0x18);
    *(void**)((char*)self + 4) = &g_vtbl_ability;
}

// @ 0x004abaf0
extern void FUN_00435be0(cSPEditorBlock* b);
extern void FUN_00449ed0();
extern void FUN_004541f0(void** p);
extern void FUN_004adfc0(int v);
void RemoveBlock(cSPEditorModel* self, cSPEditorBlock* block)
{
    if (block != 0) {
        cSPEditorBlock** begin = *(cSPEditorBlock***)((char*)self + 0x18);
        cSPEditorBlock** end = *(cSPEditorBlock***)((char*)self + 0x1c);
        cSPEditorBlock** it = begin;
        while (it != end && *it != block) {
            ++it;
        }
        if (it == end) {
            FUN_00435be0((cSPEditorBlock*)self);
            FUN_00449ed0();
            cSPEditorBlock* local = block;
            if (block != 0) {
                (*(void(**)(cSPEditorBlock*))(*(uint32_t*)block + 4))(block);
            }
            FUN_004541f0((void**)&local);
            if (local != 0) {
                (*(void(**)(cSPEditorBlock*))(*(uint32_t*)local + 8))(local);
            }
            FUN_004adfc0(1);
        }
    }
}

// @ 0x004abbc0
void* FUN_004abc50(void* self, void* a, void* b);
void* AddBlock(cSPEditorModel* self,
               float f1, float f2, float f3, unsigned int a,
               unsigned char b6, unsigned char b7, float g1, float g2, float g3)
{
    (void)f1; (void)f2; (void)f3; (void)a; (void)b6; (void)b7;
    (void)g1; (void)g2; (void)g3;
    FUN_004abc50(self, 0, 0);
    return self;
}

// @ 0x004ab690 — large routine (not reconstructed).
void* FUN_004ab690(void* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
    return self;
}

// @ 0x004abc50 — 2096-byte routine (not reconstructed).
void* FUN_004abc50(void* self, void* a, void* b)
{
    (void)self; (void)a; (void)b;
    return self;
}

// @ 0x004ac480
extern double FUN_004a5bd0(cSPEditorBlock* b);
extern void* FUN_0041db10(void* out, void* p, void* arg);
extern double FUN_0040ae50(void* v);
extern float g_floatMax;
cSPEditorBlock* FindNearestFlag7Block(cSPEditorModel* self)
{
    float best = g_floatMax;
    cSPEditorBlock* result = 0;
    int count = (int)(*(uint32_t*)((char*)self + 0x1c) - *(uint32_t*)((char*)self + 0x18)) >> 2;
    for (int i = 0; i < count; ++i) {
        cSPEditorBlock* b = *(cSPEditorBlock**)(*(uint32_t*)((char*)self + 0x18) + i * 4);
        if (b->IsFlagSet(7)) {
            float d = (float)FUN_004a5bd0(b);
            float v[3];
            float* p = (float*)FUN_0041db10(v, (char*)b + 0x48, 0);
            float len = (float)FUN_0040ae50(p);
            float delta = len - d;
            if (delta < best) {
                result = b;
                best = delta;
            }
        }
    }
    return result;
}
