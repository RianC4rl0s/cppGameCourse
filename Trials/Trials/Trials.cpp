/**********************************************************************************
// Trials (C�digo Fonte)
//
// Cria��o:     14 Mai 2012
// Atualiza��o: 22 Set 2021
// Compilador:  Visual C++ 2019
//
// Descri��o:   Exemplo de interface com menus
//
**********************************************************************************/

#include "Engine.h"
#include "Trials.h"
#include "Mouse.h"
#include "Item.h"

// ------------------------------------------------------------------------------

void Trials::Init()
{
	// cria gerenciadores
	scene = new Scene();
	audio = new Audio();

	// carrega sons e m�sica
	audio->Add(EVOLUTION, "Resources/Evolution.wav");
	audio->Play(EVOLUTION, true);

	// cria sprites
	backg = new Sprite("Resources/Trials.jpg");

	// cria objeto mouse
	mouse = new Mouse();

	// cria itens de menu
	menu[0] = new Item(570, 250, SINGLE, "Resources/SinglePlayer.png");
	menu[1] = new Item(570, 305, MULTI, "Resources/MultiPlayer.png");
	menu[2] = new Item(570, 360, TRACKS, "Resources/TrackCentral.png");
	menu[3] = new Item(570, 435, LEADERBOARD, "Resources/Leaderboards.png");
	menu[4] = new Item(570, 490, OPTIONS, "Resources/HelpOptions.png");
	menu[5] = new Item(570, 545, EXIT, "Resources/ExitGame.png");
}

// ------------------------------------------------------------------------------

void Trials::Update()
{
	// fecha a janela ao pressionar ESC
	if (window->KeyDown(VK_ESCAPE))
		window->Close();

	// atualiza objeto mouse
	mouse->Update();

	if (followMode) {
		// move item selecionado com o mouse 
		selected->MoveTo(window->MouseX(), window->MouseY());
		// solta item e sai do modo de posicionamento 
		if (mouse->Clicked())
			followMode = false;
	}
	else {


		// destaca item selecionado
		for (int i = 0; i < MaxItens; ++i)
		{
			if (scene->Collision(mouse, menu[i]))
			{
				menu[i]->Select();
				selected = menu[i];

				if (mouse->Clicked()) {
					if (editMode)
						followMode = true;
					else {
						switch (menu[i]->Type())
						{
						case SINGLE:
						case MULTI:
						case TRACKS:
						case LEADERBOARD:
						case OPTIONS: break;
						case EXIT: window->Close(); break;
						}

					}

				}

				/*
				if (editMode) {
					if (mouse->Clicked())
						followMode = true;

				}
				else {


					// executa a��es do menu
					if (mouse->Clicked())
					{
					}
				}
				*/
			}
			else
			{
				menu[i]->UnSelect();
			}

			menu[i]->Update();
		}
	}
	// habilita/desabilita modo de edi��o 
	if (window->KeyPress('E'))
		editMode = !editMode;


	// habilita/desabilita bounding box
	if (window->KeyPress('B'))
		viewBBox = !viewBBox;
}

// ------------------------------------------------------------------------------

void Trials::Draw()
{
	// desenha pano de fundo
	backg->Draw(window->CenterX(), window->CenterY(), Layer::BACK);

	// desenha itens do menu
	for (int i = 0; i < MaxItens; ++i)
		menu[i]->Draw();

	// desenha bounding box dos menus
	if (viewBBox)
		scene->DrawBBox();
}

// ------------------------------------------------------------------------------

void Trials::Finalize()
{
	// remove gerenciadores
	delete scene;
	delete audio;

	// remove sprites
	delete backg;

	// remove objetos
	delete mouse;
	for (int i = 0; i < MaxItens; ++i)
		delete menu[i];
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	Engine* engine = new Engine();

	// configura motor
	engine->window->Mode(WINDOWED);
	engine->window->Size(800, 600);
	engine->window->Color(0, 0, 0);
	engine->window->Title("Trials");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);
	//engine->graphics->VSync(true);

	// inicia o jogo
	int status = engine->Start(new Trials());

	delete engine;
	return status;
}

// ----------------------------------------------------------------------------

