#!/usr/bin/env python3
"""How much of the USA (reference) code is in the EU and ES builds: every USA function (asm/<prog>, config/*.yaml) as a
masked word sequence (tools/funcstats.mask) searched in the same program of game/eu and game/es. Prints counts.

  python3 -I tools/vermatch.py
"""
import sys,os,csv,struct,collections
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from funcstats import mask, programs
eu={p:(b,d,ts,te,ad) for p,b,d,ts,te,ad in programs()}
def W(b): n=len(b)//4; return struct.unpack('<%dI'%n,b[:n*4])
names={'main':'MAIN.EXE','boot':None}
for ver in ('eu','es'):
    fs=os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))),'game',ver)
    tot=collections.Counter()
    out=[]
    for p,(b,d,ts,te,ad) in eu.items():
        if p=='main': f='MAIN.EXE'
        elif p=='boot': f=[x for x in os.listdir(fs) if x[:4] in('SCES','SCUS')][0]
        else: f='BIN/%s.BIN'%p.upper()
        tb=open(os.path.join(fs,f),'rb').read()
        tm=[mask(w) for w in W(tb)]; tw=W(tb)
        idx=collections.defaultdict(list)
        for i in range(len(tm)-4): idx[tuple(tm[i:i+4])].append(i)
        ends=ad[1:]+[te+d]; c=collections.Counter()
        for s,e in zip(ad,ends):
            fw=W(b[s-d:e-d]); fm=[mask(w) for w in fw]
            hit=None; ident=False
            for i in idx.get(tuple(fm[:4]),[]):
                if tm[i:i+len(fm)]==fm: hit=i; ident = list(tw[i:i+len(fw)])==list(fw); break
            c['n']+=1; c['B']+=e-s
            if hit is not None: c['m']+=1; c['mB']+=e-s; c['id']+=ident
        out.append('%s %d/%d (%d identical)'%(p,c['m'],c['n'],c['id'])); tot.update(c)
    print(ver,'matched USA functions %d/%d, bytes %d/%d, byte-identical %d'%(tot['m'],tot['n'],tot['mB'],tot['B'],tot['id']))
    print('  ',', '.join(o for o in out))
