@echo off
rem Build all java source code from current folder and run
if not exist build mkdir build
javac *.java -Xlint:unchecked -d ./build -g
java -classpath ./build QuickSort 12 2