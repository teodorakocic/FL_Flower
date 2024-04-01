# Federated Learning for activity on mobile edge devices

This project is used for creating experimental environment for the simulation of the on-device federated learning process using the Flower framework. The project differentiates between training the model for two different data sets:

1. This example tracks activity for multiple users and the goal is to classify a given user activity. Dataset used is downloaded from UC Irivine's database - [HARTH](https://archive.ics.uci.edu/dataset/779/harth). The simulation of client data generation is performed by dividing the initial dataset
2. Second example's dataset is generated using the Arduino Nano 33 BLE Sense board and it tracks the activity of edge device:
   - collecting data (run script [movement_model_dataset](/movement_model_dataset/movement_model_dataset.ino))
   - data formatting (run script [create_csv](/create_csv.py))
   - in [utils](/utils.py) change **number of classes** and **features** to values 2 and 10 respectively
   - in [first](/clienteven.py) client and [second](/clientodd.py) one set values for **labels** on [0, 1]
   - in [server's](/server.py) script **number of clients** is set to 2 



## Installation

Create virtual environment and install all needed modules:

```bash
pip3 install -r requirements.txt
```

## Run the project

Start the server
```bash
python3 server.py
```
Run all clients in different terminals (id in range 1 to 4)
```bash
python3 clientsubject<id>.py
```

For clients in second project follow the next steps
```bash
python3 clienteven.py
```
```bash
python3 clientodd.py
```

## Author

[Teodora Kocic](https://github.com/teodorakocic)
