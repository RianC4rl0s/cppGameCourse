
#ifndef _ANIMAMAX_EXPLOSION_H_
#define _ANIMAMAX_EXPLOSION_H_

#include "Types.h"                      
#include "Object.h"                     
#include "Animation.h"                  
#include "TileSet.h"

class Man : public Object
{
private:
	TileSet* man = nullptr;
	Animation* anim = nullptr;


public:
	Man();
	~Man();

	void Update();
	void Draw();
};



#endif
