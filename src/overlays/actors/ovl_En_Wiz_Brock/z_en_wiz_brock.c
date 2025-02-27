/*
 * File: z_en_wiz_brock.c
 * Overlay: ovl_En_Wiz_Brock
 * Description: Wizzrobe Warp Platform
 */

#include "z_en_wiz_brock.h"
#include "objects/object_wiz/object_wiz.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_8000000)

#define THIS ((EnWizBrock*)thisx)

typedef enum {
    PLATFORM_TYPE_INACTIVE,
    PLATFORM_TYPE_FIRE,
    PLATFORM_TYPE_ICE,
    PLATFORM_TYPE_MAX,
} PlatformType;

void EnWizBrock_Init(Actor* thisx, PlayState* play);
void EnWizBrock_Destroy(Actor* thisx, PlayState* play);
void EnWizBrock_Update(Actor* thisx, PlayState* play);
void EnWizBrock_Draw(Actor* thisx, PlayState* play);

void EnWizBrock_SetupUpdateStatus(EnWizBrock* this, PlayState* play);
void EnWizBrock_UpdateStatus(EnWizBrock* this, PlayState* play);

s16 platformCount = 0;

const ActorInit En_Wiz_Brock_InitVars = {
    ACTOR_EN_WIZ_BROCK,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWizBrock),
    (ActorFunc)EnWizBrock_Init,
    (ActorFunc)EnWizBrock_Destroy,
    (ActorFunc)EnWizBrock_Update,
    (ActorFunc)EnWizBrock_Draw,
};

void EnWizBrock_Init(Actor* thisx, PlayState* play) {
    EnWizBrock* this = THIS;
    CollisionHeader* colHeader = NULL;

    DynaPolyActor_Init(&this->dyna, 0);
    CollisionHeader_GetVirtual(&object_wiz_Colheader_001690, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
    this->dyna.actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->dyna.actor.colChkInfo.health = 3;
    this->unk_1A6 = 0;
    Actor_SetScale(&this->dyna.actor, 0.01f);
    this->platformNum = platformCount++;
    this->actionFunc = EnWizBrock_SetupUpdateStatus;
    this->dyna.actor.scale.x = this->dyna.actor.scale.y = this->dyna.actor.scale.z = 0.01f;
    this->alpha = 255.0f;
}

void EnWizBrock_Destroy(Actor* thisx, PlayState* play) {
    EnWizBrock* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void EnWizBrock_SetupUpdateStatus(EnWizBrock* this, PlayState* play) {
    this->actionFunc = EnWizBrock_UpdateStatus;
}

/**
 * @brief Checks the platform status, when the Wizzrobe is defeated, which triggers timer to
 *  count up to 30 at which point the platforms are despawned.
 */
void EnWizBrock_UpdateStatus(EnWizBrock* this, PlayState* play) {
    if (this->platformType == PLATFORM_TYPE_INACTIVE) {
        if (this->dyna.actor.colChkInfo.health != PLATFORM_TYPE_MAX) {
            this->platformType = this->dyna.actor.colChkInfo.health;
        }
    }

    if (this->dyna.actor.colChkInfo.health == 0) {
        this->timer++;
        if (this->timer > (BREG(49) + 30)) {
            Math_ApproachZeroF(&this->dyna.actor.scale.y, (BREG(50) / 10.0f) + 0.3f, (BREG(51) / 10000.0f) + 0.003f);
            Math_ApproachZeroF(&this->alpha, (BREG(52) / 10.0f) + 1.0f, (BREG(53) / 10.0f) + 35.0f);
            Math_ApproachF(&this->dyna.actor.scale.x, (BREG(54) / 100.0f) + 0.02f, (BREG(55) / 100.0f) + 0.2f,
                           (BREG(56) / 1000.0f) + 0.002f);
            this->dyna.actor.scale.z = this->dyna.actor.scale.x;
            if (this->dyna.actor.scale.y < 0.001f) {
                Actor_MarkForDeath(&this->dyna.actor);
            }
        }
    }
}

void EnWizBrock_Update(Actor* thisx, PlayState* play) {
    EnWizBrock* this = THIS;

    this->actionFunc(this, play);
}

void EnWizBrock_Draw(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWizBrock* this = THIS;

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Translate(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z,
                     MTXMODE_NEW);
    Matrix_Scale(this->dyna.actor.scale.x, this->dyna.actor.scale.y, this->dyna.actor.scale.z, MTXMODE_APPLY);
    if (this->dyna.actor.colChkInfo.health != 0) {
        Scene_SetRenderModeXlu(play, 0, 1);
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
        Gfx_DrawDListOpa(play, gWizzrobePlatform);

    } else {
        Scene_SetRenderModeXlu(play, 1, 2);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, (s16)this->alpha);
        Gfx_DrawDListXlu(play, gWizzrobePlatform);
    }

    CLOSE_DISPS(play->state.gfxCtx);

    if (this->platformType != PLATFORM_TYPE_INACTIVE) {
        OPEN_DISPS(play->state.gfxCtx);
        AnimatedMat_Draw(play, Lib_SegmentedToVirtual(&gWizzrobePlatformTexAnim));
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 255, 255, 255);
        if (this->platformType == PLATFORM_TYPE_FIRE) {
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 00, 100, (s16)this->alpha);
        } else {
            gDPSetEnvColor(POLY_XLU_DISP++, 50, 00, 255, (s16)this->alpha);
        }

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, &gWizzrobePlatformCenter);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
