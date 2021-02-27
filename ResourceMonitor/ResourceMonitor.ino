/*
  Resource Monitor
  Monitoring CPU and RAM usage and demonstrating it with 9 LEDs (for each CPU and RAM)
  1 push button demonstrates ALT+F4 buttons to shutdown application

  created 25 Feb 2021
  by Mehmet Suat Morkan
*/

float cpu = 0;
float ram = 0;

#define BUTTON_PIN    A5

#define NUMBER_OF_LEDS      9   // CPU ve RAM için ayrı ayrı 9 LED'imiz bulunuyor
uint8_t cpu_leds[9] = {2, 3, 4, 5, 6, 7, 8, 9, 10};   // CPU için LED'ler
uint8_t ram_leds[9] = {11, 12, 13, A0, A1, A2, A3, A4, 0};   // RAM için LED'ler

uint8_t key_pressed = 0;
uint8_t button_pressed = 0;
uint8_t button_pressed_counter = 0;

#include "Keyboard.h"

void setup() {
  Serial.begin(9600);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);              // BUTON pini input pullup tanımlıyoruz
  
  for (int k = 0; k < sizeof(cpu_leds); k++) {    // LED pinlerini OUTPUT yapıyoruz ve HIGH'da bırakıyoruz
    pinMode(cpu_leds[k], OUTPUT);
    digitalWrite(cpu_leds[k], HIGH);
  }

  for (int d = 0; d < sizeof(ram_leds) - 1; d++) {    // LED pinlerini OUTPUT yapıyoruz ve HIGH'da bırakıyoruz
    pinMode(ram_leds[d], OUTPUT);
    digitalWrite(ram_leds[d], HIGH);
  }
  
  Keyboard.begin();
}

void turnOnLEDsUntil(uint8_t pin_array[], uint8_t led_count) {
  for (int i = 0; i < NUMBER_OF_LEDS; i++) {
    if (i < led_count) {
      digitalWrite(pin_array[i], LOW);
    } else {
      digitalWrite(pin_array[i], HIGH);
    }
  }
}

void loop() {
  delay(10);
  if (digitalRead(BUTTON_PIN) == LOW) {
    button_pressed_counter++;     // button basılıysa basılı counter'ımızı artırıyoruz
  } else {
    button_pressed_counter = 0;
    button_pressed = 0;
  }

  if (button_pressed_counter >= 6 && button_pressed == 0) {   // en az 60 ms tusa basılmalı
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_F4);
    button_pressed = 1;    // Her basışta yalnızca bir tane program kapatması için basılı durumu hafızaya alıyoruz
    key_pressed = 1; // Klavyeye "basılı" komutu gönderildi
  } else if (key_pressed == 1) {
    Keyboard.release(KEY_LEFT_ALT);
    Keyboard.release(KEY_F4);
    key_pressed = 0; // Klavyeye "bırakılı" komutu gönderildi
  }

  while (Serial.available() > 0) {

    // Pyhton kodunda seri kanaldan gelecek olan veriyi aralarında virgül olacak şekilde ayarlamıştık
    // parseFloat() fonksiyonu virgülle ayrılmış olan verileri uygun şekilde alıp float tipinde bir değişkene atayabiliyor
    cpu = Serial.parseFloat(); // ilk float sayımız olan CPU kullanımı değerini okuyoruz
    ram = Serial.parseFloat(); // ikinci float sayımız olan RAM kullanımı değerini okuyoruz

    // Satır sonu değerimiz de geldikten sonra aldığımız verileri değerlendirebiliriz
    if (Serial.read() == '\n') {
      ///// CPU KULLANIMINA GORE LED DURUMLARI  /////
      if (cpu > 90) {
        turnOnLEDsUntil(&cpu_leds[0], 9);
      } else if (cpu > 80) {
        turnOnLEDsUntil(&cpu_leds[0], 8);
      } else if (cpu > 70) {
        turnOnLEDsUntil(&cpu_leds[0], 7);
      } else if (cpu > 60) {
        turnOnLEDsUntil(&cpu_leds[0], 6);
      } else if (cpu > 50) {
        turnOnLEDsUntil(&cpu_leds[0], 5);
      } else if (cpu > 40) {
        turnOnLEDsUntil(&cpu_leds[0], 4);
      } else if (cpu > 30) {
        turnOnLEDsUntil(&cpu_leds[0], 3);
      } else if (cpu > 20) {
        turnOnLEDsUntil(&cpu_leds[0], 2);
      } else if (cpu > 10) {
        turnOnLEDsUntil(&cpu_leds[0], 1);
      } else {
        turnOnLEDsUntil(&cpu_leds[0], 0);
      }

      ///// RAM KULLANIMINA GORE LED DURUMLARI  /////
      if (ram > 90) {
        turnOnLEDsUntil(&ram_leds[0], 8);
      } else if (ram > 80) {
        turnOnLEDsUntil(&ram_leds[0], 7);
      } else if (ram > 70) {
        turnOnLEDsUntil(&ram_leds[0], 6);
      } else if (ram > 60) {
        turnOnLEDsUntil(&ram_leds[0], 5);
      } else if (ram > 50) {
        turnOnLEDsUntil(&ram_leds[0], 4);
      } else if (ram > 40) {
        turnOnLEDsUntil(&ram_leds[0], 3);
      } else if (ram > 30) {
        turnOnLEDsUntil(&ram_leds[0], 2);
      } else if (ram > 20) {
        turnOnLEDsUntil(&ram_leds[0], 1);
      } else {
        turnOnLEDsUntil(&ram_leds[0], 0);
      }
      
    }
  }
}
