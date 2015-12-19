#!/bin/sh

echo 'Your name (or dir) : '
read name
echo 'Your algorithm path from your name (or dir) : '
read algoPath
echo 'Situation chosen : '
read sit

if [ "$2" != '' ] && [ -e "$2" ]; then
	$1 $name/$algoPath < testInputs/situation$sit | tee $2/result_"$name"_Situation"$sit"
else
	$1 $name/$algoPath < testInputs/situation$sit
fi
