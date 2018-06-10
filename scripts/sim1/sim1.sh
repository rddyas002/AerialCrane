#!/bin/sh
# start simulators
echo "Start simulator 1"
gnome-terminal -e "/home/yashren/.dronekit/sitl/copter-3.3/apm --home=-34.224405,19.127213,0,200 --model=quad --instance 0"
# start mav proxy sessions
sleep 5
echo "Start MAVproxy session 1"
gnome-terminal -e "mavproxy.py --master=tcp:0.0.0.0:5760 --out=udp:0.0.0.0:14550"
