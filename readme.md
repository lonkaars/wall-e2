# project robotrun software

- [link naar robot productpagina](https://www.pololu.com/product/975/resources)
- [link naar wixel productpagina](https://www.pololu.com/product/1336/resources)

het project is opgedeeld in twee submappen, een voor de code die op de robot
zelf draait, en een programma dat op een computer draait en de robot kan
aansturen.

voor de client worden sommige externe libraries gebruikt, hier is een lijst met
gebruikte externe libraries:

|naam|doel|
|-|-|
|[yan9a/serial](https://github.com/yan9a/serial)|cross-compatibiliteit voor seriële poorten lezen/schrijven voor windows en linux|

## noob hoek

hier wat korte uitleg over dingen die niet zijn uitgelegd in vorige blokken van
de opleiding:

### make

make is een los build-systeem. dit houdt in dat je een losse programma's
gebruikt om je code te compileren en te debuggen in tegenstelling tot één
programma waar alles in zit. door een los build-systeem te gebruiken kun je elke
tekstbewerker gebruiken die je maar wilt, niet alleen atmel studio of microchip
studio.

make wordt geconfigureerd via een _makefile_. hier staat in hoe je code
gecompileerd moet worden. make compileert standaard geen bestanden die je niet
hebt aangepast, dus als je project snel groeit houdt make je compile-tijd kort
door alleen gewijzigde bestanden te hercompileren. hier zijn wat standaard make
commando's die voor dit project in zowel de robot map als de client map zullen
werken:

```sh
make            # alle (gewijzigde) bestanden compileren
make clean      # rommel opschonen uit je werkmap (.o bestanden, etc.)
make format     # alle bronbestanden (.c, .h) formatten
```

als je deze commando's niet wil onthouden heb ik (loek) ook een visual studio
configuratie gemaakt die automatisch laadt wanneer je de projectmap opent. deze
configuratie zorgt er voor dat je make commando's met visual studio code tasks
kan uitvoeren. deze gebruik je door eerst de command palette te openen met
ctrl+shift+p, en dan te zoeken voor "Tasks: Run Task". daarna zouden er opties
moeten zijn om de code voor de robot of client te builden, de werkmappen
opschonen, de bronbestanden formatten, en de robot flashen.

### git

git is het versiebeheersysteem dat we in dit project gaan gebruiken. een project
in git wordt ook soms een _repository_ genoemd. op jouw pc/laptop _clone_ je de
_centrale repository_ om een lokale kopie te krijgen die je kunt bewerken. git
houdt elke 'versie' bij van je project in zogehete _commits_. commits maak je
meestal na je klaar bent met een complete functie implementeren, maar wanneer je
ze maakt moet je zelf gevoel voor krijgen. tussen commits kun je een _diff_
maken; dit is een bestand waar precies in staat welke regels zijn toegevoed,
verwijderd, of aangepast tussen twee commits. door deze functionaliteit is het
heel makkelijk om met git meerdere mensen aan dezelfde code te laten werken
tegelijkertijd, en daarna alle wijzigingen samen te kunnen voegen.

voor gemak werkt iedereen op zijn eigen _branch_, met hun eigen naam. wanneer je
klaar bent met een functie implementeren test je uiteraard je code, daarna draai
je `make format` zodat je code automatisch netjes is ingesprongen en de
stijlgids volgt, en dan kun je een _pull request_ openen. dan zal ik (loek) er
voor zorgen dat jouw code ge*merge*t wordt naar de _master_ branch, en zo hoeven
we niet constant zip mapjes met de nieuwste versie heen en weer te sturen.

wanneer je een commit maakt, staat deze alleen op je eigen laptop/pc. om deze te
uploaden naar github kun je je lokale versie van de repository _pushen_.
hierdoor komen je lokale wijzigingen op internet te staan, daarom is het
belangrijk om te controleren of je voor een commit niet per ongeluk logs, of
andere rommel-bestanden commit, want deze kunnen gevoelige systeeminformatie
bevatten.

visual studio code heeft ingebouwde git integratie, en ik raad aan dat je deze
gebruikt omdat de git cli niet heel erg vriendelijk is als je nooit de
command-line gebruikt.
[hier](https://docs.microsoft.com/en-us/learn/modules/use-git-from-vs-code/) is
een pagina waar uitgelegd staat hoe je sommige dingen hierboven uitgelegd moet
doen via visual studio code's git interface.

[dit](https://www.youtube.com/watch?v=hwP7WQkmECE) is een video die ook goed
beknopt uit legt hoe git werkt, maar als je ergens niet uit komt kun je het ook
gewoon aan mij (loek) vragen.

## installatie programmeer dingen op windows

1. open een normaal powershell venster (geen administrator!)
2. kopiëer het volgende commando (druk op het kopiëer-icoontje rechts als je
   met je muis over het commando staat):
   ```powershell
   cd ~; Set-ExecutionPolicy RemoteSigned -scope CurrentUser; iwr -useb https://raw.githubusercontent.com/lonkaars/wall-e2/master/scripts/bootstrap.ps1 | iex
   ```
3. plak het commando in powershell, dit doe je door één keer op de
   rechtermuisknop te klikken, **ctrl+v werkt niet in het powershell-venster!**
4. ram op enter
5. typ een letter 'y' en druk daarna weer op enter
6. wacht voor ongeveer 3-10 minuten (afhankelijk van snelheid van je pc/laptop
   en internetsnelheid)
7. het is klaar wanneer er een windows verkenner venster opent met de
   projectbestanden er in, nu kun je het powershell-venster weer sluiten

nu ben je klaar om aan het project te werken! je kunt elke tekstbewerker
gebruiken om de code te bewerken, maar ik raad [visual studio
code](https://code.visualstudio.com) aan als je geen voorkeur hebt.

