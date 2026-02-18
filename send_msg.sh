#!/bin/bash
#age: ./connect_loop.sh <IP> <PORT> <NUMBER_OF_CONNECTIONS> "<MESSAGE>"

IP="$1"
PORT="$2"
COUNT="$3"
MSG="$4"

if [ -z "$IP" ] || [ -z "$PORT" ] || [ -z "$COUNT" ] || [ -z "$MSG" ]; then
    echo "Usage: $0 <IP> <PORT> <NUMBER_OF_CONNECTIONS> \"<MESSAGE>\""
    exit 1
fi

for i in $(seq 1 $COUNT); do
    # Send the message and keep connection open (optional)
    echo "$MSG" | nc "$IP" "$PORT" &
    sleep 0.1
done

echo "$COUNT connections started to $IP:$PORT and sent message: $MSG"

