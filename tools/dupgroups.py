#!/usr/bin/env python3
"""Pending functions that have copies in several programs (the same masked word sequence), most copies first:
the best targets for hand decompilation, since tools/dupsweep.py --install then puts the C into every copy.

  python3 -I tools/dupgroups.py [MAX_SIZE=200]   -> copies, size, program, name (first copy)
"""
import sys, re, os, struct, collections, glob
os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from funcstats import mask, programs
pend={}
for p in os.listdir(os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), 'src')):
    f=f'src/{p}/{p}.c'
    if os.path.exists(f): pend[p]=set(re.findall(r'INCLUDE_ASM\("[^"]+", (\w+)\);',open(f).read()))
groups=collections.defaultdict(list)
for prog,b,d,ts,te,addrs in programs():
    if prog not in pend: continue
    names={}
    for f in glob.glob(f'asm/{prog}/nonmatchings/{prog}/*.s'):
        m=re.search(r'/\* \w+ ([0-9A-F]{8}) ',open(f).read())
        if m: names[int(m.group(1),16)]=os.path.basename(f)[:-2]
    ends=list(addrs[1:])+[te+d]
    for s,e in zip(addrs,ends):
        n=names.get(s)
        if n not in pend[prog]: continue
        fb=b[s-d:e-d]; k=len(fb)//4
        key=tuple(mask(w) for w in struct.unpack('<%dI'%k,fb[:k*4]))
        groups[key].append((prog,n,e-s))
lim=int(sys.argv[1]) if len(sys.argv)>1 else 200
big=sorted([g for g in groups.values() if len(set(p for p,_,_ in g))>=2 and 12<g[0][2]<=lim],key=lambda g:(-len(g), g[0][2]))
for g in big[:30]: print(len(g), g[0][2], g[0][0], g[0][1])
