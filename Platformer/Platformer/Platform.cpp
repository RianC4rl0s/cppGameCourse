/**********************************************************************************
// Platform (Código Fonte)
// 
// Criação:     21 Abr 2012
// Atualização: 02 Set 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"

// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, uint platType)
{
    platform = new Sprite("Resources/LongGray.png");
    BBox(
        new Rect(
            -1.0f * platform->Width() / 2,
            -1.0f * platform->Height() / 2,
            +1.0f * platform->Width() / 2,
            +1.0f * platform->Height() / 2
        )
    );
    
    MoveTo(posX, posY);
    
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    Translate(-200.0f * gameTime, 0);
}

// -------------------------------------------------------------------------------
