// @slice s0133ed00
// Property/attribute descriptor registrars.  Each function stamps a run of
// 0x3c-byte Simulator::Attribute records into a contiguous global table.
// Every record is identical in shape: a name, a hash key, a member offset,
// two flag words left at zero, and seven callbacks (default/offset getter,
// two writers, two parsers, an init hook and a serialiser).
//
// The three words at +0x0c/+0x10/+0x14 are never written by any of these
// registrars (the original copies them verbatim from the uninitialised stack
// temporary), so they are modelled as named-but-untouched storage.

typedef unsigned int u32;
typedef void (*AttrFn)();

struct Attribute {
    const char* mpName;    // +0x00  attribute name ("mHealth", ...)
    u32         mKey;      // +0x04  hashed property key
    u32         mOffset;   // +0x08  byte offset of the member in the owner
    u32         mUnk0c;    // +0x0c  uninitialised in the original
    u32         mUnk10;    // +0x10  uninitialised in the original
    u32         mUnk14;    // +0x14  uninitialised in the original
    u32         mFlags18;  // +0x18  always 0
    u32         mFlags1c;  // +0x1c  always 0
    AttrFn      mpfn20;    // +0x20  default/offset accessor (0x692ca0)
    AttrFn      mpfn24;    // +0x24  writer/reader A
    AttrFn      mpfn28;    // +0x28  writer A
    AttrFn      mpfn2c;    // +0x2c  parser/reader A
    AttrFn      mpfn30;    // +0x30  parser A
    AttrFn      mpfn34;    // +0x34  init hook (0xb1fbf0)
    AttrFn      mpfn38;    // +0x38  serialiser
};

// destination tables (one per registrar)
Attribute s_creatureStateAttrs[5];    // 0x01575468
Attribute s_diseaseAttrs[10];         // 0x015756d8
Attribute s_exploreAttrs[9];          // 0x01575978
Attribute s_fetchAttrs[9];            // 0x01575bd8
Attribute s_ufoAttrs[5];              // 0x01576840

// Store order mirrors the original: name, key, the two zero flag words, the
// seven callbacks, then the member offset last.
#define ATTR(dst, nm, k, off, f0, f1, f2, f3, f4, f5, f6)          \
    do {                                                           \
        Attribute t;                                               \
        t.mpName = (nm);                                           \
        t.mKey = (k);                                              \
        t.mFlags18 = 0;                                            \
        t.mFlags1c = 0;                                            \
        t.mpfn20 = (AttrFn)(f0);                                   \
        t.mpfn24 = (AttrFn)(f1);                                   \
        t.mpfn28 = (AttrFn)(f2);                                   \
        t.mpfn2c = (AttrFn)(f3);                                   \
        t.mpfn30 = (AttrFn)(f4);                                   \
        t.mpfn34 = (AttrFn)(f5);                                   \
        t.mpfn38 = (AttrFn)(f6);                                   \
        t.mOffset = (off);                                         \
        (dst) = t;                                                 \
    } while (0)

// @ 0x0133ed00
void FUN_0133ed00()
{
    ATTR(s_creatureStateAttrs[0], "mChangeArchetypeState", 0x3385389d, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_creatureStateAttrs[1], "mProgressSoFar", 0x3385389e, 0x1fc,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_creatureStateAttrs[2], "mChangeArchetypeTo", 0x3385389f, 0x1f4,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_creatureStateAttrs[3], "mNumTotalActions", 0x338538a0, 0x1f8,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_creatureStateAttrs[4], "mKeyHistory", 0x338538a1, 0x200,
         0x692ca0, 0xb04e00, 0xc761c0, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xeafe40);
}

// @ 0x01340070
void FUN_01340070()
{
    ATTR(s_diseaseAttrs[0], "mEradicateType", 0x3852fb1, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[1], "mEradicateMissionState", 0x3852fb2, 0x1f4,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[2], "mMaxNumDiseasedCreatures", 0x3852fb3, 0x1f8,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[3], "mNumDiseasedKills", 0x3852fb4, 0x208,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[4], "mMaxNumHealthyKills", 0x3852fb5, 0x20c,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[5], "mNumHealthyKills", 0x3852fb6, 0x210,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[6], "mTotalNumKillsNeeded", 0x3852fb7, 0x204,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[7], "mMinDiseasedPerHerd", 0x3852fb8, 0x1fc,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[8], "mMaxDiseasedPerHerd", 0x3852fb9, 0x200,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_diseaseAttrs[9], "mCanFail", 0x3852fba, 0x214,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
}

// @ 0x013413f0
void FUN_013413f0()
{
    ATTR(s_exploreAttrs[0], "mExploreMissionState", 0x3852454, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_exploreAttrs[1], "mVisitCities", 0x3852455, 0x1f4,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
    ATTR(s_exploreAttrs[2], "mVisitRadius", 0x3852456, 0x1f8,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_exploreAttrs[3], "mNumVisitedCities", 0x3852457, 0x208,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_exploreAttrs[4], "mCityVisitInfosInitialized", 0x3852459, 0x210,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
    ATTR(s_exploreAttrs[5], "mEffectHeight", 0x3852460, 0x1fc,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_exploreAttrs[6], "mNumCitiesToVisit", 0x3852461, 0x204,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_exploreAttrs[7], "mExploreType", 0x3852462, 0x20c,
         0x692ca0, 0x572810, 0x572840, 0x693090, 0x694f00, 0xb1fbf0, 0x675ca0);
    ATTR(s_exploreAttrs[8], "mCityVisitInfos", 0x3852463, 0x214,
         0x692ca0, 0xc51630, 0xc50e00, 0xc2e4e0, 0x692fb0, 0xb1fbf0, 0xc51440);
}

// @ 0x01342770
void FUN_01342770()
{
    ATTR(s_fetchAttrs[0], "mFetchMissionState", 0x385389d, 0x1f0,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_fetchAttrs[1], "mTypeOfFetch", 0x385389e, 0x1f4,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_fetchAttrs[2], "mFetchArtifactCargoItemID", 0x385389f, 0x1f8,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[3], "mFetchPlantSpeciesKey", 0x3f69492, 0x210,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[4], "mFetchAnimalSpeciesKey", 0x3f69497, 0x21c,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[5], "mFetchCommodityKey", 0x3f69498, 0x228,
         0x692ca0, 0xae3430, 0xae3450, 0x693150, 0x695080, 0xb1fbf0, 0xae5720);
    ATTR(s_fetchAttrs[6], "mSamplerPlate", 0x38538a3, 0x234,
         0x692ca0, 0xc53ac0, 0xc52c60, 0xc2e4e0, 0x692fb0, 0xc52cf0, 0xca8710);
    ATTR(s_fetchAttrs[7], "mDropOffRequired", 0x3f69499, 0x248,
         0x692ca0, 0xac8750, 0xac8780, 0x693090, 0x694fa0, 0xb1fbf0, 0x57ce00);
    ATTR(s_fetchAttrs[8], "mDropOffDistance", 0x3f69500, 0x24c,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
}

// @ 0x01347610
void FUN_01347610()
{
    ATTR(s_ufoAttrs[0], "mUFOType", 0x648cfb0, 4,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
    ATTR(s_ufoAttrs[1], "mPosition", 0x648cfb6, 8,
         0x692ca0, 0xb6e3a0, 0xac88c0, 0x6930f0, 0x695010, 0xb1fbf0, 0xacbba0);
    ATTR(s_ufoAttrs[2], "mHealth", 0x648cfba, 0x14,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_ufoAttrs[3], "mMaxHealth", 0x648cfbe, 0x18,
         0x692ca0, 0x572810, 0xac88f0, 0x6930b0, 0x694fc0, 0xb1fbf0, 0xacbb80);
    ATTR(s_ufoAttrs[4], "mBomberIndex", 0x648cfc2, 0x1c,
         0x692ca0, 0x572810, 0x572840, 0x692ff0, 0x694ee0, 0xb1fbf0, 0x57cde0);
}