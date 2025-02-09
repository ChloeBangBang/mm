#ifndef Z_BG_HAKA_BOMBWALL_H
#define Z_BG_HAKA_BOMBWALL_H

#include "global.h"

#define BGHAKABOMBWALL_GET_7F(thisx) ((thisx)->params & 0x7F)

struct BgHakaBombwall;

typedef void (*BgHakaBombwallActionFunc)(struct BgHakaBombwall*, PlayState*);

typedef struct BgHakaBombwall {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ ColliderCylinder collider;
    /* 0x1A8 */ BgHakaBombwallActionFunc actionFunc;
    /* 0x1AC */ s8 csTimer;
} BgHakaBombwall; // size = 0x1B0

extern const ActorInit Bg_Haka_Bombwall_InitVars;

#endif // Z_BG_HAKA_BOMBWALL_H
