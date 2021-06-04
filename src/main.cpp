#include <Arduino.h>
#include "GyverButton.h"
#include "ds_ledstrip.h"

Ledstrip<2, 27, GRB, 27> *buttons_ledstrip;
enum MODE {
  LIGHTTEMP,
  SINGLE_COLOR,
  RAINBOW
} mode;
bool isOn = true;
html_color_t lights[9] =  {
  html_color_t{255, 80, 0},
  html_color_t{255, 100, 0},
  html_color_t{255, 120, 0},
  html_color_t{255, 150, 0},
  html_color_t{255, 150, 20},
  html_color_t{255, 200, 40},
  html_color_t{255, 255, 80},
  html_color_t{255, 255, 255},
  html_color_t{100, 255, 255} };
uint8_t current_light = 8;
uint8_t brightnesses[9]= {10, 20, 33, 45, 60, 75,80, 100};
uint8_t current_brightness = 3;
GButton butt1(3);
void setup() {
  mode = LIGHTTEMP;
  buttons_ledstrip = new Ledstrip<2,27,GRB,27>();
  Serial.begin(115200);  
}

void loop() {
   butt1.tick();
  if (butt1.isSingle()){
    switch (mode)
    {
    case LIGHTTEMP:
      current_brightness++;
      if (current_brightness==8){
        current_brightness=0;
      }
      Serial.println(current_brightness);
      if (current_brightness == 7){
        for (size_t i = 0; i < 2; i++)
        {
        delay(100);
        buttons_ledstrip->clear();
        delay(100);
        buttons_ledstrip->set(lights[current_light]);
        }
        
      }
      buttons_ledstrip->set_brightness(brightnesses[current_brightness]);

      buttons_ledstrip->show();
      break;
        case SINGLE_COLOR:
      /* code */
      break;
        case RAINBOW:
      /* code */
      break;
    
    default:
      break;
    }
    
  }
  if (butt1.isDouble()){
        switch (mode)
    {
    case LIGHTTEMP:
            current_light++;
      if (current_light==9){
        current_light=0;
      }
      buttons_ledstrip->set(lights[current_light]);
      buttons_ledstrip->show();
      break;
        case SINGLE_COLOR:
      /* code */
      break;
        case RAINBOW:
      /* code */
      break;
    
    default:
      break;
    }
  }
  if (butt1.isTriple()){
        switch (mode)
    {
    case LIGHTTEMP:
      mode++;
      break;
        case SINGLE_COLOR:
      mode++;
      break;
        case RAINBOW:
      mode=0;
      break;
    
    default:
      break;
    }
  }
  if (butt1.isHolded()){
        switch (mode)
    {
    case LIGHTTEMP:
      if (isOn){
        buttons_ledstrip->clear();
        isOn = false;
      }
      else{
        buttons_ledstrip->set(lights[current_light]);
        isOn = true;
      }
      break;
        case SINGLE_COLOR:
      /* code */
      break;
        case RAINBOW:
      /* code */
      break;
    
    default:
      break;
    }
  }
}
