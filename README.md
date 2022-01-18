email: jae-beom@kakao.com

# urdf_test
urdf: pendulum &amp; slider-crank

## Rviz launch

### Pendulem URDF model check   
<pre><code>roslaunch urdf_test urdf_pen_test.launch
</code></pre>

### Slider-Crank URDF model check   
<pre><code>roslaunch urdf_test urdf_sc_test.launch
</code></pre>

#### Joint control:   
1st kill joint_state_publisher_gui
<pre><code>rosnode kill /joint_state_publisher_gui
</code></pre>

2nd rosrun node   

##### Pendulum
<pre><code>rosrun urdf_test pen_joint_node
</code></pre>

##### Slider-Crank
IF 'Error: Could not open input file',
edit sc_joint_node.cpp: chdir("catkin_ws/"); to chdir("ROS_WORKSPACE/");
<pre><code>rosrun urdf_test sc_joint_node
</code></pre>


## URDF tool
submit slider_crank.urdf or pendulum.urdf  

### URDF model check 
<pre><code>check_urdf slider_crank.urdf
</code></pre>

### Structure: PDF File
<pre><code>urdf_to_graphiz slider_crank.urdf
</code></pre>
