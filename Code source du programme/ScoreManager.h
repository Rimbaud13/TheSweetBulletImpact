//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#ifndef SCORE
#define SCORE
#include <string>
#include <fstream>
#include <irrlicht.h>

class CScore
{

public :

    CScore();
    ~CScore();

    void updateHighScore(int);
    void syncHighScore();
    irr::core::stringw getHighScore() const;

private :

    std::ifstream m_hsStreamRead;
    std::ofstream m_hsStreamWrite;
    int m_currentHigh;

};


#endif
