#pragma once
//==========================設計===================================


//=================================================================




/**************************問題***********************************/
//使用tile?

/*****************************************************************/


#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include <cstring>
#include <vector>
#include "Map.h"

using namespace std;

class Abstract_Interface {

public:
	virtual void interface();  //主要函數

	Abstract_Interface();
	~Abstract_Interface();
	virtual void clockTick();
	virtual void draw(SDL_Surface *surface);
	virtual void keyPressed(SDLKey key); //??
	//Check if mouse hit a specific area.
	bool mouseHit(const int mouseX, const int mouseY, const int x, const int y, const int w, const int h);
	virtual void  mouseMoved(const int button, const int mouseX, const int mouseY);
	virtual void  mousePressed(const int button, const int mouseX, const int mouseY);
	virtual void initialize_interface();
	virtual void input(); //main input function
	//static const std::string  intToString(const int number);  //Convert Int to String.
	//static const std::vector< std::string >  getFilesInDir(const std::string dir);  //Get a list of files in a directory.


	Abstract_Interface *  state;
	SDL_Event  event;
	Map *  map;
	string  mapLoaded;
	int  myScore;
	unsigned int  round;
	bool  done;


};

class Start_State :public Abstract_Interface {
	virtual void interface();
	virtual void initialize_interface();
	virtual void  mouseMoved(const int button, const int mouseX, const int mouseY);
	virtual void  mousePressed(const int button, const int mouseX, const int mouseY);
};

class Edit_State :public Abstract_Interface {
	virtual void interface();  //主要函數
	virtual void initialize_interface();
	virtual void  mouseMoved(const int button, const int mouseX, const int mouseY);
	virtual void  mousePressed(const int button, const int mouseX, const int mouseY);
	virtual void input(); //main input function



};

class GameOver_State :public Abstract_Interface {


};

class Show_Result_State :public Abstract_Interface {


};