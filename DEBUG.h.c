 #ifndef _DEBUG_H
 #define _DEBUG_H
  
 //Подключаем библиотеки
 #include <stdio.h>
 #include <os_port.h>
  
 //Определения уровня трассировки
 #define TRACE_LEVEL_OFF      0
 #define TRACE_LEVEL_FATAL    1
 #define TRACE_LEVEL_ERROR    2
 #define TRACE_LEVEL_WARNING  3
 #define TRACE_LEVEL_INFO     4
 #define TRACE_LEVEL_DEBUG    5
 #define TRACE_LEVEL_VERBOSE  6
  
 //Уровень трассировки по умолчанию
 #ifndef TRACE_LEVEL
    #define TRACE_LEVEL TRACE_LEVEL_DEBUG
 #endif
  
 //Перенаправление выходных данных трассировки
 #ifndef TRACE_PRINTF
    #define TRACE_PRINTF(...) osSuspendAllTasks(), fprintf(stderr, __VA_ARGS__), osResumeAllTasks()
 #endif
  
 #ifndef TRACE_ARRAY
    #define TRACE_ARRAY(p, a, n) osSuspendAllTasks(), debugDisplayArray(stderr, p, a, n), osResumeAllTasks()
 #endif
  
 #ifndef TRACE_MPI
    #define TRACE_MPI(p, a) osSuspendAllTasks(), mpiDump(stderr, p, a), osResumeAllTasks()
 #endif
  
 //Отладочные макросы
 #if (TRACE_LEVEL >= TRACE_LEVEL_FATAL)
    #define TRACE_FATAL(...) TRACE_PRINTF(__VA_ARGS__)
    #define TRACE_FATAL_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
    #define TRACE_FATAL_MPI(p, a) TRACE_MPI(p, a)
 #else
    #define TRACE_FATAL(...)
    #define TRACE_FATAL_ARRAY(p, a, n)
    #define TRACE_FATAL_MPI(p, a)
 #endif
  
 #if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
    #define TRACE_ERROR(...) TRACE_PRINTF(__VA_ARGS__)
    #define TRACE_ERROR_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
    #define TRACE_ERROR_MPI(p, a) TRACE_MPI(p, a)
 #else
    #define TRACE_ERROR(...)
    #define TRACE_ERROR_ARRAY(p, a, n)
    #define TRACE_ERROR_MPI(p, a)
 #endif
  
 #if (TRACE_LEVEL >= TRACE_LEVEL_WARNING)
    #define TRACE_WARNING(...) TRACE_PRINTF(__VA_ARGS__)
    #define TRACE_WARNING_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
    #define TRACE_WARNING_MPI(p, a) TRACE_MPI(p, a)
 #else
    #define TRACE_WARNING(...)
    #define TRACE_WARNING_ARRAY(p, a, n)
    #define TRACE_WARNING_MPI(p, a)
 #endif
  
 #if (TRACE_LEVEL >= TRACE_LEVEL_INFO)
    #define TRACE_INFO(...) TRACE_PRINTF(__VA_ARGS__)
    #define TRACE_INFO_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
    #define TRACE_INFO_NET_BUFFER(p, b, o, n)
    #define TRACE_INFO_MPI(p, a) TRACE_MPI(p, a)
 #else
    #define TRACE_INFO(...)
    #define TRACE_INFO_ARRAY(p, a, n)
    #define TRACE_INFO_NET_BUFFER(p, b, o, n)
    #define TRACE_INFO_MPI(p, a)
 #endif
  
 #if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
    #define TRACE_DEBUG(...) TRACE_PRINTF(__VA_ARGS__)
    #define TRACE_DEBUG_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
    #define TRACE_DEBUG_NET_BUFFER(p, b, o, n)
    #define TRACE_DEBUG_MPI(p, a) TRACE_MPI(p, a)
 #else
    #define TRACE_DEBUG(...)
    #define TRACE_DEBUG_ARRAY(p, a, n)
    #define TRACE_DEBUG_NET_BUFFER(p, b, o, n)
    #define TRACE_DEBUG_MPI(p, a)
 #endif
  
 #if (TRACE_LEVEL >= TRACE_LEVEL_VERBOSE)
    #define TRACE_VERBOSE(...) TRACE_PRINTF(__VA_ARGS__)
    #define TRACE_VERBOSE_ARRAY(p, a, n) TRACE_ARRAY(p, a, n)
    #define TRACE_VERBOSE_NET_BUFFER(p, b, o, n)
    #define TRACE_VERBOSE_MPI(p, a) TRACE_MPI(p, a)
 #else
    #define TRACE_VERBOSE(...)
    #define TRACE_VERBOSE_ARRAY(p, a, n)
    #define TRACE_VERBOSE_NET_BUFFER(p, b, o, n)
    #define TRACE_VERBOSE_MPI(p, a)
 #endif
  
 //C++ настройка
 #ifdef __cplusplus
 extern "C" {
 #endif
  
 //Функции, связанные с отладкой
 void debugInit(uint32_t baudrate);
  
 void debugDisplayArray(FILE *stream,
    const char_t *prepend, const void *data, size_t length);
  
 //Устаревшие определения
 #define TRACE_LEVEL_NO_TRACE TRACE_LEVEL_OFF
  
 //C++ настройка
 #ifdef __cplusplus
 }
 #endif
  
 #endif