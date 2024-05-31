import pandas as pd
import numpy as np
import pickle
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split, GridSearchCV
from sklearn.preprocessing import StandardScaler, LabelEncoder
from sklearn.metrics import jaccard_score, f1_score, accuracy_score
from sklearn.tree import DecisionTreeClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.svm import SVC
from sklearn.linear_model import LogisticRegression
from sklearn.ensemble import RandomForestClassifier

# Load the dataset
data = pd.read_csv('testmean.csv')

# Data Preprocessing
le = LabelEncoder()
data['output'] = le.fit_transform(data['output'])

# Prepare features and target
X = data.drop('output', axis=1)
y = data['output']

# Scale the features
scaler = StandardScaler()
X_scaled = scaler.fit_transform(X)

# Split the data into training and testing sets
X_train, X_test, y_train, y_test = train_test_split(X_scaled, y, test_size=0.2, random_state=42)

# Initialize models
models = {
    'DT': DecisionTreeClassifier(),
    'KNN': KNeighborsClassifier(),
    'SVM': SVC(probability=True),
    'Logistic_Regre': LogisticRegression(max_iter=1000),
    'RF': RandomForestClassifier()
}

# Define hyperparameters grid for GridSearchCV
param_grid = {
    'DT': {'max_depth': [3, 5, 7, 10]},
    'KNN': {'n_neighbors': [3, 5, 7, 10]},
    'SVM': {'C': [0.1, 1, 10], 'kernel': ['linear', 'rbf']},
    'Logistic_Regre': {'C': [0.1, 1, 10]},
    'RF': {'n_estimators': [50, 100, 200], 'max_depth': [3, 5, 7, 10]}
}

# Evaluate models and find the best one
results = []
best_model = None
best_accuracy = 0

for model_name in models:
    grid = GridSearchCV(models[model_name], param_grid[model_name], cv=5, scoring='accuracy')
    grid.fit(X_train, y_train)
    best_estimator = grid.best_estimator_
    y_pred = best_estimator.predict(X_test)
    accuracy = accuracy_score(y_test, y_pred)
    if accuracy > best_accuracy:
        best_accuracy = accuracy
        best_model = best_estimator
    results.append((model_name, grid.best_params_, accuracy))

# Save the best model, scaler, and LabelEncoder
with open('model.pkl', 'wb') as model_file:
    pickle.dump(best_model, model_file)

with open('scaler.pkl', 'wb') as scaler_file:
    pickle.dump(scaler, scaler_file)

with open('label_encoder.pkl', 'wb') as le_file:
    pickle.dump(le, le_file)

print(f"Best Model: {best_model}")
print(f"Results: {results}")
