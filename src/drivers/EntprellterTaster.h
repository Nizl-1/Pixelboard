#ifndef ENTPRELLTER_TASTER_H
#define ENTPRELLTER_TASTER_H

#include <Arduino.h>

class EntprellterTaster {
  private:
    int pin;
    bool entprellterZustand;
    unsigned long letzteAenderung;
    unsigned long druckBeginn;
    bool gedruecktGemeldet;
    static const unsigned long entprellZeit = 50; // 50 ms Entprellzeit
    static const unsigned long langeDruckZeit = 1000; // 1 Sekunde für langen Druck

  public:
    EntprellterTaster(int tasterPin)
      : pin(tasterPin), entprellterZustand(false), letzteAenderung(0), druckBeginn(0), gedruecktGemeldet(true) {
      pinMode(pin, INPUT_PULLUP);
    }

    void aktualisieren() {
      bool aktuellGedrueckt = digitalRead(pin) == LOW;
      unsigned long jetzt = millis();

      if (aktuellGedrueckt != entprellterZustand) {
        if (jetzt - letzteAenderung >= entprellZeit) {
          letzteAenderung = jetzt;
          entprellterZustand = aktuellGedrueckt;

          if (entprellterZustand) {
            druckBeginn = jetzt;
            gedruecktGemeldet = false;
          }
        }
      }
    }

    bool istGedrueckt() const {
      return entprellterZustand;
    }

    bool wurdeGedrueckt() {
      if (!entprellterZustand || gedruecktGemeldet) {
        return false;
      }
      gedruecktGemeldet = true;
      return true;
    }

    bool istLangGedrueckt() const {
      return entprellterZustand && (millis() - druckBeginn >= langeDruckZeit);
    }
};

#endif
