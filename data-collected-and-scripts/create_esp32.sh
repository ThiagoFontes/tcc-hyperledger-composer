curl --location --request POST 'http://localhost:3000/api/Device' --header 'Content-Type: application/json' --data-raw '{
        "$class": "dev.thiagofontes.Device",
        "deviceId": "ESP32_01",
        "model": "ESP32",
        "encryptionKey": "4To4jyTAOMvf99fx",
        "owner": "resource:dev.thiagofontes.User#thiago",
        "users": ["resource:dev.thiagofontes.User#thiago"]
        }' -w "%{time_starttransfer}\n" -s -o /dev/null