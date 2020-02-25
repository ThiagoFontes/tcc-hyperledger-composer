#!/bin/bash
counter=0

while [ $counter -lt 10 ]
do
    printf "user"$counter";"
    curl --location --request POST 'http://localhost:3000/api/User' \
        --header 'Content-Type: application/json' \
        --data-raw '{
            "$class": "dev.thiagofontes.User",
            "userId": "user'$counter'",
            "userName": "user'$counter'"
        }'\
        -w "%{time_starttransfer}\n" -s -o /dev/null

    counter=$((counter + 1))
done