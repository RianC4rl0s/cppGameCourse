
#include "Human.h"
#include "AnimaMax.h"

// ---------------------------------------------------------------------------------

Human::Human()
{
    ts = new TileSet("Resources/TileAnimation.png", 240, 260, 5, 20);

    anim = new Animation(ts, 0.060f, true);
}

// ---------------------------------------------------------------------------------

Human::~Human()
{
    delete ts;
    delete anim;
}

// ---------------------------------------------------------------------------------

void Human::Update()
{
    anim->NextFrame();
   
}

// ---------------------------------------------------------------------------------
void Human::Draw() {
    anim->Draw(x,y,z);
}