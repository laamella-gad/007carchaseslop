

;007.bas ==1001==
    0 ifc=0thenc=c+1:load"007",8,1
    2 poke53280,0:poke53281,0:poke53269,0:poke53232,0:print"{clr}{wht}wait for data transfer"
    3 poke53276,255:poke53285,0:poke53286,2:poke49630,32:poke49631,46:poke49632,198
    4 d$="country":gosub8000:poke49173,234:poke49174,234:poke49175,234:goto39
    5 v1=peek(v)-18:v2=peek(v)+18:v3=peek(v+12):v4=peek(v)-10:v5=peek(v)+10
    6 j1=j1-1:j2=j2-1:j3=j3-1:j4=j4-1:gosub45:ifpeek(v+2)>v1andpeek(v+2)<v2thengosub20
    7 ifpeek(v+4)>v1andpeek(v+4)<v2thengosub24
    8 ifpeek(v+6)>v1andpeek(v+6)<v2thengosub28
    9 ifpeek(v+8)>v1andpeek(v+8)<v2thengosub32
   10 ifv3>0thengosub36
   11 gosub51:te=0:print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{wht}score";sc:return
   12 poke2041,33:j1=1:pokev+40,7:goto18
   13 poke2042,33:j2=1:pokev+41,7:goto18
   14 poke2043,33:j3=1:pokev+42,7:goto18
   15 poke2044,33:j4=1:pokev+43,7:goto18
   18 sys50900:sc=sc+((peek(53232)+1)*50)
   19 return
   20 ifpeek(v+3)>110andpeek(v+3)<140andpeek(53246)=1then12
   21 ifpeek(v+3)>175andpeek(v+3)<200andpeek(53246)=3then12
   22 ifpeek(v+3)>140andpeek(v+3)<180andj1<=0then5999
   23 return
   24 ifpeek(v+5)>110andpeek(v+5)<140andpeek(53246)=1then13
   25 ifpeek(v+5)>175andpeek(v+5)<200andpeek(53246)=3then13
   26 ifpeek(v+5)>140andpeek(v+5)<180andj2<=0then5999
   27 return
   28 ifpeek(v+7)>110andpeek(v+7)<140andpeek(53246)=1then14
   29 ifpeek(v+7)>175andpeek(v+7)<200andpeek(53246)=3then14
   30 ifpeek(v+7)>140andpeek(v+7)<180andj3<=0then5999
   31 return
   32 ifpeek(v+9)>110andpeek(v+9)<140andpeek(53246)=1then15
   33 ifpeek(v+9)>175andpeek(v+9)<200andpeek(53246)=3then15
   34 ifpeek(v+9)>140andpeek(v+9)<180andj4<=0then5999
   35 return
   36 ifv3>v4andv3<v5andpeek(v+13)>140andpeek(v+13)<180then5999
   37 ifpeek(v+13)>195thenpokev+13,0
   38 return
   39 poke49633,96:poke53246,0:ch=3:p1=13:p2=14:d=0
   40 v=53248:pokev+46,7:pokev+23,128:poke50556,120:poke50610,120
   41 poke2046,34
   42 forx=56221to56241:pokex,7:next
   43 d$="country":gosub20000
   44 goto11000
   45 ifj1=0andpeek(2041)=33thenpoke53241,0:pokev+2,0
   46 ifj2=0andpeek(2042)=33thenpoke53242,0:pokev+4,0
   47 ifj3=0andpeek(2043)=33thenpoke53243,0:pokev+6,0
   48 ifj4=0andpeek(2044)=33thenpoke53244,0:pokev+8,0
   49 return
   51 ifpeek(197)=3thench=-1
   52 ifpeek(197)=6thengosub58
   53 ifpeek(v+15)>50andpeek(v+15)<70then55
   54 return
   55 ifpeek(v+14)>peek(v+10)-15andpeek(v+14)<peek(v+10)+15then57
   56 return
   57 forn=0to4:poke2045,33:sys50900:poke2045,15:next:sc=sc+2000:return
   58 forx=0to1000:next
   59 ifpeek(197)<>6then59
   60 return
   91 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{blk}track"
   92 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}plan"
   93 forx=56221to56241:pokex,7:next:poke53285,0:poke53286,2
   94 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{wht}cars";ch
   95 forn=1to6
   96 onngosub100,101,102,103,105,115
   97 next
   98 goto180
  100 pokev,180:pokev+1,160:poke2040,p1:pokev+39,15:return
  101 pokev+2,180:pokev+3,80:poke2041,p2:poke53241,int(rnd(1)*5)+1:pokev+40,2:return
  102 pokev+4,180:pokev+5,80:poke2042,p2:poke53242,int(rnd(1)*5)+1:pokev+41,3:return
  103 pokev+6,180:pokev+7,80:poke2043,p2:poke53243,int(rnd(1)*5)+1:pokev+42,5:return
  105 za=int(rnd(1)*5)+1:poke2044,p1:poke53244,za:pokev+43,int(rnd(1)*10)
  106 onzagoto107,108,109,110,111
  107 pokev+8,60:pokev+9,200:return
  108 pokev+8,108:pokev+9,200:return
  109 pokev+8,180:pokev+9,200:return
  110 pokev+8,252:pokev+9,200:return
  111 pokev+8,255:pokev+9,160:return
  115 pokev+44,15:poke2045,15:pokev+10,80:pokev+11,55:poke53245,1:return
  120 pokev,180:pokev+1,160:poke2040,13:pokev+39,15:return
  121 pokev+2,180:pokev+3,80:poke2041,14:poke53241,int(rnd(1)*2)+1:return
  122 pokev+4,180:pokev+5,80:poke2042,p2:poke53242,int(rnd(1)*2)+1:return
  123 pokev+6,180:pokev+7,80:poke2043,p2:poke53243,int(rnd(1)*2)+1:return
  125 za=int(rnd(1)*2)+1:poke2044,p1:poke53244,za:pokev+43,int(rnd(1)*10)
  126 onzagoto107,108,109,110,111
  127 pokev+8,60:pokev+9,200:return
  128 pokev+8,108:pokev+9,200:return
  129 pokev+8,180:pokev+9,200:return
  130 pokev+8,252:pokev+9,200:return
  131 pokev+8,255:pokev+9,160:return
  135 pokev+44,15:poke2045,15:pokev+10,80:pokev+11,55:poke53245,1:return
  140 a1$="    {CBM-*}{SHIFT-POUND} {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}      {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND} "
  141 a2$="    N   M     N   N       M       M  N  "
  142 a3$="   N         N             M       M    "
  144 return
  145 a1$=right$(a1$,38)+left$(a1$,2)
  146 a2$=right$(a2$,38)+left$(a2$,2)
  147 a3$=right$(a3$,38)+left$(a3$,2)
  148 print"{blu}{home}{down}{down}";a1$;a2$;a3$
  149 return
  150 a1$=right$(a1$,2)+left$(a1$,38)
  151 a2$=right$(a2$,2)+left$(a2$,38)
  152 a3$=right$(a3$,2)+left$(a3$,38)
  153 print"{blu}{home}{down}{down}";a1$;a2$;a3$
  154 return
  180 pokev+21,255
  188 poke53280,0:poke53281,12:poke53245,1:gosub115:poke53233,0
  189 print"{home}{rvon}{blu}                                        {rvof}";
  190 print"{cyn}{CBM-I}{CBM-I}{CBM-POUND}{red}{CBM-+}{CBM-+}{wht}{CBM-I}{CBM-I}{CBM-F}{blu}{rvon}     {rvof}{blk}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{blu}{rvon}   {rvof}{brn}{CBM-+}{blu}{rvon}    {rvof}{gry3}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM--}{gry1}{CBM-POUND}{CBM-I}{CBM-I}{CBM-I}{CBM-F}";
  191 print"{cyn}{CBM-B}{CBM-B}{CBM-+}{red}{CBM-+}{CBM-+}{wht}{CBM-B}{CBM-B}{CBM-K}{yel}{CBM-D}{CBM-I}{CBM-I}{CBM-I}{CBM-POUND}{blk}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rvon}{blu}   {rvof}{brn}{CBM-+}{red}{CBM-I}{CBM-I}{CBM-I}{CBM-I}{gry3}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM--}{gry1}{CBM-+}{CBM-B}{CBM-B}{CBM-B}{CBM-K}";
  192 print"{cyn}{CBM-B}{CBM-B}{CBM-+}{red}{CBM-+}{CBM-+}{wht}{CBM-B}{CBM-B}{CBM-J}{yel}{CBM-L}{CBM-B}{CBM-B}{CBM-B}{CBM-+}{blk}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{blu}{rvon}   {rvof}{brn}{CBM-+}{red}{CBM-B}{CBM-B}{CBM-B}{CBM-B}{CBM-B}{gry3}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{CBM--}{gry1}{CBM-+}{CBM-B}{CBM-B}{CBM-B}{CBM-K}";
  193 print"{cyn}{CBM-B}{CBM-B}{CBM-+}{red}{CBM-+}{CBM-+}{wht}{CBM-B}{CBM-B}{CBM-J}{yel}{CBM-L}{CBM-B}{CBM-B}{CBM-B}{CBM-+}{blk}{CBM-+}{CBM-+}{CBM-+}{wht}{CBM-B}{CBM-B}{CBM-+}{CBM-+}{blu}{rvon}   {rvof}{brn}{CBM-+}{red}{CBM-B}{CBM-B}{CBM-B}{CBM-B}{CBM-B}{gry3}{CBM-+}{CBM-+}{wht}{CBM-+}{CBM-B}{CBM-B}{CBM-J}{gry1}{CBM-+}{CBM-B}{CBM-B}{CBM-B}{CBM-K}";
  194 print"{cyn}{CBM-B}{CBM-B}{SHIFT-POUND} {wht}{CBM-L}{CBM-B}{CBM-B}{CBM-J}{yel}{CBM-L}{CBM-B}{CBM-B}{CBM-B}{SHIFT-POUND}  {wht}{CBM-L}{CBM-B}{CBM-B}{CBM-B}{SHIFT-POUND}   {red}{CBM-*}{CBM-B}{CBM-B}{CBM-B}{CBM-B}{CBM-B}{CBM-J} {wht}{CBM-*}{CBM-B}{CBM-B}{CBM-J}{gry1}{CBM-*}{CBM-B}{CBM-B}{CBM-B}{CBM-J}";
  195 p=p+1
  196 p1=13:p2=14:poke2040,p1:poke2041,p2:poke2042,p2:poke2043,p2
  197 poke2044,p1
  200 sys49155:print"{home}{down}{down}{down}{down}{down}{rvon}{grn}                 {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}              {rvof}";
  201 sys51000:print"{rvon}{grn}                {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}  {SHIFT--}  {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}             {rvof}";
  202 sys49152:print"{rvon}{grn}               {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}            {rvof}";
  203 print"{rvon}{grn}              {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}    {SHIFT--}    {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}           {rvof}";
  204 sys49152:print"{rvon}{grn}             {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}          {rvof}";
  205 print"{rvon}{grn}            {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}      {SHIFT--}      {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}         {rvof}";
  206 sys49561:print"{rvon}{grn}           {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}               {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}        {rvof}";
  207 sys51000:sys49152:print"{rvon}{grn}          {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}        {SHIFT--}        {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}       {rvof}";
  208 sys49561:print"{grn}{rvon}         {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}      {rvof}";
  209 print"{grn}{rvon}        {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}     {rvof}";
  210 sys49152:print"{rvon}{grn}       {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}          {wht} {SHIFT--}{red}           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}    {rvof}";
  211 print"{rvon}{grn}      {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                         {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}   {rvof}";
  212 sys49155:print"{rvon}{grn}     {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}  {rvof}";
  213 sys49561:print"{rvon}{grn}    {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}              {SHIFT--}              {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon} {rvof}";
  214 print"{rvon}{grn}   {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                               {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}";
  215 sys51000:sys49155:ifcr(p)=3thenprint"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{wht}bridge out"
  216 sys49152:ifcr(p)=3thenprint"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{wht}on left   "
  217 sys49561:gosub5:ifch=-1then39
  220 sys49152:print"{home}{down}{down}{down}{down}{down}{rvon}{grn}                 {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND} {SHIFT--} {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}              {rvof}";
  221 sys49561:print"{rvon}{grn}                {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}             {rvof}";
  222 sys49152:print"{rvon}{grn}               {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}   {SHIFT--}   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}            {rvof}";
  223 sys49561:print"{rvon}{grn}              {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}         {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}           {rvof}";
  224 print"{rvon}{grn}             {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}     {SHIFT--}     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}          {rvof}";
  225 sys49155:print"{rvon}{grn}            {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}             {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}         {rvof}";
  226 print"{rvon}{grn}           {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}       {SHIFT--}       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}        {rvof}";
  227 sys51000:print"{rvon}{grn}          {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                 {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}       {rvof}";
  228 sys49152:print"{grn}{rvon}         {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}         {SHIFT--}         {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}      {rvof}";
  229 sys49561:print"{grn}{rvon}        {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}     {rvof}";
  230 sys49152:print"{rvon}{grn}       {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}    {rvof}";
  231 sys49561:print"{rvon}{grn}      {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}           {wht} {SHIFT--}            {red}{CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}   {rvof}";
  232 print"{rvon}{grn}     {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}  {rvof}";
  233 sys49561:print"{rvon}{grn}    {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                             {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon} {rvof}";
  234 print"{rvon}{grn}   {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                               {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}";
  235 sys49561:d=d+1:ifd=10andcr=1thend=0:goto380
  236 ifd=10andcr(p)=1thend=0:goto500
  237 ifd=10andcr(p)=2thend=0:goto1000
  238 sys49561:ifd=10andcr(p)=3thend=0:goto2100
  239 ifcr(p)=3thenprint"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{wht}bridge out"
  240 sys51000:sys49155:ifcr(p)=3thenprint"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{wht}on left   "
  241 ifcr(p)=6thengosub7100
  242 ifpeek(53241)=0thengosub101
  243 ifpeek(53242)=0thengosub102
  244 sys49561:ifpeek(53243)=0thengosub103
  245 ifpeek(53244)=0thengosub105
  246 ifpeek(53245)=1andpeek(v+10)<140thenpoke53245,int(rnd(1)*2)+1
  250 sys49561:gosub5:ifch=-1then39
  251 goto200
  300 end
  380 poke53280,0:poke53281,12:poke53233,0:pokev+10,0
  381 print"{clr}{wht}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+} {blu}{rvon}      {rvof}{wht}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  382 print"{wht}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+} {blu}{rvon}      {rvof}{wht}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  383 print"{wht}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+} {blu}{rvon}      {rvof}{wht}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  384 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}      {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  385 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}         {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  386 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}           {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  387 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}           {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  389 p=p+1:sd=1
  391 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}                        {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  392 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}                        {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  393 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}                        {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  394 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}                        {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  395 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}                        {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  396 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}                        {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  397 print"{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}                        {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";
  398 print"                                 {SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}{SHIFT-+}";                         
  399 c1=155:c2=149:c3=28
  400 sys51000:printchr$(c1):print"{home}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{rght}{CBM-+}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{rght}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}";
  401 print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{rght}{CBM-+}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{rght}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}";
  402 sys49155:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{rght}{CBM-+}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{rght}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}";
  403 sys49561:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{rght}{SHIFT-POUND}{rght}{rght}{rght}{rght}{CBM-*}{CBM-+}{rght}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}";
  404 sys49152:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+} {rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{rght}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}";
  405 print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{SHIFT-POUND}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght} {CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}";
  406 sys49155:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{SHIFT-POUND}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}";
  407 gosub5:ifch=-1then39
  419 sys49561:printchr$(c2):sys51000
  420 print"{home}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  421 sys49152:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  422 sys49561:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  423 print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  424 sys49155:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  425 print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  426 sys49561:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  427 sys49155:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  428 print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  429 sys49561:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  430 print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  431 sys49152:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{SHIFT-POUND}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  432 sys51000:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{SHIFT-POUND}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  433 sys49561:print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{SHIFT-POUND}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}";
  434 print"{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{rght}{rght}{rght}{rght}{rght}{rght}";
  449 gosub5:ifch=-1then39
  450 sys49155:printchr$(c3):print"{home}{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  451 print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  452 sys49561:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  453 sys49152:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  454 print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  455 sys51000:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  456 sys49155:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  457 print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  458 sys49561:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  459 sys49152:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  460 sys49561:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  461 print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  462 sys49561:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  463 print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  464 sys51000:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  465 sys49152:print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  466 print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  467 print"{CBM-+}{CBM-+}{CBM-+}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-+}{CBM-+}{CBM-+}";
  468 sys49155:print"{CBM-+}{CBM-+}{SHIFT-POUND}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{CBM-+}{CBM-+}";
  469 print"{CBM-+}{SHIFT-POUND}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{CBM-*}{CBM-+}";
  470 sys49561:print"{wht}{home}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght} {down}{down}{left} {down}{down}{down}{left} {down}{down}{down}{down}{left} {down}{down}{down}{down}{down}{left} "
  471 print"{wht}{home}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght} {down}{down}{left} {down}{down}{down}{left} {down}{down}{down}{down}{left} {down}{down}{down}{down}{down}{left} "
  472 ifsd=1thenprint"{wht}{home}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{SHIFT--}{down}{down}{left}{SHIFT--}{down}{down}{down}{left}{SHIFT--}{down}{down}{down}{down}{left}{SHIFT--}{down}{down}{down}{down}{down}{left}{SHIFT--}"
  473 sys49561:ifsd=-1thenprint"{wht}{home}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{SHIFT--}{down}{down}{left}{SHIFT--}{down}{down}{down}{left}{SHIFT--}{down}{down}{down}{down}{left}{SHIFT--}{down}{down}{down}{down}{down}{left}{SHIFT--}"
  480 gosub5:ifch=-1then39
  485 ifcr(p)=6thengosub7100
  486 sys49561:ifd=10andcr(p)=3thend=0:goto188
  487 sd=-sd
  488 d=d+1:ifd=10andcr(p)=1thend=0:goto188
  489 ifd=10andcr(p)=2thend=0:goto500
  490 ifpeek(53241)=0thengosub101
  491 sys49561:ifpeek(53242)=0thengosub102
  492 ifpeek(53243)=0thengosub103
  493 ifpeek(53244)=0thengosub105
  494 ifpeek(53245)=1andpeek(v+10)<140thenpoke53245,int(rnd(1)*2)+1
  497 sys49561:ifc1=155thenc1=28:c2=155:c3=149:goto400
  498 ifc1=149thenc1=155:c2=149:c3=28:goto400
  499 ifc1=28thenc1=149:c2=28:c3=155:goto400
  500 print"{home}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3}       {rvof}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}"
  501 print"{home}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}   {blk}  {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}"
  502 print"{home}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}   {blk}  {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}"
  503 print"{home}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}   {blk}  {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}"
  504 print"{home}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}   {blk}  {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}"
  507 sys49155:fordf=0to100:next
  510 print"{home}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3}           {rvof}{rght}{rght}{rght}{rght}{rght}{rght}"
  511 print"{home}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}     {blk}    {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}"
  512 print"{home}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}     {blk}    {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}"
  513 print"{home}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}     {blk}    {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}"
  514 print"{home}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}     {blk}    {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}"
  515 print"{home}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}     {blk}    {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}"
  517 print"{home}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}     {blk}    {gry3} {rvof}{rght}{rght}{rght}{rght}{rght}{rght}"
  518 sys51000:sys49155:fordf=0to100:next
  520 print"{home}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3}                 {rvof}{rght}{rght}{rght}"
  521 print"{home}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  522 print"{home}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  523 print"{home}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  524 print"{home}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  525 print"{home}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  526 print"{home}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  527 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  528 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rvon}{gry3} {blk}        {blk}       {gry3} {rvof}{rght}{rght}{rght}"
  529 sys49155:fordf=0to100:next
  780 poke53233,1:pokev+11,140:poke2045,50:poke53245,0:pokev+12,0:pokev+44,7
  790 poke53280,0:poke53281,0
  793 p=p+1
  794 print"{clr}{yel}  {CBM-N}     {CBM-N}      {CBM-N}   {CBM-N}   {yel}{CBM-J}     {CBM-H}   {CBM-H}    {CBM-H} ";
  795 print"{yel}  {CBM-N}     {CBM-N}      {CBM-N}   {CBM-N}{rvon}{blu}   {rvof}{yel}{CBM-J}     {CBM-H}   {CBM-H}    {CBM-H} ";
  796 print"{yel}  {CBM-N}     {CBM-N}      {CBM-N}   {CBM-N}{rvon}{blu}   {rvof}{yel}{CBM-J}     {CBM-H}   {CBM-H}    {CBM-H} ";
  797 print"{yel}  {CBM-N}     {CBM-N}      {CBM-N}   {CBM-N}{rvon}{blu}   {rvof}{yel}{CBM-J}     {CBM-H}   {CBM-H}    {CBM-H} ";
  798 print"{yel}  {CBM-N}     {CBM-N}      {CBM-N}   {CBM-N}{rvon}{blu}   {rvof}{yel}{CBM-J}     {CBM-H}   {CBM-H}    {CBM-H} ";
  800 sys49152:print"{home}{down}{down}{down}{down}{down}  {CBM-N}     {CBM-N}      {CBM-N}  {yel}NN   MM    {CBM-H}   {CBM-H}    {CBM-H} ";
  801 sys51000:print"  {CBM-N}     {CBM-N}      {CBM-N} {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}  {SHIFT--}  {CBM-*}{rvon}{CBM-*}{rvof}   {CBM-H}   {CBM-H}    {CBM-H} ";
  802 sys49155:print"  {CBM-N}     {CBM-N}      {CBM-N}NN       MM  {CBM-H}   {CBM-H}    {CBM-H} ";
  803 print"  {CBM-N}     {CBM-N}      {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}    {SHIFT--}    {CBM-*}{rvon}{CBM-*}{rvof} {CBM-H}   {CBM-H}    {CBM-H} ";
  804 sys49561:print"  {CBM-N}     {CBM-N}     NN           MM{CBM-H}   {CBM-H}    {CBM-H} ";
  805 sys49152:print"  {CBM-N}     {CBM-N}    {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}      {SHIFT--}      {CBM-*}{rvon}{CBM-*}{rvof}   {CBM-H}    {CBM-H} ";
  806 print"  {CBM-N}     {CBM-N}   NN               MM  {CBM-H}    {CBM-H} ";
  807 sys51000:sys49152:print"  {CBM-N}     {CBM-N}  {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}        {SHIFT--}        {CBM-*}{rvon}{CBM-*}{rvof} {CBM-H}    {CBM-H} ";
  808 sys49561:print"  {CBM-N}     {CBM-N} NN                   MM{CBM-H}    {CBM-H} ";
  809 print"  {CBM-N}     {CBM-N}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                     {CBM-*}{rvon}{CBM-*}{rvof}    {CBM-H} ";
  810 sys49155:print"  {CBM-N}     NN           {SHIFT--}           MM   {CBM-H} ";
  811 print"  {CBM-N}    {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                         {CBM-*}{rvon}{CBM-*}{rvof}  {CBM-H} ";
  812 sys49561:print"  {CBM-N}   NN                           MM {CBM-H} ";
  813 sys49152:print"  {CBM-N}  {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                             {CBM-*}{rvon}{CBM-*}{rvof}{CBM-H} ";
  814 print"  {CBM-N} NN               {SHIFT--}               MM ";
  815 sys49561:sys51000:poke2045,50
  819 gosub5:ifch=-1then39
  820 sys49155:print"{home}{down}{down}{down}{down}{down}  {CBM-N}     {CBM-N}      {CBM-N}  {yel}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND} {SHIFT--} {CBM-*}{rvon}{CBM-*}{rvof}    {CBM-H}   {CBM-H}    {CBM-H} ";
  821 sys49561:print"  {CBM-N}     {CBM-N}      {CBM-N} NN     MM   {CBM-H}   {CBM-H}    {CBM-H} ";
  822 print"  {CBM-N}     {CBM-N}      {CBM-N}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}   {SHIFT--}   {CBM-*}{rvon}{CBM-*}{rvof}  {CBM-H}   {CBM-H}    {CBM-H} ";
  823 sys49152:print"  {CBM-N}     {CBM-N}      NN         MM {CBM-G}   {CBM-H}    {CBM-H} ";
  824 print"  {CBM-N}     {CBM-N}     {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}     {SHIFT--}     {CBM-*}{rvon}{CBM-*}{rvof}{CBM-H}   {CBM-H}    {CBM-H} ";
  825 sys49152:print"  {CBM-N}     {CBM-N}    NN             MM   {CBM-H}    {CBM-H} ";
  826 sys49561:print"  {CBM-N}     {CBM-N}   {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}       {SHIFT--}       {CBM-*}{rvon}{CBM-*}{rvof}  {CBM-H}    {CBM-H} ";
  827 sys51000:print"  {CBM-N}     {CBM-N}  NN                 MM {CBM-H}    {CBM-H} ";
  828 sys49152:print"  {CBM-N}     {CBM-N} {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}         {SHIFT--}         {CBM-*}{rvon}{CBM-*}{rvof}{CBM-H}    {CBM-H} ";
  829 print"  {CBM-N}     {CBM-N}NN                     MM    {CBM-H} ";
  830 sys49152:print"  {CBM-N}     {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                       {CBM-*}{rvon}{CBM-*}{rvof}   {CBM-H} ";
  831 sys49561:print"  {CBM-N}    NN            {SHIFT--}            MM  {CBM-H} ";
  832 print"  {CBM-N}   {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                           {CBM-*}{rvon}{CBM-*}{rvof} {CBM-H} ";
  833 sys49155:print"  {CBM-N}  NN                             MM{CBM-H} ";
  834 print"  {CBM-N} {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                               {CBM-*}{rvon}{CBM-*}{rvof} ";
  835 sys49561:d=d+1:ifd=10andcr(p)=1thend=0:goto380
  836 ifd=10andcr(p)=2thend=0:goto188
  837 ifd=10andcr(p)=3thend=0:goto188
  838 sys49561:ifcr(p)=6thengosub7100
  840 sys51000:poke2045,50
  842 sys49155:ifpeek(53241)=0thengosub101
  843 ifpeek(53242)=0thengosub102
  844 ifpeek(53243)=0thengosub103
  845 sys49561:ifpeek(53244)=0thengosub105
  846 pokev+10,peek(v)
  847 gosub5:ifch=-1then39
  850 goto800
 1000 v=53248:poke53280,0:poke53281,12:gosub140
 1001 print"{home}{rvon}{blu}                                        {rvof}";
 1002 print"{rvon}{blu}                                        {rvof}";
 1003 print"    {CBM-*}{SHIFT-POUND} {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}      {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND} ";
 1004 print"    N   M     N   N       M       M  N  ";
 1005 print"   N         N             M       M    ";
 1006 print"                                        ";
 1007 p=p+1
 1010 sys49152:print"{home}{down}{down}{down}{down}{down}{rvon}{grn}                        {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}    {rvon}{CBM-*}{grn}        {rvof}";
 1011 sys51000:print"{rvon}{grn}                      {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}   N  {CBM-*}{rvon}{grn}        {rvof}";
 1012 print"{rvon}{grn}                     {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}        {rvon}{CBM-*}{grn}       {rvof}";
 1013 sys49155:print"{rvon}{grn}                   {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}     N    {CBM-*}{rvon}{grn}       {rvof}";
 1014 print"{rvon}{grn}                  {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}            {rvon}{CBM-*}{grn}      {rvof}";
 1015 sys49561:print"{rvon}{grn}                {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}       N      {CBM-*}{rvon}{grn}      {rvof}";
 1016 sys49152:print"{rvon}{grn}               {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                {rvon}{CBM-*}{grn}     {rvof}";
 1017 sys49561:print"{rvon}{grn}             {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}         /        {CBM-*}{rvon}{grn}     {rvof}";
 1018 sys51000:print"{grn}{rvon}            {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                    {rvon}{CBM-*}{grn}    {rvof}";
 1019 sys49155:print"{grn}{rvon}          {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                      {CBM-*}{rvon}{grn}    {rvof}";
 1020 print"{rvon}{grn}         {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}           {wht} N{red}           {rvon}{CBM-*}{grn}   {rvof}";
 1021 sys49152:print"{rvon}{grn}       {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                          {CBM-*}{rvon}{grn}   {rvof}";
 1022 sys49561:print"{rvon}{grn}      {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                            {rvon}{CBM-*}{grn}  {rvof}";
 1023 print"{rvon}{grn}    {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}               N              {CBM-*}{rvon}{grn}  {rvof}";
 1024 sys49155:print"{rvon}{grn}   {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                                {rvon}{CBM-*}{grn} {rvof}";
 1025 sys51000
 1026 pokev,peek(v)-20:ifpeek(v)<80thenpokev,80
 1027 sys49561:gosub5:ifch=-1then39
 1030 sys49152:print"{home}{down}{down}{down}{down}{down}{rvon}{grn}                        {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}    {rvon}{CBM-*}{grn}        {rvof}";
 1031 print"{rvon}{grn}                      {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}      {CBM-*}{rvon}{grn}        {rvof}";
 1032 print"{rvon}{grn}                     {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}    N   {rvon}{CBM-*}{grn}       {rvof}";
 1033 sys49155:print"{rvon}{grn}                   {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}          {CBM-*}{rvon}{grn}       {rvof}";
 1034 print"{rvon}{grn}                  {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}      N     {rvon}{CBM-*}{grn}      {rvof}";
 1035 sys49561:print"{rvon}{grn}                {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}              {CBM-*}{rvon}{grn}      {rvof}";
 1036 sys49152:print"{rvon}{grn}               {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}        N       {rvon}{CBM-*}{grn}     {rvof}";
 1037 sys51000:print"{rvon}{grn}             {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                  {CBM-*}{rvon}{grn}     {rvof}";
 1038 sys49561:print"{grn}{rvon}            {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                    {rvon}{CBM-*}{grn}    {rvof}";
 1039 sys49152:print"{grn}{rvon}          {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}          {wht}  N{red}         {CBM-*}{rvon}{grn}    {rvof}";
 1040 print"{rvon}{grn}         {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                        {rvon}{CBM-*}{grn}   {rvof}";
 1041 print"{rvon}{grn}       {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                          {CBM-*}{rvon}{grn}   {rvof}";
 1042 sys49155:print"{rvon}{grn}      {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}              N             {rvon}{CBM-*}{grn}  {rvof}";
 1043 print"{rvon}{grn}    {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                              {CBM-*}{rvon}{grn}  {rvof}";               
 1044 sys49561:print"{rvon}{grn}   {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                                {rvon}{CBM-*}{grn} {rvof}";
 1045 sys49152:d=d+1:ifd=3andcr(p)=1thend=0:goto200
 1046 ifd=3andcr(p)=2thend=0:goto1100
 1047 ifd=3andcr(p)=3thend=0:goto188
 1048 ifcr(p)=6thengosub7100
 1049 sys49561:pokev,peek(v)-20:ifpeek(v)<80thenpokev,80
 1050 ifcr(p)=6thengosub7100
 1051 sys49155:ifpeek(53241)=0thengosub101
 1052 ifpeek(53242)=0thengosub102
 1053 ifpeek(53243)=0thengosub103
 1054 sys49561:ifpeek(53244)=0thengosub105
 1055 sys51000:ifpeek(53245)=1andpeek(v+10)<140thenpoke53245,int(rnd(1)*2)+1
 1056 gosub5:ifch=-1then39
 1060 goto1010
 1100 v=53248:poke53280,0:poke53281,12:gosub140
 1101 print"{home}{rvon}{blu}                                        {rvof}";
 1102 print"{rvon}{blu}                                        {rvof}";
 1103 print"    {CBM-*}{SHIFT-POUND} {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}      {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND} ";
 1104 print"    N   M     N   N       M       M  N  ";
 1105 print"   N         N             M       M    ";
 1106 print"                                        ";
 1107 p=p+1
 1110 sys49155:print"{home}{down}{down}{down}{down}{down}{grn}{rvon}          {rvof}{SHIFT-POUND}{red}{SHIFT-POUND}   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                     {rvof}";
 1111 sys51000:print"{grn}{rvon}          {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}  M   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                   {rvof}";
 1112 sys49152:print"{grn}{rvon}          {rvof}{SHIFT-POUND}{red}{SHIFT-POUND}       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                  {rvof}";
 1113 print"{grn}{rvon}         {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}    M     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                {rvof}";
 1114 sys49152:print"{grn}{rvon}         {rvof}{SHIFT-POUND}{red}{SHIFT-POUND}           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}               {rvof}";
 1115 sys49561:print"{rvon}{grn}        {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}      M       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}             {rvof}";
 1116 print"{grn}{rvon}        {rvof}{SHIFT-POUND}{red}{SHIFT-POUND}               {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}            {rvof}";
 1117 sys49152:print"{grn}{rvon}       {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}        M         {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}          {rvof}";
 1118 sys51000:print"{grn}{rvon}       {rvof}{SHIFT-POUND}{red}{SHIFT-POUND}                   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}         {rvof}";
 1119 print"{grn}{rvon}      {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}                      {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}       {rvof}";
 1120 sys49152:print"{grn}{rvon}      {rvof}{SHIFT-POUND}{red}{SHIFT-POUND}           {wht}M{red}           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}      {rvof}";
 1121 print"{grn}{rvon}     {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}                          {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}    {rvof}";
 1122 sys49155:print"{grn}{rvon}     {rvof}{SHIFT-POUND}{red}{SHIFT-POUND}                           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}   {rvof}";
 1123 print"{grn}{rvon}    {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}               M              {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon} {rvof}";
 1124 sys49561:print"{rvon}{grn}   {rvof}{SHIFT-POUND}{red} {SHIFT-POUND}                               {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}";
 1125 sys51000
 1126 ifpeek(v)<240thenpokev,peek(v)+20
 1127 gosub5:ifch=-1then39
 1130 sys49155:print"{home}{down}{down}{down}{down}{down}{grn}{rvon}          {rvof}{SHIFT-POUND}{wht}{SHIFT-POUND} M {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                     {rvof}";
 1131 sys49561:print"{grn}{rvon}          {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}      {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                   {rvof}";
 1132 sys49152:print"{grn}{rvon}          {rvof}{SHIFT-POUND}{wht}{SHIFT-POUND}   M   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                  {rvof}";
 1133 print"{grn}{rvon}         {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}          {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}                {rvof}";
 1134 sys49152:print"{grn}{rvon}         {rvof}{SHIFT-POUND}{wht}{SHIFT-POUND}     M     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}               {rvof}";
 1135 print"{rvon}{grn}        {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}              {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}             {rvof}";
 1136 sys51000:print"{grn}{rvon}        {rvof}{SHIFT-POUND}{wht}{SHIFT-POUND}       M       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}            {rvof}";
 1137 sys49152:print"{grn}{rvon}       {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}                  {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}          {rvof}";
 1138 sys49561:print"{grn}{rvon}       {rvof}{SHIFT-POUND}{wht}{SHIFT-POUND}                   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}         {rvof}";
 1139 print"{grn}{rvon}      {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}          {wht}M{red}           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}       {rvof}";
 1140 sys49152:print"{grn}{rvon}      {rvof}{SHIFT-POUND}{wht}{SHIFT-POUND}                       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}      {rvof}";
 1141 print"{grn}{rvon}     {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}                          {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}    {rvof}";
 1142 sys49155:print"{grn}{rvon}     {rvof}{SHIFT-POUND}{wht}{SHIFT-POUND}             M             {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}   {rvof}";
 1143 print"{grn}{rvon}    {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}                              {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon} {rvof}";
 1144 print"{rvon}{grn}   {rvof}{SHIFT-POUND}{wht} {SHIFT-POUND}                               {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}";
 1145 d=d+1:ifd=3andcr(p)=1thend=0:goto200
 1146 ifd=3andcr(p)=2thend=0:goto1000
 1147 ifd=3andcr(p)=3thend=0:goto188
 1148 ifcr(p)=6thengosub7100
 1149 gosub150
 1150 ifcr(p)=6thengosub7100
 1151 sys49155:ifpeek(53241)=0thengosub101
 1152 ifpeek(53242)=0thengosub102
 1153 ifpeek(53243)=0thengosub103
 1154 ifpeek(53244)=0thengosub105
 1155 sys51000:ifpeek(53245)=1andpeek(v+10)<140thenpoke53245,int(rnd(1)*2)+1
 1156 ifpeek(v)<240thenpokev,peek(v)+20
 1157 gosub5:ifch=-1then39
 1160 goto1110
 1200 print"{home}{down}{down}{down}{down}{down}{rvon}{grn}                        {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}    {rvon} {grn}        {rvof}";
 1201 print"{rvon}{grn}                      {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}   N  {rvon} {grn}        {rvof}";
 1202 print"{rvon}{grn}                     {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}        {rvon} {grn}       {rvof}";
 1203 print"{rvon}{grn}                   {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}     N    {rvon} {grn}       {rvof}";
 1204 print"{rvon}{grn}                  {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}            {rvon} {grn}      {rvof}";
 1205 print"{rvon}{grn}                {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}       N      {rvon} {grn}      {rvof}";
 1206 print"{rvon}{grn}               {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                {rvon} {grn}     {rvof}";
 1207 print"{rvon}{grn}             {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}         /        {rvon} {grn}     {rvof}";
 1208 print"{grn}{rvon}            {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                    {rvon} {grn}    {rvof}";
 1209 print"{grn}{rvon}          {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                      {rvon} {grn}    {rvof}";
 1210 print"{rvon}{grn}         {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}            N           {rvon} {grn}   {rvof}";
 1211 print"{rvon}{grn}       {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                          {rvon} {grn}   {rvof}";
 1212 print"{rvon}{grn}      {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                            {rvon} {grn}  {rvof}";
 1213 print"{rvon}{grn}    {rvof}{SHIFT-POUND}{wht}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}               N              {rvon} {grn}  {rvof}";
 1214 print"{rvon}{grn}   {rvof}{SHIFT-POUND}{red}{rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}                                {rvon} {grn} {rvof}";
 1300 print"{home}{rvon}{blu}                                        {rvof}";
 1301 print"{rvon}{blu}                                        {rvof}";
 1302 a1$="    {CBM-*}{SHIFT-POUND} {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND}     {CBM-*}{SHIFT-POUND}      {CBM-*}{SHIFT-POUND}  {CBM-*}{SHIFT-POUND} "
 1303 a2$="    N   M     N   N       M       M  N  "
 1304 a3$="   N         N             M       M    "
 1305 print"                                        ";
 1310 printlen(a1$),len(a2$),len(a3$),len(a4$),len(a5$)
 1320 a1$=right$(a1$,55)+left$(a1$,1)
 1321 a2$=right$(a2$,51)+left$(a2$,1)
 1322 a3$=right$(a3$,51)+left$(a3$,1)
 1323 a4$=right$(a4$,53)+left$(a4$,1)
 1324 a5$=right$(a5$,46)+left$(a5$,1)
 1330 print"{home}";a1$;
 1331 printa2$;a3$;a4$;a5$:goto1320
 1400 end
 1499 poke53270,peek(53270)and247
 1500 print"{home}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w{down}{left}w"
 1501 poke53270,(peek(53270)and248)+7
 1502 forx=0to7step1:poke53270,(peek(53270)and248)+x:next
 1600 end                                                                   
 2100 print"{home}{blu}{rvon}                                        {rvof}";
 2101 print"{blu}{rvon}                                        {rvof}";
 2102 print"{blu}{rvon}                                        {rvof}";
 2103 print"{blu}{rvon}                                        {rvof}";
 2105 print"{blu}{rvon}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{CBM-@}{rvof}";
 2110 poke53280,0:poke53281,12:
 2111 gosub12:gosub13:gosub14:gosub15
 2120 pokev+2,0:p1=48:p2=49:rem  poke2044,p1:poke2041,p2:poke2042,p2:poke2043,p2
 2121 ifpeek(v)<180thenpoke2040,p1
 2200 sys49152:print"{home}{down}{down}{down}{down}{down}{rvon}{grn}                  {blu}   {red} {rvof} {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}              {rvof}";
 2201 sys51000:print"{rvon}{grn}                {rvof}{SHIFT-POUND}{rvon}{blu}    {wht} {rvof}  {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}             {rvof}";
 2202 sys49155:print"{rvon}{grn}                {blu}     {red} {rvof}   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}            {rvof}";
 2203 print"{rvon}{grn}              {rvof}{SHIFT-POUND}{rvon}{blu}      {wht} {rvof}    {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}           {rvof}";
 2204 sys49561:print"{rvon}{grn}              {blu}       {red} {rvof}     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}          {rvof}";
 2205 sys49152:print"{rvon}{grn}            {rvof}{SHIFT-POUND}{rvon}{blu}        {wht} {rvof}      {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}         {rvof}";
 2206 sys49561:print"{rvon}{grn}            {blu}         {red} {rvof}       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}        {rvof}";
 2207 sys51000:print"{rvon}{grn}          {rvof}{SHIFT-POUND}{rvon}{blu}          {wht} {rvof}        {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}       {rvof}";
 2208 sys49152:print"{grn}{rvon}          {blu}           {red} {rvof}         {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}      {rvof}";
 2209 print"{grn}{rvon}        {rvof}{SHIFT-POUND}{rvon}{blu}            {wht} {rvof}          {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}     {rvof}";
 2210 sys49155:print"{rvon}{grn}        {blu}             {red} {rvof}           {red}{CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}    {rvof}";
 2211 print"{rvon}{grn}      {rvof}{SHIFT-POUND}{rvon}{blu}              {wht} {rvof}            {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}   {rvof}";
 2212 sys49561:print"{rvon}{grn}      {blu}               {red} {rvof}             {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}  {rvof}";
 2213 sys49152:print"{rvon}{grn}    {rvof}{SHIFT-POUND}{rvon}{blu}                {wht} {rvof}              {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon} {rvof}";
 2214 print"{rvon}{grn}    {blu}                 {red} {rvof}               {red}{CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}";
 2215 sys49561:gosub5:sys51000:ifch=-1then39
 2216 ifpeek(v)>170andpeek(v)<200thengosub6000
 2220 sys49155:print"{home}{down}{down}{down}{down}{down}{rvon}{grn}                  {blu}   {wht} {rvof} {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}              {rvof}";
 2221 print"{rvon}{grn}                 {blu}    {red} {rvof}  {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}             {rvof}";
 2222 sys49152:print"{rvon}{grn}               {rvof}{SHIFT-POUND}{rvon}{blu}     {wht} {rvof}   {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}            {rvof}";
 2223 sys49561:print"{rvon}{grn}               {blu}      {red} {rvof}    {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}           {rvof}";
 2224 print"{rvon}{grn}             {rvof}{SHIFT-POUND}{rvon}{blu}       {wht} {rvof}     {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}          {rvof}";
 2225 sys49155:print"{rvon}{grn}             {blu}        {red} {rvof}      {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}         {rvof}";
 2226 print"{rvon}{grn}           {rvof}{SHIFT-POUND}{rvon}{blu}         {wht} {rvof}       {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}        {rvof}";
 2227 sys51000:sys49152:print"{rvon}{grn}           {blu}          {red} {rvof}        {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}       {rvof}";
 2228 sys49561:print"{grn}{rvon}         {rvof}{SHIFT-POUND}{rvon}{blu}           {wht} {rvof}         {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}      {rvof}";
 2229 print"{grn}{rvon}         {blu}            {red} {rvof}          {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}     {rvof}";
 2230 sys49152:print"{rvon}{grn}       {rvof}{SHIFT-POUND}{rvon}{blu}             {wht} {rvof}           {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}    {rvof}";
 2231 print"{rvon}{grn}       {blu}              {red} {rvof}            {red}{CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}   {rvof}";
 2232 sys49561:print"{rvon}{grn}     {rvof}{SHIFT-POUND}{rvon}{blu}               {wht} {rvof}             {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon}  {rvof}";
 2233 print"{rvon}{grn}     {blu}                {red} {rvof}              {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}{rvon} {rvof}";
 2234 sys49152:print"{rvon}{grn}   {rvof}{SHIFT-POUND}{rvon}{blu}                 {wht} {rvof}               {CBM-*}{rvon}{CBM-*}{rvof}{grn}{CBM-*}";
 2235 d=d+1:ifd=30thend=0:goto188
 2239 sys51000
 2240 ifpeek(v)>170andpeek(v)<200thengosub6000
 2243 ifpeek(53242)=0thengosub122
 2244 sys49561:ifpeek(53243)=0thengosub123
 2245 ifpeek(53244)=0thengosub125
 2246 ifpeek(53245)=1andpeek(v+10)<180thenpoke53245,int(rnd(1)*2)+1
 2247 sys49561:gosub5:ifch=-1then39
 2250 goto2200
 5999 ifte=1thenreturn
 6000 pokev,peek(v)-10:poke2040,14:forx=0to100:next:sys49155
 6001 sys50900:pokev,peek(v)-10:poke2040,p1:forx=0to100:next:ifpeek(v)>60then6000
 6002 poke2040,33:forx=15to0step-1
 6003 poke54296,x:poke54276,129:poke54277,15:poke54272,200:poke54273,40:pokev+39,7
 6004 fory=0to300:next:sys49155:pokev+39,15
 6006 poke54296,0:poke54276,0:next
 6007 poke2040,p1:poke53232,0:ifte=1thenreturn
 6008 ch=ch-1:te=1: ifch<0thench=-1:return
 6010 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{wht}cars";ch
 6011 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{blk}track"
 6012 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}plan"
 6099 return
 7000 forn=1to6
 7002 cr(n)=int(rnd(1)*3)+1
 7003 next
 7004 cr(7)=6:p=1:print"{blk}"
 7005 x=30:y=24:n=1:dr=1
 7006 rem 1=500:2=1000:3=2100 country
 7007 rem1=188:3=188:2=500   city
 7008 rem1=380:2=188:3=188   tunnel
 7009 rem1=188:2=1100:3=188  right curve
 7010 gosub7400
 7011 forz1=30to39:forz2=20to24:poke55296+z1+40*z2,0:next:next
 7015 n=n+1:ifcr(n)=6then7300
 7016 ifd$="country"then7040
 7017 ifd$="bridge"thenn=n-1:goto7060
 7018 ifd$="left curve"then7065
 7019 ifd$="right curve"then7085
 7020 ifd$="city"then7035
 7021 ifd$="tunnel"then7022
 7022 ifcr(n)=2then7025
 7023 ifcr(n)=1then7031
 7024 ifcr(n)=3then7025
 7025 d$="country"
 7026 ondrgoto7027,7028,7029,7030
 7027 dr=1:poke1024+x+40*y,93:y=y-1:goto7015
 7028 dr=2:poke1024+x+40*y,67:x=x+1:goto7015
 7029 dr=3:poke1024+x+40*y,93:y=y+1:goto7015
 7030 dr=4:poke1024+x+40*y,67:x=x-1:goto7015
 7031 d$="city"
 7032 ondrgoto7027,7028,7029,7030
 7035 ifcr(n)=1orcr(n)=3then7037
 7036 ifcr(n)=2then7039
 7037 d$="country":ondrgoto7027,7028,7029,7030
 7039 d$="tunnel":ondrgoto7027,7028,7029,7030
 7040 ifcr(n)=1then7045
 7041 ifcr(n)=2then7047
 7042 ifcr(n)=3then7049
 7045 d$="tunnel"
 7046 ondrgoto7027,7028,7029,7030
 7047 d$="left curve"
 7048 ondrgoto7027,7028,7029,7030
 7049 d$="bridge"
 7050 ondrgoto7027,7028,7029,7030
 7060 d$="country":ondrgoto7027,7028,7029,7030
 7065 ifcr(n)=1then7075
 7066 ifcr(n)=3then7075
 7067 ifcr(n)=2then7077
 7070 dr=2:poke1024+x+40*y,85:x=x+1:goto7015
 7071 dr=3:poke1024+x+40*y,73:y=y+1:goto7015
 7072 dr=4:poke1024+x+40*y,75:x=x-1:goto7015
 7073 dr=1:poke1024+x+40*y,74:y=y-1:goto7015
 7075 d$="country"
 7076 ondrgoto7070,7071,7072,7073
 7077 d$="right curve"
 7078 ondrgoto7070,7071,7072,7073
 7082 ifcr(n)=2then7097
 7085 ifcr(n)=1then7095
 7086 ifcr(n)=3then7095
 7087 ifcr(n)=2then7097
 7090 dr=4:poke1024+x+40*y,75:x=x-1:goto7015
 7091 dr=1:poke1024+x+40*y,75:y=y-1:goto7015                           
 7092 dr=2:poke1024+x+40*y,74:x=x+1:goto7015                           
 7093 dr=3:poke1024+x+40*y,85:y=y+1:goto7015
 7095 d$="country"
 7096 ondrgoto7090,7091,7092,7093
 7097 d$="left curve"
 7098 ondrgoto7090,7091,7092,7093
 7099 return
 7100 gosub13000:bp=bp+1000:print"{home}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{wht}bonus";bp
 7101 forfg=1to20
 7102 sc=sc+bp/20:print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{wht}score";sc
 7103 forhj=0to20:next:next
 7104 goto7000
 7300 return
 7301 return
 7400 forz1=30to39:forz2=20to24:poke1024+z1+40*z2,32:next:next
 7401 return
 7500 forz1=30to39:forz2=18to24:poke55296+z1+40*z2,0:next:next:return
 8000 forn=0to62:poke832+n,peek(52000+n):next:ifpeek(53200)=21thenreturn
 8006 forn=0to62:poke896+n,peek(52063+n):next
 8007 forn=0to62:poke960+n,peek(52127+n):next
 8008 forn=0to62:poke3008+n,peek(52190+n):next
 8009 forn=0to62:poke2112+n,peek(52255+n):next
 8010 forn=0to62:poke2176+n,peek(52319+n):next
 8011 forn=0to62:poke2560+n,peek(52383+n):next
 8012 forn=0to62:poke2624+n,peek(52447+n):next
 8013 forn=0to62:poke2688+n,peek(52511+n):next
 8014 forn=0to62:poke2752+n,peek(52575+n):next
 8015 forn=0to127:poke2816+n,0:next
 8016 forn=0to62:poke2944+n,peek(52639+n):next
 8017 forn=0to62:poke3072+n,peek(52703+n):next
 8018 forn=0to62:poke3136+n,peek(52767+n):next
 8019 forn=0to62:poke3200+n,peek(52831+n):next:n=50900
 8020 reada:ifa=-1then8025
 8021 poken,a:n=n+1:goto8020
 8025 forn=0to62:poke3264+n,peek(52895+n):next:n=50900
 8026 forn=0to62:poke3328+n,peek(52959+n):next:n=50900
 8027 forn=0to62:poke3392+n,peek(53023+n):next:n=50900
 8028 forn=0to62:poke3456+n,peek(53087+n):next:n=51900
 8030 reada:ifa=-1then8032
 8031 poken,a:n=n+1:goto8030
 8032 n=51200
 8040 reada:ifa=-1then8042
 8041 poken,a:n=n+1:goto8040
 8042 n=51000
 8050 reada:ifa=-1then8052
 8051 poken,a:n=n+1:goto8050
 8052 rem
 8098 poke53200,21
 8099 return
 9000 poke53280,0:poke53281,0:print"{clr}{rght}{rght}{yel}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}wait for machine code to load"
 9001 forx=0to100:next
 9002 open1,1,0,"007 car chase"
 9003 input#1,ps$
 9004 x=49152
 9005 input#1,a:ifa=-1then9010
 9006 pokex,a:x=x+1
 9007 goto9005
 9010 close1
 9011 return
10000 data169,0,141,24,212,141,4,212
10001 data141,5,212,169,15,141,24,212
10002 data169,129,141,4,212,169,136
10003 data141,5,212,169,40,141,1,212
10004 data169,200,141,0,212,96,-1
10005 data174,0,208,202,202,202,142,0,208
10006 data174,2,208,202,202,202,142,2,208
10007 data174,4,208,202,202,202,142,4,208
10008 data174,6,208,202,202,202,142,6,208,96,-1
10010 data6,16,255,6,108,255
10011 data6,16,255,6,108,255
10012 data6,16,255,6,108,255
10013 data6,16,255,6,108,255
10014 data9,159,136,10,205,136,11,114,136
10015 data9,159,136,10,205,136,11,114,136
10016 data9,159,136,10,205,136,11,114,136
10017 data9,159,136,10,205,136,11,114,136
10018 data9,159,136,10,205,136,11,114,136
10019 data9,159,136,10,205,136,11,114,136
10020 data9,159,136,10,205,136,11,114,136
10021 data9,159,136,10,205,65,10,205,65
10022 data10,205,65,9,159,65,9,159,65
10023 data9,159,65,9,159,65,11,114,65
10024 data11,114,65,10,205,65,10,205,65
10025 data10,205,65
10026 data9,159,136,10,205,65,10,205,65
10027 data10,205,65,9,159,65,9,159,65
10028 data9,159,65,9,159,65,11,114,65
10029 data11,114,65,10,205,65,10,205,65
10030 data10,205,65
10031 data9,159,136,10,205,65,10,205,65
10032 data10,205,65,9,159,65,9,159,65
10033 data9,159,65,9,159,65,11,114,65
10034 data11,114,65,10,205,65,10,205,65
10035 data10,205,65
10036 data10,205,65,10,60,136,9,159,136
10037 data16,47,255,14,107,255,12,216,255
10038 data12,32,255,12,216,136,-1
10050 data169,0,141,12,212,141,11,212
10051 data169,15,141,24,212,169,9,141,12,212
10052 data169,65,141,11,212,169,0,141,10,212
10053 data169,255,141,9,212,174,255,199
10054 data232,189,0,200,141,8,212
10055 data232,189,0,200,141,7,212
10056 data232,189,0,200,141,13,212
10057 data142,255,199,169,233,205,255,199
10058 data240,1,96,169,92,141,255,199
10059 data238,254,199,169,5,205,254,199
10060 data240,1,96,169,2,141,255,199,141,254,199,96,-1
10999 goto94
11000 print"{clr}":poke53280,0:poke53281,0:v=53248:poke53276,255:poke54296,0:sc=0
11001 poke53285,2:poke53286,15
11002 pokev+21,0:forx=0to15:pokev+x,0:next:pokev+21,255:bp=0
11010 print"{home}{down}{yel}          {rvon}{SHIFT-POUND}   {CBM-*}{rvof}  {rvon}{SHIFT-POUND}   {CBM-*}{rvof} {red} {rvon}    {rvof}{SHIFT-POUND}{rvon}{SHIFT-POUND}     {rvof}     ";
11011 print" {yel}         {rvon} {rvof}   {rvon} {rvof}  {rvon} {rvof}   {rvon} {rvof}   {red} {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND} {SHIFT-*}{SHIFT-*}{SHIFT-*}K       ";
11012 print"{yel}          {rvon} {rvof}   {rvon} {rvof}  {rvon} {rvof}   {rvon} {rvof}  {red} {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}             ";
11013 print"{yel}          {CBM-*}{rvon}   {rvof}{SHIFT-POUND}  {CBM-*}{rvon}   {rvof}{SHIFT-POUND} {red} {rvon}{SHIFT-POUND}{rvof}{SHIFT-POUND}              ";
11014 print"{down}{down}{down}{down}{down}{down}{rvon}{SHIFT-POUND}  {rvof} {rvon}{SHIFT-POUND}  {CBM-*}{rvof} {rvon}  {CBM-*}{rvof}   {rvon}{SHIFT-POUND}  {rvof} {rvon} {rvof} {rvon} {rvof} {rvon}{SHIFT-POUND}  {CBM-*}{rvof} {rvon}{SHIFT-POUND}  {CBM-*}{rvof} {rvon}    {rvof}   ";
11015 print"{rvon} {rvof}   {rvon} {rvof}  {rvon} {rvof} {rvon} {rvof} {rvon} {rvof}   {rvon} {rvof}   {rvon} {rvof} {rvon} {rvof} {rvon} {rvof}  {rvon} {rvof} {rvon} {rvof}    {rvon} {rvof}      ";
11016 print"{rvon} {rvof}   {rvon}    {rvof} {rvon}  {rvof}{SHIFT-POUND}   {rvon} {rvof}   {rvon}   {rvof} {rvon}    {rvof} {CBM-*}{rvon}  {CBM-*}{rvof} {rvon}    {rvof}   ";
11017 print"{rvon} {rvof}   {rvon} {rvof}  {rvon} {rvof} {rvon} {rvof}{CBM-*}{rvon}{CBM-*}{rvof}   {rvon} {rvof}   {rvon} {rvof} {rvon} {rvof} {rvon} {rvof}  {rvon} {rvof}    {rvon} {rvof} {rvon} {rvof}      ";
11018 print"{CBM-*}{rvon}  {rvof} {rvon} {rvof}  {rvon} {rvof} {rvon} {rvof} {rvon} {rvof}   {CBM-*}{rvon}  {rvof} {rvon} {rvof} {rvon} {rvof} {rvon} {rvof}  {rvon} {rvof} {CBM-*}{rvon}  {rvof}{SHIFT-POUND} {rvon}    {rvof}   ";
11019 print"{down}        (c)coplin software 1985"
11020 print"{down}{down}       press 'i' for instructions"
11021 print"       or any other to start game"
11030 poke2040,52:pokev,95:pokev+1,100
11031 poke2041,53:pokev+2,145:pokev+3,100
11032 poke2042,53:pokev+4,190:pokev+5,100
11033 poke2043,54:pokev+6,235:pokev+7,100
11034 pokev+29,255:pokev+23,0
11067 poke51199,2:poke51198,2
11069 geta$:ifa$<>""then11069
11070 geta$:sys51900:sys51000:forx=0to50:next:ifa$=""then11070
11071 ifa$="i"then12000
11072 poke54296,0:poke51199,2:poke51198,2
11075 mu=0
11078 pokev+21,0:forx=0to15:pokev+x,0:next:pokev+21,255
11079 print"{clr}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{yel}ready"
11080 pokev+29,0
11100 pokev+23,128:gosub7500:gosub7000
11999 goto91
12000 gosub12100:print"{clr}":v=53248:pokev+21,0:forx=0to15:pokev+x,0:next:pokev+21,255
12001 poke53281,11:print"{home}{down}{rght}{blk}            the car.":pokev+29,1
12002 print"            {CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}"
12005 poke53285,0:poke53286,2
12010 poke2040,13:pokev+39,15:pokev+23,peek(v+23)+1:pokev,150:pokev+1,150
12020 print"     this is the car you drive. it was "
12021 print"{rght}{rght}{rght}designed    especially   for   this "
12022 print"{rght}{rght}{rght}mission and features secret gadgets"
12023 print"{rght}{rght}{rght}to use."
12025 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{yel}<= double"
12026 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}  fire  "
12027 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}  guns."
12028 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}  machine"
12029 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{cyn}{rght}surface =>"
12030 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{cyn}{rght}to air "
12031 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{cyn}{rght}missiles"
12032 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{gry3}{rght}rear ^"
12033 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}smoke screen."
12034 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{rght}{blk}{rght}hit any key to continue."
12035 geta$:ifa$=""then12035
12040 :v=53248:pokev,0:pokev+1,0:pokev+29,0
12041 print"{clr}{down}{rght}{down}{rght}            the controls."
12042 print"             {CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}{CBM-T}"
12050 print"                                        ";
12051 print"              N{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}{CBM-Y}M             ";
12052 print"              {CBM-H}  U{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}I  {CBM-N}             ";
12053 print"              {CBM-H}  {SHIFT--}{cyn}guns{blk} {SHIFT--}  {CBM-N}             ";
12054 print"              {CBM-H}  J{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}K  {CBM-N}             ";
12055 print"              {CBM-H}  {cyn}missile{blk}  {CBM-N}             ";
12056 print"              {CBM-H}  U{SHIFT-*}{SHIFT-*}{CBM-E}{SHIFT-*}{SHIFT-*}I  {CBM-N}             ";
12057 print"              {CBM-H}  {SHIFT--}     {SHIFT--}  {CBM-N}             ";
12058 print"             {cyn}left{blk}{CBM-W}     {CBM-Q}{cyn}right{blk}           ";
12060 print"              {CBM-H}  {SHIFT--}     {SHIFT--}  {CBM-N}             ";
12061 print"              {CBM-H}  J{SHIFT-*}{SHIFT-*}{CBM-R}{SHIFT-*}{SHIFT-*}K  {CBM-N}             ";
12062 print"              {CBM-H}   {cyn}smoke{blk}   {CBM-N}             ";
12063 print"              M{CBM-P}{CBM-P}{CBM-P}{CBM-P}{CBM-P}{CBM-P}{CBM-P}{CBM-P}{CBM-P}{CBM-P}{CBM-P}N             ";
12064 print"{down}{down}     only one of your weapons can     "
12065 print"         be used at one time.     "
12066 print"{down}{down}        {cyn}hit any key to continue   "
12067 geta$:ifa$=""then12067
12070 print"{clr}{down}{rght} {cyn}U{SHIFT-*}{SHIFT-*}I                                   ";
12071 print" {SHIFT--}{blk}f1{cyn}{SHIFT--}{blk} pressing this puts you in turbo   ";
12072 print" {cyn}J{SHIFT-*}{SHIFT-*}K                                   ";
12073 print" U{SHIFT-*}{SHIFT-*}I                                   ";
12074 print" {SHIFT--}{blk}f3{cyn}{SHIFT--}{blk} pressing this slows you down      ";
12075 print" {cyn}J{SHIFT-*}{SHIFT-*}K                                   ";
12076 print" U{SHIFT-*}{SHIFT-*}I                                   ";
12077 print" {SHIFT--}{blk}f5{cyn}{SHIFT--}{blk} pressing this pauses the game     ";
12078 print"{cyn} J{SHIFT-*}{SHIFT-*}K                                   ";
12079 print" U{SHIFT-*}{SHIFT-*}I                                   ";
12080 print" {SHIFT--}{blk}f7{cyn}{SHIFT--} {blk}pressing this restarts the game   ";
12081 print" {cyn}J{SHIFT-*}{SHIFT-*}K                                   ";
12089 print"{down}{down}        {cyn}hit any key to continue   "
12090 geta$:ifa$=""then12090
12099 goto11000
12100 gosub12400:gosub12200: print"{clr}{blk}{down}{rght}  the aim of this game is to shoot the"
12101 print"  cars with your smoke and guns."
12102 print"  blast the helicopter with your missile";
12103 print"  and last the circuit for bonus points.";
12104 print"{down}{down}{down}{cyn}  scoring:-"
12105 print"{down}             {blk}50  points or"
12106 print"             100 when in turbo"
12107 print"{down}             2000 points"
12110 v=53248:pokev+23,0:pokev+29,0:pokev+39,2:pokev,90:poke2040,13:pokev+1,130
12111 poke2041,15:pokev+2,90:pokev+3,155:pokev+40,15
12112 print"{down}{down}  {cyn}track plan :-"
12113 print"{blk}   the purpose of this is to give an"
12114 print"   indication when to expect the curves.";
12115 print"   the track plan is randomly generated.";
12189 print"{down}{down}        {cyn}hit any key to continue   "
12190 geta$:ifa$=""then12190
12199 return
12200 v=53248:pokev+21,0:forx=0to15:pokev+x,0:next:pokev+21,255
12201 poke53280,0:poke53281,11:poke53285,0:poke53286,2:return
12400 poke54296,0:  pokev+21,0:forx=0to15:pokev+x,0:next:pokev+21,255
12401 print"{clr}{down}{down}{down}{down}{rght}{rght}{rght}{rght}{rght}{yel}welcome 007."
12405 print"     here's your licence to kill."
12410 print"{down}{down}{down}     {red}U{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}I                  ";
12411 print"    {red} {SHIFT--} {cyn} james  bond  {red}{SHIFT--}                  ";
12412 print"    {red} {SHIFT--} {cyn} agent: 007   {red}{SHIFT--}                  ";
12413 print"    {red} {SHIFT--} {cyn} live and let {red}{SHIFT--}                  ";
12414 print"    {red} {SHIFT--} {cyn}     die.     {red}{SHIFT--}                  ";
12415 print" {red}    J{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}{SHIFT-*}K                  ";
12417 print"{down}{down}{rght}{rght}{rght}please wait"
12420 forx=0to7000:next:return
13000 forx=2to15step2:pokev+x,0:next:poke54296,15:pokev+3,0
13001 poke53241,0:poke53242,0:poke53243,0:poke53244,0:x=peek(v)
13002 poke54296,0:poke51199,2:poke51198,2
13010 poke2041,51:pokev+40,1:fory=80tox:pokev,peek(v)-1:next:pokev+2,180
13011 s=54272
13012 fort=0to23:pokes+t,0:next:pokes+14,50:pokes+5,255
13013 pokes+t,143:pokes+4,17:pokes+18,33
13014 fort=0to500:pokes+1,peek(s+27):next:pokes+24,0
13015 forx=0to70:fory=0to10:next:pokev+3,200-x:next
13016 forx=80to180:pokev,x:fory=0to10:next:next
13017 forx=160to140step-1:fory=0to10:next:pokev+1,x:next
13018 forx=0to1000:next
13021 forx=140to160:pokev+1,x:next
13022 forx=180to80step-1:pokev,x:fory=0to10:next:next
13029 forx=0to70:fory=0to10:next:pokev+3,130+x:next
13030 pokev+2,0
13099 return
20000 pokev+21,0:poke54296,0:ifsc>sc(10)then20002
20001 return
20002 ifsc>sc(10)andsc<sc(9)thensc(10)=sc:x=10:goto20050
20003 ifsc>sc(9)andsc<sc(8)thenx=9:goto20100
20004 ifsc>sc(8)andsc<sc(7)thenx=8:goto20100
20005 ifsc>sc(7)andsc<sc(6)thenx=7:goto20100
20006 ifsc>sc(6)andsc<sc(5)thenx=6:goto20100
20007 ifsc>sc(5)andsc<sc(4)thenx=5:goto20100
20008 ifsc>sc(4)andsc<sc(3)thenx=4:goto20100
20009 ifsc>sc(3)andsc<sc(2)thenx=3:goto20100
20010 ifsc>sc(2)andsc<sc(1)thenx=2:goto20100
20011 ifsc>sc(1)thenx=1:goto20100
20049 end
20050 print"{clr}{down}{rght} top 10 agents :enter your code{down}":poke53281,2
20051 forn=1to10:print"{rght}{rght}";sc$(n),,sc(n):next
20055 print"{home}{down}":forn=1tox:print"{down}";:next
20056 geta$:ifa$<>""then20056
20057 poke51199,2:poke51198,2
20058 fort=0to76:sys51000:fory=0to100:next:next:poke54296,0
20060 inputsc$:sc$(x)=left$(sc$,8)
20065 print"{clr}{down}{rght} top 10 agents :enter your code{down}"
20066 forn=1to10:print"{rght}{rght}";sc$(n),,sc(n):next
20070 print"{home}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}{down}       hit any key to continue"
20071 geta$:ifa$=""then20071
20080 return
20100 forn=9toxstep-1:sc(n)=sc(n-1):sc$(n)=sc$(n-1):next:sc$(x)="":sc(x)=sc
20110 goto20050

