#!/bin/bash
read  "Dropping packets from $1..." 
iptables -I INPUT -s $ip -j DROP
echo "The packets from $1 will be dropped."
