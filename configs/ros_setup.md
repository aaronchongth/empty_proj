# ROS setup

Mainly the tools and aliases I use after all the ROS installations are done. These lines should go into the `~/.bashrc` file,

```bash
# ROS sourcing and gazebo killing alias
alias r1="source /opt/ros/melodic/setup.bash"
alias r2="source /opt/ros/dashing/setup.bash"
alias killgazebo="pkill -9 gzserver && pkill -9 gzclient"

# this is for ROS2 separation of domains
ROS_DOMAIN_ID=128

# middlewares are awesome
alias rmw_frtps="export RMW_IMPLEMENTATION=rmw_fastrtps_cpp"
alias rmw_cyclone="export RMW_IMPLEMENTATION=rmw_opensplice_cpp"
alias rmw_os="export RMW_IMPLEMENTATION=rmw_cyclonedds_cpp"
```
