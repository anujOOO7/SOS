#include <Servo.h>

// declaration of objects for servo motors
// horizontal servo
Servo horizontalServo;
int horizontalAngle = 90;
int horizontalLimitHigh = 180;
int horizontalLimitLow = 0;

// vertical servo
Servo verticalServo;
int verticalAngle = 120;
int verticalLimitHigh = 180;
int verticalLimitLow = 60;

// LDR pin connections
int ldrTopRight = 0;
int ldrTopLeft = 1;
int ldrBottomRight = 2;
int ldrBottomLeft = 3;

void setup() {
  Serial.begin(9600);

  // Servo connections
  horizontalServo.attach(9);
  verticalServo.attach(10);

  // Move servos to initial position
  horizontalServo.write(90);
  verticalServo.write(90);
  delay(3000);
}

void loop() {
  int topRight = analogRead(ldrTopRight);
  int topLeft = analogRead(ldrTopLeft);
  int bottomRight = analogRead(ldrBottomRight);
  int bottomLeft = analogRead(ldrBottomLeft);

  int tolerance = 20;

  int averageTop = (topLeft + topRight) / 2;
  int averageBottom = (bottomLeft + bottomRight) / 2;
  int averageLeft = (topLeft + bottomLeft) / 2;
  int averageRight = (topRight + bottomRight) / 2;

  int verticalDifference = averageTop - averageBottom;
  int horizontalDifference = averageLeft - averageRight;

  // Send data to the serial monitor if desired
  Serial.print("topLeft= ");
  Serial.print(topLeft);
  Serial.print(" ");
  Serial.print("topRight= ");
  Serial.print(topRight);
  Serial.print(" ");
  Serial.print("bottomLeft= ");
  Serial.print(bottomLeft);
  Serial.print(" ");
  Serial.print("bottomRight= ");
  Serial.print(bottomRight);
  Serial.println("");

  // Check if the difference is within the tolerance, else change vertical angle
  if (-1 * tolerance > verticalDifference || verticalDifference > tolerance) {
    if (averageTop > averageBottom) {
      verticalAngle = --verticalAngle;
      if (verticalAngle > verticalLimitHigh) {
        verticalAngle = verticalLimitHigh;
      }
    } 
    else if (averageTop < averageBottom) {
      verticalAngle = ++verticalAngle;
      if (verticalAngle < verticalLimitLow) {
        verticalAngle = verticalLimitLow;
      }
    }
    verticalServo.write(verticalAngle);
  }

  // Check if the difference is within the tolerance, else change horizontal angle
  if (-1 * tolerance > horizontalDifference || horizontalDifference > tolerance) {
    if (averageLeft > averageRight) {
      horizontalAngle = --horizontalAngle;
      if (horizontalAngle < horizontalLimitLow) {
        horizontalAngle = horizontalLimitLow;
      }
    } 
    else if (averageLeft < averageRight) {
      horizontalAngle = ++horizontalAngle;
      if (horizontalAngle > horizontalLimitHigh) {
        horizontalAngle = horizontalLimitHigh;
      }
    }
    horizontalServo.write(horizontalAngle);
  }
  delay(20);
}

// #include <Servo.h>

// // Define the servo motor
// Servo myServo;

// void setup() {
//   // Attach the servo to pin 9
//   myServo.attach(10);
// }

// void loop() {
//   // Gradually increase speed by changing position in small steps
//   for (int pos = 0; pos <= 180; pos += 1) {
//     myServo.write(pos);
//     delay(15); // Adjust the delay for smoother motion
//   }

//   // Gradually decrease speed
//   for (int pos = 180; pos >= 0; pos -= 1) {
//     myServo.write(pos);
//     delay(15); // Adjust the delay for smoother motion
//   }
// }


