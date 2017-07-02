#include "Animation.h"
#include "log.h"

Animation::Animation(int n, int d, AnimationType anim, int e) :
numAttr(n), duration(d), initialDelay(e), time(0){

    // Guardamos la memoria para los diferentes vectores
    initial = new int[numAttr];
    final = new int[numAttr];
    change = new int[numAttr];
    current = new float[numAttr];

    // Asigna valores perdeterminados a los vectores
    for (int i = 0; i < n; ++i)
    {
       initial[i] = final[i] = change[i] = current[i] = 0;
    }

    // Define el tipo de animación
   setAnimationType(anim);

   lDEBUG << Log::CON("Animación") << " . " << n << " parámetros.";
}


Animation::~Animation(){
    delete initial;
    delete final;
    delete change;
    delete current;

    lDEBUG << Log::DES("Animación");
}

void Animation::setAnimationType(AnimationType a){
    anim = a;

    // Quad
    if(anim == tEaseInQuad){
       puntFun = &Animation::easeInQuad;
   }
   else if(anim == tEaseOutQuad){
       puntFun = &Animation::easeOutQuad;
   }
   else if(anim == tEaseInOutQuad){
       puntFun = &Animation::easeInOutQuad;
   }

    // Cubic
   else if(anim == tEaseInCubic){
       puntFun = &Animation::easeInCubic;
   }
   else if(anim == tEaseOutCubic){
       puntFun = &Animation::easeOutCubic;
   }
   else if(anim == tEaseInOutCubic){
       puntFun = &Animation::easeInOutCubic;
   }

    // Quart
   else if(anim == tEaseInQuart){
       puntFun = &Animation::easeInQuart;
   }
   else if(anim == tEaseOutQuart){
       puntFun = &Animation::easeOutQuart;
   }
   else if(anim == tEaseInOutQuart){
       puntFun = &Animation::easeInOutQuart;
   }

    // Back
   else if(anim == tEaseOutBack){
       puntFun = &Animation::easeOutBack;
   }

    // Linear y default
   else{
       puntFun = &Animation::easeLinear;
   }

}

void Animation::update(bool a){

    if(time - initialDelay > duration){
       for (int i = 0; i < numAttr; ++i)
       {
           current[i] = final[i];
       }
       return;
   }

   else if(time >= initialDelay)
   {
       for (int i = 0; i < numAttr; ++i){
           current[i] = (*puntFun)(time - initialDelay, initial[i], change[i], duration);
       }

   }

   if(a) ++time;
}



float Animation::get(int i){
    if(i < numAttr){
       return current[i];
   }else{
       return 0;
   }
}

void Animation::setInitial(int i, int v){
    if(i < numAttr){
       initial[i] = v;
       change[i] = final[i] - v;
       current[i] = v;
   }
}

void Animation::setFinal(int i, int v){
    if(i < numAttr){
       final[i] = v;
       change[i] = v - initial[i];
   }
}

void Animation::set(int i, int v1, int v2){
    if(i < numAttr){
       initial[i] = v1;
       final[i] = v2;
       change[i] = v2 - v1;
       current[i] = v1;
   }
}

void Animation::reverse(){
    int a;
    for (int i = 0; i < numAttr; ++i)
    {
       a = initial[i];
       initial[i] = final[i];
       final[i] = a;
       change[i] = final[i] - initial[i];
   }

}

void Animation::end() { time = duration + initialDelay; update(false); }
void Animation::init() { time = 0; }
bool Animation::finished(){
    return time > duration + initialDelay;
}
