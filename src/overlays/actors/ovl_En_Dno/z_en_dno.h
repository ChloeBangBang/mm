#ifndef Z_EN_DNO_H
#define Z_EN_DNO_H

#include "global.h"

struct EnDno;

typedef void (*EnDnoActionFunc)(struct EnDno*, PlayState*);

#define ENDNO_GET_F(thisx) ((thisx)->params & 0xF)
#define ENDNO_GET_7F(thisx) ((thisx)->params & 0x7F)
#define ENDNO_GET_7F0(thisx) (((thisx)->params >> 4) & 0x7F)
#define ENDNO_GET_3F80(thisx) (((thisx)->params >> 7) & 0x7F)
#define ENDNO_GET_C000(thisx) (((thisx)->params >> 0xE) & 0x3)

enum {
    /* 0x0 */ ENDNO_GET_F_0,
    /* 0x1 */ ENDNO_GET_F_1,
};

enum {
    /* 0x0 */ ENDNO_GET_C000_0,
    /* 0x1 */ ENDNO_GET_C000_1,
};

typedef struct EnDno {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnDnoActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s jointTable[28];
    /* 0x280 */ Vec3s morphTable[28];
    /* 0x328 */ s32 unk_328;
    /* 0x32C */ s32 unk_32C;
    /* 0x330 */ UNK_TYPE1 unk_330[0x4];
    /* 0x334 */ Vec3f unk_334;
    /* 0x340 */ ActorPathing actorPath;
    /* 0x3AC */ s16 unk_3AC;
    /* 0x3AE */ s16 unk_3AE;
    /* 0x3B0 */ u16 unk_3B0;
    /* 0x3B2 */ UNK_TYPE1 unk_3B2[0xC];
    /* 0x3BE */ s16 unk_3BE;
    /* 0x3C0 */ f32 unk_3C0;
    /* 0x3C4 */ UNK_TYPE1 unk_3C4[0x78];
    /* 0x43C */ LightNode* lightNode;
    /* 0x440 */ LightInfo lightInfo;
    /* 0x44E */ u8 unk_44E;
    /* 0x44F */ UNK_TYPE1 unk_44F[0x3];
    /* 0x452 */ s16 unk_452;
    /* 0x454 */ f32 unk_454;
    /* 0x458 */ s32 getItemId;
    /* 0x45C */ s16 unk_45C;
    /* 0x460 */ Actor* unk_460;
    /* 0x464 */ u16 textId;
    /* 0x466 */ s16 unk_466;
    /* 0x468 */ u8 unk_468;
} EnDno; // size = 0x46C

extern const ActorInit En_Dno_InitVars;

#endif // Z_EN_DNO_H
