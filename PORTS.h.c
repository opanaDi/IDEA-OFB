#ifndef _OS_PORT_H
 #define _OS_PORT_H
  
 //Подключаем библиотеки
 #include <os_port_config.h>
 #include <compiler_port.h>
  
 //Флаги компиляции, используемые для включения/отключения функций
 #define ENABLED  1
 #define DISABLED 0
  
 #define PTR_OFFSET(addr, offset) ((void *) ((uint8_t *) (addr) + (offset)))
  
 #define timeCompare(t1, t2) ((int32_t) ((t1) - (t2)))
  
 //Разные макросы
 #ifndef FALSE
    #define FALSE 0
 #endif
  
 #ifndef TRUE
    #define TRUE 1
 #endif
  
 #ifndef LSB
    #define LSB(x) ((x) & 0xFF)
 #endif
  
 #ifndef MSB
    #define MSB(x) (((x) >> 8) & 0xFF)
 #endif
  
 #ifndef MIN
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
 #endif
  
 #ifndef MAX
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
 #endif
  
 #ifndef arraysize
    #define arraysize(a) (sizeof(a) / sizeof(a[0]))
 #endif
  
 //Бесконечная задержка
 #define INFINITE_DELAY ((uint_t) -1)
 //Максимальная задержка
 #define MAX_DELAY (INFINITE_DELAY / 2)
  
 //Нет ли Операционной системы реального времени
 #if defined(USE_NO_RTOS)
    #include <os_port_none.h>
 //ChibiOS/RT порт?
 #elif defined(USE_CHIBIOS)
    #include <os_port_chibios.h>
 //CMX-RTX порт?
 #elif defined(USE_CMX_RTX)
    #include <os_port_cmx_rtx.h>
 //CMSIS-RTOS порт?
 #elif defined(USE_CMSIS_RTOS)
    #include <os_port_cmsis_rtos.h>
 //CMSIS-RTOS2 порт?
 #elif defined(USE_CMSIS_RTOS2)
    #include <os_port_cmsis_rtos2.h>
 //FreeRTOS порт?
 #elif defined(USE_FREERTOS)
    #include <os_port_freertos.h>
 //SafeRTOS порт?
 #elif defined(USE_SAFERTOS)
    #include <os_port_safertos.h>
 //Azure RTOS ThreadX порт?
 #elif defined(USE_THREADX)
    #include <os_port_threadx.h>
 //Keil RTX порт?
 #elif defined(USE_RTX)
    #include <os_port_rtx.h>
 //Micrium uC/OS-II порт?
 #elif defined(USE_UCOS2)
    #include <os_port_ucos2.h>
 //Micrium uC/OS-III порт?
 #elif defined(USE_UCOS3)
    #include <os_port_ucos3.h>
 //Segger embOS порт?
 #elif defined(USE_EMBOS)
    #include <os_port_embos.h>
 //TI SYS/BIOS порт?
 #elif defined(USE_SYS_BIOS)
    #include <os_port_sys_bios.h>
 //Zephyr порт?
 #elif defined(USE_ZEPHYR)
    #include <os_port_zephyr.h>
 //Windows порт?
 #elif defined(_WIN32)
    #include <os_port_windows.h>
 //POSIX Threads порт?
 #elif defined(__linux__) || defined(__FreeBSD__)
    #include <os_port_posix.h>
 #endif
  
 //Заполняем блок памяти
 #ifndef osMemset
    #include <string.h>
    #define osMemset(p, value, length) (void) memset(p, value, length)
 #endif
  
 //Копируем блок памяти
 #ifndef osMemcpy
    #include <string.h>
    #define osMemcpy(dest, src, length) (void) memcpy(dest, src, length)
 #endif
  
 //Перемещаем блок памяти
 #ifndef osMemmove
    #include <string.h>
    #define osMemmove(dest, src, length) (void) memmove(dest, src, length)
 #endif
  
 //Сравниваем два блока памяти
 #ifndef osMemcmp
    #include <string.h>
    #define osMemcmp(p1, p2, length) memcmp(p1, p2, length)
 #endif
  
 //Получаем длину строки
 #ifndef osStrlen
    #include <string.h>
    #define osStrlen(s) strlen(s)
 #endif
  
 //Сравниваем строк
 #ifndef osStrcmp
    #include <string.h>
    #define osStrcmp(s1, s2) strcmp(s1, s2)
 #endif
  
 //Сравниваем подстроки
 #ifndef osStrncmp
    #include <string.h>
    #define osStrncmp(s1, s2, length) strncmp(s1, s2, length)
 #endif
  
 //Сравниваем строк без регистра
 #ifndef osStrcasecmp
    #include <string.h>
    #define osStrcasecmp(s1, s2) strcasecmp(s1, s2)
 #endif
  
 //Сравниваем подстроки без регистра
 #ifndef osStrncasecmp
    #include <string.h>
    #define osStrncasecmp(s1, s2, length) strncasecmp(s1, s2, length)
 #endif
  
 //Поиск первого вхождения данного символа
 #ifndef osStrchr
    #include <string.h>
    #define osStrchr(s, c) strchr(s, c)
 #endif
  
 //Поиск первого вхождения подстроки
 #ifndef osStrstr
    #include <string.h>
    #define osStrstr(s1, s2) strstr(s1, s2)
 #endif
  
 //Копируем строку
 #ifndef osStrcpy
    #include <string.h>
    #define osStrcpy(s1, s2) (void) strcpy(s1, s2)
 #endif
  
 //Копируем символы из строки
 #ifndef osStrncpy
    #include <string.h>
    #define osStrncpy(s1, s2, length) (void) strncpy(s1, s2, length)
 #endif
  
 //Объединяем строк
 #ifndef osStrcat
    #include <string.h>
    #define osStrcat(s1, s2) (void) strcat(s1, s2)
 #endif
  
 //Извлекаем токенов из строки
 #ifndef osStrtok_r
    #include <string.h>
    #define osStrtok_r(s, delim, last) strtok_r(s, delim, last)
 #endif
  
 //Форматируем строку
 #ifndef osSprintf
    #include <stdio.h>
    #define osSprintf(dest, ...) sprintf(dest, __VA_ARGS__)
 #endif
  
 //Форматируем строку
 #ifndef osVsnprintf
    #include <stdio.h>
    #define osVsnprintf(dest, size, format, ap) vsnprintf(dest, size, format, ap)
 #endif
  
 //Преобразуем строку в длинное целое число без знака
 #ifndef osStrtoul
    #include <stdlib.h>
    #define osStrtoul(s, endptr, base) strtoul(s, endptr, base)
 #endif
  
 //Преобразовать строку в длинное длинное целое число без знака
 #ifndef osStrtoull
    #include <stdlib.h>
    #define osStrtoull(s, endptr, base) strtoull(s, endptr, base)
 #endif
  
 //Преобразование символа в нижний регистр
 #ifndef osTolower
    #include <ctype.h>
    #define osTolower(c) tolower((uint8_t) (c))
 #endif
  
 //Преобразование символа в верхний регистр
 #ifndef osToupper
    #include <ctype.h>
    #define osToupper(c) toupper((uint8_t) (c))
 #endif
  
 //Проверка, является ли символ заглавной буквой
 #ifndef osIsupper
    #include <ctype.h>
    #define osIsupper(c) isupper((uint8_t) (c))
 #endif
  
 //Проверка, является ли символ десятичной цифрой
 #ifndef osIsdigit
    #include <ctype.h>
    #define osIsdigit(c) isdigit((uint8_t) (c))
 #endif
  
 //Проверка, является ли символ символом пробела
 #ifndef osIsspace
    #include <ctype.h>
    #define osIsspace(c) isspace((uint8_t) (c))
 #endif
  
 //Проверка, является ли символ пустым символом
 #ifndef osIsblank
    #define osIsblank(c) ((c) == ' ' || (c) == '\t')
 #endif
  
 #if !defined(__linux__) && !defined(__FreeBSD__)
  
 //Процедуры задержки
 #ifndef usleep
    #define usleep(delay) {volatile uint32_t n = delay * 4; while(n > 0) n--;}
 #endif
  
 #ifndef sleep
    #define sleep(delay) {volatile uint32_t n = delay * 4000; while(n > 0) n--;}
 #endif
  
 #endif
  
 //Объект задачи (устарел)
 #define OsTask void
 //Недопустимое значение дескриптора (устарело)
 #define OS_INVALID_HANDLE OS_INVALID_TASK_ID
  
 #endif