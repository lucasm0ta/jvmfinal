#include "decodificador.h"

const char *INSTR_TABLESWITCH = "tableswitch";
const char *INSTR_LOOKUPSWITCH = "lookupswitch";

void inicializar_decodificador() {
  strcpy(decode[0].instruction, "nop");
  decode[0].bytes = 0;

  strcpy(decode[1].instruction, "aconst_null");
  decode[1].bytes = 0;
  decode[1].referencesCP = 0;

  strcpy(decode[2].instruction, "iconst_m1");
  decode[2].bytes = 0;
  decode[2].referencesCP = 0;

  strcpy(decode[3].instruction, "iconst_0");
  decode[3].bytes = 0;
  decode[3].referencesCP = 0;

  strcpy(decode[4].instruction, "iconst_1");
  decode[4].bytes = 0;
  decode[4].referencesCP = 0;

  strcpy(decode[5].instruction, "iconst_2");
  decode[5].bytes = 0;
  decode[5].referencesCP = 0;

  strcpy(decode[6].instruction, "iconst_3");
  decode[6].bytes = 0;
  decode[6].referencesCP = 0;

  strcpy(decode[7].instruction, "iconst_4");
  decode[7].bytes = 0;
  decode[7].referencesCP = 0;

  strcpy(decode[8].instruction, "iconst_5");
  decode[8].bytes = 0;
  decode[8].referencesCP = 0;

  strcpy(decode[9].instruction, "lconst_0");
  decode[9].bytes = 0;
  decode[9].referencesCP = 0;

  strcpy(decode[10].instruction, "lconst_1");
  decode[10].bytes = 0;
  decode[10].referencesCP = 0;

  strcpy(decode[11].instruction, "fconst_0");
  decode[11].bytes = 0;
  decode[11].referencesCP = 0;

  strcpy(decode[12].instruction, "fconst_1");
  decode[12].bytes = 0;
  decode[12].referencesCP = 0;

  strcpy(decode[13].instruction, "fconst_2");
  decode[13].bytes = 0;
  decode[13].referencesCP = 0;

  strcpy(decode[14].instruction, "dconst_0");
  decode[14].bytes = 0;
  decode[14].referencesCP = 0;

  strcpy(decode[15].instruction, "dconst_1");
  decode[15].bytes = 0;
  decode[15].referencesCP = 0;

  strcpy(decode[16].instruction, "bipush");
  decode[16].bytes = 1;
  decode[16].referencesCP = 0;

  strcpy(decode[17].instruction, "sipush");
  decode[17].bytes = 2;
  decode[17].referencesCP = 0;

  strcpy(decode[18].instruction, "ldc");
  decode[18].bytes = 1;
  decode[18].referencesCP = 1;

  strcpy(decode[19].instruction, "ldc_w");
  decode[19].bytes = 2;
  decode[19].referencesCP = 1;

  strcpy(decode[20].instruction, "ldc2_w");
  decode[20].bytes = 2;
  decode[20].referencesCP = 1;

  strcpy(decode[21].instruction, "iload");
  decode[21].bytes = 1;
  decode[21].referencesCP = 0;

  strcpy(decode[22].instruction, "lload");
  decode[22].bytes = 1;
  decode[22].referencesCP = 0;

  strcpy(decode[23].instruction, "fload");
  decode[23].bytes = 1;
  decode[23].referencesCP = 0;

  strcpy(decode[24].instruction, "dload");
  decode[24].bytes = 1;
  decode[24].referencesCP = 0;

  strcpy(decode[25].instruction, "aload");
  decode[25].bytes = 1;
  decode[25].referencesCP = 0;

  strcpy(decode[26].instruction, "iload_0");
  decode[26].bytes = 0;
  decode[26].referencesCP = 0;

  strcpy(decode[27].instruction, "iload_1");
  decode[27].bytes = 0;
  decode[27].referencesCP = 0;

  strcpy(decode[28].instruction, "iload_2");
  decode[28].bytes = 0;
  decode[28].referencesCP = 0;

  strcpy(decode[29].instruction, "iload_3");
  decode[29].bytes = 0;
  decode[29].referencesCP = 0;

  strcpy(decode[30].instruction, "lload_0");
  decode[30].bytes = 0;
  decode[30].referencesCP = 0;

  strcpy(decode[31].instruction, "lload_1");
  decode[31].bytes = 0;
  decode[31].referencesCP = 0;

  strcpy(decode[32].instruction, "lload_2");
  decode[32].bytes = 0;
  decode[32].referencesCP = 0;

  strcpy(decode[33].instruction, "lload_3");
  decode[33].bytes = 0;
  decode[33].referencesCP = 0;

  strcpy(decode[34].instruction, "fload_0");
  decode[34].bytes = 0;
  decode[34].referencesCP = 0;

  strcpy(decode[35].instruction, "fload_1");
  decode[35].bytes = 0;
  decode[35].referencesCP = 0;

  strcpy(decode[36].instruction, "fload_2");
  decode[36].bytes = 0;
  decode[36].referencesCP = 0;

  strcpy(decode[37].instruction, "fload_3");
  decode[37].bytes = 0;
  decode[37].referencesCP = 0;

  strcpy(decode[38].instruction, "dload_0");
  decode[38].bytes = 0;
  decode[38].referencesCP = 0;

  strcpy(decode[39].instruction, "dload_1");
  decode[39].bytes = 0;
  decode[39].referencesCP = 0;

  strcpy(decode[40].instruction, "dload_2");
  decode[40].bytes = 0;
  decode[40].referencesCP = 0;

  strcpy(decode[41].instruction, "dload_3");
  decode[41].bytes = 0;
  decode[41].referencesCP = 0;

  strcpy(decode[42].instruction, "aload_0");
  decode[42].bytes = 0;
  decode[42].referencesCP = 0;

  strcpy(decode[43].instruction, "aload_1");
  decode[43].bytes = 0;
  decode[43].referencesCP = 0;

  strcpy(decode[44].instruction, "aload_2");
  decode[44].bytes = 0;
  decode[40].referencesCP = 0;

  strcpy(decode[45].instruction, "aload_3");
  decode[45].bytes = 0;
  decode[45].referencesCP = 0;

  strcpy(decode[46].instruction, "iaload");
  decode[46].bytes = 0;
  decode[46].referencesCP = 0;

  strcpy(decode[47].instruction, "laload");
  decode[47].bytes = 0;
  decode[47].referencesCP = 0;

  strcpy(decode[48].instruction, "faload");
  decode[48].bytes = 0;
  decode[48].referencesCP = 0;

  strcpy(decode[49].instruction, "daload");
  decode[49].bytes = 0;
  decode[49].referencesCP = 0;

  strcpy(decode[50].instruction, "aaload");
  decode[50].bytes = 0;
  decode[50].referencesCP = 0;

  strcpy(decode[51].instruction, "baload");
  decode[51].bytes = 0;
  decode[51].referencesCP = 0;

  strcpy(decode[52].instruction, "caload");
  decode[52].bytes = 0;
  decode[52].referencesCP = 0;

  strcpy(decode[53].instruction, "saload");
  decode[53].bytes = 0;
  decode[53].referencesCP = 0;

  strcpy(decode[54].instruction, "istore");
  decode[54].bytes = 1;
  decode[54].referencesCP = 0;

  strcpy(decode[55].instruction, "lstore");
  decode[55].bytes = 1;
  decode[55].referencesCP = 0;

  strcpy(decode[56].instruction, "fstore");
  decode[56].bytes = 1;
  decode[56].referencesCP = 0;

  strcpy(decode[57].instruction, "dstore");
  decode[57].bytes = 1;
  decode[57].referencesCP = 0;

  strcpy(decode[58].instruction, "astore");
  decode[58].bytes = 1;
  decode[58].referencesCP = 0;

  strcpy(decode[59].instruction, "istore_0");
  decode[59].bytes = 0;
  decode[59].referencesCP = 0;

  strcpy(decode[60].instruction, "istore_1");
  decode[60].bytes = 0;
  decode[60].referencesCP = 0;

  strcpy(decode[61].instruction, "istore_2");
  decode[61].bytes = 0;
  decode[61].referencesCP = 0;

  strcpy(decode[62].instruction, "istore_3");
  decode[62].bytes = 0;
  decode[62].referencesCP = 0;

  strcpy(decode[63].instruction, "lstore_0");
  decode[63].bytes = 0;
  decode[63].referencesCP = 0;

  strcpy(decode[64].instruction, "lstore_1");
  decode[64].bytes = 0;
  decode[64].referencesCP = 0;

  strcpy(decode[65].instruction, "lstore_2");
  decode[65].bytes = 0;
  decode[65].referencesCP = 0;

  strcpy(decode[66].instruction, "lstore_3");
  decode[66].bytes = 0;
  decode[66].referencesCP = 0;

  strcpy(decode[67].instruction, "fstore_0");
  decode[67].bytes = 0;
  decode[67].referencesCP = 0;

  strcpy(decode[68].instruction, "fstore_1");
  decode[68].bytes = 0;
  decode[68].referencesCP = 0;

  strcpy(decode[69].instruction, "fstore_2");
  decode[69].bytes = 0;
  decode[69].referencesCP = 0;

  strcpy(decode[70].instruction, "fstore_3");
  decode[70].bytes = 0;
  decode[70].referencesCP = 0;

  strcpy(decode[71].instruction, "dstore_0");
  decode[71].bytes = 0;
  decode[71].referencesCP = 0;

  strcpy(decode[72].instruction, "dstore_1");
  decode[72].bytes = 0;
  decode[72].referencesCP = 0;

  strcpy(decode[73].instruction, "dstore_2");
  decode[73].bytes = 0;
  decode[73].referencesCP = 0;

  strcpy(decode[74].instruction, "dstore_3");
  decode[74].bytes = 0;
  decode[74].referencesCP = 0;

  strcpy(decode[75].instruction, "astore_0");
  decode[75].bytes = 0;
  decode[75].referencesCP = 0;

  strcpy(decode[76].instruction, "astore_1");
  decode[76].bytes = 0;
  decode[76].referencesCP = 0;

  strcpy(decode[77].instruction, "astore_2");
  decode[77].bytes = 0;
  decode[77].referencesCP = 0;

  strcpy(decode[78].instruction, "astore_3");
  decode[78].bytes = 0;
  decode[78].referencesCP = 0;

  strcpy(decode[79].instruction, "iastore");
  decode[79].bytes = 0;
  decode[79].referencesCP = 0;

  strcpy(decode[80].instruction, "lastore");
  decode[80].bytes = 0;
  decode[80].referencesCP = 0;

  strcpy(decode[81].instruction, "fastore");
  decode[81].bytes = 0;
  decode[81].referencesCP = 0;

  strcpy(decode[82].instruction, "dastore");
  decode[82].bytes = 0;
  decode[82].referencesCP = 0;

  strcpy(decode[83].instruction, "aastore");
  decode[83].bytes = 0;
  decode[83].referencesCP = 0;

  strcpy(decode[84].instruction, "bastore");
  decode[84].bytes = 0;
  decode[84].referencesCP = 0;

  strcpy(decode[85].instruction, "castore");
  decode[85].bytes = 0;
  decode[85].referencesCP = 0;

  strcpy(decode[86].instruction, "sastore");
  decode[86].bytes = 0;
  decode[86].referencesCP = 0;

  strcpy(decode[87].instruction, "pop");
  decode[87].bytes = 0;
  decode[87].referencesCP = 0;

  strcpy(decode[88].instruction, "pop2");
  decode[88].bytes = 0;
  decode[88].referencesCP = 0;

  strcpy(decode[89].instruction, "dup");
  decode[89].bytes = 0;
  decode[89].referencesCP = 0;

  strcpy(decode[90].instruction, "dup_x1");
  decode[90].bytes = 0;
  decode[90].referencesCP = 0;

  strcpy(decode[91].instruction, "dup_x2");
  decode[91].bytes = 0;
  decode[91].referencesCP = 0;

  strcpy(decode[92].instruction, "dup2");
  decode[92].bytes = 0;
  decode[92].referencesCP = 0;

  strcpy(decode[93].instruction, "dup2_x1");
  decode[93].bytes = 0;
  decode[93].referencesCP = 0;

  strcpy(decode[94].instruction, "dup2_x2");
  decode[94].bytes = 0;
  decode[94].referencesCP = 0;

  strcpy(decode[95].instruction, "swap");
  decode[95].bytes = 0;
  decode[95].referencesCP = 0;

  strcpy(decode[96].instruction, "iadd");
  decode[96].bytes = 0;
  decode[96].referencesCP = 0;

  strcpy(decode[97].instruction, "ladd");
  decode[97].bytes = 0;
  decode[97].referencesCP = 0;

  strcpy(decode[98].instruction, "fadd");
  decode[98].bytes = 0;
  decode[98].referencesCP = 0;

  strcpy(decode[99].instruction, "dadd");
  decode[99].bytes = 0;
  decode[99].referencesCP = 0;

  strcpy(decode[100].instruction, "isub");
  decode[100].bytes = 0;
  decode[100].referencesCP = 0;

  strcpy(decode[101].instruction, "lsub");
  decode[101].bytes = 0;
  decode[101].referencesCP = 0;

  strcpy(decode[102].instruction, "fsub");
  decode[102].bytes = 0;
  decode[102].referencesCP = 0;

  strcpy(decode[103].instruction, "dsub");
  decode[103].bytes = 0;
  decode[103].referencesCP = 0;

  strcpy(decode[104].instruction, "imul");
  decode[104].bytes = 0;
  decode[104].referencesCP = 0;

  strcpy(decode[105].instruction, "lmul");
  decode[105].bytes = 0;
  decode[105].referencesCP = 0;

  strcpy(decode[106].instruction, "fmul");
  decode[106].bytes = 0;
  decode[106].referencesCP = 0;

  strcpy(decode[107].instruction, "dmul");
  decode[107].bytes = 0;
  decode[107].referencesCP = 0;

  strcpy(decode[108].instruction, "idiv");
  decode[108].bytes = 0;
  decode[108].referencesCP = 0;

  strcpy(decode[109].instruction, "ldiv");
  decode[109].bytes = 0;
  decode[109].referencesCP = 0;

  strcpy(decode[110].instruction, "fdiv");
  decode[110].bytes = 0;
  decode[110].referencesCP = 0;

  strcpy(decode[111].instruction, "ddiv");
  decode[111].bytes = 0;
  decode[111].referencesCP = 0;

  strcpy(decode[112].instruction, "irem");
  decode[112].bytes = 0;
  decode[112].referencesCP = 0;

  strcpy(decode[113].instruction, "lrem");
  decode[113].bytes = 0;
  decode[113].referencesCP = 0;

  strcpy(decode[114].instruction, "frem");
  decode[114].bytes = 0;
  decode[114].referencesCP = 0;

  strcpy(decode[115].instruction, "drem");
  decode[115].bytes = 0;
  decode[115].referencesCP = 0;

  strcpy(decode[116].instruction, "ineg");
  decode[116].bytes = 0;
  decode[116].referencesCP = 0;

  strcpy(decode[117].instruction, "lneg");
  decode[117].bytes = 0;
  decode[117].referencesCP = 0;

  strcpy(decode[118].instruction, "fneg");
  decode[118].bytes = 0;
  decode[118].referencesCP = 0;

  strcpy(decode[119].instruction, "dneg");
  decode[119].bytes = 0;
  decode[119].referencesCP = 0;

  strcpy(decode[120].instruction, "ishl");
  decode[120].bytes = 0;
  decode[120].referencesCP = 0;

  strcpy(decode[121].instruction, "lshl");
  decode[121].bytes = 0;
  decode[121].referencesCP = 0;

  strcpy(decode[122].instruction, "ishr");
  decode[122].bytes = 0;
  decode[122].referencesCP = 0;

  strcpy(decode[123].instruction, "lshr");
  decode[123].bytes = 0;
  decode[123].referencesCP = 0;

  strcpy(decode[124].instruction, "iushr");
  decode[124].bytes = 0;
  decode[124].referencesCP = 0;

  strcpy(decode[125].instruction, "lushr");
  decode[125].bytes = 0;
  decode[125].referencesCP = 0;

  strcpy(decode[126].instruction, "iand");
  decode[126].bytes = 0;
  decode[126].referencesCP = 0;

  strcpy(decode[127].instruction, "land");
  decode[127].bytes = 0;
  decode[127].referencesCP = 0;

  strcpy(decode[128].instruction, "ior");
  decode[128].bytes = 0;
  decode[128].referencesCP = 0;

  strcpy(decode[129].instruction, "lor");
  decode[129].bytes = 0;
  decode[129].referencesCP = 0;

  strcpy(decode[130].instruction, "ixor");
  decode[130].bytes = 0;
  decode[130].referencesCP = 0;

  strcpy(decode[131].instruction, "lxor");
  decode[131].bytes = 0;
  decode[131].referencesCP = 0;

  strcpy(decode[132].instruction, "iinc");
  decode[132].bytes = 2;
  decode[132].referencesCP = 0;

  strcpy(decode[133].instruction, "i2l");
  decode[133].bytes = 0;
  decode[133].referencesCP = 0;

  strcpy(decode[134].instruction, "i2f");
  decode[134].bytes = 0;
  decode[134].referencesCP = 0;

  strcpy(decode[135].instruction, "i2d");
  decode[135].bytes = 0;
  decode[135].referencesCP = 0;

  strcpy(decode[136].instruction, "l2i");
  decode[136].bytes = 0;
  decode[136].referencesCP = 0;

  strcpy(decode[137].instruction, "l2f");
  decode[137].bytes = 0;
  decode[137].referencesCP = 0;

  strcpy(decode[138].instruction, "l2d");
  decode[138].bytes = 0;
  decode[138].referencesCP = 0;

  strcpy(decode[139].instruction, "f2i");
  decode[139].bytes = 0;
  decode[139].referencesCP = 0;

  strcpy(decode[140].instruction, "f2l");
  decode[140].bytes = 0;
  decode[140].referencesCP = 0;

  strcpy(decode[141].instruction, "f2d");
  decode[141].bytes = 0;
  decode[141].referencesCP = 0;

  strcpy(decode[142].instruction, "d2i");
  decode[142].bytes = 0;
  decode[142].referencesCP = 0;

  strcpy(decode[143].instruction, "d2l");
  decode[143].bytes = 0;
  decode[143].referencesCP = 0;

  strcpy(decode[144].instruction, "d2f");
  decode[144].bytes = 0;
  decode[144].referencesCP = 0;

  strcpy(decode[145].instruction, "i2b");
  decode[145].bytes = 0;
  decode[145].referencesCP = 0;

  strcpy(decode[146].instruction, "i2c");
  decode[146].bytes = 0;
  decode[146].referencesCP = 0;

  strcpy(decode[147].instruction, "i2s");
  decode[147].bytes = 0;
  decode[146].referencesCP = 0;

  strcpy(decode[148].instruction, "lcmp");
  decode[148].bytes = 0;
  decode[148].referencesCP = 0;

  strcpy(decode[149].instruction, "fcmpl");
  decode[149].bytes = 0;
  decode[149].referencesCP = 0;

  strcpy(decode[150].instruction, "fcmpg");
  decode[150].bytes = 0;
  decode[150].referencesCP = 0;

  strcpy(decode[151].instruction, "dcmpl");
  decode[151].bytes = 0;
  decode[151].referencesCP = 0;

  strcpy(decode[152].instruction, "dcmpg");
  decode[152].bytes = 0;
  decode[152].referencesCP = 0;

  strcpy(decode[153].instruction, "ifeq");
  decode[153].bytes = 2;
  decode[153].referencesCP = 0;

  strcpy(decode[154].instruction, "ifne");
  decode[154].bytes = 2;
  decode[154].referencesCP = 0;

  strcpy(decode[155].instruction, "iflt");
  decode[155].bytes = 2;
  decode[155].referencesCP = 0;

  strcpy(decode[156].instruction, "ifge");
  decode[156].bytes = 2;
  decode[156].referencesCP = 0;

  strcpy(decode[157].instruction, "ifgt");
  decode[157].bytes = 2;
  decode[157].referencesCP = 0;

  strcpy(decode[158].instruction, "ifle");
  decode[158].bytes = 2;
  decode[158].referencesCP = 0;

  strcpy(decode[159].instruction, "if_icmpeq");
  decode[159].bytes = 2;
  decode[159].referencesCP = 0;

  strcpy(decode[160].instruction, "if_icmpne");
  decode[160].bytes = 2;
  decode[160].referencesCP = 0;

  strcpy(decode[161].instruction, "if_icmplt");
  decode[161].bytes = 2;
  decode[161].referencesCP = 0;

  strcpy(decode[162].instruction, "if_icmpg2");
  decode[162].bytes = 2;
  decode[162].referencesCP = 0;

  strcpy(decode[163].instruction, "if_icmpgt");
  decode[163].bytes = 2;
  decode[163].referencesCP = 0;

  strcpy(decode[164].instruction, "if_icmple");
  decode[164].bytes = 2;
  decode[164].referencesCP = 0;

  strcpy(decode[165].instruction, "if_acmpeq");
  decode[165].bytes = 2;
  decode[165].referencesCP = 0;

  strcpy(decode[166].instruction, "if_acmpne");
  decode[166].bytes = 2;
  decode[166].referencesCP = 0;

  strcpy(decode[167].instruction, "goto");
  decode[167].bytes = 2;
  decode[167].referencesCP = 0;

  strcpy(decode[168].instruction, "jsr");
  decode[168].bytes = 2;
  decode[168].referencesCP = 0;

  strcpy(decode[169].instruction, "ret");
  decode[169].bytes = 1;
  decode[169].referencesCP = 0;

  strcpy(decode[170].instruction, INSTR_TABLESWITCH);
  // instrução tem tamanho variável
  decode[170].bytes = 34;
  decode[170].referencesCP = 0;

  strcpy(decode[171].instruction, INSTR_LOOKUPSWITCH);
  // instrução tem tamanho variável
  decode[171].bytes = 26;
  decode[171].referencesCP = 0;

  strcpy(decode[172].instruction, "ireturn");
  decode[172].bytes = 0;
  decode[172].referencesCP = 0;

  strcpy(decode[173].instruction, "lreturn");
  decode[173].bytes = 0;
  decode[173].referencesCP = 0;

  strcpy(decode[174].instruction, "freturn");
  decode[174].bytes = 0;
  decode[174].referencesCP = 0;

  strcpy(decode[175].instruction, "dreturn");
  decode[175].bytes = 0;
  decode[175].referencesCP = 0;

  strcpy(decode[176].instruction, "areturn");
  decode[176].bytes = 0;
  decode[176].referencesCP = 0;

  strcpy(decode[177].instruction, "return");
  decode[177].bytes = 0;
  decode[177].referencesCP = 0;

  strcpy(decode[178].instruction, "getstatic");
  decode[178].bytes = 2;
  decode[178].referencesCP = 1;

  strcpy(decode[179].instruction, "putstatic");
  decode[179].bytes = 2;
  decode[179].referencesCP = 1;

  strcpy(decode[180].instruction, "getfield");
  decode[180].bytes = 2;
  decode[180].referencesCP = 1;

  strcpy(decode[181].instruction, "putfield");
  decode[181].bytes = 2;
  decode[181].referencesCP = 1;

  strcpy(decode[182].instruction, "invokevirtual");
  decode[182].bytes = 2;
  decode[182].referencesCP = 1;

  strcpy(decode[183].instruction, "invokespecial");
  decode[183].bytes = 2;
  decode[183].referencesCP = 1;

  strcpy(decode[184].instruction, "invokestatic");
  decode[184].bytes = 2;
  decode[184].referencesCP = 1;

  strcpy(decode[185].instruction, "invokeinterface");
  decode[185].bytes = 4;
  decode[185].referencesCP = 1;

  strcpy(decode[186].instruction, "invokedynamic");
  decode[186].bytes = 4;
  decode[186].referencesCP = 1;

  strcpy(decode[187].instruction, "new");
  decode[187].bytes = 2;
  decode[187].referencesCP = 1;

  strcpy(decode[188].instruction, "newarray");
  decode[188].bytes = 1;
  decode[188].referencesCP = 0;

  strcpy(decode[189].instruction, "anewarray");
  decode[189].bytes = 2;
  decode[189].referencesCP = 1;

  strcpy(decode[190].instruction, "arraylength");
  decode[190].bytes = 0;
  decode[190].referencesCP = 0;

  strcpy(decode[191].instruction, "athrow");
  decode[191].bytes = 0;
  decode[191].referencesCP = 0;

  strcpy(decode[192].instruction, "checkcast");
  decode[192].bytes = 2;
  decode[192].referencesCP = 1;

  strcpy(decode[193].instruction, "instanceof");
  decode[193].bytes = 2;
  decode[193].referencesCP = 1;

  strcpy(decode[194].instruction, "monitorenter");
  decode[194].bytes = 0;
  decode[194].referencesCP = 0;

  strcpy(decode[195].instruction, "monitorexit");
  decode[195].bytes = 0;
  decode[195].referencesCP = 0;

  strcpy(decode[196].instruction, "wide");
  decode[196].bytes = 3;
  decode[196].referencesCP = 0;

  strcpy(decode[197].instruction, "multianewarray");
  decode[197].bytes = 3;
  decode[197].referencesCP = 1;

  strcpy(decode[198].instruction, "ifnull");
  decode[198].bytes = 2;
  decode[198].referencesCP = 0;

  strcpy(decode[199].instruction, "ifnonnull");
  decode[199].bytes = 2;
  decode[199].referencesCP = 0;

  strcpy(decode[200].instruction, "goto_w");
  decode[200].bytes = 4;
  decode[200].referencesCP = 0;

  strcpy(decode[201].instruction, "jsr_w");
  decode[201].bytes = 4;
  decode[201].referencesCP = 0;


  // reservados
  strcpy(decode[202].instruction, "breakpoint");
  decode[200].bytes = 0;

  strcpy(decode[254].instruction, "impdep1");
  decode[254].bytes = 0;

  strcpy(decode[255].instruction, "impdep2");
  decode[255].bytes = 0;



}
