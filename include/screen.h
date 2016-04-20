#ifndef SCREEN_H
#define SCREEN_H

#include "types.h"
#include "system.h"
#include "string.h"

int cursorX=0, cursorY=0;
const uint8 sw=80, sh=25, sd=2;   //sw =screen widht. sd =depth for colour

void ClearLine(uint8 from, uint8 to)
{
	uint16 i = sw*from*sd;		//start box of screen to clear
	string vidmem = (string)0xb8000;// first box of screen has this address
	for(i;i<(sw*(to+1)*sd);i++)
		vidmem[i] = 0x0;	//clear all the boxes by using 0x0
}

void UpdateCursor()
{
	unsigned int temp;
	temp = cursorY*sw + cursorX;
	
	outportb(0x3D4,14); //this address controls the cursor port in x86
	outportb(0x3D5,temp>>8);
	outportb(0x3D4, 15);
	outportb(0x3D5, temp);
}

void ClearScreen()
{
	ClearLine(0,sh-1);
	cursorX=0;
	cursorY=0;
	UpdateCursor();
}
	
void ScrollUp(uint8 lineNumber)
{
	string vidmem=(string)0xb8000;
	uint16 i = 0;
	for(i;i<sw*(sh-1)*sd;i++)
		vidmem[i] = vidmem[i+sw*sd*lineNumber];
	
	ClearLine(sh-1-lineNumber, sh-1);
	if((cursorY - lineNumber)<0)
	{
		cursorY = 0;
		cursorX = 0;
	}
	
	else
		cursorY -= lineNumber;
	UpdateCursor();
}

void NewLineCheck()
{
	if(cursorY>=sh-1)
		ScrollUp(1);
}

void PrintChar(char c)
{
	string vidmem = (string) 0xb8000;
	switch(c)
	{
		case (0x08):    // for backspace
			if(cursorX > 0)
			{
				cursorX--;
				vidmem[(cursorY*sw + cursorX)*sd]=0x00;
			}
			break;
 		case (0x09):  //for tab button
			cursorX = (cursorX + 8) & ~(8 - 1);
			break;
		case('\r'):
			cursorX = 0;
			break;
		case('\n'):
			cursorX = 0;
			cursorY++;
			break;
		default:
			vidmem[((cursorY*sw) + cursorX)*sd] = c;
			vidmem[((cursorY*sw) + cursorX)*sd+1] = 0x02; //colour
			cursorX++;
			break;
	}
	if(cursorX >= sw)
	{
		cursorX = 0;
		cursorY++;
	}
	NewLineCheck();
	UpdateCursor();
}

void print(string s)
{
	uint16 i = 0;
	uint8 length = stringlen(s);
	for(i;i<=length;i++)
		PrintChar(s[i]);
}

#endif
