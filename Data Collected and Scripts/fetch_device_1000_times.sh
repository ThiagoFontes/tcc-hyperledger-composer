#!/bin/bash
counter=0

while [ $counter -lt 1000 ]
do
    printf "fetch-"$counter";"
    curl --location --request GET 'http://localhost:3000/api/Device/Device5853' \
    -w "%{time_starttransfer}\n" -s -o /dev/null
    counter=$((counter + 1))
done