
#include "Man.h"
#include "TileSet.h"
#include "Animation.h"


Man::Man()
{
	man = new TileSet("Resources/TileAnimation.png", 240, 260, 5, 20);

	anim = new Animation(man, 0.060f, true);

	MoveTo(window->CenterX() - 120, window->CenterY() - 130);
}

// ---------------------------------------------------------------------------------

Man::~Man()
{
	delete man;
	delete anim;
}

// ---------------------------------------------------------------------------------

void Man::Update()
{
	anim->NextFrame();
	Draw();
}

// ---------------------------------------------------------------------------------
void Man::Draw() {
	anim->Draw(x, y, z);
}