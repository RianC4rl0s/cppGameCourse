/**********************************************************************************
// AnimaMax (Código Fonte)
// 
// Criação:     10 Abr 2012
// Atualização: 27 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Exemplo de uso da classe Animation
//
**********************************************************************************/

#include "Engine.h"
#include "AnimaMax.h"
#include "Human.h"
#include "Resources.h"

// -----------------------------------------------------------------------------

Scene * AnimaMax::scene = nullptr;

// -----------------------------------------------------------------------------

void AnimaMax::Init()
{
    scene   = new Scene();
    
    backg   = new Sprite("Resources/bkg.png");
    
    Human* hm = new Human();
    hm->MoveTo(window->CenterX() - 120, window->CenterY() - 130);
    scene->Add(hm, STATIC);
    


}

// ------------------------------------------------------------------------------

void AnimaMax::Update()
{
    
    if (window->KeyDown(VK_ESCAPE))
        window->Close();

    

    scene->Update();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Draw()
{
    backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);
 
    scene->Draw();
} 

// ------------------------------------------------------------------------------

void AnimaMax::Finalize()
{
  
    delete backg;
 
    delete scene;
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, 
                     _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
    Engine * engine = new Engine();

    // configura janela
    engine->window->Mode(WINDOWED);
    engine->window->Size(1280, 720);
    engine->window->Color(0, 0, 0);
    engine->window->Title("AnimaMax");
    engine->window->Icon(IDI_ICON);

    // configura dispositivo gráfico
    //engine->graphics->VSync(true);
    
    // inicia o jogo
    int status = engine->Start(new AnimaMax());

    delete engine;
    return status;
}

// ----------------------------------------------------------------------------

