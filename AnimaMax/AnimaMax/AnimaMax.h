/**********************************************************************************
// AnimaMax (Arquivo de Cabe�alho)
//
// Cria��o:     10 Abr 2012
// Atualiza��o: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Exemplo de uso da classe Animation
//
**********************************************************************************/

#ifndef _ANIMAMAX_H_
#define _ANIMAMAX_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Game.h"
#include "Scene.h"
#include "Sprite.h"

#include <random>

// ------------------------------------------------------------------------------

class AnimaMax : public Game
{
private:
    Sprite * text = nullptr;        // instru��es
    Sprite * backg = nullptr;       // sprite de fundo
   



public:
    static Scene * scene;           // gerenciador de cena

    void Init();                    // inicializa jogo
    void Update();                  // atualiza l�gica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif