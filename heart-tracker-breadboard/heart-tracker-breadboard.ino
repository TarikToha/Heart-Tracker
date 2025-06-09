#include <MAX30105.h>
#include <heartRate.h>
#include <Adafruit_SSD1306.h>
#define SIZE 20

MAX30105 particleSensor;
long delta, lastBeat = 0;
float beatsPerMinute = 0;

Adafruit_SSD1306 display(128, 64, &Wire, -1);
int rd_idx = -1, i, pos, scaled, pos1, scaled1;
long irValue, maxIR, minIR, data[SIZE];

void setup() {
  // Serial.begin(115200);

  particleSensor.begin(Wire, I2C_SPEED_FAST);
  particleSensor.setup();
  particleSensor.setPulseAmplitudeRed(0x0A);
  particleSensor.setPulseAmplitudeGreen(0);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(SSD1306_WHITE);
  display.display();

  for (i = 0; i < SIZE; i++) {
    data[i] = 50000;
  }
}

void loop() {
  // delay(100);
  sense();
  // testDisplay();

  if (rd_idx == SIZE - 1) {
    shiftArray();
  } else {
    rd_idx++;
  }

  data[rd_idx] = irValue;

  updateMinMax();

  drawRealTimePlot();
}

void sense() {
  irValue = particleSensor.getIR();
  if (irValue < 50000) {
    irValue = 50000;
  }

  // Serial.print("IR=");
  // Serial.print(irValue);
  // Serial.print(", BPM=");

  if (irValue > 50000 && checkForBeat(irValue) == true) {
    delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);
    // Serial.print("<beat detected>");
  }

  if (irValue == 50000) {
    beatsPerMinute = 0;
    // Serial.print("No finger?");
  } else {
    // Serial.print(beatsPerMinute);
  }

  // Serial.println();
}

void updateMinMax() {
  maxIR = data[0];
  minIR = data[0];
  for (i = 1; i < SIZE; i++) {
    if (maxIR < data[i]) {
      maxIR = data[i];
    } else if (minIR > data[i]) {
      minIR = data[i];
    }
  }
}

void shiftArray() {
  for (i = 0; i < SIZE - 1; i++) {
    data[i] = data[i + 1];
  }
}

void testDisplay() {
  display.clearDisplay();
  display.setCursor(0, 10);

  display.print("IR=");
  display.print(irValue);
  display.print(", BPM=");
  display.println(beatsPerMinute);

  display.display();
}

void drawRealTimePlot() {
  display.clearDisplay();

  drawVerticalLines();
  drawHorizontalLines();

  drawArray();

  display.display();
}

void drawVerticalLines() {
  for (i = 0; i < 20; i++) {
    pos = 10 + i * 6;
    if (i == 0 || i == 19) {
      display.drawLine(pos, 2, pos, 54, SSD1306_WHITE);
    } else {
      display.drawLine(pos, 52, pos, 54, SSD1306_WHITE);
    }
  }
  display.setCursor(53, 57);
  display.print("Time");
}

void drawHorizontalLines() {
  for (i = 0; i < 6; i++) {
    pos = 2 + i * 10;
    if (i == 0 || i == 5) {
      display.drawLine(8, pos, 124, pos, SSD1306_WHITE);
    } else {
      display.drawLine(8, pos, 10, pos, SSD1306_WHITE);
    }
  }
  display.setCursor(0, 20);
  display.print("I");
  display.setCursor(0, 30);
  display.print("R");
}

void drawArray() {
  for (i = 0; i < SIZE; i++) {
    if (data[i] == 0) {
      continue;
    }

    pos = 10 + i * 6;
    scaled = 52 - (data[i] * 1.0 - minIR) / (maxIR - minIR + 1) * 50;
    display.fillCircle(pos, scaled, 2, SSD1306_WHITE);

    if (i == SIZE - 1) {
      continue;
    }

    if (data[i + 1] == 0) {
      continue;
    }

    pos1 = pos + 6;
    scaled1 = 50 - (data[i + 1] * 1.0 - minIR) / (maxIR - minIR + 1) * 45;
    display.drawLine(pos, scaled, pos1, scaled1, SSD1306_WHITE);
  }
}