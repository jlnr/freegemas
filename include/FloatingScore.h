/**
 * @file FloatingScore.h
 *
 * @author José Tomás Tocino García
 * @date 2010
 *
 * Copyright (C) 2010 José Tomás Tocino García <theom3ga@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */


#ifndef _FLOATINGSCORE_H_
#define _FLOATINGSCORE_H_

#include <string>

#include "log.h"
#include <Gosu/Gosu.hpp>

class FloatingScore{
public:
    FloatingScore(Gosu::Window * parentWindow, int score, float x, float y, float z) :
        x_(x), y_(y), z_(z), mCurrentStep(0), mTotalSteps(50),
        mScoreImage(Gosu::create_text(std::to_string(score), "media/fuentelcd.ttf", 60))
    {
    }

    bool ended(){
        return mCurrentStep == mTotalSteps;
    }

    void draw(){
        if(mCurrentStep >= mTotalSteps) return;

        mCurrentStep += 1;

        float p = 1.f - (float)mCurrentStep/mTotalSteps;

        float posX = 241 + x_ * 65;
        float posY = 41 + y_ * 65 - (1 - p) * 20;

        mScoreImage.draw(posX, posY, z_, 1, 1, Gosu::Color(p * 255, 255, 255, 255));

        mScoreImage.draw(posX + 2, posY + 2, z_ - 0.1, 1, 1, Gosu::Color(p * 255, 0, 0, 0));

        mScoreImage.draw(posX - 2, posY - 2, z_ - 0.1, 1, 1, Gosu::Color(p * 255, 0, 0, 0));

    }
private:
    Gosu::Image mScoreImage;

    float x_;
    float y_;
    float z_;

    int mCurrentStep;
    int mTotalSteps;


};

#endif /* _FLOATINGSCORE_H_ */
