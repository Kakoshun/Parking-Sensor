#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);

float cm; //Δήλωση μεταβλητής για μέτρηση σε εκατοστά
float inches; //Δήλωση μεταβλητής για μέτρηση σε ίντσες
const int buzzerPin = 10; //Δήλωση pin για το Buzzer
const int trigPin = 9; //Δήλωση pin για το Trig
const int echoPin = 8; //Δήλωση pin για το Echo

void setup()
{

Serial.begin(9600);
pinMode(trigPin, OUTPUT); //Δήλωση ως έξοδος
pinMode(echoPin, INPUT); //Δήλωση ως είσοδος
  lcd.init(); //Αρχικοποίηση οθόνης, οι επόμενες σειρές είναι για να δείχνουν μόνιμα τα στοιχεία αυτά
  lcd.backlight();
  lcd.setCursor(1,0); //Δήλωση πρώτα αριθμού στήλης (1) και μετά της γραμμής (0)
  lcd.print("Mantzarh Stylianh"); //Κείμενο
	lcd.setCursor(5,1);
  lcd.print("Apostash se ");
  lcd.setCursor(9,2);
  lcd.print("inches");
  lcd.setCursor(4,2);
  lcd.print("cm");

}
void loop()
{

tone(buzzerPin, 0, 0);
long duration, cm; //Επανάληψη λειτουργίας του οργάνου, για την μέτρηση του μήκους
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH,30000);

if (duration==0)
{
pinMode(echoPin, OUTPUT);
delay(10);
digitalWrite(echoPin, LOW);
delay(10);
pinMode(echoPin, INPUT);
delay(10);
}

cm = microsecondsToCentimeters(duration); //Λήψη τιμής μέτρησης
inches = cm/2.54; //Μετατροπή τιμής μέτρησης σε ίντσες

  lcd.setCursor(4,3); //Ένδειξη στην οθόνη των μετρώσεων
  lcd.print(cm);
  lcd.setCursor(9,3);
  lcd.print(inches);
  tone(buzzerPin, 2000, 70); //Αρχικοποίηση του Buzzer και δήλωση των Hz (400) και για την διάρκεια του ήχου που θα βγάλει σε msec
  delay(cm*2); //Δήλωση χτυπήματος Buzzer με χρήση της μέτρησης απόστασης για την αλλαγή του ήχου σε συνεχόμενο όταν είναι μικρή η απόσταση
  
}

long microsecondsToCentimeters(long microseconds)
{
return microseconds / 58;
}
