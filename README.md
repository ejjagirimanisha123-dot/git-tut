# Smart Fire Fighting Robot

An autonomous robot project capable of detecting fire sources and extinguishing them using an integrated pump or fan system.

##  Overview
This project focuses on robotics and embedded systems. The robot uses sensory feedback to navigate, identify fire hazards in real-time, and take immediate action.

## 🛠️ Hardware Components
* **Microcontroller:** [e.g., Arduino Uno / ESP32]
* **Sensors:** * IR Flame Sensors (for fire detection)
    * Ultrasonic Sensor (HC-SR04 for obstacle avoidance)
* **Actuators:**
    * DC Motors (for movement)
    * Water Pump/Fan (for extinguishing)
    * Servo Motor (to direct the nozzle/fan)
* **Motor Driver:** [e.g., L298N]

## ⚙️ How It Works
1. **Patrol:** The robot moves autonomously while avoiding obstacles.
2. **Sense:** The flame sensor continuously monitors for infrared radiation.
3. **Act:** Upon detecting a flame, the robot stops, uses the servo to orient toward the source, and triggers the pump/fan.
4. **Return:** Once the fire is cleared, it resumes patrolling.


##  Contributing
Feel free to fork this project and submit pull requests for any improvements or bug fixes.
