#!/bin/sh
# start simulators
echo "Start simulators"
gnome-terminal -e "dronekit-sitl copter --home=-34.224405,19.127213,0,200 --model=quad --instance 1"
gnome-terminal -e "dronekit-sitl copter --home=-34.224395,19.127373,0,200 --model=quad --instance 2"
# start mav proxy sessions
sleep(5)
echo "Start MAVproxy sessions"
gnome-terminal -e "mavproxy.py --master=tcp:0.0.0.0:5770 --out=udp:0.0.0.0:14550"
gnome-terminal -e "mavproxy.py --master=tcp:0.0.0.0:5780 --out=udp:0.0.0.0:14551"

