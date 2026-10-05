// Slice s00490a70 (batch w1g0, slice 86), 0x00490a70..0x00491350.
// /Od editor-region code. Both functions are large; 00490a70 is the real
// SP::EditorUtils::GetAlignmentPosition (named in the dev PDB).
//
// These are reconstructed skeletons: the high-level call sequence is present but
// several inlined sub-steps (matrix/basis copies, EASTL vector temporaries) are
// approximated, so they are listed as partial.

#include "types.h"

struct Vector3 {
    float x, y, z;
};

struct Matrix3 {
    float m[9];
    void Assign(const void* src);
};

struct BBox16 {
    float a;
    Vector3 v;
};

struct cSPEditorBlock {
    char pad[0x2000];
};

struct Mgr {
    char pad[0x100];
};

// stub helpers (masked relocs)
void Vector3_CopyCtor(Vector3* dst, const Vector3* src);
float FUN_00491b40(void* self, void* mgr);
void FUN_004904a0(void* self, void* mgr, void* vec, int type);
float FUN_0048fee0(void* self, void* mgr, void* out, float scale);
float GetLateralAlignmentPosition(void* self, void* mgr, void* a, void* b, float f, void* c, void* d);
float FUN_0048e590(void* self, void* a, void* b, void* c);
void FUN_0044e7c0(void* self, int x);
float FUN_00492e70(void* self, void* a, void* b, void* c, void* d, int e, int f);
void FUN_00429360(void* self, void* a);
void FUN_00540470(void* self, void* a);
int FUN_0048c790(void* self, void* out, int arg);
void FUN_004541f0(void* self, void* p);
void FUN_00454e90(void* a, void* b);
void FUN_00425990();
void VectorDtor(void* self);

// @ 0x00490a70
float SP_EditorUtils_GetAlignmentPosition(cSPEditorBlock* self, Mgr* mgr, Vector3 v,
                                          Matrix3 m, bool* outFlag, int flag, Matrix3 m2) {
    if (self == 0)
        return -1.0f;

    Vector3 pos;
    Vector3_CopyCtor(&pos, (Vector3*)((char*)self + 0x48));

    Matrix3 basis;
    basis.Assign(&m2);

    float align = FUN_00491b40(self, mgr);

    Vector3 lat;
    Vector3_CopyCtor(&lat, &pos);
    Matrix3 tmp;
    tmp.Assign(&m);

    float a1 = FUN_0048fee0(self, mgr, &v, align);

    Matrix3 tmp2;
    tmp2.Assign(&m);

    float a2 = FUN_0048fee0(self, mgr, &v, align);
    float latAlign = GetLateralAlignmentPosition(self, mgr, &lat, &v, align, &tmp2, &tmp);

    float scale = ((*(uint32_t*)((char*)self + 0xdc8) & 0x100) == 0) ? 1.2f : 10.0f;
    float b1 = FUN_0048e590(self, mgr, &v, &scale);

    Matrix3 tmp3;
    tmp3.Assign(&m);

    int neg = -2;
    FUN_0044e7c0(self, neg);
    float off = FUN_00492e70(self, &lat, &tmp3, &v, &neg, (int)(uint8_t)flag, 0);

    (void)a1;
    (void)a2;
    (void)latAlign;
    (void)b1;
    (void)off;
    (void)align;
    if (outFlag)
        *outFlag = false;

    VectorDtor(&tmp3);
    VectorDtor(&tmp2);
    VectorDtor(&tmp);
    return 1.0f;
}

// @ 0x00491350
int FUN_00491350(int* self, int mode) {
    int total = 0;
    BBox16 a, b;
    FUN_00540470(&a, &b);
    FUN_00540470(&b, &a);

    int* list[3];
    FUN_0048c790(self, list, 0);

    if (self[0xf8 / 4] != 0) {
        FUN_0048c790((void*)self[0xf8 / 4], list, 0);
    }

    for (unsigned i = 0; i < (unsigned)((list[1] - list[0]) >> 2); ++i) {
        int* blk = (int*)list[0][i];
        int flags = *(int*)((char*)blk + 0xdcc);
        if ((flags & 0x2000000) == 0) {
            total += *(int*)((char*)blk + 0x5e4);
        } else if (*(int*)((char*)blk + 0x3e4) == 0) {
            if (mode == 1)
                total += *(int*)((char*)blk + 0x5e4);
        } else if (mode == 2) {
            total += *(int*)((char*)blk + 0x5e4);
        } else if (mode == 1) {
            int* end = list[1];
            int* it = list[0];
            while (it != end && *it != blk[0x3e4 / 4])
                ++it;
            if (it != end)
                total += *(int*)((char*)blk + 0x5e4);
        }
    }

    FUN_00454e90(list[0], list[1]);
    FUN_00425990();
    VectorDtor(list);
    return total;
}
