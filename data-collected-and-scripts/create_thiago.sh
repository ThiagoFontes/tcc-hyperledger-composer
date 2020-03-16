curl --location --request POST 'http://localhost:3000/api/User' \
        --header 'Content-Type: application/json' \
        --data-raw '{
            "$class": "dev.thiagofontes.User",
            "userId": "thiago",
            "userName": "thiago"
        }'\
        -w "%{time_starttransfer}\n" -s -o /dev/null