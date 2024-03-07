#include <ArxContainer.h>

void flashTxt(char* txt, int flashes = 2, int interval = 200, int x = 0, int y = 0);

void writeKana(char txt[]);

extern std::map<String, char> kana; // i dont know if this is right but it shuts up the compiler