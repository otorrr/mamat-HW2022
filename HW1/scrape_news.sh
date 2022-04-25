#!/bin/bash


array=

echo -n "" > tmp.txt

for line in $(cat 3082)
do
	result=$(echo $line | grep "www.ynetnews.com/article/*" | cut -d '"' -f2)	#copies atricles' links
	if [[ -z $result ]]; then
		continue
	fi
	echo $result >> tmp.txt	
done


uniq tmp.txt unique_tmp.txt	#removes duplicated files

echo -n "" > results.csv
cat unique_tmp.txt | wc -l  >> results.csv	#num of overall links


i=0
for line in $(cat unique_tmp.txt)	#this loop is for visiting every link and write the num of occurrences for each link
do
    wget -O "link_result.txt" $line
    echo -n $line >> results.csv
    
	if [[($(cat link_result.txt | grep "Bennett" | wc -l) -eq 0) && ($(cat link_result.txt | grep "Netanyahu" | wc -l) -eq 0)]]; then	#no accurrences, neither Netanyahu nor Bennett
	    echo ",-" >> results.csv
    else
        echo -n ",Bennett," >> results.csv
        cat link_result.txt | grep "Bennett" | wc -l | tr -d '\n' >> results.csv
        echo -n ",Netanyahu," >> results.csv
        cat link_result.txt | grep "Netanyahu" | wc -l >> results.csv
	fi
	
	i=$((i+1))
done

rm link_result.txt tmp.txt unique_tmp.txt
