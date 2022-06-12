#!/bin/bash
pkts = $(cat/dev/stdin)
while read line do
matched_packets = ""
line = `echo "$line" | sed 's/ //g' |cut -f1 -d "#"`
if [ "$line" == ""]; then continue
	fi
IFS = ', ' read -r -a arr <<< "$line"
for i in "${arr[@]" do
	matched_packets = matched_packets + `echo "$pkts" | ./firewall.exe "$i" 2> /dev/null`
	matched_packets = matched_packets + "\n"
			  done
temp = `echo -e "${matched_packets}" | sed '/^$/d' | sort | uniq -c | grep -E "^ *${arr[@]}"  | sed -e "s/^ *${#arr[@]} //"`
list = list + "$temp"
list = list + "\n"
done<"$1"
echo -e "${list}" | sed '/^$/d' | sed 's/ //g' | sort
