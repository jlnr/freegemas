#include "BaseButton.h"

#include <Gosu/Gosu.hpp>

BaseButton::BaseButton() { }


void BaseButton::set (Gosu::Window * parentWindow, std::string caption, std::string iconPath)
{
    mParentWindow = parentWindow;

    // Load the background image
    mImgBackground.reset(new Gosu::Image("media/buttonBackground.png"));

    // Set the flag
    mHasIcon = !iconPath.empty();

    // Load the icon image
    if (mHasIcon)
    {
        mImgIcon.reset(new Gosu::Image("media/" + iconPath));
    }

    setText(caption);
}

void BaseButton::setText(std::string caption)
{
    // Generate the button caption texture
    Gosu::Bitmap bitmap = Gosu::create_text(caption, "media/fuenteNormal.ttf", 27);
    mImgCaption.reset(new Gosu::Image(bitmap));

    // Calculate the position of the text
    if (mHasIcon)
    {
        mTextHorizontalPosition = 40 + (mImgBackground->width() - 40) / 2 - mImgCaption->width() / 2;
    }
    else
    {
        mTextHorizontalPosition = mImgBackground->width() / 2 - mImgCaption->width() / 2;
    }
}


void BaseButton::draw(int x, int y, double z)
{
    mLastX = x;
    mLastY = y;

    if (mHasIcon)
    {
        mImgIcon->draw(x + 7, y, z + 1);
    }

    mImgCaption->draw(x + mTextHorizontalPosition, y + 5, z + 2);
    mImgCaption->draw(x + mTextHorizontalPosition + 1, y + 7, z + 1, 1, 1, Gosu::Color(128, 0, 0, 0));

    mImgBackground->draw(x, y, z);
}

bool BaseButton::clicked(unsigned int mX, unsigned int mY)
{
    if(mX > mLastX && mX < mLastX + mImgBackground->width() &&
       mY > mLastY && mY < mLastY + mImgBackground->height())
       {
        return true;
    }else
    {
        return false;
    }
}
