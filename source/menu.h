#pragma once

#include "gfx.h"
#include "scanner.h"
#include "descriptor.h"

#define ENTRY_PATHLENGTH (128)
#define ENTRY_NAMELENGTH (64)
#define ENTRY_DESCLENGTH (128)
#define ENTRY_AUTHORLENGTH (64)
#define ENTRY_ARGLENGTH (256)
#define ENTRY_ICON_WIDTH (48)
#define ENTRY_ICON_HEIGHT (48)
#define ENTRY_ICONSIZE (ENTRY_ICON_WIDTH*ENTRY_ICON_HEIGHT*3)
#define ENTRY_WIDTH (66)
#define ENTRY_WIDTH_SELECTED (72)
#define ENTRY_FWIDTH (63)
#define ENTRY_FWIDTH_SELECTED (63)
#define ENTRY_HEIGHT (294)
#define ENTRY_HEIGHT_SELECTED (298)

#define ENTRY_BGCOLOR (u8[]){246, 252, 255}
#define ENTRY_BGCOLOR_SHADOW (u8[]){34, 153, 183}

#define fptToInt(v) ((v)>>10)
#define intToFpt(v) ((v)<<10)

typedef enum menuEntryType_s
{
	MENU_ENTRY_FILE,
	MENU_ENTRY_FOLDER,
}menuEntryType_s;

typedef struct menuEntry_s
{
	char executablePath[ENTRY_PATHLENGTH+1];
	char name[ENTRY_NAMELENGTH+1];
	char description[ENTRY_DESCLENGTH+1];
	char author[ENTRY_AUTHORLENGTH+1];
	char arg[ENTRY_ARGLENGTH+1];
	u8 iconData[ENTRY_ICONSIZE];
	menuEntryType_s type;
	descriptor_s descriptor;
	struct menuEntry_s* next;
}menuEntry_s;

typedef struct
{
	menuEntry_s* entries;
	u16 numEntries;
	u16 selectedEntry;
	s32 scrollTarget; //10 bit fixed point
	s32 scrollLocation; //10 bit fixed point
	s32 scrollVelocity; //10 bit fixed point
	s32 scrollBarSize;
	s32 currentScrollBarSize;
	s32 scrollBarPos;
	touchPosition previousTouch, firstTouch;
	u16 touchTimer;
	bool atEquilibrium;
}menu_s;

extern menuEntry_s regionfreeEntry;

//menu stuff
void initMenu(menu_s* m);
void drawMenu(menu_s* m);
bool updateMenu(menu_s* m);
void addMenuEntry(menu_s* m, menuEntry_s* me);
void addMenuEntryCopy(menu_s* m, menuEntry_s* me);
void sortMenu(menu_s* m);
void addMenuEntryAt(menu_s* m, menuEntry_s* me, int offset);
void addMenuEntryCopyAt(menu_s* m, menuEntry_s* me, int offset);
void clearMenuEntries(menu_s* m);
void createMenuEntry(menu_s* m, char* execPath, char* name, char* description, char* author, u8* iconData, menuEntryType_s type);
menuEntry_s* getMenuEntry(menu_s* m, u16 n);

//menu entry stuff
void initEmptyMenuEntry(menuEntry_s* me);
void initMenuEntry(menuEntry_s* me, char* execPath, char* name, char* description, char* author, u8* iconData, menuEntryType_s type);
int drawMenuEntry(menuEntry_s* me, gfxScreen_t screen, u16 x, u16 y, bool selected);

void scanMenuEntry(menuEntry_s* me);
void freeMenuEntry(menuEntry_s* me);
