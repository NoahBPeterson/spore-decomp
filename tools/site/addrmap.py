#!/usr/bin/env python3
"""Address-space map of SporeApp.exe for the public site: every retail function as a patch of a Hilbert-curve
square, coloured by status, animated over the history of main.

  python3 tools/site/addrmap.py [--out map.html]        (a standalone preview page)
  build.py imports map_body() for the site's map.html

Statuses, per function and per day (the last first-parent commit on main of each day, as build.py's history):
  2  byte-exact: a manifest row lists it and tools/ci/known_failures.txt does not (the site's only "done" count)
  1  source written: a nonmatching.txt or partial.txt note exists for it (its C++ is in the repo, bytes still differ)
  0  not started
Public-site rules hold: byte-exact counts only (no equivalence results), and no names, symbols or code; the page
carries only addresses and sizes (already public in tools/ci/fingerprints.jsonl.gz) and module names (src/game/).
"""
import argparse, bisect, datetime, gzip, json, os, re, subprocess, sys

ROOT = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build as B  # noqa: E402

# Events that explain a jump in the map, shown under the date on that day's frame.
EVENTS = {
    "2026-11-09": "The pull-request fingerprint check arrived. 1,093 functions counted as byte-exact before were set "
                  "aside because they fail it from a clean checkout: about half are open-source library code it cannot "
                  "build, and the rest were not true matches.",
}

NOTE_RE = re.compile(r"^(match/slices/[^/]+|src/game/.+)/(nonmatching|partial)\.txt$")


def note_vas(text):
    out = set()
    for line in text.splitlines():
        p = line.split(None, 1)
        if p and not line.lstrip().startswith("#"):
            try:
                out.add(int(p[0], 16))
            except ValueError:
                pass
    return out


class StateCache:
    """per commit: (byte-exact VAs, noted VAs), reading each blob once"""
    def __init__(self):
        self.blob = {}

    def _read(self, shas):
        need = [s for s in shas if s not in self.blob]
        if not need:
            return
        out = subprocess.run(["git", "cat-file", "--batch"], cwd=ROOT, capture_output=True,
                             input="\n".join(need).encode() + b"\n", check=True).stdout
        i = 0
        for sha in need:
            hdr_end = out.index(b"\n", i)
            size = int(out[i:hdr_end].split()[2])
            self.blob[sha] = out[hdr_end + 1:hdr_end + 1 + size].decode("utf-8", "replace")
            i = hdr_end + 1 + size + 1

    def at(self, commit, fps):
        tree = B.git("ls-tree", "-r", commit, "--", "match", "src/game", "tools/ci/known_failures.txt")
        man, notes, known = [], [], None
        for line in tree.splitlines():
            meta, path = line.split("\t", 1)
            sha = meta.split()[2]
            if path == "tools/ci/known_failures.txt":
                known = sha
            elif B.MANIFEST_RE.match(path):
                man.append(sha)
            elif NOTE_RE.match(path):
                notes.append(sha)
        self._read(man + notes + ([known] if known else []))
        exact, noted = set(), set()
        for s in man:
            exact |= B.rows_vas(self.blob[s])
        if known:
            exact -= B.known_vas(self.blob[known])
        for s in notes:
            noted |= note_vas(self.blob[s])
        return exact & fps.keys(), (noted & fps.keys()) - exact


def days():
    last = {}
    for line in B.git("log", "--first-parent", "--format=%H %cI", "HEAD").splitlines():
        if line.strip():
            sha, when = line.split()
            day = datetime.datetime.fromisoformat(when).astimezone(datetime.timezone.utc).date().isoformat()
            last.setdefault(day, sha)
    return [(d, last[d]) for d in sorted(last)]


def varints(nums):
    """non-negative ints -> compact base-32 string: 5 bits per char, high bit of each digit group marks 'more'"""
    a = "0123456789abcdefghijklmnopqrstuv"
    A = "ABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&*"  # continuation digits
    out = []
    for n in nums:
        groups = [n & 31]
        n >>= 5
        while n:
            groups.append(n & 31)
            n >>= 5
        for g in reversed(groups[1:]):
            out.append(A[g])
        out.append(a[groups[0]])
    return "".join(out)


def deltas(sorted_idx):
    prev, out = -1, []
    for i in sorted_idx:
        out.append(i - prev - 1)
        prev = i
    return out


def map_data():
    fps = {int(d["va"], 16): d["size"] for d in map(json.loads, gzip.open(os.path.join(ROOT, "tools", "ci", "fingerprints.jsonl.gz"), "rt"))}
    vas = sorted(fps)
    index = {v: i for i, v in enumerate(vas)}
    mods = json.load(open(os.path.join(ROOT, "tools", "site", "modules.json")))
    starts = [int(r[0], 16) for r in mods["runs"]]
    mod_of = [mods["runs"][bisect.bisect_right(starts, v) - 1][1] if bisect.bisect_right(starts, v) else 0 for v in vas]
    cache, frames, prev = StateCache(), [], [0] * len(vas)
    for day, sha in days():
        exact, noted = cache.at(sha, fps)
        cur = [0] * len(vas)
        for v in noted:
            cur[index[v]] = 1
        for v in exact:
            cur[index[v]] = 2
        changed = [[], [], []]
        for i, (a, b) in enumerate(zip(prev, cur)):
            if a != b:
                changed[b].append(i)
        if any(changed) or not frames:
            frames.append({"d": day, "c": [varints(deltas(c)) for c in changed]})
            if day in EVENTS:
                frames[-1]["note"] = EVENTS[day]
        prev = cur
    # module runs as index ranges over the sorted functions, for hover and outlines
    runs, last = [], None
    for i, m in enumerate(mod_of):
        if m != last:
            runs.append([i, m])
            last = m
    return {"va": varints([vas[0]] + [b - a for a, b in zip(vas, vas[1:])]),
            "size": varints([fps[v] for v in vas]), "frames": frames, "modules": mods["modules"], "runs": runs}


JS = r"""
(function(){
const D=JSON.parse(document.getElementById('mapdata').textContent);
function dec(s){const o=[];let n=0;for(const ch of s){const c=ch.charCodeAt(0);
 let k='0123456789abcdefghijklmnopqrstuv'.indexOf(ch);if(k>=0){o.push(n*32+k);n=0}else{n=n*32+'ABCDEFGHIJKLMNOPQRSTUVWXYZ!#$%&*'.indexOf(ch)}}return o}
const gaps=dec(D.va),size=dec(D.size),N=size.length,va=new Array(N);let acc=0;
for(let i=0;i<N;i++){acc+=gaps[i];va[i]=acc}
const off=new Float64Array(N+1);for(let i=0;i<N;i++)off[i+1]=off[i]+size[i];const TOTAL=off[N];
const ORDER=9,SIDE=1<<ORDER,CELLS=SIDE*SIDE,PER=TOTAL/CELLS;
const cx=new Uint16Array(CELLS),cy=new Uint16Array(CELLS);
for(let d=0;d<CELLS;d++){let x=0,y=0,t=d;for(let s=1;s<SIDE;s*=2){const rx=1&(t>>1),ry=1&(t^rx);
 if(ry===0){if(rx===1){x=s-1-x;y=s-1-y}const q=x;x=y;y=q}x+=s*rx;y+=s*ry;t>>=2}cx[d]=x;cy[d]=y}
const states=[];let st=new Uint8Array(N);
for(const f of D.frames){for(let s=0;s<3;s++){let i=-1;for(const g of dec(f.c[s])){i+=g+1;st[i]=s}}states.push(st.slice())}
const cv=document.getElementById('map'),ctx=cv.getContext('2d');cv.width=SIDE;cv.height=SIDE;
const img=ctx.createImageData(SIDE,SIDE);
function rgb(v){const m=/#?([0-9a-f]{2})([0-9a-f]{2})([0-9a-f]{2})/i.exec(v.trim());return m?[1,2,3].map(k=>parseInt(m[k],16)):[128,128,128]}
let C;function colours(){const cs=getComputedStyle(document.documentElement);
 C=[rgb(cs.getPropertyValue('--todo')),rgb(cs.getPropertyValue('--wip')),rgb(cs.getPropertyValue('--done'))]}
colours();
const w0=new Float32Array(CELLS),w1=new Float32Array(CELLS),w2=new Float32Array(CELLS);const W=[w0,w1,w2];
function draw(k){const s=states[k];w0.fill(0);w1.fill(0);w2.fill(0);
 for(let i=0;i<N;i++){const a=off[i]/PER,b=off[i+1]/PER,w=W[s[i]];let c=Math.floor(a);const e=Math.min(CELLS-1,Math.floor(b-1e-9));
  if(c===e){w[c]+=b-a;continue}w[c]+=c+1-a;for(c++;c<e;c++)w[c]+=1;w[e]+=b-e}
 const p=img.data;let nf=[0,0,0],nb=[0,0,0];
 for(let d=0;d<CELLS;d++){const t=w0[d]+w1[d]+w2[d]||1,a=w0[d]/t,b=w1[d]/t,c=w2[d]/t,j=(cy[d]*SIDE+cx[d])*4;
  p[j]=a*C[0][0]+b*C[1][0]+c*C[2][0];p[j+1]=a*C[0][1]+b*C[1][1]+c*C[2][1];p[j+2]=a*C[0][2]+b*C[1][2]+c*C[2][2];p[j+3]=255}
 ctx.putImageData(img,0,0);
 for(let i=0;i<N;i++){nf[s[i]]++;nb[s[i]]+=size[i]}
 document.getElementById('mday').textContent=new Date(D.frames[k].d+'T12:00:00Z').toLocaleDateString(undefined,{year:'numeric',month:'short',day:'numeric'});
 const nt=document.getElementById('mnote');nt.textContent=D.frames[k].note||'';nt.hidden=!D.frames[k].note;
 const pc=(x,t)=>(100*x/t).toFixed(1)+'%';
 document.getElementById('mexact').textContent=pc(nb[2],TOTAL)+' of bytes, '+nf[2].toLocaleString()+' functions';
 document.getElementById('msrc').textContent=pc(nb[1],TOTAL)+' of bytes, '+nf[1].toLocaleString()+' functions';
 document.getElementById('mnone').textContent=pc(nb[0],TOTAL)+' of bytes, '+nf[0].toLocaleString()+' functions';}
const sl=document.getElementById('mslider');sl.max=states.length-1;sl.value=states.length-1;let cur=states.length-1;draw(cur);
sl.addEventListener('input',()=>{stop();cur=+sl.value;draw(cur)});
let timer=null;const btn=document.getElementById('mplay');
function stop(){if(timer){clearTimeout(timer);timer=null;btn.textContent='Play'}}
btn.addEventListener('click',()=>{if(timer){stop();return}if(cur>=states.length-1)cur=0;draw(cur);sl.value=cur;btn.textContent='Pause';
 const step=()=>{cur++;sl.value=cur;draw(cur);if(cur>=states.length-1){stop();return}timer=setTimeout(step,D.frames[cur].note?4000:450)};
 timer=setTimeout(step,450)});
const inv=new Int32Array(CELLS);for(let d=0;d<CELLS;d++)inv[cy[d]*SIDE+cx[d]]=d;
const tip=document.getElementById('mtip'),names=['not started','source written','byte-exact'];
function modAt(i){let lo=0,hi=D.runs.length-1;while(lo<hi){const m=(lo+hi+1)>>1;if(D.runs[m][0]<=i)lo=m;else hi=m-1}return D.modules[D.runs[lo][1]]}
cv.addEventListener('mousemove',e=>{const r=cv.getBoundingClientRect(),x=Math.floor((e.clientX-r.left)/r.width*SIDE),y=Math.floor((e.clientY-r.top)/r.height*SIDE);
 if(x<0||y<0||x>=SIDE||y>=SIDE){tip.hidden=true;return}const pos=(inv[y*SIDE+x]+.5)*PER;let lo=0,hi=N-1;
 while(lo<hi){const m=(lo+hi+1)>>1;if(off[m]<=pos)lo=m;else hi=m-1}
 tip.hidden=false;tip.textContent='0x'+va[lo].toString(16).padStart(8,'0')+' · '+size[lo].toLocaleString()+' bytes · '+names[states[cur][lo]]+' · '+modAt(lo);});
cv.addEventListener('mouseleave',()=>{tip.hidden=true});
matchMedia('(prefers-color-scheme: dark)').addEventListener('change',()=>{colours();draw(cur)});
})();
"""

CSS = """
:root{--wip:#d9a441}@media (prefers-color-scheme:dark){:root:not([data-theme=light]){--wip:#b07f2c}}
.mapwrap{display:grid;grid-template-columns:minmax(0,560px) minmax(220px,1fr);gap:20px;align-items:start}
@media (max-width:760px){.mapwrap{grid-template-columns:1fr}}
#map{width:100%;height:auto;aspect-ratio:1;image-rendering:pixelated;border-radius:6px;display:block;cursor:crosshair}
.mctl{display:flex;gap:12px;align-items:center;margin-top:12px}.mctl input{flex:1;accent-color:var(--accent)}
.mctl button{font:inherit;padding:6px 14px;border-radius:6px;border:1px solid var(--line);background:var(--panel);color:var(--ink);cursor:pointer}
#mday{font-size:22px;font-weight:700;font-variant-numeric:tabular-nums}
.mkey{list-style:none;padding:0;margin:12px 0 0}.mkey li{margin:10px 0;font-size:14px}.mkey b{display:block;font-weight:600}
.mkey span{color:var(--muted);font-variant-numeric:tabular-nums}.mkey i{display:inline-block;width:12px;height:12px;border-radius:3px;margin-right:8px;vertical-align:-1px}
#mnote{margin:8px 0 0;padding:8px 10px;border-left:3px solid var(--accent);background:var(--code);border-radius:4px;font-size:14px}
#mtip{font:13px ui-monospace,SFMono-Regular,Menlo,monospace;color:var(--muted);min-height:1.5em;margin-top:8px}
"""


def map_body():
    data = map_data()
    body = ("<style>%s</style><h1>The whole program, mapped</h1>"
            '<p class="lede">Every function of <code>SporeApp.exe</code>, laid out in address order along a space-filling '
            "curve, so code that sits together in the program sits together here. Area is proportional to size in "
            "bytes. Press play to watch it fill in.</p>"
            '<div class="panel mapwrap"><div><canvas id="map" aria-label="Map of the program by function status"></canvas>'
            '<div class="mctl"><button id="mplay" type="button">Play</button><input id="mslider" type="range" min="0" '
            'step="1" aria-label="Date"></div><div id="mtip" hidden></div></div>'
            '<div><div id="mday"></div><p id="mnote" hidden></p><ul class="mkey">'
            '<li><b><i style="background:var(--done)"></i>Byte-exact</b><span id="mexact"></span></li>'
            '<li><b><i style="background:var(--wip)"></i>C++ written, bytes still differ</b><span id="msrc"></span></li>'
            '<li><b><i style="background:var(--todo);outline:1px solid var(--line)"></i>Not started</b><span id="mnone"></span></li>'
            '</ul><p class="note">One frame per day of work on the main branch. A cell that holds several functions blends '
            "their colours. Hover to see a function's address, size and module.</p></div></div>"
            '<script type="application/json" id="mapdata">%s</script><script>%s</script>'
            % (CSS, json.dumps(data, separators=(",", ":")), JS))
    return body, data


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--out", required=True)
    ap.add_argument("--repo", default="NoahBPeterson/spore-decomp")
    a = ap.parse_args()
    body, data = map_body()
    meta = {"repo": a.repo, "sha": B.git("rev-parse", "HEAD").strip(),
            "when": datetime.datetime.now(datetime.timezone.utc).strftime("%Y-%m-%d %H:%M UTC")}
    open(a.out, "w", encoding="utf-8").write(B.page("spore-decomp: map", "map.html", body, meta))
    print("%s: %d frames, %d KB" % (a.out, len(data["frames"]), os.path.getsize(a.out) // 1024))


if __name__ == "__main__":
    main()
