// Slice s0138b190: static initialisers of the Simulator attribute descriptor
// tables.  Each record is a 15 dword (0x3c byte) attribute description that is
// built on the stack and copied into the global table slot.

typedef unsigned char uchar;
typedef unsigned int  uint;

// Descriptor layout as written by the original initialisers:
//   +0x00 name         +0x04 hash        +0x08 member offset
//   +0x0c .. +0x14     three dwords the initialisers never touch
//   +0x18, +0x1c       two zeroed dwords
//   +0x20              default-offset thunk (0x00692ca0)
//   +0x24 .. +0x38     six accessor/serialiser thunks
struct cAttribute
{
    const char* m_name;             // 0x00
    int         m_hash;             // 0x04
    int         m_offset;           // 0x08
    int         m_reserved0;        // 0x0c
    int         m_reserved1;        // 0x10
    int         m_reserved2;        // 0x14
    void*       m_zero0;            // 0x18
    void*       m_zero1;            // 0x1c
    void*       m_defaultOffset;    // 0x20
    void*       m_get;              // 0x24
    void*       m_set;              // 0x28
    void*       m_parse;            // 0x2c
    void*       m_toString;         // 0x30
    void*       m_fromString;       // 0x34
    void*       m_serialise;        // 0x38
};

// ---------------------------------------------------------------------------
// Accessor thunks referenced by the descriptor tables.  Only their addresses
// matter here, so they are declared as opaque objects.
// ---------------------------------------------------------------------------
extern char s_defaultOffsetThunk;   // 0x00692ca0

extern char s_f26be0;               // 0x00f26be0
extern char s_f26c20;               // 0x00f26c20
extern char s_c2e4e0;               // 0x00c2e4e0
extern char s_692fb0;               // 0x00692fb0
extern char s_f25b80;               // 0x00f25b80
extern char s_f2a510;               // 0x00f2a510

extern char s_ac8750;               // 0x00ac8750
extern char s_ac8780;               // 0x00ac8780
extern char s_693090;               // 0x00693090
extern char s_694fa0;               // 0x00694fa0
extern char s_b1fbf0;               // 0x00b1fbf0
extern char s_57ce00;               // 0x0057ce00

extern char s_ae3430;               // 0x00ae3430
extern char s_ae3450;               // 0x00ae3450
extern char s_693150;               // 0x00693150
extern char s_695080;               // 0x00695080
extern char s_ae5720;               // 0x00ae5720

extern char s_aff840;               // 0x00aff840
extern char s_aff870;               // 0x00aff870
extern char s_692fd0;               // 0x00692fd0
extern char s_694ec0;               // 0x00694ec0
extern char s_595a70;               // 0x00595a70

extern char s_572810;               // 0x00572810
extern char s_572840;               // 0x00572840
extern char s_692ff0;               // 0x00692ff0
extern char s_694ee0;               // 0x00694ee0
extern char s_57cde0;               // 0x0057cde0

extern char s_f2c950;               // 0x00f2c950
extern char s_f268f0;               // 0x00f268f0
extern char s_f26990;               // 0x00f26990
extern char s_f29410;               // 0x00f29410

extern char s_f26ac0;               // 0x00f26ac0
extern char s_f26aa0;               // 0x00f26aa0
extern char s_f27ec0;               // 0x00f27ec0
extern char s_ac8050;               // 0x00ac8050

extern char s_f2e370;               // 0x00f2e370
extern char s_f26b00;               // 0x00f26b00
extern char s_f26ba0;               // 0x00f26ba0
extern char s_f297a0;               // 0x00f297a0
extern char s_f293f0;               // 0x00f293f0
extern char s_f268b0;               // 0x00f268b0
extern char s_f25b60;               // 0x00f25b60
extern char s_f28880;               // 0x00f28880
extern char s_ac88f0;               // 0x00ac88f0
extern char s_6930b0;               // 0x006930b0
extern char s_694fc0;               // 0x00694fc0
extern char s_acbb80;               // 0x00acbb80
extern char s_b6e3a0;               // 0x00b6e3a0
extern char s_ac88c0;               // 0x00ac88c0
extern char s_6930f0;               // 0x006930f0
extern char s_695010;               // 0x00695010
extern char s_acbba0;               // 0x00acbba0
extern char s_c41210;               // 0x00c41210
extern char s_c40e80;               // 0x00c40e80
extern char s_c41b00;               // 0x00c41b00
extern char s_694f00;               // 0x00694f00
extern char s_675ca0;               // 0x00675ca0

// Attribute table of this slice, one 0x3c byte slot per record.
cAttribute g_attributes[32];

// ------------------------------------------------------------------ 0138bc70
// Attribute table of the asset part descriptor (asset handle, lock flag and
// the two deprecated cache keys).
// @ 0x0138bc70
void InitAssetPartAttributes()
{
    cAttribute attr;

    attr.m_name = "mAsset";
    attr.m_hash = 0x1c3f08b3;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0;
    g_attributes[0] = attr;

    attr.m_name = "isLocked";
    attr.m_hash = 0x7c4c078;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ac8750;
    attr.m_set = &s_ac8780;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694fa0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57ce00;
    attr.m_offset = 0x20;
    g_attributes[1] = attr;

    attr.m_name = "assetKeyDEPRECATED";
    attr.m_hash = 0x1c3f08b1;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ae3430;
    attr.m_set = &s_ae3450;
    attr.m_parse = &s_693150;
    attr.m_toString = &s_695080;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_ae5720;
    attr.m_offset = 0x24;
    g_attributes[2] = attr;

    attr.m_name = "serverIDDEPRECATED";
    attr.m_hash = 0x1c3f08b2;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_aff840;
    attr.m_set = &s_aff870;
    attr.m_parse = &s_692fd0;
    attr.m_toString = &s_694ec0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_595a70;
    attr.m_offset = 0x30;
    g_attributes[3] = attr;
}

// ------------------------------------------------------------------ 0138b190
// Attribute table of the simulator class descriptor (class ids, required count,
// visibility, dialog and flags).
// @ 0x0138b190
void InitClassAttributes()
{
    cAttribute attr;

    attr.m_name = "type";
    attr.m_hash = 0x7114b5f;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 0;
    g_attributes[0] = attr;

    attr.m_name = "targetClassIndex";
    attr.m_hash = 0x7114b60;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 4;
    g_attributes[1] = attr;

    attr.m_name = "targetClass2Index";
    attr.m_hash = 0x733df78;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 8;
    g_attributes[2] = attr;

    attr.m_name = "requiredCount";
    attr.m_hash = 0x71d3b1d;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_serialise = &s_57cde0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 0x0c;
    g_attributes[3] = attr;

    attr.m_name = "visibility";
    attr.m_hash = 0x71d3b1e;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ac8750;
    attr.m_set = &s_ac8780;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694fa0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57ce00;
    attr.m_offset = 0x10;
    g_attributes[4] = attr;

    attr.m_name = "dialog";
    attr.m_hash = 0x728ffd81;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f2c950;
    attr.m_set = &s_f268f0;
    attr.m_parse = &s_b1fbf0;
    attr.m_toString = &s_57cde0;
    attr.m_serialise = &s_f29410;
    attr.m_fromString = &s_f26990;
    attr.m_offset = 0x18;
    g_attributes[5] = attr;

    attr.m_name = "flags";
    attr.m_hash = 0x7bbdea5;
    attr.m_zero0 = 0;
    attr.m_zero1 = &s_f26ac0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26aa0;
    attr.m_set = &s_f27ec0;
    attr.m_parse = &s_b1fbf0;
    attr.m_toString = &s_57cde0;
    attr.m_serialise = &s_ac8050;
    attr.m_fromString = &s_b1fbf0;
    attr.m_offset = 0x14;
    g_attributes[6] = attr;
}

// ------------------------------------------------------------------ 0138b9b0
// Attribute table of the visual simulator descriptor (animation state, cast
// name and the graphics override slots).
// @ 0x0138b9b0
void InitVsliderAttributes()
{
    cAttribute attr;

    attr.m_name = "acts";
    attr.m_hash = 0x7114973;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f2e370;
    attr.m_set = &s_f26b00;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f26ba0;
    attr.m_serialise = &s_f297a0;
    attr.m_offset = 0x70;
    g_attributes[0] = attr;

    attr.m_name = "castName";
    attr.m_hash = 0x7114975;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f293f0;
    attr.m_set = &s_f268b0;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b60;
    attr.m_serialise = &s_f28880;
    attr.m_offset = 0x2788;
    g_attributes[1] = attr;

    attr.m_name = "mAsset";
    attr.m_hash = 0x7114976;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0;
    g_attributes[2] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset";
    attr.m_hash = 0x96a94671;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x28;
    g_attributes[3] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset_Secondary";
    attr.m_hash = 0x96a94670;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x50;
    g_attributes[4] = attr;

    attr.m_name = "gfxOverideType";
    attr.m_hash = 0x96a9466e;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x24;
    g_attributes[5] = attr;

    attr.m_name = "gfxOverideTypeSecondary";
    attr.m_hash = 0x96a9466f;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x48;
    g_attributes[6] = attr;
}

// ------------------------------------------------------------------ 0138be20
// Attribute table of the patrol descriptor (wander radius, patrol and
// teleport positions, path and style).
// @ 0x0138be20
void InitPatrolAttributes()
{
    cAttribute attr;

    attr.m_name = "wanderRadius";
    attr.m_hash = 0x76dc170;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_ac88f0;
    attr.m_parse = &s_6930b0;
    attr.m_toString = &s_694fc0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_acbb80;
    attr.m_offset = 0;
    g_attributes[0] = attr;

    attr.m_name = "patrolPositionDEPRECATED";
    attr.m_hash = 0x76dc171;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_b6e3a0;
    attr.m_set = &s_ac88c0;
    attr.m_parse = &s_6930f0;
    attr.m_toString = &s_695010;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_acbba0;
    attr.m_offset = 4;
    g_attributes[1] = attr;

    attr.m_name = "teleportPositionDEPRECATED";
    attr.m_hash = 0x76dc172;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_b6e3a0;
    attr.m_set = &s_ac88c0;
    attr.m_parse = &s_6930f0;
    attr.m_toString = &s_695010;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_acbba0;
    attr.m_offset = 0x10;
    g_attributes[2] = attr;

    attr.m_name = "patrolPath";
    attr.m_hash = 0x7114773;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_c41210;
    attr.m_set = &s_c40e80;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_c41b00;
    attr.m_offset = 0x1c;
    g_attributes[3] = attr;

    attr.m_name = "patrolStyle";
    attr.m_hash = 0x7114774;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x30;
    g_attributes[4] = attr;
}

// ------------------------------------------------------------------ 0138b560
// Attribute table of the simulator descriptor proper.
// @ 0x0138b560
void InitSimulatorAttributes()
{
    cAttribute attr;

    attr.m_name = "acts";
    attr.m_hash = 0x7114973;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f2e370;
    attr.m_set = &s_f26b00;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f26ba0;
    attr.m_serialise = &s_f297a0;
    attr.m_offset = 0x70;
    g_attributes[0] = attr;

    attr.m_name = "castName";
    attr.m_hash = 0x7114975;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f293f0;
    attr.m_set = &s_f268b0;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b60;
    attr.m_serialise = &s_f28880;
    attr.m_offset = 0x2788;
    g_attributes[1] = attr;

    attr.m_name = "mAsset";
    attr.m_hash = 0x7114976;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0;
    g_attributes[2] = attr;

    attr.m_name = "isDeepEditEnabled";
    attr.m_hash = 0x96a9466b;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ac8750;
    attr.m_set = &s_ac8780;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694fa0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57ce00;
    attr.m_offset = 0x20;
    g_attributes[3] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset";
    attr.m_hash = 0x96a94671;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x28;
    g_attributes[4] = attr;

    attr.m_name = "gameplayObjectGfxOverrideAsset_Secondary";
    attr.m_hash = 0x96a94670;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_f26be0;
    attr.m_set = &s_f26c20;
    attr.m_parse = &s_c2e4e0;
    attr.m_toString = &s_692fb0;
    attr.m_fromString = &s_f25b80;
    attr.m_serialise = &s_f2a510;
    attr.m_offset = 0x50;
    g_attributes[5] = attr;

    attr.m_name = "gfxOverideType";
    attr.m_hash = 0x96a9466e;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x24;
    g_attributes[6] = attr;

    attr.m_name = "gfxOverideTypeSecondary";
    attr.m_hash = 0x96a9466f;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_692ff0;
    attr.m_toString = &s_694ee0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_57cde0;
    attr.m_offset = 0x48;
    g_attributes[7] = attr;

    attr.m_name = "assetKeyDEPRECATED";
    attr.m_hash = 0x7114972;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_ae3430;
    attr.m_set = &s_ae3450;
    attr.m_parse = &s_693150;
    attr.m_toString = &s_695080;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_ae5720;
    attr.m_offset = 0x27c4;
    g_attributes[8] = attr;

    attr.m_name = "modelTypeDEPRECATED";
    attr.m_hash = 0x74fc4f6;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_572810;
    attr.m_set = &s_572840;
    attr.m_parse = &s_693090;
    attr.m_toString = &s_694f00;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_675ca0;
    attr.m_offset = 0x27d0;
    g_attributes[9] = attr;

    attr.m_name = "serverIDDEPRECATED";
    attr.m_hash = 0x7114974;
    attr.m_zero0 = 0;
    attr.m_zero1 = 0;
    attr.m_defaultOffset = &s_defaultOffsetThunk;
    attr.m_get = &s_aff840;
    attr.m_set = &s_aff870;
    attr.m_parse = &s_692fd0;
    attr.m_toString = &s_694ec0;
    attr.m_fromString = &s_b1fbf0;
    attr.m_serialise = &s_595a70;
    attr.m_offset = 0x27d8;
    g_attributes[10] = attr;
}
