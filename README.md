# Smart Table Tennis Racket

Our project focuses on creating a smart table tennis racket using IoT and Machine Learning to revolutionize how players train and analyze their performance.

## Project Description

🏓🤖 **Smart Table Tennis Racket:**

- **IoT Sensors:** Using the MPU6050 sensor, we capture detailed data on gyroscope and acceleration coordinates (x, y, z) during forehand, backhand, and flick shots.
- **Connectivity:** The ESP32C3 microcontroller with an inbuilt Wi-Fi module ensures seamless data transmission.
- **Cloud Technology:** We use Firebase for storing and managing our data in the cloud.
- **Machine Learning:** Training models (Decision Tree, KNN, Logistic Regression, SVM, Random Forest) on the collected dataset to classify forehand, backhand, and flick shots. These models provide valuable performance metrics and insights into the player’s technique and playing style.
- **Performance Metrics & Insights:** Extracted valuable metrics to evaluate and enhance the player’s technique and playing style.
- **Frontend Integration:** Integrated the ML model with a user-friendly frontend to display real-time performance.

## Technologies Used

- **IoT (including Wi-Fi connectivity):** Enables real-time data transmission.
- **Cloud Technology (Firebase):** Facilitates efficient and scalable data management.
- **Machine Learning:** Advanced algorithms process data and classify strokes.
- **Frontend Development:** HTML5, CSS, and JavaScript create a dynamic and interactive user interface.
- **Integration:** Seamless connection between the ML model and frontend for real-time feedback.

## Steps

1. Connect the Microcontroller Esp32c3 with MPU6050.

   ![Circuit_diagram](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/146100584/9be545e5-6812-456d-b38b-810b5534dcb5)
   
3. Upload the .ino file to the Esp32c3. (For Data read upload Data_Read.ino and to send the data to Firebase use Cloud.ino file)
4. Make the .csv file of the data read and train the ML Model (We have used 5 models: KNN, SVM, Decision Tree, Neo Base, and Random Forest. Then we use Random Forest)

   ![dataset](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/146100584/7c4d2f76-2ad8-4990-8fab-a24741af5714)
   
6. Using the Pickle Library in Python, save your ML model.
7. Using Flask, integrate the ML model with the webpage.

**Webpage Output**

![Frontend1](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/161807876/68b85746-28fc-40b1-b6e9-435b12f324af)
![Frontend2](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/161807876/e4ebdd45-80ec-40b7-8e1e-d7c2d82184b2)
![Frontend3](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/161807876/2d07c254-6bac-4c72-996f-e61c9867c3ff)
![Frontend4](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/161807876/0a41ec78-75e4-4aae-90e1-fdb953312416)


## Final Prototype of Smart Table Tennis Racket:
  
  ![Smart_racket_1](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/146100584/0934802b-9482-40b0-beb6-cee0b7f5c46f)


