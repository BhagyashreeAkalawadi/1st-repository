Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL_pq9oBWB"
#define BLYNK_TEMPLATE_NAME         "NodeMCU"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "PrimeNumber";
char pass[] = "PrimeNumber";

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
#include <Wire.h>
#include <Adafruit_BMP280.h>
#include <SparkFun_MAX30102.h>
#include <MPU6050.h>

Adafruit_BMP280 bmp;      // BMP280 object
MAX30105 particleSensor;  // MAX30102 object
MPU6050 mpu;              // MPU6050 object

void setup() {
  Serial.begin(115200);
  Wire.begin(D2, D1);  // SDA, SCL

  // Initialize BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
  } else {
    Serial.println("BMP280 OK");
  }

  // Initialize MAX30102
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) {
    Serial.println("MAX30102 not found!");
  } else {
    Serial.println("MAX30102 OK");
    particleSensor.setup(); // Default
  }

  // Initialize MPU6050
  if (mpu.begin() != 0) {
    Serial.println("MPU6050 not found!");
  } else {
    Serial.println("MPU6050 OK");
    mpu.calcOffsets();  // Optional calibration
  }
}

void loop() {
  // Read MPU6050
  mpu.update();
  float ax = mpu.getAccX();
  float ay = mpu.getAccY();
  float az = mpu.getAccZ();
  Serial.print("Accel: ");
  Serial.print(ax); Serial.print(", ");
  Serial.print(ay); Serial.print(", ");
  Serial.println(az);

  // Read BMP280
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100;  // hPa
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" *C, Pressure: "); Serial.print(pressure);
  Serial.println(" hPa");

  // Read MAX30102
  long irValue = particleSensor.getIR();  // IR value (used for SpO2/HR)
  Serial.print("IR: "); Serial.println(irValue);

  Serial.println("--------------------");
  delay(1000);
}