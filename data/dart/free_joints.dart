<?xml version="1.0" ?>
<dart version="1.0">
    <world name="world 1">
        <physics>
            <time_step>0.001</time_step>
            <gravity>0 -9.81 0</gravity>
        </physics>
        <skeleton name="skeleton 1">
            <body name="link 1">
                <gravity>1</gravity>
                <transformation>1 2 3 0.1 0 0</transformation>
                <inertia>
                    <mass>5</mass>
                    <offset>0 0 0</offset>
                    <moment_of_inertia>
                        <ixx>1</ixx>
                        <iyy>1</iyy>
                        <izz>1</izz>
                        <ixy>0</ixy>
                        <ixz>0</ixz>
                        <iyz>0</iyz>
                    </moment_of_inertia>
                </inertia>
                <visualization_shape>
                    <transformation>0 0 0 0 0 0</transformation>
                    <geometry>
                        <box>
                            <size>0.1 0.2 0.3</size>
                        </box>
                    </geometry>
                </visualization_shape>
                <collision_shape>
                    <transformation>0 0 0 0 0 0</transformation>
                    <geometry>
                        <box>
                            <size>0.1 0.2 0.3</size>
                        </box>
                    </geometry>
                </collision_shape>                                
            </body>
            <joint type="free" name="joint 1">
                <parent>world</parent>
                <child>link 1</child>
                <transformation>0 0 0 0 0 0</transformation>
            </joint>
        </skeleton>	
    </world>
</dart>
