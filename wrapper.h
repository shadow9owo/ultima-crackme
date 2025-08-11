#pragma once

extern unsigned long unixtimestamp();
extern char* rotN(char* input, int diff);
extern int wraparound(int input,int min,int max);
extern unsigned short fl_checksum(char* input);