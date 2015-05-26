#ifndef DEF_FPS
#define DEF_FPS

#include <irrlicht.h>
#include <irrklang.h>
#include <irrTypes.h>
#include <vector>
#include "joueur.h"
#include "framework.h"
#include "Niveau.h"
#include "Zombie.h"
#include "ScoreManager.h"
#include "Items.h"

using namespace irr;
using namespace irrklang;
using namespace core;
using namespace scene;
using namespace video;


class CFps : public CFramework, public irr::IEventReceiver
{

public:

    CFps();
    ~CFps();
    virtual bool run();
    virtual bool OnEvent(const irr::SEvent &event);

private:


    bool m_tir;
    bool m_shootingRay;
    bool m_pickupRay;
    bool m_lampeTorche;
    bool m_activerZoneDebug;
    bool m_wipBlocker;
    bool m_minFPSActive;
    bool m_drawHUD;
    bool m_modeRafale;
    bool m_drawFPS;
    bool m_activerEjectionChargeur;

    double m_angleArme;

    int m_nombre_balles;
    int m_nombre_chargeurs;
    int m_nombre_round;
    int m_nombre_score;
    int m_nombre_zombiesParRound;
    int m_nextDecal;
    int m_maxDecals;
    int m_parseurDouilles;
    int m_parseurChargeurs;
    int m_parseurZombies;
    int m_parseurCreationZombies;
    int m_maxChargeurs;
    int m_maxDouilles;
    int m_armeActuelle;
    int m_tempSwitchArme;
    int m_zombieRestants;

    int m_FPS;
    int m_LASTFPS;
    int m_MAXFPS;
    int m_MINFPS;
    int m_santeHUD;

    s32 PosCamX;
    s32 PosCamZ;

    u32 m_delaiPourEjecterChargeur;
    u32 m_deltaDelaiPourEjecterChargeur;

    u32 m_delaiIA;
    u32 m_deltaDelaiIA;

    u32 m_chronoIA;
    u32 m_deltaChronoIA;

    u32 m_delaiItemAB;
    u32 m_deltaDelaiItemAB;
    int m_parseurItemAB;
    int m_previousItemLocationAB;

    int m_ZombieLoaderCount;
    bool m_chronoIASwitcher;
    bool m_songSwitcher;


    E_FILTER_TYPE           m_filterType;

    CJoueur*                m_joueur;
    CLevel*                 m_map;
    CScore*                 m_scoreManager;
    ISoundEngine*           m_soundEngine;
    ISoundSource*           m_berettaShootSound;
    ISoundSource*           m_uziShootSound;
    ISoundSource*           m_reloadSound;
    ISoundSource*           m_outOfAmmoSound;
    ISoundSource*           m_torcheSound;
    ISoundSource*           m_pickupSound;
    ISoundSource*           m_frenzy1;
    ISoundSource*           m_frenzy2;
    ISoundSource*           m_frenzy3;
    ISoundSource*           m_frenzy4;
    ISoundSource*           m_frenzy5;
    ISoundSource*           m_frenzy6;
    ISoundSource*           m_hit1;
    ISoundSource*           m_hit2;
    ISoundSource*           m_hit3;
    ISoundSource*           m_hurt1;
    ISoundSource*           m_hurt2;
    ISoundSource*           m_hurt3;
    ISoundSource*           m_themeAction1;
    ISoundSource*           m_themeThrill1;
    ISceneNodeAnimator*     animViser;
    ISceneNodeAnimator*     animDeviser;
    ISceneNode*             m_muzzleflash;
    ISceneNode*             m_repereDouilles;
    ISceneNode*             m_repereDouilles2;
    ITexture*               m_neonTex;
    vector3df               m_vel;

    scene::ILightSceneNode*     m_lightnodeTorche;
    scene::ILightSceneNode*     m_muzzlelumiere;
    scene::ISceneNodeAnimator*  m_animViser;
    scene::ISceneNodeAnimator*  m_animDeviser;

    std::vector<IMeshSceneNode*> m_tablePointLum;
    std::vector<ILightSceneNode*> m_tableLumieres;
    std::vector<IRigidBody*> m_tableBodiesDouilles;
    std::vector<IRigidBody*> m_tableBodiesChargeurs;
    std::vector<CZombie*> m_tableZombies;
    std::vector<CAmmoBox*> m_tableItemAB;


};

#endif
