// 0x00d30830..0x00d31a8f -- SP::cCreatureModeInputStrategy (SPCreature / SPGonzago).
// Creature-mode mouse input: double-click feedback timers, tuning reload and the
// movement-goal effect spawner.
// Flags: /O2 /MD /Gy /EHsc /TP.

#include "types.h"

struct CNoun
{
    virtual void vfn00();
    virtual void vfn01();
    virtual void vfn02();
    virtual uint32_t GetInteractionTarget();    // slot 0x0c

    CNoun* GetSelectedNoun();                   // 0x00c0ee60
};

struct CNounManager
{
    CNoun* GetAvatar();                         // 0x00b1fdb0
};

CNounManager* GetNounManager();                 // 0x00b3d300

// 0x00d2ffd0: classify an interactable value, reporting whether it is a valid
// interaction target.
uint32_t ClassifyTarget(uint32_t nValue, bool* pbIsTarget);

// ---------------------------------------------------------------------------
// Timers / red-black tree nodes used by the input strategy.
// ---------------------------------------------------------------------------
struct CSpTimer
{
    bool     IsRunning();        // 0x00feba90
    uint64_t GetElapsedTime();   // 0x00bc3190
    void     Restart();          // 0x00bc3130
};

struct CRBTreeNode
{
    /* 000h */ uint8_t   mPad_000[0x14];
    /* 014h */ CSpTimer* mpTimer;    // tree value
};

struct CRBTreeIterator
{
    /* 000h */ CRBTreeNode* mpNode;
};

struct CRBTree
{
    /* 000h */ uint8_t     mPad_000[4];
    /* 004h */ CRBTreeNode  mAnchor;          // sentinel; &mAnchor is end()

    void find(CRBTreeIterator* pIt, const uint32_t& nKey);   // 0x00e5c780
};

struct cCreatureModeInputStrategy
{
    /* 000h */ uint8_t mPad_000[0x6c];
    /* 06ch */ CRBTree mTimerMap;

    bool DidDoubleClick(uint32_t nKey);
};

// double-click acceptance threshold (0x01582bcc)
uint32_t gnDoubleClickThreshold;

// ---------------------------------------------------------------------------
// 0x00d30ee0: SP::cCreatureModeInputStrategy::DidDoubleClick -- true when the
// timer recorded for the click key is still inside the double-click window.
// ---------------------------------------------------------------------------
// @ 0x00d30ee0
bool cCreatureModeInputStrategy::DidDoubleClick(uint32_t nKey)
{
    bool bResult = false;
    CRBTreeIterator it;
    mTimerMap.find(&it, nKey);
    if (it.mpNode != &mTimerMap.mAnchor)
    {
        CSpTimer* pcTimer = it.mpNode->mpTimer;
        if (pcTimer->IsRunning() && pcTimer->GetElapsedTime() <= gnDoubleClickThreshold)
        {
            pcTimer->Restart();
            bResult = true;
        }
        else
        {
            pcTimer->Restart();
        }
    }
    return bResult;
}

// ---------------------------------------------------------------------------
// 0x00d30f60: is the given noun the avatar or a valid interaction target of
// type 7?
// ---------------------------------------------------------------------------
// @ 0x00d30f60
bool FUN_00d30f60(CNoun* pNoun)
{
    if (pNoun != 0)
    {
        if (GetNounManager()->GetAvatar()->GetSelectedNoun() == pNoun)
            return true;

        uint32_t nTarget   = pNoun->GetInteractionTarget();
        bool     bIsTarget = false;
        uint32_t eTarget   = ClassifyTarget(nTarget, &bIsTarget);
        if (bIsTarget && eTarget == 7)
            return true;
    }
    return false;
}