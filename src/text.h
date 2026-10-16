// Made by tools/bas2c.py from 007.bas and build/timing.txt: don't edit
#ifndef TEXT_H
#define TEXT_H

// What a row line does before its PRINT, in this order
#define OP_TUNE		1	// sys51000
#define OP_FRAME	2	// sys49155
#define OP_TURBO	4	// sys49152
#define OP_WEAPON	8	// sys49561
#define OP_NEWLINE	16	// the PRINT ends without ';'

typedef struct {
	const char *text;
	char ops;
	unsigned long cycles;
} Row;

extern const char t0[];
extern const char t2[];
extern const char t4[];
extern const char t11[];
extern const char t91[];
extern const char t92[];
extern const char t94[];
extern const char t140[];
extern const char t141[];
extern const char t142[];
extern const char t148[];
extern const char t189[];
extern const char t190[];
extern const char t191[];
extern const char t192[];
extern const char t193[];
extern const char t194[];
extern const char t200[];
extern const char t201[];
extern const char t202[];
extern const char t203[];
extern const char t204[];
extern const char t205[];
extern const char t206[];
extern const char t207[];
extern const char t208[];
extern const char t209[];
extern const char t210[];
extern const char t211[];
extern const char t212[];
extern const char t213[];
extern const char t214[];
extern const char t215[];
extern const char t216[];
extern const char t220[];
extern const char t221[];
extern const char t222[];
extern const char t223[];
extern const char t224[];
extern const char t225[];
extern const char t226[];
extern const char t227[];
extern const char t228[];
extern const char t229[];
extern const char t230[];
extern const char t231[];
extern const char t232[];
extern const char t233[];
extern const char t234[];
extern const char t381[];
extern const char t382[];
extern const char t384[];
extern const char t385[];
extern const char t386[];
extern const char t391[];
extern const char t398[];
extern const char t400[];
extern const char t401[];
extern const char t403[];
extern const char t404[];
extern const char t405[];
extern const char t406[];
extern const char t420[];
extern const char t421[];
extern const char t431[];
extern const char t432[];
extern const char t433[];
extern const char t434[];
extern const char t450[];
extern const char t451[];
extern const char t468[];
extern const char t469[];
extern const char t470[];
extern const char t471[];
extern const char t472[];
extern const char t473[];
extern const char t500[];
extern const char t501[];
extern const char t502[];
extern const char t503[];
extern const char t504[];
extern const char t510[];
extern const char t511[];
extern const char t512[];
extern const char t513[];
extern const char t514[];
extern const char t515[];
extern const char t517[];
extern const char t520[];
extern const char t521[];
extern const char t522[];
extern const char t523[];
extern const char t524[];
extern const char t525[];
extern const char t526[];
extern const char t527[];
extern const char t528[];
extern const char t794[];
extern const char t795[];
extern const char t800[];
extern const char t801[];
extern const char t802[];
extern const char t803[];
extern const char t804[];
extern const char t805[];
extern const char t806[];
extern const char t807[];
extern const char t808[];
extern const char t809[];
extern const char t810[];
extern const char t811[];
extern const char t812[];
extern const char t813[];
extern const char t814[];
extern const char t820[];
extern const char t821[];
extern const char t822[];
extern const char t823[];
extern const char t824[];
extern const char t825[];
extern const char t826[];
extern const char t827[];
extern const char t828[];
extern const char t829[];
extern const char t830[];
extern const char t831[];
extern const char t832[];
extern const char t833[];
extern const char t834[];
extern const char t1002[];
extern const char t1006[];
extern const char t1010[];
extern const char t1011[];
extern const char t1012[];
extern const char t1013[];
extern const char t1014[];
extern const char t1015[];
extern const char t1016[];
extern const char t1017[];
extern const char t1018[];
extern const char t1019[];
extern const char t1020[];
extern const char t1021[];
extern const char t1022[];
extern const char t1023[];
extern const char t1024[];
extern const char t1030[];
extern const char t1031[];
extern const char t1032[];
extern const char t1033[];
extern const char t1034[];
extern const char t1035[];
extern const char t1036[];
extern const char t1037[];
extern const char t1038[];
extern const char t1039[];
extern const char t1040[];
extern const char t1041[];
extern const char t1042[];
extern const char t1043[];
extern const char t1044[];
extern const char t1110[];
extern const char t1111[];
extern const char t1112[];
extern const char t1113[];
extern const char t1114[];
extern const char t1115[];
extern const char t1116[];
extern const char t1117[];
extern const char t1118[];
extern const char t1119[];
extern const char t1120[];
extern const char t1121[];
extern const char t1122[];
extern const char t1123[];
extern const char t1124[];
extern const char t1130[];
extern const char t1131[];
extern const char t1132[];
extern const char t1133[];
extern const char t1134[];
extern const char t1135[];
extern const char t1136[];
extern const char t1137[];
extern const char t1138[];
extern const char t1139[];
extern const char t1140[];
extern const char t1141[];
extern const char t1142[];
extern const char t1143[];
extern const char t1144[];
extern const char t2100[];
extern const char t2101[];
extern const char t2105[];
extern const char t2200[];
extern const char t2201[];
extern const char t2202[];
extern const char t2203[];
extern const char t2204[];
extern const char t2205[];
extern const char t2206[];
extern const char t2207[];
extern const char t2208[];
extern const char t2209[];
extern const char t2210[];
extern const char t2211[];
extern const char t2212[];
extern const char t2213[];
extern const char t2214[];
extern const char t2220[];
extern const char t2221[];
extern const char t2222[];
extern const char t2223[];
extern const char t2224[];
extern const char t2225[];
extern const char t2226[];
extern const char t2227[];
extern const char t2228[];
extern const char t2229[];
extern const char t2230[];
extern const char t2231[];
extern const char t2232[];
extern const char t2233[];
extern const char t2234[];
extern const char t7004[];
extern const char t7017[];
extern const char t7018[];
extern const char t7019[];
extern const char t7020[];
extern const char t7021[];
extern const char t7100[];
extern const char t11000[];
extern const char t11010[];
extern const char t11011[];
extern const char t11012[];
extern const char t11013[];
extern const char t11014[];
extern const char t11015[];
extern const char t11016[];
extern const char t11017[];
extern const char t11018[];
extern const char t11019[];
extern const char t11020[];
extern const char t11021[];
extern const char t11069[];
extern const char t11071[];
extern const char t11079[];
extern const char t12001[];
extern const char t12002[];
extern const char t12020[];
extern const char t12021[];
extern const char t12022[];
extern const char t12023[];
extern const char t12025[];
extern const char t12026[];
extern const char t12027[];
extern const char t12028[];
extern const char t12029[];
extern const char t12030[];
extern const char t12031[];
extern const char t12032[];
extern const char t12033[];
extern const char t12034[];
extern const char t12041[];
extern const char t12042[];
extern const char t12051[];
extern const char t12052[];
extern const char t12053[];
extern const char t12054[];
extern const char t12055[];
extern const char t12056[];
extern const char t12057[];
extern const char t12058[];
extern const char t12061[];
extern const char t12062[];
extern const char t12063[];
extern const char t12064[];
extern const char t12065[];
extern const char t12066[];
extern const char t12070[];
extern const char t12071[];
extern const char t12072[];
extern const char t12073[];
extern const char t12074[];
extern const char t12077[];
extern const char t12078[];
extern const char t12080[];
extern const char t12100[];
extern const char t12101[];
extern const char t12102[];
extern const char t12103[];
extern const char t12104[];
extern const char t12105[];
extern const char t12106[];
extern const char t12107[];
extern const char t12112[];
extern const char t12113[];
extern const char t12114[];
extern const char t12115[];
extern const char t12401[];
extern const char t12405[];
extern const char t12410[];
extern const char t12411[];
extern const char t12412[];
extern const char t12413[];
extern const char t12414[];
extern const char t12415[];
extern const char t12417[];
extern const char t20050[];
extern const char t20051[];
extern const char t20055[];
extern const char t20055_2[];
extern const char t20070[];

extern const Row rows_91[2];	// lines 91-92
extern const Row rows_189[6];	// lines 189-194
extern const Row rows_200[15];	// lines 200-214
extern const Row rows_220[15];	// lines 220-234
extern const Row rows_381[7];	// lines 381-387
extern const Row rows_391[8];	// lines 391-398
extern const Row rows_401[6];	// lines 401-406
extern const Row rows_420[15];	// lines 420-434
extern const Row rows_451[21];	// lines 451-471
extern const Row rows_500[5];	// lines 500-504
extern const Row rows_510[7];	// lines 510-517
extern const Row rows_520[9];	// lines 520-528
extern const Row rows_794[20];	// lines 794-814
extern const Row rows_820[15];	// lines 820-834
extern const Row rows_1001[6];	// lines 1001-1006
extern const Row rows_1010[15];	// lines 1010-1024
extern const Row rows_1030[15];	// lines 1030-1044
extern const Row rows_1101[6];	// lines 1101-1106
extern const Row rows_1110[15];	// lines 1110-1124
extern const Row rows_1130[15];	// lines 1130-1144
extern const Row rows_2100[5];	// lines 2100-2105
extern const Row rows_2200[15];	// lines 2200-2214
extern const Row rows_2220[15];	// lines 2220-2234
extern const Row rows_6011[2];	// lines 6011-6012
extern const Row rows_11010[12];	// lines 11010-11021
extern const Row rows_12020[14];	// lines 12020-12034
extern const Row rows_12041[18];	// lines 12041-12066
extern const Row rows_12070[13];	// lines 12070-12089
extern const Row rows_12101[7];	// lines 12101-12107
extern const Row rows_12112[5];	// lines 12112-12189
extern const Row rows_12401[9];	// lines 12401-12417

// Cycles per pass of each line in the original, without its subroutines
#define CYCLES_0	0ul
#define CYCLES_2	0ul
#define CYCLES_3	8ul
#define CYCLES_4	0ul
#define CYCLES_5	32610ul
#define CYCLES_6	40919ul
#define CYCLES_7	14694ul
#define CYCLES_8	14716ul
#define CYCLES_9	14600ul
#define CYCLES_10	5677ul
#define CYCLES_11	29343ul
#define CYCLES_12	18613ul
#define CYCLES_13	18986ul
#define CYCLES_14	18766ul
#define CYCLES_15	18786ul
#define CYCLES_18	22937ul
#define CYCLES_19	244ul
#define CYCLES_20	29317ul
#define CYCLES_21	29005ul
#define CYCLES_22	31206ul
#define CYCLES_23	214ul
#define CYCLES_24	29137ul
#define CYCLES_25	28759ul
#define CYCLES_26	31312ul
#define CYCLES_27	192ul
#define CYCLES_28	26486ul
#define CYCLES_29	25986ul
#define CYCLES_30	28374ul
#define CYCLES_31	205ul
#define CYCLES_32	20667ul
#define CYCLES_33	28839ul
#define CYCLES_34	32688ul
#define CYCLES_35	220ul
#define CYCLES_36	31694ul
#define CYCLES_37	10454ul
#define CYCLES_38	221ul
#define CYCLES_39	29041ul
#define CYCLES_40	43493ul
#define CYCLES_41	8474ul
#define CYCLES_42	113872ul
#define CYCLES_43	61845ul
#define CYCLES_44	42355ul
#define CYCLES_45	14813ul
#define CYCLES_46	14636ul
#define CYCLES_47	14694ul
#define CYCLES_48	14653ul
#define CYCLES_49	214ul
#define CYCLES_51	6307ul
#define CYCLES_52	6969ul
#define CYCLES_53	18176ul
#define CYCLES_54	217ul
#define CYCLES_55	29879ul
#define CYCLES_56	222ul
#define CYCLES_57	130957ul
#define CYCLES_58	0ul
#define CYCLES_59	0ul
#define CYCLES_60	0ul
#define CYCLES_91	19368ul
#define CYCLES_92	18879ul
#define CYCLES_93	129057ul
#define CYCLES_94	26421ul
#define CYCLES_95	759ul
#define CYCLES_96	4859ul
#define CYCLES_97	984ul
#define CYCLES_98	3816ul
#define CYCLES_100	26487ul
#define CYCLES_101	45824ul
#define CYCLES_102	45831ul
#define CYCLES_103	44652ul
#define CYCLES_105	44939ul
#define CYCLES_106	4456ul
#define CYCLES_107	13061ul
#define CYCLES_108	14251ul
#define CYCLES_109	14048ul
#define CYCLES_110	14582ul
#define CYCLES_111	3748ul
#define CYCLES_115	39469ul
#define CYCLES_120	0ul
#define CYCLES_121	0ul
#define CYCLES_122	38798ul
#define CYCLES_123	38830ul
#define CYCLES_125	40165ul
#define CYCLES_126	9248ul
#define CYCLES_127	7ul
#define CYCLES_128	7ul
#define CYCLES_129	8ul
#define CYCLES_130	7ul
#define CYCLES_131	0ul
#define CYCLES_135	0ul
#define CYCLES_140	4860ul
#define CYCLES_141	4937ul
#define CYCLES_142	4971ul
#define CYCLES_144	230ul
#define CYCLES_145	0ul
#define CYCLES_146	0ul
#define CYCLES_147	0ul
#define CYCLES_148	0ul
#define CYCLES_149	0ul
#define CYCLES_150	15075ul
#define CYCLES_151	1653ul
#define CYCLES_152	15413ul
#define CYCLES_153	55611ul
#define CYCLES_154	225ul
#define CYCLES_180	8860ul
#define CYCLES_188	42523ul
#define CYCLES_189	19549ul
#define CYCLES_190	24228ul
#define CYCLES_191	21907ul
#define CYCLES_192	22054ul
#define CYCLES_193	15153ul
#define CYCLES_194	20003ul
#define CYCLES_195	2775ul
#define CYCLES_196	22341ul
#define CYCLES_197	4530ul
#define CYCLES_200	33055ul
#define CYCLES_201	28935ul
#define CYCLES_202	29713ul
#define CYCLES_203	22567ul
#define CYCLES_204	29713ul
#define CYCLES_205	22541ul
#define CYCLES_206	30266ul
#define CYCLES_207	35872ul
#define CYCLES_208	30261ul
#define CYCLES_209	22611ul
#define CYCLES_210	30611ul
#define CYCLES_211	22613ul
#define CYCLES_212	30659ul
#define CYCLES_213	30081ul
#define CYCLES_214	21712ul
#define CYCLES_215	23282ul
#define CYCLES_216	16036ul
#define CYCLES_217	12573ul
#define CYCLES_220	32079ul
#define CYCLES_221	30145ul
#define CYCLES_222	29797ul
#define CYCLES_223	30118ul
#define CYCLES_224	21665ul
#define CYCLES_225	30496ul
#define CYCLES_226	22847ul
#define CYCLES_227	28908ul
#define CYCLES_228	29721ul
#define CYCLES_229	30117ul
#define CYCLES_230	29845ul
#define CYCLES_231	31069ul
#define CYCLES_232	21234ul
#define CYCLES_233	30128ul
#define CYCLES_234	21588ul
#define CYCLES_235	20274ul
#define CYCLES_236	11987ul
#define CYCLES_237	11964ul
#define CYCLES_238	19378ul
#define CYCLES_239	9018ul
#define CYCLES_240	23316ul
#define CYCLES_241	6335ul
#define CYCLES_242	11772ul
#define CYCLES_243	11713ul
#define CYCLES_244	18207ul
#define CYCLES_245	11684ul
#define CYCLES_246	27823ul
#define CYCLES_250	12744ul
#define CYCLES_251	9734ul
#define CYCLES_300	0ul
#define CYCLES_380	31815ul
#define CYCLES_381	63387ul
#define CYCLES_382	18869ul
#define CYCLES_383	18761ul
#define CYCLES_384	16498ul
#define CYCLES_385	16552ul
#define CYCLES_386	16682ul
#define CYCLES_387	16582ul
#define CYCLES_389	10148ul
#define CYCLES_391	16980ul
#define CYCLES_392	16989ul
#define CYCLES_393	16830ul
#define CYCLES_394	16725ul
#define CYCLES_395	16772ul
#define CYCLES_396	16755ul
#define CYCLES_397	16949ul
#define CYCLES_398	17753ul
#define CYCLES_399	23089ul
#define CYCLES_400	24825ul
#define CYCLES_401	13753ul
#define CYCLES_402	21500ul
#define CYCLES_403	21274ul
#define CYCLES_404	20339ul
#define CYCLES_405	13626ul
#define CYCLES_406	21025ul
#define CYCLES_407	5261ul
#define CYCLES_419	18232ul
#define CYCLES_420	14391ul
#define CYCLES_421	20624ul
#define CYCLES_422	21206ul
#define CYCLES_423	13928ul
#define CYCLES_424	21689ul
#define CYCLES_425	13863ul
#define CYCLES_426	21236ul
#define CYCLES_427	21688ul
#define CYCLES_428	13677ul
#define CYCLES_429	21420ul
#define CYCLES_430	13809ul
#define CYCLES_431	20883ul
#define CYCLES_432	19839ul
#define CYCLES_433	20955ul
#define CYCLES_434	13244ul
#define CYCLES_449	5168ul
#define CYCLES_450	26564ul
#define CYCLES_451	13728ul
#define CYCLES_452	21050ul
#define CYCLES_453	20704ul
#define CYCLES_454	13584ul
#define CYCLES_455	20022ul
#define CYCLES_456	21528ul
#define CYCLES_457	13737ul
#define CYCLES_458	21088ul
#define CYCLES_459	20763ul
#define CYCLES_460	21075ul
#define CYCLES_461	13849ul
#define CYCLES_462	21116ul
#define CYCLES_463	13806ul
#define CYCLES_464	19960ul
#define CYCLES_465	20699ul
#define CYCLES_466	13745ul
#define CYCLES_467	13741ul
#define CYCLES_468	21560ul
#define CYCLES_469	13601ul
#define CYCLES_470	26496ul
#define CYCLES_471	18096ul
#define CYCLES_472	15051ul
#define CYCLES_473	21434ul
#define CYCLES_480	5304ul
#define CYCLES_485	6292ul
#define CYCLES_486	19185ul
#define CYCLES_487	4638ul
#define CYCLES_488	15990ul
#define CYCLES_489	11080ul
#define CYCLES_490	12073ul
#define CYCLES_491	19644ul
#define CYCLES_492	12035ul
#define CYCLES_493	12031ul
#define CYCLES_494	21077ul
#define CYCLES_497	25834ul
#define CYCLES_498	21008ul
#define CYCLES_499	34450ul
#define CYCLES_500	14308ul
#define CYCLES_501	18044ul
#define CYCLES_502	18195ul
#define CYCLES_503	18328ul
#define CYCLES_504	18849ul
#define CYCLES_507	140515ul
#define CYCLES_510	14922ul
#define CYCLES_511	16597ul
#define CYCLES_512	16734ul
#define CYCLES_513	17252ul
#define CYCLES_514	17536ul
#define CYCLES_515	18001ul
#define CYCLES_517	18325ul
#define CYCLES_518	145491ul
#define CYCLES_520	15395ul
#define CYCLES_521	17091ul
#define CYCLES_522	17473ul
#define CYCLES_523	17899ul
#define CYCLES_524	9101ul
#define CYCLES_525	18556ul
#define CYCLES_526	18819ul
#define CYCLES_527	19368ul
#define CYCLES_528	19561ul
#define CYCLES_529	138914ul
#define CYCLES_780	46259ul
#define CYCLES_790	16269ul
#define CYCLES_793	4404ul
#define CYCLES_794	62938ul
#define CYCLES_795	19689ul
#define CYCLES_796	19586ul
#define CYCLES_797	19397ul
#define CYCLES_798	19532ul
#define CYCLES_800	27009ul
#define CYCLES_801	25456ul
#define CYCLES_802	25238ul
#define CYCLES_803	19125ul
#define CYCLES_804	24866ul
#define CYCLES_805	26148ul
#define CYCLES_806	17329ul
#define CYCLES_807	31895ul
#define CYCLES_808	24881ul
#define CYCLES_809	19231ul
#define CYCLES_810	25309ul
#define CYCLES_811	19206ul
#define CYCLES_812	24906ul
#define CYCLES_813	26131ul
#define CYCLES_814	17404ul
#define CYCLES_815	22079ul
#define CYCLES_819	5211ul
#define CYCLES_820	29932ul
#define CYCLES_821	24702ul
#define CYCLES_822	19317ul
#define CYCLES_823	24081ul
#define CYCLES_824	19333ul
#define CYCLES_825	24117ul
#define CYCLES_826	26912ul
#define CYCLES_827	23541ul
#define CYCLES_828	26307ul
#define CYCLES_829	17205ul
#define CYCLES_830	26405ul
#define CYCLES_831	24764ul
#define CYCLES_832	19536ul
#define CYCLES_833	25097ul
#define CYCLES_834	19464ul
#define CYCLES_835	22849ul
#define CYCLES_836	11525ul
#define CYCLES_837	12585ul
#define CYCLES_838	13917ul
#define CYCLES_840	14565ul
#define CYCLES_842	19601ul
#define CYCLES_843	11636ul
#define CYCLES_844	11783ul
#define CYCLES_845	19099ul
#define CYCLES_846	6977ul
#define CYCLES_847	5217ul
#define CYCLES_850	18984ul
#define CYCLES_1000	33513ul
#define CYCLES_1001	19429ul
#define CYCLES_1002	19012ul
#define CYCLES_1003	16979ul
#define CYCLES_1004	17305ul
#define CYCLES_1005	17198ul
#define CYCLES_1006	17500ul
#define CYCLES_1007	4402ul
#define CYCLES_1010	31001ul
#define CYCLES_1011	27913ul
#define CYCLES_1012	21811ul
#define CYCLES_1013	29473ul
#define CYCLES_1014	21765ul
#define CYCLES_1015	29180ul
#define CYCLES_1016	28759ul
#define CYCLES_1017	29122ul
#define CYCLES_1018	28154ul
#define CYCLES_1019	29544ul
#define CYCLES_1020	22715ul
#define CYCLES_1021	28582ul
#define CYCLES_1022	29295ul
#define CYCLES_1023	21557ul
#define CYCLES_1024	29681ul
#define CYCLES_1025	6408ul
#define CYCLES_1026	14883ul
#define CYCLES_1027	12816ul
#define CYCLES_1030	31076ul
#define CYCLES_1031	21699ul
#define CYCLES_1032	21839ul
#define CYCLES_1033	29488ul
#define CYCLES_1034	21910ul
#define CYCLES_1035	29183ul
#define CYCLES_1036	28780ul
#define CYCLES_1037	27919ul
#define CYCLES_1038	29390ul
#define CYCLES_1039	29514ul
#define CYCLES_1040	21791ul
#define CYCLES_1041	21650ul
#define CYCLES_1042	29781ul
#define CYCLES_1043	21940ul
#define CYCLES_1044	29309ul
#define CYCLES_1045	22055ul
#define CYCLES_1046	10523ul
#define CYCLES_1047	12819ul
#define CYCLES_1048	6209ul
#define CYCLES_1049	22672ul
#define CYCLES_1050	6274ul
#define CYCLES_1051	20318ul
#define CYCLES_1052	12518ul
#define CYCLES_1053	12575ul
#define CYCLES_1054	19859ul
#define CYCLES_1055	34324ul
#define CYCLES_1056	5405ul
#define CYCLES_1060	23170ul
#define CYCLES_1100	33374ul
#define CYCLES_1101	19402ul
#define CYCLES_1102	19133ul
#define CYCLES_1103	17166ul
#define CYCLES_1104	17478ul
#define CYCLES_1105	17396ul
#define CYCLES_1106	17654ul
#define CYCLES_1107	4527ul
#define CYCLES_1110	31720ul
#define CYCLES_1111	29497ul
#define CYCLES_1112	28979ul
#define CYCLES_1113	22869ul
#define CYCLES_1114	28924ul
#define CYCLES_1115	30863ul
#define CYCLES_1116	21917ul
#define CYCLES_1117	30205ul
#define CYCLES_1118	28316ul
#define CYCLES_1119	22861ul
#define CYCLES_1120	30097ul
#define CYCLES_1121	23143ul
#define CYCLES_1122	29988ul
#define CYCLES_1123	23199ul
#define CYCLES_1124	28624ul
#define CYCLES_1125	1845ul
#define CYCLES_1126	3774ul
#define CYCLES_1127	1421ul
#define CYCLES_1130	31610ul
#define CYCLES_1131	30555ul
#define CYCLES_1132	28719ul
#define CYCLES_1133	22623ul
#define CYCLES_1134	28540ul
#define CYCLES_1135	22715ul
#define CYCLES_1136	27835ul
#define CYCLES_1137	29545ul
#define CYCLES_1138	29125ul
#define CYCLES_1139	23462ul
#define CYCLES_1140	28355ul
#define CYCLES_1141	22824ul
#define CYCLES_1142	29416ul
#define CYCLES_1143	22791ul
#define CYCLES_1144	20509ul
#define CYCLES_1145	17787ul
#define CYCLES_1146	12608ul
#define CYCLES_1147	9894ul
#define CYCLES_1148	6927ul
#define CYCLES_1149	8779ul
#define CYCLES_1150	6321ul
#define CYCLES_1151	20786ul
#define CYCLES_1152	12633ul
#define CYCLES_1153	13167ul
#define CYCLES_1154	12762ul
#define CYCLES_1155	37454ul
#define CYCLES_1156	13251ul
#define CYCLES_1157	5319ul
#define CYCLES_1160	26662ul
#define CYCLES_2100	19481ul
#define CYCLES_2101	19361ul
#define CYCLES_2102	18969ul
#define CYCLES_2103	19255ul
#define CYCLES_2105	18074ul
#define CYCLES_2110	18249ul
#define CYCLES_2111	8778ul
#define CYCLES_2120	12859ul
#define CYCLES_2121	12932ul
#define CYCLES_2200	31701ul
#define CYCLES_2201	29581ul
#define CYCLES_2202	30489ul
#define CYCLES_2203	23201ul
#define CYCLES_2204	29950ul
#define CYCLES_2205	30156ul
#define CYCLES_2206	29982ul
#define CYCLES_2207	29538ul
#define CYCLES_2208	29286ul
#define CYCLES_2209	23133ul
#define CYCLES_2210	30854ul
#define CYCLES_2211	23117ul
#define CYCLES_2212	29817ul
#define CYCLES_2213	30052ul
#define CYCLES_2214	21866ul
#define CYCLES_2215	19262ul
#define CYCLES_2216	14322ul
#define CYCLES_2220	32557ul
#define CYCLES_2221	22101ul
#define CYCLES_2222	30291ul
#define CYCLES_2223	29568ul
#define CYCLES_2224	23259ul
#define CYCLES_2225	30018ul
#define CYCLES_2226	23333ul
#define CYCLES_2227	35342ul
#define CYCLES_2228	30755ul
#define CYCLES_2229	22021ul
#define CYCLES_2230	30318ul
#define CYCLES_2231	22523ul
#define CYCLES_2232	30735ul
#define CYCLES_2233	22088ul
#define CYCLES_2234	29266ul
#define CYCLES_2235	8298ul
#define CYCLES_2239	6438ul
#define CYCLES_2240	14340ul
#define CYCLES_2243	11693ul
#define CYCLES_2244	19197ul
#define CYCLES_2245	11690ul
#define CYCLES_2246	25935ul
#define CYCLES_2247	12750ul
#define CYCLES_2250	32255ul
#define CYCLES_5999	4198ul
#define CYCLES_6000	151411ul
#define CYCLES_6001	177812ul
#define CYCLES_6002	1088ul
#define CYCLES_6003	55497ul
#define CYCLES_6004	395041ul
#define CYCLES_6006	17359ul
#define CYCLES_6007	19517ul
#define CYCLES_6008	10539ul
#define CYCLES_6010	22916ul
#define CYCLES_6011	18531ul
#define CYCLES_6012	17993ul
#define CYCLES_6099	231ul
#define CYCLES_7000	757ul
#define CYCLES_7002	14442ul
#define CYCLES_7003	968ul
#define CYCLES_7004	8854ul
#define CYCLES_7005	11378ul
#define CYCLES_7010	5660ul
#define CYCLES_7011	917704ul
#define CYCLES_7015	9506ul
#define CYCLES_7016	4095ul
#define CYCLES_7017	4975ul
#define CYCLES_7018	4070ul
#define CYCLES_7019	3353ul
#define CYCLES_7020	3093ul
#define CYCLES_7021	3787ul
#define CYCLES_7022	5952ul
#define CYCLES_7023	6475ul
#define CYCLES_7024	6810ul
#define CYCLES_7025	1456ul
#define CYCLES_7026	3581ul
#define CYCLES_7027	58963ul
#define CYCLES_7028	57769ul
#define CYCLES_7029	57724ul
#define CYCLES_7030	58713ul
#define CYCLES_7031	1458ul
#define CYCLES_7032	39340ul
#define CYCLES_7035	13459ul
#define CYCLES_7036	6056ul
#define CYCLES_7037	40994ul
#define CYCLES_7039	40576ul
#define CYCLES_7040	6052ul
#define CYCLES_7041	6241ul
#define CYCLES_7042	6842ul
#define CYCLES_7045	1432ul
#define CYCLES_7046	39561ul
#define CYCLES_7047	1507ul
#define CYCLES_7048	39590ul
#define CYCLES_7049	1434ul
#define CYCLES_7050	39644ul
#define CYCLES_7060	40987ul
#define CYCLES_7065	6260ul
#define CYCLES_7066	6320ul
#define CYCLES_7067	7198ul
#define CYCLES_7070	58040ul
#define CYCLES_7071	58148ul
#define CYCLES_7072	0ul
#define CYCLES_7073	0ul
#define CYCLES_7075	1455ul
#define CYCLES_7076	41207ul
#define CYCLES_7077	1518ul
#define CYCLES_7078	41461ul
#define CYCLES_7082	0ul
#define CYCLES_7085	6568ul
#define CYCLES_7086	6468ul
#define CYCLES_7087	7321ul
#define CYCLES_7090	55414ul
#define CYCLES_7091	59856ul
#define CYCLES_7092	60950ul
#define CYCLES_7093	0ul
#define CYCLES_7095	1551ul
#define CYCLES_7096	43099ul
#define CYCLES_7097	1389ul
#define CYCLES_7098	42422ul
#define CYCLES_7099	0ul
#define CYCLES_7100	47874ul
#define CYCLES_7101	685ul
#define CYCLES_7102	35896ul
#define CYCLES_7103	31511ul
#define CYCLES_7104	35241ul
#define CYCLES_7300	222ul
#define CYCLES_7301	0ul
#define CYCLES_7400	945768ul
#define CYCLES_7401	219ul
#define CYCLES_7500	1255901ul
#define CYCLES_8000	0ul
#define CYCLES_8006	0ul
#define CYCLES_8007	0ul
#define CYCLES_8008	0ul
#define CYCLES_8009	0ul
#define CYCLES_8010	0ul
#define CYCLES_8011	0ul
#define CYCLES_8012	0ul
#define CYCLES_8013	0ul
#define CYCLES_8014	0ul
#define CYCLES_8015	0ul
#define CYCLES_8016	0ul
#define CYCLES_8017	0ul
#define CYCLES_8018	0ul
#define CYCLES_8019	0ul
#define CYCLES_8020	0ul
#define CYCLES_8021	0ul
#define CYCLES_8025	0ul
#define CYCLES_8026	0ul
#define CYCLES_8027	0ul
#define CYCLES_8028	0ul
#define CYCLES_8030	0ul
#define CYCLES_8031	0ul
#define CYCLES_8032	0ul
#define CYCLES_8040	0ul
#define CYCLES_8041	0ul
#define CYCLES_8042	0ul
#define CYCLES_8050	0ul
#define CYCLES_8051	0ul
#define CYCLES_8098	0ul
#define CYCLES_8099	0ul
#define CYCLES_10999	0ul
#define CYCLES_11000	87929ul
#define CYCLES_11001	17910ul
#define CYCLES_11002	109093ul
#define CYCLES_11010	23131ul
#define CYCLES_11011	23087ul
#define CYCLES_11012	23087ul
#define CYCLES_11013	21202ul
#define CYCLES_11014	28532ul
#define CYCLES_11015	29271ul
#define CYCLES_11016	25178ul
#define CYCLES_11017	29325ul
#define CYCLES_11018	29258ul
#define CYCLES_11019	14126ul
#define CYCLES_11020	15428ul
#define CYCLES_11021	14673ul
#define CYCLES_11030	19766ul
#define CYCLES_11031	23278ul
#define CYCLES_11032	22514ul
#define CYCLES_11033	23063ul
#define CYCLES_11034	14457ul
#define CYCLES_11067	17362ul
#define CYCLES_11069	308443ul
#define CYCLES_11070	428976ul
#define CYCLES_11071	3262ul
#define CYCLES_11072	25678ul
#define CYCLES_11075	2420ul
#define CYCLES_11078	108595ul
#define CYCLES_11079	58624ul
#define CYCLES_11080	5783ul
#define CYCLES_11100	85115ul
#define CYCLES_11999	5025ul
#define CYCLES_12000	169347ul
#define CYCLES_12001	28086ul
#define CYCLES_12002	9855ul
#define CYCLES_12005	17021ul
#define CYCLES_12010	40480ul
#define CYCLES_12020	17450ul
#define CYCLES_12021	17307ul
#define CYCLES_12022	16691ul
#define CYCLES_12023	5285ul
#define CYCLES_12025	16388ul
#define CYCLES_12026	16341ul
#define CYCLES_12027	16690ul
#define CYCLES_12028	17102ul
#define CYCLES_12029	14293ul
#define CYCLES_12030	13347ul
#define CYCLES_12031	14262ul
#define CYCLES_12032	16167ul
#define CYCLES_12033	19089ul
#define CYCLES_12034	23613ul
#define CYCLES_12035	5347ul
#define CYCLES_12040	20822ul
#define CYCLES_12041	57240ul
#define CYCLES_12042	12023ul
#define CYCLES_12050	17189ul
#define CYCLES_12051	17028ul
#define CYCLES_12052	17029ul
#define CYCLES_12053	18058ul
#define CYCLES_12054	17061ul
#define CYCLES_12055	18299ul
#define CYCLES_12056	16895ul
#define CYCLES_12057	17038ul
#define CYCLES_12058	19263ul
#define CYCLES_12060	17236ul
#define CYCLES_12061	17070ul
#define CYCLES_12062	18166ul
#define CYCLES_12063	16944ul
#define CYCLES_12064	17647ul
#define CYCLES_12065	14865ul
#define CYCLES_12066	16298ul
#define CYCLES_12067	5291ul
#define CYCLES_12070	62598ul
#define CYCLES_12071	18497ul
#define CYCLES_12072	17740ul
#define CYCLES_12073	17196ul
#define CYCLES_12074	18432ul
#define CYCLES_12075	17521ul
#define CYCLES_12076	16917ul
#define CYCLES_12077	18635ul
#define CYCLES_12078	17489ul
#define CYCLES_12079	16972ul
#define CYCLES_12080	18631ul
#define CYCLES_12081	17542ul
#define CYCLES_12089	16112ul
#define CYCLES_12090	5062ul
#define CYCLES_12099	45619ul
#define CYCLES_12100	69691ul
#define CYCLES_12101	14105ul
#define CYCLES_12102	17147ul
#define CYCLES_12103	17255ul
#define CYCLES_12104	7319ul
#define CYCLES_12105	12545ul
#define CYCLES_12106	13538ul
#define CYCLES_12107	11353ul
#define CYCLES_12110	44612ul
#define CYCLES_12111	29149ul
#define CYCLES_12112	8865ul
#define CYCLES_12113	16581ul
#define CYCLES_12114	17626ul
#define CYCLES_12115	17470ul
#define CYCLES_12189	16459ul
#define CYCLES_12190	5309ul
#define CYCLES_12199	269ul
#define CYCLES_12200	114034ul
#define CYCLES_12201	34347ul
#define CYCLES_12400	114636ul
#define CYCLES_12401	53772ul
#define CYCLES_12405	14541ul
#define CYCLES_12410	18463ul
#define CYCLES_12411	18521ul
#define CYCLES_12412	18378ul
#define CYCLES_12413	18276ul
#define CYCLES_12414	18277ul
#define CYCLES_12415	17284ul
#define CYCLES_12417	7614ul
#define CYCLES_12420	8237072ul
#define CYCLES_13000	60695ul
#define CYCLES_13001	37054ul
#define CYCLES_13002	24876ul
#define CYCLES_13010	127548ul
#define CYCLES_13011	11766ul
#define CYCLES_13012	223221ul
#define CYCLES_13013	27566ul
#define CYCLES_13014	6370099ul
#define CYCLES_13015	1933924ul
#define CYCLES_13016	2127511ul
#define CYCLES_13017	495004ul
#define CYCLES_13018	1143447ul
#define CYCLES_13021	135977ul
#define CYCLES_13022	2130567ul
#define CYCLES_13029	1960997ul
#define CYCLES_13030	4451ul
#define CYCLES_13099	197ul
#define CYCLES_20000	21010ul
#define CYCLES_20001	216ul
#define CYCLES_20002	13927ul
#define CYCLES_20003	12537ul
#define CYCLES_20004	12607ul
#define CYCLES_20005	12829ul
#define CYCLES_20006	12732ul
#define CYCLES_20007	12786ul
#define CYCLES_20008	12918ul
#define CYCLES_20009	13242ul
#define CYCLES_20010	13989ul
#define CYCLES_20011	3045ul
#define CYCLES_20049	0ul
#define CYCLES_20050	65535ul
#define CYCLES_20051	181254ul
#define CYCLES_20055	9418ul
#define CYCLES_20056	644836ul
#define CYCLES_20057	16654ul
#define CYCLES_20058	10044913ul
#define CYCLES_20060	994059ul
#define CYCLES_20065	57482ul
#define CYCLES_20066	183952ul
#define CYCLES_20070	21482ul
#define CYCLES_20071	156722ul
#define CYCLES_20080	187ul
#define CYCLES_20100	159799ul
#define CYCLES_20110	53535ul

#pragma compile("text.c")

#endif
