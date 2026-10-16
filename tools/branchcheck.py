# Checks that every branch and jump in an oscar64 listing lands on an instruction
# (oscar64 1.32.271 once shortened an instruction after placing a branch over it)
import re,sys
starts=set(); br=[]
for l in open(sys.argv[1]):
    m=re.match(r'^([0-9a-f]{4}) : ((?:[0-9a-f_]{2} ){3})\s*(\w+)\s*(.*)',l)
    if not m: continue
    a=int(m[1],16); starts.add(a)
    t=re.match(r'\$([0-9a-f]{4})',m[4])
    if m[3] in('BPL','BMI','BNE','BEQ','BCC','BCS','BVC','BVS','JMP','JSR') and t and '(' not in m[4][:1]:
        br.append((a,m[3],int(t[1],16)))
lo,hi=min(starts),max(starts)
bad=[(a,o,t) for a,o,t in br if lo<=t<=hi and t not in starts]
for a,o,t in bad: print(f"{a:04x} {o} ${t:04x}")
sys.exit(1 if bad else 0)
