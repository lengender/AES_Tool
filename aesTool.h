#ifndef _AESTOOL_H_
#define _AESTOOL_H_

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <sys/time.h>
#include "aes.h"
#include "filters.h"
#include "modes.h"
using namespace std;
uint64_t getNowMiliTime();
void initKV(const char *tmpIV, const char *tmpK);
string encrypt(string plainText);
string decrypt(string cipherTextHex);

#endif
