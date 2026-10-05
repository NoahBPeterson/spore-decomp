// Slice s004a4d60: SP editor pinning pick (single very large /Od function).
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

struct cSPEditorBlock { virtual void _v0(); };

// @ 0x4a4d60
void PickBlockForPinning(cSPEditorBlock* block) { (void)block; }
