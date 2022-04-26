#!/bin/sh

bye () {
	echo "run me as root!"
	exit 1
}

[ $(id -g) -ne 0 ] && bye

mkdir temp
cd temp

wget https://www.pololu.com/file/0J1058/libpololu-avr-151002.zip -O libpololu-avr.zip
wget https://www.pololu.com/file/0J490/wixel-linux-110623-amd64.tar.gz -O wixel-linux.tar.gz

unzip libpololu-avr.zip
tar -xvzf wixel-linux.tar.gz

rm libpololu-avr.zip wixel-linux.tar.gz

cd libpololu-avr
make install
cd ..

cd wixel_linux
mv wixelconfig /usr/bin/wixelconfig
mv wixelcmd /usr/bin/wixelcmd
mv 99-pololu.rules /etc/udev/rules.d/99-pololu.rules
cd ..

cd ..
rm -rf temp
