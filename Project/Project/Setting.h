#pragma once
//==========================設計===================================


//=================================================================




/**************************問題***********************************/


/*****************************************************************/

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
using namespace std;
class Setting {
public:
	Setting();
	virtual  ~Setting();

	static const string  IMAGE_DIR = "game/images/";  //Folders.
		

	static const string  MAP_DIR;
	static const char *  FONT;  //Files / Assets.
	

	static const string  BACKGROUND;
	static const string  BACKGROUND_PLAY ;
	//static const std::string  HIGHSCORE = "game/files/highscore.txt";
	static const string  DEFAULT_MAP ;
	//static const unsigned int  LIFE = 3; //	Game settings.
	

	static unsigned int  ROUNDS ; //目前進行到的回合數
	//static const unsigned int  TIME_START = 120;
	static unsigned int  WEALTH ; //金錢(資源)

};

const string Setting::MAP_DIR = "game/maps/";
const string  Setting::MAP_DIR = "game/maps/";
const char *  Setting::FONT = "game/fonts/AARDC.TTF"; //Files / Assets.
const string  Setting::BACKGROUND = IMAGE_DIR + "background.png";
const string  Setting::BACKGROUND_PLAY = IMAGE_DIR + "playstate.png";
const string  Setting::DEFAULT_MAP = "game/files/defaultMap.rtd";
unsigned int  Setting::ROUNDS = 0; //目前進行到的回合數
unsigned int  Setting::WEALTH = 200; //金錢(資源)