from flask import Flask, render_template, request, jsonify
import pickle
import numpy as np
import firebase_admin
from firebase_admin import credentials, db

app = Flask(__name__)

# Load the trained model, scaler, and label encoder from the pickle files
with open('model.pkl', 'rb') as model_file:
    model = pickle.load(model_file)

with open('scaler.pkl', 'rb') as scaler_file:
    scaler = pickle.load(scaler_file)

with open('label_encoder.pkl', 'rb') as le_file:
    le = pickle.load(le_file)

# Initialize Firebase with the JSON file path and the database URL
cred = credentials.Certificate("./samrttt-29d2a-firebase-adminsdk-wwyts-2905915968.json")
firebase_admin.initialize_app(cred, {
    'databaseURL': 'https://samrttt-29d2a-default-rtdb.firebaseio.com/'
})

def fetch_data_and_predict():
    # Fetch data from Firebase
    firebase_data = db.reference('/MPU6050').get()
    if firebase_data:
        # Extract relevant values from firebase_data
        aX = firebase_data['meanax']
        aY = firebase_data['meanay']
        aZ = firebase_data['meanaz']
        gX = firebase_data['meangx']
        gY = firebase_data['meangy']
        gZ = firebase_data['meangz']

        # Prepare the input data for prediction
        input_data = np.array([[aX, aY, aZ, gX, gY, gZ]])
        scaled_input_data = scaler.transform(input_data)

        # Predict the class and probabilities
        predicted_class = model.predict(scaled_input_data)
        predicted_class_label = le.inverse_transform(predicted_class)[0]
        probabilities = model.predict_proba(scaled_input_data)[0] * 100  # Convert to percentages
        class_labels = le.inverse_transform(np.arange(len(probabilities)))

        # Prepare the result
        result = {
            'predicted_label': predicted_class_label,
            'probabilities': dict(zip(class_labels, probabilities))
        }
        return result
    return None

@app.route('/')
def dashboard():
    return render_template('dashboard.html')

@app.route('/fetch_latest_results', methods=['GET'])
def fetch_latest_results():
    result = fetch_data_and_predict()
    return jsonify(result)

if __name__ == '__main__':
    app.run(debug=True)
