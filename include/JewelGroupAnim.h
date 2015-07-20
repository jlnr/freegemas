#ifndef _JEWELGROUPANIM_H_
#define _JEWELGROUPANIM_H_

#include "Animation.h"

#include <vector>

#include <Gosu/Gosu.hpp>

class JewelGroupAnim
{
public:
    void loadResources (Gosu::Window * w)
    {
        imgGems.push_back(Gosu::Image(L"media/gemWhite.png"));
        imgGems.push_back(Gosu::Image(L"media/gemRed.png"));
        imgGems.push_back(Gosu::Image(L"media/gemPurple.png"));
        imgGems.push_back(Gosu::Image(L"media/gemOrange.png"));
        imgGems.push_back(Gosu::Image(L"media/gemGreen.png"));
        imgGems.push_back(Gosu::Image(L"media/gemYellow.png"));
        imgGems.push_back(Gosu::Image(L"media/gemBlue.png"));

        for (int i = 0; i < 7; ++i)
        {
            posX[i] = 800 / 2 - (65 * 7) / 2 + i * 65;
        }

        animationCurrentStep = 0;
        animationTotalSteps = 30;
        posFinalY = 265;
    }

    void draw(){

        // Step the animation
        if(animationCurrentStep < 7 * 5 + animationTotalSteps) {
            ++animationCurrentStep;
        }

        // Draw the jewels
        for(int i = 0; i < 7; ++i)
        {
            int composedStep = animationCurrentStep - i * 5;
            if(composedStep < 0) continue;

            if(composedStep < animationTotalSteps){
                imgGems[i].draw(posX[i],
                                   Animation::easeOutCubic(
                                       (float) composedStep,
                                       600.f,
                                       (float) posFinalY - 600.f,
                                       (float) animationTotalSteps),
                                   2.f);
            }else{
                imgGems[i].draw(posX[i], posFinalY, 2);
            }
        }
    }

private:
    std::vector<Gosu::Image> imgGems;

    int posX[7], posFinalY;

    int animationCurrentStep;
    int animationTotalSteps;

};


#endif /* _JEWELGROUPANIM_H_ */
