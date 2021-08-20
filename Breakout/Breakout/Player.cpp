/**********************************************************************************
// Player (Arquivo de Cabeçalho)
// 
// Criação:     22 Dez 2012
// Atualização: 18 Ago 2021
// Compilador:  Visual C++ 2019
//
// Descrição:   Player do jogo Breakout
//
**********************************************************************************/

#include "Player.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
	sprite = new Sprite("Resources/Player.png");
	speed = 100;
	
	MoveTo(window->CenterX() - (sprite->Width() / 2), window->Height() - 50.0f);
}

Player::~Player()
{
	delete sprite;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	if (window->KeyDown(VK_LEFT)) {
		Translate(-speed * gameTime, 0);
	}

	if (window->KeyDown(VK_RIGHT)) {
		Translate(speed * gameTime, 0);
	}

	if (x < 0) {
		MoveTo(0,y);
	}
	if (x + sprite->Width() > window->Width()) {
		MoveTo(window->Width()- sprite->Width(), y);
	}
}

void Player::Draw() 
{
	sprite->Draw(x, y, z);
}

