#include "RSAEncryptor.h"

// timing attacks irrelevant for encryptor -- the power is public!
CRSAEncrypt::CRSAEncrypt(CBigInteger &nPublicPower, CBigInteger &nModulus) : m_Box(nPublicPower, nModulus, false)
{
	BYTE *pFirstDigit = (BYTE *) (nModulus.GetValue() + nModulus.GetSize() - 1);
	int  i            = sizeof(DIGIT) - 1;
	m_nModulusBYTESize = nModulus.GetSize()*sizeof(DIGIT);
	// tweak the modulus size to its exact size in BYTEs.  Note the first digit is guaranteed to be nonzero,
	// so need not check against using index -1
	while(0 == pFirstDigit[i--]) m_nModulusBYTESize--;
}

size_t CRSAEncrypt::SpaceNeededForEncryptedMessage(size_t nMessageLength)
{
	// <number of chunks>*<size of each chunk> + <a little extra workspace>
	size_t nMessageSpace = ((nMessageLength + m_nModulusBYTESize - 2)/(m_nModulusBYTESize - 1))*m_nModulusBYTESize;
#ifdef _DEBUG
	// add a little extra space for buffer guard
	nMessageSpace++;
#endif
	return nMessageSpace;
}

bool CRSAEncrypt::Encrypt(const char *pMessage, size_t nMessageLength, char *&pEncryptedMessage, size_t &nEncryptedMessageLength, size_t &nPadding)
{
	CBigInteger nChunk, nEncrypted;
	size_t      nChunks, nChunkDigits, nFinalChunkBYTEs, i, nSize;
	const char  *pMessageChunk;
	char        *pEncryptedChunk;
	nChunks                 = (nMessageLength + m_nModulusBYTESize - 2)/(m_nModulusBYTESize - 1);
	nFinalChunkBYTEs        = nMessageLength - (nChunks - 1)*(m_nModulusBYTESize - 1);
	nPadding                = (m_nModulusBYTESize-1) - nFinalChunkBYTEs;
	nEncryptedMessageLength = nChunks*m_nModulusBYTESize;
	if (NULL == pEncryptedMessage)
	{
		// need to allocate it
#ifdef _DEBUG
		// add one extra character to allocation for buffer guard
		pEncryptedMessage = (char *) malloc(nEncryptedMessageLength+1);
#else
		pEncryptedMessage = (char *) malloc(nEncryptedMessageLength);
#endif
	}
	if(NULL == pEncryptedMessage) return false;
#ifdef _DEBUG
	// add buffer guard
	pEncryptedMessage[nEncryptedMessageLength] = 'X';
#endif
	pMessageChunk   = pMessage;
	pEncryptedChunk = pEncryptedMessage;
	nChunkDigits    = (m_nModulusBYTESize + sizeof(DIGIT) - 2)/sizeof(DIGIT);
	nChunk.Reserve(nChunkDigits);
	nChunk.GetValue()[nChunkDigits - 1] = 0;
	// Note: loop to nChunks-1 -- final chunk may be smaller than the rest
	for(i=0; i<nChunks-1; i++)
	{
		memcpy(nChunk.GetValue(), pMessageChunk, m_nModulusBYTESize - 1);
		nChunk.SetSize(nChunkDigits);
		nChunk.FixLeadingZeros(); // in case the data has leading 0s
		m_Box.Power(nChunk, nEncrypted);
		nSize = nEncrypted.GetSize()*sizeof(DIGIT);
		if(nSize<m_nModulusBYTESize)
		{
			// need to pad with 0s
			memcpy(pEncryptedChunk, nEncrypted.GetValue(), nSize);
			memset(pEncryptedChunk+nSize,0,m_nModulusBYTESize-nSize);
		}
		else
		{
			memcpy(pEncryptedChunk, nEncrypted.GetValue(), m_nModulusBYTESize);
		}
		pMessageChunk   += (m_nModulusBYTESize - 1);
		pEncryptedChunk += m_nModulusBYTESize;
	}
	// final chunk
	memcpy(nChunk.GetValue(), pMessageChunk, nFinalChunkBYTEs);
	for(i=nFinalChunkBYTEs; i<m_nModulusBYTESize-1; i++)
	{
	    ((char *) nChunk.GetValue())[i] = 0;
	}
	nChunk.SetSize(nChunkDigits);
	nChunk.FixLeadingZeros(); // in case the data has leading 0s
	m_Box.Power(nChunk, nEncrypted);
	nSize = nEncrypted.GetSize()*sizeof(DIGIT);
	if (nSize < m_nModulusBYTESize)
	{
		// need to pad with 0s
		memcpy(pEncryptedChunk, nEncrypted.GetValue(), nSize);
		memset(pEncryptedChunk + nSize, 0, m_nModulusBYTESize - nSize);
	}
	else
	{
		memcpy(pEncryptedChunk, nEncrypted.GetValue(), m_nModulusBYTESize);
	}
#ifdef _DEBUG
	// check buffer guard
	if('X' != pEncryptedMessage[nEncryptedMessageLength])
	{
		printf("Message buffer overrun in encryption\n");
	}
#endif
	return true;
}