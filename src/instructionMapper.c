#include "instructionMapper.h"

const char *INSTR_TABLESWITCH = "tableswitch";
const char *INSTR_LOOKUPSWITCH = "lookupswitch";

void initMapper() {
  strcpy(mapper[0].instruction, "nop");
  mapper[0].bytes = 0;

  strcpy(mapper[1].instruction, "aconst_null");
  mapper[1].bytes = 0;
  mapper[1].referencesCP = 0;

  strcpy(mapper[2].instruction, "iconst_m1");
  mapper[2].bytes = 0;
  mapper[2].referencesCP = 0;

  strcpy(mapper[3].instruction, "iconst_0");
  mapper[3].bytes = 0;
  mapper[3].referencesCP = 0;

  strcpy(mapper[4].instruction, "iconst_1");
  mapper[4].bytes = 0;
  mapper[4].referencesCP = 0;

  strcpy(mapper[5].instruction, "iconst_2");
  mapper[5].bytes = 0;
  mapper[5].referencesCP = 0;

  strcpy(mapper[6].instruction, "iconst_3");
  mapper[6].bytes = 0;
  mapper[6].referencesCP = 0;

  strcpy(mapper[7].instruction, "iconst_4");
  mapper[7].bytes = 0;
  mapper[7].referencesCP = 0;

  strcpy(mapper[8].instruction, "iconst_5");
  mapper[8].bytes = 0;
  mapper[8].referencesCP = 0;

  strcpy(mapper[9].instruction, "lconst_0");
  mapper[9].bytes = 0;
  mapper[9].referencesCP = 0;

  strcpy(mapper[10].instruction, "lconst_1");
  mapper[10].bytes = 0;
  mapper[10].referencesCP = 0;

  strcpy(mapper[11].instruction, "fconst_0");
  mapper[11].bytes = 0;
  mapper[11].referencesCP = 0;

  strcpy(mapper[12].instruction, "fconst_1");
  mapper[12].bytes = 0;
  mapper[12].referencesCP = 0;

  strcpy(mapper[13].instruction, "fconst_2");
  mapper[13].bytes = 0;
  mapper[13].referencesCP = 0;

  strcpy(mapper[14].instruction, "dconst_0");
  mapper[14].bytes = 0;
  mapper[14].referencesCP = 0;

  strcpy(mapper[15].instruction, "dconst_1");
  mapper[15].bytes = 0;
  mapper[15].referencesCP = 0;

  strcpy(mapper[16].instruction, "bipush");
  mapper[16].bytes = 1;
  mapper[16].referencesCP = 0;

  strcpy(mapper[17].instruction, "sipush");
  mapper[17].bytes = 2;
  mapper[17].referencesCP = 0;

  strcpy(mapper[18].instruction, "ldc");
  mapper[18].bytes = 1;
  mapper[18].referencesCP = 1;

  strcpy(mapper[19].instruction, "ldc_w");
  mapper[19].bytes = 2;
  mapper[19].referencesCP = 1;

  strcpy(mapper[20].instruction, "ldc2_w");
  mapper[20].bytes = 2;
  mapper[20].referencesCP = 1;

  strcpy(mapper[21].instruction, "iload");
  mapper[21].bytes = 1;
  mapper[21].referencesCP = 0;

  strcpy(mapper[22].instruction, "lload");
  mapper[22].bytes = 1;
  mapper[22].referencesCP = 0;

  strcpy(mapper[23].instruction, "fload");
  mapper[23].bytes = 1;
  mapper[23].referencesCP = 0;

  strcpy(mapper[24].instruction, "dload");
  mapper[24].bytes = 1;
  mapper[24].referencesCP = 0;

  strcpy(mapper[25].instruction, "aload");
  mapper[25].bytes = 1;
  mapper[25].referencesCP = 0;

  strcpy(mapper[26].instruction, "iload_0");
  mapper[26].bytes = 0;
  mapper[26].referencesCP = 0;

  strcpy(mapper[27].instruction, "iload_1");
  mapper[27].bytes = 0;
  mapper[27].referencesCP = 0;

  strcpy(mapper[28].instruction, "iload_2");
  mapper[28].bytes = 0;
  mapper[28].referencesCP = 0;

  strcpy(mapper[29].instruction, "iload_3");
  mapper[29].bytes = 0;
  mapper[29].referencesCP = 0;

  strcpy(mapper[30].instruction, "lload_0");
  mapper[30].bytes = 0;
  mapper[30].referencesCP = 0;

  strcpy(mapper[31].instruction, "lload_1");
  mapper[31].bytes = 0;
  mapper[31].referencesCP = 0;

  strcpy(mapper[32].instruction, "lload_2");
  mapper[32].bytes = 0;
  mapper[32].referencesCP = 0;

  strcpy(mapper[33].instruction, "lload_3");
  mapper[33].bytes = 0;
  mapper[33].referencesCP = 0;

  strcpy(mapper[34].instruction, "fload_0");
  mapper[34].bytes = 0;
  mapper[34].referencesCP = 0;

  strcpy(mapper[35].instruction, "fload_1");
  mapper[35].bytes = 0;
  mapper[35].referencesCP = 0;

  strcpy(mapper[36].instruction, "fload_2");
  mapper[36].bytes = 0;
  mapper[36].referencesCP = 0;

  strcpy(mapper[37].instruction, "fload_3");
  mapper[37].bytes = 0;
  mapper[37].referencesCP = 0;

  strcpy(mapper[38].instruction, "dload_0");
  mapper[38].bytes = 0;
  mapper[38].referencesCP = 0;

  strcpy(mapper[39].instruction, "dload_1");
  mapper[39].bytes = 0;
  mapper[39].referencesCP = 0;

  strcpy(mapper[40].instruction, "dload_2");
  mapper[40].bytes = 0;
  mapper[40].referencesCP = 0;

  strcpy(mapper[41].instruction, "dload_3");
  mapper[41].bytes = 0;
  mapper[41].referencesCP = 0;

  strcpy(mapper[42].instruction, "aload_0");
  mapper[42].bytes = 0;
  mapper[42].referencesCP = 0;

  strcpy(mapper[43].instruction, "aload_1");
  mapper[43].bytes = 0;
  mapper[43].referencesCP = 0;

  strcpy(mapper[44].instruction, "aload_2");
  mapper[44].bytes = 0;
  mapper[40].referencesCP = 0;

  strcpy(mapper[45].instruction, "aload_3");
  mapper[45].bytes = 0;
  mapper[45].referencesCP = 0;

  strcpy(mapper[46].instruction, "iaload");
  mapper[46].bytes = 0;
  mapper[46].referencesCP = 0;

  strcpy(mapper[47].instruction, "laload");
  mapper[47].bytes = 0;
  mapper[47].referencesCP = 0;

  strcpy(mapper[48].instruction, "faload");
  mapper[48].bytes = 0;
  mapper[48].referencesCP = 0;

  strcpy(mapper[49].instruction, "daload");
  mapper[49].bytes = 0;
  mapper[49].referencesCP = 0;

  strcpy(mapper[50].instruction, "aaload");
  mapper[50].bytes = 0;
  mapper[50].referencesCP = 0;

  strcpy(mapper[51].instruction, "baload");
  mapper[51].bytes = 0;
  mapper[51].referencesCP = 0;

  strcpy(mapper[52].instruction, "caload");
  mapper[52].bytes = 0;
  mapper[52].referencesCP = 0;

  strcpy(mapper[53].instruction, "saload");
  mapper[53].bytes = 0;
  mapper[53].referencesCP = 0;

  strcpy(mapper[54].instruction, "istore");
  mapper[54].bytes = 1;
  mapper[54].referencesCP = 0;

  strcpy(mapper[55].instruction, "lstore");
  mapper[55].bytes = 1;
  mapper[55].referencesCP = 0;

  strcpy(mapper[56].instruction, "fstore");
  mapper[56].bytes = 1;
  mapper[56].referencesCP = 0;

  strcpy(mapper[57].instruction, "dstore");
  mapper[57].bytes = 1;
  mapper[57].referencesCP = 0;

  strcpy(mapper[58].instruction, "astore");
  mapper[58].bytes = 1;
  mapper[58].referencesCP = 0;

  strcpy(mapper[59].instruction, "istore_0");
  mapper[59].bytes = 0;
  mapper[59].referencesCP = 0;

  strcpy(mapper[60].instruction, "istore_1");
  mapper[60].bytes = 0;
  mapper[60].referencesCP = 0;

  strcpy(mapper[61].instruction, "istore_2");
  mapper[61].bytes = 0;
  mapper[61].referencesCP = 0;

  strcpy(mapper[62].instruction, "istore_3");
  mapper[62].bytes = 0;
  mapper[62].referencesCP = 0;

  strcpy(mapper[63].instruction, "lstore_0");
  mapper[63].bytes = 0;
  mapper[63].referencesCP = 0;

  strcpy(mapper[64].instruction, "lstore_1");
  mapper[64].bytes = 0;
  mapper[64].referencesCP = 0;

  strcpy(mapper[65].instruction, "lstore_2");
  mapper[65].bytes = 0;
  mapper[65].referencesCP = 0;

  strcpy(mapper[66].instruction, "lstore_3");
  mapper[66].bytes = 0;
  mapper[66].referencesCP = 0;

  strcpy(mapper[67].instruction, "fstore_0");
  mapper[67].bytes = 0;
  mapper[67].referencesCP = 0;

  strcpy(mapper[68].instruction, "fstore_1");
  mapper[68].bytes = 0;
  mapper[68].referencesCP = 0;

  strcpy(mapper[69].instruction, "fstore_2");
  mapper[69].bytes = 0;
  mapper[69].referencesCP = 0;

  strcpy(mapper[70].instruction, "fstore_3");
  mapper[70].bytes = 0;
  mapper[70].referencesCP = 0;

  strcpy(mapper[71].instruction, "dstore_0");
  mapper[71].bytes = 0;
  mapper[71].referencesCP = 0;

  strcpy(mapper[72].instruction, "dstore_1");
  mapper[72].bytes = 0;
  mapper[72].referencesCP = 0;

  strcpy(mapper[73].instruction, "dstore_2");
  mapper[73].bytes = 0;
  mapper[73].referencesCP = 0;

  strcpy(mapper[74].instruction, "dstore_3");
  mapper[74].bytes = 0;
  mapper[74].referencesCP = 0;

  strcpy(mapper[75].instruction, "astore_0");
  mapper[75].bytes = 0;
  mapper[75].referencesCP = 0;

  strcpy(mapper[76].instruction, "astore_1");
  mapper[76].bytes = 0;
  mapper[76].referencesCP = 0;

  strcpy(mapper[77].instruction, "astore_2");
  mapper[77].bytes = 0;
  mapper[77].referencesCP = 0;

  strcpy(mapper[78].instruction, "astore_3");
  mapper[78].bytes = 0;
  mapper[78].referencesCP = 0;

  strcpy(mapper[79].instruction, "iastore");
  mapper[79].bytes = 0;
  mapper[79].referencesCP = 0;

  strcpy(mapper[80].instruction, "lastore");
  mapper[80].bytes = 0;
  mapper[80].referencesCP = 0;

  strcpy(mapper[81].instruction, "fastore");
  mapper[81].bytes = 0;
  mapper[81].referencesCP = 0;

  strcpy(mapper[82].instruction, "dastore");
  mapper[82].bytes = 0;
  mapper[82].referencesCP = 0;

  strcpy(mapper[83].instruction, "aastore");
  mapper[83].bytes = 0;
  mapper[83].referencesCP = 0;

  strcpy(mapper[84].instruction, "bastore");
  mapper[84].bytes = 0;
  mapper[84].referencesCP = 0;

  strcpy(mapper[85].instruction, "castore");
  mapper[85].bytes = 0;
  mapper[85].referencesCP = 0;

  strcpy(mapper[86].instruction, "sastore");
  mapper[86].bytes = 0;
  mapper[86].referencesCP = 0;

  strcpy(mapper[87].instruction, "pop");
  mapper[87].bytes = 0;
  mapper[87].referencesCP = 0;

  strcpy(mapper[88].instruction, "pop2");
  mapper[88].bytes = 0;
  mapper[88].referencesCP = 0;

  strcpy(mapper[89].instruction, "dup");
  mapper[89].bytes = 0;
  mapper[89].referencesCP = 0;

  strcpy(mapper[90].instruction, "dup_x1");
  mapper[90].bytes = 0;
  mapper[90].referencesCP = 0;

  strcpy(mapper[91].instruction, "dup_x2");
  mapper[91].bytes = 0;
  mapper[91].referencesCP = 0;

  strcpy(mapper[92].instruction, "dup2");
  mapper[92].bytes = 0;
  mapper[92].referencesCP = 0;

  strcpy(mapper[93].instruction, "dup2_x1");
  mapper[93].bytes = 0;
  mapper[93].referencesCP = 0;

  strcpy(mapper[94].instruction, "dup2_x2");
  mapper[94].bytes = 0;
  mapper[94].referencesCP = 0;

  strcpy(mapper[95].instruction, "swap");
  mapper[95].bytes = 0;
  mapper[95].referencesCP = 0;

  strcpy(mapper[96].instruction, "iadd");
  mapper[96].bytes = 0;
  mapper[96].referencesCP = 0;

  strcpy(mapper[97].instruction, "ladd");
  mapper[97].bytes = 0;
  mapper[97].referencesCP = 0;

  strcpy(mapper[98].instruction, "fadd");
  mapper[98].bytes = 0;
  mapper[98].referencesCP = 0;

  strcpy(mapper[99].instruction, "dadd");
  mapper[99].bytes = 0;
  mapper[99].referencesCP = 0;

  strcpy(mapper[100].instruction, "isub");
  mapper[100].bytes = 0;
  mapper[100].referencesCP = 0;

  strcpy(mapper[101].instruction, "lsub");
  mapper[101].bytes = 0;
  mapper[101].referencesCP = 0;

  strcpy(mapper[102].instruction, "fsub");
  mapper[102].bytes = 0;
  mapper[102].referencesCP = 0;

  strcpy(mapper[103].instruction, "dsub");
  mapper[103].bytes = 0;
  mapper[103].referencesCP = 0;

  strcpy(mapper[104].instruction, "imul");
  mapper[104].bytes = 0;
  mapper[104].referencesCP = 0;

  strcpy(mapper[105].instruction, "lmul");
  mapper[105].bytes = 0;
  mapper[105].referencesCP = 0;

  strcpy(mapper[106].instruction, "fmul");
  mapper[106].bytes = 0;
  mapper[106].referencesCP = 0;

  strcpy(mapper[107].instruction, "dmul");
  mapper[107].bytes = 0;
  mapper[107].referencesCP = 0;

  strcpy(mapper[108].instruction, "idiv");
  mapper[108].bytes = 0;
  mapper[108].referencesCP = 0;

  strcpy(mapper[109].instruction, "ldiv");
  mapper[109].bytes = 0;
  mapper[109].referencesCP = 0;

  strcpy(mapper[110].instruction, "fdiv");
  mapper[110].bytes = 0;
  mapper[110].referencesCP = 0;

  strcpy(mapper[111].instruction, "ddiv");
  mapper[111].bytes = 0;
  mapper[111].referencesCP = 0;

  strcpy(mapper[112].instruction, "irem");
  mapper[112].bytes = 0;
  mapper[112].referencesCP = 0;

  strcpy(mapper[113].instruction, "lrem");
  mapper[113].bytes = 0;
  mapper[113].referencesCP = 0;

  strcpy(mapper[114].instruction, "frem");
  mapper[114].bytes = 0;
  mapper[114].referencesCP = 0;

  strcpy(mapper[115].instruction, "drem");
  mapper[115].bytes = 0;
  mapper[115].referencesCP = 0;

  strcpy(mapper[116].instruction, "ineg");
  mapper[116].bytes = 0;
  mapper[116].referencesCP = 0;

  strcpy(mapper[117].instruction, "lneg");
  mapper[117].bytes = 0;
  mapper[117].referencesCP = 0;

  strcpy(mapper[118].instruction, "fneg");
  mapper[118].bytes = 0;
  mapper[118].referencesCP = 0;

  strcpy(mapper[119].instruction, "dneg");
  mapper[119].bytes = 0;
  mapper[119].referencesCP = 0;

  strcpy(mapper[120].instruction, "ishl");
  mapper[120].bytes = 0;
  mapper[120].referencesCP = 0;

  strcpy(mapper[121].instruction, "lshl");
  mapper[121].bytes = 0;
  mapper[121].referencesCP = 0;

  strcpy(mapper[122].instruction, "ishr");
  mapper[122].bytes = 0;
  mapper[122].referencesCP = 0;

  strcpy(mapper[123].instruction, "lshr");
  mapper[123].bytes = 0;
  mapper[123].referencesCP = 0;

  strcpy(mapper[124].instruction, "iushr");
  mapper[124].bytes = 0;
  mapper[124].referencesCP = 0;

  strcpy(mapper[125].instruction, "lushr");
  mapper[125].bytes = 0;
  mapper[125].referencesCP = 0;

  strcpy(mapper[126].instruction, "iand");
  mapper[126].bytes = 0;
  mapper[126].referencesCP = 0;

  strcpy(mapper[127].instruction, "land");
  mapper[127].bytes = 0;
  mapper[127].referencesCP = 0;

  strcpy(mapper[128].instruction, "ior");
  mapper[128].bytes = 0;
  mapper[128].referencesCP = 0;

  strcpy(mapper[129].instruction, "lor");
  mapper[129].bytes = 0;
  mapper[129].referencesCP = 0;

  strcpy(mapper[130].instruction, "ixor");
  mapper[130].bytes = 0;
  mapper[130].referencesCP = 0;

  strcpy(mapper[131].instruction, "lxor");
  mapper[131].bytes = 0;
  mapper[131].referencesCP = 0;

  strcpy(mapper[132].instruction, "iinc");
  mapper[132].bytes = 2;
  mapper[132].referencesCP = 0;

  strcpy(mapper[133].instruction, "i2l");
  mapper[133].bytes = 0;
  mapper[133].referencesCP = 0;

  strcpy(mapper[134].instruction, "i2f");
  mapper[134].bytes = 0;
  mapper[134].referencesCP = 0;

  strcpy(mapper[135].instruction, "i2d");
  mapper[135].bytes = 0;
  mapper[135].referencesCP = 0;

  strcpy(mapper[136].instruction, "l2i");
  mapper[136].bytes = 0;
  mapper[136].referencesCP = 0;

  strcpy(mapper[137].instruction, "l2f");
  mapper[137].bytes = 0;
  mapper[137].referencesCP = 0;

  strcpy(mapper[138].instruction, "l2d");
  mapper[138].bytes = 0;
  mapper[138].referencesCP = 0;

  strcpy(mapper[139].instruction, "f2i");
  mapper[139].bytes = 0;
  mapper[139].referencesCP = 0;

  strcpy(mapper[140].instruction, "f2l");
  mapper[140].bytes = 0;
  mapper[140].referencesCP = 0;

  strcpy(mapper[141].instruction, "f2d");
  mapper[141].bytes = 0;
  mapper[141].referencesCP = 0;

  strcpy(mapper[142].instruction, "d2i");
  mapper[142].bytes = 0;
  mapper[142].referencesCP = 0;

  strcpy(mapper[143].instruction, "d2l");
  mapper[143].bytes = 0;
  mapper[143].referencesCP = 0;

  strcpy(mapper[144].instruction, "d2f");
  mapper[144].bytes = 0;
  mapper[144].referencesCP = 0;

  strcpy(mapper[145].instruction, "i2b");
  mapper[145].bytes = 0;
  mapper[145].referencesCP = 0;

  strcpy(mapper[146].instruction, "i2c");
  mapper[146].bytes = 0;
  mapper[146].referencesCP = 0;

  strcpy(mapper[147].instruction, "i2s");
  mapper[147].bytes = 0;
  mapper[146].referencesCP = 0;

  strcpy(mapper[148].instruction, "lcmp");
  mapper[148].bytes = 0;
  mapper[148].referencesCP = 0;

  strcpy(mapper[149].instruction, "fcmpl");
  mapper[149].bytes = 0;
  mapper[149].referencesCP = 0;

  strcpy(mapper[150].instruction, "fcmpg");
  mapper[150].bytes = 0;
  mapper[150].referencesCP = 0;

  strcpy(mapper[151].instruction, "dcmpl");
  mapper[151].bytes = 0;
  mapper[151].referencesCP = 0;

  strcpy(mapper[152].instruction, "dcmpg");
  mapper[152].bytes = 0;
  mapper[152].referencesCP = 0;

  strcpy(mapper[153].instruction, "ifeq");
  mapper[153].bytes = 2;
  mapper[153].referencesCP = 0;

  strcpy(mapper[154].instruction, "ifne");
  mapper[154].bytes = 2;
  mapper[154].referencesCP = 0;

  strcpy(mapper[155].instruction, "iflt");
  mapper[155].bytes = 2;
  mapper[155].referencesCP = 0;

  strcpy(mapper[156].instruction, "ifge");
  mapper[156].bytes = 2;
  mapper[156].referencesCP = 0;

  strcpy(mapper[157].instruction, "ifgt");
  mapper[157].bytes = 2;
  mapper[157].referencesCP = 0;

  strcpy(mapper[158].instruction, "ifle");
  mapper[158].bytes = 2;
  mapper[158].referencesCP = 0;

  strcpy(mapper[159].instruction, "if_icmpeq");
  mapper[159].bytes = 2;
  mapper[159].referencesCP = 0;

  strcpy(mapper[160].instruction, "if_icmpne");
  mapper[160].bytes = 2;
  mapper[160].referencesCP = 0;

  strcpy(mapper[161].instruction, "if_icmplt");
  mapper[161].bytes = 2;
  mapper[161].referencesCP = 0;

  strcpy(mapper[162].instruction, "if_icmpg2");
  mapper[162].bytes = 2;
  mapper[162].referencesCP = 0;

  strcpy(mapper[163].instruction, "if_icmpgt");
  mapper[163].bytes = 2;
  mapper[163].referencesCP = 0;

  strcpy(mapper[164].instruction, "if_icmple");
  mapper[164].bytes = 2;
  mapper[164].referencesCP = 0;

  strcpy(mapper[165].instruction, "if_acmpeq");
  mapper[165].bytes = 2;
  mapper[165].referencesCP = 0;

  strcpy(mapper[166].instruction, "if_acmpne");
  mapper[166].bytes = 2;
  mapper[166].referencesCP = 0;

  strcpy(mapper[167].instruction, "goto");
  mapper[167].bytes = 2;
  mapper[167].referencesCP = 0;

  strcpy(mapper[168].instruction, "jsr");
  mapper[168].bytes = 2;
  mapper[168].referencesCP = 0;

  strcpy(mapper[169].instruction, "ret");
  mapper[169].bytes = 1;
  mapper[169].referencesCP = 0;

  strcpy(mapper[170].instruction, INSTR_TABLESWITCH);
  // instrução tem tamanho variável
  mapper[170].bytes = 34;
  mapper[170].referencesCP = 0;

  strcpy(mapper[171].instruction, INSTR_LOOKUPSWITCH);
  // instrução tem tamanho variável
  mapper[171].bytes = 26;
  mapper[171].referencesCP = 0;

  strcpy(mapper[172].instruction, "ireturn");
  mapper[172].bytes = 0;
  mapper[172].referencesCP = 0;

  strcpy(mapper[173].instruction, "lreturn");
  mapper[173].bytes = 0;
  mapper[173].referencesCP = 0;

  strcpy(mapper[174].instruction, "freturn");
  mapper[174].bytes = 0;
  mapper[174].referencesCP = 0;

  strcpy(mapper[175].instruction, "dreturn");
  mapper[175].bytes = 0;
  mapper[175].referencesCP = 0;

  strcpy(mapper[176].instruction, "areturn");
  mapper[176].bytes = 0;
  mapper[176].referencesCP = 0;

  strcpy(mapper[177].instruction, "return");
  mapper[177].bytes = 0;
  mapper[177].referencesCP = 0;

  strcpy(mapper[178].instruction, "getstatic");
  mapper[178].bytes = 2;
  mapper[178].referencesCP = 1;

  strcpy(mapper[179].instruction, "putstatic");
  mapper[179].bytes = 2;
  mapper[179].referencesCP = 1;

  strcpy(mapper[180].instruction, "getfield");
  mapper[180].bytes = 2;
  mapper[180].referencesCP = 1;

  strcpy(mapper[181].instruction, "putfield");
  mapper[181].bytes = 2;
  mapper[181].referencesCP = 1;

  strcpy(mapper[182].instruction, "invokevirtual");
  mapper[182].bytes = 2;
  mapper[182].referencesCP = 1;

  strcpy(mapper[183].instruction, "invokespecial");
  mapper[183].bytes = 2;
  mapper[183].referencesCP = 1;

  strcpy(mapper[184].instruction, "invokestatic");
  mapper[184].bytes = 2;
  mapper[184].referencesCP = 1;

  strcpy(mapper[185].instruction, "invokeinterface");
  mapper[185].bytes = 4;
  mapper[185].referencesCP = 1;

  strcpy(mapper[186].instruction, "invokedynamic");
  mapper[186].bytes = 4;
  mapper[186].referencesCP = 1;

  strcpy(mapper[187].instruction, "new");
  mapper[187].bytes = 2;
  mapper[187].referencesCP = 1;

  strcpy(mapper[188].instruction, "newarray");
  mapper[188].bytes = 1;
  mapper[188].referencesCP = 0;

  strcpy(mapper[189].instruction, "anewarray");
  mapper[189].bytes = 2;
  mapper[189].referencesCP = 1;

  strcpy(mapper[190].instruction, "arraylength");
  mapper[190].bytes = 0;
  mapper[190].referencesCP = 0;

  strcpy(mapper[191].instruction, "athrow");
  mapper[191].bytes = 0;
  mapper[191].referencesCP = 0;

  strcpy(mapper[192].instruction, "checkcast");
  mapper[192].bytes = 2;
  mapper[192].referencesCP = 1;

  strcpy(mapper[193].instruction, "instanceof");
  mapper[193].bytes = 2;
  mapper[193].referencesCP = 1;

  strcpy(mapper[194].instruction, "monitorenter");
  mapper[194].bytes = 0;
  mapper[194].referencesCP = 0;

  strcpy(mapper[195].instruction, "monitorexit");
  mapper[195].bytes = 0;
  mapper[195].referencesCP = 0;

  strcpy(mapper[196].instruction, "wide");
  mapper[196].bytes = 3;
  mapper[196].referencesCP = 0;

  strcpy(mapper[197].instruction, "multianewarray");
  mapper[197].bytes = 3;
  mapper[197].referencesCP = 1;

  strcpy(mapper[198].instruction, "ifnull");
  mapper[198].bytes = 2;
  mapper[198].referencesCP = 0;

  strcpy(mapper[199].instruction, "ifnonnull");
  mapper[199].bytes = 2;
  mapper[199].referencesCP = 0;

  strcpy(mapper[200].instruction, "goto_w");
  mapper[200].bytes = 4;
  mapper[200].referencesCP = 0;

  strcpy(mapper[201].instruction, "jsr_w");
  mapper[201].bytes = 4;
  mapper[201].referencesCP = 0;


  // reservados
  strcpy(mapper[202].instruction, "breakpoint");
  mapper[200].bytes = 0;

  strcpy(mapper[254].instruction, "impdep1");
  mapper[254].bytes = 0;

  strcpy(mapper[255].instruction, "impdep2");
  mapper[255].bytes = 0;



}
