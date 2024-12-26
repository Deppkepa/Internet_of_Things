import time, sys
import datetime
import paho.mqtt.client as mqtt_client
import random
import hashlib
from uuid import getnode as get_mac
import questionary

def our_hash(string):
    h = hashlib.new('sha256')
    h.update(str(string).encode())

    return h.hexdigest()[:20]

def get_client_id():
    mac = get_mac()
    id = our_hash(mac)

    return id


topic = sys.argv[1]

broker = "test.mosquitto.org"#"broker.emqx.io"

client = mqtt_client.Client(
   mqtt_client.CallbackAPIVersion.VERSION2,
   get_client_id()
)

print("Connecting to broker", broker)
print(client.connect(broker))
client.loop_start()
print(f"Publishing on topic {topic}")

last_execution_time = time.monotonic()
state = ""
top = 40
bottom = 20
last_time=datetime.datetime.now()

while True:
    now = datetime.datetime.now()
    if now.second == bottom and state != "HIGH":
        client.publish(topic, 1)
        print("HIGH")
        state = "HIGH"
    elif now.second == top and state != "LOW":
        client.publish(topic, 0)
        print("LOW")
        state = "LOW"
    if (now-last_time).total_seconds()>=60:
        top-=1
        if top==30:
            top=40
            last_time=now

client.disconnect()
client.loop_stop()
