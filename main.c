#include "wrapper.h"
#include "beep.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "des.h"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    #include <windows.h>
#endif

unsigned long timegen;
unsigned short lastcalled;

unsigned char* name = NULL;
unsigned char* key = NULL;

extern void init();
extern int main();
extern int beep(int freq, int ms);

size_t hex_to_bytes(const char* hex, unsigned char* out)
{
    size_t len = strlen(hex);
    if (len % 2 != 0) return 0;
    for (size_t i = 0; i < len / 2; i++)
    {
        unsigned int byte;
        if (sscanf(hex + 2*i, "%2x", &byte) != 1) return 0;
        out[i] = (unsigned char)byte;
    }
    return len / 2;
}

void GNU_GCC_1()
{
    return;
}

void refresh()
{
    char buffer[32];
    sprintf(buffer, "%lu", timegen);


    char combined[256];
    snprintf(combined, sizeof(combined), "%s%s%s", name, buffer, "updog");
    
    lastcalled = fl_checksum(combined);

    generate_key((unsigned char*)combined);
}

void init()
{
    timegen = unixtimestamp();

    if (!name) {
        name = malloc(64);
        if (!name) { perror("malloc"); exit(1); }
        memset(name, 0, 64);
    }
    if (!key) {
        key = malloc(256);
        if (!key) { perror("malloc"); exit(1); }
        memset(key, 0, 256);
    }
}

bool checksum()
{
    char buffer[32];
    sprintf(buffer, "%lu", 1920);
    unsigned short chk = fl_checksum(buffer);
#ifdef DEBUG
    printf("checksum %hu\n", chk);
#endif
    if (chk != 1484)
    {
        exit(1);
        return false;
    }

    char buffer1[32];
    sprintf(buffer1, "%lu", timegen);

    char combined[256];
    snprintf(combined, sizeof(combined), "%s%s%s", name, buffer1, "updog");

    unsigned char main_key[8] = {0};
    size_t combined_len = strlen(combined);
    if (combined_len >= 8) {
        memcpy(main_key, combined, 8);
    } else {
        memcpy(main_key, combined, combined_len);
    }
    key_set ks;
    generate_sub_keys(main_key, &ks);

    unsigned char plaintext[8] = { 'C','R','A','C','K','M','E','!' };
    unsigned char processed[8] = {0};

    process_message(plaintext, processed, &ks, ENCRYPTION_MODE);

#ifdef DEBUG
    {
        printf("DEBUG processed (enc) bytes: ");
        for (int i = 0; i < 8; ++i) printf("%02x", processed[i]);
        printf("\n");
    }
#endif
    unsigned char userkey_bytes[8] = {0};
    size_t userkey_len = hex_to_bytes((char*)key, userkey_bytes);

#ifdef DEBUG
    printf("DEBUG userkey_len=%zu\n", userkey_len);
#endif

    if (userkey_len != 8) {
        return false;
    }

    if (memcmp(userkey_bytes, processed, 8) == 0) {
        return true;
    }
    return false;
}

void funnies()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
    typedef BOOL (WINAPI *IsDebuggerPresent_t)(void);
    HMODULE hKernel32 = LoadLibraryA("kernel32.dll");
    if (!hKernel32) {exit(1);}
    IsDebuggerPresent_t pIsDebuggerPresent = (IsDebuggerPresent_t)GetProcAddress(hKernel32, "IsDebuggerPresent");
    if (!pIsDebuggerPresent) {exit(1);}
    BOOL a = pIsDebuggerPresent();
    FreeLibrary(hKernel32);

    if (a)
    {
        char buf[] = "qrohttre";
        rotN(buf, -13);
        for (int i = 0; i < 101; i++)
        {
            printf("%s\n", buf);
            fflush(stdout);
            beep(100, 10);s
        }
        char buf1[] = "cerff pgey+p gb dhvg";
        rotN(buf1, -13);
        printf("%s\n", buf1);
        for (;;)
        {
        }
        exit(1);
    }
#endif
}

void checker()
{
    if (checksum())
    {
        char buf[] = "penpxrq";
        rotN(buf, -13);
        for (int i = 0; i < 101; i++)
        {
            printf("%s\n", buf);
            fflush(stdout);
            beep(100, 10);
        }
        char buf1[] = "cerff pgey+p gb dhvg";
        rotN(buf1, -13);
        printf("%s\n", buf1);

        for (;;)
        {
        }
        exit(0);
    }
    else
    {
        printf("wrong\n");
        return;
    }
}

void GNU_GCC_2()
{
    return;
}

void (*f1)() = GNU_GCC_1;
void (*f3)() = GNU_GCC_2;

int main()
{
    size_t region_size = (char*)f3 - (char*)f1;
    #ifdef DEBUG
        printf("%zu\n", region_size);
    #endif
    if (region_size != 4294967280)
    {
        return -1;
    }
    init();
#ifdef DEBUG
    fprintf(stdout, "%lu\n", timegen);
#endif

    char buf1[] = "ragre lbhe hfreanzr";
    char buf2[] = "ragre lbhe cebqhpg xrl";

    rotN(buf1, -13);
    rotN(buf2, -13);

    for (;;)
    {
        printf("%s\n", buf1);

        scanf("%63s", name);
        refresh();
        printf("%s\n", buf2);

        scanf("%16s", key);
        checker();
        funnies();
    }

    free(name);
    free(key);

    return 1;
}
