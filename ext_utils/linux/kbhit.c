#include "kbhit.h"
#ifndef WIN32
#include <termios.h>
#include <unistd.h>   /* for read() */
#else
#include <io.h>
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif
#include <stdio.h>

#ifndef WIN32
static struct termios initial_settings, new_settings;
#endif
static int peek_character = -1;

void init_keyboard()
{
    printf("Initializing keyboard.\n");
#ifndef WIN32
    tcgetattr(0,&initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_lflag &= ~ISIG;
    new_settings.c_cc[VMIN] = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &new_settings);
#endif
}

void close_keyboard()
{
    printf("Restoring keyboard settings.\n");
#ifndef WIN32
    tcsetattr(0, TCSANOW, &initial_settings);
#endif
}

int kbhit()
{
    unsigned char ch;
    int nread;
    
    if (peek_character != -1) return 1;
#ifndef WIN32
    new_settings.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &new_settings);
#endif
    nread = read(0,&ch,1);
#ifndef WIN32
    new_settings.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &new_settings);
#endif
    if(nread == 1)
    {
        peek_character = ch;
        return 1;
    }
    return 0;
}

int readch()
{
    char ch;
    ssize_t ret;

    if(peek_character != -1)
    {
        ch = peek_character;
        peek_character = -1;
        return ch;
    }
    ret = read(0,&ch,1);
    return ch;
}

