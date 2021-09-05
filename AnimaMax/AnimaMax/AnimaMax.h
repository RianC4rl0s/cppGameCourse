/**********************************************************************************
// AnimaMax (Arquivo de Cabeçalho)
//
// Criação:     10 Abr 2012
// Atualização: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de uso da classe Animation
//
**********************************************************************************/

#ifndef _ANIMAMAX_H_
#define _ANIMAMAX_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Game.h"
#include "Scene.h"
#include "Sprite.h"

#include <random>

// ------------------------------------------------------------------------------

class AnimaMax : public Game
{
private:
    Sprite * text = nullptr;        // instruções
    Sprite * backg = nullptr;       // sprite de fundo
   



public:
    static Scene * scene;           // gerenciador de cena

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo
};

// ---------------------------------------------------------------------------------

#endif