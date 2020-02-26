#include <Arduino.h>
#include "mbedtls/aes.h"

#define IV_SIZE     16
#define INPUT_SIZE  256

// Random Number peripheral included on ESP32
//http://www.lucadentella.it/en/2017/02/10/esp32-10-generatore-numeri-random/
#define DR_REG_RNG_BASE 0x3ff75144

const std::string key_string = "4To4jyTAOMvf99fx";

// Function that generates a random string given a lenght
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

// Function that encrypt a string message
std::string encrypt(std::string random_message) {
  mbedtls_aes_context aes;

  //Translating our key into char array
  char key[key_string.size()+1];
  strcpy(key, key_string.c_str());

  char input[random_message.size()+1];
  strcpy(input, random_message.c_str());

  unsigned char iv[IV_SIZE] = {0};
  unsigned char output[INPUT_SIZE] = {0};

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_enc( &aes, (const unsigned char*) key, strlen(key) * 8 );
  int TXT_VALID_LENGTH = ((strlen((const char*)input)%16 == 0)  ?  strlen((const char*)input) :  (strlen((const char*)input)/16 + 1)*16);
  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_ENCRYPT, TXT_VALID_LENGTH, iv,(const unsigned char*)input, output);
  mbedtls_aes_free( &aes );

  std::string output_string((char*)output);

  return output_string;
}

std::string decrypt(std::string encrypeted_string){
   //Translating our key into char array
  char key[key_string.size()+1];
  strcpy(key, key_string.c_str());

  char input[encrypeted_string.size()+1];
  strcpy(input, encrypeted_string.c_str());

  unsigned char iv[IV_SIZE] = {0};
  unsigned char output[INPUT_SIZE] = {0};

  mbedtls_aes_context aes;

  mbedtls_aes_init( &aes );
  mbedtls_aes_setkey_dec( &aes, (const unsigned char*) key, strlen(key) * 8 );
  int TXT_VALID_LENGTH = ((strlen((const char*)input)%16 == 0)  ?  strlen((const char*)input) :  (strlen((const char*)input)/16 + 1)*16);
  mbedtls_aes_crypt_cbc(&aes, MBEDTLS_AES_DECRYPT, TXT_VALID_LENGTH, iv,(const unsigned char*)input, output);
  mbedtls_aes_free( &aes );

  std::string output_string((char*)output);
  return output_string;
}

void print_string(std::string message, std::string string_message) {
  char char_array1[message.size()+1];
  strcpy(char_array1, message.c_str());
  char char_array2[string_message.size()+1];
  strcpy(char_array2, string_message.c_str());

  Serial.printf("%s: %s\n", char_array1, char_array2);
}

void print_as_hex(std::string encrypeted_string) {
  Serial.print("Encrypted String as HEX: ");
  char char_array[encrypeted_string.size()+1];
  strcpy(char_array, encrypeted_string.c_str());
  for (int i = 0; i < strlen((const char*) char_array); i++) {
    char str[3];
    sprintf(str, "%02x", (int)char_array[i]);
    Serial.print(str);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  print_string("Key", key_string);
  std::string random_string = get_random_string(32);
  print_string("Random String", random_string);
  std::string encrypeted_string = encrypt(random_string);
  print_as_hex(encrypeted_string);
  std::string decrypted_string = decrypt(encrypeted_string);
  print_string("Decrypted String", decrypted_string);
}

void loop() {
  // put your main code here, to run repeatedly:
}
