//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#ifndef DEF_JOUEUR
#define DEF_JOUEUR

#include <irrlicht.h>
#include <irrklang.h>
#include <irrTypes.h>
#include <vector>
#include "Arme.h"

using namespace irr;
using namespace irrklang;
using namespace core;
using namespace scene;
using namespace video;


class CJoueur
{

public :

    CJoueur();
    ~CJoueur();

    CArme*  getArme(int);
    void initArmes();

    bool    isShooting() const;
    void    setShooting(bool);

    bool    isAiming() const;
    void    setAiming(bool);

    bool    isReloading() const;
    void    setReloading(bool);

    bool    isIdle() const;
    void    setIdle(bool);

    //!----------------------//
    int     getSizeTableArmes() const;

    bool    canShoot() const;
    void    setShootAbility(bool);
    bool    canReload() const;
    void    setReloadAbility(bool);

    void    setTempsTir(u32);
    void    setDeltaTempsTir(u32);
    u32     getTempsTir() const;
    u32     getDeltaTempsTir() const;

    void    setTempsRecharge(u32);
    void    setDeltaTempsRecharge(u32);
    u32     getTempsRecharge() const;
    u32     getDeltaTempsRecharge() const;

    void    setTempsTorche(u32);
    void    setDeltaTempsTorche(u32);
    u32     getTempsTorche() const;
    u32     getDeltaTempsTorche() const;

    void    setTempsSwitchArme(u32);
    void    setDeltaTempsSwitchArme(u32);
    u32     getTempsSwitchArme() const;
    u32     getDeltaTempsSwitchArme() const;

    void    setTempsDebViser(u32);
    void    setTempsFinViser(u32);
    void    setDeltaTempsViser(u32);
    u32     getTempsDebViser() const;
    u32     getTempsFinViser() const;
    u32     getDeltaTempsViser() const;

    void    setTempsFlash(u32);
    void    setDeltaTempsFlash(u32);
    u32     getTempsFlash() const;
    u32     getDeltaTempsFlash() const;

    void    majsante (int maj_sant);
    u32     getSante() const;

    bool    getPossesM9() const;
    void    setPossesM9(bool);
    bool    getPossesUzi() const;
    void    setPossesUzi(bool);

private :

    std::vector<CArme*> m_tableArmes;
    bool    m_shooting;
    bool    m_aiming;
    bool    m_reloading;
    bool    m_idle;
    bool    m_stopShoot;
    bool    m_stopReload;
    bool    m_possesM9;
    bool    m_possesUzi;

    u32     m_sante;
    u32     m_tempsTir;
    u32     m_deltaTempsTir;
    u32     m_tempsRecharge;
    u32     m_deltaTempsRecharge;
    u32     m_tempsTorche;
    u32     m_deltaTempsTorche;
    u32     m_tempsSwitchArme;
    u32     m_deltaTempsSwitchArme;
    u32     m_debutViser;
    u32     m_finViser;
    u32     m_deltaTempsViser;
    u32     m_tempsFlash;
    u32     m_deltaTempsFlash;

};

#endif
