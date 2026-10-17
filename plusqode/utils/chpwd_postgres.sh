#!/bin/bash

read -s -p "[sudo] password:" SUDO_PASS

echo $SUDO_PASS | sudo -S -u postgres psql -d template1 -c "ALTER  USER postgres WITH PASSWORD '$SUDO_PASS'"

echo "New Postgres Password is:" $SUDO_PASS 
