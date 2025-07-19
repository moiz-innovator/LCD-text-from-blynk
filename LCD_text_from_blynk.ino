#define BLYNK_TEMPLATE_ID "TMPL3ZTNUXru4"
#define BLYNK_TEMPLATE_NAME "lcd text"
#define BLYNK_AUTH_TOKEN "ZdgynbCfxVW58NicwFV2V-uIaf6lfULC"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <LiquidCrystal_I2C.h>

// WiFi credentials
char ssid[] = "yourwifiname";
char pass[] = "ourwifipassword";

// LCD setup
LiquidCrystal_I2C lcd(0x20, 16, 2);  // Your working address

BlynkTimer timer;

// Blynk text input handler
BLYNK_WRITE(V0) {
  String text = param.asString();
  Serial.println("✅ Text received from Blynk: " + text);
  lcd.clear();

  if (text.length() <= 16) {
    lcd.setCursor(0, 0);
    lcd.print(text);
  } else {
    lcd.setCursor(0, 0);
    lcd.print(text.substring(0, 16));
    lcd.setCursor(0, 1);
    lcd.print(text.substring(16, 32));
  }
}

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Connecting to");
  lcd.setCursor(0, 1);
  lcd.print("WiFi...");
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, pass);
  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ WiFi connected!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Connected");
    lcd.setCursor(0, 1);
    lcd.print(WiFi.localIP());
  } else {
    Serial.println("\n❌ WiFi failed!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("WiFi Failed!");
    return;
  }

  // Connect to Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Blynk Connected");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Send Text via");
  lcd.setCursor(0, 1);
  lcd.print("Blynk V0");
}

void loop() {
  Blynk.run();
  timer.run();
}
