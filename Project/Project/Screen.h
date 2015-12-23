#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"  //還沒裝
#include "stdio.h"
#include "string"
#include <vector>
//==========================設計===================================
////引擎:SDL2
////遊戲介面、動畫效果
//主畫面

//地圖

//塔

//城堡

//敵人進擊動畫

//Bullet攻擊動畫

//點選塔出現選單與說明 
//塔的位置:升級資訊
//下方說明欄:目前塔的屬性與下一等級的屬性

//游標摸到塔出現浮動的簡略屬性資訊

//游標移到敵人時顯示血條

//點選敵人時
//敵人位置:出現血條
//下方說明欄:出現詳細敵人屬性資料

//敵人進入城堡的動畫



//=================================================================




/**************************問題***********************************/


/*****************************************************************/

class Screen_Manager {

public:
	class LTexture {
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile(std::string path);

		#ifdef _SDL_TTF_H			//這幹嘛用的??
		//Creates image from font string
		bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
		#endif 

		//Deallocates texture
		void free_texture();

		//Set color modulation
		void setColor(Uint8 red, Uint8 green, Uint8 blue);

		//Set blending
		void setBlendMode(SDL_BlendMode blending);

		//Set alpha modulation
		void setAlpha(Uint8 alpha);

		//Renders texture at given point
		void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
	};
	//需再宣告LTexture物件
	LTexture Map;
	LTexture Main_Screen;
	vector<LTexture> Texture_Set; 
	vector<LTexture> Enemy_Set;
	LTexture castle;
	LTexture Bullet;




	//Starts up SDL and creates window
	bool init();

	//Loads media
	bool loadMedia();

	//Frees media and shuts down SDL
	void close();

	//The window we'll be rendering to
	SDL_Window* gWindow = NULL;

	//The window renderer
	SDL_Renderer* gRenderer = NULL;

	//Scene texture
	LTexture gPromptTexture;




};

