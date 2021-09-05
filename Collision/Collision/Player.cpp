/**********************************************************************************
// Player (Arquivo de Cabeçalho)
//
// Criação:     22 Dez 2012
// Atualização: 20 Ago 2021
// Compilador:  Visual C++ 14
//
// Descrição:   Player do jogo Breakout
//
**********************************************************************************/

#include "Breakout.h"
#include "Player.h"
#include "Ball.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
	// tamanho do player é 100x20
	bbox = new Rect(0, 0, 99, 19);

	// bounding box alternativa: experimente usar 
	// uma combinação de retângulos e círculos

	//Mixed * mixed = new Mixed();
	//
	//Circle * cLeft = new Circle(10.0f);
	//cLeft->MoveTo(0.0f, 0.0f);

	//Circle * cRight = new Circle(10.0f);
	//cRight->MoveTo(80.0f, 0.0f);

	//Rect * rect = new Rect(0.0f, 0.0f, 80.0f, 20.0f);
	//rect->MoveTo(10, 0);
	//
	//mixed->Insert(cLeft);
	//mixed->Insert(cRight);
	//mixed->Insert(rect);
	//
	//bbox = mixed;

	// sprite do jogador
	sprite = new Sprite("Resources/Player.png");

	// centraliza o jogador
	MoveTo(window->CenterX() - sprite->Width() / 2.0f,
		window->Height() - 30.0f,
		Layer::FRONT);

	// velocidade do jogador
	vel = 500;

	// estado inicial do jogo
	state = STOPED;

	// tipo do objeto
	type = PLAYER;

}

// ---------------------------------------------------------------------------------

Player::~Player()
{
	delete sprite;
	delete bbox;
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object* obj)
{
	// bola colidiu com o player
	if (obj->Type() == BALL)
	{

		Ball* ball = (Ball*)obj;

		Circle* c = (Circle*)ball->BBox();

		Rect* p = ((Rect*)bbox);
		//verifica se esta em cima ou em baixo
		if ((c->CenterX() > p->Left() && c->CenterX() < p->Right()) && (c->CenterY() > p->Bottom() || c->CenterY() < p->Top())) {
						
			if (c->CenterY() > p->Bottom()) {
				ball->MoveTo(ball->X(), y + sprite->Height() + c->radius);
			}
			else if (c->CenterY() < p->Top()) {
				ball->MoveTo(ball->X(),y - 2*c->radius);
			}
			
			ball->velY = -ball->velY;
		}
		else if ((c->CenterY() > p->Top() && c->CenterY() < p->Bottom()) && (c->CenterX() > p->Right() || c->CenterX() < p->Left())) {
			
			if (c->CenterX() > p->Right()) {
				ball->MoveTo(x + c->radius + sprite->Width(), ball->Y());
			}else if(c->CenterX() < p->Left()) {
				ball->MoveTo(x - 2*c->radius, ball->Y());
			}
			
			ball->velX = -ball->velX;
		}
		else {
			ball->velY = -ball->velY;
			ball->velX = -ball->velX;
		}



	}
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
	// inicia o jogo com barra de espaço
	if (state == STOPED && window->KeyDown(VK_SPACE))
		state = PLAYING;

	// desloca jogador horizontalmente
	if (window->KeyDown(VK_RIGHT))
		Translate(vel * gameTime, 0);
	if (window->KeyDown(VK_LEFT))
		Translate(-vel * gameTime, 0);

	// mantém jogador dentro da janela (tam. da barra: 100x20)
	if (x < 0)
		MoveTo(0.0f, y);
	if (x + sprite->Width() > window->Width())
		MoveTo(float(window->Width() - sprite->Width()), y);
}

// ---------------------------------------------------------------------------------
