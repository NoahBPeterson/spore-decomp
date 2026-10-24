// Slice s00e0f050 -- minimap window icon bookkeeping: erasing every icon from the icon tree and the
// single-node erase helper shared with the tree's remove path.
// Flags: /O2 /MD /Gy /EHsc /TP /arch:SSE2 /fp:fast
#include "types.h"

#pragma warning(disable : 4100)

class cRefCounted {
public:
    virtual void r00();                                  // +0x00
    virtual void Release();                              // +0x04
};

// Node of the minimap icon tree: icon id at +0x10, value pointer at +0x28.
struct cIconNode {
    uint8_t         pad000[0x10];                        // +0x00 .. +0x0f
    uint32_t        mIconId;                             // +0x10
    uint8_t         pad014[0x14];                        // +0x14 .. +0x27
    cRefCounted*    mpValue;                             // +0x28
};

// Red-black tree header embedded in the owning objects.
struct cRBTreeHeader {
    uint8_t pad000[0x10];                                // +0x00 .. +0x0f
};

void* __cdecl RBTreeIncrement(cIconNode* pNode);         // 0x00921580
void  __cdecl RBTreeErase(cIconNode* pNode, cRBTreeHeader* pTree); // 0x00921880
void  __cdecl operator_delete_array(void* p);            // 0x00f47380

class cIconTree {
public:
    uint8_t         pad000[4];                           // +0x00
    cRBTreeHeader   mTree;                               // +0x04
    int32_t         mCount;                              // +0x14

    void FUN_00e0f1a0(cIconNode** ppOut, cIconNode* pNode);
};

class cSPUIMinimapWin {
public:
    void FUN_00e0f050();
    void FUN_00e0f100(float a1, float a2, float a3, float a4);
    void FUN_00e0f1a0();
    void draw_civilization_borders();
    ~cSPUIMinimapWin();
    bool RemoveIcon(uint32_t iconId, int first, int flags);
    bool RemoveAllIcons();
    void FUN_00e0fb90(uint32_t mask);
    void CRG_Minimap();
    void FUN_00e0ff80();

    uint8_t         pad000[0x324];                       // +0x000 .. +0x323
    cIconNode*      mpFirstIcon;                         // +0x324
    uint8_t         pad328[8];                           // +0x328 .. +0x32f
    uint32_t        mIconCount;                          // +0x330
};

// @ 0xe0f050 cSPUIMinimapWin::FUN_00e0f050
void __thiscall cSPUIMinimapWin::FUN_00e0f050()
{
}

// @ 0xe0f100 cSPUIMinimapWin::FUN_00e0f100
void __thiscall cSPUIMinimapWin::FUN_00e0f100(float a1, float a2, float a3, float a4)
{
    (void)a1; (void)a2; (void)a3; (void)a4;
}

// @ 0xe0f1a0 cIconTree::FUN_00e0f1a0
void __thiscall cIconTree::FUN_00e0f1a0(cIconNode** ppOut, cIconNode* pNode)
{
    --mCount;
    cIconNode* pNext = (cIconNode*)RBTreeIncrement(pNode);
    RBTreeErase(pNode, &mTree);
    cRefCounted* pValue = pNode->mpValue;
    if (pValue)
        pValue->Release();
    operator_delete_array(pNode);
    *ppOut = pNext;
}

// @ 0xe0f2c0 cSPUIMinimapWin::draw_civilization_borders
void __thiscall cSPUIMinimapWin::draw_civilization_borders()
{
}

// @ 0xe0f810 cSPUIMinimapWin::~cSPUIMinimapWin
cSPUIMinimapWin::~cSPUIMinimapWin()
{
}

// @ 0xe0f9c0 cSPUIMinimapWin::RemoveIcon
bool __thiscall cSPUIMinimapWin::RemoveIcon(uint32_t iconId, int first, int flags)
{
    (void)iconId;
    (void)first;
    (void)flags;
    return true;
}

// @ 0xe0fb50 cSPUIMinimapWin::RemoveAllIcons
bool __thiscall cSPUIMinimapWin::RemoveAllIcons()
{
    bool ok = true;
    while (mIconCount > 0) {
        if (ok)
            ok = RemoveIcon(mpFirstIcon->mIconId, 1, 0);
        else
            ok = false;
    }
    return ok;
}

// @ 0xe0fb90 cSPUIMinimapWin::FUN_00e0fb90
void __thiscall cSPUIMinimapWin::FUN_00e0fb90(uint32_t mask)
{
    (void)mask;
}

// @ 0xe0fc90 cSPUIMinimapWin::CRG_Minimap
void __thiscall cSPUIMinimapWin::CRG_Minimap()
{
}

// @ 0xe0ff80 cSPUIMinimapWin::FUN_00e0ff80
void __thiscall cSPUIMinimapWin::FUN_00e0ff80()
{
}
