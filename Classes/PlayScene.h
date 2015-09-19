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
 * PlayScene.h
 *
 *  Created on: 2015/09/14
 *      Author: tamura shingo
 */

#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_

#include "cocos2d.h"
#include "PostKun.h"
#include "CharLayer.h"

class PlayScene : public cocos2d::Layer
{
public:
    PlayScene();
    virtual ~PlayScene();

    static cocos2d::Scene* createScene();

    virtual bool init();

    virtual void update(float delta);

    CREATE_FUNC(PlayScene);

    void readyThree(float frame);
    void readyTwo(float frame);
    void readyOne(float frame);
    void readyStart(float frame);
    void start(float frame);

    virtual bool onTouchBegan(Touch* touch, Event* event);

private:
    PostKun* postkun;
    CharLayer* characterLayer;
    Label* scoreLabel;
    EventListenerTouchOneByOne* listener;
    int score;
    int counter;
    bool jumped;
}
;

#endif /* PLAYSCENE_H_ */
