# Project Documentation

## Title: Thermal Comfort and Pain Management of MRSA Patients using IoT Connectivity

### Abstract
This project aims to enhance the thermal comfort and pain management of MRSA patients using IoT technology. The Predicted Mean Vote (PMV) and Predicted Percentage of Dissatisfied (PPD) models are utilized to assess thermal comfort based on room temperature and humidity. Additionally, pain levels are determined using Electromyography (EMG), Galvanic Skin Response (GSR), and body temperature data, analyzed through a machine learning model (XGBoost).

---

## Table of Contents
1. Introduction
2. System Design and Architecture
3. Data Collection
4. Thermal Comfort Analysis
5. Pain Management Analysis
6. Machine Learning Model for Pain Prediction
7. Results and Discussion
8. Conclusion
9. References
10. Appendices

---

## 1. Introduction

### 1.1 Background
MRSA infections are difficult to treat due to antibiotic resistance, making patient care challenging. This project leverages IoT technology to monitor and enhance patient comfort and pain management.

### 1.2 Objectives
- Improve thermal comfort for MRSA patients using IoT and PMV/PPD models.
- Manage and predict pain levels using IoT data and machine learning (XGBoost).

### 1.3 Scope
The project focuses on using IoT sensors for real-time data collection, applying thermal comfort models, and developing a pain prediction model using machine learning.

---

## 2. System Design and Architecture

### 2.1 IoT Devices
- **Temperature and Humidity Sensors**: Measure room conditions.
- **EMG Sensors**: Record muscle activity.
- **GSR Sensors**: Measure skin conductance.
- **Body Temperature Sensors**: Track patient's body temperature.

### 2.2 Network Architecture
- **Data Flow**: Sensors → IoT Gateway → Cloud Storage → Data Processing
- **Connectivity**: Wi-Fi/Bluetooth for sensor data transmission.

### 2.3 Data Storage
- Cloud-based storage for large-scale data management.
- Database setup for efficient data retrieval and analysis.

---

## 3. Data Collection

### 3.1 Environmental Data
- **Room Temperature and Humidity**: Continuous monitoring using IoT sensors.
- **Data Logging**: Every 5 minutes, stored in cloud database.

### 3.2 Physiological Data
- **EMG**: Muscle activity recorded during periods of discomfort.
- **GSR**: Skin conductance changes logged continuously.
- **Body Temperature**: Recorded in real-time.

### 3.3 Data Preprocessing
- **Cleaning**: Removal of noise and artifacts from raw data.
- **Synchronization**: Aligning environmental and physiological data timestamps.

---

## 4. Thermal Comfort Analysis

### 4.1 PMV Model
- Inputs: Air temperature, mean radiant temperature, relative humidity, air speed, metabolic rate, clothing insulation.
- Calculation: Uses Fanger’s equation to derive PMV value.

### 4.2 PPD Model
- Relationship: PPD is a function of PMV.
- Calculation: Uses standard formula to determine the percentage of dissatisfied individuals.

### 4.3 Implementation
- Real-time computation using collected data.
- Visualization of PMV and PPD values for immediate feedback.

---

## 5. Pain Management Analysis

### 5.1 Physiological Indicators
- **EMG**: High muscle activity indicating pain.
- **GSR**: Increased skin conductance linked to stress/pain.
- **Body Temperature**: Fluctuations correlated with pain episodes.

### 5.2 Data Analysis
- Feature extraction from raw EMG, GSR, and body temperature data.
- Identification of patterns associated with pain levels.

---

## 6. Machine Learning Model for Pain Prediction

### 6.1 Model Selection
- **XGBoost**: Chosen for its efficiency and accuracy in handling complex datasets.

### 6.2 Model Training
- **Dataset Preparation**: Labeled data from patient observations.
- **Training**: Split data into training and testing sets, apply cross-validation.

### 6.3 Model Evaluation
- Metrics: Accuracy, precision, recall, F1 score.
- Validation: Ensuring the model’s reliability through multiple test cases.

### 6.4 Deployment
- Integration with IoT framework for continuous pain level prediction.
- Real-time alerts and feedback to caregivers.

---

## 7. Results and Discussion

### 7.1 Thermal Comfort Results
- Analysis of PMV and PPD values over different conditions.
- Effectiveness of IoT interventions in maintaining comfort.

### 7.2 Pain Management Results
- Performance of the pain prediction model.
- Case studies showcasing the system's impact on patient care.

### 7.3 Discussion
- Implications for MRSA patient care.
- Limitations and areas for improvement.

---

## 8. Conclusion

### 8.1 Summary of Findings
- IoT technology effectively monitors and enhances thermal comfort and pain management.
- PMV/PPD models and XGBoost provide reliable assessments and predictions.

### 8.2 Future Work
- Further research on integrating additional sensors and improving model accuracy.
- Expansion of the system for broader healthcare applications.


