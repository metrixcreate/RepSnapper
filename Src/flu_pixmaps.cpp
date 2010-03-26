// $Id: flu_pixmaps.cpp,v 1.10 2003/12/06 16:52:43 jbryan Exp $

/***************************************************************
 *                FLU - FLTK Utility Widgets 
 *  Copyright (C) 2002 Ohio Supercomputer Center, Ohio State University
 *
 * This file and its content is protected by a software license.
 * You should have received a copy of this license with this file.
 * If not, please contact the Ohio Supercomputer Center immediately:
 * Attn: Jason Bryan Re: FLU 1224 Kinnear Rd, Columbus, Ohio 43212
 * 
 ***************************************************************/



#include "flu_pixmaps.h"

/* XPM */
char * plus_xpm[] = {
"15 15 4 1",
"       c None",
".      c #444444",
"+      c #FFFFFF",
"@      c #000000",
"               ",
"               ",
"  ...........  ",
"  .+++++++++.  ",
"  .++++@++++.  ",
"  .++++@++++.  ",
"  .++++@++++.  ",
"  .+@@@@@@@+.  ",
"  .++++@++++.  ",
"  .++++@++++.  ",
"  .++++@++++.  ",
"  .+++++++++.  ",
"  ...........  ",
"               ",
"               "};

/* XPM */
char * minus_xpm[] = {
"15 15 4 1",
"       c None",
".      c #444444",
"+      c #FFFFFF",
"@      c #000000",
"               ",
"               ",
"  ...........  ",
"  .+++++++++.  ",
"  .+++++++++.  ",
"  .+++++++++.  ",
"  .+++++++++.  ",
"  .+@@@@@@@+.  ",
"  .+++++++++.  ",
"  .+++++++++.  ",
"  .+++++++++.  ",
"  .+++++++++.  ",
"  ...........  ",
"               ",
"               "};

/* XPM */
char * folder_save_xpm[] = {
"20 20 180 2",
"  	c None",
". 	c #000000",
"+ 	c #FFFFFF",
"@ 	c #FFF5F6",
"# 	c #FFF6F7",
"$ 	c #FFEBEE",
"% 	c #FFF1F3",
"& 	c #FFA4B5",
"* 	c #FFB3C1",
"= 	c #FFB4C1",
"- 	c #FFB8C5",
"; 	c #FFB9C6",
"> 	c #FFBCC8",
", 	c #FFBDC9",
"' 	c #FFBECA",
") 	c #FFC2CD",
"! 	c #FFC4CE",
"~ 	c #FFC4CF",
"{ 	c #FFC6D0",
"] 	c #FFC8D2",
"^ 	c #FFCED7",
"/ 	c #FFD1D9",
"( 	c #FFD7DE",
"_ 	c #FFDCE2",
": 	c #FFE4E9",
"< 	c #FFE9ED",
"[ 	c #FFEDF0",
"} 	c #FFEEF1",
"| 	c #FFF9FA",
"1 	c #FF9AAD",
"2 	c #FF9FB2",
"3 	c #FFA1B3",
"4 	c #FFA6B7",
"5 	c #FFA7B8",
"6 	c #FFA8B9",
"7 	c #FFABBB",
"8 	c #FFACBC",
"9 	c #FFADBD",
"0 	c #FFAFBE",
"a 	c #FFB1C0",
"b 	c #FFB5C3",
"c 	c #FFB5C4",
"d 	c #FFB7C5",
"e 	c #FFBBC8",
"f 	c #FFBFCB",
"g 	c #FFC1CD",
"h 	c #FFC5D0",
"i 	c #FFC7D2",
"j 	c #FFC8D3",
"k 	c #FFC9D4",
"l 	c #FFCAD4",
"m 	c #FFCCD6",
"n 	c #FFCED8",
"o 	c #FFD2DB",
"p 	c #FFD4DD",
"q 	c #FFD5DD",
"r 	c #FFD7DF",
"s 	c #FFD9E1",
"t 	c #FFDAE1",
"u 	c #FFDBE2",
"v 	c #FFDDE4",
"w 	c #FFE0E6",
"x 	c #FFE1E7",
"y 	c #FFE2E8",
"z 	c #FFE6EB",
"A 	c #FFE7EC",
"B 	c #FFEFF2",
"C 	c #FFCBD6",
"D 	c #FFD0DA",
"E 	c #FFD5DE",
"F 	c #FFDEE5",
"G 	c #FFE8ED",
"H 	c #FFF2F5",
"I 	c #FFEAEF",
"J 	c #C3C2C3",
"K 	c #C1C0C1",
"L 	c #979697",
"M 	c #2106C3",
"N 	c #2207C3",
"O 	c #270CC5",
"P 	c #2B11C6",
"Q 	c #3118C7",
"R 	c #3720C9",
"S 	c #3D26CC",
"T 	c #3D26CB",
"U 	c #3F28CB",
"V 	c #442DCD",
"W 	c #452ECE",
"X 	c #432ECD",
"Y 	c #452FCD",
"Z 	c #4630CD",
"` 	c #4A35CF",
" .	c #4A35CE",
"..	c #4B36CF",
"+.	c #4C37D0",
"@.	c #4C38D0",
"#.	c #4E39D0",
"$.	c #513CD1",
"%.	c #513DD1",
"&.	c #523ED1",
"*.	c #533FD1",
"=.	c #5440D2",
"-.	c #5642D2",
";.	c #5744D2",
">.	c #5845D3",
",.	c #5B48D4",
"'.	c #5A47D3",
").	c #5D4AD4",
"!.	c #5E4CD5",
"~.	c #604ED5",
"{.	c #6150D6",
"].	c #6351D6",
"^.	c #6452D7",
"/.	c #6452D6",
"(.	c #6553D6",
"_.	c #6756D7",
":.	c #6958D8",
"<.	c #6A59D8",
"[.	c #6A5AD8",
"}.	c #6F5EDA",
"|.	c #7667DC",
"1.	c #7566DB",
"2.	c #7B6CDD",
"3.	c #7E70DE",
"4.	c #7F71DE",
"5.	c #877AE1",
"6.	c #887BE0",
"7.	c #6858D8",
"8.	c #6F60DA",
"9.	c #7061DA",
"0.	c #7668DB",
"a.	c #7769DC",
"b.	c #7C6FDE",
"c.	c #8174DF",
"d.	c #8276DF",
"e.	c #8578E0",
"f.	c #897DE1",
"g.	c #8D82E2",
"h.	c #8F84E3",
"i.	c #8E83E2",
"j.	c #9489E4",
"k.	c #958BE5",
"l.	c #9B92E7",
"m.	c #9C93E7",
"n.	c #B1AAED",
"o.	c #A19AE8",
"p.	c #A7A0EA",
"q.	c #ADA6EB",
"r.	c #B2ACED",
"s.	c #7D7D7E",
"t.	c #787979",
"u.	c #B6B7B7",
"v.	c #ACADAD",
"w.	c #8C8D8D",
"x.	c #767776",
"y.	c #8F908F",
"z.	c #B9B9B8",
"A.	c #ADADAC",
"B.	c #6C6B6B",
"C.	c #B7B6B6",
"D.	c #9E9D9D",
"E.	c #C5C5C5",
"F.	c #C2C2C2",
"G.	c #AAAAAA",
"H.	c #A2A2A2",
"I.	c #A0A0A0",
"J.	c #999999",
"K.	c #949494",
"L.	c #919191",
"M.	c #8A8A8A",
"N.	c #888888",
"O.	c #858585",
"P.	c #828282",
"Q.	c #808080",
"R.	c #7B7B7B",
"S.	c #747474",
"T.	c #727272",
"U.	c #6E6E6E",
"V.	c #6C6C6C",
"W.	c #6A6A6A",
"                                        ",
"  . . . . . . . . . . . . . . . . . .   ",
"  . r.. 1 3 5 0 b e g i ^ p u x . F..   ",
"  . r.. 2 T.T.T.T.T.T.T.T.T.T.z . . .   ",
"  . r.. & 7 a d , ! k D ( v : $ . [..   ",
"  . r.. 6 T.T.T.T.T.n q _ y G } . ^..   ",
"  . n.. 9 = ; f { m o s w A [ H . )..   ",
"  . q.. a T.T.~ l T.T.T.T.T.% # . -..   ",
"  . p.. c > g j n E _ y < B @ | . #..   ",
"  . o.m.. . . . . . . . . . . . @.Z .   ",
"  . l.k.h.f.d.b.|.8.[.(.!.>.&...Y U .   ",
"  . j.i.6.c.2.1.}.:./.).;.$.` X S R .   ",
"  . g.5.. . . . . . . . . . . . . Q .   ",
"  . e.4.. E.E._.{.,.C.v.H.J.y.O.. P .   ",
"  . 3.a.. E.E.~.'.=.G.I.L w.P.t.. O .   ",
"  . 0.9.. E.J >.*.+.D.K.M.Q.x.U.. N .   ",
"  . 8.<.. K z.%...W L.N.s.S.V.W.. M .   ",
"  . 7.].. u.A. .V T O.R.T.B.W.W.. M .   ",
"    . . . . . . . . . . . . . . . . .   ",
"                                        "};

/* XPM */
char * folder_load_xpm[] = {
"20 20 42 1",
" 	c None",
".	c #000000",
"+	c #FFF1A5",
"@	c #FFEEA3",
"#	c #FFECA1",
"$	c #FFE99F",
"%	c #FFE79D",
"&	c #FFE49B",
"*	c #FFE299",
"=	c #FFE097",
"-	c #FFDD95",
";	c #FFDB93",
">	c #FFD891",
",	c #FFD68F",
"'	c #FFD48E",
")	c #B59B69",
"!	c #B59E6C",
"~	c #B5A26E",
"{	c #B5A571",
"]	c #B5A974",
"^	c #B5AA75",
"/	c #B59665",
"(	c #B59A68",
"_	c #B59D6B",
":	c #B5A16D",
"<	c #B5A470",
"[	c #B5A773",
"}	c #B59867",
"|	c #B59C69",
"1	c #B59F6C",
"2	c #B5A36F",
"3	c #B5A672",
"4	c #B59766",
"5	c #B59E6B",
"6	c #B5A16E",
"7	c #B5A873",
"8	c #B59967",
"9	c #B59C6A",
"0	c #B5A06D",
"a	c #B5A370",
"b	c #B5A772",
"c	c #B59866",
"                    ",
"           ....     ",
"          .    .  . ",
"         .      ... ",
" ....           ... ",
".+@#$.         .... ",
".@#$%.              ",
".#$%&*........      ",
".$%&*=-;>,'''.      ",
".%&*=-;>,''''.      ",
".&*=-;>.............",
".*=-;>.)!~{]^^^^^^^.",
".=-;>./(_:<[^^^^^^. ",
".-;>.//}|123^^^^^.  ",
".;>.///4(56{7^^^.   ",
".>./////890ab^^.    ",
"..//////c)!~{].     ",
"..............      ",
"                    ",
"                    "};

/* XPM */
char * reload_xpm[] = {
"20 20 41 1",
" 	c None",
".	c #777777",
"+	c #000000",
"@	c #3439AC",
"#	c #1C23A3",
"$	c #080F9A",
"%	c #5257B8",
"&	c #3A40AF",
"*	c #2329A5",
"=	c #0C139C",
"-	c #585DBB",
";	c #4146B1",
">	c #2A30A8",
",	c #5F63BE",
"'	c #484DB4",
")	c #3036AB",
"!	c #666AC0",
"~	c #4E53B7",
"{	c #373DAD",
"]	c #555ABA",
"^	c #3E43B0",
"/	c #262DA7",
"(	c #5C60BC",
"_	c #444AB3",
":	c #2D33A9",
"<	c #5E5E5E",
"[	c #4B50B6",
"}	c #676767",
"|	c #646464",
"1	c #6D6D6D",
"2	c #767676",
"3	c #12199F",
"4	c #616161",
"5	c #6A6A6A",
"6	c #737373",
"7	c #7C7C7C",
"8	c #1920A1",
"9	c #707070",
"0	c #797979",
"a	c #808080",
"b	c #838383",
"        .++++++.    ",
"      .++@#$$$$++.  ",
"     .+%&*=++++$$+. ",
"    .+-;>++.  .++$+.",
"   .+,')+.      .+++",
"   +!~{+.         .+",
"  .+]^/+      .+.   ",
"  +(_:+.     .+<+.  ",
" .+[@#+     .+<<}+. ",
"++%&*=$++  .+<<|12+.",
".+;>3$$+.  ++<4567++",
" .+8$$+.     +}90+. ",
"  .+$+.     .+12a+  ",
"   .+.      +567+.  ",
"+.         .+90b+   ",
"+++.      .+12a+.   ",
".+<++.  .++567+.    ",
" .+<<++++<}90+.     ",
"  .++<<<<|1++.      ",
"    .++++++.        "};

/* XPM */
char * home_xpm[] = {
"20 20 46 1",
" 	c None",
".	c #000000",
"+	c #1C2F54",
"@	c #4162AD",
"#	c #872525",
"$	c #894226",
"%	c #875B25",
"&	c #DDDA30",
"*	c #4665B0",
"=	c #6279BF",
"-	c #4A68B2",
";	c #697EC3",
">	c #4363AE",
",	c #4C69B3",
"'	c #556FB8",
")	c #5D76BC",
"!	c #667CC1",
"~	c #6E81C6",
"{	c #7687CA",
"]	c #7989CC",
"^	c #4C6AB3",
"/	c #5570B8",
"(	c #5E76BD",
"_	c #677DC2",
":	c #7083C7",
"<	c #828FD0",
"[	c #F43333",
"}	c #ED3030",
"|	c #E62E2E",
"1	c #3E60AB",
"2	c #E02C2C",
"3	c #D92A2A",
"4	c #3A5DA9",
"5	c #5A73BB",
"6	c #D22828",
"7	c #CC2626",
"8	c #3559A6",
"9	c #526EB6",
"0	c #C52424",
"a	c #BF2222",
"b	c #3055A3",
"c	c #365AA7",
"d	c #3C5EAA",
"e	c #4262AD",
"f	c #B82020",
"g	c #B11D1D",
"                    ",
"        .           ",
"       .+. ....     ",
"      .+@+..#$.     ",
"     .%%%%%.$#.     ",
"    .%&&%&&%.$.     ",
"   .+%&&%&&%+..     ",
"  .+*%&&%&&%=+. .   ",
" .+@-%%%%%%%;=+.+.  ",
". .>,')!~{]{~!.+,+. ",
"  .>^/(_:]<]:.+/^>+.",
"  .>%%%%~{]{~%%%%>. ",
"  .@%&&%;[}|;%&&%@. ",
"  .1%&&%=|23=%&&%1. ",
"  .4%&&%53675%&&%4. ",
"  .8%%%%970a9%%%%8. ",
"  .bcde*-afg-*edcb. ",
"  ................. ",
"                    ",
"                    "};

/* XPM */
char * trash_xpm[] = {
"20 20 8 1",
" 	c None",
".	c #000000",
"+	c #B7B7B7",
"@	c #D3D3D3",
"#	c #3F3F3F",
"$	c #8E8E8E",
"%	c #FFFFFF",
"&	c #666666",
"                    ",
"      ........      ",
"    ..+@####+$..    ",
"  ..$@%#@@@@#@+$..  ",
"  .#+@%%%@@@@@+$#.  ",
"  .+###%%%%@@###&.  ",
"   .+@%######+$&.   ",
"   .###@@@@$+###.   ",
"   .+@%######$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"   .+@%+@@$++$&&.   ",
"    ..%+@@$++$..    ",
"      ........      "};

/* XPM */
char * arrow_closed_xpm[] = {
"15 15 3 1",
" 	c None",
".	c #FFFFFF",
"+	c #000000",
"               ",
"               ",
"               ",
"   ++          ",
"   ++++        ",
"   ++++++      ",
"   ++++++++    ",
"   +++++++++   ",
"   ++++++++    ",
"   ++++++      ",
"   ++++        ",
"   ++          ",
"               ",
"               ",
"               "};

/* XPM */
char * arrow_open_xpm[] = {
"15 15 3 1",
" 	c None",
".	c #FFFFFF",
"+	c #000000",
"               ",
"               ",
"               ",
"   +++++++++   ",
"   +++++++++   ",
"    +++++++    ",
"    +++++++    ",
"     +++++     ",
"     +++++     ",
"      +++      ",
"      +++      ",
"       +       ",
"               ",
"               ",
"               "};

/* XPM */
char * bluedot_xpm[] = {
"13 13 9 1",
" 	c None",
".	c #D4D4FF",
"+	c #6363FF",
"@	c #1A1AFF",
"#	c #0000FF",
"$	c #A8A8FF",
"%	c #6060FF",
"&	c #EAEAFF",
"*	c #FFFFFF",
"             ",
"   .+@#@+.   ",
"  $#######$  ",
" .#%&&%####. ",
" +#&**&####+ ",
" @#&**&####@ ",
" ##%&&%##### ",
" @#########@ ",
" +#########+ ",
" .#########. ",
"  $#######$  ",
"   .+@#@+.   ",
"             "};

/* XPM */
char * book_xpm[] = {
"18 18 15 1",
" 	c None",
".	c #840084",
"+	c #000000",
"@	c #FF9CFF",
"#	c #CE00CE",
"$	c #630063",
"%	c #9C009C",
"&	c #636363",
"*	c #9C9C9C",
"=	c #848484",
"-	c #C6C6C6",
";	c #ADAD94",
">	c #E7E7D6",
",	c #D60094",
"'	c #CE63CE",
"                  ",
"        .+        ",
"       .@#$+      ",
"      .@###%$+    ",
"     .@#####..$+  ",
"    .@#######..++ ",
"   .@########.+.  ",
"  .@########.+&.  ",
" .@########%+&*.+ ",
" ...######%+&*=.+ ",
" .*-..###%+&*;.+  ",
" .*>-;..%+=*-.+   ",
" .,'>>--.*;-.+    ",
"  $$,'>>>--.+     ",
"    $$,'>-.+      ",
"      $$,.+       ",
"        $+        ",
"                  "};

/* XPM */
char * cd_drive_xpm[] = {
"18 16 29 1",
" 	c None",
".	c #737373",
"+	c #9CCE9C",
"@	c #CECE63",
"#	c #C6C6C6",
"$	c #319C9C",
"%	c #63CE9C",
"&	c #B5B5B5",
"*	c #313131",
"=	c #CECE9C",
"-	c #DEDEDE",
";	c #848484",
">	c #319CCE",
",	c #639CCE",
"'	c #63CECE",
")	c #D6D6D6",
"!	c #949494",
"~	c #A5A5A5",
"{	c #639C9C",
"]	c #000000",
"^	c #CECECE",
"/	c #F7F7F7",
"(	c #E7E7E7",
"_	c #EFEFEF",
":	c #FFFFFF",
"<	c #CEFFFF",
"[	c #009CCE",
"}	c #00FF00",
"|	c #008400",
"         ...      ",
"       ..+@#..    ",
"      .$%+@&##*   ",
"     .%%$%=#&-&*  ",
"     ;>,%';&)#&*  ",
"    .!~{';];~&^^* ",
"    .&&^;]/];^^^* ",
"    .(/(&;];&_/^* ",
"  ;;;;~&~~;$-(:*  ",
" ;:::.~~&)=%><&*  ",
" ;:###.~&^=+[[]   ",
" ;:****;;^=+**]   ",
" ;:}|::##***#.]   ",
" .;;;;;;;;;;;;]   ",
"  ]]]]]]]]]]]]    ",
"                  "};

/* XPM */
char * computer_xpm[] = {
"20 20 47 1",
" 	c None",
".	c #FFFFFF",
"+	c #848484",
"@	c #9C9CCE",
"#	c #9C9C63",
"$	c #63639C",
"%	c #393939",
"&	c #FFFFCE",
"*	c #FFFFF7",
"=	c #CECEFF",
"-	c #424242",
";	c #F7F7F7",
">	c #6363CE",
",	c #000031",
"'	c #003163",
")	c #CEEFFF",
"!	c #4A4A4A",
"~	c #9CCEFF",
"{	c #63FFFF",
"]	c #9CFFFF",
"^	c #63CEFF",
"/	c #319CFF",
"(	c #0063FF",
"_	c #B5B5B5",
":	c #31CEFF",
"<	c #3163CE",
"[	c #639CCE",
"}	c #CEFFFF",
"|	c #009CFF",
"1	c #313100",
"2	c #292929",
"3	c #ADAD94",
"4	c #DEDEDE",
"5	c #101010",
"6	c #CE9C9C",
"7	c #080808",
"8	c #000000",
"9	c #EFD6C6",
"0	c #CE9CCE",
"a	c #636363",
"b	c #633131",
"c	c #636331",
"d	c #848400",
"e	c #C6C6C6",
"f	c #EFEFEF",
"g	c #E7E7D6",
"h	c #212121",
"                    ",
"                    ",
"   +@@@@@@@@@@#$    ",
"  %&...&&&&&**.=-   ",
"  %=;&@>,,,,,,')!   ",
"  %~=;>{]]]^^/({-   ",
"  %_=*>]]]{]::<]-   ",
"  %=_*[{]]{{::<}-   ",
"  %__.[^]{{^^|<.-   ",
"  %_=./:::::/|(.-   ",
"  11_&^<<<<<<<<.2   ",
"   113=4&&&&&&4@5   ",
"  167888888888752   ",
"  1%90ab%c33b5%a    ",
"  1$de9=9f=&3g3=3a  ",
"  1$$%=9=ggg=@dd=h  ",
"   1$h9=9=&=&=9=9h  ",
"    chhhhhhhhhhhhh  ",
"                    ",
"                    "};

/* XPM */
char * ram_drive_xpm[] = {
"18 16 14 1",
" 	c None",
".	c #444444",
"+	c #2D2D2D",
"@	c #000000",
"#	c #FFFFFF",
"$	c #737373",
"%	c #B5B5B5",
"&	c #1C1C1C",
"*	c #DEDEDE",
"=	c #C6C6C6",
"-	c #949494",
";	c #D6D6D6",
">	c #00CE00",
",	c #008400",
"                  ",
"         .+++++   ",
"      @  +....@  @",
"       @@+.#..@@@ ",
"      @  +..#.@  @",
"       @@+....@@@ ",
"      @  +.##.@  @",
"   $$$$@@+....@@@ ",
"  $%%%@%%+.#..@& @",
" $#####@@+....@@@ ",
" $*%====%@@@@@@&  ",
" $*$$$$$$$$$%-$&  ",
" $;>,#######%-$&  ",
" $$$$$$$$$$$$$&   ",
"  &&&&&&&&&&&&    ",
"                  "};

/* XPM */
char * network_drive_xpm[] = {
"18 16 15 1",
" 	c None",
".	c #A80525",
"+	c #42000E",
"@	c #1A29A8",
"#	c #737373",
"$	c #B5B5B5",
"%	c #000000",
"&	c #FFFFFF",
"*	c #9C9C9C",
"=	c #DEDEDE",
"-	c #C6C6C6",
";	c #949494",
">	c #D6D6D6",
",	c #00CE00",
"'	c #008400",
"                  ",
" ..  ..   ..  ..  ",
" ..+ ..+  ..+ ..+ ",
" ..+ ..+  ..+ ..+ ",
"  @+  @+   @+  @+ ",
"  @@@@@@@@@@@@@@  ",
"        @         ",
"   ############   ",
"  #$$$$$$$$$$$#%  ",
" #&&&&&&&&&&&*#%  ",
" #=$----$$$$$;#%  ",
" #=#########$;#%  ",
" #>,'&&&&&&&$;#%  ",
" #############%   ",
"  %%%%%%%%%%%%    ",
"                  "};

/* XPM */
char * floppy_drive_xpm[] = {
"18 16 12 1",
" 	c None",
".	c #858585",
"+	c #737373",
"@	c #9CFFFF",
"#	c #000000",
"$	c #FFFFFF",
"%	c #CEFDFD",
"&	c #CECECE",
"*	c #C5C5C5",
"=	c #B5B5B5",
"-	c #F40000",
";	c #808080",
"                  ",
"          ......  ",
"         +@@@@@@# ",
"         +$$$$$## ",
"         +$$$%%%# ",
"         +%%%%%%# ",
"         +&*&=*=# ",
"   ......+*....*# ",
"  .******+&+#+$=# ",
" .$$$$$$$$######  ",
" .*********-*.+#  ",
" .***....&***.+#  ",
" ;*;.####;.;*;+#  ",
" .***$$$$****.+#  ",
" ..;...;...;..#   ",
"  ############    "};

/* XPM */
char * removable_drive_xpm[] = {
"20 12 12 1",
" 	c None",
".	c #858585",
"+	c #B5B5B5",
"@	c #626262",
"#	c #000000",
"$	c #FFFFFF",
"%	c #808080",
"&	c #E7E7D6",
"*	c #C5C5C5",
"=	c #F40000",
"-	c #7B0006",
";	c #CECECE",
"                    ",
"    .............   ",
"   .++++++++++++@#  ",
"  .$$$$$$$$$$$$.@#  ",
"  %$+&*+*+*+*+*.@#  ",
" %.$=-@######@*.@#  ",
"  .$&+$######$*.@#  ",
"  .$+&+$$$$$$*;.@#  ",
"  %$&+***++++++.@#  ",
"  .$............#   ",
"   #############    ",
"                    "};

/* XPM */
char * disk_drive_xpm[] = {
"20 12 12 1",
" 	c None",
".	c #737373",
"+	c #B5B5B5",
"@	c #000000",
"#	c #FFFFFF",
"$	c #9C9C9C",
"%	c #D6D6D6",
"&	c #C6C6C6",
"*	c #949494",
"=	c #DEDEDE",
"-	c #00CE00",
";	c #008400",
"                    ",
"                    ",
"    .............   ",
"   .++++++++++++.@  ",
"  .############$.@  ",
"  .%&&&&&&&++++*.@  ",
"  .=+&&&&&+++++*.@  ",
"  .=..........+*.@  ",
"  .%-;########+*.@  ",
"  ..............@   ",
"   @@@@@@@@@@@@@    ",
"                    "};

/* XPM */
char * filled_folder_xpm[] = {
"18 18 18 1",
" 	c None",
".	c #63639C",
"+	c #CEFFFF",
"@	c #000000",
"#	c #848400",
"$	c #FFFFFF",
"%	c #CECEFF",
"&	c #CECE63",
"*	c #319CFF",
"=	c #0063FF",
"-	c #9CFFFF",
";	c #9C9C00",
">	c #3131CE",
",	c #313100",
"'	c #31009C",
")	c #9C9CFF",
"!	c #FFFF9C",
"~	c #FFCE9C",
"                  ",
"         .        ",
"        .+@       ",
"    ###.+$%@      ",
"   #&&.+$*+%@     ",
"  #&&.+$=-$+%@;;  ",
"  #&.+$>-$>$+%@&, ",
"  #.+%')%')%%%%@, ",
" ;;;;;;;;;;;;)+%@ ",
" ;$!!!!!!~!~&,%%@ ",
" ;$!!!!~!!~!&,)@, ",
"  ;$!!!!!~!~~;,;, ",
"  ;$!!~!~!~~~&,;, ",
"   ;$~!~!~~~~&;,, ",
"   ;;;;;;;;;;;;,, ",
"    ,,,,,,,,,,,,, ",
"                  ",
"                  "};

/* XPM */
char * folder_up_xpm[] = {
"20 18 8 1",
" 	c None",
".	c #9C9C00",
"+	c #000000",
"@	c #F7F7F7",
"#	c #FFFFCE",
"$	c #FFFF9C",
"%	c #CECE63",
"&	c #FFCE9C",
"                    ",
"                    ",
"                    ",
"     .....+         ",
"    .@##$$.+        ",
"   .%%%%%%%......   ",
"   .###########$%+  ",
"   .#$$$+$$$$$$&%+  ",
"   .#$$+++$$&$&$%+  ",
"   .#$+++++$$&$&%+  ",
"   .#$$$+$&$&$&$%+  ",
"   .#$$$+$$&$&$&%+  ",
"   .#$$$++++++&&%+  ",
"   .#&$&$&$&$&&&%+  ",
"   .%%%%%%%%%%%%%+  ",
"    ++++++++++++++  ",
"                    ",
"                    "};

/* XPM */
char * folder_closed_xpm[] = {
"20 16 44 1",
" 	c None",
".	c #A68A5E",
"+	c #54452F",
"@	c #FEE89E",
"#	c #FEE59B",
"$	c #FEE298",
"%	c #FEDE95",
"&	c #FEDB93",
"*	c #CEAB75",
"=	c #FEF6A9",
"-	c #FEF2A7",
";	c #FEEFA4",
">	c #FEECA1",
",	c #FEE99E",
"'	c #FEE69C",
")	c #FEE399",
"!	c #FEDF96",
"~	c #FEDC93",
"{	c #FED991",
"]	c #FED68E",
"^	c #FEF3A7",
"/	c #FEF0A4",
"(	c #FEEDA2",
"_	c #FEE99F",
":	c #FEE097",
"<	c #FEDD94",
"[	c #FEDA91",
"}	c #FED78E",
"|	c #FEF0A5",
"1	c #FEEA9F",
"2	c #FEE79D",
"3	c #FEE49A",
"4	c #FEE197",
"5	c #FEDA92",
"6	c #FED78F",
"7	c #FEEEA3",
"8	c #FEEAA0",
"9	c #FEE198",
"0	c #FEDB92",
"a	c #FED88F",
"b	c #FEEBA0",
"c	c #FED890",
"d	c #FEE299",
"e	c #FED990",
"                    ",
"          .....+    ",
"         .@#$%&.+   ",
"   ......*******.   ",
"   .=-;>,')!~{]].+  ",
"   .^/(_'):<[}]].+  ",
"   .|(1234<56]]].+  ",
"   .78239%0a]]]].+  ",
"   .b@#$%&c]]]]].+  ",
"   .@#d!~e]]]]]].+  ",
"   .')!~{]]]]]]].+  ",
"   .):<[}]]]]]]].+  ",
"   ..............+  ",
"    ++++++++++++++  ",
"                    ",
"                    "};
/*
"20 16 29 1",
" 	c None",
".	c #9E9E02",
"+	c #222202",
"@	c #FEFECE",
"#	c #FEF2C2",
"$	c #FEEABA",
"%	c #FEDEAE",
"&	c #FEDAA6",
"*	c #CECE62",
"=	c #FEFECA",
"-	c #FEFACA",
";	c #FEF6C6",
">	c #FEEEBA",
",	c #FEE6B6",
"'	c #FEE2B2",
")	c #FEDAAA",
"!	c #FEEEBE",
"~	c #FEEAB6",
"{	c #FEE6B2",
"]	c #FEE2AE",
"^	c #FEDEAA",
"/	c #FEFAC6",
"(	c #FEF6C2",
"_	c #FEF2BE",
":	c #FED6A2",
"<	c #FED6A6",
"[	c #FED2A2",
"}	c #FED29E",
"|	c #FECE9E",
"                    ",
"     .....+         ",
"    .@#$%&.+        ",
"   .*******......   ",
"   .@@=-;#>$,'%)*+  ",
"   .@@-;#!!~{]^)*+  ",
"   .@-/(_>$,']^)*+  ",
"   .@-;#!$,{')&:*+  ",
"   .@/(#!~,]])<:*+  ",
"   ./;#!$,'')&<[*+  ",
"   .;#_>${]%)<}}*+  ",
"   .##!${'%^<:[|*+  ",
"   .*************+  ",
"    ++++++++++++++  ",
"                    ",
"                    "};
*/

char * folder_open_xpm[] = {
"20 16 34 1",
" 	c None",
".	c #A68A5E",
"+	c #FEF3A7",
"@	c #FEECA1",
"#	c #FEE49A",
"$	c #FEDD94",
"%	c #FED68E",
"&	c #FEF6A9",
"*	c #FEEEA3",
"=	c #FEE79D",
"-	c #FEDF96",
";	c #FED890",
">	c #FEF1A5",
",	c #FEE99F",
"'	c #FEE298",
")	c #FEDA92",
"!	c #FEF0A5",
"~	c #FEEBA1",
"{	c #FEE69C",
"]	c #FEE198",
"^	c #FEDC93",
"/	c #FED78F",
"(	c #54452F",
"_	c #FEF2A6",
":	c #FEEDA2",
"<	c #FEE299",
"[	c #FEE99E",
"}	c #FEDE95",
"|	c #FED991",
"1	c #FEEFA4",
"2	c #FEEA9F",
"3	c #FEE59B",
"4	c #FEE096",
"5	c #FEDB92",
"                    ",
"          .....     ",
"         .+@#$%.    ",
"   ......&*=-;%%.   ",
"   .&&&&&>,')%%%.   ",
"   .&&&&+@#$%%%%.   ",
"   .&&............  ",
"   .&&.&!~{]^/%%%.( ",
"   .&&._:=<$;%%%%.( ",
"   .&.+*[#}|%%%%.(  ",
"   .&.12345%%%%%.(  ",
"    .!~{]^/%%%%.(   ",
"    ............(   ",
"    ((((((((((((    ",
"                    ",
"                    "};

/*
"20 16 41 1",
" 	c None",
".	c #9E9E02",
"+	c #FEFECE",
"@	c #FEFACA",
"#	c #F6F2C4",
"$	c #F2EABE",
"%	c #EEE6B9",
"&	c #FAF6C6",
"*	c #F2EEBE",
"=	c #EADEB2",
"-	c #E2D6AA",
";	c #EAE2B6",
">	c #E6DAAE",
",	c #E2D2AA",
"'	c #DAC69E",
")	c #D2C296",
"!	c #CEBA92",
"~	c #CAB28A",
"{	c #C2AA82",
"]	c #CECE62",
"^	c #222202",
"/	c #FEFECA",
"(	c #D6C69A",
"_	c #C2A67E",
":	c #FEF2BE",
"<	c #FEEABA",
"[	c #FEE6B6",
"}	c #FEE2B2",
"|	c #FEDEAE",
"1	c #FEDAAA",
"2	c #BA9E7A",
"3	c #FEF6C6",
"4	c #FEF2C2",
"5	c #FEEEBA",
"6	c #FEEAB6",
"7	c #FEDEAA",
"8	c #FED6A4",
"9	c #FEEEBE",
"0	c #FED2A2",
"a	c #FEF6C2",
"b	c #FECE9E",
"                    ",
"     .....          ",
"    .+@#$%.         ",
"   .++&*%=-......   ",
"   .+@#$;>,')!~{]^  ",
"   ./&*%=>,()!~{]^  ",
"  ............{_]^  ",
"  .++@&:<[}|1]^2]^  ",
"  .++@3456}|1]^2]^  ",
"   ./@4:<[}718.^.^  ",
"   .@349<[}1800^.^  ",
"    .a:96}|180b.^^  ",
"    ............^^  ",
"     ^^^^^^^^^^^^^  ",
"                    ",
"                    "};
*/

/* XPM */
char * greendot_xpm[] = {
"13 13 9 1",
" 	c None",
".	c #D4FFD4",
"+	c #63FF63",
"@	c #1AFF1A",
"#	c #00FF00",
"$	c #A8FFA8",
"%	c #60FF60",
"&	c #EAFFEA",
"*	c #FFFFFF",
"             ",
"   .+@#@+.   ",
"  $#######$  ",
" .#%&&%####. ",
" +#&**&####+ ",
" @#&**&####@ ",
" ##%&&%##### ",
" @#########@ ",
" +#########+ ",
" .#########. ",
"  $#######$  ",
"   .+@#@+.   ",
"             "};

/* XPM */
char * purpledot_xpm[] = {
"13 13 9 1",
" 	c None",
".	c #FFD4FF",
"+	c #FF63FF",
"@	c #FF1AFF",
"#	c #FF00FF",
"$	c #FFA8FF",
"%	c #FF60FF",
"&	c #FFEAFF",
"*	c #FFFFFF",
"             ",
"   .+@#@+.   ",
"  $#######$  ",
" .#%&&%####. ",
" +#&**&####+ ",
" @#&**&####@ ",
" ##%&&%##### ",
" @#########@ ",
" +#########+ ",
" .#########. ",
"  $#######$  ",
"   .+@#@+.   ",
"             "};
/* XPM */
char * question_book_xpm[] = {
"18 18 19 1",
" 	c None",
".	c #840084",
"+	c #000000",
"@	c #FF9CFF",
"#	c #CE00CE",
"$	c #630063",
"%	c #9C009C",
"&	c #9C6331",
"*	c #FFFF00",
"=	c #CE9C31",
"-	c #FFCE31",
";	c #636363",
">	c #9C9C9C",
",	c #848484",
"'	c #C6C6C6",
")	c #ADAD94",
"!	c #E7E7D6",
"~	c #D60094",
"{	c #CE63CE",
"                  ",
"        .+        ",
"       .@#$+      ",
"      .@###%$+    ",
"     .@##&&$..$+  ",
"    .@##***=$..++ ",
"   .@#####-*$.+.  ",
"  .@####**-&.+;.  ",
" .@###*-&%.%+;>.+ ",
" ...##%%##%+;>,.+ ",
" .>'..###%+;>).+  ",
" .>!')..%+,>'.+   ",
" .~{!!''.>)'.+    ",
"  $$~{!!!''.+     ",
"    $$~{!'.+      ",
"      $$~.+       ",
"        $+        ",
"                  "};
/* XPM */
char * reddot_xpm[] = {
"13 13 9 1",
" 	c None",
".	c #FFD4D4",
"+	c #FF6363",
"@	c #FF1A1A",
"#	c #FF0000",
"$	c #FFA8A8",
"%	c #FF6060",
"&	c #FFEAEA",
"*	c #FFFFFF",
"             ",
"   .+@#@+.   ",
"  $#######$  ",
" .#%&&%####. ",
" +#&**&####+ ",
" @#&**&####@ ",
" ##%&&%##### ",
" @#########@ ",
" +#########+ ",
" .#########. ",
"  $#######$  ",
"   .+@#@+.   ",
"             "};
/* XPM */
char * tealdot_xpm[] = {
"13 13 9 1",
" 	c None",
".	c #D4FFFF",
"+	c #63FFFF",
"@	c #1AFFFF",
"#	c #00FFFF",
"$	c #A8FFFF",
"%	c #60FFFF",
"&	c #EAFFFF",
"*	c #FFFFFF",
"             ",
"   .+@#@+.   ",
"  $#######$  ",
" .#%&&%####. ",
" +#&**&####+ ",
" @#&**&####@ ",
" ##%&&%##### ",
" @#########@ ",
" +#########+ ",
" .#########. ",
"  $#######$  ",
"   .+@#@+.   ",
"             "};
/* XPM */
char * textdoc_xpm[] = {
"15 18 5 1",
" 	c None",
".	c #848484",
"+	c #FFFFFF",
"@	c #C6C6C6",
"#	c #000000",
"               ",
" ..........    ",
" .++++++++@.   ",
" .+@......@+.  ",
" .++++++++...# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .+@.......+@# ",
" .++++++++++@# ",
" .@@@@@@@@@@@# ",
"  ############ ",
"               "};

/* XPM */
char * yellowdot_xpm[] = {
"13 13 9 1",
" 	c None",
".	c #FFFFD4",
"+	c #FFFF63",
"@	c #FFFF1A",
"#	c #FFFF00",
"$	c #FFFFA8",
"%	c #FFFF60",
"&	c #FFFFEA",
"*	c #FFFFFF",
"             ",
"   .+@#@+.   ",
"  $#######$  ",
" .#%&&%####. ",
" +#&**&####+ ",
" @#&**&####@ ",
" ##%&&%##### ",
" @#########@ ",
" +#########+ ",
" .#########. ",
"  $#######$  ",
"   .+@#@+.   ",
"             "};

/* XPM */
char * cdrom_xpm[] = {
"22 22 39 1",
"       c None",
".      c #ADADAD",
"+      c #C67BA5",
"@      c #DEDEDE",
"#      c #E7E7E7",
"$      c #E6E6E6",
"%      c #7B9CBD",
"&      c #CE8CAD",
"*      c #DE8CAD",
"=      c #FFFFFF",
"-      c #6BB58C",
";      c #7BCEBD",
">      c #8CA5D6",
",      c #DE9CC6",
"'      c #8CD67B",
")      c #8CDEB5",
"!      c #7BB5D6",
"~      c #9C9CDE",
"{      c #DE94B5",
"]      c #FFB1FF",
"^      c #C0C0C0",
"/      c #9CBD63",
"(      c #ADD67B",
"_      c #94DEC6",
":      c #CEAD73",
"<      c #D6C67B",
"[      c #BDD67B",
"}      c #94C67B",
"|      c #94B5D6",
"1      c #C6A584",
"2      c #DEBD8C",
"3      c #DECE94",
"4      c #9CCE84",
"5      c #7B7B7B",
"6      c #FFD48E",
"7      c #DEDEEF",
"8      c #FFEFEF",
"9      c #6BA5BD",
"0      c #C6849C",
"                      ",
"        ......        ",
"      ..+@#$#$..      ",
"    ..%&*$$$$===..    ",
"   .-;>,*$$$$===$..   ",
"   .')!~{]$$$==$=^.   ",
"  ./('_%,]$$==$=^$$.  ",
"  .:<[}_|]#@=$=^$$$.  ",
" .122234_.55.=^$$$$$. ",
" .$$$666.5555.$$$$$$. ",
" .$$$$$#55  55@$$$$$. ",
" .$$$$$$55  557$$$$$. ",
" .#$$$$$.5555.66688#. ",
" .$$$$$^=$55._}32<21. ",
"  .$$$^=$=$#]|_}(<:.  ",
"  .$$^=$==$$],%_44/.  ",
"   .^=$===$$]{~!)'.   ",
"   ..$===$$$8*,>;-.   ",
"    ..===$$$8*&9..    ",
"      ..=$@@#0..      ",
"        ......        ",
"                      "};

/* XPM */
char * big_folder_new_xpm[] = {
"20 20 73 1",
" 	c None",
".	c #000000",
"+	c #FFFFFF",
"@	c #444444",
"#	c #474747",
"$	c #353535",
"%	c #CEC765",
"&	c #FFF373",
"*	c #FFEF77",
"=	c #FFEC78",
"-	c #FFE87C",
";	c #C8B46E",
">	c #3C3C3C",
",	c #C0B666",
"'	c #FFE97A",
")	c #FFE67D",
"!	c #FFE182",
"~	c #FFE082",
"{	c #FFDE83",
"]	c #FAD982",
"^	c #C1AA70",
"/	c #BFA872",
"(	c #FFEFA4",
"_	c #FFDB87",
":	c #FFD88A",
"<	c #FFD68B",
"[	c #FFD48E",
"}	c #FFD48D",
"|	c #FFD48C",
"1	c #FFD58B",
"2	c #EFC885",
"3	c #FFEEA3",
"4	c #FFECA1",
"5	c #C8BB86",
"6	c #FFE89F",
"7	c #FFE69D",
"8	c #FFE49B",
"9	c #FFE39A",
"0	c #FFE29A",
"a	c #FFE199",
"b	c #FFE098",
"c	c #FFDF97",
"d	c #FFDE96",
"e	c #FFDD95",
"f	c #FFDC94",
"g	c #FFECA2",
"h	c #FFEBA1",
"i	c #FFE79E",
"j	c #FFE299",
"k	c #FFDC95",
"l	c #FFDB94",
"m	c #FFEBA0",
"n	c #FFE89E",
"o	c #FFE79D",
"p	c #FFE097",
"q	c #FFD992",
"r	c #FFE99E",
"s	c #FFE69C",
"t	c #FFE59B",
"u	c #FFDA93",
"v	c #FFD690",
"w	c #FFD790",
"x	c #FFD791",
"y	c #FFD891",
"z	c #FFD58E",
"A	c #FFD58F",
"B	c #FFD68F",
"C	c #FFE198",
"D	c #FFDF96",
"E	c #FFDE95",
"F	c #FFDB93",
"G	c #FFD991",
"H	c #FFDA92",
"                    ",
" .+ .  .+   @#####  ",
"  .+. .+   $%&*=-;> ",
" ##...+####,')!~{]^#",
"#...+.../(#_:<[}|12#",
"#++...++345#########",
"#/.+.+.+677890abcde#",
"#.+/.+/.+aabccddeff#",
"#(gh6i8jbddeekkflll#",
"#mno89pelqqqqqqqqqq#",
"#rstjbeuqvvvvwxxyyy#",
"#8jbdeuxv[[[zABBvww#",
"#CDEfFGwB[[[[zAABBB#",
"#cekuuyvA[[[[zAABBB#",
"#FHqyyvAz[[[[[zzzzz#",
"#qyywwBA[[[[[[[[[[[#",
"#zzzzz[[[[[[[[[[[[[#",
" ################## ",
"                    ",
"                    "};

/* XPM */
char * big_folder_up_xpm[] = {
"20 20 70 1",
" 	c None",
".	c #474747",
"+	c #434343",
"@	c #3B3B3B",
"#	c #B9B260",
"$	c #FFF373",
"%	c #FFEF77",
"&	c #FFEC78",
"*	c #FFE87C",
"=	c #C8B46E",
"-	c #3C3C3C",
";	c #C2B667",
">	c #FFE97B",
",	c #FFE67D",
"'	c #FFE182",
")	c #FFE082",
"!	c #FFDE83",
"~	c #FFDD84",
"{	c #D1B775",
"]	c #FFF6AA",
"^	c #FFE79E",
"/	c #FFF1A5",
"(	c #FFEFA4",
"_	c #484848",
":	c #F7D584",
"<	c #FFD88A",
"[	c #FFD68B",
"}	c #FFD48E",
"|	c #FFD48D",
"1	c #FFD48C",
"2	c #FFD58B",
"3	c #FFEEA3",
"4	c #FFECA1",
"5	c #BEB280",
"6	c #BFA872",
"7	c #000000",
"8	c #FFE89F",
"9	c #FFE69D",
"0	c #FFE49B",
"a	c #FFE39A",
"b	c #FFE29A",
"c	c #FFE199",
"d	c #FFE098",
"e	c #FFDF97",
"f	c #FFDE96",
"g	c #FFDD95",
"h	c #FFDC94",
"i	c #FFECA2",
"j	c #FFDC95",
"k	c #FFDB94",
"l	c #FFEBA0",
"m	c #FFE89E",
"n	c #FFD992",
"o	c #FFE99E",
"p	c #FFE69C",
"q	c #FFE59B",
"r	c #FFE299",
"s	c #FFDA93",
"t	c #FFD690",
"u	c #FFD790",
"v	c #FFD791",
"w	c #FFD891",
"x	c #FFD58E",
"y	c #FFD58F",
"z	c #FFD68F",
"A	c #FFE198",
"B	c #FFDF96",
"C	c #FFDE95",
"D	c #FFDB93",
"E	c #FFDA92",
"                    ",
"            .....+  ",
"           @#$%&*=- ",
" ..........;>,')!~{.",
".]]^^////(_:<[}|122.",
".]]^^^33345.........",
".](3^6768990abcdefg.",
".((367776ccdeeffghh.",
".(i6777776fggjjhkkk.",
".lm7777777nnnnnnnnn.",
".opqr67snttttuvvwww.",
".0rdf67vt}}}xyzztuu.",
".ABCh67666666666zzz.",
".egjs67777777777zzz.",
".DEnwwtyx}}}}}xxxxx.",
".nwwuuzy}}}}}}}}}}}.",
".xxxxx}}}}}}}}}}}}}.",
" .................. ",
"                    ",
"                    "};
