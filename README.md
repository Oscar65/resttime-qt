# resttime-qt

Is a Qt desktop application that you can configure to show you a warn when you need to rest or anything else.
Can show blink in taskbar (openbox), different color (KDE) or restore window state at end.

I created this Qt application because gnome-clocks countdown timer in openbox don't show any
warn and in gnome is very easy not to notice about the warning.

I released this application with GNU GPL version 3 license.

## Steps to compile, install & run (first you must install qt5-base)

$ qmake

$ make

$ sudo make install

$ /opt/resttime-qt/bin/resttime-qt

To uninstall

$ sudo make uninstall

## How create new languages

Add filename in TRANSLATIONS with the country code (file resttime-qt.pro)

By calling lupdate you create the language files (.ts):

$ lupdate -verbose resttime-qt.pro

Which you translate by using the tool Qt Linguist:

$ linguist languages/resttime-qt_es.ts

After doing this, you call lrelease to create the binary language files (.qm):

$ lrelease resttime-qt.pro
