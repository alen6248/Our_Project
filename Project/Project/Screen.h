#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"  //�٨S��
#include "stdio.h"
#include "string"
#include <vector>
//==========================�]�p===================================
////����:SDL2
////�C�������B�ʵe�ĪG
//�D�e��

//�a��

//��

//����

//�ĤH�i���ʵe

//Bullet�����ʵe

//�I���X�{���P���� 
//�𪺦�m:�ɯŸ�T
//�U�軡����:�ثe���ݩʻP�U�@���Ū��ݩ�

//��кN���X�{�B�ʪ�²���ݩʸ�T

//��в���ĤH����ܦ��

//�I��ĤH��
//�ĤH��m:�X�{���
//�U�軡����:�X�{�ԲӼĤH�ݩʸ��

//�ĤH�i�J�������ʵe



//=================================================================




/**************************���D***********************************/


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

		#ifdef _SDL_TTF_H			//�o�F���Ϊ�??
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
	//�ݦA�ŧiLTexture����
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

