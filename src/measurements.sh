#! /bin/bash
# Mahsa Rezaei firuzkuhi
#source ./.bashrc

cd /home2/acct10/sort-test

echo 'First iteration'

echo 'Size 1024'
./sort-test 1024

echo 'Size 8192'
./sort-test 8192

echo 'Size 65536'
./sort-test 65536


echo '2nd iteration'

echo 'Size 1024'
./sort-test 1024

echo 'Size 8192'
./sort-test 8192

echo 'Size 65536'
./sort-test 65536

echo '3rd iteration'

echo 'Size 1024'
./sort-test 1024

echo 'Size 8192'
./sort-test 8192

echo 'Size 65536'
./sort-test 65536

exit
