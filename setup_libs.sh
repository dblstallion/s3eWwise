#!/bin/sh
for f in $(find Wwise/SDK/iOS/Debug-iphoneos/lib -type f); do cp $f ${f/.a/_d.a}; done
mv Wwise/SDK/iOS/Debug-iphoneos/lib/*_d.a Wwise/SDK/iOS
cp Wwise/SDK/iOS/Release-iphoneos/lib/*.a Wwise/SDK/iOS

for f in $(find Wwise/SDK/Win32_vc100/Debug\(StaticCRT\)/lib -type f); do cp $f ${f/./_d.}; done
mv Wwise/SDK/Win32_vc100/Debug\(StaticCRT\)/lib/*_d.* Wwise/SDK/Win32_vc100
cp Wwise/SDK/Win32_vc100/Release\(StaticCRT\)/lib/* Wwise/SDK/Win32_vc100