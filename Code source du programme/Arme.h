//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#ifndef ARME
#define ARME
#include <string>
#include <irrlicht.h>
#include <irrTypes.h>
#include "XEffects.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;


class CArme
{

public :

    CArme(stringw nom, int degats, int maxChargeur, int maxMunChargeur, int cadenceTir, int cadenceRecharge, bool coupParCoup);
    ~CArme();

    IAnimatedMeshSceneNode* getGunMesh() const;
    IAnimatedMeshSceneNode* getHandRMesh() const;
    IAnimatedMeshSceneNode* getHandLMesh() const;
    stringw                 getNomArme() const;
    void                    Init3D(scene::ISceneManager*,video::IVideoDriver* , scene::ICameraSceneNode*);
    void                    setLooped(bool);
    void                    setFL(int, int);
    void                    setGunFL(int,int);
    void                    setHandRFL(int,int);
    void                    setHandLFL(int,int);
    void                    setArmeActive(bool);
    void                    setNomArme(stringw);
    void                    setDegatsArme(int);
    void                    majMunition(int maj_muni);
    void                    majChargeur(int maj_chrg);
    int                     getDegats() const;
    int                     getMunitions() const;
    int                     getChargeurs() const;
    int                     getCadenceTirArme() const;
    int                     getCadenceRechargeArme() const;
    int                     getCapaciteArmeChargeurs() const;
    int                     getCapaciteArmeMunitions() const;
    bool                    isLooped();
    bool                    isCoupParCoup();

private :

    IAnimatedMeshSceneNode* m_gun3D;
    IAnimatedMeshSceneNode* m_handR3D;
    IAnimatedMeshSceneNode* m_handL3D;
    ISceneNode*             m_boneHandR;
    ISceneNode*             m_boneHandL;
    ITexture*               m_gunTex;
    ITexture*               m_gunTexMap;
    ITexture*               m_handTex;
    ITexture*               m_handTexMap;
    stringw                 m_nomArme;
    int                     m_degatsArme;
    int                     m_maxChargeursArme;
    int                     m_maxMunitionsChargeurArme;
    int                     m_cadenceTirArme;
    int                     m_cadenceRechargeArme;
    int                     m_munitions;
    int                     m_chargeurs;
    bool                    m_isLooped;
    bool                    m_isActive;
    bool                    m_coupParCoup;


};


#endif
