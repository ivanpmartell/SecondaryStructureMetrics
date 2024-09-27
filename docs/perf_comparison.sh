#!/bin/bash
ssmetricspath=$1
sovrefinepath=$2

sizes=(10 100 1000 10000 50000 100000)
for i in ${sizes[@]}; do
    < /dev/urandom tr -dc A-Z | head -c $i > randRef.fa
    sed -i '1i>randReference' randRef.fa
    < /dev/urandom tr -dc A-Z | head -c $i > randPred.fa
    sed -i '1i>randPrediction' randPred.fa
    printf "$i" >> ssmetrics_perf.txt
    /usr/lib/linux-tools/5.4.0-195-generic/perf stat -e task-clock:u -r 1 -d $ssmetricspath -r randRef.fa -p randPred.fa 2>&1 | grep task-clock | awk '/^[ \t]*[0-9\.]*/{printf ",%s\n",$1;}' >> ssmetrics_perf.txt
    printf "$i" >> sovrefine_perf.txt
    /usr/lib/linux-tools/5.4.0-195-generic/perf stat -e task-clock:u -r 1 -d $sovrefinepath randRef.fa randPred.fa 2>&1 | grep task-clock | awk '/^[ \t]*[0-9\.]*/{printf ",%s\n",$1;}' >> sovrefine_perf.txt
done

numfiles=(10 100 1000 5000 10000)
for i in ${numfiles[@]}; do
    ssmetricsres=0
    sovrefineres=0
    for ((j = 0; j < i; j++)); do
        < /dev/urandom tr -dc A-Z | head -c 500 > randRef.fa
        sed -i '1i>randReference' randRef.fa
        < /dev/urandom tr -dc A-Z | head -c 500 > randPred.fa
        sed -i '1i>randPrediction' randPred.fa
        ssmetricsres=$(expr $ssmetricsres + $(echo $( TIMEFORMAT="(%3U + %3S)"; { time $ssmetricspath -r randRef.fa -p randPred.fa > /dev/null; } 2>&1) "* 1000" | bc | xargs printf "%0.f"))
        sovres=$(echo $( TIMEFORMAT="(%3U + %3S)"; { time $sovrefinepath randRef.fa randPred.fa > /dev/null; } 2>&1))
        sovfiltered=${sovres#*. }
        sovrefineres=$(expr $sovrefineres + $(echo $sovfiltered "* 1000" | bc | xargs printf "%0.f"))
    done
    printf "$i," >> ssmetrics_perf_files.txt
    printf "$ssmetricsres\n" >> ssmetrics_perf_files.txt
    printf "$i," >> sovrefine_perf_files.txt
    printf "$sovrefineres\n" >> sovrefine_perf_files.txt
done