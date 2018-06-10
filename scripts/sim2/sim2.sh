#!/bin/sh
# start simulators
echo "Start simulator 2"
gnome-terminal -e "/home/yashren/.dronekit2/sitl/copter-3.3/apm --home=-34.224395,19.127373,0,200 --model=quad --instance 1"
# start mav proxy sessions
sleep 5
echo "Start MAVproxy session 2"
gnome-terminal -e "mavproxy.py --master=tcp:0.0.0.0:5770 --out=udp:0.0.0.0:14560"

