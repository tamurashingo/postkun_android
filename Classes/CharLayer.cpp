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
 * CharLayer.cpp
 *
 *  Created on: 2015/09/14
 *      Author: tamura shingo
 */


#include "CharLayer.h"
#include "PostKunConstants.h"

void CharLayer::setPostKun(PostKun* p)
{
    this->postkun = p;
}

bool CharLayer::init()
{
    backLayer = DrawNode::create();
    frontLayer = DrawNode::create();
    sprite = Sprite::create("post.png");
    sprite->setAnchorPoint(Vec2(0.5f, 0.5f));

    this->addChild(backLayer, 0);
    this->addChild(sprite, 1);
    this->addChild(frontLayer, 2);

    this->setVisible(false);

    return true;
}


void CharLayer::enterFrame(int count)
{
    backLayer->clear();
    frontLayer->clear();
    if (count < 3) {
        draw(count, backLayer);
    }
    else {
        draw(count, frontLayer);
    }
    postkun->enterFrame();
    sprite->setPositionX(postkun->x);
    sprite->setPositionY(postkun->y);
}

void CharLayer::draw(int count, DrawNode* node)
{
    const struct NAWAPOS *pos = &CharLayer::nawapos[count];
    Vec2 p1 = Vec2(PostKunConstants::NAWA_CENTER_X + pos->x[0], PostKunConstants::NAWA_CENTER_Y - pos->y[0]);
    for (int ix = 1; ix < pos->size; ix++) {
        Vec2 p2 = Vec2(PostKunConstants::NAWA_CENTER_X + pos->x[ix], PostKunConstants::NAWA_CENTER_Y - pos->y[ix]);
        node->drawSegment(p1, p2, 0.5f, Color4F(0, 0, 0, 1));
        p1 = p2;
    }
}

const struct NAWAPOS CharLayer::nawapos[7] = {
    // 0
    {
        7,
        { 19, 25, 38, 46, 42, 41,  4},
        { 46, 54, 58, 58, 54, 53, 46}
    },
    // 1
    {
        9,
        { 19, 31, 42, 42, 32,  1, -3,  3, 14},
        { 46, 50, 42, 28, 20, 18, 29, 42, 46}
    },
    // 2
    {
        7,
        { 19, 30, 35, 22,  2,  7, 14},
        { 46, 41, 15, -5, 10, 44, 48}
    },
    // 3
    {
        7,
        { 19, 29, 31, 12,  0,  3, 14},
        { 46, 46, 22,  6, 28, 42, 46}
    },
    // 4
    {
        7,
        { 19, 27, 11, -7, -7,  7, 14},
        { 46, 42, 23, 20, 28, 44, 46}
    },
    // 5
    {
        7,
        { 19, 16,  5, -5, -5,  7, 14},
        { 46, 54, 58, 55, 51, 47, 46}
    },
    // 6
    {
        6,
        { 19, 23, 22, 18, 11, 14},
        { 41, 50, 55, 56, 52, 53}
    }
};
