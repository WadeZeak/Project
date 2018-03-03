#pragma once

#include<iostream>
#include<graphics.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")


#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT	 480 

typedef struct CharNode
{
	char chr;
	int x;
	int y;
	struct  CharNode *pNext;

}LETTER;


LETTER *pLetter = NULL;
IMAGE bkImg;
void Interface();
void playGame();
void CreateList();
void AddLetterNode();
