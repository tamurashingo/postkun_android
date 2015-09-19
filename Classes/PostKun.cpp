/*-
 * PostKun - Cocos2d-x version
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2002, 2013, 2015 tamura shingo
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/*
 * PostKun.cpp
 *
 *  Created on: 2015/09/14
 *      Author: tamura shingo
 */


#include "PostKun.h"
#include "PostKunConstants.h"

void PostKun::init()
{
    this->isJump = false;
    this->isOver = false;
    this->h = 0;
    this->x = PostKunConstants::CENTER_X;
    this->y = PostKunConstants::CENTER_Y;
}

void PostKun::jump()
{
    if (this->isJump == false) {
        this->isJump = true;
        this->h = 6;
    }
}

void PostKun::land()
{
    this->isJump = false;
}

void PostKun::over()
{
    this->isOver = true;
    this->x = PostKunConstants::CENTER_X - 10;
}

void PostKun::enterFrame()
{
    if (this->h > 0) {
        this->h -= 2;
    }
    if (this->h <= 0) {
        this->land();
    }
    this->y = PostKunConstants::CENTER_Y + this->h;
}

