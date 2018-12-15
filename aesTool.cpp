#include "aesTool.h"

byte key[ CryptoPP::AES::DEFAULT_KEYLENGTH ], iv[ CryptoPP::AES::BLOCKSIZE];

uint64_t getNowMiliTime()
{
	timeval tv;
	memset(&tv, 0, sizeof(tv));

	if (0 != gettimeofday(&tv, NULL))
	{
		return 0;
	}

	uint64_t ullTime = (uint64_t)tv.tv_sec * (uint64_t)1000 + tv.tv_usec / 1000;
	return ullTime;
}


void initKV(const char *tmpIV, const char *tmpK)
{
	//char tmpK[] = "wweibaoxZ!Hcurfi";
	//char tmpIV[] = "zKmnzBvP%FRJ23lD";
	for (int j = 0; j < CryptoPP::AES::DEFAULT_KEYLENGTH; ++j)
	{
		key[j] = tmpK[j];
	}
	for (int i = 0; i < CryptoPP::AES::BLOCKSIZE; ++i)
	{
		iv[i] = tmpIV[i];
	}

}

string encrypt(string plainText)
{
	string cipherText;
	//
	CryptoPP::AES::Encryption aesEncryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption( aesEncryption, iv );
	CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink( cipherText ));
	stfEncryptor.Put( reinterpret_cast<const unsigned char*>( plainText.c_str() ), plainText.length());
	stfEncryptor.MessageEnd();
	string cipherTextHex;
	
	for( int i = 0; i < cipherText.size(); i++ )
	{
		char ch[3] = {0};
		sprintf(ch, "%02x", static_cast<byte>(cipherText[i]));
		cipherTextHex += ch;
	}
	return cipherTextHex;
}

string decrypt(string cipherTextHex)
{
	string cipherText;
	string decryptedText;
	int i = 0;
	while(true)
	{
		char c;
		int x;
		stringstream ss;
		ss<<hex<<cipherTextHex.substr(i, 2).c_str();
		ss>>x;
		c = (char)x;
		cipherText += c;
		if(i >= cipherTextHex.length() - 2)break;
		i += 2;
	}
	//
	CryptoPP::AES::Decryption aesDecryption(key, CryptoPP::AES::DEFAULT_KEYLENGTH);
	CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption( aesDecryption, iv );
	CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink( decryptedText ));
	stfDecryptor.Put( reinterpret_cast<const unsigned char*>( cipherText.c_str() ), cipherText.size());
	stfDecryptor.MessageEnd();
	return decryptedText;
}

