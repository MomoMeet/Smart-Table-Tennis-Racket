# Smart-Table-Tennis-Racket
 Our project focuses on creating a smart table tennis racket using IoT and Machine Learning to revolutionize how players train and analyze their performance.
# Steps
 1.Connet the Microcontroller Esp32c3 with MPU6050.
  ![cd](https://github.com/MomoMeet/Smart-Table-Tennis-Racket/assets/161807876/b4085da6-d1dc-48ac-93f3-b2dd71184c0b)
 2.Upload the .ino file to the Esp32c3.(For Data read upload Data_Read.ino and for senf the data to the firebase use Cloud.ino file)
 3.Make the .csv file of the data read and train the ML Model (We had use 5 Model KNN,SVM,Decision tree,Neo base and randomforest then we had use randomforest)
 4.Using the Pickel Library in python save your ML model.
 5.Using flask integrate the ML model with the webpage.
