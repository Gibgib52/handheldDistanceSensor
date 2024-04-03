#include <ArxContainer.h>
#include <string.h>

void flashTxt(char* txt, int flashes = 2, int interval = 200, int x = 0, int y = 0);

void writeKana(String str);

extern std::map<String, int, 64> kana;

extern std::map<String, int, 64> dakutenKana;

extern std::map<String, int, 64> spec;

void buzzUp(bool force = false);
void buzzDown(bool force = false);
void buzzSuccess(bool force = false);
void buzzFault(bool force = false);
void buzzHiLo(bool force = false);
void buzzArp(bool force = false);
void buzzS(bool force = false);
void buzzL(bool force = false);

void typeText(String txt, int cpm = 100);