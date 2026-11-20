// Slice s0106cab0 -- SP::cSPUISpace space-cursor teardown (0x0106cab0, 215 bytes).
//
// Called from SP::cSPUISpace::Update (0x010743a0) right after UpdateActiveToolCursor.
// While the space cursor's "active" flag (0x00ff3ce0, byte at +0x94 of the object held in
// cSPUISpace+0x238) is set, it walks every tool entry registered under the cursor key
// (cSPUISpace+0x23c) in the EASTL hashtable at cSPUISpace+0x25c and releases each value,
// then releases the two rollover effects at +0x298/+0x29c. Finally it refreshes the
// visibility of the cursor window (id 0x5d42af0): shown only while the cursor is active
// and the UI sound helper's flag (0x00a98020) is clear.
//
// Retail's cSPUISpace layout differs from the 2008 dev PDB (mGlobalLayout sits at +0x224
// in retail, +0x258 in the PDB), so the members are reached through a local stub with the
// offsets the disassembly gives.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

typedef unsigned int uint32;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

// ---------------------------------------------------------------- EASTL hashtable
// Node layout taken from the shared equal_range body at 0x009a6dd0:
// key at +0x00, mapped value at +0x04, chain pointer at +0x08.
namespace eastl {
struct hash_node {
    uint32 mKey;                              // +0x00
    void*  mpValue;                           // +0x04
    hash_node* mpNext;                        // +0x08
};
struct hashtable_iterator {
    hash_node*  mpNode;                       // +0x00
    hash_node** mpBucket;                     // +0x04
};
struct hashtable_range {
    hashtable_iterator first;                 // +0x00
    hashtable_iterator second;                // +0x08
};
}  // namespace eastl

// Object reached through the node's mapped value; only the +0x2c slot is used here.
struct IReleasable {
    virtual void r00(); virtual void r04(); virtual void r08(); virtual void r0c();
    virtual void r10(); virtual void r14(); virtual void r18(); virtual void r1c();
    virtual void r20(); virtual void r24(); virtual void r28();
    virtual void Release();                   // +0x2c
};

// Hashtable instance embedded in cSPUISpace (+0x25c).  The shared equal_range body
// (0x009a6dd0) reads the bucket array at +0x04 and the bucket count at +0x08.
struct Hashtable {
    uint32                          mUnknown00;   // +0x00
    eastl::hash_node**              mpBucketArray;  // +0x04
    uint32                          mnBucketCount;  // +0x08
    void equal_range(eastl::hashtable_range* out, const uint32& key);   // 0x009a6dd0
};

// ---------------------------------------------------------------- UTFWin windows
struct Win {
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10(); virtual void w14(); virtual void w18(); virtual void w1c();
    virtual void w20(); virtual void w24(); virtual void w28(); virtual void w2c();
    virtual void w30(); virtual void w34(); virtual void w38(); virtual void w3c();
    virtual void w40(); virtual void w44(); virtual void w48(); virtual void w4c();
    virtual void w50(); virtual void w54(); virtual void w58(); virtual void w5c();
    virtual void w60(); virtual void w64(); virtual void w68(); virtual void w6c();
    virtual void w70(); virtual void w74(); virtual void w78();
    virtual void SetVisible(int a, bool b);   // +0x7c
};

struct cSPUIGlobalUI {
    Win* FindWindowByID(uint32 id);           // 0x00e012b0
};

// ---------------------------------------------------------------- UI sound helper
struct UISoundHelper {
    bool GetFlag();                           // 0x00a98020
};
UISoundHelper* GetUISoundHelper();            // 0x01015df0

namespace SP {

// The space-cursor object held in cSPUISpace+0x238.  Retail keeps three plain members and
// exposes them through the out-of-line accessors 0x00ff3ce0 (byte +0x94), 0x00ff3f00
// (dword +0x8c) and 0x00ff3f10 (dword +0x90).
struct cSPUISpaceCursor {
    char pad00[0x94];
    bool IsActive();                          // 0x00ff3ce0
};

class cSPUISpace {
public:
    char            pad000[0x224];
    cSPUIGlobalUI*  mpGlobalUI;               // +0x224
    char            pad228[0x238 - 0x228];
    cSPUISpaceCursor* mpCursor;               // +0x238
    uint32          mCursorKey;               // +0x23c
    char            pad240[0x25c - 0x240];
    Hashtable       mCursorTable;             // +0x25c
    char            pad268[0x298 - 0x268];
    IReleasable*    mpRollover298;            // +0x298
    IReleasable*    mpRollover29c;            // +0x29c

    void FUN_0106cab0();
};

}  // namespace SP

// @ 0x0106cab0
void SP::cSPUISpace::FUN_0106cab0()
{
    bool active = mpCursor->IsActive();
    if (active) {
        eastl::hashtable_range range;
        mCursorTable.equal_range(&range, mCursorKey);
        eastl::hash_node*  node = range.first.mpNode;
        eastl::hash_node*  end  = range.second.mpNode;
        _ReadWriteBarrier();          // keeps end's load before the bucket load, so cl picks ebx directly
        eastl::hash_node** bucket = range.first.mpBucket;
        while (node != end) {
            ((IReleasable*)node->mpValue)->Release();
            node = node->mpNext;
            if (!node) {
                do {
                    node = *++bucket;
                } while (!node);
            }
        }
        IReleasable* rollover = mpRollover298;
        if (rollover)
            rollover->Release();
        rollover = mpRollover29c;
        if (rollover)
            rollover->Release();
    }

    Win* window = mpGlobalUI->FindWindowByID(0x5d42af0);
    window->SetVisible(1, active && !GetUISoundHelper()->GetFlag());
}
