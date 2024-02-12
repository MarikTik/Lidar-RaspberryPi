1. System Setup

    First, connect the LiDAR to your system's motherboard via an onboard serial port or a USB-to-serial module (e.g., CP2102 module).
    Second, set the -x permission for the LiDAR's serial port device mounted in the system (using /dev/ttyUSB0 as an example)
        In actual use, set this according to the LiDAR's actual mounted status in your system. You can use the ls -l /dev command to check.

bash

cd ~/ldlidar_ws/ldlidar_stl_sdk



sudo chmod 777 /dev/ttyUSB0

2. Compilation

bash

cd ~/ldlidar_ws/ldlidar_stl_sdk


./auto_build.sh

3. Execution

bash

./start_node.sh

"""
Writing the translated README content to a README file

readme_path = "/mnt/data/README_EN.md" with open(readme_path, "w") as readme_file: readme_file.write(translated_text)

readme_path

Result

'/mnt/data/README_EN.md'