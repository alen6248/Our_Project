// Project.cpp : �w�q�D���x���ε{�����i�J�I�C
//


//==========================�]�p===================================
//�{���j�������|����P�ĤH�j�h�]�p��reference (&)  �ӫDpointer



//=================================================================




/**************************���D***********************************/


/*****************************************************************/

//�ק�
//2015.12.29   �ﱼmain

//

#include "stdafx.h"
#include <iostream>
#include "SDL.h"
using namespace std;






void MouseInput();



int main()
{
	init();
	while (!quitGame && mainEvent->type != SDL_QUIT) { //game_loop
		int round = 0;  //�^�X��
		bool game_over = false;

		for (round = 1; game_over != true; round++) {  //round_loop
			input_interface(); //input ���a����
			deploy();  //���a�}�l�G�p
			game_over=calculate(); //�p�⵲�G 
			show_result();  //�M�X�w�g�p�⧹�����C���e�������a

		}//end of round_loop

	}//end of game_loop

	close();

    return 0;
}//end of main 
