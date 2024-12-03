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
global pub_id
pub_id = h.hexdigest()[:10]
sub_id=h.hexdigest()[10:]
print(f"Listen me at id {pub_id}")

client = mqtt_client.Client(mqtt_client.CallbackAPIVersion.VERSION2, pub_id)
average_number=deque(maxlen=100)

print("Connecting to broker", broker)
print(client.connect(broker))
client.loop_start()
print("Publishing")

global pub_id_got
pub_id_got=False
subbed=False

def on_message(client,userdata,message):
    try:
        data=message.payload.decode('utf-8')
        pub_id_got=True
        print("received message = ", data, f" on topic: Client_sub/{pub_id}")
            
    except:
        print(message.payload)
client.on_message=on_message
client.subscribe(f"Client_sub/{pub_id}")
while not pub_id_got:
    client.publish("Tetsushiro/Yuji/Get/Pub/Id",pub_id)
print("pub_id_got!")



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
min_max_time_start=0
_min,_max=0,0
while True:

    photo_val_resp: str = send_command('p', responses['p'], connection_photo)
    if photo_val_resp:
        photo_val = int(photo_val_resp.replace("\n", "").replace("b",''))
        _min=photo_val if photo_val<_min else _min
        _max=photo_val if photo_val>_max else _max
        
        if time.time() >=instant_time_start+0.5:
                client.publish(f"lab/{pub_id}/photo/instant", photo_val)
                print("photo_val: ",photo_val)
                instant_time_start=time.time()
                
        if len(average_number)<100:
            average_number.append(photo_val)
        elif len(average_number) >= 100:
            average_number.popleft()
            average_number.append(photo_val)
        num = manipulate_queue(average_number)
        if time.time() >=averge_time_start+0.5:
            client.publish(f"lab/{pub_id}/photo/averge", num)
            print("num: ", num)
            averge_time_start=time.time()
        
        if time.time() >=min_max_time_start+0.5:
            client.publish(f"lab/{pub_id}/photo/min_max", f"{photo_val} {_min} {_max}")
            print("min_max: ",f"{photo_val} {_min} {_max}")
            min_max_time_start=time.time()
        

client.disconnect()
client.loop_stop()
