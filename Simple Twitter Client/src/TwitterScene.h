/*
 *  NO2 Web and Mobile Applications, S.L CONFIDENTIAL
 *
 *  Strawberry SDK ( OpenGL + HTML + CSS  cross-platform framework )
 *  Copyright © 2013 by NO2 Web and Mobile Applications, S.L. All rights reserved.
 *  
 *  File name: TwitterScene.h
 *  Created by Xavi Rigau on 14/03/13
 */ 
#ifndef SimpleTwitterClient_TwitterScene
#define SimpleTwitterClient_TwitterScene

#include "NO2GL.h"

class TwitterScene : public NO2Scene, public NO2HTTPResponseDelegate, public NO2DataSource, public NO2TextFieldDelegate {

    NO2MutableDictionary *m_imageCache;
    
public:
    TwitterScene();
    
    // ******** Begin of Scene methods ********
	virtual void onSceneWillAppear();
    virtual void onSceneDidAppear();
	virtual void onSceneDidDisappear();
    virtual void onCommand(int command, int subcommand, NO2Object *object);
    virtual void onDidEndResize(float width, float height);
    // ****************************************

    // ******** Begin of HttpResponseDelegate methods ********
    virtual void onRequestCompleted(NO2HTTPRequest *request,  NO2HTTPResponse *response);
    virtual void onRequestFailed(NO2HTTPRequest *request, int errorCode);
    // *******************************************************

    // ******** Begin of DataSource methods ********
    virtual int numberOfSections(NO2Drawable *container);
    virtual int numberOfItemsInSection(NO2Drawable *container, int section);
    virtual NO2String *templateForIndex(NO2Drawable *container, const NO2IndexPath &indexPath);
    virtual void fillDataForIndex(NO2Drawable *container, NO2Drawable *tpl, NO2String *tplName, const NO2IndexPath &indexPath);
    virtual void didSelectedIndex(NO2Drawable *container, const NO2IndexPath &indexPath);
    // *********************************************

    // ******** Begin of TextField Delegate methods ********
    virtual void textFieldDidBeginEditing(NO2TextField *textField);
    virtual void textFieldDidEndEditing(NO2TextField *textField);
    virtual void textFieldDidChanged(NO2TextField *textField);
    virtual void textFieldDidReturn(NO2TextField *textField);
    // *****************************************************

    
    void doSearch(NO2String *searchTerm);
    
protected:
	~TwitterScene();
    
    NO2_COMMON_METHODS(TwitterScene);
        
private:
    NO2Array *m_data;

};

#endif