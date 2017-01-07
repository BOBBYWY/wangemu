// this boot rom image came from the 6789 CPU I bought off of ebay.
// the three eproms were unlabeled and were in fact three different
// brands, making me think that perhaps this wasn't an official Wang set
// of eproms.  I'm not actually sure if these are for VP or MVP operation,
// but it works for both.

#include "ucode_2200.h"

uint32 ucode_2200vp[UCODE_WORDS_2200VP] = {
        0xDE2E80,       // 8000
        0x5C0100,       // 8001
        0xDE2780,       // 8002
        0x5D3480,       // 8003
        0xDC0410,       // 8004
        0x5C0528,       // 8005
        0x5C0680,       // 8006
        0xDC0780,       // 8007
        0xDC0880,       // 8008
        0x5C0980,       // 8009
        0x5C0A80,       // 800A
        0x5E4C80,       // 800B
        0xDC0C80,       // 800C
        0xDC8A80,       // 800D
        0xDD2E80,       // 800E
        0x5D3280,       // 800F
        0x208E0F,       // 8010
        0x68118D,       // 8011
        0x548380,       // 8012
        0x978200,       // 8013
        0xDC8380,       // 8014
        0x200F0F,       // 8015
        0x200009,       // 8016
        0x541980,       // 8017
        0xA00008,       // 8018
        0xA0C19F,       // 8019
        0x0C4201,       // 801A
        0x542080,       // 801B
        0x884201,       // 801C
        0xDC2080,       // 801D
        0x800000,       // 801E
        0x5C2480,       // 801F
        0xC82221,       // 8020
        0xAC0272,       // 8021
        0x200E02,       // 8022
        0x5C1180,       // 8023
        0x200EDF,       // 8024
        0xD41180,       // 8025
        0xA00EAF,       // 8026
        0x5C1180,       // 8027
        0xA00E09,       // 8028
        0xD41180,       // 8029
        0xD828F8,       // 802A
        0x87800F,       // 802B
        0xD41180,       // 802C
        0xA00E09,       // 802D
        0xD41180,       // 802E
        0x200E08,       // 802F
        0x5C1180,       // 8030
        0x21430F,       // 8031
        0x21025F,       // 8032
        0x2100DF,       // 8033
        0x05800F,       // 8034
        0x004713,       // 8035
        0x783923,       // 8036
        0x7C3953,       // 8037
        0xA00787,       // 8038
        0x54A880,       // 8039
        0x548080,       // 803A
        0x54A880,       // 803B
        0x190050,       // 803C
        0x542A80,       // 803D
        0x54A880,       // 803E
        0xA00E5F,       // 803F
        0x190107,       // 8040
        0x542C80,       // 8041
        0x998050,       // 8042
        0x542A80,       // 8043
        0x200E1F,       // 8044
        0x198A2A,       // 8045
        0x542C80,       // 8046
        0xD41180,       // 8047
        0x541080,       // 8048
        0xA14E3F,       // 8049
        0x1B4953,       // 804A
        0x542C80,       // 804B
        0x214E4F,       // 804C
        0x9B054D,       // 804D
        0x542C80,       // 804E
        0x541080,       // 804F
        0x1B0552,       // 8050
        0xD42D80,       // 8051
        0x1B0F52,       // 8052
        0x542C80,       // 8053
        0x541080,       // 8054
        0xA08E8F,       // 8055
        0x8208E2,       // 8056
        0x542C80,       // 8057
        0x0208E0,       // 8058
        0xD42D80,       // 8059
        0x541080,       // 805A
        0xE85D47,       // 805B
        0xD7ED80,       // 805C
        0x8D800F,       // 805D
        0x541680,       // 805E
        0xFC6907,       // 805F
        0x787137,       // 8060
        0x541080,       // 8061
        0xDC6480,       // 8062
        0xDE2E80,       // 8063
        0xD4AF80,       // 8064
        0xA0000E,       // 8065
        0x541980,       // 8066
        0x541680,       // 8067
        0x5C7180,       // 8068
        0x7C7127,       // 8069
        0x541080,       // 806A
        0x706F47,       // 806B
        0x200006,       // 806C
        0x541980,       // 806D
        0xF071C7,       // 806E
        0x8208E4,       // 806F
        0x541680,       // 8070
        0x208E9F,       // 8071
        0xD41180,       // 8072
        0x541080,       // 8073
        0x208EAF,       // 8074
        0x198A2A,       // 8075
        0x542C80,       // 8076
        0x5C2480,       // 8077
        0x200F0F,       // 8078
        0xDE2780,       // 8079
        0xA0001F,       // 807A
        0x87800F,       // 807B
        0x8381AF,       // 807C
        0x200E08,       // 807D
        0x8381AF,       // 807E
        0x5C8180,       // 807F
        0xA00E5F,       // 8080
        0x178C00,       // 8081
        0x548380,       // 8082
        0xD48480,       // 8083
        0x548580,       // 8084
        0x200F0F,       // 8085
        0x200F0F,       // 8086
        0x87800F,       // 8087
        0x190FFF,       // 8088
        0x5C8B80,       // 8089
        0x57F180,       // 808A
        0x860000,       // 808B
        0xA00209,       // 808C
        0x81800F,       // 808D
        0xFC9412,       // 808E
        0xA16FAF,       // 808F
        0xA01F0F,       // 8090
        0xA02F0F,       // 8091
        0x200E0B,       // 8092
        0xDC9880,       // 8093
        0xA14EAF,       // 8094
        0xD4B180,       // 8095
        0x8B800F,       // 8096
        0xD4AF80,       // 8097
        0x50A4EE,       // 8098
        0x7C9BFE,       // 8099
        0x70A4FE,       // 809A
        0x7CA45E,       // 809B
        0xF8A4AE,       // 809C
        0x8B800F,       // 809D
        0x0200E8,       // 809E
        0x18C929,       // 809F
        0xF4A312,       // 80A0
        0xFCA389,       // 80A1
        0xAC4909,       // 80A2
        0xD88D29,       // 80A3
        0xFCA712,       // 80A4
        0x195FFF,       // 80A5
        0xA8CDFD,       // 80A6
        0x87800F,       // 80A7
        0x998000,       // 80A8
        0xD48280,       // 80A9
        0xD8A9F8,       // 80AA
        0x7CA909,       // 80AB
        0x87800F,       // 80AC
        0xA00040,       // 80AD
        0x87800F,       // 80AE
        0x05800F,       // 80AF
        0x878600,       // 80B0
        0xA7CEFE,       // 80B1
        0x05800F,       // 80B2
        0x8B800F,       // 80B3
        0x078400,       // 80B4
        0x05800F,       // 80B5
        0xA0000E,       // 80B6
        0xD4B180,       // 80B7
        0x8D800F,       // 80B8
        0x05800F,       // 80B9
        0xD4AF80,       // 80BA
        0x040E0E,       // 80BB
        0x0200E8,       // 80BC
        0x8B800F,       // 80BD
        0x060008,       // 80BE
        0x8D800F,       // 80BF
        0xD8C31F,       // 80C0
        0x58C30F,       // 80C1
        0xD0A70E,       // 80C2
        0xA0060E,       // 80C3
        0x0204E0,       // 80C4
        0x21013F,       // 80C5
        0x21032F,       // 80C6
        0xDD3080,       // 80C7
        0xD4AF80,       // 80C8
        0x81800F,       // 80C9
        0x990001,       // 80CA
        0x5CB180,       // 80CB
        0x8A00EE,       // 80CC
        0x990001,       // 80CD
        0x23FFFF,       // 80CE
        0x802FEF,       // 80CF
        0x44CF08,       // 80D0
        0x87800F,       // 80D1
        0x190000,       // 80D2
        0x01801F,       // 80D3
        0x57FD80,       // 80D4
        0x0B801F,       // 80D5
        0xA60209,       // 80D6
        0x81800F,       // 80D7
        0x0208E0,       // 80D8
        0x200E02,       // 80D9
        0x54B580,       // 80DA
        0xFCE099,       // 80DB
        0x78E009,       // 80DC
        0x7CE008,       // 80DD
        0xF8E008,       // 80DE
        0x2A0909,       // 80DF
        0xD8D9F9,       // 80E0
        0x7CD908,       // 80E1
        0x87800F,       // 80E2
        0x540D80,       // 80E3
        0x1FCFFF,       // 80E4
        0xA20D0D,       // 80E5
        0x000FEF,       // 80E6
        0x801FEF,       // 80E7
        0xE4024D,       // 80E8
        0x58E619,       // 80E9
        0x58E608,       // 80EA
        0xA8CDFD,       // 80EB
        0x20000F,       // 80EC
        0x87800F,       // 80ED
        0x19000F,       // 80EE
        0xD4AF80,       // 80EF
        0xD0ECE9,       // 80F0
        0x81803F,       // 80F1
        0x190000,       // 80F2
        0x81800F,       // 80F3
        0x2BCDED,       // 80F4
        0x2009FF,       // 80F5
        0x01802F,       // 80F6
        0x060222,       // 80F7
        0x060444,       // 80F8
        0x860666,       // 80F9
        0x8B800F,       // 80FA
        0x01820F,       // 80FB
        0xD4AF80,       // 80FC
        0xD74D80,       // 80FD
        0x51050F,       // 80FE
        0x03800F,       // 80FF
        0xFE2F89,       // 8100
        0xFA2F09,       // 8101
        0xFE2F08,       // 8102
        0xFA2FD8,       // 8103
        0x03800F,       // 8104
        0x84077E,       // 8105
        0x060558,       // 8106
        0x1A8222,       // 8107
        0x180444,       // 8108
        0x380202,       // 8109
        0x9A0228,       // 810A
        0x18044E,       // 810B
        0x8B800F,       // 810C
        0x78FBE8,       // 810D
        0x7CFBF8,       // 810E
        0x0B802F,       // 810F
        0x200009,       // 8110
        0x8B800F,       // 8111
        0xD8FB09,       // 8112
        0x01820F,       // 8113
        0xD4AF80,       // 8114
        0x592C4E,       // 8115
        0x592C39,       // 8116
        0x592C28,       // 8117
        0x84077E,       // 8118
        0x060558,       // 8119
        0x8B800F,       // 811A
        0x01820F,       // 811B
        0xD4AF80,       // 811C
        0xA7C7F7,       // 811D
        0xA7C6F6,       // 811E
        0xA7C5F5,       // 811F
        0x592C7E,       // 8120
        0x592C69,       // 8121
        0xD92C58,       // 8122
        0x8B800F,       // 8123
        0x200009,       // 8124
        0x8B803F,       // 8125
        0x50EC09,       // 8126
        0x0B802F,       // 8127
        0xAC4909,       // 8128
        0xFCF689,       // 8129
        0xAC4909,       // 812A
        0x5CF680,       // 812B
        0x8B800F,       // 812C
        0x800FFF,       // 812D
        0x21013F,       // 812E
        0x21436F,       // 812F
        0x543280,       // 8130
        0x5E3780,       // 8131
        0xA1014F,       // 8132
        0x5D2F80,       // 8133
        0xA00D2D,       // 8134
        0x190000,       // 8135
        0x190000,       // 8136
        0x190000,       // 8137
        0xA00E5F,       // 8138
        0x178C00,       // 8139
        0x190000,       // 813A
        0x190000,       // 813B
        0xE93C8D,       // 813C
        0xA00E3F,       // 813D
        0x978200,       // 813E
        0xE93F8D,       // 813F
        0xA10EDF,       // 8140
        0x978200,       // 8141
        0xE9428D,       // 8142
        0x5C0C80,       // 8143
        0x210EFF,       // 8144
        0x978200,       // 8145
        0x69468D,       // 8146
        0x547A80,       // 8147
        0x54AD80,       // 8148
        0xD77280,       // 8149
        0xD77480,       // 814A
        0xFD4BA0,       // 814B
        0xF94C50,       // 814C
        0x1B4505,       // 814D
        0xD42D80,       // 814E
        0x57E380,       // 814F
        0x992000,       // 8150
        0x193000,       // 8151
        0x991000,       // 8152
        0xA8CDFD,       // 8153
        0xA10EEF,       // 8154
        0xD41180,       // 8155
        0x1B4AA5,       // 8156
        0x0200E8,       // 8157
        0x0202E0,       // 8158
        0x8204E2,       // 8159
        0x0206E4,       // 815A
        0x5A3A79,       // 815B
        0x5A3A68,       // 815C
        0x0208E5,       // 815D
        0x7D5759,       // 815E
        0x214E4F,       // 815F
        0xD41180,       // 8160
        0x20000F,       // 8161
        0x190000,       // 8162
        0x000FEF,       // 8163
        0xDA3A09,       // 8164
        0x7E3A08,       // 8165
        0x7A3A18,       // 8166
        0x0C80FF,       // 8167
        0x800FFF,       // 8168
        0xDA3A09,       // 8169
        0x5A3A08,       // 816A
        0x541080,       // 816B
        0x190000,       // 816C
        0x81800F,       // 816D
        0x81821F,       // 816E
        0x01C22F,       // 816F
        0x0B802F,       // 8170
        0x0200E8,       // 8171
        0x1FCFFF,       // 8172
        0x5A3A19,       // 8173
        0x5A3A08,       // 8174
        0x9AC0E0,       // 8175
        0x8B800F,       // 8176
        0x5A3A19,       // 8177
        0x5A3A08,       // 8178
        0x9AC0E0,       // 8179
        0x0B801F,       // 817A
        0x5A3A19,       // 817B
        0x5A3A08,       // 817C
        0xA14E3F,       // 817D
        0xD41180,       // 817E
        0x2D40AF,       // 817F
        0xAE8150,       // 8180
        0x1B4AFF,       // 8181
        0xDA3A09,       // 8182
        0xDA3A18,       // 8183
        0xAD42B1,       // 8184
        0x5A3A02,       // 8185
        0x98C321,       // 8186
        0xDA3A30,       // 8187
        0x988421,       // 8188
        0x18C340,       // 8189
        0x7E3A54,       // 818A
        0xFA3A94,       // 818B
        0x7E3AB3,       // 818C
        0xFA3A43,       // 818D
        0xA00D1D,       // 818E
        0x3BC3FF,       // 818F
        0xDA3A3F,       // 8190
        0x2BCDED,       // 8191
        0x3BC3F3,       // 8192
        0xFE3AF3,       // 8193
        0x7A3AF3,       // 8194
        0x0CC430,       // 8195
        0x7E3AA4,       // 8196
        0xFA3A54,       // 8197
        0x20071F,       // 8198
        0x0C877F,       // 8199
        0x5A3A7F,       // 819A
        0x1900FF,       // 819B
        0x8201E8,       // 819C
        0x1AC3E1,       // 819D
        0x990100,       // 819E
        0x5A3A49,       // 819F
        0x5A3A38,       // 81A0
        0x20000F,       // 81A1
        0x8E833F,       // 81A2
        0xDA3A42,       // 81A3
        0x5A3A31,       // 81A4
        0xA14E9F,       // 81A5
        0xD41180,       // 81A6
        0x194111,       // 81A7
        0x8201E8,       // 81A8
        0x05800F,       // 81A9
        0x98C00F,       // 81AA
        0x1A8818,       // 81AB
        0xFDA960,       // 81AC
        0x0203E8,       // 81AD
        0x8D800F,       // 81AE
        0x8EC331,       // 81AF
        0x5A3A49,       // 81B0
        0x5A3A38,       // 81B1
        0x0C800F,       // 81B2
        0x59AE0F,       // 81B3
        0xA14E3F,       // 81B4
        0xD41180,       // 81B5
        0x2BCDED,       // 81B6
        0xB1400F,       // 81B7
        0xB0011F,       // 81B8
        0x354210,       // 81B9
        0xDA3A21,       // 81BA
        0xA00D1D,       // 81BB
        0xB40221,       // 81BC
        0x5A3A2F,       // 81BD
        0x22409F,       // 81BE
        0x108302,       // 81BF
        0xDA3A03,       // 81C0
        0x10C33F,       // 81C1
        0xEA3A1D,       // 81C2
        0xDA3A3F,       // 81C3
        0x1482E0,       // 81C4
        0xDA3A12,       // 81C5
        0x14C433,       // 81C6
        0x5A3A40,       // 81C7
        0x214E4F,       // 81C8
        0xD41180,       // 81C9
        0x2140AF,       // 81CA
        0xA0C1CF,       // 81CB
        0xBC8250,       // 81CC
        0xFE3A12,       // 81CD
        0xFA3A92,       // 81CE
        0x3C0271,       // 81CF
        0x7E3A52,       // 81D0
        0x7A3A42,       // 81D1
        0x9CC302,       // 81D2
        0x7E3A13,       // 81D3
        0x7A3A93,       // 81D4
        0x1C8313,       // 81D5
        0xFE3A03,       // 81D6
        0x7A3AC3,       // 81D7
        0x1C0213,       // 81D8
        0x7E3A92,       // 81D9
        0xFA3A02,       // 81DA
        0x210E5F,       // 81DB
        0xD41180,       // 81DC
        0x2140AF,       // 81DD
        0xA2815F,       // 81DE
        0x044211,       // 81DF
        0x5A3A20,       // 81E0
        0x0C4300,       // 81E1
        0xFE3A53,       // 81E2
        0x7A3A53,       // 81E3
        0x004410,       // 81E4
        0xDA3A41,       // 81E5
        0x084304,       // 81E6
        0xFE3AA3,       // 81E7
        0x7A3AA3,       // 81E8
        0xA10EDF,       // 81E9
        0xD41180,       // 81EA
        0x1D0400,       // 81EB
        0x81803F,       // 81EC
        0x01C22F,       // 81ED
        0x9D0006,       // 81EE
        0x81800F,       // 81EF
        0x54F780,       // 81F0
        0x541080,       // 81F1
        0x200C0F,       // 81F2
        0xD4CC80,       // 81F3
        0xAC8C0C,       // 81F4
        0xFDF30C,       // 81F5
        0xA14E0F,       // 81F6
        0xD41180,       // 81F7
        0x1D000B,       // 81F8
        0x54C880,       // 81F9
        0x27C0FE,       // 81FA
        0x8201E8,       // 81FB
        0x990001,       // 81FC
        0xD4AF80,       // 81FD
        0x5A3A0E,       // 81FE
        0x5A3A29,       // 81FF
        0xDA3A18,       // 8200
        0x01801F,       // 8201
        0x8208EE,       // 8202
        0x01802F,       // 8203
        0x210ECF,       // 8204
        0x9B0154,       // 8205
        0x542C80,       // 8206
        0x1B0552,       // 8207
        0x542C80,       // 8208
        0xD63B80,       // 8209
        0x1B4A5A,       // 820A
        0x54D380,       // 820B
        0x1D85A5,       // 820C
        0x54D380,       // 820D
        0x540D80,       // 820E
        0xA20D0D,       // 820F
        0x1AC8E0,       // 8210
        0x81800F,       // 8211
        0x20060F,       // 8212
        0x8B800F,       // 8213
        0x2C0017,       // 8214
        0x2C0110,       // 8215
        0x8082FF,       // 8216
        0x800FFF,       // 8217
        0xDA1B6F,       // 8218
        0x202F01,       // 8219
        0x203F00,       // 821A
        0xD76A80,       // 821B
        0xA00001,       // 821C
        0xAC0111,       // 821D
        0x521D71,       // 821E
        0x5A1628,       // 821F
        0xDA1629,       // 8220
        0xAC0616,       // 8221
        0xFA1336,       // 8222
        0xAC0717,       // 8223
        0xFA1207,       // 8224
        0xDE0A80,       // 8225
        0x5E4C80,       // 8226
        0xA1014F,       // 8227
        0x543180,       // 8228
        0xA20D0D,       // 8229
        0x2ACDFD,       // 822A
        0x991000,       // 822B
        0x29CDFD,       // 822C
        0x5E3780,       // 822D
        0x8D800F,       // 822E
        0x800FFF,       // 822F
        0x0200E8,       // 8230
        0x9D000C,       // 8231
        0xDA3419,       // 8232
        0xD14408,       // 8233
        0x0208E0,       // 8234
        0x21013F,       // 8235
        0x543180,       // 8236
        0x1D000B,       // 8237
        0x54C880,       // 8238
        0xD63B80,       // 8239
        0xDE3A80,       // 823A
        0x99010A,       // 823B
        0xD42D80,       // 823C
        0x998050,       // 823D
        0x542A80,       // 823E
        0x200E1F,       // 823F
        0x190A50,       // 8240
        0x542C80,       // 8241
        0x214E2F,       // 8242
        0x9B0553,       // 8243
        0x542C80,       // 8244
        0x198052,       // 8245
        0x542C80,       // 8246
        0x9B0553,       // 8247
        0xD42D80,       // 8248
        0x1B0554,       // 8249
        0xD42D80,       // 824A
        0x5C2480,       // 824B
        0xA00C2F,       // 824C
        0x220D2D,       // 824D
        0x2ACDFD,       // 824E
        0x991000,       // 824F
        0x548080,       // 8250
        0xA00E3F,       // 8251
        0x19054B,       // 8252
        0x542C80,       // 8253
        0x210E5F,       // 8254
        0x9B4920,       // 8255
        0x542C80,       // 8256
        0x9B4346,       // 8257
        0xD42D80,       // 8258
        0x19873F,       // 8259
        0xD42D80,       // 825A
        0x541080,       // 825B
        0xA0850F,       // 825C
        0xA0860F,       // 825D
        0x190000,       // 825E
        0x8181DF,       // 825F
        0xAB8C7C,       // 8260
        0x56FA80,       // 8261
        0x20070E,       // 8262
        0x56FA80,       // 8263
        0xA0060E,       // 8264
        0x56FA80,       // 8265
        0xA0050E,       // 8266
        0xA04C0C,       // 8267
        0x56FA80,       // 8268
        0x5C0380,       // 8269
        0xAC4000,       // 826A
        0x5A7F0F,       // 826B
        0x8B80CF,       // 826C
        0x200408,       // 826D
        0x8B80FF,       // 826E
        0x537648,       // 826F
        0xD78180,       // 8270
        0x994F00,       // 8271
        0xDE7E80,       // 8272
        0x2BCCDC,       // 8273
        0x547C80,       // 8274
        0xA20D0D,       // 8275
        0x57E380,       // 8276
        0x190000,       // 8277
        0x8180FF,       // 8278
        0xD78180,       // 8279
        0x195F00,       // 827A
        0xA0080A,       // 827B
        0x8180CF,       // 827C
        0x194F10,       // 827D
        0x0200E8,       // 827E
        0x0208E0,       // 827F
        0xA01F0F,       // 8280
        0xFE6A1B,       // 8281
        0xFA6A0B,       // 8282
        0xFE6A0A,       // 8283
        0xAC0888,       // 8284
        0x801FEF,       // 8285
        0xFE6A4B,       // 8286
        0xFA6A0B,       // 8287
        0x5A6AC7,       // 8288
        0x801FEF,       // 8289
        0x5A6AD6,       // 828A
        0xDA6AA5,       // 828B
        0x801FEF,       // 828C
        0xFE6A2B,       // 828D
        0xFA6A0B,       // 828E
        0x7A8C08,       // 828F
        0xAC0020,       // 8290
        0x0208E0,       // 8291
        0x001F0F,       // 8292
        0x0208EA,       // 8293
        0x8180FF,       // 8294
        0xD78180,       // 8295
        0x195F00,       // 8296
        0xE6D84D,       // 8297
        0xE6E22B,       // 8298
        0x7F788B,       // 8299
        0x995F04,       // 829A
        0x52CEBF,       // 829B
        0xA0000B,       // 829C
        0x195F06,       // 829D
        0x0208EA,       // 829E
        0x0180DF,       // 829F
        0x995F08,       // 82A0
        0xA0030B,       // 82A1
        0x52D73F,       // 82A2
        0x0184CF,       // 82A3
        0x7F7800,       // 82A4
        0xE2AA1C,       // 82A5
        0xD4CC80,       // 82A6
        0xD4D280,       // 82A7
        0xA00C1C,       // 82A8
        0x5EDF80,       // 82A9
        0x280130,       // 82AA
        0x000C1C,       // 82AB
        0xF2BB30,       // 82AC
        0x7B7810,       // 82AD
        0x0B80DF,       // 82AE
        0x0380CF,       // 82AF
        0xA0C2CF,       // 82B0
        0x0392CF,       // 82B1
        0xE6D84D,       // 82B2
        0x575E80,       // 82B3
        0x8382CF,       // 82B4
        0x2FC3F3,       // 82B5
        0x52D73F,       // 82B6
        0x2FC2F2,       // 82B7
        0x5AB12F,       // 82B8
        0x9AC8E8,       // 82B9
        0x5EB080,       // 82BA
        0x20423F,       // 82BB
        0x8B80CF,       // 82BC
        0x801FEF,       // 82BD
        0x001EDF,       // 82BE
        0x0011DF,       // 82BF
        0xA0000B,       // 82C0
        0x8180CF,       // 82C1
        0x0208E0,       // 82C2
        0x81800F,       // 82C3
        0x0B80DF,       // 82C4
        0x8182DF,       // 82C5
        0x54B580,       // 82C6
        0x0C833F,       // 82C7
        0x52D73F,       // 82C8
        0x0C822F,       // 82C9
        0xE2BC1D,       // 82CA
        0x8B80CF,       // 82CB
        0x0182CF,       // 82CC
        0xDEBB80,       // 82CD
        0x195F0A,       // 82CE
        0x548080,       // 82CF
        0x000FEF,       // 82D0
        0x001EDF,       // 82D1
        0xD41180,       // 82D2
        0xFED148,       // 82D3
        0x7AD178,       // 82D4
        0xD42480,       // 82D5
        0x547C80,       // 82D6
        0x6E954D,       // 82D7
        0x548080,       // 82D8
        0xA14E0F,       // 82D9
        0xD41180,       // 82DA
        0x196F00,       // 82DB
        0xA01F0F,       // 82DC
        0x2ACDFD,       // 82DD
        0x547C80,       // 82DE
        0x0380FF,       // 82DF
        0x03C2FF,       // 82E0
        0xDE9580,       // 82E1
        0xEAF22C,       // 82E2
        0xD4EE80,       // 82E3
        0x54E380,       // 82E4
        0x198001,       // 82E5
        0x8181EF,       // 82E6
        0x190000,       // 82E7
        0x0181FF,       // 82E8
        0x280C4C,       // 82E9
        0xEAEC4C,       // 82EA
        0x200CCF,       // 82EB
        0xDC0300,       // 82EC
        0x200F0F,       // 82ED
        0x200F0F,       // 82EE
        0x200F0F,       // 82EF
        0x800000,       // 82F0
        0x5F4D80,       // 82F1
        0x280C4C,       // 82F2
        0x548080,       // 82F3
        0x991000,       // 82F4
        0xFEF7FB,       // 82F5
        0xF25BFB,       // 82F6
        0x001EDF,       // 82F7
        0xD41180,       // 82F8
        0xDEF580,       // 82F9
        0x200E1F,       // 82FA
        0xD48180,       // 82FB
        0xD7BD80,       // 82FC
        0xA0000E,       // 82FD
        0x548080,       // 82FE
        0xA00E00,       // 82FF
        0xE30A4D,       // 8300
        0x76FA00,       // 8301
        0x66FA80,       // 8302
        0x66FA1C,       // 8303
        0x60118C,       // 8304
        0x210E0F,       // 8305
        0x5AFA0E,       // 8306
        0xD41180,       // 8307
        0xA00C8C,       // 8308
        0xDEFA80,       // 8309
        0x63418C,       // 830A
        0x8208EE,       // 830B
        0x8181DF,       // 830C
        0xEB1B2C,       // 830D
        0x7F130E,       // 830E
        0xF359FE,       // 830F
        0xE2FA6E,       // 8310
        0x21070F,       // 8311
        0xDF1980,       // 8312
        0xFEFA1E,       // 8313
        0xA1070E,       // 8314
        0xABC7C7,       // 8315
        0x7B18C7,       // 8316
        0xA00C4C,       // 8317
        0xA80E3E,       // 8318
        0x574680,       // 8319
        0xDF2680,       // 831A
        0xAD0710,       // 831B
        0x6B264C,       // 831C
        0xA1071F,       // 831D
        0x53260F,       // 831E
        0xA00E3F,       // 831F
        0xCB250E,       // 8320
        0xA00E6F,       // 8321
        0x4B240E,       // 8322
        0xAC0717,       // 8323
        0xAC0717,       // 8324
        0xAC0717,       // 8325
        0xA1090F,       // 8326
        0x200807,       // 8327
        0xD42D80,       // 8328
        0x19802F,       // 8329
        0xD42D80,       // 832A
        0x0B81AF,       // 832B
        0xA0C209,       // 832C
        0xA0C19F,       // 832D
        0x542080,       // 832E
        0xD41880,       // 832F
        0x998021,       // 8330
        0x542A80,       // 8331
        0xA08E8F,       // 8332
        0x9B024F,       // 8333
        0x542C80,       // 8334
        0x9B4453,       // 8335
        0x542C80,       // 8336
        0x214E4F,       // 8337
        0x9B4241,       // 8338
        0x542C80,       // 8339
        0x9B403D,       // 833A
        0xD42D80,       // 833B
        0x214E2F,       // 833C
        0x99C529,       // 833D
        0x542C80,       // 833E
        0xD42480,       // 833F
        0x5E7380,       // 8340
        0x7EFA0E,       // 8341
        0xF359FE,       // 8342
        0xE2FA6E,       // 8343
        0x574680,       // 8344
        0xDF2980,       // 8345
        0x3C088E,       // 8346
        0xA80988,       // 8347
        0x29C808,       // 8348
        0x2C0939,       // 8349
        0xAC4808,       // 834A
        0x0181AF,       // 834B
        0x87800F,       // 834C
        0x0200E8,       // 834D
        0x84011E,       // 834E
        0x040110,       // 834F
        0x04401F,       // 8350
        0x040101,       // 8351
        0xBC0041,       // 8352
        0x040101,       // 8353
        0x6B5641,       // 8354
        0x240181,       // 8355
        0x60EC81,       // 8356
        0x23C0FF,       // 8357
        0x87800F,       // 8358
        0xD42480,       // 8359
        0x99000D,       // 835A
        0x54C880,       // 835B
        0xA8CDFD,       // 835C
        0x5C0E00,       // 835D
        0x200E0B,       // 835E
        0x202F0E,       // 835F
        0xA01F0F,       // 8360
        0x67634D,       // 8361
        0x50A7BE,       // 8362
        0x0406BE,       // 8363
        0x0A04EE,       // 8364
        0xA1014F,       // 8365
        0xA1432F,       // 8366
        0xDD3080,       // 8367
        0x202F01,       // 8368
        0x203F00,       // 8369
        0xA01F0F,       // 836A
        0xE76E4D,       // 836B
        0xDB6EB1,       // 836C
        0x50A7A0,       // 836D
        0x0604A0,       // 836E
        0x20060F,       // 836F
        0xA1014F,       // 8370
        0x5CC680,       // 8371
        0xA08000,       // 8372
        0x87800F,       // 8373
        0xA20000,       // 8374
        0x87800F,       // 8375
        0x22002F,       // 8376
        0xDF7980,       // 8377
        0x22008F,       // 8378
        0xA00800,       // 8379
        0x20090F,       // 837A
        0x21034F,       // 837B
        0x21029F,       // 837C
        0xA1413F,       // 837D
        0x2100BF,       // 837E
        0x543480,       // 837F
        0x5E3780,       // 8380
        0x579880,       // 8381
        0x20000F,       // 8382
        0x57A780,       // 8383
        0x5B810F,       // 8384
        0xD7C080,       // 8385
        0xD41280,       // 8386
        0x57CB80,       // 8387
        0x994F00,       // 8388
        0xA0020F,       // 8389
        0xD7BD80,       // 838A
        0x98822E,       // 838B
        0x20010E,       // 838C
        0xD7BD80,       // 838D
        0x98822E,       // 838E
        0xA0000E,       // 838F
        0x576880,       // 8390
        0x000FEF,       // 8391
        0x0000EF,       // 8392
        0x5B8A08,       // 8393
        0xD7BD80,       // 8394
        0x50A72E,       // 8395
        0xA2407F,       // 8396
        0xDF7980,       // 8397
        0xEB988D,       // 8398
        0xA00D2D,       // 8399
        0xA28E0F,       // 839A
        0x978800,       // 839B
        0xA00E0F,       // 839C
        0xD41180,       // 839D
        0x57D680,       // 839E
        0xE39A1D,       // 839F
        0xA0020F,       // 83A0
        0xF7A4CE,       // 83A1
        0x7FA5DE,       // 83A2
        0x20021F,       // 83A3
        0x87800F,       // 83A4
        0x22400F,       // 83A5
        0xDF7980,       // 83A6
        0x210E0F,       // 83A7
        0x978800,       // 83A8
        0x0B81AF,       // 83A9
        0xF3AD39,       // 83AA
        0xA04000,       // 83AB
        0x0181AF,       // 83AC
        0x8B80FF,       // 83AD
        0x0182FF,       // 83AE
        0xD7DD80,       // 83AF
        0xDBBF0F,       // 83B0
        0x6BB712,       // 83B1
        0x20000F,       // 83B2
        0xD7DD80,       // 83B3
        0xDBBF0F,       // 83B4
        0x200009,       // 83B5
        0x5FB880,       // 83B6
        0x29C0F9,       // 83B7
        0xD7DD80,       // 83B8
        0xDBBF0F,       // 83B9
        0xA00008,       // 83BA
        0xD7DD80,       // 83BB
        0x53BF0F,       // 83BC
        0x2BCD8D,       // 83BD
        0x6BBE2D,       // 83BE
        0x87800F,       // 83BF
        0xD7BD80,       // 83C0
        0xE3C51E,       // 83C1
        0x63C72E,       // 83C2
        0xE3C94E,       // 83C3
        0xDC8380,       // 83C4
        0xA2408F,       // 83C5
        0xDF7980,       // 83C6
        0xA2401F,       // 83C7
        0xDF7980,       // 83C8
        0xA2404F,       // 83C9
        0xDF7980,       // 83CA
        0xD7BD80,       // 83CB
        0xE3D41E,       // 83CC
        0x63D02E,       // 83CD
        0xE3D24E,       // 83CE
        0x87800F,       // 83CF
        0x22403F,       // 83D0
        0xDF7980,       // 83D1
        0x22406F,       // 83D2
        0xDF7980,       // 83D3
        0x22405F,       // 83D4
        0xDF7980,       // 83D5
        0x9B0B01,       // 83D6
        0xABCDCD,       // 83D7
        0x63DC2D,       // 83D8
        0x9AC8E8,       // 83D9
        0x6BD81D,       // 83DA
        0xA00D2D,       // 83DB
        0x87800F,       // 83DC
        0xA00D2D,       // 83DD
        0xA00E00,       // 83DE
        0xD41180,       // 83DF
        0xD7BD80,       // 83E0
        0x84000E,       // 83E1
        0x5C8280,       // 83E2
        0x9D0003,       // 83E3
        0xD4AF80,       // 83E4
        0x81800F,       // 83E5
        0x99000E,       // 83E6
        0x01C21F,       // 83E7
        0xD4B180,       // 83E8
        0xA7CEFE,       // 83E9
        0x0B801F,       // 83EA
        0xF7E709,       // 83EB
        0x87800F,       // 83EC
        0xAB880C,       // 83ED
        0xD41880,       // 83EE
        0xA08EEF,       // 83EF
        0x5C1180,       // 83F0
        0x994FFF,       // 83F1
        0xA20D0D,       // 83F2
        0x2ACDFD,       // 83F3
        0x87800F,       // 83F4
        0x800000,       // 83F5
        0x800000,       // 83F6
        0x800000,       // 83F7
        0x800000,       // 83F8
        0x800000,       // 83F9
        0xDE4D80,       // 83FA
        0x5E7380,       // 83FB
        0x5F4D80,       // 83FC
        0x5C8880,       // 83FD
        0xD9BD76,       // 83FE
        0x033441,       // 83FF
};

// vim: ts=8:et:sw=4:smarttab
