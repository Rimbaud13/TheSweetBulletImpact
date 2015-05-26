//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#ifndef ITEMS
#define ITEMS

#include <irrlicht.h>
#include <irrTypes.h>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;


class CItem
{

public :

    CItem(vector3df ,int );
    ~CItem();


protected:

    ITriangleSelector*          m_itemSelector;
    int                         m_dureeDeVie;
    vector3df                   m_pos;


};



class CAmmoBox : public CItem
{

public :

    CAmmoBox(vector3df, int);
    ~CAmmoBox();

    void initItemAmmoBox3D(scene::ISceneManager*,video::IVideoDriver* , map<scene::IAnimatedMeshSceneNode*, CAmmoBox*>&);
    IAnimatedMeshSceneNode* getAmmoBoxNode() const;
    void destroy();


private :

    IAnimatedMeshSceneNode*     m_AmmoBoxNode;
    ITexture*                   m_AmmoBoxTex;

};


#endif
