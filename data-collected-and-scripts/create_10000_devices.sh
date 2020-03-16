#!/bin/bash
counter=0

while [ $counter -lt 1000 ]
do
    printf "iotDevice"$counter";"
    curl --location --request POST 'http://localhost:3000/api/Device' --header 'Content-Type: application/json' --data-raw '{
        "$class": "dev.thiagofontes.Device",
        "deviceId": "iotDevice'$counter'",
        "model": "12341",
        "encryptionKey": "'$(head /dev/urandom | tr -dc A-Za-z0-9 | head -c 16)'",
        "owner": "resource:dev.thiagofontes.User#user1",
        "users": ["resource:dev.thiagofontes.User#user1"]
        }' -w "%{time_starttransfer}\n" -s -o /dev/null
    counter=$((counter + 1))
done
