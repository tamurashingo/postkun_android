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
 * PostKunConstants.h
 *
 *  Created on: 2015/09/14
 *      Author: tamura shingo
 */

#ifndef POSTKUNCONSTANTS_H_
#define POSTKUNCONSTANTS_H_

class PostKunConstants
{
public:
    static const int SCREEN_WIDTH = 120;
    static const int SCREEN_HEIGHT = 160;
    static const int POST_WIDTH = 35;
    static const int POST_HEIGHT = 58;

    static const int CENTER_X = (SCREEN_WIDTH) / 2;
    static const int CENTER_Y = (SCREEN_HEIGHT) / 2;

    static const int NAWA_CENTER_X = CENTER_X - (POST_WIDTH / 2);
    static const int NAWA_CENTER_Y = CENTER_Y + (POST_HEIGHT / 2);
};


#endif /* POSTKUNCONSTANTS_H_ */
