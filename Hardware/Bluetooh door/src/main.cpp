#include <Arduino.h>
#include "mbedtls/aes.h"

#define IV_SIZE     16
#define INPUT_SIZE  256

// Random Number peripheral included on ESP32
//http://www.lucadentella.it/en/2017/02/10/esp32-10-generatore-numeri-random/
#define DR_REG_RNG_BASE 0x3ff75144


std::string get_random_string( size_t length )
{
    auto randchar = []() -> char
    {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        uint32_t randomNumber = READ_PERI_REG(DR_REG_RNG_BASE);
        const size_t max_index = (sizeof(charset) - 1);
        return charset[ randomNumber % max_index ];
    };
    std::string str(length,0);
    std::generate_n( str.begin(), length, randchar );
    return str;
}

std::string encrypt_message(std::string random_message) {
  mbedtls_aes_context aes;

  //Defining our key and translating it into char array
  std::string key_string = "4To4jyTAOMvf99fx";
  char key[key_string.size()+1];
  strcpy(key, key_string.c_str());

  char input[random_message.size()+1];
  // std::string random_message = "Vamu ver se isso worka";
  // char input[TXT_VALID_LENGTH];
  strcpy(input, random_message.c_str());

  unsigned char iv[IV_SIZE] = {0};

  unsigned char output[INPUT_SIZE] = {0};

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  int TXT_VALID_LENGTH = ((strlen((const char*)input)%16 == 0)  ?  strlen((const char*)input) :  (strlen((const char*)input)/16 + 1)*16);
  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, TXT_VALID_LENGTH, iv,(const unsigned char*)input, output);
  mbedtls_aes_free( &aes );


  Serial.print("Encrypted message: ");
  for (int i = 0; i < strlen((const char*) output); i++) {
    char str[3];

    sprintf(str, "%02x", (int)output[i]);
    Serial.print(str);
  }

  Serial.printf("\nkey: %s\n", key);
  Serial.printf("Message: %s\n", input);

  std::string output_string((char*)output);
  // for(int i = 0; i < strlen((const char*) output); i++) {
  //   output_string = output_string + (char)output[i];
  // }

  return output_string;
}

void setup() {
  Serial.begin(115200);

  std::string random_string = get_random_string(32);
  std::string encrypeted_string = encrypt_message(random_string);
}

void loop() {
  // put your main code here, to run repeatedly:
}
