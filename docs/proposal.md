# Project Proposal

## 1. Motivation & Objective
When COVID-19 forced lockdowns, some people adopted a pet and some adopted a plant. However, that was when work-from-home was set to be the new normal. People spent most of their time home, and were able to take care of their beloved plants at all times. Now, with most companies returning to on-site working environments, most houseplants however are now left unattended. Therefore, we are interested in building a self-care mobile platform that carries the houseplants around looking for sunlight without the help of their owners.

## 2. State of the Art & Its Limitations

We did some research and found that most of the similar existing products that aid houseplant care nowadays still require humans to step in for its better growth conditions. We think they are lacking in utilizing the technology we have today, including machine learning and LiDAR, that can be of good use of proactively letting the houseplants look for sunlight on their own.

## 3. Novelty & Rationale

Our approach is to have a houseplant seek out sunlight without any person’s interaction. Using a camera and a thermal sensor to find the sunlight spot without having to blindly go everywhere to find the sunlight location. We think we would be successful because it would require a lot of computation to find the sunlight using features of sunlight.

## 4. Potential Impact

We want this product to be able to offer these houseplant owners a choice of not being attending for them once in a while, either it’s for their business trip or they might just be forgetful from time to time. The houseplants can therefore independently provide themselves with an ideal growth condition at least in the sense of sunlight exposure.

## 5. Challenges

The challenges are finding ways to have the robot move, avoid obstacles, find the location of the sunlight and be mobile the entire time. There are challenges to having a reliable prediction function and a timer function for the robot. There is also the risk of finding the ideal location to test the robot and what phone application to send the message to the robot.

## 6. Requirements for Success

We would need a camera that can tell the distance of any objects that are in front of it as well as an algorithm that can recognize windows so that the robot can precinct where the sunlight would land. We would also need a robotic body for the platform so that it can move around in the room. We are also thinking of using bluetooth communication between the user and our robot. 

## 7. Metrics of Success

In order to succeed, we would need the camera discussed above to be able to identify windows and the distance of its. Some other sensors including UV and compass would need to work properly. Finally, the communication mentioned above also needs to smoothly send input from a phone app to the robot, preferably Arduino Uno.

## 8. Execution Plan

We will be downloading, installing and setting up the development environment for hardwares for the first week or two. The sensor's calibration and camera functionality should be tested afterwards for general purposes. We should begin implementing specific tests, including object detection and distance measurement on desired objects by week 7-8. And finally, we will assemble each individual part and integrate both hardware and software to make sure it works as expected.

## 9. Related Work

### 9.a. Papers

In this article "Human Following of Mobile Robot [5]", the robot uses computer vision and a constant loop of image searching for the subject. In our work, we would like to loop searching for the window and move to the distance where the sunlight would be. The robot loop would include the camera sensor, which also checks the frame per second when the object is detected. The algorithm pattern and computer vision is what we used for our project.

We sought inspiration and motivation in this next paper “Smart Plant Pot [6].”. In this research, the authors were trying to develop a smart automated system that helped plants with their growing conditions by monitoring their soil moisture, temperature, and sunlight. When any of the metrics fell under the required threshold, it would automatically warn the user and suggest corresponding actions. We noticed that, even though it had an automatic watering and cooling mechanism, the sunlight requirement still was limited to human intervention or replaced with an artificial light. Research has pointed out sunlight is still generally considered more preferable and beneficial for plant growth than artificial light [7]. Hence, we were inspired and motivated to look into the possible approaches and solutions.

### 9.b. Datasets

We are looking into fetching window data as we will be needing to train a model if we cannot find any existing models that can identify a window. Hence, a large dataset of windows should be needed.

### 9.c. Software

We will be installing Raspberry Pi OS, UBUNTU, or UBUNTU Mate onto our Raspberry Pi and hope that there would not exist any installation issues. An existing algorithm that can identify objects would be preferable. OpenCV might be required as well since we will need to do some computer vision processing. 

## 10. References

[1] Ed. “Raspberry Pi Arduino Serial Communication - Everything You Need to Know - the Robotics Back.” End, 15 Nov. 2021, https://roboticsbackend.com/raspberry-pi-arduino-serial-communication/

[2] “Object Detection with yolov5 and Pytorch.” Section, https://www.section.io/engineering-education/object-detection-with-yolov5-and-pytorch/

[3] Ferraro, Kathleen. “How Gardening Became a Wellness Practice among Millennials.” Bustle, Bustle, 21 June 2021, https://www.bustle.com/wellness/gardening-wellness-trend-millennial-self-care-benefits.

[4] PlantWhisperer. “Best Tech Gadgets for Indoor Plant Lovers.” PlantMaid, 10 Dec. 2022, https://www.plantmaid.com/best-tech-gadgets-for-indoor-plant-lovers/.  

[5] Algabri, Redhwan, and Mun-Taek Choi. “Deep-Learning-Based Indoor Human Following of Mobile Robot Using Color Feature.” Sensors (Basel, Switzerland), U.S. National Library of Medicine, 9 May 2020, https://www.ncbi.nlm.nih.gov/pmc/articles/PMC7273221/.  

[6] Kurdeya, Ola, Hadeel Salamin, and Israa Bet-rashed. "Smart plant pot." (2015).

[7] “Do Plants Grow as Well under Artificial Light?” EarthSky, 4 Nov. 2022, https://earthsky.org/human-world/artificial-light-plant-growth/. 

