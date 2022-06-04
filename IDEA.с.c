//Переключаемся на соответствующий уровень трассировки
 #define TRACE_LEVEL CRYPTO_TRACE_LEVEL
  
 //Подключаем библиотеки
 #include "core/crypto.h"
 #include "cipher/idea.h"
 #include "debug.h"
  
 //Проверяем конфигурацию криптографической библиотеки
 #if (IDEA_SUPPORT == ENABLED)
  
 //Общий интерфейс для алгоритмов шифрования
 const CipherAlgo ideaCipherAlgo =
 {
    "IDEA",
    sizeof(IdeaContext),
    CIPHER_ALGO_TYPE_BLOCK,
    IDEA_BLOCK_SIZE,
    (CipherAlgoInit) ideaInit,
    NULL,
    NULL,
    (CipherAlgoEncryptBlock) ideaEncryptBlock,
    (CipherAlgoDecryptBlock) ideaDecryptBlock
 };
  
  
 /**
  * @brief Модульное умножение
  * @параметр[in] a Первый операнд
  * @параметр[in] b Второй операнд
  * @возврат Результирующего значения
  **/
  
 static uint16_t ideaMul(uint16_t a, uint16_t b)
 {
    uint32_t c;
  
    //Выполняем умножение по модулю 2^16 - 1
    c = a * b;
  
    if(c != 0)
    {
       c = ((ROL32(c, 16) - c) >> 16) + 1;
    }
    else
    {
       c = 1 - a - b;
    }
  
    //Возвравращаем результат
    return c & 0xFFFF;
 }
  
  
 /**
  * @brief Вычисляем обратный модуль
  * @параметр[in] a операнд
  * @возврат Результирующего значения
  **/
  
 static uint16_t ideaInv(uint16_t a)
 {
    uint32_t b;
    uint32_t q;
    uint32_t r;
    int32_t t;
    int32_t u;
    int32_t v;
  
    //Вычисляем мультипликативную обратную величину по модулю 2^16 - 1
    b = 0x10001;
    u = 0;
    v = 1;
  
    while(a > 0)
    {
       q = b / a;
       r = b % a;
  
       b = a;
       a = r;
  
       t = v;
       v = u - q * v;
       u = t;
    }
  
    if(u < 0)
    {
       u += 0x10001;
    }
  
    //Возвравращаем результат
    return u;
 }
  
  
 /**
  * @brief Инициализируем контекст IDEA с помощью предоставленного ключа
  * @параметр[in] контекстный указатель на контекст IDEA для инициализации
  * @параметр[in] ключ-Pointer Указатель на ключ
  * @параметр[in] ключ-Len Длина ключа
  * @возвращаем код ошибки
  **/
  
 error_t ideaInit(IdeaContext *context, const uint8_t *key, size_t keyLen)
 {
    uint_t i;
    uint16_t *ek;
    uint16_t *dk;
  
    //Проверка параметров
    if(context == NULL || key == NULL)
       return ERROR_INVALID_PARAMETER;
  
    //Недопустимая длина ключа?
    if(keyLen != 16)
       return ERROR_INVALID_KEY_LENGTH;
  
    //Указываем на подразделы шифрования и дешифрования
    ek = context->ek;
    dk = context->dk;
  
    //Во-первых, 128-битный ключ разбивается на восемь 16-битных подблоков
    for(i = 0; i < 8; i++)
    {
       ek[i] = LOAD16BE(key + i * 2);
    }
  
    //Разворачиваем подразделы шифрования
    for(i = 8; i < 52; i++)
    {
       if((i % 8) == 6)
       {
          ek[i] = (ek[i - 7] << 9) | (ek[i - 14] >> 7);
       }
       else if((i % 8) == 7)
       {
          ek[i] = (ek[i - 15] << 9) | (ek[i - 14] >> 7);
       }
       else
       {
          ek[i] = (ek[i - 7] << 9) | (ek[i - 6] >> 7);
       }
    }
  
    //Генерируеем подразделы для расшифровки
    for(i = 0; i < 52; i += 6)
    {
       dk[i] = ideaInv(ek[48 - i]);
  
       if(i == 0 || i == 48)
       {
          dk[i + 1] = -ek[49 - i];
          dk[i + 2] = -ek[50 - i];
       }
       else
       {
          dk[i + 1] = -ek[50 - i];
          dk[i + 2] = -ek[49 - i];
       }
  
       dk[i + 3] = ideaInv(ek[51 - i]);
  
       if(i < 48)
       {
          dk[i + 4] = ek[46 - i];
          dk[i + 5] = ek[47 - i];
       }
    }
  
    //Нет сообщения об ошибке
    return NO_ERROR;
 }
  
  
 /**
  * @brief Шифрование 16-байтового блока с использованием алгоритма IDEA
  * @параметр[in] контекстный указатель на контекст IDEA
  * @параметр[in] входной блок открытого текста для шифрования
  * @параметр[out] выходной блок зашифрованного текста, полученный в результате шифрования
  **/
  
 void ideaEncryptBlock(IdeaContext *context, const uint8_t *input, uint8_t *output)
 {
    uint_t i;
    uint16_t e;
    uint16_t f;
    uint16_t *k;
  
    //Открытый текст разделен на четыре 16-разрядных регистра
    uint16_t a = LOAD16BE(input + 0);
    uint16_t b = LOAD16BE(input + 2);
    uint16_t c = LOAD16BE(input + 4);
    uint16_t d = LOAD16BE(input + 6);
  
    //Указываем на ключевую точку
    k = context->ek;
  
    //Процесс состоит из восьми идентичных этапов шифрования
    for(i = 0; i < 8; i++)
    {
       //Обращаемся к циклу
       a = ideaMul(a, k[0]);
       b += k[1];
       c += k[2];
       d = ideaMul(d, k[3]);
  
       e = a ^ c;
       f = b ^ d;
  
       e = ideaMul(e, k[4]);
       f += e;
       f = ideaMul(f, k[5]);
       e += f;
  
       a ^= f;
       d ^= e;
       e ^= b;
       f ^= c;
  
       b = f;
       c = e;
  
       //Предварительное текущее местоположение в ключевом расписании
       k += 6;
    }
  
    //Четыре 16-битных значения, полученные в конце 8-го шифрования
    //Раунды объединяются с последними четырьмя из 52 ключевых подблоков
    a = ideaMul(a, k[0]);
    c += k[1];
    b += k[2];
    d = ideaMul(d, k[3]);
  
    //Результирующее значение представляет собой зашифрованный текст
    STORE16BE(a, output + 0);
    STORE16BE(c, output + 2);
    STORE16BE(b, output + 4);
    STORE16BE(d, output + 6);
 }
  
  
 /**
  * @brief Расшифровываем 16-байтовый блок с помощью алгоритма IDEA
  * @параметр[in] контекстный указатель на контекст IDEA
  * @параметр[in] входной блок зашифрованного текста для расшифровки
  * @параметр[out] выходной блок открытого текста, полученный в результате дешифрования
  **/
  
 void ideaDecryptBlock(IdeaContext *context, const uint8_t *input, uint8_t *output)
 {
    uint_t i;
    uint16_t e;
    uint16_t f;
    uint16_t *k;
  
    //Зашифрованный текст разделен на четыре 16-битных регистра
    uint16_t a = LOAD16BE(input + 0);
    uint16_t b = LOAD16BE(input + 2);
    uint16_t c = LOAD16BE(input + 4);
    uint16_t d = LOAD16BE(input + 6);
  
    //Указываем на ключевую точку
    k = context->dk;
  
    //Вычислительный процесс, используемый для дешифрования зашифрованного текста, представляет собой
    //По сути, то же самое, что используется для шифрования открытого текста
    for(i = 0; i < 8; i++)
    {
       //Обращаемся к циклу
       a = ideaMul(a, k[0]);
       b += k[1];
       c += k[2];
       d = ideaMul(d, k[3]);
  
       e = a ^ c;
       f = b ^ d;
  
       e = ideaMul(e, k[4]);
       f += e;
       f = ideaMul(f, k[5]);
       e += f;
  
       a ^= f;
       d ^= e;
       e ^= b;
       f ^= c;
  
       b = f;
       c = e;
  
       //Предварительное текущее местоположение в ключевом расписании
       k += 6;
    }
  
    //Четыре 16-битных значения, полученные в конце 8-го шифрования
    //Раунды объединяются с последними четырьмя из 52 ключевых подблоков
    a = ideaMul(a, k[0]);
    c += k[1];
    b += k[2];
    d = ideaMul(d, k[3]);
  
    //Результирующее значение представляет собой открытый текст
    STORE16BE(a, output + 0);
    STORE16BE(c, output + 2);
    STORE16BE(b, output + 4);
    STORE16BE(d, output + 6);
 }
  
 #endif