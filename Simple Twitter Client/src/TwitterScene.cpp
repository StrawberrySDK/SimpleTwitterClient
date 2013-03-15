/*
 *  NO2 Web and Mobile Applications, S.L CONFIDENTIAL
 *
 *  Strawberry SDK ( OpenGL + HTML + CSS  cross-platform framework )
 *  Copyright © 2013 by NO2 Web and Mobile Applications, S.L. All rights reserved.
 *  
 *  File name: TwitterScene.cpp
 *  Created by Xavi Rigau on 14/03/13
 */

#include "TwitterScene.h"

TwitterScene::TwitterScene():NO2Scene() {
    if (g_sharedDirector->isPhoneDevice()) {
        loadHTML("phone.html");
    } else {
        loadHTML("tablet_desktop.html");
    }
    
    getElementById("skyline")->addPositionY(100);
    
    ((NO2TextField *) getElementById("search_text"))->setDelegate(this);
    
	NO2GridView *gridView = (NO2GridView *) getElementById("tweets_grid");
	gridView->setDataSource(this);
    
    m_data = NULL;
    m_imageCache = new NO2MutableDictionary();
}

TwitterScene::~TwitterScene() {
    RELEASE(m_imageCache);
	RELEASE(m_data);
}

// ******** Begin of Scene methods ********
void TwitterScene::onSceneWillAppear() {
	NO2Scene::onSceneWillAppear();
    doSearch(_NO2STRING("@StrawberrySDK"));
}

void TwitterScene::onSceneDidAppear() {
    NO2Scene::onSceneDidAppear();
    runAction(_NO2STRING("show_skyline"));
}

void TwitterScene::onSceneDidDisappear() {
	NO2Scene::onSceneWillAppear();
}

void TwitterScene::onCommand(int command, int subcommand, NO2Object *object) {
	switch (command) {
        case 1: { // Search button was pressed
            doSearch(((NO2TextField *) getElementById("search_text"))->getText());
            break;
        }
		case COMMAND_APPLICATION_IN_BACKGROUND: {
			break;
		}
		case COMMAND_APPLICATION_IN_FOREGROUND: {
			break;
		}
		default: {
			break;
		}
	}
}

void TwitterScene::onDidEndResize(float width, float height) {
    NO2Scene::onDidEndResize(width, height);
    NO2String *search = ((NO2TextField *) getElementById("search_text"))->getText();
    if (search) {
        search = RETAIN(search);
    }
    reloadHTML();
    
    ((NO2TextField *) getElementById("search_text"))->setText(search);
    RELEASE(search);
    ((NO2TextField *) getElementById("search_text"))->setDelegate(this);
    ((NO2GridView *) getElementById("tweets_grid"))->setDataSource(this);
}
// ****************************************

// ******** Begin of HttpResponseDelegate methods ********
void TwitterScene::onRequestCompleted(NO2HTTPRequest *request,  NO2HTTPResponse *response) {
	if (response->isOk()) {
		// Response is OK, parse response.
        NO2String *json = NO2String::stringWithData(response->getBody());
        NO2JSONParser *parser = new NO2JSONParser(json);
        NO2Object *parsed = parser->parse();
        
        NO2Dictionary *dict = dynamic_cast<NO2Dictionary *>(parsed);
        if (dict) {
            NO2Array *list = (NO2Array *) dict->getObjectByExpression("results");
            SETTER(m_data, list);
        } else {
            NO2Array *list = dynamic_cast<NO2Array *>(parsed);
            if (list) {
                SETTER(m_data, list);
            }
        }
        
	} else {
		// There was an error, do something.
        LOG("HTTP Error: %d", response->getStatusCode());
	}
    
    ((NO2GridView *) getElementById("tweets_grid"))->reloadData();
    
    
    runAction(_NO2STRING("show_gridview"));
}

void TwitterScene::onRequestFailed(NO2HTTPRequest *request, int errorCode) {
	switch (errorCode) {
		default: {
			break;
		}
	}
}
// *******************************************************

// ******** Begin of DataSource methods ********
int TwitterScene::numberOfSections(NO2Drawable *container) {
	if (m_data) {
		return 1;
	} else {
		return 0;
	}
}

int TwitterScene::numberOfItemsInSection(NO2Drawable *container, int section) {
	if (m_data) {
		return m_data->size();
	} else {
		return 0;
	}
}

NO2String *TwitterScene::templateForIndex(NO2Drawable *container, const NO2IndexPath &indexPath) {
	return _NO2STRING("cell_grid_tpl.html");
}

void TwitterScene::fillDataForIndex(NO2Drawable *container, NO2Drawable *tpl, NO2String *tplName, const NO2IndexPath &indexPath) {
    NO2Dictionary *data = (NO2Dictionary *) m_data->objectAtIndex(indexPath.index);
    
    if (data->getObjectByExpression("user.screen_name")) {
        ((NO2Label *) tpl->getChildWithId("nick"))->setText(data->getStringByExpression("user.screen_name"));
    } else {
        ((NO2Label *) tpl->getChildWithId("nick"))->setText(data->getStringByExpression("from_user_name"));
    }
    
    ((NO2Label *) tpl->getChildWithId("tweet"))->setText(data->getStringByExpression("text"));
    
    
    NO2String *url = NULL;
    if (data->getObjectByExpression("user.profile_image_url")) {
        url = data->getStringByExpression("user.profile_image_url");
    } else {
        url = data->getStringByExpression("profile_image_url");
    }
    
    NO2Image *img = (NO2Image *)m_imageCache->objectForKey(url);
    if(img == NULL) {
        // If it is a new image we can add it to the image cache.
        img = loadImage(url);
        m_imageCache->addObjectForKey(img, url);
    }

    ((NO2ImageView *) tpl->getChildWithId("user_photo"))->setImage(img);
}

void TwitterScene::didSelectedIndex(NO2Drawable *container, const NO2IndexPath &indexPath) {
}
// *********************************************


// ******** Begin of TextField Delegate methods ********
void TwitterScene::textFieldDidBeginEditing(NO2TextField *textField) {
}
void TwitterScene::textFieldDidEndEditing(NO2TextField *textField) {
}
void TwitterScene::textFieldDidChanged(NO2TextField *textField) {
}
void TwitterScene::textFieldDidReturn(NO2TextField *textField) {
    doSearch(textField->getText());
}
// *****************************************************



void TwitterScene::doSearch(strawberry::NO2String *searchTerm) {
    if (!searchTerm || !searchTerm->c_str()) return;
    runAction(_NO2STRING("hide_gridview"));
    
    NO2HTTPRequest *req = NULL;
    NO2String *str = NULL;
    
    if (searchTerm->hasPreffix("@")) {
        str = NO2String::stringWithFormat("http://api.twitter.com/1/statuses/user_timeline.json?screen_name=%s&count=50", ((NO2String *) searchTerm->split('@', true)->objectAtIndex(1))->URLEncode()->c_str());
    } else {
        str = NO2String::stringWithFormat("http://search.twitter.com/search.json?q=%s&count=50", searchTerm->URLEncode()->c_str());
    }
    
    LOG("%s", str->c_str());
    req = NO2HTTPRequest::requestWithURL(str);
    g_sharedDirector->addConnectionWithRequest(req, this);
    
    
    // Clear image cache
    m_imageCache->removeAllObjects();
}