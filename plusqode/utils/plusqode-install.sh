#!/bin/bash

DB_USER=plusqode
DB_NAME=plusqode
CURR_PATH=`pwd`
DESKTOP_PATH=$(xdg-user-dir DESKTOP)

read -s -p "[sudo] password:" SUDO_PASS

echo $SUDO_PASS | sudo -S -u postgres psql -d template1 -c "ALTER  USER postgres WITH PASSWORD '$SUDO_PASS'"

cp PlusQode.desktop ${DESKTOP_PATH}

sed -i ${DESKTOP_PATH}/PlusQode.desktop -e s:~:${CURR_PATH}:g

echo "New Postgres Password is:" $SUDO_PASS 
