//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#include "Joueur.h"
#include "Arme.h"
CJoueur::CJoueur()
{
    m_shooting              = false;
    m_aiming                = false;
    m_reloading             = false;
    m_idle                  = true;
    m_stopShoot             = false;
    m_stopReload            = false;

    m_tempsTir              = 0;
    m_deltaTempsTir         = 0;
    m_tempsRecharge         = 0;
    m_deltaTempsRecharge    = 0;
    m_tempsTorche           = 0;
    m_deltaTempsTorche      = 0;
    m_tempsSwitchArme       = 0;
    m_deltaTempsSwitchArme  = 0;
    m_debutViser            = 0;
    m_finViser              = 0;
    m_deltaTempsViser       = 0;
}

CJoueur::~CJoueur()
{

}

CArme* CJoueur::getArme(int i)
{
    return m_tableArmes[i];
}

void CJoueur::initArmes()
{
    //CArme             (std::string        nom,   degats, maxChargeur,  maxMunChargeur, cadenceTir, cadenceRecharge,   coup par coup ?);
    m_tableArmes.push_back(new CArme(L"Knife",          0,       0,              0,         125,        1300,               true)); // [0]
    m_tableArmes.push_back(new CArme(L"Beretta M9",     25,     50,             12,         150,        1300,               true)); // [1]
    m_tableArmes.push_back(new CArme(L"IMI Uzi",        25,     50,             32,         100,        1300,               false)); // [2]

    //m_tableArmes.push_back(new CArme(L"Assault Rifle",  25,     50,             12,         125,        1300,               false)); // [3]
    //m_tableArmes.push_back(new CArme(L"Shotgun",        25,     50,             12,         125,        1300,               false)); // [4]
    //m_tableArmes.push_back(new CArme(L"Sniper",         25,     50,             12,         125,        1300,               false)); // [5]

}


bool CJoueur::isShooting() const
{
    return m_shooting;
}

void CJoueur::setShooting(bool maj)
{
    m_shooting=maj;
}

bool CJoueur::isAiming() const
{
    return m_aiming;
}

void CJoueur::setAiming (bool maj)
{
    m_aiming=maj;
}

bool CJoueur::isReloading() const
{
    return m_reloading;
}

void CJoueur::setReloading(bool maj)
{
    m_reloading=maj;
}

bool CJoueur::isIdle() const
{
    return m_idle;
}

void CJoueur::setIdle(bool maj)
{
    m_idle=maj;
}

//!---------------------------//
int CJoueur::getSizeTableArmes() const
{
    return m_tableArmes.size();
}


bool CJoueur::canShoot() const
{
    return (m_stopShoot)?false:true;
}

bool CJoueur::canReload() const
{
    return (m_stopReload)?false:true;
}

void CJoueur::setShootAbility(bool update)
{
    m_stopShoot = (update)?false:true;
}

void CJoueur::setReloadAbility(bool update)
{
    m_stopReload = (update)?false:true;
}

void CJoueur::setTempsTir(u32 maj_tempsTir)
{
    m_tempsTir = maj_tempsTir;
}

void CJoueur::setDeltaTempsTir(u32 maj_deltaTempsTir)
{
    m_deltaTempsTir = maj_deltaTempsTir;
}

u32 CJoueur::getTempsTir() const
{
    return m_tempsTir;
}

u32 CJoueur::getDeltaTempsTir() const
{
    return m_deltaTempsTir;
}

void CJoueur::setTempsRecharge(u32 maj_tempsRecharge)
{
    m_tempsRecharge = maj_tempsRecharge;
}

void CJoueur::setDeltaTempsRecharge(u32 maj_deltaTempsRecharge)
{
    m_deltaTempsRecharge = maj_deltaTempsRecharge;
}

u32 CJoueur::getTempsRecharge() const
{
    return m_tempsRecharge;
}

u32 CJoueur::getDeltaTempsRecharge() const
{
    return m_deltaTempsRecharge;
}

void CJoueur::setTempsTorche(u32 maj_tempsTorche)
{
    m_tempsTorche = maj_tempsTorche;
}

void CJoueur::setDeltaTempsTorche(u32 maj_deltaTempsTorche)
{
    m_deltaTempsTorche = maj_deltaTempsTorche;
}

u32 CJoueur::getTempsTorche() const
{
    return m_tempsTorche;
}

u32 CJoueur::getDeltaTempsTorche() const
{
    return m_deltaTempsTorche;
}

void CJoueur::setTempsSwitchArme(u32 maj_tempsSwitchArme)
{
    m_tempsSwitchArme = maj_tempsSwitchArme;
}

void CJoueur::setDeltaTempsSwitchArme(u32 maj_deltaTempsSwitchArme)
{
    m_deltaTempsSwitchArme = maj_deltaTempsSwitchArme;
}

u32 CJoueur::getTempsSwitchArme() const
{
    return m_tempsSwitchArme;
}

u32 CJoueur::getDeltaTempsSwitchArme() const
{
    return m_deltaTempsSwitchArme;
}

void CJoueur::setTempsFlash(u32 maj_tempsFlash)
{
    m_tempsFlash = maj_tempsFlash;
}

void CJoueur::setDeltaTempsFlash(u32 maj_deltaTempsFlash)
{
    m_deltaTempsFlash = maj_deltaTempsFlash;
}

u32 CJoueur::getTempsFlash() const
{
    return m_tempsFlash;
}

u32 CJoueur::getDeltaTempsFlash() const
{
    return m_deltaTempsFlash;
}

void CJoueur::setTempsDebViser(u32 maj_debutViser)
{
    m_debutViser = maj_debutViser;
}

void CJoueur::setTempsFinViser(u32 maj_finViser)
{
    m_finViser = maj_finViser;
}

void CJoueur::setDeltaTempsViser(u32 maj_deltaTempsViser)
{
    m_deltaTempsViser = maj_deltaTempsViser;
}

u32 CJoueur::getTempsDebViser()const
{
    return m_debutViser;
}

u32 CJoueur::getTempsFinViser() const
{
    return m_finViser;
}

u32 CJoueur::getDeltaTempsViser() const
{
    return m_deltaTempsViser;
}

u32 CJoueur::getSante() const
{
    return m_sante;
}
void CJoueur::majsante (int maj_sant)
{
    m_sante += maj_sant;
    if(m_sante >100)
    {
        m_sante = 100;
    }
}
bool CJoueur::getPossesM9 () const
{
    return m_possesM9;
}
void CJoueur::setPossesM9 (bool maj)
{
    m_possesM9 = maj;
}
bool CJoueur::getPossesUzi () const
{
    return m_possesUzi;
}
void CJoueur::setPossesUzi (bool maj)
{
    m_possesUzi = maj;
}
