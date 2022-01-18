#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ros/ros.h>
#include <sensor_msgs/JointState.h>

using namespace std;

// number of joint.
// data file type: .csv(include index(1st column))
#define JOINT_NUM 4 
#define size 2048 


struct joint_data{
    char joint_data_col[JOINT_NUM+1][size];
};


double deg2rad(double deg){
   return (deg*M_PI)/180;
}


void remove_spaces(char* str) {
    const char* space = str;
    do {
        while (*space == ' ') {
            ++space;
        }
    } while (*str++ = *space++);
}


void getfield(char* line, struct joint_data *joint_data, int end_index)
{
    int index = 0;
    char *token = strtok(line, ",");

    do{
        strcpy(joint_data->joint_data_col[index++], token);
    }
    while ( index != end_index && (token = strtok(NULL, ",")));
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "state_publisher");
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("joint_states", 1);
    ros::Rate loop_rate(100);

    sensor_msgs::JointState joint_state;


    const string jointName[4] = {
        "REV01_Base_to_Lnik1",
        "REV02_Lnik1_to_Lnik2",
        "REV03_Lnik2_to_Piston",
        "TRANS01_Base_to_Piston"
    };
    struct joint_data joint_data;
    char line[size];
    char path_name[1024];
    char current_workingDir[512];

    // get current working directory
    if (getcwd(current_workingDir, 512) == NULL) {
        perror("Error: getcwd");
        return -1;
    }
    
    // open .csv file
    chdir("catkin_ws/");
    chdir("src/urdf_test/src");
    getcwd(current_workingDir, 512);
    ROS_INFO("%s",current_workingDir);
    sprintf(path_name,"%s/sc_20sec_data.csv", current_workingDir);
    string file_path(path_name);
    FILE* stream = fopen(path_name, "r");

    if(stream == NULL){
        perror("Error: Could not open input file");
        return -1;
    }
    else ROS_INFO("Succese: File load");

    // read data (.csv file) & publish
    while (fgets(line, size, stream))
    {
        // read joint data .csv
        remove_spaces(line);
        char *tmp = strdup(line);
        getfield(tmp, &joint_data, JOINT_NUM+1);
        free(tmp);
        
        // update joint_state
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(JOINT_NUM);
        joint_state.position.resize(JOINT_NUM);

        for (int i=0; i<JOINT_NUM; i++){
            double x=0;
            joint_state.name[i] = jointName[i];
            x = atof(joint_data.joint_data_col[i+1]);
            if (i==3) joint_state.position[i] = x; //translational joint
            else joint_state.position[i] = deg2rad(x); //revolute joint
        }

        // Publish pendulum state
        joint_pub.publish(joint_state);

        // This will adjust as needed per iteration
        loop_rate.sleep();
    }
    ROS_INFO("END");
    return 0;
}

