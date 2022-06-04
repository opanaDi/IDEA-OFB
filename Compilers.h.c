 #ifndef _COMPILER_PORT_H
 #define _COMPILER_PORT_H
  
 //Подключаем библиотеки
 #include <stddef.h>
 #include <stdint.h>
 #include <inttypes.h>
  
 //C++ охрана
 #ifdef __cplusplus
 extern "C" {
 #endif
  
 //Типы данных
 typedef char char_t;
 typedef signed int int_t;
 typedef unsigned int uint_t;
  
 #if !defined(R_TYPEDEFS_H) && !defined(USE_CHIBIOS_2)
    typedef int bool_t;
 #endif
  
 //ARM компилятор?
 #if defined(__CC_ARM)
    #undef PRIu8
    #undef PRIu16
    #define PRIu8 "u"
    #define PRIu16 "u"
    #define PRIuSIZE "u"
    #define PRIXSIZE "X"
    #define PRIuTIME "lu"
 //Microchip XC32 компилятор?
 #elif defined(__XC32)
    #define PRIuSIZE "u"
    #define PRIXSIZE "X"
    #define PRIuTIME "u"
 //NXP MCUXpresso компилятор?
 #elif defined(__MCUXPRESSO)
    #undef PRIu64
    #define PRIu64 "llu"
    #define PRIuSIZE "u"
    #define PRIXSIZE "X"
    #define PRIuTIME "lu"
 //NXP CodeWarrior компилятор?
 #elif defined(__CWCC__)
    #define PRIu8 "u"
    #define PRIu16 "u"
    #define PRIu32 "u"
    #define PRIx8 "x"
    #define PRIx16 "x"
    #define PRIx32 "x"
    #define PRIX8 "X"
    #define PRIX16 "X"
    #define PRIX32 "X"
    #define PRIuSIZE "u"
    #define PRIXSIZE "X"
    #define PRIuTIME "u"
 //Espressif ESP-IDF компилятор?
 #elif defined(IDF_VER)
    #undef PRIu8
    #undef PRIu16
    #undef PRIu32
    #undef PRIx8
    #undef PRIx16
    #undef PRIx32
    #undef PRIX8
    #undef PRIX16
    #undef PRIX32
    #define PRIu8 "u"
    #define PRIu16 "u"
    #define PRIu32 "u"
    #define PRIx8 "x"
    #define PRIx16 "x"
    #define PRIx32 "x"
    #define PRIX8 "X"
    #define PRIX16 "X"
    #define PRIX32 "X"
    #define PRIuSIZE "u"
    #define PRIXSIZE "X"
    #define PRIuTIME "lu"
 //Linux GCC компилятор
 #elif defined(__linux__)
    #define PRIuSIZE "zu"
    #define PRIXSIZE "zX"
    #define PRIuTIME "lu"
 //Win32 компилятор?
 #elif defined(_WIN32)
    #define PRIuSIZE "Iu"
    #define PRIXSIZE "IX"
    #define PRIuTIME "lu"
 #else
    #define PRIuSIZE "u"
    #define PRIXSIZE "X"
    #define PRIuTIME "lu"
 #endif
  
 //ARM компилятор V6?
 #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    char *strtok_r(char *s, const char *delim, char **last);
 //GCC компилятор?
 #elif defined(__GNUC__)
    int strcasecmp(const char *s1, const char *s2);
    int strncasecmp(const char *s1, const char *s2, size_t n);
    char *strtok_r(char *s, const char *delim, char **last);
 //NXP CodeWarrior компилятор?
 #elif defined(__CWCC__)
    typedef uint32_t time_t;
    int strcasecmp(const char *s1, const char *s2);
    int strncasecmp(const char *s1, const char *s2, size_t n);
    char *strtok_r(char *s, const char *delim, char **last);
 //TI ARM компилятор?
 #elif defined(__TI_ARM__)
    int strcasecmp(const char *s1, const char *s2);
    int strncasecmp(const char *s1, const char *s2, size_t n);
    char *strtok_r(char *s, const char *delim, char **last);
 //Microchip XC32 компилятор?
 #elif defined(__XC32)
    #define sprintf _sprintf
    int sprintf(char * str, const char * format, ...);
    int strcasecmp(const char *s1, const char *s2);
    int strncasecmp(const char *s1, const char *s2, size_t n);
    char *strtok_r(char *s, const char *delim, char **last);
 #endif
  
 //ARM компилятор V6?
 #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #undef __start_packed
    #define __start_packed
    #undef __end_packed
    #define __end_packed __attribute__((packed))
 //GCC компилятор?
 #elif defined(__GNUC__)
    #undef __start_packed
    #define __start_packed
    #undef __end_packed
    #define __end_packed __attribute__((__packed__))
 //ARM компилятор?
 #elif defined(__CC_ARM)
    #pragma anon_unions
    #undef __start_packed
    #define __start_packed __packed
    #undef __end_packed
    #define __end_packed
 //IAR компилятор?
 #elif defined(__IAR_SYSTEMS_ICC__)
    #undef __start_packed
    #define __start_packed __packed
    #undef __end_packed
    #define __end_packed
 //NXP CodeWarrior компилятор?
 #elif defined(__CWCC__)
    #undef __start_packed
    #define __start_packed
    #undef __end_packed
    #define __end_packed
 //TI ARM компилятор?
 #elif defined(__TI_ARM__)
    #undef __start_packed
    #define __start_packed
    #undef __end_packed
    #define __end_packed __attribute__((__packed__))
 //Win32 компилятор?
 #elif defined(_WIN32)
    #undef interface
    #undef __start_packed
    #define __start_packed
    #undef __end_packed
    #define __end_packed
 #endif
  
 #ifndef __weak_func
    //ARM компилятор V6?
    #if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
       #define __weak_func __attribute__((weak))
    //GCC компилятор?
    #elif defined(__GNUC__)
       #define __weak_func __attribute__((weak))
    //ARM компилятор?
    #elif defined(__CC_ARM)
       #define __weak_func __weak
    //IAR компилятор?
    #elif defined(__IAR_SYSTEMS_ICC__)
       #define __weak_func __weak
    //NXP CodeWarrior компилятор?
    #elif defined(__CWCC__)
       #define __weak_func
    //TI ARM компилятор?
    #elif defined(__TI_ARM__)
       #define __weak_func __attribute__((weak))
    //Win32 компилятор?
    #elif defined(_WIN32)
       #define __weak_func
    #endif
 #endif
  
 //C++ охрана
 #ifdef __cplusplus
 }
 #endif
  
 #endif