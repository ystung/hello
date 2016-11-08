#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>

#define BUFFER_SIZE 2621440
#define PAUSE printf("Press Enter key to continue..."); fgetc(stdin);

void handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}


int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
  unsigned char *iv, unsigned char *ciphertext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /* Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

int decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key,
  unsigned char *iv, unsigned char *plaintext)
{
  EVP_CIPHER_CTX *ctx;

  int len;

  int plaintext_len;

  /* Create and initialise the context */
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  /* Initialise the decryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits */
  if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))
    handleErrors();

  /* Provide the message to be decrypted, and obtain the plaintext output.
   * EVP_DecryptUpdate can be called multiple times if necessary
   */
  if(1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len))
    handleErrors();
  plaintext_len = len;

  /* Finalise the decryption. Further plaintext bytes may be written at
   * this stage.
   */
  if(1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) handleErrors();
  plaintext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return plaintext_len;
}



int main(int argc, char *argv[])
{
	FILE *fp,*copy;
	char *buf;
	size_t ret;
	int decryptedtext_len, ciphertext_len;
	
	if(argc!=2)
	{
		printf("直接把檔案拖曳到此程式。\n指令用法：此程式檔名稱 要複製的檔案名稱\n");
		PAUSE
		printf("system(\"pause\") for linux!\n");
	}
	else
	{
		printf("複製中...");
		fp=fopen(argc[argv-1],"rb");
		copy=fopen("./copy","wb");
		buf = (char *)malloc(BUFFER_SIZE); //動態配置記憶體給Array
		ret = fread(buf, 1, BUFFER_SIZE, fp); // fread回傳讀取的byte數
		while(ret > 0)
		{
			
			
			  /* Set up the key and iv. Do I need to say to not hard code these in a
			   * real application? :-)
			   */

			  /* A 256 bit key */
			  unsigned char *key = (unsigned char *)"01234567890123456789012345678901";

			  /* A 128 bit IV */
			  unsigned char *iv = (unsigned char *)"01234567890123456";
			  /* Buffer for ciphertext. Ensure the buffer is long enough for the
			   * ciphertext which may be longer than the plaintext, dependant on the
			   * algorithm and mode
			   */
			  unsigned char ciphertext[BUFFER_SIZE];
			  
			  /* Initialise the library */
			  ERR_load_crypto_strings();
			  OpenSSL_add_all_algorithms();
			  OPENSSL_config(NULL);
			  
			  /* Encrypt the plaintext */
			//	ciphertext_len = encrypt (buf, strlen ((char *)buf), key, iv,
             //               ciphertext);
			  
			fwrite(buf, 1, ret, copy);  
			//fwrite(ciphertext, 1, ret, copy);
			//printf("loop \n");
			ret = fread(buf, 1, BUFFER_SIZE, fp);
			
			/* Clean up */
			  EVP_cleanup();
			  ERR_free_strings();
		}
		free(buf);
		fclose(fp);
		fclose(copy);
	}
	return 0;
}