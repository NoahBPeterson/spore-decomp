// Same shape as s0137e100's cSPAttachment_desc dynamic initializer (0x0137e1b0):
// computes FNVHash over the shared name string 0x1483a90 ("cSPAttachment") and
// constructs the ClassDesc at 0x16ad508 with the fields table at 0x16b1918.
// Flags: (default)
struct FieldDesc;
unsigned FNVHash(const char* s, unsigned seed, int mode);   // 0x00932E80

struct ClassDesc {
    char pad[0x2c];
    ClassDesc(const char* name, FieldDesc* fields, unsigned hash, int a, int b,
              int c, int d, int e, int f, int g);           // 0x00E4A7D0 (__thiscall)
};


// @ 0x0137df70
extern FieldDesc cFields_16b1918[];
ClassDesc g_desc_16ad508("cSPAttachment", cFields_16b1918,
    FNVHash("cSPAttachment", 0x811c9dc5, 1), 0x28, 0, 0, 0, 0, 0, 0);
