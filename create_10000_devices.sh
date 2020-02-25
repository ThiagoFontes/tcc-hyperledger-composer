#!/bin/bash
counter=2000

while [ $counter -lt 3000 ]
do
    counter=$((counter + 1))
    printf "iotDevice"$counter";"
    curl --location --request POST 'http://localhost:3000/api/Device' --header 'Content-Type: application/json' --data-raw '{
        "$class": "dev.thiagofontes.Device",
        "deviceId": "iotDevice'$counter'",
        "model": "12341",
        "encryptionKey": "=jqwjqniejqniebq",
        "owner": "resource:dev.thiagofontes.User#u1",
        "users": ["resource:dev.thiagofontes.User#u1"]
        }' -w "%{time_starttransfer}\n" -s -o /dev/null
done
