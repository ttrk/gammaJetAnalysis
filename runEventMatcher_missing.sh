#!/bin/sh

#http://stackoverflow.com/questions/3598664/creating-a-shell-script-to-run-java-program?rq=1

progName="eventMatcher_missing";

#g++ $progName.C $(root-config --cflags --libs) -Wall -Wextra -O2 -o $progName.exe || exit 1
g++ $progName.C $(root-config --cflags --libs) -Wall -Wextra -g -o $progName.exe || exit 1

./$progName.exe
