#!/bin/sh

# change this path to where you install the script
# aka copy pwd and paste it here after cloning the directory
calc="$HOME/000-Projects/basic-calculator/"
eq="$(rofi -dmenu -p "Enter equation: ")"
cd $calc
echo $eq | ./calculator.app | rofi -dmenu
