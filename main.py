from flask import Flask, render_template, request
import pickle
import numpy as np
import pandas as pd

app = Flask(__name__)

# Load the trained model, scaler, and label encoder from the pickle files
with open('model.pkl', 'rb') as model_file:
    model = pickle.load(model_file)

with open('scaler.pkl', 'rb') as scaler_file:
    scaler = pickle.load(scaler_file)

with open('label_encoder.pkl', 'rb') as le_file:
    le = pickle.load(le_file)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/predict', methods=['POST'])
def predict():
    try:
        # Get input data from form
        features = [float(x) for x in request.form.values()]
        feature_names = ['aX', 'aY', 'aZ', 'gX', 'gY', 'gZ']
        new_instance = pd.DataFrame([features], columns=feature_names)

        # Scale the new instance using the same scaler
        new_instance_scaled = scaler.transform(new_instance)

        # Predict the class using the loaded model
        predicted_class = model.predict(new_instance_scaled)
        predicted_proba = model.predict_proba(new_instance_scaled)[0] * 100  # Convert to percentages

        # Convert the predicted class index to the original class label
        predicted_class_label = le.inverse_transform(predicted_class)[0]

        # Get class labels
        class_labels = le.inverse_transform(np.arange(len(predicted_proba)))

        # Return the result and pass the zip function
        return render_template('result.html', 
                               predicted_class_label=predicted_class_label, 
                               predicted_proba=predicted_proba, 
                               class_labels=class_labels,
                               zip=zip)
    except Exception as e:
        return str(e)

if __name__ == '__main__':
    app.run(debug=True)
