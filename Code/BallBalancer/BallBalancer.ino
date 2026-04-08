#include <ESP32Servo.h>
#include <WiFi.h>

//Server
const int serverPort(80);
WiFiServer theServer(serverPort);

const char* theSSID { "Ball Balancer" };
const char* thePassword { "12345678" };

Servo servo_2;
Servo servo_4;
Servo servo_5;

int SERVO_2_PIN = 2;
int SERVO_4_PIN = 4;
int SERVO_5_PIN = 5;

int base_position_2 = 127;
int base_position_4 = 143;
int base_position_5 = 144;

int range_2 = 13;
int range_4 = 15;
int range_5 = 14;

int center_x = 340;
int center_y = 220;

int margin = 40;

int ball_x_min = 0;
int ball_x_max = 640;

int ball_y_min = 0;
int ball_y_max = 480;

// globals
float Kp = 1.2;
float Kd = 2.0;

float last_error_x = 0;
float last_error_y = 0;

float current_S2;
float current_S4;
float current_S5;

float smooth = 0.5; 


void setup() {
  WiFi.softAP(theSSID, thePassword);
  theServer.begin();
  WiFi.softAPIP();  
  // put your setup code here, to run once:
  servo_2.attach(SERVO_2_PIN);
  servo_4.attach(SERVO_4_PIN);
  servo_5.attach(SERVO_5_PIN);
  Serial.begin(9600);

  servo_2.write(base_position_2);
  servo_4.write(base_position_4);
  servo_5.write(base_position_5);

  current_S2 = base_position_2;
  current_S4 = base_position_4;
  current_S5 = base_position_5;
}

void loop() {
  
  delay(15);

  WiFiClient theClient = theServer.available();

  if (theClient) {
    Serial.println("Client connected");

    while (theClient.connected()) {
      while (theClient.available()) {
        String theReceived = theClient.readStringUntil('\n');
        theReceived.trim();

        int commaIndex = theReceived.indexOf(',');
        if (commaIndex != -1) {
          int x = theReceived.substring(0, commaIndex).toInt();
          int y = theReceived.substring(commaIndex + 1).toInt();

          Serial.print("x: ");
          Serial.println(x);
          Serial.print("y: ");
          Serial.println(y);

          find_position(x, y);
        }
      }

      delay(1);
    }

    theClient.stop();
    Serial.println("Client disconnected");
  }
  
}

float mapFloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void find_position(int x, int y){
  // --- X axis ---
  float error_x = center_x - x;
  float derivative_x = error_x - last_error_x;
  float output_x = Kp * error_x + Kd * derivative_x;
  last_error_x = error_x;

  // map PD output to servo DELTA, not absolute position
  float delta_x = mapFloat(output_x,-(ball_x_max - ball_x_min) / 2.0, (ball_x_max - ball_x_min) / 2.0,-range_2, range_2);

  delta_x = constrain(delta_x, -range_2, range_2);

  float target_S2 = base_position_2 + delta_x;
  float target_S4 = base_position_4 - delta_x;

  target_S2 = constrain(target_S2, base_position_2 - range_2, base_position_2 + range_2);
  target_S4 = constrain(target_S4, base_position_4 - range_4, base_position_4 + range_4);

  current_S2 = current_S2 + smooth * (target_S2 - current_S2);
  current_S4 = current_S4 + smooth * (target_S4 - current_S4);

  servo_2.write((int)current_S2);
  servo_4.write((int)current_S4);

  // --- Y axis ---
  float error_y = center_y - y;
  float derivative_y = error_y - last_error_y;
  float output_y = Kp * error_y + Kd * derivative_y;
  last_error_y = error_y;

  float delta_y = mapFloat(output_y,-(ball_y_max - ball_y_min) / 2.0, (ball_y_max - ball_y_min) / 2.0,-range_5, range_5);

  delta_y = constrain(delta_y, -range_5, range_5);

  float target_S5 = base_position_5 + delta_y;
  target_S5 = constrain(target_S5, base_position_5 - range_5, base_position_5 + range_5);

  current_S5 = current_S5 + smooth * (target_S5 - current_S5);

  servo_5.write((int)current_S5);
}