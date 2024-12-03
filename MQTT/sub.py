import time
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib, serial

broker="broker.emqx.io"

pub_id=""
global state

h=hashlib.new('sha256')
mac=get_mac()
h.update(str(mac).encode())
sub_id=h.hexdigest()[10:20]

responses = {"d": 7,
             "u": 6} # zero fill to
port_led = "COM9"
connection_led = serial.Serial(port_led, timeout=1, baudrate=9600)

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

def on_message(client,userdata,message):
    try:
        data=message.payload.decode('utf-8')
        if state not in ["instant","averge"]:
            value,_min,_max=list(map(int, data.split(" ")))
            if value > sum([_min,_max])/2:
                resp = send_command('u', responses['u'], connection_led)
            else:
                resp = send_command('d', responses['d'], connection_led)
        print("received message = ", data, f" on topic: {state}")
            
    except:
        print(message.payload)
def on_message2(client,userdata,message):
    try:
        data=message.payload.decode('utf-8')
        global pub_id
        pub_id=data
        client.publish(f"Client_sub/{data}","Got it!")
        print("received message = ", data, f" on topic: Tetsushiro/Yuji/Get/Pub/Id")
            
    except Exception as e:
        print(e)
        print(message.payload)   

client=mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2,
    sub_id
)


client.on_message=on_message2



print("Connecting to broker ", broker)
client.connect(broker)

print("Waiting for pub_id")




client.loop_start()
client.subscribe("lab/tetsushiro/yuji")
while not pub_id:
    continue
print(f"Got pub id: {pub_id}")

client.loop_stop()


client.on_message=on_message
client.loop_start()
state=input("Введите топик: ")


while state not in ["instant","averge","min_max"]:
    state=input("Введите топик: ")
print("Subscribing")
client.subscribe(f"lab/{pub_id}/photo/{state}")
time.sleep(1800)
client.disconnect()
client.loop_stop()

