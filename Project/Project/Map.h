#pragma once


//==========================�]�p===================================


//=================================================================




/**************************���D***********************************/
//�ϥ�tile?

/*****************************************************************/
#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <vector>
using namespace std;
class Map {
public:
	Map(int map_x, int map_y);
	virtual ~Map();
	void draw(SDL_Surface *surface);
	void  loadImageFile(string filename);  //Load map to game.
	void  setTile(int type, int x, int y); 
	//vector< int >  getEnvironment(int position); //Get tile - type in all four direction.
	//bool  mouseOver(int x, int y);  //Check if mouse is over the map or outside map.
		
	//static std::string  getImage(int type);


	string  mapImage_Loaded;  //map�ɮצW
	//int  mousePosition;
	int  sizeX;  //�e��size
	int  sizeY;	
	//int  startPoint; //??
	//int  endPoint; //??
	//int  squareSize;
	//vector< SDL_Texture * >  tower_stage; //�i��m��,���s�A���U���X���
									//��m�ĤH���|?

	//SDL_Surface *  imageStartPoint;  
	//SDL_Surface *  imageEndPoint;




};