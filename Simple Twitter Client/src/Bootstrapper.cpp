/*
 *  NO2 Web and Mobile Applications, S.L CONFIDENTIAL
 *
 *  Strawberry SDK ( OpenGL + HTML + CSS  cross-platform framework )
 *  Copyright 2010-2012 NO2 Web and Mobile Applications, S.L. All rights reserved.
 *
 * 
 *  NOTICE:  All information contained herein is, and remains
 *  the property of NO2 Web and Mobile Applications, S.L and its suppliers,
 *  if any.  The intellectual and technical concepts contained
 *  herein are proprietary to NO2 Web and Mobile Applications, S.L
 *  and its suppliers, and are protected by trade secret or copyright law.
 *  Dissemination of this information or reproduction of this material
 *  is strictly forbidden unless prior written permission is obtained
 *  from NO2 Web and Mobile Applications, S.L.
 */ 

#include "Bootstrapper.h"
#include "no2gl.h"
#include "TwitterScene.h"

bool NO2GLBootstrapper(NO2Director *director) {
	LOG("Bootstrapping...");

//    Change app orientation
//    director->setOrientation(ORIENTATION_0);
    
	return true;
}

NO2Scene *NO2GLFirstScene() {
    return AUTORELEASE(new NO2NavigationManager(AUTORELEASE(new TwitterScene())));
}
