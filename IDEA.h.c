 #ifndef _IDEA_H
 #define _IDEA_H
  
 //Подключаем библиотеки
 #include "core/crypto.h"
  
 //IDEA блочный размер
 #define IDEA_BLOCK_SIZE 8
 //Common interface for encryption algorithms
 #define IDEA_CIPHER_ALGO (&ideaCipherAlgo)
  
 //C++ охрана
 #ifdef __cplusplus
 extern "C" {
 #endif
  
  
 /**
  * @brief IDEA контекст алгоритма
  **/
  
 typedef struct
 {
    uint16_t ek[52];
    uint16_t dk[52];
 } IdeaContext;
  
  
 //IDEA связанные константы
 extern const CipherAlgo ideaCipherAlgo;
  
 //IDEA связанные функции
 error_t ideaInit(IdeaContext *context, const uint8_t *key, size_t keyLen);
 void ideaEncryptBlock(IdeaContext *context, const uint8_t *input, uint8_t *output);
 void ideaDecryptBlock(IdeaContext *context, const uint8_t *input, uint8_t *output);
  
 //C++ охрана
 #ifdef __cplusplus
 }
 #endif
  
 #endif