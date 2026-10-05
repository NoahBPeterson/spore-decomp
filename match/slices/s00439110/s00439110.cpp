// SP::cSPEditorBlock::SetModelBasedOnSymmetrySign (0x439110, 4931 bytes).
// Unoptimized module: /Od /Ob1 /arch:SSE.
//
// PARTIAL: the full 4.9 KB body (model build, symmetry-sign handling, child
// recursion) is summarised here; only the outer control flow is reproduced.
#include "types.h"

namespace SP {

struct Vec3 { float x, y, z; };
struct Matrix3 { float m[9]; Matrix3() {} Matrix3(const Matrix3&); };
struct cPropertyList;

struct cSPEditorBlock {
    char  pad0[0xC];
    cPropertyList* props;    // +0x0C
    char  pad10[0x10];

    bool  F435c80();                                 // 00435C80
    void  SetFlag(int a, int b);                     // 00435A10
    void  F3a5e0(int type, uint8_t a, uint8_t b, char c);  // 0043A5E0
    void  BuildBlock();                              // (inlined BuildBlock)
    void  F40090();
    void  F449ed0();
    void  F43a5e0(float a, int b, int c);
    void  SetModelBasedOnSymmetrySign(float* scale, char p3, char p4, char p5, int p6);
};

void Sub_4C8F0(cSPEditorBlock* self, int* out, int flag);   // 0049C8F0
void Sub_4C5030(int id, cSPEditorBlock* self);
int  Sub_4C030();                                           // 0044C030
void Sub_4B150(void* p);
void Sub_4B210(void* p);
void Sub_4A8E10(Matrix3* out, const void* a, int b);
void Sub_4769B0(void* a, void* b, void* c);
void Sub_4547F0(void* a, void* b);
void Sub_43A5E0(cSPEditorBlock* self, int a, int b, int c);
void Sub_401050(void* p);
void Sub_4E830();
void Sub_49D390(void* p);
void Sub_49D550(void* p);
void Sub_4C5A0();

// @ 0x00439110
void cSPEditorBlock::SetModelBasedOnSymmetrySign(float* scale, char p3, char p4, char p5, int p6)
{
    if (F435c80()) return;

    uint32_t local[3] = {0, 0, 0};
    if (p6 == 0) {
        Sub_4C8F0(this, (int*)local, 1);
    }
    (void)scale; (void)p3; (void)p4; (void)p5; (void)p6;

    // The remainder builds the model, applies symmetry signs, recurses into
    // symmetric child blocks and refreshes the selection. Reproduced only in
    // outline here.
    Sub_401050(this);
    Sub_4E830();
    Sub_49D390(this);
    Sub_4C5A0();
    SetFlag(9, 1);
}

} // namespace SP
