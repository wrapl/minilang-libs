#include <minilang/ml_library.h>
#include <minilang/ml_macros.h>
#include <minilang/ml_object.h>
#include <minilang/ml_stream.h>
#include <nettle/nettle-meta.h>

#undef ML_CATEGORY
#define ML_CATEGORY "crypto/cipher"

typedef struct {
	ml_type_t *Type;
	nettle_cipher_func *encrypt;
	nettle_cipher_func *decrypt;
	size_t BlockSize;
	unsigned char Context[];
} cipher_t;

ML_TYPE(CipherT, (), "cipher");

static void cipher_constructor_fn(ml_state_t *Caller, void *Data, int Count, ml_value_t **Args) {
	const struct nettle_cipher *Info = Data;
	ML_CHECKX_ARG_COUNT(1);
	ML_CHECKX_ARG_TYPE(0, MLAddressT);
	if (ml_address_length(Args[0]) < Info->key_size) ML_ERROR("ValueError", "Key expects minimum of %d bytes", Info->key_size);
	cipher_t *Cipher = xnew(cipher_t, Info->context_size, unsigned char);
	Cipher->Type = stringmap_search(CipherT->Exports, Info->name);
	Cipher->encrypt = Info->encrypt;
	Cipher->decrypt = Info->decrypt;
	Cipher->BlockSize = Info->block_size ?: 1;
	Info->set_encrypt_key(Cipher->Context, (unsigned char *)ml_address_value(Args[0]));
	Info->set_decrypt_key(Cipher->Context, (unsigned char *)ml_address_value(Args[0]));
	ML_RETURN(Cipher);
}

ML_METHOD("encrypt", CipherT, MLBufferT, MLAddressT) {
	cipher_t *Cipher = (cipher_t *)Args[0];
	size_t Length = ml_buffer_length(Args[1]);
	if (Length != ml_address_length(Args[2])) return ml_error("ShapeError", "Buffer sizes do not match");
	if (Length % Cipher->BlockSize) return ml_error("ShapeError", "Buffer size is not a multiple of block size");
	Cipher->encrypt(Cipher->Context, Length, (unsigned char *)ml_buffer_value(Args[1]), (const unsigned char *)ml_address_value(Args[2]));
	return (ml_value_t *)Cipher;
}

ML_METHOD("decrypt", CipherT, MLBufferT, MLAddressT) {
	cipher_t *Cipher = (cipher_t *)Args[0];
	size_t Length = ml_buffer_length(Args[1]);
	if (Length != ml_address_length(Args[2])) return ml_error("ShapeError", "Buffer sizes do not match");
	if (Length % Cipher->BlockSize) return ml_error("ShapeError", "Buffer size is not a multiple of block size");
	Cipher->decrypt(Cipher->Context, Length, (unsigned char *)ml_buffer_value(Args[1]), (const unsigned char *)ml_address_value(Args[2]));
	return (ml_value_t *)Cipher;
}

typedef struct {
	ml_type_t *Type;
	ml_value_t *Stream;
	typeof(ml_stream_write) *write;
	nettle_cipher_func *crypt;
	const void *Context;
	unsigned char *Output;
	size_t InputUsed, OutputSize;
	unsigned char InitVector[];
} cipher_stream_t;

ML_TYPE(EncryptStreamT, (MLStreamT), "encrypt_stream");



ML_TYPE(DecryptStreamT, (MLStreamT), "decrypt_stream");



ML_LIBRARY_ENTRY0(crypto_cipher) {
#include "cipher_init.c"
	for (const struct nettle_cipher * const *Ptr = nettle_get_ciphers(); *Ptr; Ptr++) {
		const struct nettle_cipher *Info = *Ptr;
		const char *Name = GC_strdup(Info->name);
		ml_type_t *Type = ml_type(CipherT, Name);
		Type->Constructor = ml_cfunctionx((void *)Info, cipher_constructor_fn);
		stringmap_insert(CipherT->Exports, Name, Type);
	}
	Slot[0] = (ml_value_t *)CipherT;
}
