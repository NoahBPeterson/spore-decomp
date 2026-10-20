// Slice s008aea40: EA tsi TrueType hinting interpreter (fnt_*, interp.obj).
// Every operator of the byte-code interpreter, ported from the retail
// disassembly.  The interpreter context holds an instruction pointer, an
// operand stack that grows downwards, the two active point zones and the
// glyph state block.
// Module flags: /O2 /MD /Gy /TP.
#include "types.h"

typedef uint8_t  uint8;
typedef int8_t   int8;
typedef int16_t  int16;
typedef uint16_t uint16;
typedef uint32_t uint32;
typedef int32_t  int32;
typedef unsigned long uintptr_t;

struct fnt_Ctx;
struct fnt_Zone;
struct fnt_State;
struct fnt_FuncDef;

// Function-pointer signatures used through the context.
typedef int32 (*PF_FNT_CALC)(fnt_Ctx*, int32, int32);            // project / round
typedef void  (*PF_FNT_MOVE)(fnt_Ctx*, fnt_Zone*, int32, int32);  // move a point
typedef void  (*PF_FNT_RANGE)(fnt_Ctx*, int32, int32);            // run code range
typedef int32 (*PF_FNT_CVT)(fnt_Ctx*, int32);                     // read CVT entry
typedef int32 (*PF_FNT_COMP)(fnt_Ctx*);                           // compensation
typedef int32 (*PF_FNT_REF)(fnt_State*, int32);                   // ref-distance fixup

// Point zone: one of the three coordinate sets of a glyph.
struct fnt_Zone {
    int32* orgX;    // +0x00 original x
    int32* orgY;    // +0x04 original y
    int32* curX;    // +0x08 current x
    int32* curY;    // +0x0c current y
    int16* orUS;    // +0x10 original u
    int16* orVS;    // +0x14 original v
    int32* curU;    // +0x18
    int32* curV;    // +0x1c
    int32* orgU;    // +0x20
    int32* orgV;    // +0x24
    uint8* tags;    // +0x28 per-point flags
};

// One function definition (FDEF): either built in or defined by a program.
// +0x06 is written as a whole word by FDEF, so the code-block index lives in
// the low byte and the function id in the high byte of the same word.
struct fnt_FuncDef {
    int32  offset;  // +0x00 byte offset of the body
    uint16 length;  // +0x04 body length
    union {
        uint16 opIdx;                  // +0x06 code-block index (word store)
        struct {
            uint8 zone;                // +0x06 code-block index
            int8  funcId;              // +0x07 function number
        };
    };
};

// Rounding state (state+0x58).
struct fnt_RoundState {
    int32     cutIn;     // +0x00 cut-in value
    int32     enabled;   // +0x04 non-zero when cut-in applies
    int32     f08;       // +0x08
    int32     f0c;       // +0x0c
    int32     f10;       // +0x10
    int32     minDist;   // +0x14 minimum distance
    PF_FNT_CALC roundFn; // +0x18 current rounding function
};

// Glyph/face state block (ctx+0x28).
struct fnt_State {
    uint8       pad00[0x0c];  // +0x00
    uint16      cvtCount;     // +0x0c number of CVT entries
    uint8       pad0e[0x4a];  // +0x0e
    fnt_RoundState round;        // +0x58
    uint8       pad74[0x0e];  // +0x74
    uint16      rp0;          // +0x82 reference point 0
    uint16      rp1;          // +0x84 reference point 1
    uint8       pad86[0x04];  // +0x86
    uint8       autoFlip;     // +0x8a flip auto-flip flag
    uint8       pad8b[0x05];  // +0x8b
    fnt_FuncDef* funcs;       // +0x90 functions called by CALL/LOOPCALL
    fnt_FuncDef* zones;       // +0x94 functions reachable by SHC/SHZ
    PF_FNT_REF  projRef;      // +0x98 projection used by MD on the unscaled zone
    int32       codeBase[6];  // +0x9c start of each code block
    uint16      padB4;        // +0xb4
    uint8       grayscale;    // +0xb6 non-zero for grayscale (unscaled) rendering
    uint8       padB7[0x12];  // +0xb7
    uint8       defaultZone;  // +0xc9 code-block index used by FDEF/SHZ
    uint16      numDefs;      // +0xca number of entries in zones
};

// Interpreter context.
struct fnt_Ctx {
    uint8*      ip;            // +0x00 instruction pointer
    uint32      opcode;        // +0x04 current opcode
    fnt_Zone*   zp1;           // +0x08 destination zone
    fnt_Zone*   zp2;           // +0x0c reference zone
    int32       f10;           // +0x10
    uint16      vecX;          // +0x14 projection vector x
    uint16      vecY;          // +0x16 projection vector y
    uint16      f18;           // +0x18
    uint16      f1a;           // +0x1a
    int32       f1c;           // +0x1c
    int32*      stackTop;      // +0x20 operand stack pointer
    int32*      stackLimit;    // +0x24 end of the operand stack
    fnt_State*  state;         // +0x28
    int32       f2c;           // +0x2c
    int32       np;            // +0x30 current reference point
    int32       savedNp;       // +0x34
    int32       savedPoint;    // +0x38
    int32       f3c;           // +0x3c
    int32       f40;           // +0x40
    PF_FNT_MOVE  movePoint;    // +0x44
    PF_FNT_CALC  project;      // +0x48
    PF_FNT_CALC  project2;     // +0x4c
    PF_FNT_RANGE moveZP;       // +0x50
    PF_FNT_CVT   readCvt;      // +0x54
    PF_FNT_COMP  compute;      // +0x58
    int32        f5c[0x0c];    // +0x5c
    void*        movePointTab; // +0x8c per-vector movement callbacks
    int32        f90[0x0c];    // +0x90
    void*        anglePoint;   // +0xc0
    void*        angleDistance;// +0xc4
};

// --- helpers implemented outside this slice -----------------------------
extern "C" {
int32 util_FixMul(int32 a, int32 b);        // 0x008d1590
int32 util_ShortFracMul(int32 a, int32 b);  // 0x008d1670

int32 fnt_Project(fnt_Ctx* ctx, int32 x, int32 y);       // 0x008ac360
int32 fnt_OldProject(fnt_Ctx* ctx, int32 x, int32 y);    // 0x010cca50
int32 fnt_RoundToGridX(fnt_Ctx* ctx, int32 d, int32 c);  // 0x008ac0b0
int32 fnt_RoundToGrid(fnt_Ctx* ctx, int32 d, int32 c);   // 0x008ac040
int32 fnt_Super45Round(fnt_Ctx* ctx, int32 d, int32 c);  // 0x008ac100
int32 fnt_GetCVTScale(fnt_Ctx* ctx);                     // 0x008ac370
void  fnt_ChangeCvt(fnt_Ctx* ctx);                       // 0x008ac460
void  fnt_SetRoundValues();  // 0x008ad190 (ctx in eax, period in edx, flag on stack)
fnt_FuncDef* fnt_Error(fnt_Ctx* ctx);                    // 0x008abf90
}

// Data blocks referenced by fnt_InitInterp.
extern void*  fnt_movePointTable[];   // 0x01432300
extern float  FntAnglePoint[];        // 0x01432238
extern uint16 FntAngleDistance[];     // 0x014322d8

// Skips over the operands of the opcode currently in ctx->opcode.
static void fnt_Skip(fnt_Ctx* ctx);

// @ 0x008aea40
void fnt_UnaryOperand(fnt_Ctx* ctx)
{
    int32* sp  = ctx->stackTop;
    uint32 arg = (uint32)sp[-1];
    int32  op  = (int32)ctx->opcode;
    int32* dst = sp - 1;
    switch (op) {
    case 0x56:
    case 0x57: {
        uint32 r = (uint32)fnt_RoundToGrid(ctx, (int32)arg, 0) >> 6;
        if (op == 0x56) r = r + 1;
        *dst = (int32)(~r & 1);
        ctx->stackTop = sp;
        return;
    }
    case 0x5c:
        *dst = (int32)(arg == 0);
        ctx->stackTop = sp;
        return;
    case 0x64:
        if ((int32)arg < 1) {
            *dst = (int32)-arg;
            ctx->stackTop = sp;
            return;
        }
        break;
    case 0x65:
        *dst = (int32)-arg;
        ctx->stackTop = sp;
        return;
    case 0x67:
        arg = arg + 0x3f;
        arg = arg & 0xffffffc0;
        *dst = (int32)arg;
        ctx->stackTop = sp;
        return;
    case 0x66:
        arg = arg & 0xffffffc0;
        *dst = (int32)arg;
        ctx->stackTop = sp;
        return;
    default:
        ctx->stackTop = dst;
        return;
    }
    *dst = (int32)arg;
    ctx->stackTop = sp;
}

// @ 0x008aeb00
static void fnt_Skip(fnt_Ctx* ctx)
{
    uint32 op = ctx->opcode;
    uint8* ip = ctx->ip;
    switch (op) {
    case 0x40:  // PUSHB
        ctx->ip = ip + *ip + 1;
        return;
    case 0x41:  // PUSHW
        ctx->ip = ip + *ip * 2 + 1;
        return;
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb4:
    case 0xb5:
    case 0xb6:
    case 0xb7:  // MDRP
        ctx->ip = ip + op - 0xaf;
        return;
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf:  // MIRP
        ip = ip + op * 2 - 0x16e;
        break;
    }
    ctx->ip = ip;
}

// @ 0x008aebe0
void fnt_If(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    if (ctx->stackTop[0] == 0) {
        int32 nest = 1;
        do {
            uint32 op = *ctx->ip;
            ctx->opcode = op;
            ctx->ip++;
            if (op == 0x1b) {
                if (nest == 1) return;
            }
            else if (op == 0x58) {
                nest = nest + 1;
            }
            else if (op == 0x59) {
                nest = nest - 1;
            }
            else {
                fnt_Skip(ctx);
            }
        } while (nest != 0);
    }
}

// @ 0x008aec30
void fnt_Else(fnt_Ctx* ctx)
{
    int32 nest = 1;
    do {
        uint32 op = *ctx->ip;
        ctx->opcode = op;
        ctx->ip++;
        if (op == 0x58) {
            nest = nest + 1;
        }
        else if (op == 0x59) {
            nest = nest - 1;
        }
        else {
            fnt_Skip(ctx);
        }
    } while (nest != 0);
}

// @ 0x008aec70
void fnt_JMPR(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    ctx->ip = ctx->ip + (ctx->stackTop[0] - 1);
}

// @ 0x008aec90
void fnt_JROT(fnt_Ctx* ctx)
{
    int32* t = ctx->stackTop - 1;
    if (t[0] != 0) {
        int32 offset = t[-1] - 1;
        t = t - 1;
        ctx->ip = ctx->ip + offset;
        ctx->stackTop = t;
        return;
    }
    t = t - 1;
    ctx->stackTop = t;
}

// @ 0x008aecc0
void fnt_JROF(fnt_Ctx* ctx)
{
    int32* t = ctx->stackTop - 1;
    if (t[0] != 0) {
        t = t - 1;
        ctx->stackTop = t;
        return;
    }
    int32 offset = t[-1] - 1;
    t = t - 1;
    ctx->ip = ctx->ip + offset;
    ctx->stackTop = t;
}

// @ 0x008aecf0
void fnt_Round(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    ctx->stackTop[0] = ctx->state->round.roundFn(ctx, ctx->stackTop[0], 0);
    ctx->stackTop++;
}

// @ 0x008aed20
void fnt_PopPush(fnt_Ctx* ctx)
{
    *(int32* volatile*)&ctx->stackTop = ctx->stackTop;
}

// @ 0x008aed30
void fnt_MD(fnt_Ctx* ctx)
{
    fnt_State* state = ctx->state;
    ctx->stackTop--;
    int32     np    = ctx->np;
    fnt_Zone* zp2   = ctx->zp2;
    int32     point = ctx->stackTop[0];
    fnt_Zone* zp1   = ctx->zp1;
    int32     dist;
    if (zp1 == (fnt_Zone*)ctx->stackLimit || zp2 == (fnt_Zone*)ctx->stackLimit) {
        dist = ctx->project2(ctx,
                             zp2->curX[point] - zp1->curX[np],
                             zp2->curY[point] - zp1->curY[np]);
    }
    else {
        dist = state->projRef(state,
                              ctx->project2(ctx,
                                            (int32)zp2->orUS[point] - (int32)zp1->orUS[np],
                                            (int32)zp2->orVS[point] - (int32)zp1->orVS[np]));
    }
    if (state->round.enabled != 0) {
        int32 comp = ctx->compute(ctx);
        if (dist < 0) {
            int32 d = -dist - comp;
            if (d < 0) d = -d;
            dist = -dist;
            if (d < state->round.enabled) dist = comp;
            dist = -dist;
        }
        else {
            int32 d = dist - comp;
            if (d < 0) d = -d;
            if (d < state->round.enabled) dist = comp;
        }
    }
    int32 value = dist;
    if ((ctx->opcode & 4) != 0) {
        value = state->round.roundFn(ctx, dist, 0);
    }
    if ((ctx->opcode & 8) != 0) {
        int32 lim = state->round.minDist;
        if (dist < 0) {
            lim = -lim;
            if (value <= lim) goto move;
        }
        else if (lim <= value) goto move;
        value = lim;
    }
move:
    int32 proj = ctx->project(ctx,
                              zp2->curX[point] - zp1->curX[np],
                              zp2->curY[point] - zp1->curY[np]);
    ctx->movePoint(ctx, zp2, point, value - proj);
    ctx->savedNp    = np;
    ctx->savedPoint = point;
    if ((ctx->opcode & 0x10) != 0) {
        ctx->np = point;
    }
}

// @ 0x008aeeb0
void fnt_MIRP(fnt_Ctx* ctx)
{
    fnt_Zone*  zp1   = ctx->zp1;
    fnt_State* state = ctx->state;
    ctx->stackTop--;
    uint32     op    = ctx->opcode;
    fnt_Zone*  zp2   = ctx->zp2;
    fnt_RoundState* rs    = &state->round;
    int32      d     = ctx->readCvt(ctx, ctx->stackTop[0]);
    if (rs->enabled != 0) {
        int32 comp = ctx->compute(ctx);
        if (d < 0) {
            int32 t = -d - comp;
            if (t < 0) t = -t;
            d = -d;
            if (t < rs->cutIn) d = comp;
            d = -d;
        }
        else {
            int32 t = d - comp;
            if (t < 0) t = -t;
            if (t < rs->cutIn) d = comp;
        }
    }
    ctx->stackTop--;
    int32 point = ctx->stackTop[0];
    int32 np    = ctx->np;
    ctx->savedNp    = np;
    ctx->savedPoint = point;
    if ((op & 0x10) != 0) {
        ctx->np = point;
    }
    if (zp2 == (fnt_Zone*)ctx->stackLimit) {
        zp2->curX[point] = util_ShortFracMul(d, (int32)ctx->vecX) + zp1->curX[np];
        zp1->orgX[point] = zp2->curX[point];
        zp2->curY[point] = util_ShortFracMul(d, (int32)ctx->vecY) + zp1->curY[np];
        zp1->orgY[point] = zp2->curY[point];
    }
    int32 dx;
    if (ctx->project2 == fnt_Project) {
        dx = zp2->curX[point] - zp1->curX[np];
    }
    else if (ctx->project2 == fnt_OldProject) {
        dx = zp2->curY[point] - zp1->curY[np];
    }
    else {
        dx = ctx->project2(ctx, zp2->curX[point] - zp1->curX[np],
                                zp2->curY[point] - zp1->curY[np]);
    }
    int32 along;
    if (ctx->project == fnt_Project) {
        along = zp2->orgX[point] - zp1->orgX[np];
    }
    else if (ctx->project == fnt_OldProject) {
        along = zp2->orgY[point] - zp1->orgY[np];
    }
    else {
        along = ctx->project(ctx, zp2->orgX[point] - zp1->orgX[np],
                                  zp2->orgY[point] - zp1->orgY[np]);
    }
    if (state->autoFlip != 0 && (int32)((uint32)dx ^ (uint32)d) < 0) {
        d = -d;
    }
    if ((op & 4) != 0) {
        int32 t = d - dx;
        if (t < 0) t = -t;
        if (rs->cutIn < t) d = dx;
        d = rs->roundFn(ctx, d, 0);
    }
    if ((op & 8) != 0) {
        int32 lim = rs->minDist;
        if (dx < 0) {
            lim = -lim;
            if (d <= lim) goto move;
        }
        else if (lim <= d) goto move;
        d = lim;
    }
move:
    ctx->movePoint(ctx, zp2, point, d - along);
}

// @ 0x008af120
void fnt_CALL(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    fnt_State*   state = ctx->state;
    fnt_FuncDef* fd    = state->funcs + ctx->stackTop[0];
    int32 start = state->codeBase[fd->opIdx] + fd->offset;
    ctx->moveZP(ctx, start, (int32)fd->length + start);
}

// @ 0x008af160
void fnt_FDEF(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    fnt_State*   state = ctx->state;
    fnt_FuncDef* fd    = state->funcs + ctx->stackTop[0];
    uint8        zone  = state->defaultZone;
    fd->opIdx = zone;
    fd->offset = (int32)(ctx->ip - (uint8*)state->codeBase[zone]);
    uint8* start = ctx->ip;
    uint32 op = *start;
    ctx->opcode = op;
    while (op != 0x2d) {
        ctx->ip++;
        fnt_Skip(ctx);
        op = *ctx->ip;
        ctx->opcode = op;
    }
    ctx->ip++;
    fd->length = (uint16)((uint16)(uintptr_t)ctx->ip - (uint16)(uintptr_t)start - 1);
}

// @ 0x008af1d0
void fnt_LOOPCALL(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    fnt_State*   state = ctx->state;
    fnt_FuncDef* fd    = state->funcs + ctx->stackTop[0];
    int32  base = state->codeBase[fd->opIdx];
    uint16 len  = fd->length;
    ctx->stackTop--;
    int16 count = (int16)ctx->stackTop[0];
    PF_FNT_RANGE run = ctx->moveZP;
    while ((count = count - 1) >= 0) {
        run(ctx, fd->offset + base, (int32)len + fd->offset + base);
    }
}

// @ 0x008af240
void fnt_SHC(fnt_Ctx* ctx)
{
    fnt_State*   state = ctx->state;
    fnt_FuncDef* fd    = state->zones;
    int16 count = (int16)(state->numDefs - 1);
    while (count >= 0) {
        if (fd->funcId == (int8)ctx->opcode) goto found;
        count = count - 1;
        fd++;
    }
    fd = fnt_Error(ctx);
found:
    int32 start = state->codeBase[fd->zone] + fd->offset;
    ctx->moveZP(ctx, start, (int32)fd->length + start);
}

// @ 0x008af2a0
void fnt_SHZ(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    int8 id = *(int8*)ctx->stackTop;
    fnt_State*   state = ctx->state;
    int16 count = (int16)(state->numDefs - 1);
    fnt_FuncDef* fd = state->zones;
    while (count >= 0) {
        if (fd->funcId == id) goto found;
        count = count - 1;
        fd++;
    }
    fd = 0;
found:
    uint8* start = ctx->ip;
    int32  base  = state->codeBase[state->defaultZone];
    if (fd == 0) {
        fd = state->zones + state->numDefs;
        state->numDefs = (uint16)(state->numDefs + 1);
    }
    fd->zone   = state->defaultZone;
    fd->funcId = id;
    fd->offset = (int32)(ctx->ip - (uint8*)base);
    uint32 op = *ctx->ip;
    ctx->opcode = op;
    while (op != 0x2d) {
        ctx->ip++;
        fnt_Skip(ctx);
        op = *ctx->ip;
        ctx->opcode = op;
    }
    ctx->ip++;
    fd->length = (uint16)((uint16)(uintptr_t)ctx->ip - (uint16)(uintptr_t)start - 1);
}

// @ 0x008af360
void fnt_ClearPointFlags(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    int32  point = ctx->stackTop[0];
    uint8* tags  = ctx->zp1->tags;
    if (ctx->f18 != 0) {
        tags[point] = (uint8)(tags[point] & 0xfe);
    }
    if (ctx->f1a != 0) {
        tags[point] = (uint8)(tags[point] & 0xfd);
    }
}

// @ 0x008af390
void fnt_SetRp0(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    ctx->state->rp0 = (uint16)ctx->stackTop[0];
}

// @ 0x008af3b0
void fnt_SetRp1(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    ctx->state->rp1 = (uint16)ctx->stackTop[0];
}

// Applies a DELTAP/DELTAC nibble run.  ctx arrives in esi in the retail build.
// @ 0x008af3d0
void fnt_DeltaEngine(fnt_Ctx* ctx, PF_FNT_MOVE moveFunc, int32 rp0, int32 shift)
{
    fnt_State* state = ctx->state;
    ctx->stackTop--;
    int32  n     = ctx->stackTop[0];
    uint32 count = (uint32)(n * 2);
    ctx->stackTop = ctx->stackTop - n * 2;
    uint32 coord = (uint32)state->cvtCount;
    if (state->grayscale == 0) {
        coord = (uint32)((util_FixMul((int32)(coord * 2), fnt_GetCVTScale(ctx)) + 1) >> 1);
    }
    int32 delta = (int32)(coord - (uint32)rp0);
    if ((uint32)delta < 0x10) {
        int32 key = delta * 0x10;
        int32 x   = 0;
        int32 step = ((int32)count >> 1) & 0xfffffffe;
        while (step > 2) {
            if ((int32)((uint32)ctx->stackTop[step + x] & 0xfffffff0) < key) {
                x = step + x;
            }
            step = (step >> 1) & 0xfffffffe;
        }
        for (; x < (int32)count; x = x + 2) {
            uint32 v = (uint32)ctx->stackTop[x] & 0xfffffff0;
            if ((int32)v == key) {
                int32 point = ctx->stackTop[x + 1];
                int32 nib   = (int32)((uint32)ctx->stackTop[x] & 0xf);
                nib = nib - (nib < 8 ? 8 : 7);
                int32 d = (nib << 6) >> shift;
                moveFunc(ctx, ctx->zp1, point, d);
            }
            else if (key < (int32)v) {
                return;
            }
        }
    }
}

// The DELTAP/DELTAC wrappers pass ctx in esi (retail convention) and push the
// three arguments (shift, rp0, move function) themselves.
// @ 0x008af4a0
void fnt_DeltaP1(fnt_Ctx* ctx)
{
    fnt_State* state = ctx->state;
    int32 shift = (int32)(state->rp1 & 0xffff);
    int32 rp0   = (int32)(state->rp0 & 0xffff);
    PF_FNT_MOVE fn = ctx->movePoint;
    __asm {
        push esi
        mov  esi, ctx
        push shift
        push rp0
        push fn
        call fnt_DeltaEngine
        add  esp, 0xc
        pop  esi
    }
}

// @ 0x008af4d0
void fnt_DeltaP2(fnt_Ctx* ctx)
{
    fnt_State* state = ctx->state;
    int32 rp0   = (int32)((uint16)(state->rp0 + 0x10) & 0xffff);
    int32 shift = (int32)(state->rp1 & 0xffff);
    PF_FNT_MOVE fn = ctx->movePoint;
    __asm {
        push esi
        mov  esi, ctx
        push shift
        push rp0
        push fn
        call fnt_DeltaEngine
        add  esp, 0xc
        pop  esi
    }
}

// @ 0x008af500
void fnt_DeltaP3(fnt_Ctx* ctx)
{
    fnt_State* state = ctx->state;
    int32 rp0   = (int32)((uint16)(state->rp0 + 0x20) & 0xffff);
    int32 shift = (int32)(state->rp1 & 0xffff);
    PF_FNT_MOVE fn = ctx->movePoint;
    __asm {
        push esi
        mov  esi, ctx
        push shift
        push rp0
        push fn
        call fnt_DeltaEngine
        add  esp, 0xc
        pop  esi
    }
}

// @ 0x008af530
void fnt_DeltaC1(fnt_Ctx* ctx)
{
    fnt_State* state = ctx->state;
    int32 shift = (int32)(state->rp1 & 0xffff);
    int32 rp0   = (int32)(state->rp0 & 0xffff);
    __asm {
        push esi
        mov  esi, ctx
        push shift
        push rp0
        push fnt_ChangeCvt
        call fnt_DeltaEngine
        add  esp, 0xc
        pop  esi
    }
}

// @ 0x008af560
void fnt_DeltaC2(fnt_Ctx* ctx)
{
    fnt_State* state = ctx->state;
    int32 rp0   = (int32)((uint16)(state->rp0 + 0x10) & 0xffff);
    int32 shift = (int32)(state->rp1 & 0xffff);
    __asm {
        push esi
        mov  esi, ctx
        push shift
        push rp0
        push fnt_ChangeCvt
        call fnt_DeltaEngine
        add  esp, 0xc
        pop  esi
    }
}

// @ 0x008af5a0
void fnt_DeltaC3(fnt_Ctx* ctx)
{
    fnt_State* state = ctx->state;
    int32 rp0   = (int32)((uint16)(state->rp0 + 0x20) & 0xffff);
    int32 shift = (int32)(state->rp1 & 0xffff);
    __asm {
        push esi
        mov  esi, ctx
        push shift
        push rp0
        push fnt_ChangeCvt
        call fnt_DeltaEngine
        add  esp, 0xc
        pop  esi
    }
}

// @ 0x008af5e0
void fnt_InitInterp(fnt_Ctx* ctx)
{
    ctx->movePointTab  = fnt_movePointTable;
    ctx->anglePoint    = FntAnglePoint;
    ctx->angleDistance = FntAngleDistance;
}

// @ 0x008af610
void fnt_Round1(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    int32 value = ctx->stackTop[0];
    fnt_RoundState* rnd = (fnt_RoundState*)((uint8*)ctx->state + 0x58);
    __asm {
        mov eax, ctx
        mov edx, value
        push 1
        call fnt_SetRoundValues
        add esp, 4
    }
    rnd->roundFn = fnt_RoundToGridX;
}

// @ 0x008af640
void fnt_Round0(fnt_Ctx* ctx)
{
    ctx->stackTop--;
    int32 value = ctx->stackTop[0];
    fnt_RoundState* rnd = (fnt_RoundState*)((uint8*)ctx->state + 0x58);
    __asm {
        mov eax, ctx
        mov edx, value
        push 0
        call fnt_SetRoundValues
        add esp, 4
    }
    rnd->roundFn = fnt_Super45Round;
}