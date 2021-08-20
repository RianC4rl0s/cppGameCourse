/**********************************************************************************
// Ball (Arquivo de Cabeçalho)
//
// Criação:     22 Dez 2012
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Bola do jogo Breakout
//
**********************************************************************************/

#include "Ball.h"

// ---------------------------------------------------------------------------------




Ball::Ball()
{
	sprite = new Sprite("Resources/Ball.png");
	speedX = 0;
	speedY = 0;
	MoveTo(window->CenterX() - sprite->Width() / 2, window->Height() - 65);
}

Ball::~Ball()
{
	delete sprite;
}

// ---------------------------------------------------------------------------------
void Ball::Update()
{
	Translate(speedX * gameTime, speedY * gameTime);
	 


	if (x < 0) {
		speedX = -speedX;
	}
	if (y < 0) {
		speedY = -speedY;
	}
	if (x + sprite->Width() > window->Width()) {
		speedX = -speedX;
	}
	if (y + sprite->Width() > window->Height()) {
		speedY = -speedY;
	}
}

void Ball::Draw()
{
	sprite->Draw(x, y, z);
}
