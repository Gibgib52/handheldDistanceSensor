void setupM();
void alarmLoop();
void flashTxt();
//////////////


void menuAlarm();
void menuMain(); // ^^ left | VV right | <- order of menus
void menuSettings();
void menuSettings2();
void menuSettings3();
void menuHelp();
void menuTest();


/*
// template for menu structure
void menuTemplate(){
  while(true) {
    lcd.clear();
    lcd.setCursor(15,0);
    lcd.print("?"); // replace this with 1 char to describe menu
    lcd.setCursor(0,0);

    int in = waitForInput();
    if(in == LEFT){
      ;
    } else if(in == RIGHT){
      ;
    } else if(in == UP){
      ;
    } else if(in == DOWN){

    } else if (in == BTN){
      ;
    } else{
      ;
    }
    delay(UI_DELAY);
  }
}
*/