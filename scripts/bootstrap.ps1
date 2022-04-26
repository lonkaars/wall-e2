Start-BitsTransfer -Source https://github.com/msys2/msys2-installer/releases/download/2022-03-19/msys2-x86_64-20220319.exe -Destination .\msys2-x86_64-latest.exe
.\msys2-x86_64-latest.exe in --confirm-command --accept-messages --root C:/msys64
Remove-Item .\msys2-x86_64-latest.exe
C:/msys64/usr/bin/sh.exe -c 'curl -s https://raw.githubusercontent.com/lonkaars/wall-e2/master/scripts/install-mingw-packages.sh | sh'
C:/msys64/usr/bin/sh.exe -c 'git clone https://github.com/lonkaars/wall-e2'
C:/msys64/usr/bin/sh.exe -c '~/wall-e2/scripts/install-sdk.sh'
C:/msys64/usr/bin/sh.exe -c 'cd ~/wall-e2 && explorer.exe .'
