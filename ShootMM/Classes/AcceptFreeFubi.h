//
//  AcceptFreeFubi.h
//  Shoot
//
//  Created by Kevin on 13-7-29.
//
//

#ifndef __Shoot__AcceptFreeFubi__
#define __Shoot__AcceptFreeFubi__

#include <iostream>
#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class AcceptFreeFubi : public CCLayer{
    
    
public:
    
    static CCScene* scene();
    virtual bool init();
    
    void particalSystem();
    
    CREATE_FUNC(AcceptFreeFubi);
};


#endif /* defined(__Shoot__AcceptFreeFubi__) */
