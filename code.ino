// For any problem this project you can open this tutoral link and if you need create custom android then contact in 
// whatsapp +917052722734 
// Tutorial Link : -  https://youtu.be/jTrhsKsmiWg?si=UHpGQEqj8wvHOx7i
// YouTube Channel Name : - Yarana Iot Guru!

#include <BluetoothSerial.h>
#include <AceButton.h>
using namespace ace_button;

BluetoothSerial SerialBT;

#define RelayPin1 2  
#define RelayPin2 4
#define RelayPin3 5 
#define RelayPin4 15  

#define SwitchPin1 16
#define SwitchPin2 17  
#define SwitchPin3 13  
#define SwitchPin4 12  

int toggleState_1 = 1;
int toggleState_2 = 1;
int toggleState_3 = 1;
int toggleState_4 = 1;

char bt_data;

ButtonConfig config1;
AceButton button1(&config1);
ButtonConfig config2;
AceButton button2(&config2);
ButtonConfig config3;
AceButton button3(&config3);
ButtonConfig config4;
AceButton button4(&config4);

void handleEvent1(AceButton*, uint8_t, uint8_t);
void handleEvent2(AceButton*, uint8_t, uint8_t);
void handleEvent3(AceButton*, uint8_t, uint8_t);
void handleEvent4(AceButton*, uint8_t, uint8_t);

void all_Switch_ON(){
  digitalWrite(RelayPin1, LOW); toggleState_1 = 0; delay(100);
  digitalWrite(RelayPin2, LOW); toggleState_2 = 0; delay(100);
  digitalWrite(RelayPin3, LOW); toggleState_3 = 0; delay(100);
  digitalWrite(RelayPin4, LOW); toggleState_4 = 0; delay(100);
}

void all_Switch_OFF(){
  digitalWrite(RelayPin1, HIGH); toggleState_1 = 1; delay(100);
  digitalWrite(RelayPin2, HIGH); toggleState_2 = 1; delay(100);
  digitalWrite(RelayPin3, HIGH); toggleState_3 = 1; delay(100);
  digitalWrite(RelayPin4, HIGH); toggleState_4 = 1; delay(100);
}

void Bluetooth_handle()
{
  bt_data = SerialBT.read();
  delay(20);

  switch(bt_data)
      {
        case '1': digitalWrite(RelayPin1, LOW);  toggleState_1 = 0; break;
        case '0': digitalWrite(RelayPin1, HIGH); toggleState_1 = 1; break;
        case '2': digitalWrite(RelayPin2, LOW);  toggleState_2 = 0; break;
        case '3': digitalWrite(RelayPin2, HIGH); toggleState_2 = 1; break;
        case '4': digitalWrite(RelayPin3, LOW);  toggleState_3 = 0; break;
        case '5': digitalWrite(RelayPin3, HIGH); toggleState_3 = 1; break;
        case '6': digitalWrite(RelayPin4, LOW);  toggleState_4 = 0; break;
        case '7': digitalWrite(RelayPin4, HIGH); toggleState_4 = 1; break;
        case 'A': all_Switch_ON(); break;
        case 'B': all_Switch_OFF(); break;
        default : break;
      }

  // Print received Bluetooth data to serial monitor
  Serial.println(bt_data);
}

void setup()
{
  Serial.begin(9600);
  btStart();  
  SerialBT.begin("Yarana Smart Home"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  delay(5000);

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  digitalWrite(RelayPin1, toggleState_1);
  digitalWrite(RelayPin2, toggleState_2);
  digitalWrite(RelayPin3, toggleState_3);
  digitalWrite(RelayPin4, toggleState_4);
 
  config1.setEventHandler(button1Handler);
  config2.setEventHandler(button2Handler);
  config3.setEventHandler(button3Handler);
  config4.setEventHandler(button4Handler);

  button1.init(SwitchPin1);
  button2.init(SwitchPin2);
  button3.init(SwitchPin3);
  button4.init(SwitchPin4);
}

void loop()
{  
  if (SerialBT.available()){
   Bluetooth_handle();
 }

  button1.check();
  button2.check();
  button3.check();
  button4.check();

  // Serial monitor se kuch likhkar enter press karne par yeh data Bluetooth ke through bhej dega
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n'); // Data ko string mein padhein
    SerialBT.println(data); // Bluetooth ke through data bhejein
  }
}

void button1Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_1 = 0;
      digitalWrite(RelayPin1, LOW);
      SerialBT.println("0");
      break;
    case AceButton::kEventReleased:
      toggleState_1 = 1;
      digitalWrite(RelayPin1, HIGH);
      SerialBT.println("1");
      break;
  }
}

void button2Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_2 = 0;
      digitalWrite(RelayPin2, LOW);
      SerialBT.println("2");
      break;
    case AceButton::kEventReleased:
      toggleState_2 = 1;
      digitalWrite(RelayPin2, HIGH);
      SerialBT.println("3");
      break;
  }
}

void button3Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_3 = 0;
      digitalWrite(RelayPin3, LOW);
      SerialBT.println("4");
      break;
    case AceButton::kEventReleased:
      toggleState_3 = 1;
      digitalWrite(RelayPin3, HIGH);
      SerialBT.println("5");
      break;
  }
}

void button4Handler(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      toggleState_4 = 0;
      digitalWrite(RelayPin4, LOW);
      SerialBT.println("6");
      break;
    case AceButton::kEventReleased:
      toggleState_4 = 1;
      digitalWrite(RelayPin4, HIGH);
      SerialBT.println("7");
      break;
  }
}
