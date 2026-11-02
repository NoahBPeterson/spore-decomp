// src/game/UTFSpore_Win32/EATextBidi.cpp -- migrated from slice(s) s0089e350 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EATextBidi.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Text/AnalysisInfo.h"
#include <string.h>

// ---- items of slice s0089e350 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Text {
struct BidiRecord
{
    uint32_t mValue0;   // +0x00
    uint32_t mValue1;   // +0x04
    uint32_t mLevel;    // +0x08
};
}
}
namespace EA {
namespace Text {
extern const uint32_t gWeakStateActionTable[];   // 0x0142f670
}
}
namespace EA {
namespace Text {
extern const uint32_t gWeakStateTable[];         // 0x0142f990
}
}
namespace EA {
namespace Text {
extern const uint32_t gWeakFinalActionTable[];   // 0x0142f994
}
}
namespace EA {
namespace Text {
extern const uint32_t gNeutralStateActionTable[]; // 0x0142fcb0
}
}
namespace EA {
namespace Text {
extern const uint32_t gNeutralStateTable[];       // 0x0142fd28
}
}
namespace EA {
namespace Text {
extern const uint32_t gNeutralFinalActionTable[]; // 0x0142fd2c
}
}
// ---- items of slice s0089e350 end

// @ 0x0089e740
namespace EA { namespace Text {
uint32_t BidiResolveExplicitImpl(uint32_t level, BidiRecord* pRecords, uint32_t count, int dir, int nesting)
{
    uint32_t i     = 0;
    uint32_t bound = count;

    if (count != 0)
    {
        do
        {
            BidiRecord* const pRecord   = &pRecords[i];
            uint32_t          w         = pRecord->mLevel;
            int               bidiClass = ((int)(w << 20)) >> 27;

            uint32_t newBound = count;              // bound for the next iteration
            uint32_t limit    = count;              // loop limit for the next iteration

            switch (bidiClass)
            {
            case 0xe:
            case 0xf:
                {
                    const uint32_t newLevel = ((level + 1) & ~(uint32_t)1) + 1;
                    ++nesting;
                    if ((int)newLevel > 0xf)
                    {
                        pRecord->mLevel = (w & 0xfffff57f) | 0x500;
                        bidiClass       = 10;
                        break;
                    }
                    pRecord->mLevel = (uint32_t)((newLevel & 0xf) << 12)
                                    | (w & 0xffff057f) | 0x500;
                    i += BidiResolveExplicitImpl(newLevel, pRecord + 1, count - i - 1,
                                                 -(bidiClass != 0xf) & 2, nesting + 1);
                    --nesting;
                    newBound = count;
                }
                break;

            case 0x10:
            case 0x11:
                {
                    const uint32_t newLevel = (level + 2) & ~(uint32_t)1;
                    ++nesting;
                    if ((int)newLevel > 0xf)
                    {
                        pRecord->mLevel = (w & 0xfffff57f) | 0x500;
                        bidiClass       = 10;
                        break;
                    }
                    pRecord->mLevel = (uint32_t)((level + 2 & 0xe) << 12)
                                    | (w & 0xffff057f) | 0x500;
                    i += BidiResolveExplicitImpl(newLevel, pRecord + 1, count - i - 1,
                                                 bidiClass != 0x11, nesting + 1);
                    --nesting;
                    newBound = count;
                }
                break;

            case 0x12:
                pRecord->mLevel = (w & 0xfffff57f) | 0x500;
                bidiClass       = 10;
                if (nesting > 0)
                {
                    newBound = i;
                    limit    = i;
                    if ((int)count > nesting)
                    {
                        --nesting;
                        newBound = bound;
                        limit    = count;
                    }
                }
                break;

            default:
                break;
            }

            count = limit;

            pRecord->mLevel ^= (uint32_t)(level << 12 ^ pRecord->mLevel) & 0xf000;
            {
                const uint32_t lvl = pRecord->mLevel;
                if (dir != 0)
                    bidiClass = dir;
                if ((lvl & 0xf80) != 0x500)
                    pRecord->mLevel = (uint32_t)(bidiClass << 7 ^ lvl) & 0xf80 ^ lvl;
            }

            ++i;
            bound = newBound;
        } while (i < bound);
    }
    return i;
}
}}  // namespace EA::Text

// @ 0x0089e8e0
namespace EA { namespace Text {
void BidiResolveWeak(uint32_t level, BidiRecord* pRecords, uint32_t count)
{
    int      state    = 2 - (int)((level & 1) != 0);
    int      runLen   = 0;
    uint32_t curLevel = 0;
    uint32_t i        = 0;
    uint32_t uLevel   = level;

    if (count != 0)
    {
        uint32_t* pLevel = &pRecords[0].mLevel;
        do
        {
            uint32_t w         = *pLevel;
            uint32_t prevLevel = uLevel;

            if ((w & 0xf80) == 0x500)
            {
                w = (uint32_t)(uLevel << 12 ^ w) & 0xf000 ^ w;
                *pLevel = w;

                if (runLen + 1 == (int)count && uLevel != level)
                {
                    uint32_t t = uLevel & 0x80000001;
                    if ((int)t < 0)
                        t = (t - 1 | 0xfffffffe) + 1;
                    *pLevel = (uint32_t)(((t + 1) * 0x80) ^ w) & 0xf80 ^ w;
                    state   = (((int)(*pLevel << 20)) >> 27) + state * 10;
                    goto doState;
                }
                if (runLen + 1 < (int)count)
                {
                    prevLevel = (uint32_t)((int)(pLevel[3] << 0x10) >> 0x1c);
                    if (uLevel != prevLevel && (pLevel[3] & 0xf80) != 0x500)
                    {
                        uint32_t hi = prevLevel;
                        if ((int)prevLevel < (int)uLevel)
                            hi = uLevel;
                        uint32_t t = hi & 0x80000001;
                        if ((int)t < 0)
                            t = (t - 1 | 0xfffffffe) + 1;
                        *pLevel = (uint32_t)(((t + 1) & 0x1f) << 7)
                                | (uint32_t)((hi & 0xf) << 12) | (w & 0xffff007f);
                        goto afterState;
                    }
                }
                if (curLevel != 0)
                    ++curLevel;
                goto afterState;
            }

            state = (int)((*pLevel << 0x14) >> 0x1b) + state * 10;

        doState:
            {
                uint32_t action = gWeakStateActionTable[state];
                uint32_t act    = (uint32_t)((int)action >> 4) & 0xf;
                if (act != 0xf)
                {
                    uint32_t* p    = (uint32_t*)((char*)pRecords + (i - curLevel) * 0xc);
                    uint32_t* pEnd = (uint32_t*)((char*)p + curLevel * 0xc);
                    if (p != pEnd)
                    {
                        do
                        {
                            p[2] = p[2] & 0xfffff07f | act << 7;
                            p    = (uint32_t*)((char*)p + 0xc);
                        } while (p != pEnd);
                    }
                    curLevel = 0;
                }
                if ((action & 0xf) != 0xf)
                    *pLevel = *pLevel ^ ((action & 0xf) << 7 ^ *pLevel) & 0xf80;
                if ((action & 0x100) != 0)
                    ++curLevel;
                state  = (int)gWeakStateTable[state];
                uLevel = prevLevel;
            }

        afterState:
            ++i;
            pLevel += 3;
        } while (i < count);
    }

    {
        uint32_t t = uLevel & 0x80000001;
        if ((int)t < 0)
            t = (t - 1 | 0xfffffffe) + 1;
        uint32_t act = (uint32_t)((int)gWeakFinalActionTable[t + state * 10] >> 4) & 0xf;
        if (act != 0xf)
        {
            uint32_t* p    = (uint32_t*)((char*)pRecords + (i - curLevel) * 0xc);
            uint32_t* pEnd = (uint32_t*)((char*)p + curLevel * 0xc);
            if (p != pEnd)
            {
                do
                {
                    p[2] = p[2] & 0xfffff07f | act << 7;
                    p    = (uint32_t*)((char*)p + 0xc);
                } while (p != pEnd);
            }
        }
    }
}
}}  // namespace EA::Text

// @ 0x0089eb00
namespace EA { namespace Text {
void BidiResolveNeutral(uint32_t level, BidiRecord* pRecords, uint32_t count)
{
    int      runLen = 0;
    uint32_t i      = 0;
    uint32_t dir    = ~level & 1;
    uint32_t uLevel = level;

    if (count != 0)
    {
        uint32_t* pLevel = &pRecords[0].mLevel;
        do
        {
            int cls = ((int)(*pLevel << 0x14)) >> 0x1b;

            if (cls == 10)
            {
                if (runLen != 0)
                    ++runLen;
            }
            else
            {
                int      state  = cls + (int)dir * 5;
                uint32_t action = gNeutralStateActionTable[state];
                uint32_t act    = (uint32_t)((int)action >> 4) & 0xf;

                if (act == 3)
                {
                    uint32_t t = uLevel & 0x80000001;
                    if ((int)t < 0)
                        t = (t - 1 | 0xfffffffe) + 1;
                    act = t + 1;
                }
                if (act != 0)
                {
                    uint32_t* p    = (uint32_t*)((char*)pRecords + (i - runLen) * 0xc);
                    uint32_t* pEnd = (uint32_t*)((char*)p + runLen * 0xc);
                    if (p != pEnd)
                    {
                        do
                        {
                            p[2] = p[2] & 0xfffff07f | (act & 0x1f) << 7;
                            p    = (uint32_t*)((char*)p + 0xc);
                        } while (p != pEnd);
                    }
                    runLen = 0;
                }

                uLevel = action & 0xf;
                if (uLevel != 0x100 && uLevel != 0)
                    *pLevel = *pLevel ^ (uLevel << 7 ^ *pLevel) & 0xf80;
                if ((action & 0x100) != 0)
                    ++runLen;

                dir    = gNeutralStateTable[state];
                uLevel = (uint32_t)((int)(*pLevel << 0x10) >> 0x1c);
            }

            ++i;
            pLevel += 3;
        } while (i < count);
    }

    {
        uint32_t t = uLevel & 0x80000001;
        if ((int)t < 0)
            t = (t - 1 | 0xfffffffe) + 1;
        uint32_t act = (uint32_t)((int)gNeutralFinalActionTable[t + dir * 5] >> 4) & 0xf;
        uint32_t n   = t + 1;
        if (act != 3)
            n = act;
        if (n != 0)
        {
            uint32_t* p    = (uint32_t*)((char*)pRecords + (i - runLen) * 0xc);
            uint32_t* pEnd = (uint32_t*)((char*)p + runLen * 0xc);
            if (p != pEnd)
            {
                do
                {
                    p[2] = p[2] & 0xfffff07f | (n & 0x1f) << 7;
                    p    = (uint32_t*)((char*)p + 0xc);
                } while (p != pEnd);
            }
        }
    }
}
}}  // namespace EA::Text
