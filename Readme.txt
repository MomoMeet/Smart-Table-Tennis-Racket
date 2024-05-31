# Smart Table Tennis Racket Dashboard

This project is a web-based dashboard for the Smart Table Tennis Racket. It allows users to manually input sensor data (from gyroscopes and accelerometers) and predict the type of shot using a machine learning model. The predictions are displayed on the same dashboard page.

## Features

- Manual data input for sensor readings.
- Prediction of the shot type using a pre-trained machine learning model.
- Display of prediction probabilities for each shot type.
- Modern and responsive UI for a seamless user experience.

## Prerequisites

- Python 3.6+
- pip (Python package installer)
- Virtual environment (optional but recommended)

## Setup Instructions

python -m venv venv
.\venv\Scripts\activate

pip install -r requirements.txt

python train_model.py

python app.py

deactivate

smart-table-tennis-racket/
│
├── templates/
│   └── dashboard.html       # HTML template for the dashboard
│
├── static/
│   └── styles.css           # CSS styles for the dashboard
│
├── model.pkl                # Serialized machine learning model
├── scaler.pkl               # Serialized scaler
├── label_encoder.pkl        # Serialized label encoder
│
├── train_model.py           # Script to train the model and save it
├── app.py                   # Flask application
├── requirements.txt         # Python dependencies
├── README.md                # Project instructions
└── testmean.csv             # Dataset file (example)


