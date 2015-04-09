#!/bin/sh
############################################################
## print the command
echo "command called =" $0 $1 $2
## start time of the script
date1=$(date +"%s")         # %s     seconds since 1970-01-01 00:00:00 UTC
#date1Human=$(date -d @$date1)
date1Human=$(date -d @$date1 '+%d/%m/%Y %H:%M:%S')
echo "started on     =" $date1Human
echo "############################################################"
############################################################

#http://stackoverflow.com/questions/3598664/creating-a-shell-script-to-run-java-program?rq=1

progName="eventMatcher_missing";

#g++ $progName.C $(root-config --cflags --libs) -Wall -Wextra -O2 -o $progName.exe || exit 1
g++ $progName.C $(root-config --cflags --libs) -Wall -Wextra -g -o $progName.exe || exit 1

./$progName.exe

############################################################
echo "############################################################"
echo "##### log of the SCRIPT =" $0

## finish time and run time of the script
date2=$(date +"%s")         # %s     seconds since 1970-01-01 00:00:00 UTC
#date2Human=$(date -d @$date2)
date2Human=$(date -d @$date2 '+%d/%m/%Y %H:%M:%S')
diff=$(($date2-$date1))
diffHuman=$(date -d @$diff)
#echo $date1
echo "started  on    =" $date1Human
echo "finished on    =" $date2Human
echo "$(($diff / 60)) minutes and $(($diff % 60)) seconds elapsed."
echo $diffHuman

echo "##### END #####"
############################################################
