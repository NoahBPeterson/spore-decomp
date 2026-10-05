// slice s00589ce0 -- SP::cAppModeEditorBase model loading helpers and Undo (1269/359/590/941/689 B).
// All are large editor operations; skeletons only.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

namespace SP {

class cAppModeEditorBase {
public:
    char pad0[0x600];
    void FUN_00589ce0(int* a);                       // 0x00589ce0
    void LoadModelInternal(int model);               // 0x0058a1e0
    void LoadModel(int model, void* a, void* b);     // 0x0058a350
    void Undo(char a, char b);                       // 0x0058a5a0
    void FUN_0058a950();                             // 0x0058a950
};

}  // namespace SP

using namespace SP;

// @ 0x00589ce0
// PARTIAL: loader for a model resource (1269 B).  Skeleton only.
void cAppModeEditorBase::FUN_00589ce0(int* a) { (void)a; }

// @ 0x0058a1e0
// PARTIAL: LoadModelInternal (359 B).  Skeleton only.
void cAppModeEditorBase::LoadModelInternal(int model) { (void)model; }

// @ 0x0058a350
// PARTIAL: LoadModel (590 B).  Skeleton only.
void cAppModeEditorBase::LoadModel(int model, void* a, void* b) { (void)model; (void)a; (void)b; }

// @ 0x0058a5a0
// PARTIAL: Undo (941 B).  Skeleton only.
void cAppModeEditorBase::Undo(char a, char b) { (void)a; (void)b; }

// @ 0x0058a950
// PARTIAL: helper (689 B).  Skeleton only.
void cAppModeEditorBase::FUN_0058a950() {}
