import time
import serial
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib


responses = {"d": 7,
             "u": 6,
             "p": 4} # zero fill to

port_photo = "COM10"
connection_photo = serial.Serial(port_photo, timeout=1, baudrate=9600)

broker = "broker.emqx.io"

h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
pub_id = h.hexdigest()[:10]
print(f"Listem me at id {pub_id}")

client = mqtt_client.Client(mqtt_client.CallbackAPIVersion.VERSION2, pub_id)

print("Connecting to broker", broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")
def send_command(cmd:str,
                 response_len: int,
                 connection: serial.Serial
) -> str:
    str_resp: str = ''
    connection.write(cmd.encode())
    if response_len > 0:
        print(connection.read(response_len))
        resp: bytes = connection.read(response_len)
        str_resp = resp.decode()
    return str_resp

while True:

    photo_val_resp: str = send_command('p', responses['p'], connection_photo)
    if photo_val_resp:
        photo_val = int(photo_val_resp.replace("\n", ""))
        # print(f"Publishing {photo_val}")
        client.publish(f"lab/{pub_id}/led/state", photo_val)

client.disconnect()
client.loop_stop()
