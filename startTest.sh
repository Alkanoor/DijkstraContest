#!/bin/sh

echo 'Your name (or dir) : '
read name
echo Name $name chosen
echo 'Your algorithm path from your name (or dir) : '
read algoPath
echo Algo $name/$algo chosen
echo 'Situation chosen : '
read sit
echo Situation $sit

if [ "$2" != '' ] && [ -e "$2" ]; then
	echo 'length of experiment (seconds) : '
	read delay
	$1 $name/$algoPath $sit $delay < testInputs/situation$sit | tee $2/result_"$name"_Situation"$sit"_"$delay"s
else
	echo $($name/$algoPath < testInputs/situation$sit) $(echo ' % ') | cat - testInputs/situation$sit | $1
fi
