#! /bin/bash

repertoire_mpsh=$(pwd)

(ls "/usr/local/bin/mpsh" && sudo rm "/usr/local/bin/mpsh")
make
sudo ln -s "$repertoire_mpsh/mpsh" "/usr/local/bin/mpsh"
chmod +x "$repertoire_mpsh/mpsh"
make clean