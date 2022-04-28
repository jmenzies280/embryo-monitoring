#include <Adafruit_NeoPixel.h>
#include <SerialCommand.h>
// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN    9

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 12
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

SerialCommand sCmd;     // The demo SerialCommand object

float timeOff = 5;
float timeOn = 1;
int brightRed = 0;
int brightBlue = 0;
int brightWhite = 0;
int repetitions = 2;
int flag=1;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);

strip.begin();
strip.show(); // Initialize all pixels to 'off'

sCmd.addCommand("white",    white);
sCmd.addCommand("blueon",    blue_on);
sCmd.addCommand("blueoff",    blue_off);
sCmd.addCommand("on",    start);
sCmd.addCommand("config", config);
//sCmd.addCommand("time",    time);
sCmd.addCommand("HELLO", sayHello);        // Echos the string argument back
sCmd.addCommand("P",     processCommand);  // Converts two arguments to integers and echos them back
//sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")


}//end setup

void loop() {
  // put your main code here, to run repeatedly:
sCmd.readSerial();     // We don't do much, just process serial commands
if (flag==1){
Serial.println("string format: 'on timeOn timeOff brightness repetitions' ");
flag=0;
}



}//end loop

void white(){
  //int aNumber;
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) {
    brightWhite = atoi(arg);    // Converts a char string to an integer
  }
    Serial.print("White brightness: ");
    Serial.println(brightWhite);
    
    for (int i = 0; i <=  LED_COUNT; i=i+1){
      strip.setPixelColor(i, 0, brightRed, brightBlue,brightWhite);
      }//end for
    strip.show();
  
  
}


void blue_on(){
  //int aNumber;
  char *arg;
  arg = sCmd.next();
  if (arg != NULL) {
    brightBlue = atoi(arg);    // Converts a char string to an integer
  }
    Serial.print("blue brightness: ");
    Serial.println(brightBlue);
    
    for (int i = 0; i <=  LED_COUNT; i=i+1){
      strip.setPixelColor(i, 0, brightRed, brightBlue,0);
      }//end for
    strip.show();
  
  
}
void blue_off(){
      for (int i = 0; i <=  LED_COUNT; i=i+1){
      strip.setPixelColor(i, 0, brightRed, 0,0);
      }//end for
    strip.show();
  }
void start(){
int aNumber;
  //float timeOn;
  //float timeOff;
  //int brightRed;
  int repetitions;
  char *arg;

  Serial.println("load values:");
  
  arg = sCmd.next();
  if (arg != NULL) {
    timeOn = atof(arg);    // Converts a char string to an integer
    Serial.print("time on: ");
    Serial.println(timeOn);
  }
 
  
  arg = sCmd.next();
  if (arg != NULL) {
    timeOff = atof(arg);
    Serial.print("time off: ");
    Serial.println(timeOff);
  }
  
  arg = sCmd.next();
  if (arg != NULL) {
    brightRed = atoi(arg);
    if (brightRed>255){brightRed=255;}
    if (brightRed<0){brightRed=0;}
    Serial.print("brightness red: ");
    Serial.println(brightRed);
  }

  
  arg = sCmd.next();
  if (arg != NULL) {
    repetitions = atoi(arg);
    Serial.print("repetitions: ");
    Serial.println(repetitions);
  }

  Serial.println("starting in 1 second");
  delay(1000);

  for (int j = 0; j<repetitions; j=j+1){
    for (int i = 0; i <=  LED_COUNT; i=i+1){
      strip.setPixelColor(i, 0, brightRed, brightBlue,0);
      }//end for
    strip.show();
    delay(timeOn*1000);

    for(int i=0; i<= LED_COUNT; i=i+1){
      strip.setPixelColor(i, 0, 0, brightBlue,0);
      }//end for
    strip.show();
    delay(timeOff*1000);

  }//end j
brightRed=0;
}//end blink



// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("What?");
}

void sayHello() {

  char *arg;
  arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  if (arg != NULL) {    // As long as it existed, take it
    Serial.print("Hello ");
    Serial.println(arg);
  }
  else {
    Serial.println("Hello, whoever you are");
  }
}


void processCommand() {
  int aNumber;
  char *arg;

  Serial.println("We're in processCommand");
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);    // Converts a char string to an integer
    Serial.print("First argument was: ");
    Serial.println(aNumber);
  }
  else {
    Serial.println("No arguments");
  }

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atol(arg);
    Serial.print("Second argument was: ");
    Serial.println(aNumber);
  }
  else {
    Serial.println("No second argument");
  }
}//end process command

void config() {
  int aNumber;
  float timeOn;
  float timeOff;
  int bright;
  int repetitions;
  char *arg;

  Serial.println("configure protocol");
  Serial.println("time on in seconds");
  arg = sCmd.next();
  if (arg != NULL) {
    timeOn = atof(arg);    // Converts a char string to an integer
    //Serial.print("First argument was: ");
    //Serial.println(aNumber);
  }
  else {
    Serial.println("No arguments");
  }
  
  Serial.println("time off in seconds");
  arg = sCmd.next();
  if (arg != NULL) {
    timeOff = atof(arg);
    //Serial.print("Second argument was: ");
    //Serial.println(aNumber);
  }
  Serial.println("brightness (255 is max bright)");
  arg = sCmd.next();
  if (arg != NULL) {
    bright = atoi(arg);
    //Serial.print("Second argument was: ");
    //Serial.println(aNumber);
  }

  Serial.println("number of repetitions");
  arg = sCmd.next();
  if (arg != NULL) {
    repetitions = atoi(arg);
    //Serial.print("Second argument was: ");
    //Serial.println(aNumber);
  }
  else {
    Serial.println("No second argument");
  }
}//end process command
