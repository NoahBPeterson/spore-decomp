// Slice s00f41cf0 -- scenario tutorial action evaluation driver.
// Kept in a separate translation unit: 0x00f42a00 (in s00f41cf0.cpp) must see this
// definition as an out-of-line call, which a same-TU definition would turn into a
// local call and change 0x00f42a00's byte match.
#include "types.h"

struct Action {
    int32_t  mType;                 // +0x000
    int32_t  mParam1;               // +0x004
    int32_t  mParam2;               // +0x008
    int32_t  mParam3;               // +0x00c
    char     pad10[0x14 - 0x10];    // +0x010
    uint32_t mFlags;                // +0x014
    char     pad18[0x184 - 0x18];   // +0x018
    int32_t  mState;                // +0x184
};

struct Tutorial {
    char     pad00[0x84];           // +0x000
    Action*  mActionBegin;          // +0x084
    Action*  mActionEnd;            // +0x088
    char     pad8c[0x534 - 0x8c];   // +0x08c
};

struct ScenarioManager {
    char      pad00[0x23c];         // +0x000
    Tutorial* mTutorialBegin;       // +0x23c
    Tutorial* mTutorialEnd;         // +0x240
};

struct Obj6c0200 {
    void* FUN_006c0200();           // 0x006c0200
};
struct ObjEE3020 {
    void FUN_00ee3020();            // 0x00ee3020
};
struct ScenarioGlobals {
    char pad00[0x14];               // +0x000
    Obj6c0200* mpField14;           // +0x014
};
extern void* g_16c7aa4;             // 0x016c7aa4

int  __cdecl FUN_00efc520();        // 0x00efc520  ScenarioTutorials_GetActive
void __cdecl FUN_00efc8c0(int);     // 0x00efc8c0  ScenarioTutorials_SetActive

struct ScenarioObj {
    char    pad00[0x10];            // +0x000
    void*   mpManager;              // +0x010

    bool Eval427c0();               // 0x00f427c0
    bool f_41dc0(Action* a, int idx, void* p);                    // 0x00f41dc0
    bool f_420d0(int idx, Action* a, int n, int* out, void* p);   // 0x00f420d0
};

static int TutorialCount(void* manager)
{
    ScenarioManager* mgr = (ScenarioManager*)manager;
    return (int)(mgr->mTutorialEnd - mgr->mTutorialBegin);
}

// @ 0x00f427c0
bool ScenarioObj::Eval427c0()
{
    char result = 1;
    int saved = FUN_00efc520();
    int idx = 0;
    int count = TutorialCount(mpManager);

    if (count > 0) {
        int off = 0;
        do {
            FUN_00efc8c0(idx);

            Tutorial* tutorial = 0;
            if (idx >= 0) {
                ScenarioManager* mgr = (ScenarioManager*)mpManager;
                int n = (int)(mgr->mTutorialEnd - mgr->mTutorialBegin);
                if (idx < n)
                    tutorial = (Tutorial*)((char*)mgr->mTutorialBegin + off);
            }
            if (tutorial == 0)
                break;

            int actionCount = (int)(tutorial->mActionEnd - tutorial->mActionBegin);
            unsigned actionOffset = 0;
            unsigned j = 0;
            if (actionCount != 0) {
                do {
                    Action* a = (Action*)((char*)tutorial->mActionBegin + actionOffset);
                    bool matched = false;
                    if (f_41dc0(a, idx, 0) == 0)
                        goto lab_set;
                    for (unsigned k = 0; k < j; ++k) {
                        Action* prev = &tutorial->mActionBegin[k];
                        if (a->mType != prev->mType)
                            continue;
                        if (a->mParam1 == prev->mParam1) {
                            if ((a->mType != 9 && a->mType != 6 && a->mType != 10) ||
                                (a->mParam2 == prev->mParam2 && a->mParam2 != -1)) {
                                matched = true;
                                break;
                            }
                        } else if ((a->mType == 9 || a->mType == 6 || a->mType == 10) &&
                                   a->mParam1 == prev->mParam2 &&
                                   a->mParam2 == prev->mParam1) {
                            matched = true;
                            break;
                        }
                    }
                    if (matched)
                        a->mState = 0x17;
                    else {
                        a->mFlags &= ~1u;
                        goto lab_next;
                    }
                lab_set:
                    a->mFlags |= 1;
                    result = 0;
                lab_next:
                    actionOffset += 0x188;
                    ++j;
                } while (j < (unsigned)actionCount);
            }

            if (f_420d0(idx, 0, -1, 0, 0) != 0)
                result = 0;

            off += 0x534;
            ++idx;
        } while (idx < TutorialCount(mpManager));
    }

    FUN_00efc8c0(saved);

    ScenarioGlobals* globals = (ScenarioGlobals*)g_16c7aa4;
    void* refreshed = globals->mpField14->FUN_006c0200();
    ((ObjEE3020*)refreshed)->FUN_00ee3020();

    return result;
}
