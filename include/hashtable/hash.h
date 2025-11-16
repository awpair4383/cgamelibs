#ifndef HASH_H
#define HASH_H

// Hash macros

#define DEF_HASH_FN_SIZED(RET_TYPE)                                   \
  RET_TYPE hash_##RET_TYPE##_sized(void *p_key, size_t len) {                              \
    RET_TYPE hash = 0;                                                         \
    for (unsigned i = 0; i < len; ++i) {                                   \
      unsigned char byte = ((unsigned char *)p_key)[i];                        \
      hash = (hash << 5) + byte;                                               \
    }                                                                          \
    return hash;                                                               \
  }

#define DEF_HASH_FN_HEAP(RET_TYPE, KEY_TYPE)                                   \
  RET_TYPE hash_##RET_TYPE##_##KEY_TYPE(void *p_key) {                         \
    RET_TYPE hash = 0;                                                         \
    for (unsigned i = 0; i < sizeof(KEY_TYPE); ++i) {                          \
      unsigned char byte = ((unsigned char *)p_key)[i];                        \
      hash = (hash << 5) + byte;                                               \
    }                                                                          \
    return hash;                                                               \
  }

#define DEF_HASH_FN_STACK(RET_TYPE, KEY_TYPE)                                  \
  RET_TYPE hash_##RET_TYPE##_##KEY_TYPE(KEY_TYPE key) {                        \
    KEY_TYPE *p_key = &key;                                                    \
    RET_TYPE hash = 0;                                                         \
    for (unsigned i = 0; i < sizeof(KEY_TYPE); ++i) {                          \
      unsigned char byte = ((unsigned char *)p_key)[i];                        \
      hash = (hash << 5) + byte;                                               \
    }                                                                          \
    return hash;                                                               \
  }

#define DEF_HASH_FN_DYNAMIC(RET_TYPE)                                          \
  RET_TYPE hash_##RET_TYPE(void *p_key, size_t key_len) {                      \
    RET_TYPE hash = 0;                                                         \
    for (unsigned i = 0; i < key_len; ++i) {                                   \
      unsigned char byte = ((unsigned char *)p_key)[i];                        \
      hash = (hash << 5) + byte;                                               \
    }                                                                          \
    return hash;                                                               \
  }

#define DEF_HASH_FN_NULLTERM(RET_TYPE)                                         \
  RET_TYPE hash_##RET_TYPE##_nullterm(const char *key) {                       \
    RET_TYPE hash = 0;                                                         \
    while (*key) {                                                             \
      hash = (hash << 5) + *key++;                                             \
    }                                                                          \
    return hash;                                                               \
  }

#endif