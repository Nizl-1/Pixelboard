#ifndef ENTPRELLTER_TASTER_H
#define ENTPRELLTER_TASTER_H

#include <Arduino.h>

class EntprellterTaster {
  protected:
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

    virtual void aktualisiere() {		// entspricht der Methode check()
      bool aktuellerZustand = !digitalRead(pin); // Negation für negative Logik
      unsigned long aktuelleZeit = millis();

      if (aktuellerZustand != entprellterZustand && (aktuelleZeit - letzteAenderung) > entprellZeit) {
        entprellterZustand = aktuellerZustand;
        letzteAenderung = aktuelleZeit;

        if (entprellterZustand) {
          druckBeginn = aktuelleZeit;
          gedruecktGemeldet = false;
        }
      }
    }

    bool istGedrueckt() {
      return entprellterZustand;
    }

    bool wurdeGedrueckt() {     // entspricht wurdeKurzGedrueckt
      if (!entprellterZustand && !gedruecktGemeldet) {
        if (millis() - druckBeginn < langeDruckZeit) {
          gedruecktGemeldet = true;
          return true;
        }
      }
      return false;
    }

    bool wurdeLangeGedrueckt() {
      if (entprellterZustand && !gedruecktGemeldet) {
        if (millis() - druckBeginn >= langeDruckZeit) {
          gedruecktGemeldet = true;
          return true;
        }
      }
      return false;
    }
};

#endif
