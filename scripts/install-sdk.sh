#!/bin/sh

OS=`uname -o`
LINUX="GNU/Linux"
WINDOWS="Msys"

bye () {
	echo "run me as root!"
	exit 1
}

[ "$OS" != "$WINDOWS" ] && [ $(id -g) -ne 0 ] && bye

mkdir temp
cd temp

wget https://www.pololu.com/file/0J1058/libpololu-avr-151002.zip -O libpololu-avr.zip
unzip libpololu-avr.zip
rm libpololu-avr.zip

cd libpololu-avr
make install
cd ..

if [ "$OS" = "$LINUX" ]; then
	wget https://www.pololu.com/file/0J490/wixel-linux-110623-amd64.tar.gz -O wixel-linux.tar.gz
	tar -xvzf wixel-linux.tar.gz
	rm wixel-linux.tar.gz

	cd wixel_linux
	mv wixelconfig /usr/bin/wixelconfig
	mv wixelcmd /usr/bin/wixelcmd
	mv 99-pololu.rules /etc/udev/rules.d/99-pololu.rules
	cd ..
fi

cd ..
rm -rf temp
