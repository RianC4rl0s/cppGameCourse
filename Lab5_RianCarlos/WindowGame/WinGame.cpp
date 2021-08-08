/**********************************************************************************
// WinGame
//
// Criação:     19 Mai 2007
// Atualização: 04 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Um jogo para Windows é uma classe derivada de Game.
//              Crie uma classe derivada e sobrescreva os métodos Init,
//              Update, Draw e Finalize.
//
**********************************************************************************/

#include "Resources.h"
#include "Engine.h"
#include "Game.h"
#include <sstream>
using std::stringstream;

// ------------------------------------------------------------------------------

class WinGame : public Game
{
private:
	HDC hdc = 0;
	int xi = 0,
		yi = 0,
		xf = 0,
		yf = 0;

	int speedXI = 0,
		speedXF = 0,
		speedYI = 0,
		speedYF = 0;
public:
	void Init();
	void Update();
	void Draw();
	void Finalize();
};

// ------------------------------------------------------------------------------

void WinGame::Init()
{
	hdc = GetDC(window->Id());

	xi = 40;
	yi = 40;
	xf = 40;
	yf = 40;

	speedXI = 5;
	speedYI = 6;
	speedXF = 7l;
	speedYF = 8;
}

// ------------------------------------------------------------------------------

void WinGame::Update()
{
	//Fechar jogos
	if (window->KeyDown(VK_LBUTTON))
		window->Close();

	xi += speedXI;
	yi += speedYI;
	xf += speedXF;
	yf += speedYF;



	if (xi > window->Width() || xi + 30 > window->Width()) {
		speedXI = -speedXI;
	}
	if (yi > window->Height() || yi + 30 > window->Height()) {
		speedYI = -speedYI;
	}
	if (xf > window->Width() || xf + 30 > window->Width()) {
		speedXF = -speedXF;
	}
	if (yf > window->Height() || yf + 30 > window->Height()) {
		speedYF = -speedYF;
	}
	if (xi < 0 || (xi + 30) < 0) {
		speedXI = -speedXI;
	}
	if (yi < 0 || (yi + 30) < 0) {
		speedYI = -speedYI;
	}
	if (xf < 0 || (xf + 30) < 0) {
		speedXF = -speedXF;
	}
	if (yf < 0 || (yi + 30) < 0) {
		speedYF = -speedYF;
	}

	MoveToEx(hdc, xi, yi, NULL);

}

// ------------------------------------------------------------------------------

void WinGame::Draw()
{


	LineTo(hdc, xf, yf);
	LineTo(hdc, xf + 30, yf + 30);
	LineTo(hdc, xi + 30, yi + 30);
	LineTo(hdc, xi, yi);

}

// ------------------------------------------------------------------------------

void WinGame::Finalize()
{
	ReleaseDC(window->Id(), hdc);
}


// ------------------------------------------------------------------------------
//                                  WinMain                                      
// ------------------------------------------------------------------------------

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	// cria motor e configura a janela
	Engine* engine = new Engine();
	engine->window->Mode(WINDOWED);
	engine->window->Size(960, 540);
	engine->window->Color(240, 240, 140);
	engine->window->Title("Window Game");
	engine->window->Icon(IDI_ICON);
	engine->window->Cursor(IDC_CURSOR);

	// cria e inicia o jogo
	engine->Start(new WinGame());
}

// ----------------------------------------------------------------------------

