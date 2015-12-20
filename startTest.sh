#!/bin/sh

echo 'Your name (or dir) : '
read name
echo 'Your algorithm path from your name (or dir) : '
read algoPath
echo 'Situation chosen : '
read sit

if [ "$2" != '' ] && [ -e "$2" ]; then
	echo 'length of experiment (seconds) : '
	read delay
	$1 $name/$algoPath $sit $delay < testInputs/situation$sit | tee $2/result_"$name"_Situation"$sit"_"$delay"s
else
	$1 < $($name/$algoPath < testInputs/situation$sit)
fi
