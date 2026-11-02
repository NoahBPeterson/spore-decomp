// src/game/SPAudio/eapdrtext.cpp -- migrated from slice(s) s00a4e2e0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdrtext.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <stdio.h>
#include <string.h>

// ---- items of slice s00a4e2e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_class;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_binbuf;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_rtext;
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_editor {
    uint32_t     pad00[3];
    t_rtext*     e_rtextlist;    // +0x0c  list of live t_rtext items
    uint32_t     pad10;
    t_rtext*     e_textedfor;    // +0x14
    uint32_t     pad18[14];
    unsigned     e_flags;        // +0x50: bit 0x10 = textdirty
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_gobj {
    t_class* g_pd;      // +0x00
    t_gobj*  g_next;    // +0x04
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_text : t_gobj {
    t_binbuf* te_binbuf;    // +0x08
    void*     te_outlet;    // +0x0c
    void*     te_inlet;     // +0x10
    int16_t   te_xpix;      // +0x14
    int16_t   te_ypix;      // +0x16
    int16_t   te_width;     // +0x18
    int16_t   pad1a;        // +0x1a
    unsigned  te_type;      // +0x1c: low 2 bits
    t_glist*  te_owner;     // +0x24
    t_glist*  te_glist;     // +0x28
    char      te_tag[0x34]; // +0x2c
    void*     te_next;      // +0x60
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_glist {
    uint32_t  pad00[0x28 / 4];
    t_gobj*   gl_list;      // +0x28
    t_glist*  gl_owner;     // +0x2c
    uint32_t  pad30[2];
    float     gl_x1;        // +0x38
    float     gl_y1;        // +0x3c
    float     gl_x2;        // +0x40
    float     gl_y2;        // +0x44
    uint32_t  pad48[6];
    t_editor* gl_editor;    // +0x60
    uint32_t  pad64[5];
    uint32_t  gl_flags;     // +0x78: 0x100 = graph widget, 1 = "goprect"
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
enum { GL_GOPRECT = 0x01, GL_ISGRAPH = 0x100 };
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
struct t_rtext {
    char*     rt_buf;       // +0x00 shared string from binbuf_gettext
    int       rt_bufsize;   // +0x04
    int       rt_selectfrom;// +0x08
    int       rt_selectto;  // +0x0c
    int       rt_active;    // +0x10
    int       rt_xpix;      // +0x14
    int       rt_ypix;      // +0x18
    int       rt_width;     // +0x1c
    int       rt_height;    // +0x20
    t_text*   rt_owner;     // +0x24
    t_glist*  rt_glist;     // +0x28
    char      rt_tag[0x34]; // +0x2c
    t_rtext*  rt_next;      // +0x60
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_rtext*        rtext_entered;       // 0x16754ec
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_glist*        gpEditingCanvas;     // 0x1675470
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_class*        gpCanvasClass;       // 0x1675490
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     getbytes(int n, const char* tag);                            // 0xa49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      freebytes(void* p, int n);                                   // 0xa49650
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      binbuf_gettext(t_binbuf* b, void* a, void* c);               // 0xa47080
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_glist*  glist_getcanvas(t_glist* x);                                 // 0xa4d410
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      SetSerializer(const char* fmt, ...);                         // 0xc2e4e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int*      glist_isselected(t_glist* x, t_gobj* y);                      // 0xa4c710
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       glist_getfont(t_glist* x);                                    // 0xa4ab90
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       sys_fontwidth(int font);                                      // 0xa4d2e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       sys_fontheight(int font);                                     // 0xa4d310
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       sys_fontweight(int font, const char* color);                  // 0xa4d2b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       text_xpix(t_text* x, t_glist* g);                             // 0xa4d920
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       text_ypix(t_text* x, t_glist* g);                             // 0xa4d9c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void      text_drawborder(t_text* x, t_glist* g, const char* tag,
                          int w, int h, int firsttime);                 // 0xa51240
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void*     resizebytes(void* p, int oldsz, int newsz, const char* tag);   // 0xa49670
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int*      binbuf_getvec(t_binbuf* b);                                   // 0x011922c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int       binbuf_getnatom(t_binbuf* b);                                 // 0x011838a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
t_rtext* rtext_new(t_glist* x, t_text* ob);                              // 0xa4e8a0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_free(t_rtext* x);                                             // 0xa4e920
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
const char* rtext_gettag(t_rtext* x);                                    // 0xa4e990
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_senditup(t_rtext* x, int action, int* pWidth, int* pHeight,
                    int* pCursor);                                        // 0xa4e9c0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_retext(t_rtext* x);                                           // 0xa4ee20
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
__declspec(noinline)
t_rtext* glist_findrtext(t_glist* x, t_text* y);                         // 0xa4efb0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int rtext_width(t_rtext* x);                                             // 0xa4efd0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
int rtext_height(t_rtext* x);                                            // 0xa4f010
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_draw(t_rtext* x);                                             // 0xa4f050
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_erase(t_rtext* x);                                            // 0xa4f080
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_displace(t_rtext* x, int dx, int dy);                         // 0xa4f0b0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_select(t_rtext* x, int state);                                // 0xa4f0e0
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void rtext_activate(t_rtext* x, int state);                              // 0xa4f130
}
}
}
// ---- items of slice s00a4e2e0 end

// @ 0x00a4e8a0
namespace EA { namespace Audio { namespace Eapd {
t_rtext* rtext_new(t_glist* x, t_text* ob)
{
    t_rtext* rt = (t_rtext*)getbytes(100, "EAPd/t_rtext");
    t_rtext* next;

    rt->rt_ypix = -1;
    rt->rt_owner = ob;
    rt->rt_glist = x;
    next = x->gl_editor->e_rtextlist;
    rt->rt_height = 0;
    rt->rt_width = 0;
    rt->rt_active = 0;
    rt->rt_selectto = 0;
    rt->rt_selectfrom = 0;
    rt->rt_next = next;
    binbuf_gettext(ob->te_binbuf, &rt->rt_buf, &rt->rt_bufsize);
    x->gl_editor->e_rtextlist = rt;
    sprintf(rt->rt_tag, ".x%lx.t%lx", (unsigned)(size_t)glist_getcanvas(rt->rt_glist),
            (unsigned)(size_t)rt);
    return rt;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e920
namespace EA { namespace Audio { namespace Eapd {
void rtext_free(t_rtext* x)
{
    if (x->rt_glist->gl_editor->e_textedfor == x)
        x->rt_glist->gl_editor->e_textedfor = 0;
    if (x->rt_glist->gl_editor->e_rtextlist == x) {
        x->rt_glist->gl_editor->e_rtextlist = x->rt_next;
    } else {
        t_rtext* o = x->rt_glist->gl_editor->e_rtextlist;
        while (o && o->rt_next != x)
            o = o->rt_next;
        if (o)
            o->rt_next = x->rt_next;
    }
    if (rtext_entered == x)
        rtext_entered = 0;
    freebytes(x->rt_buf, x->rt_bufsize);
    freebytes(x, 100);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e990
namespace EA { namespace Audio { namespace Eapd {
const char* rtext_gettag(t_rtext* x)
{
    return x->rt_tag;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e9a0
namespace EA { namespace Audio { namespace Eapd {
void rtext_measures(int* pIn, int* pA, int* pB)
{
    *pA = pIn[0];
    *pB = pIn[1];
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4e9c0
namespace EA { namespace Audio { namespace Eapd {
void rtext_senditup(t_rtext* x, int action, int* widthp, int* heightp, int* cursorp)
{
    int nleft = 0;          // characters written to the flattened buffer
    int nlines = 0;         // lines emitted so far
    int maxline = 0;        // widest line, in characters
    int selstart = 0;       // selection start, in flattened-buffer chars
    int selend = 0;         // selection end, in flattened-buffer chars
    int wrapwidth = (short)x->rt_owner->te_width;
    int font, fontwidth, fontheight;
    int xpos, ypos;
    int newwidth, newheight;
    char smallbuf[200];
    char* buf;
    t_glist* canvas = glist_getcanvas(x->rt_glist);
    t_text* ob = x->rt_owner;

    if (wrapwidth == 0)
        wrapwidth = 60;
    if (ob->g_pd == gpCanvasClass &&
        (((t_glist*)ob)->gl_flags & GL_ISGRAPH) &&
        (((t_glist*)ob)->gl_flags & 0x80))
        font = glist_getfont((t_glist*)ob);
    else
        font = glist_getfont(x->rt_glist);
    fontwidth = sys_fontwidth(font);
    fontheight = sys_fontheight(font);

    int wrapcol = (fontwidth / 2 + *widthp) / fontwidth;
    int cursorline = *heightp / fontheight;

    if (x->rt_bufsize < 100)
        buf = smallbuf;
    else
        buf = (char*)getbytes(x->rt_bufsize * 2 + 1, "EAPd/char");

    if (x->rt_bufsize > 0) {
        int i = 0;
        int hit = 0;
        while (i < x->rt_bufsize) {
            int remaining = x->rt_bufsize - i;
            int limit = remaining < wrapwidth ? remaining : wrapwidth;
            char* p = x->rt_buf + i;
            int ncopy = 0;
            int nl = 1;
            if (remaining <= wrapwidth) {
                while (ncopy < limit && p[ncopy] != '\n')
                    ncopy++;
                nl = 0;
            } else {
                while (ncopy < limit && p[ncopy] != '\n')
                    ncopy++;
                if (ncopy == limit) {
                    /* wrap at the last space in the window */
                    int j = ncopy;
                    while (j > 0) {
                        j--;
                        ncopy--;
                        if (p[j] == ' ')
                            break;
                    }
                    if (ncopy < 0)
                        ncopy = limit;
                }
            }
            if (nlines == cursorline) {
                *cursorp = (wrapcol < 0 ? 0 : (ncopy < wrapcol ? ncopy : wrapcol)) + i;
                hit = 1;
            }
            strncpy(buf + nleft, p, ncopy);
            if (selstart == 0 && i <= x->rt_selectfrom && x->rt_selectfrom < i + ncopy + nl)
                selstart = x->rt_selectfrom - i + nleft;
            if (i <= x->rt_selectto && x->rt_selectto < i + ncopy + nl)
                selend = x->rt_selectto - i + nleft;
            nleft += ncopy;
            i += ncopy + nl;
            if (i < x->rt_bufsize)
                buf[nleft++] = '\n';
            if ((int)ncopy > (int)maxline)
                maxline = ncopy;
            nlines++;
        }
        if (!hit)
            *cursorp = nleft;
    } else {
        *cursorp = nleft;
    }

    xpos = text_xpix(ob, x->rt_glist);
    ypos = text_ypix(ob, x->rt_glist);
    if (nlines < 1)
        nlines = 1;
    if ((short)x->rt_owner->te_width == 0 && maxline < 3) {
        int pad = 3 - maxline;
        memset(buf + nleft, ' ', pad);
        nleft += pad;
        maxline += pad;
    }
    newwidth = fontwidth * maxline + 2;
    newheight = fontheight * nlines + 4;

    if (action == 1) {
        const char* color = glist_isselected(x->rt_glist, (t_gobj*)x->rt_glist) ? "blue" : "black";
        int fontid = sys_fontweight(font, color);
        SetSerializer("pdtk_text_new .x%lx.c %s %f %f {%.*s} %d %s\n",
                      canvas, x->rt_tag,
                      (double)((float)xpos + 1.0f), (double)((float)ypos + 2.0f),
                      nleft, buf, fontid);
    } else if (action == 2) {
        SetSerializer("pdtk_text_set .x%lx.c %s {%.*s}\n",
                      canvas, x->rt_tag, nleft, buf);
        if (newwidth != x->rt_width || newheight != x->rt_height)
            text_drawborder(ob, x->rt_glist, x->rt_tag, newwidth, newheight, 0);
        if (x->rt_active) {
            if (selstart < selend) {
                SetSerializer(".x%lx.c select from %s %d\n", canvas, x->rt_tag, selstart);
                SetSerializer(".x%lx.c select to %s %d\n", canvas, x->rt_tag, selend - 1);
                SetSerializer(".x%lx.c focus \"\"\n", canvas);
            } else {
                SetSerializer(".x%lx.c select clear\n", canvas);
                SetSerializer(".x%lx.c icursor %s %d\n", canvas, x->rt_tag, selstart);
                SetSerializer(".x%lx.c focus %s\n", canvas, x->rt_tag);
            }
        }
    }
    x->rt_width = newwidth;
    x->rt_height = newheight;
    *widthp = newwidth;
    *heightp = newheight;
    if (buf != smallbuf)
        freebytes(buf, x->rt_bufsize * 2 + 1);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4ee20
namespace EA { namespace Audio { namespace Eapd {
void rtext_retext(t_rtext* x)
{
    int dummyh = 0;
    int dummyc = 0;
    int dummyw = 0;
    t_text* ob = x->rt_owner;
    int len;

    freebytes(x->rt_buf, x->rt_bufsize);
    binbuf_gettext(ob->te_binbuf, &x->rt_buf, &x->rt_bufsize);
    if ((short)ob->te_width < 1 || (ob->te_type & 3) != 3 ||
        x->rt_bufsize <= (short)ob->te_width)
        goto done;

    len = x->rt_bufsize;
    {
        int* atoms = binbuf_getvec(ob->te_binbuf);
        int natom = binbuf_getnatom(ob->te_binbuf);
        int limit = len - (short)ob->te_width;

        if (natom == 1 && atoms[0] == 1) {
            /* A single float: keep only a signed mantissa. */
            char* p = x->rt_buf;
            char* end = p + len;
            while (p < end && *p != '.')
                p++;
            if (p < end) {
                char* q = p + 1;
                while (q < end && *q >= '0' && *q <= '9')
                    q++;
                if ((int)(q - 1 - p) < limit) {
                    x->rt_buf[0] = (0.0f < (float)atoms[1]) ? '+' : '-';
                    x->rt_buf = (char*)resizebytes(x->rt_buf, len, 1, "EAPd/char");
                    len = 1;
                } else {
                    char* dst = q - limit;
                    char* src = q;
                    while (src < end)
                        *dst++ = *src++;
                    x->rt_buf = (char*)resizebytes(x->rt_buf, len,
                                                   (short)ob->te_width, "EAPd/char");
                    len = (short)ob->te_width;
                }
            }
        } else if ((short)ob->te_width < len) {
            x->rt_buf[(short)ob->te_width - 1] = '>';
            x->rt_buf = (char*)resizebytes(x->rt_buf, len,
                                           (short)ob->te_width, "EAPd/char");
            len = (short)ob->te_width;
        }
        x->rt_bufsize = len;
    }
done:
    rtext_senditup(x, 2, &dummyw, &dummyh, &dummyc);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4efb0
namespace EA { namespace Audio { namespace Eapd {
__declspec(noinline) t_rtext* glist_findrtext(t_glist* x, t_text* y)
{
    t_rtext* rt = x->gl_editor->e_rtextlist;
    while (rt && rt->rt_owner != y)
        rt = rt->rt_next;
    return rt;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4efd0
namespace EA { namespace Audio { namespace Eapd {
int rtext_width(t_rtext* x)
{
    int w = 0;
    int h = 0;
    int c = 0;
    rtext_senditup(x, 0, &w, &h, &c);
    return w;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4f010
namespace EA { namespace Audio { namespace Eapd {
int rtext_height(t_rtext* x)
{
    int w = 0;
    int h = 0;
    int c = 0;
    rtext_senditup(x, 0, &w, &h, &c);
    return h;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4f050
namespace EA { namespace Audio { namespace Eapd {
void rtext_draw(t_rtext* x)
{
    int w = 0;
    int h = 0;
    int c = 0;
    rtext_senditup(x, 1, &w, &h, &c);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4f080
namespace EA { namespace Audio { namespace Eapd {
void rtext_erase(t_rtext* x)
{
    SetSerializer(".x%lx.c delete %s\n", glist_getcanvas(x->rt_glist), x->rt_tag);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4f0b0
namespace EA { namespace Audio { namespace Eapd {
void rtext_displace(t_rtext* x, int dx, int dy)
{
    SetSerializer(".x%lx.c move %s %d %d\n", glist_getcanvas(x->rt_glist),
                  x->rt_tag, dx, dy);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4f0e0
namespace EA { namespace Audio { namespace Eapd {
void rtext_select(t_rtext* x, int state)
{
    t_glist* canvas = glist_getcanvas(x->rt_glist);
    SetSerializer(".x%lx.c itemconfigure %s -fill %s\n", canvas, x->rt_tag,
                  state ? "blue" : "black");
    gpEditingCanvas = canvas;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a4f130
namespace EA { namespace Audio { namespace Eapd {
void rtext_activate(t_rtext* x, int state)
{
    int w = 0;
    int h = 0;
    t_glist* canvas;
    t_glist* gl = x->rt_glist;

    canvas = glist_getcanvas(gl);
    if (state) {
        SetSerializer(".x%lx.c focus %s\n", canvas, x->rt_tag);
        gl->gl_editor->e_textedfor = x;
        gl->gl_editor->e_flags &= 0xffffffef;
        x->rt_selectfrom = 0;
        x->rt_xpix = 0;
        x->rt_selectto = x->rt_bufsize;
        x->rt_active = 1;
    } else {
        SetSerializer("selection clear .x%lx.c\n", canvas);
        SetSerializer(".x%lx.c focus \"\"\n", canvas);
        if (gl->gl_editor->e_textedfor == x)
            gl->gl_editor->e_textedfor = 0;
        x->rt_active = 0;
    }
    rtext_senditup(x, 2, &w, &h, &h);
}
}}}  // namespace EA::Audio::Eapd
