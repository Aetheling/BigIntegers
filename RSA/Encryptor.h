#pragma once
class IEncrypt
{
public: // functions
	// Sets nPadding the number of BYTEs used to pad out the message -- if the message is not a multiple of the chunk
	// size, extra BYTEs added to round things off.  Because we want the decryption to include any leading 0s
	// if the original message has them
	// If pEncryptedMessage is NULL, allocate it using malloc; otherwise, assume it is big enough
	// Returns false if an error detected during encryption; true otherwise
	virtual bool Encrypt(const char *pMessage, size_t nMessageLength, char *&pEncryptedMessage, size_t &nEncryptedMessageLength, size_t &nPadding)=0;
	// returns how much space is needed for the encrypted message, assuming the caller wants to allocate it
	virtual size_t SpaceNeededForEncryptedMessage(size_t nMessageLength)=0;
};

class IDecrypt
{
public: // functions
	// nPaddingBYTEs: if the original message was not a multiple of the chunk size, padding BYTEs added.
	// Ignore these in decrypting
	// If pDecryptedMessage is NULL, allocate it using malloc; otherwise, assume it is big enough
	// Returns false if a corruption in the encrypted message is detected or an error occurred during decryption, true otherwise
	virtual bool Decrypt(const char *pMessage, size_t nEncryptedMessageLength, size_t nPaddingBYTEs, char *&pDecryptedMessage, size_t &nMessageLength)=0;
	// returns how much space is needed for the decrypted message, assuming the caller wants to allocate it
	virtual size_t SpaceNeededForDecryptedMessage(size_t nEncryptedMessageLength)=0;
};