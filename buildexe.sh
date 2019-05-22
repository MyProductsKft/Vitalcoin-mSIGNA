#!/bin/bash

set -x
set -e

x86_64-w64-mingw32-g++ -Wl,-s -Wl,-subsystem,windows -mthreads -o build/release/mSIGNA.exe object_script.mSIGNA.Release  -lmingw32 -lqtmain -Lsysroot/lib -lCoinDB -lCoinQ -lCoinCore -llogger -lqrencode -L/usr/local/x86_64-w64-mingw32/plugins/platforms -static -static-libgcc -static-libstdc++ -lpthread -lmswsock -lboost_system-mt-s -lboost_filesystem-mt-s -lboost_regex-mt-s -lboost_thread_win32-mt-s -lboost_serialization-mt-s -lcrypto -lodb-sqlite -lodb -lsqlite3 -lQt5Widgets -lQt5Gui -lQt5Network -lQt5Core /usr/local/x86_64-w64-mingw32/plugins/platforms/libqwindows.a -lwinspool -lshlwapi -lQt5PlatformSupport -L/usr/local/x86_64-w64-mingw32/plugins/imageformats /usr/local/x86_64-w64-mingw32/plugins/imageformats/libqdds.a /usr/local/x86_64-w64-mingw32/plugins/imageformats/libqicns.a /usr/local/x86_64-w64-mingw32/plugins/imageformats/libqico.a /usr/local/x86_64-w64-mingw32/plugins/imageformats/libqtga.a /usr/local/x86_64-w64-mingw32/plugins/imageformats/libqtiff.a /usr/local/x86_64-w64-mingw32/plugins/imageformats/libqwbmp.a /usr/local/x86_64-w64-mingw32/plugins/imageformats/libqwebp.a -lQt5Gui -lcomdlg32 -loleaut32 -limm32 -lwinmm -lglu32 -lopengl32 -lgdi32 -lqtpng -lqtharfbuzzng -L/usr/local/x86_64-w64-mingw32/plugins/bearer /usr/local/x86_64-w64-mingw32/plugins/bearer/libqgenericbearer.a /usr/local/x86_64-w64-mingw32/plugins/bearer/libqnativewifibearer.a -lQt5Network -ldnsapi -liphlpapi -lQt5Core -lole32 -luuid -lws2_32 -ladvapi32 -lshell32 -luser32 -lkernel32 -lmpr -lqtpcre build/release/obj/mSIGNA_res.o
