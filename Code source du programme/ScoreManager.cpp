//!//////////////////////////////////////////////
//!         (The Sweet) Bullet Impact          //
//!               Project File                 //
//! by Roussel Nicolas & Kieliger Leandro 2012 //
//!//////////////////////////////////////////////

#include "ScoreManager.h"
#include <fstream>
#include <string>
#include <iostream>
#include <irrlicht.h>

using namespace std;


CScore::CScore()
{
    ifstream m_hsStreamRead;
    ofstream m_hsStreamWrite;
    m_currentHigh = 0;
}
CScore::~CScore()
{

}

void CScore::syncHighScore()
{
    m_hsStreamRead.open("DATA/scores.dat");
    m_hsStreamRead >> m_currentHigh;
    m_hsStreamRead.close();
}

void CScore::updateHighScore(int newScore)
{

    if(newScore > m_currentHigh)
    {
        m_currentHigh = newScore;
        m_hsStreamWrite.open("DATA/scores.dat", ios::trunc);
        m_hsStreamWrite << m_currentHigh;
        m_hsStreamWrite.close();
    }
}

irr::core::stringw CScore::getHighScore() const
{

    irr::core::stringw str_return = L"High: ";
    str_return += m_currentHigh;
    return str_return;

}
