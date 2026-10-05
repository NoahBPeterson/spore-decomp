// Slice s005b5a30 -- SP::cSPEditorManipulationRotationHandle::Reset
// Flags for this region: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
//
// PARTIAL: the body below reproduces only the entry guard.  The full body is a
// ~6.6 KB /O2 function (see disassembly 0x005b5a30..0x005b742a) built from the
// rotation-handle math, ray picking, symmetry-sign handling and EASTL string
// plumbing visible in the Ghidra decompile.  It is listed in partial.txt.

typedef unsigned char uint8_t;

namespace SP {

class cSPEditorBlock;

class cSPEditorManipulationRotationHandle {
public:
    char pad0[0x1c];
    void* mRotationHandle;      // +0x1c
    cSPEditorBlock* mBlock;     // +0x20
    char pad24[0x148 - 0x24];

    // @ 0x005b5a30
    void Reset(float param_2);
};

void cSPEditorManipulationRotationHandle::Reset(float param_2) {
    (void)param_2;
    if (mBlock == 0)
        return;
    // TODO(partial): rest of the original body not reconstructed.
}

}  // namespace SP
