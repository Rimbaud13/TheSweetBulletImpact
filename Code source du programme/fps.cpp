//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#include <sstream>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <irrlicht.h>
#include <irrBullet.h>
#include <irrklang.h>
#include "fps.h"
#include "joueur.h"
#include "framework.h"
#include "decalscenenode.h"
#include "Zombie.h"
#include "Niveau.h"
#include "Items.h"
#include "ScoreManager.h"

using namespace irr;
using namespace irrklang;
using namespace core;
using namespace scene;
using namespace video;

enum EKeyState
{
    ksDown,
    ksHeldDown,
    ksUp
};


enum
{
    //définit les node sélectionnables par le ray cast
    ID_IsNotPickable = 0,
    IDFlag_IsPickable = 1 << 0,
};

EKeyState keys[KEY_KEY_CODES_COUNT];

CFps::CFps()
{
    m_joueur                        = new CJoueur();
    m_map                           = new CLevel("Test");
    m_scoreManager                  = new CScore();
    m_soundEngine                   = createIrrKlangDevice();
    m_berettaShootSound             = m_soundEngine->addSoundSourceFromFile("SOUNDS/Beretta_fire.wav");
    m_uziShootSound                 = m_soundEngine->addSoundSourceFromFile("SOUNDS/Uzi_fire.wav");
    m_reloadSound                   = m_soundEngine->addSoundSourceFromFile("SOUNDS/reload.wav");
    m_outOfAmmoSound                = m_soundEngine->addSoundSourceFromFile("SOUNDS/click.wav");
    m_torcheSound                   = m_soundEngine->addSoundSourceFromFile("SOUNDS/torche.wav");
    m_pickupSound                   = m_soundEngine->addSoundSourceFromFile("SOUNDS/ammoPickup.wav");
    m_frenzy1                       = m_soundEngine->addSoundSourceFromFile("SOUNDS/fz_frenzy1.wav");
    m_frenzy2                       = m_soundEngine->addSoundSourceFromFile("SOUNDS/fz_frenzy2.wav");
    m_frenzy3                       = m_soundEngine->addSoundSourceFromFile("SOUNDS/fz_frenzy3.wav");
    m_frenzy4                       = m_soundEngine->addSoundSourceFromFile("SOUNDS/fz_frenzy4.wav");
    m_frenzy5                       = m_soundEngine->addSoundSourceFromFile("SOUNDS/fz_frenzy5.wav");
    m_frenzy6                       = m_soundEngine->addSoundSourceFromFile("SOUNDS/fz_frenzy6.wav");
    m_hit1                          = m_soundEngine->addSoundSourceFromFile("SOUNDS/Touche_Zombie1.wav");
    m_hit2                          = m_soundEngine->addSoundSourceFromFile("SOUNDS/Touche_Zombie2.wav");
    m_hit3                          = m_soundEngine->addSoundSourceFromFile("SOUNDS/Touche_Zombie3.wav");
    m_hurt1                         = m_soundEngine->addSoundSourceFromFile("SOUNDS/hurt1.wav");
    m_hurt2                         = m_soundEngine->addSoundSourceFromFile("SOUNDS/hurt2.wav");
    m_hurt3                         = m_soundEngine->addSoundSourceFromFile("SOUNDS/hurt3.wav");
    m_themeAction1                  = m_soundEngine->addSoundSourceFromFile("SOUNDS/theme_action1.wav");
    m_themeThrill1                  = m_soundEngine->addSoundSourceFromFile("SOUNDS/theme_thrill1.wav");
    m_nombre_score                  = 0;
    m_nombre_round                  = 1;
    m_nombre_zombiesParRound        = 0;
    m_nombre_balles                 = 7;
    m_nombre_chargeurs              = 0;
    m_nextDecal                     = 0;
    m_zombieRestants                = 0;
    m_maxDecals                     = 50;
    m_parseurDouilles               = 0;
    m_parseurZombies                = 0;
    m_parseurCreationZombies        = 0;
    m_maxDouilles                   = 30;
    m_parseurChargeurs              = 0;
    m_maxChargeurs                  = 5;
    m_angleArme                     = 0;
    m_armeActuelle                  = 1;
    m_tempSwitchArme                = 1;
    m_animViser                     = 0;
    m_animDeviser                   = 0;
    m_FPS                           = 0;
    m_lightnodeTorche               = 0;
    m_muzzleflash                   = 0;
    m_muzzlelumiere                 = 0;
    m_repereDouilles                = 0;
    m_repereDouilles2               = 0;
    m_vel                              ;
    m_LASTFPS                       = -1;
    m_MAXFPS                        = 0;
    m_MINFPS                        = 1000;
    m_delaiPourEjecterChargeur      = 0;
    m_deltaDelaiPourEjecterChargeur = 0;
    m_delaiIA                       = 0;
    m_deltaDelaiIA                  = 0;
    m_chronoIA                      = 0;
    m_deltaChronoIA                 = 0;
    m_ZombieLoaderCount             = 0;
    m_delaiItemAB                    = 0;
    m_deltaDelaiItemAB                = 0;
    m_parseurItemAB                   = 0;
    m_previousItemLocationAB          = 0;
    m_activerEjectionChargeur       = false;
    m_drawHUD                       = true;
    m_drawFPS                       = false;
    m_minFPSActive                  = false;
    m_wipBlocker                    = false;
    m_lampeTorche                   = true;
    m_activerZoneDebug              = false;
    m_shootingRay                   = false;
    m_pickupRay                     = false;
    m_tir                           = false;
    m_chronoIASwitcher              = false;
    m_songSwitcher                  = false;

}


bool CFps::run()
{
    //!/////////////////////////////////////////////////////////////
    //! QUELQUES APPELS PRELIMINAIRES QUI JOUENT LE ROLE D'OPTIONS //
    //!/////////////////////////////////////////////////////////////

    char C = 0;
    std::string largeur = ("");
    std::string hauteur = ("");
    int largeurdevice=0;
    int hauteurdevice=0;

    // Ask the user for the driver type.
    std::cout   <<"================================================================================" <<std::endl;
    std::cout   <<"  ______         __ __         __     _______                             __   " <<std::endl;
    std::cout   <<" |   __ \ .--.--.|  |  |.-----.|  |_  |_     _|.--------.-----.---.-.----.|  |_" <<std::endl;
    std::cout   <<" |   __ <|  |  ||  |  ||  -__||   _|  _|   |_ |        |  _  |  _  |  __||   _|" <<std::endl;
    std::cout   <<" |______/|_____||__|__||_____||____| |_______||__|__|__|   __|___._|____||____|" <<std::endl;
    std::cout   <<"                                                       |__|                    " <<std::endl;
    std::cout   <<"" <<std::endl;
    std::cout   <<"                             A First Person Shooter                            "<<std::endl;
    std::cout   <<"                    made by Roussel Nicolas & Kieliger Leandro                 " <<std::endl;
    std::cout   <<"================================================================================" <<std::endl;

    std::cout	<< "==Version=1=2=5==" << std::endl;
    std::cout   <<"" <<std::endl;
    std::cout   <<"Touches de deplacement: W, A, S, D et ESPACE pour sauter" <<std::endl;
    std::cout   <<"Touches d'action: E, F, R, P, bouton gauche et droit de la souris" <<std::endl;
    std::cout   <<"" <<std::endl;
    std::cout   <<"LISEZ LE FICHIER INSTRUCTIONS.TXT POUR PLUS D'INFORMATIONS" <<std::endl;
    std::cout   <<"" <<std::endl;
    std::cout   <<"Alt+F4 pour quitter" <<std::endl;
    std::cout   <<"" <<std::endl;
    std::cout   <<"" <<std::endl;
    std::cout	<< "Selectionnez votre resolution d'ecran: (Maximum: 2560x2048p Minimum: 1024x600p)" << std::endl;
    std::cout   << "largeur (en pixels): " ;
    std::cin >> largeur;
    std::cout   << "hauteur (en pixels): ";
    std::cin >> hauteur;

    std::istringstream numLargeur( largeur );
    std::istringstream numHauteur( hauteur );

    numLargeur >> largeurdevice;
    numHauteur >> hauteurdevice;

    while(largeurdevice>2560 || largeurdevice <1024 || hauteurdevice > 2048 || hauteurdevice<600)
    {
        std::cout	<< "Selectionnez votre resolution d'ecran: " << std::endl;
    std::cout   << "largeur (en pixels): " ;
    std::cin >> largeur;
    std::cout   << "hauteur (en pixels): ";
    std::cin >> hauteur;

    std::istringstream numLargeur( largeur );
    std::istringstream numHauteur( hauteur );

    numLargeur >> largeurdevice;
    numHauteur >> hauteurdevice;
    }

    // create device
    device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(largeurdevice,hauteurdevice), 32 , false, true, false, this);
    if (!device)
    {
        return 1;
    }


    //device->setEventReceiver(this);
    device->getCursorControl()->setVisible(false);

    //!/////////////////////////////
    //! Quelques options de debug //
    //!/////////////////////////////
    debugPos = false;
    debugMode = false;
    drawProperties = false;
    drawWireFrame = false;
    m_wipBlocker = false;


    //!///////////////////////////////
    //! Creation de irrBullet World //
    //!///////////////////////////////
    world = createIrrBulletWorld(device, true, false);

    world->setDebugMode(EPDM_NoHelpText);
    world->setGravity(vector3df(0,-9.81,0));


    u32 TimeStamp = device->getTimer()->getTime();
    u32 DeltaTime = 0;


    //!/////////////////////////////////////////////////
    //! Création de pointeurs pour simplifier le code //
    //!/////////////////////////////////////////////////
    gui::IGUIEnvironment *gui = device->getGUIEnvironment();
    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();
    scene::ISceneCollisionManager* collMan = smgr->getSceneCollisionManager();

    InitFramework();

    //!//////////////////////
    //! Ajout des lumières //
    //!//////////////////////
    smgr->setShadowColor(video::SColor(150,0,0,0));
    //lampe torche
    m_lightnodeTorche = smgr->addLightSceneNode(0, vector3df(0,0,0), video::SColorf(1.0f,1.0f,1.0f, 1.0f), 100.0f);
    //m_lightnodeTorche->getLightData().Type = ELT_SPOT;
    //m_lightnodeTorche->getLightData().OuterCone = 30.0f;
    m_lightnodeTorche->getLightData().CastShadows = false;
    m_neonTex = driver->getTexture("MODELS/OTHER/neon_tex.png");

    //eclairage map
    for(int x=0; x<600; x+=100)
    {
        for(int z=100; z<300; z+=125)
        {

            IMeshSceneNode* pointLum = smgr->addMeshSceneNode(smgr->getMesh("MODELS/OTHER/neon.obj"));
            pointLum->setMaterialTexture(0,m_neonTex);
            pointLum->setPosition(vector3df(x,45,z));
            ILightSceneNode* lum = smgr->addLightSceneNode(pointLum, vector3df(0,-1.5,0), video::SColorf(0.9f,0.9f, 0.9f), 70.0f);
            lum->getLightData().CastShadows = false;

            m_tableLumieres.push_back(lum);
            m_tablePointLum.push_back(pointLum);

        }
    }


    //MUZZLEFLASH
    m_muzzlelumiere = smgr->addLightSceneNode(0,vector3df(0,0,0), video::SColorf(1.0f,1.0f, 1.0f), 100.0f);
    m_muzzleflash = smgr->addBillboardSceneNode(0, dimension2d<f32>(10, 10));
    m_muzzleflash->setMaterialFlag(video::EMF_LIGHTING, false);
    m_muzzleflash->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    m_muzzleflash->setMaterialTexture(0, driver->getTexture("TEXTURES/BERETTAM9/particlewhite.bmp"));


    //!////////////////////////////////////
    //! Création des tables associatives //
    //!////////////////////////////////////
    core::map<scene::ISceneNode*, IRigidBody*> NodeBodyMap;
    core::map<scene::IAnimatedMeshSceneNode*, CZombie*> NodeZombieMap;
    core::map<scene::IAnimatedMeshSceneNode*, CAmmoBox*> NodeItemAmmoBoxMap;

    //!///////////////////////////////////////////
    //! Initialisations des touches (relachées) //
    //!///////////////////////////////////////////
    for (int i=0; i<KEY_KEY_CODES_COUNT; i++)
    {
        keys[i] = ksUp;
    }

    //!//////////////////////////////////////////
    //! Réglage du niveau sonore des bruitages //
    //!//////////////////////////////////////////
    m_berettaShootSound->setDefaultVolume(0.0f);
    m_soundEngine->play2D(m_berettaShootSound);
    m_berettaShootSound->setDefaultVolume(0.4f);
    m_uziShootSound->setDefaultVolume(0.4f);

    {
        //!GESTION DE LA DISTANCE MINIMALE DU SON
        /*  m_hit1->setDefaultMinDistance(500.0f);
          m_hit2->setDefaultMinDistance(500.0f);
          m_hit3->setDefaultMinDistance(500.0f);

          m_frenzy1->setDefaultMinDistance(500.0f);
          m_frenzy2->setDefaultMinDistance(500.0f);
          m_frenzy3->setDefaultMinDistance(500.0f);
          m_frenzy4->setDefaultMinDistance(500.0f);
          m_frenzy5->setDefaultMinDistance(500.0f);
          m_frenzy6->setDefaultMinDistance(500.0f);*/
    }
    m_soundEngine->setDefault3DSoundMinDistance(200.0f);

    {
        //!GESTION DU VOLUME DES ZOMBIES
        /*  m_hit1->setDefaultVolume(2.0f);
          m_hit2->setDefaultVolume(2.0f);
          m_hit3->setDefaultVolume(2.0f);

          m_frenzy1->setDefaultVolume(30.0f);
          m_frenzy2->setDefaultVolume(30.0f);
          m_frenzy3->setDefaultVolume(30.0f);
          m_frenzy4->setDefaultVolume(30.0f);
          m_frenzy5->setDefaultVolume(30.0f);
          m_frenzy6->setDefaultVolume(30.0f);*/
    }
    m_themeAction1->setDefaultVolume(0.4f);

    m_soundEngine->setSoundVolume(1.0f);
    m_soundEngine->play2D(m_themeThrill1);




    //!/////////////////////
    //! Ajout de la camera//
    //!/////////////////////
    camera = smgr->addCameraSceneNodeFPS(0, 100.0f, 0.3f, ID_IsNotPickable, 0,0, true);
    camera->setAspectRatio((largeurdevice*1.0f)/(hauteurdevice*1.0f));
    camera->setTarget(core::vector3df(200,18,2000));
    camera->setFarValue(2000.0f);
    camera->setNearValue(0.5f);

    //IMeshSceneNode* cameraBoxNode = smgr->addSphereSceneNode(8.0f,16);
    IMeshSceneNode* cameraBoxNode = smgr->addMeshSceneNode(smgr->getMesh("MODELS/OTHER/cameraBox.obj"));

    cameraBoxNode->setVisible(false);
    //!cameraBoxNode->setPosition(core::vector3df(154,8,-180));
    cameraBoxNode->setPosition(core::vector3df(500,20,100));
    ICollisionShape* cameraShape = new IConvexHullShape(cameraBoxNode, cameraBoxNode->getMesh(), 1);
    //ICollisionShape* cameraShape = new IBoxShape(cameraBoxNode,80,false);
    IRigidBody *cameraBody;
    cameraBody = world->addRigidBody(cameraShape);
    cameraBody->setActivationState(EAS_DISABLE_DEACTIVATION);
    cameraBody->setFriction(0.01f);
    cameraBody->setRestitution(0.1f);


    //!///////////////////
    //! Ajout de la map //
    //!///////////////////
    m_map->loadMap3D(smgr, driver, world);
    m_map->loadSkyDome(smgr, driver);

    //!////////////////////////////////////////
    //! Ajout des caractéristiques du joueur //
    //!////////////////////////////////////////
    m_joueur->majsante(100);

    //!///////////////////////////////
    //! Ajout du flingue (pew pew !)//
    //!///////////////////////////////
    m_joueur->initArmes();

    for(int i = 0; i < m_joueur->getSizeTableArmes() ; i++)
    {
        m_joueur->getArme(i)->Init3D(smgr, driver, camera);
        m_joueur->getArme(i)->setArmeActive(false);
    }
    m_repereDouilles = smgr->addCubeSceneNode(1);
    if(!debugMode)
    {
        m_repereDouilles->setVisible(false);
    }
    m_repereDouilles2 = smgr->addCubeSceneNode(1);
    if(!debugMode)
    {
        m_repereDouilles2->setVisible(false);
    }
    m_joueur->getArme(m_armeActuelle)->getGunMesh()->addChild(m_lightnodeTorche);
    m_joueur->getArme(m_armeActuelle)->getGunMesh()->addChild(m_muzzlelumiere);
    m_joueur->getArme(m_armeActuelle)->getGunMesh()->addChild(m_repereDouilles);
    m_joueur->getArme(m_armeActuelle)->getGunMesh()->addChild(m_repereDouilles2);
    m_lightnodeTorche->setPosition(vector3df(0.0f,0.0f,3.0f));
    m_muzzlelumiere->setPosition(vector3df(0,3.5,4));
    m_repereDouilles->setPosition(vector3df(0.0f,3.0f,-1.0f));
    m_repereDouilles2->setPosition(vector3df(3.0f,7.0f,-1.0f));

    m_joueur->getArme(m_armeActuelle)->setArmeActive(true);

    m_joueur->getArme(1)->majMunition(100);
    m_joueur->getArme(1)->majChargeur(5);

    m_joueur->getArme(2)->majMunition(100);
    m_joueur->getArme(2)->majChargeur(0);

    m_joueur->setPossesM9(true);
    m_joueur->setPossesUzi(true);

    //!///////
    //! WIP //
    //!///////


    int nombreCaisse =2;
    int nombreColonne = 2;
    int nombreLigne = 2;
    // des caisses pour jouer =)
    for (int k= 100; k<(100+8*nombreLigne); k+=8)
    {
        for(int i=400; i<(400+8*nombreColonne); i+=8)
        {
            for(int j=8; j<(8+8*nombreCaisse); j+=8)
            {
                addCrate(vector3df(i,j,k), vector3df(4,4,4),40, NodeBodyMap);
            }
        }
    }




    //!//////////////////////////////////////////
    //! HEAD UP DISPLAY --- PARTIE GRAPHIQUE 2D//
    //!//////////////////////////////////////////
    gui::IGUIFont *fontHUD = gui->getFont("GUI/HUD/fontHUDv2.png");

    // hud_MUNITIONS
    ITexture *hud_fondBallesChargeurs = driver->getTexture("GUI/HUD/HUDetiquette_doublecut_vert250px.png");
    dimension2d<u32> m_dimenfondBallesChargeurs = hud_fondBallesChargeurs->getSize ();
    position2d<irr::s32> fondBallesChargeurs;
    fondBallesChargeurs.X = m_dimenfondBallesChargeurs.Width;
    fondBallesChargeurs.Y = m_dimenfondBallesChargeurs.Height;
    gui::IGUIImage *GUIfondBallesChargeurs = gui->addImage(hud_fondBallesChargeurs, position2d<s32>
            (largeurdevice/2 - fondBallesChargeurs.X/2,hauteurdevice -fondBallesChargeurs.Y), true);

    gui::IGUIStaticText *hud_balles = gui->addStaticText(L"",
                                      core::rect<s32>(largeurdevice/2 -35,hauteurdevice-fondBallesChargeurs.Y +25,largeurdevice/2 + fondBallesChargeurs.X/2,
                                              largeurdevice), false, true, 0, -1, false);
    hud_balles->setOverrideFont(fontHUD);
    hud_balles->setOverrideColor(video::SColor (255,225,0,0)) ;

    ITexture *hud_ImgBalles = driver->getTexture("GUI/HUD/HUDbullet20px.png");
    dimension2d<u32> m_dimenImgBalles = hud_ImgBalles->getSize ();
    position2d<irr::s32> ImgBalles;
    ImgBalles.X = m_dimenImgBalles.Width;
    ImgBalles.Y = m_dimenImgBalles.Height;
    gui::IGUIImage *GUIballes = gui->addImage(hud_ImgBalles,position2d<s32>(largeurdevice/2 - fondBallesChargeurs.X/2 +20,
                                hauteurdevice -fondBallesChargeurs.Y+25), true);


    gui::IGUIStaticText *hud_chargeur = gui->addStaticText(L"",
                                        core::rect<s32>(largeurdevice/2,hauteurdevice-fondBallesChargeurs.Y +25,largeurdevice/2 + fondBallesChargeurs.X/2,
                                                largeurdevice), false, true, 0, -1, false);
    hud_chargeur->setOverrideFont(fontHUD);
    hud_chargeur->setOverrideColor(video::SColor (255,225,0,0));

    ITexture *hud_ImgChargeurs = driver->getTexture("GUI/HUD/HUD_mag20px.png");
    dimension2d<u32> m_dimenImgChargeurs = hud_ImgChargeurs->getSize ();
    position2d<irr::s32> ImgChargeurs;
    ImgChargeurs.X = m_dimenImgChargeurs.Width;
    ImgChargeurs.Y = m_dimenImgChargeurs.Height;
    gui::IGUIImage *GUIchargeurs = gui->addImage(hud_ImgChargeurs,position2d<s32>(largeurdevice/2 + fondBallesChargeurs.X/2 - 40,
                                   hauteurdevice -fondBallesChargeurs.Y+25), true);


    gui::IGUIStaticText *hud_munitions = gui->addStaticText(L"MUNITIONS",
                                         core::rect<s32>(largeurdevice/2 - 65,hauteurdevice-fondBallesChargeurs.Y,largeurdevice/2 + fondBallesChargeurs.X/2,
                                                 largeurdevice), false, true, 0, -1, false);
    hud_munitions->setOverrideFont(fontHUD);
    hud_munitions->setOverrideColor(video::SColor (255,225,0,0));

    //hud_chrono
    ITexture *hud_ImgChrono = driver->getTexture("GUI/HUD/HUDetiquetteUpsidedown250px.png");
    dimension2d<u32> m_dimenchrono = hud_ImgChrono->getSize ();
    position2d<s32> chrono;
    chrono.X = m_dimenchrono.Width;
    chrono.Y = m_dimenchrono.Height;
    gui::IGUIImage *GUIchrono = gui->addImage(hud_ImgChrono, position2d<s32>(0,0), true);
    gui::IGUIStaticText *hud_chrono = gui->addStaticText(L"Chrono: ",
                                      core::rect<s32>(13,13,chrono.X,chrono.Y), false, true, 0, -1, false);
    hud_chrono->setOverrideFont(fontHUD);
    hud_chrono->setOverrideColor(video::SColor (255,225,0,0));


    //hud_sante
    ITexture *hud_sante = driver->getTexture("GUI/HUD/HUDetiquette_reverse250px.png");
    dimension2d<u32> m_dimensante = hud_sante->getSize ();
    position2d<s32> sante;
    sante.X = m_dimensante.Width;
    sante.Y = m_dimensante.Height;
    gui::IGUIImage *GUIsante = gui->addImage(hud_sante, position2d<s32>(0,hauteurdevice - sante.Y), true);

    ITexture *hud_croixSante = driver->getTexture("GUI/HUD/HUDcross40px.png");
    dimension2d<u32> m_dimencroixSante = hud_croixSante->getSize ();
    position2d<s32> croixSante;
    croixSante.X = m_dimencroixSante.Width;
    croixSante.Y = m_dimencroixSante.Height;
    gui::IGUIImage *GUIcroixSante = gui->addImage(hud_croixSante, position2d<s32>(2,hauteurdevice - sante.Y +5), true);

    gui::IGUIStaticText *hud_santeTexte = gui->addStaticText(L"",
                                          core::rect<s32>(45,hauteurdevice-sante.Y+13,sante.X,
                                                  hauteurdevice), false, true, 0, -1, false);
    hud_santeTexte->setOverrideFont(fontHUD);
    hud_santeTexte->setOverrideColor(video::SColor (255,225,0,0));

    gui::IGUIStaticText *hud_santeChiffre = gui->addStaticText(L"/100",
                                            core::rect<s32>(185,hauteurdevice-sante.Y+13,sante.X,
                                                    hauteurdevice), false, true, 0, -1, false);
    hud_santeChiffre->setOverrideFont(fontHUD);
    hud_santeChiffre->setOverrideColor(video::SColor (255,225,0,0));

    //hud_armes
    ITexture *hud_armes = driver->getTexture("GUI/HUD/HUDetiquette_arme400px.png");
    dimension2d<u32> m_dimenArmes = hud_armes->getSize ();
    position2d<s32> armes;
    armes.X = m_dimenArmes.Width;
    armes.Y = m_dimenArmes.Height;
    gui::IGUIImage *GUIarmes = gui->addImage(hud_armes, position2d<s32>(largeurdevice/2-armes.X/2,0),true);

    ITexture *hud_silM9 = driver->getTexture("GUI/HUD/HUDsilhouette_m9.png");
    dimension2d<u32> m_dimensilM9 = hud_silM9->getSize ();
    position2d<s32> silM9;
    silM9.X = m_dimenArmes.Width;
    silM9.Y = m_dimenArmes.Height;
    ITexture *hud_silUzi = driver->getTexture("GUI/HUD/HUDsilhouette_uzi.png");
    dimension2d<u32> m_dimensilUzi = hud_silUzi->getSize ();
    position2d<s32> silUzi;
    silUzi.X = m_dimensilUzi.Width;
    silUzi.Y = m_dimensilUzi.Height;


    //hud_viseur
    ITexture *hud_viseurvert = driver->getTexture("GUI/HUD/viseur vertical.png");
    ITexture *hud_viseurhori = driver->getTexture("GUI/HUD/viseur horizontal.png");

    //hud_nomarme
    ITexture *hud_ImgNomarme = driver->getTexture("GUI/HUD/HUDetiquette250px.png");
    dimension2d<u32> m_dimenNomarme = hud_ImgNomarme->getSize ();
    position2d<irr::s32> nomarme;
    nomarme.X = m_dimenNomarme.Width;
    nomarme.Y = m_dimenNomarme.Height;
    gui::IGUIImage *GUInomarme = gui->addImage(hud_ImgNomarme, position2d<s32>(largeurdevice - nomarme.X,hauteurdevice - nomarme.Y), true);
    gui::IGUIStaticText *hud_nomarme = gui->addStaticText(L"",
                                       core::rect<s32>(largeurdevice-nomarme.X + 30 , hauteurdevice-nomarme.Y +13,largeurdevice,hauteurdevice), false, true, 0, -1, false);
    hud_nomarme->setOverrideFont(fontHUD);
    hud_nomarme->setOverrideColor(video::SColor (255,225,0,0));

    //hud_score
    ITexture *hud_ImgScore = driver->getTexture("GUI/HUD/HUDetiquette_doublecut_hor250px.png");
    dimension2d<u32> m_dimenScore = hud_ImgScore->getSize ();
    position2d<irr::s32> score;
    score.X = m_dimenScore.Width;
    score.Y = m_dimenScore.Height;
    gui::IGUIImage *GUIscore = gui->addImage(hud_ImgScore, position2d<s32>(largeurdevice - score.X,hauteurdevice - nomarme.Y - score.Y), true);
    gui::IGUIStaticText *hud_score = gui->addStaticText(L"",
                                     core::rect<s32>(largeurdevice-score.X +20, hauteurdevice-nomarme.Y-score.Y+13,largeurdevice,hauteurdevice), false, true, 0, -1, false);
    hud_score->setOverrideFont(fontHUD);
    hud_score->setOverrideColor(video::SColor (255,225,0,0));

    //hud_highscore
    ITexture *hud_ImgHighScore = driver->getTexture("GUI/HUD/HUDetiquette_doublecut_hor250px.png");
    dimension2d<u32> m_dimenHighScore = hud_ImgHighScore->getSize ();
    position2d<irr::s32> highScore;
    highScore.X = m_dimenHighScore.Width;
    highScore.Y = m_dimenHighScore.Height;
    gui::IGUIImage *GUIHighScore = gui->addImage(hud_ImgHighScore, position2d<s32>(largeurdevice - highScore.X,hauteurdevice - nomarme.Y - score.Y - highScore.Y), true);
    gui::IGUIStaticText *hud_highScore = gui->addStaticText(L"High: ",
                                         core::rect<s32>(largeurdevice-highScore.X +20, hauteurdevice-nomarme.Y-score.Y-highScore.Y+13,largeurdevice,hauteurdevice), false, true, 0, -1, false);
    hud_highScore->setOverrideFont(fontHUD);
    hud_highScore->setOverrideColor(video::SColor (255,225,0,0)) ;


    //hud_minimap
    ITexture *hud_minimap = driver->getTexture("GUI/HUD/minimap.png");
    ITexture *hud_minimapPerso = driver->getTexture("GUI/HUD/minimapperso.png");
    ITexture *hud_minimapTexte = driver->getTexture("GUI/HUD/HUDetiquette_minimap100px.png");
    dimension2d<u32> m_dimenMinimap = hud_minimap->getSize ();
    position2d<irr::s32> minimap;
    minimap.X = m_dimenMinimap.Width;
    minimap.Y = m_dimenMinimap.Height;
    dimension2d<u32> m_dimenPerso = hud_minimapPerso->getSize ();
    position2d<irr::s32> minimapPerso;
    minimapPerso.X = m_dimenPerso.Width;
    minimapPerso.Y = m_dimenPerso.Height;
    dimension2d<u32> m_dimenMiniTexte = hud_minimapTexte->getSize ();
    position2d<irr::s32> minimapTexte;
    minimapTexte.X = m_dimenMiniTexte.Width;
    minimapTexte.Y = m_dimenMiniTexte.Height;
    gui::IGUIImage *GUIminimap = gui->addImage(hud_minimap, position2d<s32>(largeurdevice - minimap.X,0), true);
    gui::IGUIImage *GUIminimapTexte = gui->addImage(hud_minimapTexte, position2d<s32>(largeurdevice - minimap.X -minimapTexte.X,0), true);

    //hud_sang
    gui::IGUIInOutFader* fader = device->getGUIEnvironment()->addInOutFader();
    fader->setColor(SColor(0,255,0,0));
    fader->fadeIn(0);


    gui::IGUIFont *fontHUDdebug = gui->getFont("GUI/HUD/fontHUDv2Debug.png");

        //hud_gameover
    ITexture *hud_gameover = driver->getTexture("GUI/HUD/gameover.png");



    // hud_DEBUG
    gui::IGUIStaticText *hud_debug1 = gui->addStaticText(L"",
                                      core::rect<s32>(100, 35,2000,2000), false, true, 0, -1, false);
    hud_debug1->setOverrideColor(video::SColor (255,225,0,0)) ;
    hud_debug1->setOverrideFont(fontHUDdebug);

    gui::IGUIStaticText *hud_debug2 = gui->addStaticText(L"",
                                      core::rect<s32>(100, 60,2000,2000), false, true, 0, -1, false);
    hud_debug2->setOverrideColor(video::SColor (255,225,0,0)) ;
    hud_debug2->setOverrideFont(fontHUDdebug);

    gui::IGUIStaticText *hud_debug3 = gui->addStaticText(L"",
                                      core::rect<s32>(100, 85,2000,2000), false, true, 0, -1, false);
    hud_debug3->setOverrideColor(video::SColor (255,225,0,0)) ;
    hud_debug3->setOverrideFont(fontHUDdebug);

    gui::IGUIStaticText *hud_fps = gui->addStaticText(L"",
                                   core::rect<s32>(70, 10,largeurdevice,hauteurdevice), false, true, 0, -1, false);
    hud_fps->setOverrideFont(fontHUDdebug);
    hud_fps->setOverrideColor(video::SColor (255,255,0,0));


    //! RECUPERATION DU HIGHSCORE

    m_scoreManager->syncHighScore();
    hud_highScore->setText(m_scoreManager->getHighScore().c_str());


//!=================================================================================================//
//!=================================================================================================//
//!=========================================  RENDU  ===============================================//
//!=================================================================================================//
//!=================================================================================================//


    while(device->run())
    {
        if(device->isWindowActive())
        {
            driver->beginScene(true, true, SColor (255,0,0,0));
            smgr->drawAll();
            gui->drawAll();



            //!///////////////////////////////////
            //!  VARIABLES DE SIMPLIFICATION ;) //
            //!///////////////////////////////////
            u32 actualTime = device->getTimer()->getTime();
            CArme* armeJoueur = m_joueur->getArme(m_armeActuelle);
            IAnimatedMeshSceneNode* meshArmeJoueur = m_joueur->getArme(m_armeActuelle)->getGunMesh();
            IAnimatedMeshSceneNode* meshMainDroiteJoueur = m_joueur->getArme(m_armeActuelle)->getHandRMesh();
            IAnimatedMeshSceneNode* meshMainGaucheJoueur = m_joueur->getArme(m_armeActuelle)->getHandLMesh();
            triangle3df hitTriangle;
            vector3df intersection;
            vector3df pos = cameraBoxNode->getAbsolutePosition();
            m_armeActuelle = m_tempSwitchArme;


            //!///////////////////////////////////////////////////
            //! Mise à jour des temps et des différences (delta)//
            //!///////////////////////////////////////////////////
            m_joueur->setDeltaTempsTir(actualTime - m_joueur->getTempsTir());
            m_joueur->setDeltaTempsRecharge(actualTime - m_joueur->getTempsRecharge());
            m_joueur->setDeltaTempsTorche(actualTime - m_joueur->getTempsTorche());
            m_joueur->setDeltaTempsViser(actualTime- m_joueur->getTempsDebViser());
            m_joueur->setDeltaTempsSwitchArme(actualTime - m_joueur->getTempsSwitchArme());
            m_joueur->setDeltaTempsFlash(actualTime - m_joueur->getTempsFlash());
            m_deltaDelaiPourEjecterChargeur = actualTime - m_delaiPourEjecterChargeur;
            m_deltaDelaiIA = actualTime - m_delaiIA;
            m_deltaChronoIA = actualTime - m_chronoIA;
            m_deltaDelaiItemAB = actualTime - m_delaiItemAB;

            DeltaTime = actualTime - TimeStamp;
            TimeStamp = actualTime;

            world->stepSimulation(DeltaTime*0.004f, 120);


            //!/////////////////////////////////////////////////////////
            //! GESTION DES DEPLACEMENTS (la caméra suit un RigidBody)//
            //!/////////////////////////////////////////////////////////

            camera->setPosition(vector3df(pos.X, pos.Y+5, pos.Z));
            m_soundEngine->setListenerPosition(camera->getAbsolutePosition(), camera->getTarget() - camera->getAbsolutePosition());
            m_soundEngine->update();

            matrix4 mat;
            mat.setRotationDegrees(camera->getRotation());

            m_vel = (cameraBody->getLinearVelocity() * vector3df(0, 1, 0));

            if (keys[KEY_KEY_W] == ksHeldDown)
            {
                vector3df forwardDir(vector3df(mat[8],0,mat[10]) * 15);
                m_vel += forwardDir;
            }

            if (keys[KEY_KEY_S] == ksHeldDown)
            {
                vector3df forwardDir(vector3df(mat[8],0,mat[10]) * 15);
                m_vel -= forwardDir;
            }

            if (keys[KEY_KEY_A] == ksHeldDown)
            {
                vector3df rightDir(vector3df(mat[0],0,mat[2]) * 12);
                m_vel -= rightDir;
            }

            if (keys[KEY_KEY_D] == ksHeldDown)
            {
                vector3df rightDir(vector3df(mat[0],0,mat[2]) * 12);
                m_vel += rightDir;
            }

            if (keys[KEY_SPACE] == ksDown)
            {
                if (m_vel.Y < 1 && m_vel.Y > -1)
                {
                    vector3df upDir(vector3df(0,1,0)*15);
                    m_vel += upDir;
                }
            }

            /* if (pos.Y > 28)
             {
                 m_vel = vector3df(m_vel.X,0,m_vel.Z);
             }
             */


            cameraBody->setLinearVelocity(m_vel);
            //cameraBody->faceTarget(camera->getTarget());
            //cameraBody->setAngularVelocity(vector3df(0,0,0));




            //!////////////////////////////////////////////////////
            //! Gestion de la lampe torche (Cpt.Obvious was here)//
            //!////////////////////////////////////////////////////

            m_lightnodeTorche->setVisible((m_lampeTorche)?true:false);

            //!////////////////////////////////////////
            //! TIR                                  //
            //!////////////////////////////////////////

            if(m_joueur->isShooting()
                    && m_joueur->getDeltaTempsTir()>armeJoueur->getCadenceTirArme())
            {
              m_shootingRay = true;

                if(armeJoueur->isLooped() == false)
                {
                    switch(m_armeActuelle)
                    {
                    case 1:
                        armeJoueur->setGunFL(1,35);
                        armeJoueur->setHandRFL(1,35);
                        armeJoueur->setLooped(true);
                        break;
                    case 2:
                        armeJoueur->setGunFL(1,20);
                        armeJoueur->setHandRFL(1,20);
                        armeJoueur->setLooped(true);
                        break;
                    default:
                        armeJoueur->setGunFL(1,30);
                        armeJoueur->setHandRFL(1,30);
                        armeJoueur->setLooped(true);
                        break;
                    }
                    meshArmeJoueur->animateJoints();
                    meshMainDroiteJoueur->animateJoints();
                }

                m_joueur->setTempsFlash(device->getTimer()->getTime());
                m_joueur->setTempsTir(device->getTimer()->getTime());
                m_joueur->getArme(m_armeActuelle)->majMunition(-1);

                m_tableBodiesDouilles.push_back(ejecterDouille(m_repereDouilles->getAbsolutePosition(), m_repereDouilles2->getAbsolutePosition() ,m_vel));
                m_parseurDouilles++;

                if(m_parseurDouilles > m_maxDouilles)
                {
                    m_tableBodiesDouilles[m_parseurDouilles-m_maxDouilles]->remove();
                }

                switch(m_armeActuelle)
                {
                case 1:
                    m_soundEngine->play2D(m_berettaShootSound);
                    break;
                case 2:
                    m_soundEngine->play2D(m_uziShootSound);
                    break;
                default:
                    m_soundEngine->play2D(m_berettaShootSound);
                    break;
                }
            }
            else if(armeJoueur->getMunitions()==0
                    || armeJoueur->isCoupParCoup())
            {
                m_joueur->setShooting(false);
            }

            if (m_joueur->getDeltaTempsFlash() < 30)
            {
                m_muzzlelumiere->setVisible(true);
                m_muzzleflash->setPosition(m_muzzlelumiere->getAbsolutePosition());
            }
            else
            {
                m_muzzlelumiere->setVisible(false);
                m_muzzleflash->setPosition(vector3df(0,-1000,0));
            }


            //!////////////////////////////////////
            //! RECHARGE                         //
            //!////////////////////////////////////

            if(m_joueur->isReloading()
                    && m_joueur->getDeltaTempsRecharge()<armeJoueur->getCadenceRechargeArme()
              )
            {
                if(armeJoueur->isLooped() == false)
                {
                    switch(m_armeActuelle)
                    {
                    case 1:
                        armeJoueur->setGunFL(35,300);
                        armeJoueur->setHandRFL(35,300);
                        armeJoueur->setHandLFL(35,300);
                        armeJoueur->setLooped(true);
                        break;
                    case 2:
                        armeJoueur->setGunFL(35,300);
                        armeJoueur->setHandRFL(35,300);
                        armeJoueur->setHandLFL(35,300);
                        armeJoueur->setLooped(true);
                        break;
                    }
                }
                meshArmeJoueur->animateJoints();
                meshMainDroiteJoueur->animateJoints();
                meshMainGaucheJoueur->animateJoints();

                //effegunct->getShadowLight(1).setPosition(vector3df(gun->getAbsolutePosition().X,gun->getAbsolutePosition().Y ,gun->getAbsolutePosition().Z));
                //effect->getShadowLight(1).setTarget(camera->getTarget());
            }
            else if(m_joueur->getDeltaTempsRecharge()>armeJoueur->getCadenceRechargeArme())
            {
                m_joueur->setReloading(false);
            }


            //!//////////////////////////
            //! REPOS                  //
            //!//////////////////////////
            if(!m_joueur->isReloading()
                    &&!m_joueur->isShooting()
                    && m_joueur->getDeltaTempsTir() > armeJoueur->getCadenceTirArme())
            {
                if(armeJoueur->isLooped() == true)
                {
                    armeJoueur->setGunFL(0,0);
                    armeJoueur->setHandRFL(0,0);
                    armeJoueur->setHandLFL(0,0);
                    armeJoueur->setLooped(false);
                }

                meshArmeJoueur->animateJoints();
                meshMainDroiteJoueur->animateJoints();
                meshMainGaucheJoueur->animateJoints();

                m_muzzlelumiere->setVisible(false);
                m_muzzleflash->setPosition(vector3df(0,-1000,0));
            }

            //!////////////////////////////////////
            //! VISÉE                            //
            //!////////////////////////////////////
            if (m_joueur->isAiming() && m_angleArme < 1)
            {
                m_angleArme += 1.6;
                meshMainDroiteJoueur->setRotation(core::vector3df(0,m_angleArme,0));

                switch(m_armeActuelle)
                {
                case 1:                                                                //A                          B
                    m_animViser = smgr->createFlyStraightAnimator(core::vector3df(2.0f,-1.8f,4.8f),core::vector3df(0.030,-1.53f,3.0f),150, false, false);
                    break;
                case 2:                                                                //A                          B
                    m_animViser = smgr->createFlyStraightAnimator(core::vector3df(2.0f,-1.8f,4.8f),core::vector3df(0.015f,-1.69f,3.7f),150, false, false);
                    break;
                default:                                                               //A                          B
                    m_animViser = smgr->createFlyStraightAnimator(core::vector3df(2.0f,-1.8f,4.8f),core::vector3df(0.030,-1.53f,3.0f),150, false, false);
                    break;
                }

                meshMainDroiteJoueur->addAnimator(m_animViser);
                m_animViser->drop();

            }



            else if (!m_joueur->isAiming() && m_angleArme > -1.6 && m_joueur->getDeltaTempsViser() > 175)
            {
                m_angleArme -= 1.6;
                meshMainDroiteJoueur->setRotation(core::vector3df(0,m_angleArme,0));

                switch(m_armeActuelle)
                {
                case 1:                                                                   //A                          B
                    m_animDeviser = smgr->createFlyStraightAnimator(core::vector3df(0.030,-1.53f,3),core::vector3df(2,-1.8,4.8),150, false, false);
                    break;
                case 2:                                                                   //A                          B
                    m_animDeviser = smgr->createFlyStraightAnimator(core::vector3df(0.015f,-1.69f,3),core::vector3df(2,-1.8,4.8),150, false, false);
                    break;
                default:                                                                  //A                          B
                    m_animDeviser = smgr->createFlyStraightAnimator(core::vector3df(0.030,-1.53f,3),core::vector3df(2,-1.8,4.8),150, false, false);
                    break;
                }

                meshMainDroiteJoueur->addAnimator(m_animDeviser);
                m_animDeviser->drop();
            }


            //!////////////
            //! RAYCASTS //
            //!////////////
            core::line3d<f32> rayTir;
            rayTir.start = camera->getPosition();
            rayTir.end = rayTir.start + (camera->getTarget() - rayTir.start).normalize() * 1000.0f;

            core::line3d<f32> rayPickup;
            rayPickup.start = camera->getPosition();
            rayPickup.end = rayPickup.start + (camera->getTarget() - rayPickup.start).normalize() * 25.0f;



            if(m_shootingRay)
            {
                m_shootingRay = false;

                ISceneNode* selectedSceneNode =collMan->getSceneNodeAndCollisionPointFromRay(rayTir,intersection,hitTriangle,0,0);
                IAnimatedMeshSceneNode* selectedMeshSceneNode = static_cast<IAnimatedMeshSceneNode*>(selectedSceneNode);


                IParticleSystemSceneNode* partSys = createParticleSystem (intersection, hitTriangle.getNormal().normalize()/100, 20, 25,
                                                    SColor(0,255,255,255), SColor(0,255,255,255),
                                                    500.0f, 500.0f,
                                                    0,
                                                    dimension2df(2.f,2.f), dimension2df(4.0f,4.0f),
                                                    "MISC/smoke2.jpg",
                                                    500.0f,
                                                    true,
                                                    EMT_TRANSPARENT_ADD_COLOR,
                                                    true) ;


                if (NodeBodyMap.find(selectedSceneNode))
                {
                    IRigidBody* bodyImpact = NodeBodyMap[selectedSceneNode];

                    core::line3d<f32> relSearch;
                    relSearch.start = selectedSceneNode->getAbsolutePosition();
                    relSearch.end = intersection;

                    bodyImpact->activate();
                    bodyImpact->applyImpulse((rayTir.getVector()/2), relSearch.getVector(), ERBTS_WORLD);
                }

                if (NodeZombieMap.find(selectedMeshSceneNode))
                {
                    CZombie* zombImpact = NodeZombieMap[selectedMeshSceneNode];

                    zombImpact->recevoirDegats(armeJoueur->getDegats());

                    int n = rand()%(3) +1;

                    switch(n)
                    {
                    case 1:
                        m_soundEngine->play3D(m_hit1,intersection);
                        break;
                    case 2:
                        m_soundEngine->play3D(m_hit2,intersection);
                        break;
                    case 3:
                        m_soundEngine->play3D(m_hit3,intersection);
                        break;

                    }

                }
            }

            if(m_pickupRay)
            {
                m_pickupRay = false;

                ISceneNode* selectedSceneNode =collMan->getSceneNodeAndCollisionPointFromRay(rayPickup,intersection,hitTriangle,0,0);
                IAnimatedMeshSceneNode* selectedMeshSceneNode = static_cast<IAnimatedMeshSceneNode*>(selectedSceneNode);

                if (NodeItemAmmoBoxMap.find(selectedMeshSceneNode))
                {
                    CAmmoBox* pickedUpAmmoBox = NodeItemAmmoBoxMap[selectedMeshSceneNode];
                    m_joueur->getArme(m_armeActuelle)->majChargeur(1);
                    pickedUpAmmoBox->destroy();
                    m_soundEngine->play2D(m_pickupSound);
                }

            }

            //!/////////////////////////
            //! AWESOME ITEM MANAGER  //
            //!/////////////////////////

            //! POINTS DE SPAWN POSSIBLES:
            /*      X       Z
                    135     120
                    265     118
                    430     430
                    435     -75
                    650     -370
                    20      -95
                    -235    275
                    78      156
                    -150    -3
            */
            if(m_deltaDelaiItemAB > 45000)
            {
                m_delaiItemAB = actualTime;

                int n = rand()%(10) +1;

                if(n!=m_previousItemLocationAB)
                {
                    std::cout<<"Ammobox was created at spot "<<n<<std::endl;
                    switch(n)
                    {
                    case 1:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(380,2.5f,-280), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 2:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(135,2.5f,120), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 3:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(265,2.5f,-118), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 4:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(430,2.5f,430), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 5:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(435,2.5f,-75), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 6:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(650,2.5f,-370), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 7:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(20,2.5f,-95), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 8:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(-235,2.5f,275), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 9:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(78,2.5f,156), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;
                    case 10:
                        m_tableItemAB.push_back(new CAmmoBox(vector3df(-150,2.5f,-3), 20));
                        m_tableItemAB[m_parseurItemAB]->initItemAmmoBox3D(smgr, driver, NodeItemAmmoBoxMap);
                        m_parseurItemAB++;
                        m_previousItemLocationAB = n;
                        break;

                    }
                }

            }



            //!///////////////////////
            //! AWESOME IA SYSTEM   //
            //!///////////////////////
            int deadCount=0;
            for(int i=0; i<m_tableZombies.size(); i++)
            {
                if(m_tableZombies[i]==0)
                {
                    deadCount++;
                }
            }
            m_zombieRestants = m_tableZombies.size()-deadCount;

            if(m_deltaChronoIA>30000 && m_chronoIASwitcher == false)
            {
                m_chronoIASwitcher=true;
                m_chronoIA = actualTime;
                m_nombre_zombiesParRound = (m_nombre_round*2)+5;
                m_nombre_round++;
            }

            if(m_deltaChronoIA>31000 && m_tableZombies.size()==0 && m_chronoIASwitcher == true)
            {
                m_chronoIASwitcher=false;
                m_chronoIA = actualTime;
            }


            if(m_chronoIASwitcher==true) //! ROUND DE COMBAT
            {
                if(m_ZombieLoaderCount>600 && m_nombre_zombiesParRound!=0)
                {
                    //! SPAWNS POSSIBLES
                    //! 570 20 520
                    //! -230 20 -140
                    m_ZombieLoaderCount=0;
                    m_nombre_zombiesParRound-=1;

                    int n = rand()%(3) +1;

                    switch(n)
                    {
                    case 1:
                        m_tableZombies.push_back(new CZombie(vector3df(570,20,520),200));
                        break;
                    case 2:
                        m_tableZombies.push_back(new CZombie(vector3df(-230,20,-240),200));
                        break;
                    case 3:
                        m_tableZombies.push_back(new CZombie(vector3df(610,20,-411),200));
                        break;
                    }
                    m_tableZombies[m_parseurCreationZombies]->initZombie3D(smgr, driver, world, NodeZombieMap);
                    m_parseurCreationZombies++;
                }
                else
                {
                    m_ZombieLoaderCount++;
                }


                if(m_songSwitcher==false) //! On met du son digne de ce nom
                {
                    m_songSwitcher = true;
                    m_soundEngine->stopAllSounds();
                    m_soundEngine->play2D(m_themeAction1,true);
                }

                if(m_tableZombies.size()!=0 && m_deltaDelaiIA>(1000/(m_tableZombies.size()*5)))
                {
                    m_parseurZombies++;
                    if (m_parseurZombies>m_tableZombies.size()-1)
                    {
                        m_parseurZombies=0;
                    }

                    if(m_tableZombies[m_parseurZombies]!=0)
                    {
                        //! ON CHECK SI LE ZOMBIE DOIT MOURIR
                        if(m_tableZombies[m_parseurZombies]->isAlive()== false)
                        {
                            m_tableZombies[m_parseurZombies]->preDelete();
                            m_tableZombies[m_parseurZombies]=0;
                            m_nombre_score+=100;

                            m_scoreManager->updateHighScore(m_nombre_score);
                            hud_highScore->setText(m_scoreManager->getHighScore().c_str());
                        }
                        //! DEUXIEME CONTROLE AU CAS OU LE ZOMBIE VIENT DE MOURIR, ENSUITE MISE A JOUR DES MOBS
                        if(m_tableZombies[m_parseurZombies]!=0)
                        {
                            m_tableZombies[m_parseurZombies]->updateStatus(pos);
                            //! BRUITAGES ZOMBIES
                            int n = rand()%(100) +1;

                            switch(n)
                            {
                            case 1:
                                m_soundEngine->play3D(m_frenzy1,m_tableZombies[m_parseurZombies]->getPos());
                                break;
                            case 2:
                                m_soundEngine->play3D(m_frenzy2,m_tableZombies[m_parseurZombies]->getPos());
                                break;
                            case 3:
                                m_soundEngine->play3D(m_frenzy3,m_tableZombies[m_parseurZombies]->getPos());
                                break;
                            case 4:
                                m_soundEngine->play3D(m_frenzy4,m_tableZombies[m_parseurZombies]->getPos());
                                break;
                            case 5:
                                m_soundEngine->play3D(m_frenzy5,m_tableZombies[m_parseurZombies]->getPos());
                                break;
                            case 6:
                                m_soundEngine->play3D(m_frenzy6,m_tableZombies[m_parseurZombies]->getPos());
                                break;
                            }

                            //! FIN BRUITAGES
                            if(m_tableZombies[m_parseurZombies]->attaqueJoueur(pos))
                            {
                                m_joueur->majsante(-10);
                                fader->fadeOut(0);
                                fader->fadeIn(500);
                                int n = rand()%(3) +1;
                                switch(n)
                                {
                                case 1:
                                    m_soundEngine->play2D(m_hurt1);
                                    break;
                                case 2:
                                    m_soundEngine->play2D(m_hurt2);
                                    break;
                                case 3:
                                    m_soundEngine->play2D(m_hurt3);
                                    break;

                                }
                            }
                        }
                    }

                    m_delaiIA = actualTime;
                    if(m_tableZombies[m_tableZombies.size()-1]==0)
                    {
                        m_tableZombies.pop_back();
                    }

                }
            }
            else //! INTER-ROUND, on met la musique calme
            {
                if(m_songSwitcher==true)
                {
                    m_songSwitcher = false;
                    m_soundEngine->stopAllSounds();
                    m_soundEngine->play2D(m_themeThrill1,true);
                    m_parseurCreationZombies=0;
                }
            }


            //!////////////
            //! DELAIS   //
            //!////////////

            if(m_deltaDelaiPourEjecterChargeur > 250 && m_activerEjectionChargeur == true)
            {
                m_tableBodiesChargeurs.push_back(ejecterChargeur(m_joueur->getArme(m_armeActuelle)->getGunMesh()));
                m_parseurChargeurs++;

                if(m_parseurChargeurs > m_maxChargeurs)
                {
                    m_tableBodiesChargeurs[m_parseurChargeurs-m_maxChargeurs]->remove();
                }
                m_activerEjectionChargeur = false;
            }

            //hud_Balles 2.0
            //!//////////////////////////////////////////////////////////////////////////////////////////////////////
            //! HUD MISE A JOUR DE L'AFFICHAGE DES MUNITIONS ET DES CHARGEURS RESTANTS ET DE LA MANCHE ET DU VISEUR//
            //!//////////////////////////////////////////////////////////////////////////////////////////////////////

            if(m_drawHUD)
            {
                stringw str_score = L"Score: ";
                str_score += m_nombre_score;
                hud_score->setText(str_score.c_str());


                if (m_joueur->isAiming())
                {
                    /*
                    if(m_activerZoneDebug){
                    driver->draw2DImage(hud_viseurvert, irr::core::position2d<irr::s32>(largeurdevice/2 -1,hauteurdevice/2 -5),
                                            irr::core::rect<irr::s32>(0,0,2,10), 0,
                        irr::video::SColor(255, 255, 255, 255), true);
                    driver->draw2DImage(hud_viseurhori, irr::core::position2d<irr::s32>(largeurdevice/2 -8, hauteurdevice/2 -1),
                                            irr::core::rect<irr::s32>(0,0,16,2), 0,
                        irr::video::SColor(255, 255, 255, 255), true);
                    }
                    */
                }

                else if (!m_joueur->isAiming())
                {
                    /*
                    if(m_activerZoneDebug){
                    driver->draw2DImage(hud_viseurvert, irr::core::position2d<irr::s32>(largeurdevice/2 -1,hauteurdevice/2 -5),
                                            irr::core::rect<irr::s32>(0,0,2,10), 0,
                        irr::video::SColor(255, 255, 255, 255), true);
                    driver->draw2DImage(hud_viseurhori, irr::core::position2d<irr::s32>(largeurdevice/2 -8, hauteurdevice/2 -1),
                                            irr::core::rect<irr::s32>(0,0,16,2), 0,
                        irr::video::SColor(255, 255, 255, 255), true);
                    }
                    */
                }


                if(m_joueur->getPossesM9()&& m_joueur->getSante() > 0)
                {
                    driver->draw2DImage(hud_silM9, position2d<s32>(largeurdevice/2 - armes.X/2,20),
                                        rect<s32>(0,0,100,50),0,
                                        SColor(255, 255, 255, 255), true);
                }
                if(m_joueur->getPossesUzi()&& m_joueur->getSante() > 0)
                {
                    driver->draw2DImage(hud_silUzi, position2d<s32>(largeurdevice/2 - armes.X/2 + 100,20),
                                        rect<s32>(0,0,100,50),0,
                                        SColor(255, 255, 255, 255), true);
                }

                dimension2d<u32> m_dimenMinimap = hud_minimap->getSize ();
                            position2d<irr::s32> minimap;
                            minimap.X = m_dimenMinimap.Width;
                            minimap.Y = m_dimenMinimap.Height;
                            if (m_joueur->getSante() > 0)
                            {
                            driver->draw2DImage(hud_minimap, irr::core::position2d<irr::s32>(largeurdevice - minimap.X,0),
                                                        irr::core::rect<irr::s32>(0,0,minimap.X,minimap.Y), 0,
                                    irr::video::SColor(255, 255, 255, 255), true);
                            }

                            dimension2d<u32> m_dimenPerso = hud_minimapPerso->getSize ();
                            position2d<irr::s32> minimapPerso;
                            minimapPerso.X = m_dimenPerso.Width;
                            minimapPerso.Y = m_dimenPerso.Height;
                            PosCamX = camera->getAbsolutePosition().X;
                            PosCamZ = camera->getAbsolutePosition().Z;
                            if (m_joueur->getSante() > 0)
                            {
                                driver->draw2DImage(hud_minimapPerso, position2d<s32>(largeurdevice - minimap.X + 181 - PosCamX * (313/2530.28), 0 + 1 + 78 + PosCamZ * (214/1740.8)),
                                                irr::core::rect<irr::s32>(0,0,2,2), 0,
                                    irr::video::SColor(255, 255, 255, 255), true);
                            }
//!  A OPTIMISER ==================================================
//!  A OPTIMISER ==================================================
//!  A OPTIMISER ==================================================
//!  A OPTIMISER ==================================================
//!  A OPTIMISER ==================================================
                m_santeHUD = m_joueur->getSante();
                core::stringw str_sante = L"SANTE ";
                str_sante += m_santeHUD;
                hud_santeTexte->setText(str_sante.c_str());

                m_nombre_chargeurs = m_joueur->getArme(m_armeActuelle)->getChargeurs();
                core::stringw str_chargeurs = L"/ ";
                str_chargeurs += m_nombre_chargeurs;
                hud_chargeur->setText(str_chargeurs.c_str());

                m_nombre_balles = m_joueur->getArme(m_armeActuelle)->getMunitions();
                core::stringw str_balles = L"";
                str_balles += m_nombre_balles;
                hud_balles->setText(str_balles.c_str());

                stringw str_nomarme = armeJoueur->getNomArme();
                hud_nomarme->setText(str_nomarme.c_str());

                if(m_chronoIASwitcher==true)
                {
                    core::stringw str_chrono = L"Creatures: ";
                    str_chrono += m_zombieRestants;
                    hud_chrono->setText(str_chrono.c_str());
                }
                else
                {
                    core::stringw str_chrono = L"Repos: ";
                    str_chrono += (30000-m_deltaChronoIA)/1000;
                    hud_chrono->setText(str_chrono.c_str());
                }

                if(m_activerZoneDebug)
                {
                    hud_debug1->setVisible(true);
                    hud_debug2->setVisible(true);
                    hud_debug3->setVisible(true);

                    stringw str_debug1 = L"1: ";
                    str_debug1 += camera->getAbsolutePosition().X;
                    hud_debug1->setText(str_debug1.c_str());

                    stringw str_debug2 = L"2: ";
                    str_debug2 += camera->getAbsolutePosition().Y;
                    hud_debug2->setText(str_debug2.c_str());

                    stringw str_debug3 = L"3: ";
                    str_debug3 += camera->getAbsolutePosition().Z;
                    hud_debug3->setText(str_debug3.c_str());

                }
                else
                {
                    hud_debug1->setVisible(false);
                    hud_debug2->setVisible(false);
                    hud_debug3->setVisible(false);
                }

                if(m_drawFPS)
                {
                    hud_fps->setVisible(true);
                    m_FPS = driver->getFPS();
                    if (m_LASTFPS != m_FPS)
                    {
                        if(m_FPS > m_MAXFPS)
                        {
                            m_MAXFPS = m_FPS;    //! SI LES FPS DEPASSENT LE MAX, METTRE A JOUR LE MAX
                        }

                        if(m_FPS < m_MINFPS)                //! SI LE TEMPS NECESSAIRE A LA STABILISATION DES FPS EST DEPASSÉ, ACTIVER LA MISE A JOUR DU MIN
                        {
                            if(!m_minFPSActive)
                            {
                                if(device->getTimer()->getTime() > 15000)
                                    m_minFPSActive = true;
                            }
                            else
                            {
                                m_MINFPS = m_FPS;
                            }
                        }

                        stringw str_fps = L"";

                        str_fps += " FPS: ";
                        str_fps += m_FPS;
                        str_fps += " MIN: ";
                        str_fps += m_MINFPS;
                        str_fps += " MAX: ";
                        str_fps += m_MAXFPS;
                        hud_fps->setText(str_fps.c_str());
                        m_LASTFPS = m_FPS;
                    }
                }
                else
                {
                    hud_fps->setVisible(false);
                }

            if (m_joueur->getSante() == 0)
            {
                dimension2d<u32> m_dimenGameover = hud_gameover->getSize ();
                    position2d<irr::s32> gameover;
                        gameover.X = m_dimenGameover.Width;
                        gameover.Y = m_dimenGameover.Height;
                driver->draw2DImage(hud_gameover, irr::core::position2d<irr::s32>((largeurdevice-gameover.X)/2,(hauteurdevice-gameover.Y)/2),
                                            irr::core::rect<irr::s32>(0,0,gameover.X,gameover.Y), 0,
                                            irr::video::SColor(255, 255, 255, 255), true);
                device->getTimer()->setSpeed(0.0f);
            }

            }

            driver->endScene();

            //!////////////////////////////////////
            //! Mise à jour de l'état des touches//
            //!////////////////////////////////////
            for (int i=0; i<KEY_KEY_CODES_COUNT; i++)
            {
                if (keys[i] == ksDown)
                {
                    keys[i] = ksHeldDown;
                }
            }

        }
        else
        {
            device->yield();
        }

    }
    if(world)
        delete world;

    if(device)
        device->drop();

    m_soundEngine->removeAllSoundSources();
    m_soundEngine->drop();

    delete m_joueur;
    delete m_map;
    delete m_scoreManager;

}

//!/////////////////////////////////////
//! Reste du gestionnaire d'événements//
//!/////////////////////////////////////

bool CFps::OnEvent(SEvent const& event)
{

    //il s'agit d'un event concernant un appui/relachement de touche
    if(event.EventType == EET_MOUSE_INPUT_EVENT)
    {
        switch(event.MouseInput.Event)
        {
            //! Le bouton gauche a été enfoncé
        case EMIE_LMOUSE_PRESSED_DOWN:
            if(m_joueur->getArme(m_armeActuelle)->getMunitions()>0
               && !m_joueur->isReloading())
            {
                m_joueur->setShooting(true);
                return true;
            }
            else if(m_joueur->getArme(m_armeActuelle)->getMunitions() == 0)
            {
                m_soundEngine->play2D(m_outOfAmmoSound);
            }
            break;

        case EMIE_LMOUSE_LEFT_UP:
            //m_joueur->setShootAbility(true);
            //m_joueur->setReloadAbility(true);
            m_joueur->setShooting(false);
            return true;
            break;

        case EMIE_RMOUSE_PRESSED_DOWN:
            m_joueur->setTempsDebViser(device->getTimer()->getTime());
            m_joueur->setAiming(true);
            return true;
            break;

        case EMIE_RMOUSE_LEFT_UP:
            m_joueur->setAiming(false);
            return true;
            break;

        }
    }

    if(event.EventType == EET_KEY_INPUT_EVENT)
    {


        if (event.KeyInput.PressedDown)
        {
            if (keys[event.KeyInput.Key] == ksDown)
            {
                keys[event.KeyInput.Key] = ksHeldDown;
                return true;
            }
            else if (keys[event.KeyInput.Key] == ksUp)
            {
                keys[event.KeyInput.Key] = ksDown;
                return true;
            }
        }
        else
        {
            keys[event.KeyInput.Key] = ksUp;
        }



        switch(event.KeyInput.Key)
        {



        case KEY_KEY_R:
            if (m_joueur->getDeltaTempsTir() > m_joueur->getArme(m_armeActuelle)->getCadenceTirArme()
                    && !m_joueur->isAiming()
                    && !m_joueur->isShooting()
                    && m_joueur->getArme(m_armeActuelle)->getChargeurs() > 0
                    && m_nombre_balles < m_joueur->getArme(m_armeActuelle)->getCapaciteArmeMunitions()
                    && m_joueur->getDeltaTempsRecharge()> m_joueur->getArme(m_armeActuelle)->getCadenceRechargeArme())
            {
                m_joueur->setReloading(true);
                m_joueur->setTempsRecharge(device->getTimer()->getTime());
                m_soundEngine->play2D(m_reloadSound);
                m_joueur->setReloadAbility(false);
                m_joueur->getArme(m_armeActuelle)->majChargeur(-1);
                m_joueur->getArme(m_armeActuelle)->majMunition(50);

                m_delaiPourEjecterChargeur = device->getTimer()->getTime();
                m_activerEjectionChargeur = true;

                return true;
            }

            break;

        case KEY_KEY_E:
            m_pickupRay = true;
            return true;
            break;

        case KEY_KEY_Q:
            m_joueur->getArme(m_armeActuelle)->majChargeur(3);
            return true;
            break;

        case KEY_KEY_F:
            if(m_lampeTorche==true && m_joueur->getDeltaTempsTorche() > 500)
            {
                m_joueur->setTempsTorche(device->getTimer()->getTime());
                m_soundEngine->play2D(m_torcheSound);
                m_lampeTorche = false;
                return true;
            }
            else if (m_joueur->getDeltaTempsTorche() > 500)
            {
                m_joueur->setTempsTorche(device->getTimer()->getTime());
                m_soundEngine->play2D(m_torcheSound);
                m_lampeTorche = true;
                return true;
            }
            break;

        case KEY_F1:
            m_drawFPS = (m_drawFPS) ? false : true;
            break;

        case KEY_F2:
            m_activerZoneDebug = (m_activerZoneDebug) ? false : true;
            break;

        case KEY_KEY_P:
            m_soundEngine->setSoundVolume((m_soundEngine->getSoundVolume()==0.0f)?1.0f:0.0f);
            device->getTimer()->setSpeed((device->getTimer()->getSpeed()==0.0f)?1.0f:0.0f);
            break;


        case KEY_KEY_1:
            if(m_joueur->getDeltaTempsSwitchArme() > 1000)
            {
                m_joueur->setTempsSwitchArme(device->getTimer()->getTime());

                m_joueur->getArme(m_armeActuelle)->setArmeActive(false);
                //m_joueur->getArme(m_armeActuelle)->getGunMesh()->removeChild(m_lightnodeTorche);
                m_tempSwitchArme = 1;
                m_joueur->getArme(1)->setArmeActive(true);
                m_joueur->getArme(1)->getGunMesh()->addChild(m_lightnodeTorche);
                m_joueur->getArme(1)->getGunMesh()->addChild(m_muzzlelumiere);
                m_joueur->getArme(1)->getGunMesh()->addChild(m_repereDouilles);
                m_joueur->getArme(1)->getGunMesh()->addChild(m_repereDouilles2);
                m_lightnodeTorche->setPosition(vector3df(0.0f,0.0f,3.0f));
                m_repereDouilles->setPosition(vector3df(0.0f,3.0f,-1.0f));
                m_repereDouilles2->setPosition(vector3df(3.0f,7.0f,-1.0f));
                m_muzzlelumiere->setPosition(vector3df(0,3.5,4));
                m_angleArme = 1.6;
                return true;
            }
            break;

        case KEY_KEY_2:
            if (m_joueur->getDeltaTempsSwitchArme() > 1000
                    && m_wipBlocker == false)
            {
                m_joueur->setTempsSwitchArme(device->getTimer()->getTime());

                m_joueur->getArme(m_armeActuelle)->setArmeActive(false);
                //m_joueur->getArme(m_armeActuelle)->getGunMesh()->removeChild(m_lightnodeTorche);
                m_tempSwitchArme = 2;
                m_joueur->getArme(2)->setArmeActive(true);
                m_joueur->getArme(2)->getGunMesh()->addChild(m_lightnodeTorche);
                m_joueur->getArme(2)->getGunMesh()->addChild(m_muzzlelumiere);
                m_joueur->getArme(2)->getGunMesh()->addChild(m_repereDouilles);
                m_joueur->getArme(2)->getGunMesh()->addChild(m_repereDouilles2);
                m_lightnodeTorche->setPosition(vector3df(0.0f,0.0f,3.0f));
                m_repereDouilles->setPosition(vector3df(0.0f,3.0f,-1.0f));
                m_repereDouilles2->setPosition(vector3df(3.0f,7.0f,-1.0f));
                m_muzzlelumiere->setPosition(vector3df(0,3.5,4));
                m_angleArme = 1.6;
                return true;
            }
            break;
            /*
                        case KEY_KEY_3:
                            if (m_joueur->getDeltaTempsSwitchArme() > 1000){
                            m_joueur->setTempsSwitchArme(device->getTimer()->getTime());
                            m_joueur->getArme(m_armeActuelle)->setArmeActive(false);
                            m_tempSwitchArme = 3;
                            m_joueur->getArme(3)->setArmeActive(true);
                                            m_angleArme = 1.6;
                            return true;
                            }
                        break;

                        case KEY_KEY_4:
                            if (m_joueur->getDeltaTempsSwitchArme() > 1000){
                            m_joueur->setTempsSwitchArme(device->getTimer()->getTime());
                            m_joueur->getArme(m_armeActuelle)->setArmeActive(false);
                            m_tempSwitchArme = 4;
                            m_joueur->getArme(4)->setArmeActive(true, effect, m_filterType);
                                            m_angleArme = 1.6;
                            return true;
                            }
                        break;

                        case KEY_KEY_5:
                            if (m_joueur->getDeltaTempsSwitchArme() > 1000){
                            m_joueur->setTempsSwitchArme(device->getTimer()->getTime());
                            m_joueur->getArme(m_armeActuelle)->setArmeActive(false);
                            m_tempSwitchArme = 5;
                            m_joueur->getArme(5)->setArmeActive(true, effect, m_filterType);
                                            m_angleArme = 1.6;
                            return true;
                            }
                        break;
            */
        }

    }

    //Si on arrive la, c'est qu'on a pas traite l'event
    return false;
}


CFps::~CFps()
{

}
