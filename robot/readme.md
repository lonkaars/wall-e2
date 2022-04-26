# robot code

dit is de submap voor alle code die op de robot zelf draait

## make gedoe

om de code te uploaden naar de robot moet je de juiste com-poort instellen in de
makefile in deze map (regel waar `PORT ?= /dev/ttyACM0` staat). deze kun je
waarschijnlijk vinden in apparaatbeheer op windows. daarna kun je `make flash`
uitvoeren om de code te uploaden
