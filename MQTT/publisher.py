import time
import serial
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib
from collections import deque

responses = {"d": 7,
             "u": 6,
             "p": 4} # zero fill to

port_photo = "COM7"
connection_photo = serial.Serial(port_photo, timeout=1, baudrate=9600)

broker = "broker.emqx.io"

h = hashlib.new('sha256')
mac = get_mac()
h.update(str(mac).encode())
pub_id = h.hexdigest()[:10]
print(f"Listen me at id {pub_id}")

client = mqtt_client.Client(mqtt_client.CallbackAPIVersion.VERSION2, pub_id)
average_number=deque(maxlen=100)

print("Connecting to broker", broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")




def manipulate_queue(queue):
    elements_sum = 0
    for i in range(len(queue)):
        elements_sum += queue[i]
    return  int(elements_sum / len(queue))

def send_command(cmd:str,
                 response_len: int,
                 connection: serial.Serial
) -> str:
    str_resp: str = ''
    connection.write(cmd.encode())
    if response_len > 0:
        resp: bytes = connection.read(response_len)
        str_resp = resp.decode()
    return str_resp
instant_time_start=0
averge_time_start=0
while True:

    photo_val_resp: str = send_command('p', responses['p'], connection_photo)
    if photo_val_resp:
        photo_val = int(photo_val_resp.replace("\n", "").replace("b",''))
        
        if time.time() >=instant_time_start+0.5:
                client.publish(f"lab/{pub_id}/photo/instant", photo_val)
                print("photo_val: ",photo_val)
                instant_time_start=time.time()
        if len(average_number)<100:
            average_number.append(photo_val)
        elif len(average_number) >= 100:
            
            #print(num)
            average_number.popleft()
            average_number.append(photo_val)
            #average_number.clear()
        num = manipulate_queue(average_number)
        if time.time() >=averge_time_start+0.5:
            client.publish(f"lab/{pub_id}/photo/averge", str(num))
            print("num: ", num)
            averge_time_start=time.time()
        
        #print(photo_val)
        
#client.publish(f"lab/{pub_id}/led/state","")
client.disconnect()
client.loop_stop()
