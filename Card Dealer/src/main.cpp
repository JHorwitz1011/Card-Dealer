#include <Arduino.h>

#include <Encoder.h>
Encoder selector = Encoder(4, 3);

#include <LiquidCrystal.h>
LiquidCrystal display = LiquidCrystal(7, 8, 9, 10, 11, 12);

/* #include <AccelStepper.h>
AccelStepper motion = AccelStepper(4,5,6,7); */

//#include <Player.h>

bool button = true;
int count = 0;
double length = 98.0F;

void welcomeScreen()
{
  display.print("Hi, I'm DEAL-ia!");
  display.setCursor(0, 1);
  display.print("Press To Begin.");
  delay(100);
  while (digitalRead(2))
  { //not sure if digitalread can work as boolean value care
    if (!digitalRead(2))
    {
      break;
    }
  }
}
/**
 *  - adds players to the playerarray,
 * 
 *  - configures the position of each player at the table
 * 
 * COMING SOON
 */
void playerInit()
{
  delay(100);
}

void selectGame()
{
  display.clear();
  display.print("Cards per deal?");
  delay(1000);

  int oldPosition = -999;
  int pastmov = -2;
  int mov = -1;
  int amplifier = 50;

  while (digitalRead(2))
  {
    long newPosition = selector.read();
    if (newPosition != oldPosition)
    {
      oldPosition = newPosition;
      mov = (int)newPosition / amplifier;
      // Serial.println(oldPosition);
    }

    if (mov != pastmov)
    {
      pastmov = mov;
      display.clear();
      display.print("Cards per deal?");
      display.setCursor(0, 1);
      display.print(mov);
    }
  }
  count = mov;
  playerInit();
}

/**
 * - deals cards to specified players based on chosen gamemode
 * 
 * - will rely on global acceleration values of stepper
 */
void deal()
{
  Serial.println("dealing..");
  display.clear();
  display.print("Press to deal");

  while (digitalRead(2))
  {
    if (!digitalRead(2))
    {
      break;
    }
  }
  display.setCursor(0, 1);
  display.write("dealing...");
  for (int i = 0; i < count; i++)
  {
    digitalWrite(5, HIGH);
    delay(length);
    if (length < 114)
    {
      length += .4F;
      Serial.println(length);
    }
    digitalWrite(5, LOW);
    delay(500);
  }
}

void loop()
{
  deal();
  delay(1000);
}

void setup()
{

  //testing purposes only
  Serial.begin(9600);

  //initialize LCD
  display.begin(16, 2);

  //initialize Encoder
  pinMode(2, INPUT_PULLUP);

  //initialize stepper motor

  //iniialize flinger
  pinMode(5, OUTPUT);

  welcomeScreen();

  selectGame();

  playerInit();
  digitalWrite(5, HIGH);
  delay(45);
  digitalWrite(5, LOW);
}