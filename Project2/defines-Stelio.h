#pragma once // initial day

#define SM_WINSOCK WM_USER+1 // intial day

#define LOGIN_BANNER "logo2.txt"
#define MUD_WINDOWTITLE "CSC_160 MUD Server (v0.0)"
#define WINDOW_CLASS "MUD_SRV"
#define MUD_TITLE "Shenannigans"
#define MUD_LSTNPORT 6776
#define MUD_TEXT_USERCOUNT 100
#define MUD_LINE_MAX 16384
#define MUD_SPAM_MAX 256

//Player Rank Flags

#define RANK_NONE 1<<1
#define RANK_PLAYER 1<<2
#define RANK_NEWBIE 1<<3
#define RANK_BUILDER 1<<4
#define RANK_ADMIN 1<<30
#define RANK_GOD 1<<31
#define RANK_ALL 4294967295


#define RESET		"\033[0m"
#define BLACK		"\033[30m"			   /* Black */
#define RED			"\033[31m"			   /* Red */
#define GREEN		"\033[32m"			   /* Green */
#define YELLOW		"\033[33m"			   /* Yellow */
#define BLUE		"\033[34m"			   /* Blue */
#define MAGENTA		"\033[35m"			   /* Magenta */
#define CYAN		"\033[36m"			   /* Cyan */
#define WHITE		"\033[37m"			   /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */



typedef unsigned long int FLAG;