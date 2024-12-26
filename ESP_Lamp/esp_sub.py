import time
import paho.mqtt.client as paho
import random

broker="broker.emqx.io"

def on_message(client, userdata, message):
    time.sleep(1)
    data = str(message.payload.decode("utf-8"))
    print("received message =", data)

client= paho.Client() 
client.on_message=on_message

print("Connecting to broker",broker)
client.connect(broker) 
client.loop_start() 
print("Subcribing")
client.subscribe("esp8266/state")
time.sleep(1800)
client.disconnect()
client.loop_stop()
