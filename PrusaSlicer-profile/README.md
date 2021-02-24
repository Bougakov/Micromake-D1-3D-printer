# Just a bare-bones [PrusaSlicer](https://www.prusa3d.com/prusaslicer/) profile for a custom Micromake D1

To edit the configuration preset:
```
mate /Applications/Original\ Prusa\ Drivers/PrusaSlicer.app/Contents/Resources/profiles/Micromake_D1.ini
```

To clean up old config:
```
cd ~/Library/Application\ Support/PrusaSlicer && rm -Rf *
```


To debug, run 
```
/Applications/Original\ Prusa\ Drivers/PrusaSlicer.app/Contents/MacOS/PrusaSlicer --loglevel 4
```
