#ifndef COLORS_H
# define COLORS_H

struct Color {
  int ledPin;
  int buttonPin;
  int ledIntensity;
  int lastButtonState;
  int stableState;
  unsigned long lastDebounceTime;
};

#endif

