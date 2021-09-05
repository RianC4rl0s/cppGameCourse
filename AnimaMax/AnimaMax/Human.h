
#ifndef _ANIMAMAX_EXPLOSION_H_
#define _ANIMAMAX_EXPLOSION_H_

#include "Types.h"                      
#include "Object.h"                     
#include "Animation.h"                  

class Human : public Object
{
private:
    Animation * anim;                  

    TileSet  * ts = nullptr;

public:
    Human();         
    ~Human();                       

    void Update();                      
    void Draw();                       
};



// ---------------------------------------------------------------------------------

#endif