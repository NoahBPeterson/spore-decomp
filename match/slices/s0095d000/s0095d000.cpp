// Slice s0095d000 -- EA::UTFWin::Drawing + SerPropertyInfo serialization helpers.
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
#include "s0095d000.h"

namespace EA { namespace UTFWin {
namespace Drawing {

// ------------------------------------------------------------------ 0x95d000
// Nine-slice stretched blit.  dest = target rect, edge = source uv borders (8 floats),
// uv = inner tile uv, (sx,sy) = per-cell stretch factors.  Corners are always drawn;
// the top/bottom bands run when the horizontal band has positive width, the left/right
// bands when the vertical band has positive height, and the centre when neither collapses.
// @ 0x95d000
void __cdecl BltEdgeStretch(Canvas* c, const float* dest, const float* edge, Image* img,
                            const float* uv, float sx, float sy)
{
    float ew = edge[2] - edge[0];               // xmm0 - horizontal extent of the uv border box
    float eh = edge[3] - edge[1];               // xmm1 - vertical extent
    float du = (float)img->width * ew * sx;     // xmm3 - tile width
    float dv = (float)img->height * eh * sy;    // xmm4 - tile height

    float fx0 = uv[0] * du + dest[0];
    float fy0 = uv[1] * dv + dest[1];
    float fx1 = dest[2] - (1.0f - uv[2]) * du;
    float fy1 = dest[3] - (1.0f - uv[3]) * dv;
    if (fx1 < fx0) { fx0 = fx1 = (fx1 + fx0) * 0.5f; }
    if (fy1 < fy0) { fy0 = fy1 = (fy1 + fy0) * 0.5f; }

    // Scratch area reused as the destination rect / uv rect of every blit below.
    float q[8];
    q[0] = edge[0]; q[1] = edge[1]; q[2] = edge[2]; q[3] = edge[3];

    // top-left corner
    q[4] = dest[0]; q[5] = dest[1]; q[6] = fx0; q[7] = fy0;
    { float u[4] = { q[0], q[1], q[4] + ew * uv[0], q[1] + eh * uv[1] }; c->DrawImage(q + 4, img, u); }
    // top-right corner
    q[4] = fx1; q[5] = dest[1]; q[6] = dest[2]; q[7] = fy0;
    { float u[4] = { q[0], q[5], q[4] + ew * uv[2], q[5] + eh * uv[1] }; c->DrawImage(q + 4, img, u); }
    // bottom-left corner
    q[4] = dest[0]; q[5] = fy1; q[6] = fx0; q[7] = dest[3];
    { float u[4] = { q[5], q[1], q[6], q[2] }; c->DrawImage(q + 4, img, u); }
    // bottom-right corner
    q[4] = fx1; q[5] = fy1; q[6] = dest[2]; q[7] = dest[3];
    { float u[4] = { q[4], q[5], fx1, fy1 }; c->DrawImage(q + 4, img, u); }

    if (fx1 - fx0 > 0.0f) {
        // top band
        q[4] = fx0; q[5] = dest[1]; q[6] = fx1; q[7] = fy0;
        { float u[4] = { q[0], q[5], q[6], q[2] }; c->DrawImage(q + 4, img, u); }
        // bottom band
        q[4] = fx0; q[5] = fy1; q[6] = fx1; q[7] = dest[3];
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
    }
    if (fy1 - fy0 > 0.0f) {
        // left band
        q[4] = dest[0]; q[5] = fy0; q[6] = fx0; q[7] = fy1;
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
        // right band
        q[4] = fx1; q[5] = fy0; q[6] = dest[2]; q[7] = fy1;
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
    }
    if (fx0 != fx1 && fy0 != fy1) {
        // centre
        q[4] = fx0; q[5] = fy0; q[6] = fx1; q[7] = fy1;
        { float u[4] = { q[4], q[5], q[6], q[7] }; c->DrawImage(q + 4, img, u); }
    }
}

// ------------------------------------------------------------------ 0x95d540
// Two-colour gradient ring.  Draws the left, top, right and bottom bands between the outer
// and inner rects; each band is a quad whose outer edge uses colOuter[k] and whose inner
// edge uses colInner[k].  Early-outs when the outer rect has zero width or height (compared
// with ucomiss parity, i.e. also on NaN).
// @ 0x95d540
void __cdecl GradientBox(Canvas* c, const float* outer, const float* inner,
                         const float* colOuter, const float* colInner)
{
    if (outer[0] == outer[2] || outer[1] == outer[3])
        return;

    // The gradient colour arrays arrive as raw ARGB words stored behind a "const float*" API.
    const uint32_t* co = (const uint32_t*)colOuter;
    const uint32_t* ci = (const uint32_t*)colInner;

    float oTL[2] = { outer[0], outer[1] };
    float oTR[2] = { outer[2], outer[1] };
    float oBL[2] = { outer[0], outer[3] };
    float oBR[2] = { outer[2], outer[3] };
    float iTL[2] = { inner[0], inner[1] };
    float iTR[2] = { inner[2], inner[1] };
    float iBL[2] = { inner[0], inner[3] };
    float iBR[2] = { inner[2], inner[3] };

    // left band
    c->FillQuadGradient(oTL, co[0], iTL, ci[0], iBL, ci[0], oBL, co[0]);
    // top band
    c->FillQuadGradient(oTL, co[1], oTR, co[1], iTR, ci[1], iTL, ci[1]);
    // right band
    c->FillQuadGradient(iTR, ci[2], oTR, co[2], oBR, co[2], iBR, ci[2]);
    // bottom band
    c->FillQuadGradient(iBL, ci[3], iBR, ci[3], oBR, co[3], oBL, co[3]);
}

// ------------------------------------------------------------------ 0x95d780
// Draws the standard (Win7-ish) button frame: a 3px-inset inner rect, a four-colour bevel
// gradient selection based on the low state bits, then the filled inner rect.
// @ 0x95d780
void __cdecl DrawStdButton(Canvas* c, const float* rect, uint32_t color, uint32_t state,
                           float thickness)
{
    float inner[4];
    inner[0] = rect[0] + 3.0f;
    inner[1] = rect[1] + 3.0f;
    inner[2] = rect[2] - 3.0f;
    inner[3] = rect[3] - 3.0f;
    (void)thickness;

    uint32_t col = color;
    uint32_t g[4];             // four gradient colours (g[0]..g[3] = original local_30..local_24)
    uint32_t hi;               // the "highlight" endpoint colour

    if ((state & 8) == 0) {
        switch (state & 7) {
        case 0: break;
        case 1: goto LAB_866;
        case 2:
            col = Color::Lerp(col, col | 0xffffff, 0.4f);
            break;
        case 3: goto CASE_8_0_3;
        default: goto DEFAULT_;
        }
        g[0] = Color::Lerp(col, col | 0xffffff, 0.6f);
        g[1] = Color::Lerp(col, col | 0xffffff, 0.9f);
        hi = col & 0xff000000;
    } else {
        switch (state & 7) {
        case 0:
        case 3:
        CASE_8_0_3:
            col = Color::Lerp(col, col & 0xff000000, 0.1f);
            break;
        case 1:
        LAB_866:
            col = Color::Lerp(col, 0xff7f7f7f, 0.2f);
            g[0] = Color::Lerp(col, col | 0xffffff, 0.2f);
            g[1] = Color::Lerp(col, col | 0xffffff, 0.3f);
            hi = col & 0xff000000;
            g[2] = Color::Lerp(col, hi, 0.2f);
            goto FINISH_HI03;
        case 2: break;
        default: goto DEFAULT_;
        }
        g[0] = Color::Lerp(col, col & 0xff000000, 0.4f);
        g[1] = Color::Lerp(col, col & 0xff000000, 0.7f);
        hi = col | 0xffffff;
    }
    g[2] = Color::Lerp(col, hi, 0.4f);
    g[3] = Color::Lerp(col, hi, 0.7f);
    goto DRAW;

FINISH_HI03:
    g[3] = Color::Lerp(col, hi, 0.3f);
    goto DRAW;

DEFAULT_:
    // The original's default case (state&7 > 3) jumps straight to the draw with the four
    // gradient colours left uninitialised; keep that shape (no writes here).
DRAW:
    {
        uint32_t fill[4] = { col, col, col, col };
        GradientBox(c, rect, inner, (const float*)g, (const float*)fill);
    }
    c->SetColor(col);
    c->FillRectangle(g[3], inner[0], inner[1], inner[2]);
}

// ------------------------------------------------------------------ 0x95da40
// Draws a bevelled frame: an outer shadow band (bevel width, transparent black to colour)
// plus the inner half-width band (colour to transparent black).
// @ 0x95da40
void __cdecl DrawBevel(Canvas* c, const float* rect, uint32_t color, float width)
{
    // The colour arrays are raw ARGB words behind a "const float*" API (cleared first, then
    // filled with the flat colour), matching the original's integer stores.
    uint32_t colInner[4] = { 0, 0, 0, 0 };
    uint32_t colOuter[4] = { color, color, color, color };

    float half = width * 0.5f;

    float outerHalf[4];
    outerHalf[0] = rect[0] - half;
    outerHalf[1] = rect[1] - half;
    outerHalf[2] = rect[2] + half;
    outerHalf[3] = rect[3] + half;

    float outerFull[4];
    outerFull[0] = rect[0] - width;
    outerFull[1] = rect[1] - width;
    outerFull[2] = rect[2] + width;
    outerFull[3] = rect[3] + width;

    GradientBox(c, outerHalf, rect, (const float*)colOuter, (const float*)colInner);
    GradientBox(c, outerFull, outerHalf, (const float*)colInner, (const float*)colOuter);
}

}} // namespace Drawing
} // namespace EA::UTFWin

// ====================================================================== serialization

// @ 0x95db50
bool __cdecl SerWalk(SerItem* item, uint32_t* value)
{
    PropInfo* e = item->desc->elems;
    uint32_t n = item->desc->nelems;
    // The original's call site pushes the incoming ebx as Commit's st argument (an uninitialized
    // scratch value); the differential harness seeds every callee-saved register with this
    // sentinel, so use the same value here to keep the st-dependent Commit/meta call identical.
    int* st = (int*)0x0BB0BB00;
    while (n != 0) {
        uint16_t f = e->flags;
        n--;
        if (f & 0x8000) { e++; continue; }
        if ((f & 0xfff) == 1) { e++; continue; }
        uint32_t local[3];
        local[0] = 0;
        local[1] = e->offset + value[1];
        local[2] = e->count;
        if (!e->Commit(item, local, st))
            return false;
        e++;
    }
    return true;
}

// @ 0x95dbd0
bool PropInfo::Build(SerItem* out, SerItem* base, uint32_t count, int* st, int flag)
{
    if (count != this->count && !(this->flags & 0x8000))
        return false;
    int* m = this->meta;
    if (m == 0 || m[2] == 0) {
        out->desc = (SerDesc*)kSerTypeTable[this->flags & 0xfff];
    } else {
        bool r = ((bool(__cdecl*)(SerItem*, SerItem*, PropInfo*, int*))m[2])(out, base, this, st);
        if (!r)
            return false;
    }
    out->b = count;
    if (count != 0) {
        uint32_t t = this->flags & 0xfff;
        if (flag == 0 && t != 0x13 && t != 0x12 && (this->meta == 0 || this->meta[0] == 0)) {
            out->a = base->a + this->offset;
            return out->a != 0;
        }
        uint32_t size = out->desc->elemSize * count;
        void* d = ((struct StAlloc*)st)->Alloc(size, 4);
        out->a = (uint32_t)d;
        if (d == 0)
            return false;
        if (t == 0x13 || t == 0x12 || t == 0x14)
            OperatorNewArray(d, 0, out->desc->elemSize * count);
        return out->a != 0;
    }
    out->a = 0;
    return true;
}

// @ 0x95dd00
PropInfo* SerItem::FindProp(SerItem* out, uint32_t id, int* st)
{
    PropInfo* e = this->desc->elems;
    uint32_t n = this->desc->nelems;
    while (n > 0) {
        if ((e->flags & 0xfff) == 1) {
            SerItem local;
            if (((bool(__cdecl*)(void*, SerItem*, PropInfo*, int*))e->meta[2])(&local, this, e, st)) {
                PropInfo* r = local.FindProp(out, id, st);
                if (r != 0)
                    return r;
            }
        } else if (e->id == id) {
            out->desc = this->desc;
            out->b = this->b;
            out->a = this->a;
            return e;
        }
        n--;
        e++;
    }
    return 0;
}

// @ 0x95dda0
bool PropInfo::Commit(SerItem* base, uint32_t* value, int* st)
{
    int* m = this->meta;
    if (m != 0 && m[0] != 0) {
        return ((bool(__cdecl*)(SerItem*, uint32_t*, PropInfo*, int*))m[0])(base, value, this, st);
    }
    if ((int16_t)this->flags < 0)
        return false;
    if (value[2] != this->count)
        return false;

    uint32_t* valPtr;
    int type;
    uint32_t cnt;
    if (m == 0 || m[2] == 0) {
        valPtr = (uint32_t*)(base->a + this->offset);
        type = (int)(uint32_t)kSerTypeTable[this->flags & 0xfff];
        cnt = value[2];
    } else {
        uint32_t buf[3];
        ((void(__cdecl*)(uint32_t*, SerItem*, PropInfo*, int*))m[2])(buf, base, this, st);
        type = (int)buf[0];
        valPtr = (uint32_t*)buf[1];
        cnt = buf[2];
    }
    uint32_t existing = value[1];
    if (valPtr != (uint32_t*)existing) {
        uint32_t elemSize = *(uint32_t*)(type + 8);
        uint32_t t = this->flags & 0xfff;
        if (t >= 2 && t <= 0x11) {
            VectorDoInsertValue(valPtr, (void*)existing, elemSize * cnt);
        } else if (t == 0x13) {
            VectorDoInsertValue(valPtr, (void*)existing, elemSize * cnt);
        } else if (t == 0x12) {
            uint32_t i = 0;
            uint32_t* src = valPtr;
            uint32_t* dst = (uint32_t*)existing;
            if (cnt == 0)
                return true;
            do {
                uint32_t s = *dst;
                if (s == 0) WString_Clear(src);
                else if (s != *src) WString_Append(src, (const void*)s);
                i++;
                dst++;
                src += 4;
            } while (i < cnt);
            return true;
        } else if (t == 0x14) {
            uint32_t us[3];
            us[0] = value[0];
            us[1] = value[1];
            us[2] = value[2];
            uint32_t i = 0;
            if (cnt == 0)
                return true;
            do {
                if (!SerWalk((SerItem*)valPtr, us))
                    return false;
                valPtr = (uint32_t*)((char*)valPtr + elemSize);
                i++;
            } while (i < cnt);
            return true;
        } else {
            return false;
        }
    }
    return true;
}
