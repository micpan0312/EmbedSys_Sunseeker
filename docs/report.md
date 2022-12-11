# Table of Contents
* Abstract
* [Introduction](#1-introduction)
* [Related Work](#2-related-work)
* [Technical Approach](#3-technical-approach)
* [Evaluation and Results](#4-evaluation-and-results)
* [Discussion and Conclusions](#5-discussion-and-conclusions)
* [References](#6-references)

# Abstract

After indoor time increases, people’s love for houseplants has blossomed, and hence it is no surprise to see indoor gardening continuing to surge in popularity. While some smart gadgets and devices were developed for improving the growth conditions for houseplants, they are limited in watering, soil moisture, and light monitoring, which require owners to take corresponding actions after they are informed. Therefore, in this project, an easier and smarter way of assisting houseplants seek sunlight is proposed and developed. We built an autonomous device with cameras, sensors, and motors that helps houseplants actively look for sunlight without the need of owners interfering. Even though limitations are realized at the late stage of the development process, most of the vital functionalities were fulfilled and shown to work as expected. 

# 1. Introduction

* **Motivation & Objective:** When COVID-19 forced lockdowns and stay-at-home orders, some people adopted a pet and some adopted a plant. Plants have a scientifically supported healing effect with gardening a few times a week being associated with higher levels of perceived well-being, lower stress and increased physical activity [ref]. As a result, the popularity in indoor gardening has surged ever since. However, that was during the lockdowns and work-from-home was set to be the new normal, and hence people spent most of their time home, able to take care of their beloved plants most of if not all times. Now, with the coronavirus dying down and most companies returning to on-site working environments, most houseplants however are now left unattended. Even though auto watering devices or plant growth condition monitors exist in the market, little does a device have the functionality that proactively seeks sunlight indoors and autonomously takes the houseplant to bathe under it. In this project, we are inspired to develop and build a self-care houseplant robot that will change houseplant care. Instead of requiring human’s attention and care, now with our Sunseeker, it is capable of taking care of itself by looking for sunlight during the time when the owner is unavailable. 

* **State of the Art & Its Limitations:** Similar existing products that aid houseplant care nowadays mainly focus on auto watering, soil moisture, and light intensity monitoring with the need of the owner stepping in. 

* **Novelty & Rationale:** Our approach focuses on bringing the houseplant to live and seeking what is essential for it without any intervention. With the growth in indoor gardening over the past few years due to COVID-19 and the returning of on-site working environment for most people in the current climate, we believe our new approach of taking care of houseplants will make the owners' lives more convenient and optimize the growing condition for houseplants.

* **Potential Impact:** Sunseeker offers a choice that owners can have their beloved houseplants self care when they need to. Houseplants could now independently provide themselves with an ideal growth condition.

* **Challenges:** A challenge is to minimize the latency of communication between our edge devices and the robot. Since we have multiple subroutines, there exists a risk of too large latency in our avoidance feature as well as sunlight search functionality, leading to insufficient response in real time when obstacles appear and missing identifying a window when it actually sees one. Bluetooth connection between the Arduino Uno and the Android App struggled to keep the connection. The issue is tied to both the hardware and software. There were also challenges to keep the message organized so the arduino could interpret the message correctly and not miss the time frame to activate the robot’s modules.



* **Requirements for Success:** What skills and resources are necessary to perform the project? We needed one Raspberry Pi for serving as the brain of the robot that ran object detection and distance measurement. One Arduino Uno controlled the mobility of the robot as well as collected the sensor data from UV detection and compass direction measurement. Another Arduino Uno acted as the Bluetooth module that received string input from users that communicated with the robot. Yolov5, a one-stage CNN object detection and classifier, is required to perform window detection.



* **Metrics of Success:** A metric for success in our project is the ability to identify a window and have its distance measured. The communication between Raspberry Pi and Arduino for the distance and window detection information is another key metric in our project. Since our Sunseeker would be operating inside a person’s room, the ability to avoid obstacles is also one required metric. Another essential would be the sensor measurement as it provides the critical information to predict sunlight location and where and how the bot would navigate. Finally, the last metric is a well connected and working bluetooth app and its communication with our robot, as it plays a vital role in inputting the user's desired working time frame. 


# 2. Related Work

# 3. Technical Approach

## Sunlight Spot Prediction function
* **Window detection:** In order to locate where the sunlight lands on the floor in the room, we need to know where the sun is coming from and hence a search of windows in the robot’s surroundings would be of paramount importance in the first step of sunlight spot prediction. Utilizing Yolov5, You Only Look Once, a single-stage object detection algorithm that provides high inference speeds (see figure 1), our Sunseeker was now equipped with computer vision but without the classification of ‘windows’. A sequence of training our own dataset was consequently deployed. As the result turned out, however, our trained model with only window data could sometimes end with misjudgment of anything in the shape of square or rectangle. Merging the pre-existing model with our trained window model showed the best result of all, especially using largest model of the YOLOv5 family, YOLOv5l, with 46.5 million parameters, did the fused model show the best identification result as now even small object detection was feasible and that could distinguish windows to stand out from any other objects in the robot’s vision (see figure 2).

* **Distance Measurement:** Now that our Sunseeker had window identification, what was missing here was the distance between the robot and the window so that we could further predict where the sunlight would land. This was when Intel RealSense L515 came in. RealSense L515 is a LiDAR depth camera that emits a laser and has it bounce back to measure the distance from whatever the vision of the camera is at the moment. It has a consistent high accuracy of 0.25 to 9 meters in range, which provides sufficient range for what the Sunseeker would generally need for indoor measurements. 

* **Combine Object Detection and Distance Measurement:** With both the object identification and distance measurement in place, objects in the robot’s vision would be boxed and detected; at the same time, the coordinates of the four corners of the object would be marked to measure the depth from RealSense to that of the center. In figure 4, it is clearly shown that objects on the desk are detected with the correct identification with precise distance measurements, even the toilet further away in the background is as well recognized and measured in distance. A serial communication between the Raspberry Pi and Arduino is essential to receive window requests and transmit the processed distance from and to one another. Two outputs would be transmitted for our final step of determining the location of the sun, which will be explained in details in the next section: first, the distance from the RealSense depth camera to the center of the window, and second, the absolute distance from the camera to the window. 

* **Distance Data Processed and Sunlight location Predicted:** Details in calculation and prediction of where the sun would land on the floor are illustrated in details in figure 5. After windows are identified and their respective distances measured, the Sunseeker is just one step away from getting to the sunlight spot: the relative angle of the location and the relative distance from the bot to the spot. Before getting started, clarification of what are known and unknown are listed in table 1 below: 

First of all, 𝜽2 can be attained by   𝜽2=cos-1(d3d1). With 𝜽2, d4 = d1 * sin(𝜽2). d5 would just be the sum of d4 and the camera height off of the ground d5=d2 + d4. d6  , the absolute distance from the predicted sunlight spot to window can then be calculated as d6= d5  / tan(𝜽3). 𝜽5 = 180- 𝜽1-𝜽4. Finally, we can derive d7, the distance the robot needs to move from the current spot to the desired destination, from Law of Cosines d7= d32+d62-2d3d6cos(𝜽5) . Same applies to the degrees 𝜽6 the robot needs to rotate before heading straight to the sunlight spot, 𝜽6=cos-1(d62-d52-d722d52d72). Now the bot just need to rotate 𝜽6 degrees and go straight forward by d7 meters and the sunlight spot search would be complete.

## Bluetooth Module
The Bluetooth app for the android phone is written by the MIT app inventor developer. The App inventor uses a scratch program. The MIT app inventor has a builtin bluetooth client that would allow to send a message. In this project, we would be using a String message to send a message to the bluetooth device on the robot. The robot uses the arduino HC-06 module to receive the String message. The String message includes the time the message is sent, the start time for the robot, and the time duration for the robot to run all the subroutines. The time the message sent would tell the arduino what the current time is and that is the start time of the arduino count down. The start time for the robot is the time when the rest of the robot needs to activate all the other modules like the Camera, UV sensor, and Compass. The other modules are activated using GPIO input from one arduino with the bluetooth to the other arduino connected to the rest of the other modules since the first arduino is occupied with the RX and TX for the bluetooth and the Camera’s Raspberry pi uses the RX and TX for communication [3]. Once the internal timer counts up to the end time, which is the duration time added to the start time, the robot will stop running all the other modules. All the inputs are shown in the figure below.

## Sunlight Trajectory Prediction function
The sunlight trajectory prediction is to predict the angle of the sunlight movement based on the initial position. The sunlight trajectory prediction must be at the spot that the Sunlight Spot prediction made. The robot would start moving back and forth for a specific distance calculated from the absolute distance from the robot. The robot will constantly check for the UV light. Once the UV is detected the angle measured from the compass would be stored into an array element in the Arduino. Once a 30 minute cycle has passed, it would use the angle that the compass measured and move forward to see if the UV light is present on the spot. If the robot does not find UV light it would restart to the original start degree from the sunlight spot prediction. Once it is able to find the new spot it would store the new degree as an additional array element. The array would add all the degrees together and get the average degree and use the degree for the next cycle.



# 4. Evaluation and Results

# 5. Discussion and Conclusions

# 6. References
