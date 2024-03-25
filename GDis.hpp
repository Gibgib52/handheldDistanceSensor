#include <ArxContainer.h>
#include <string.h>

void flashTxt(char* txt, int flashes = 2, int interval = 200, int x = 0, int y = 0);

void writeKana(String str);

extern std::map<String, int, 64> kana;

extern std::map<String, int, 64> dakutenKana;

void buzzUp();
void buzzDown();
void buzzSuccess();
void buzzFault();
void buzzHiLo();
void buzzArp();
void buzzS();
void buzzL();