#include "test.h"

#include <stdlib.h>
#include <string.h>

#include <openssl/rand.h>

typedef struct webpush_aesgcm_encrypt_ok_test_s {
  const char* desc;
  const char* ciphertext;
  const char* senderPrivKey;
  const char* recvPubKey;
  const char* authSecret;
  const char* salt;
  const char* plaintext;
  size_t plaintextLen;
  size_t padLen;
  size_t maxCiphertextLen;
  size_t ciphertextLen;
  uint32_t rs;
} webpush_aesgcm_encrypt_ok_test_t;

static webpush_aesgcm_encrypt_ok_test_t webpush_aesgcm_encrypt_ok_tests[] = {
  {
    .desc = "Example from draft-ietf-webpush-encryption-04",
    .ciphertext = "\xea\x7a\x80\x41\x43\x04\xf2\x13\x6a\xc3\x92\x77\x92\x5f"
                  "\x1c\xa5\x55\x49\xca\x55\xca\x62\xa6\x4e\x7a\xc7\x99\x1b"
                  "\xc5\x2e\x78\xaa\x40",
    .senderPrivKey = "\x9c\x24\x9c\x7a\x4f\x90\xa4\x48\xe6\x38\xe9\x53\xfa"
                     "\xb4\x37\xf2\x76\x73\xbd\xd3\xe5\xa9\xad\x34\x67\x2d"
                     "\x22\xea\x6d\x8e\x26\xf6",
    .recvPubKey = "\x04\x21\x24\x06\x3c\xcb\xf1\x9d\xc2\xfa\x88\xb6\x43\xba"
                  "\x04\xe6\xdd\x8d\xa7\xea\x7b\xa2\xc8\xc6\x2e\x0f\x77\xa9"
                  "\x43\xf4\xc2\xfa\x91\x4f\x6d\x44\x11\x6c\x9f\xd1\xc4\x03"
                  "\x41\xc6\xa4\x40\xca\xb3\xe2\x14\x0a\x60\xe4\x37\x8a\x5d"
                  "\xa7\x35\x97\x2d\xe0\x78\x00\x51\x05",
    .authSecret =
      "\x47\x6f\x6f\x20\x67\x6f\x6f\x20\x67\x27\x20\x6a\x6f\x6f\x62\x21",
    .salt = "\x96\x78\x1a\xad\xbc\x8a\x7c\xca\x22\xf5\x9e\xf9\xc5\x85\xe6\x92",
    .plaintext = "I am the walrus",
    .plaintextLen = 15,
    .padLen = 0,
    .maxCiphertextLen = 33,
    .ciphertextLen = 33,
    .rs = 4096,
  },
  {
    .desc = "rs = 4, trailer",
    .ciphertext =
      "\xe8\x7d\x81\x05\x8d\x25\xd1\xdb\xfc\xf3\x1c\x5d\x52\xd4\x39\x51\xb4"
      "\x7c\x63\x07\x4d\x6d\xb3\xf0\xaf\x89\xe4\xb3\xae\x64\x3d\x00\xb5\xce"
      "\xda\x84\x4c\xf7\x9b\xce\xb7\xf9\x4e\xdc\x95\xa9\xf8\x78\x4d\xcf\xf0"
      "\xb7\xeb\xdc\x27\x7e\x9a\x17\xdb\xd4\x62\x78\xaa\x8d\x7e\xe9\x65\x24"
      "\x81\x22\xe8\x40\x81\x37\x4c\xab\xd0\x3d\xb8\x3b\x98\x39\xdb\x34\x28"
      "\x88\xf9\x68\x58\x35\x26\x58\x34\xbb\x11\xe6\xdb\x1e\xb0\x95\xcd\x17"
      "\x5e\x12\xc5\xf8\x3f\x1f\xb6\xed\x3a\x4a\x00\x2b\x05\x7c\x10\xeb\x97"
      "\x94\x16\x6a\xc6\x1d\xc0\x00\x74\xf8\xd0\x95\xbb\xb6\x7f\xa8\x18\x35"
      "\xac\x1b\xa7\x16\xc8\xde\x94\xda\x49\xfb\xdb\x0a\x74\xf6\xac\x68\x89"
      "\x7b\xb3\x8d\x3f\xba\x88\x7a\x8b\xc9\x44\xa4\xc9\xdd\x83\x61\x20\x8b"
      "\xc3\x82\x57\x65\xe6\xb8\xc7\x69\xd5\x4d\xa7\xa4\x6f\x26\xf0\x50\xd0"
      "\xad\xc9\x5a\x16\xde\xa1\xa7\x50\xb0\xf7\xcf\x4d\x3b\xf4\xf5\x1f\xad"
      "\x32\xaf\x7a\x0a\x4a\x6a\x4c\x33\x2b\xa8\x49\xe5\xcf\x78\xa3\xf7\x8b"
      "\x38\x98\xdc\x3a\x8c\x95\x3c\xde\xb1\xc9\x79\x9b\x0e\xb4\x6e\xad\x37"
      "\xe0\xfa\xf4\xba\xc2\xbe\xd6\x56\x58\xb4\x86\x1c\xf9\x42\xfd\x77\xf2"
      "\x36\x33\xc5\xe5\xa1\x2e\xe1\x3c\xba\xd7\x64\xa2\x1a\x92\x5c\x79\x47"
      "\xf1\xd3\x18\x34\x9a\x9d\x96\x10\x71\xb8\x74\xc6\xb0\xc1\x06\x66\x62"
      "\x34\x97\x27\x84\x36\xa9\x3c\xd1\xa9\xa4\xe0\x32\xa9\x64\x9f\x29\x7a"
      "\x4d\x8b\xa4\x59\x44\xf6\x3b\xdb\x0b\xce\x45\xce\x0d\x75\xd3\x7c\x24"
      "\xa0\x69\x0f\xa0\x96\x0d\x86\x6e\x99\x2d\x61\x63\x15\xba\x01\x3b\x80"
      "\xc6\xe3\xac\xfd\x97\x26\x07\x42\x4b\xec\x10\x88\x8d\xd5\x0a\x15\x13"
      "\x42\xf1\x5d\x48\x18\x36\xfd\xf3\x65\x8c\x86\xe8\x58\xac\xc0\xf2\x5f"
      "\x3f\xe0\xce\xe5\xc2\x29\x5f\x04\x4e\x1e\x82\x89\xbc\x52\x50\x9d\x4f"
      "\x5c\x4e\xb5\x56\x5d\x4e\x62\x0a\xe5\x9c\xdb\x26\xa5\x02\x09\x63\xfc"
      "\x6e\x43\xca\x0e\x7c\x45\x29\xb3\x22\x38\xfd\x3a\xf6\x0e\xda\xf6\xc5"
      "\x6c\x9f\xb4\x08\x95\xb1\xe6\x01\x4a\xd7\x3b\x69\xb3\xcb\x55\x2c\xe8"
      "\xc0\xa8\xbb\x14\xff\xe9\x66\xc7\x4d\x40\xfc\x28\xd2\x05\xab\xee\x5f"
      "\x73\xed\x9a\x0d\xb9\x64\xe0\x69\xe4\x86\xb3\x02\xef\x58\xcc\xf6\xa3"
      "\x4b\x4e",
    .senderPrivKey = "\xf1\xfe\xd7\x17\xb0\xd8\x35\xd2\x9b\x9e\x4e\x4f\x4c"
                     "\xf8\x7d\x0c\xb9\x85\xe2\xbc\x44\xff\xd6\xd4\x37\xa4"
                     "\xe7\x4a\x18\x04\x55\x87",
    .recvPubKey = "\x04\x09\x22\xf1\x7c\xed\x7d\x09\xd4\x55\x10\x2d\xd9\x0c"
                  "\x31\x46\xce\x33\x2f\x45\xd2\x34\x96\x46\xfe\x64\xca\xbb"
                  "\x7f\x41\x23\x03\xbe\x5c\x23\x53\x9a\xff\x5c\x30\x72\xdd"
                  "\x85\xa9\x0b\x76\x92\xe1\x96\x22\x09\x39\xee\xb7\x3e\x0e"
                  "\xf2\x47\x59\x32\xb1\xcd\xa9\x16\xc7",
    .authSecret =
      "\xd3\xf8\x22\xf4\x8c\x74\x74\x19\x5d\xa6\x4d\x78\x5f\x40\x8f\x26",
    .salt = "\x77\x10\x67\x4b\x1e\xcd\x0b\xf7\xa7\xd3\x25\x88\xea\xe9\x53\x9c",
    .plaintext = "I am the very model of a modern Major-General.",
    .plaintextLen = 46,
    .padLen = 0,
    .maxCiphertextLen = 478,
    .ciphertextLen = 478,
    .rs = 4,
  },
  {
    .desc = "rs = 6, pad = 4",
    .ciphertext = "\x54\x6d\x13\x0b\x1e\xf0\xc2\x3e\xff\x49\x87\xe5\xc6\x57\xf1"
                  "\x94\xb1\xb8\xad\x5a\xda\xb7\x02\x32\x3c\xf9\xc0\x7b\xd8\x28"
                  "\x20\x9e\x5d\xe7\x5e\x8b\xf6\x6a\xa5\xf8\xf6\x3b\x0a\x66\xd3"
                  "\x99\xeb\x8b\x98\x70\x6c\xfc\xa5\xa5\x3f\x8f\x50\x8c\x26\x56"
                  "\x5a\x34\xe4",
    .senderPrivKey = "\xe3\x31\x8e\xc3\x99\xa9\xc4\x71\x7a\xa9\x4b\xa4\xed\xb3"
                     "\xaa\x1d\x90\x96\x5c\xe7\x6a\x57\x6b\x52\xa0\x7c\x27\x44"
                     "\x0c\x6d\x9b\xd1",
    .recvPubKey = "\x04\xaa\xec\x79\x05\x22\xad\x2b\x70\x56\x05\x58\x99\xda\xa6"
                  "\x47\x7d\x55\xab\x3f\x16\x5d\x76\x00\x56\x19\xf3\xdf\xa9\x72"
                  "\x19\xf5\x59\x02\x5d\x09\xc0\x80\x83\x70\xc6\x06\x8a\x66\x51"
                  "\x81\xd4\x3d\x74\xac\x3d\x0a\xca\x28\x67\x5e\x81\x55\x9a\x20"
                  "\x4a\x6d\x44\xb5\x91",
    .authSecret =
      "\x54\x9d\xe2\xfd\x40\x52\xef\x4e\x05\x28\x45\x13\x3e\x37\x61\x3d",
    .salt = "\x3a\x4b\xd3\x72\x75\x09\x5d\x71\xc9\x81\xe0\x9c\xde\x0d\xa6\x2a",
    .plaintext = "Hello",
    .plaintextLen = 5,
    .padLen = 4,
    .maxCiphertextLen = 63,
    .ciphertextLen = 63,
    .rs = 6,
  },
};

void
test_webpush_aesgcm_encrypt_ok(void) {
  size_t tests = sizeof(webpush_aesgcm_encrypt_ok_tests) /
                 sizeof(webpush_aesgcm_encrypt_ok_test_t);
  for (size_t i = 0; i < tests; i++) {
    webpush_aesgcm_encrypt_ok_test_t t = webpush_aesgcm_encrypt_ok_tests[i];

    const void* senderPrivKey = t.senderPrivKey;
    const void* authSecret = t.authSecret;
    const void* salt = t.salt;
    const void* recvPubKey = t.recvPubKey;
    const void* plaintext = t.plaintext;

    size_t ciphertextLen =
      ece_aesgcm_ciphertext_max_length(t.rs, t.padLen, t.plaintextLen);
    ece_assert(ciphertextLen == t.maxCiphertextLen,
               "Got ciphertext max length %zu for `%s`; want %zu",
               ciphertextLen, t.desc, t.maxCiphertextLen);

    uint8_t* ciphertext = calloc(ciphertextLen, sizeof(uint8_t));

    int err = ece_webpush_aesgcm_encrypt_with_keys(
      senderPrivKey, ECE_WEBPUSH_PRIVATE_KEY_LENGTH, authSecret,
      ECE_WEBPUSH_AUTH_SECRET_LENGTH, salt, ECE_SALT_LENGTH, recvPubKey,
      ECE_WEBPUSH_PUBLIC_KEY_LENGTH, t.rs, t.padLen, plaintext, t.plaintextLen,
      ciphertext, &ciphertextLen);
    ece_assert(!err, "Got %d encrypting ciphertext for `%s`", err, t.desc);

    ece_assert(ciphertextLen == t.ciphertextLen,
               "Got actual ciphertext length %zu for `%s`; want %zu",
               ciphertextLen, t.desc, t.ciphertextLen);
    ece_assert(!memcmp(ciphertext, t.ciphertext, ciphertextLen),
               "Wrong ciphertext for `%s`", t.desc);

    free(ciphertext);
  }
}

void
test_webpush_aesgcm_encrypt_pad(void) {
  static const uint32_t maxRs = 128;

  const void* senderPrivKey = "\xac\xae\xc1\xc3\x7c\x30\x7c\xb9\x02\x8f\xbb\xd9"
                              "\xc7\xf3\xc6\x89\x26\x60\x08\x95\x9a\x5e\xd4\x03"
                              "\x42\x21\xb2\xda\x72\x01\x82\x8f";
  const void* authSecret =
    "\x44\x29\x81\x2d\x53\x5f\xbf\xdb\xea\xc8\x6d\xb7\x14\x5c\x6a\xf2";
  const void* salt =
    "\x45\x2b\xfb\xea\x8c\xc7\xa7\x57\x14\xd2\x03\xcf\xf1\x02\xe8\x76";
  const void* recvPubKey =
    "\x04\x2d\x78\x8d\x3e\x8e\x82\xf2\xd7\xea\xef\xbd\xe3\xa1\xbe\xde\xa2\x1f"
    "\x3b\xc9\x60\x33\x15\x73\x22\xa0\x9e\x14\x46\x55\xa3\xdf\x78\xfd\xca\xc8"
    "\x10\xe3\x02\x2a\xb5\x6a\x0e\xa9\xb8\xec\x06\x73\x8a\xce\x41\x1f\x49\x54"
    "\x7b\xc0\x0d\x1a\x1c\xde\x97\xce\x7b\xdd\x26";

  for (uint32_t rs = ECE_AESGCM_MIN_RS + 1; rs <= maxRs; rs++) {
    // Generate a random plaintext.
    size_t plaintextLen = (size_t)(rand() % (maxRs - 1) + 1);
    uint8_t* plaintext = calloc(plaintextLen, sizeof(uint8_t));
    int ok = RAND_bytes(plaintext, (int) plaintextLen);
    ece_assert(ok == 1, "Got %d generating plaintext for rs = %d", ok, rs);

    size_t maxPadLen = (rs - ECE_AESGCM_MIN_RS) * (plaintextLen + 1);

    // Encrypting with the maximum padding length should succeed.
    size_t ciphertextLen =
      ece_aesgcm_ciphertext_max_length(rs, maxPadLen, plaintextLen);
    uint8_t* ciphertext = calloc(ciphertextLen, sizeof(uint8_t));

    int err = ece_webpush_aesgcm_encrypt_with_keys(
      senderPrivKey, ECE_WEBPUSH_PRIVATE_KEY_LENGTH, authSecret,
      ECE_WEBPUSH_AUTH_SECRET_LENGTH, salt, ECE_SALT_LENGTH, recvPubKey,
      ECE_WEBPUSH_PUBLIC_KEY_LENGTH, rs, maxPadLen, plaintext, plaintextLen,
      ciphertext, &ciphertextLen);
    ece_assert(!err, "Got %d encrypting with rs = %d, padLen = %zu", err, rs,
               maxPadLen);

    // Adding more padding should fail.
    size_t badPadLen = maxPadLen + 1;
    ciphertextLen =
      ece_aesgcm_ciphertext_max_length(rs, badPadLen, plaintextLen);
    ciphertext = realloc(ciphertext, ciphertextLen);

    err = ece_webpush_aesgcm_encrypt_with_keys(
      senderPrivKey, ECE_WEBPUSH_PRIVATE_KEY_LENGTH, authSecret,
      ECE_WEBPUSH_AUTH_SECRET_LENGTH, salt, ECE_SALT_LENGTH, recvPubKey,
      ECE_WEBPUSH_PUBLIC_KEY_LENGTH, rs, badPadLen, plaintext, plaintextLen,
      ciphertext, &ciphertextLen);
    ece_assert(err == ECE_ERROR_ENCRYPT_PADDING,
               "Want error encrypting with rs = %d, padLen = %zu", rs,
               badPadLen);

    free(plaintext);
    free(ciphertext);
  }
}
