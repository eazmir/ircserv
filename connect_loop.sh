#!/bin/bash

# Usage: ./connect_loop.sh <IP> <PORT> <NUMBER_OF_CONNECTIONS>

IP="$1"
PORT="$2"
COUNT="$3"

if [ -z "$IP" ] || [ -z "$PORT" ] || [ -z "$COUNT" ]; then
    echo "Usage: $0 <IP> <PORT> <NUMBER_OF_CONNECTIONS>"
    exit 1
fi

for i in $(seq 1 $COUNT); do
    nc "$IP" "$PORT" &
    sleep 0.1
done

echo "$COUNT connections started to $IP:$PORT"

