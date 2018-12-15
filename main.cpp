#include "aesTool.h"
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char *argv[])
{
    initKV("3434535%FRSssref","5%F434535%FRSssr");
	string sessid = encrypt("hello,world");
	
	cout << sessid << endl;
	string res = decrypt(sessid);
	cout << res << endl;
	
    return 0;
}
