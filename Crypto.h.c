 #ifndef _CRYPTO_LEGACY_H
 #define _CRYPTO_LEGACY_H
  
 //Устаревшие функции
 #define mpiReadRaw(r, data, length) mpiImport(r, data, length, MPI_FORMAT_BIG_ENDIAN)
 #define mpiWriteRaw(a, data, length) mpiExport(a, data, length, MPI_FORMAT_BIG_ENDIAN)
  
 #ifdef CURVE25519_SUPPORT
    #define X25519_SUPPORT CURVE25519_SUPPORT
 #endif
  
 #ifdef CURVE448_SUPPORT
    #define X448_SUPPORT CURVE448_SUPPORT
 #endif
  
 #define ecdsaGenerateKeyPair ecGenerateKeyPair
 #define ecdsaGeneratePrivateKey ecGeneratePrivateKey
 #define ecdsaGeneratePublicKey ecGeneratePublicKey
  
 #define MAX_HASH_CONTEXT_SIZE sizeof(HashContext)
 #define MAX_CIPHER_CONTEXT_SIZE sizeof(CipherContext)
  
 #ifdef SAMD51_CRYPTO_PUKCC_SUPPORT
    #define SAMD51_CRYPTO_PKC_SUPPORT SAMD51_CRYPTO_PUKCC_SUPPORT
 #endif
  
 #ifdef SAME54_CRYPTO_PUKCC_SUPPORT
    #define SAME54_CRYPTO_PKC_SUPPORT SAME54_CRYPTO_PUKCC_SUPPORT
 #endif
  
 #endif