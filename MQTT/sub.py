import time
import paho.mqtt.client as mqtt_client
import random
from uuid import getnode as get_mac
import hashlib, serial

broker="broker.emqx.io"
pub_id="d97d31bf4c"

if not pub_id:
    raise RuntimeError("Publisher id can not be found")

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
    data=int(message.payload.decode('utf-8'))
    if data > 500:
        resp = send_command('u', responses['u'], connection_led)

    else:
        resp = send_command('d', responses['d'], connection_led)
    
    print("received message = ", data)

client=mqtt_client.Client(
    mqtt_client.CallbackAPIVersion.VERSION2,
    sub_id
)
client.on_message=on_message



print("Connecting to broker ", broker)
client.connect(broker)
client.loop_start()
print("Subscribing")
#while True:
client.subscribe(f"lab/{pub_id}/led/state")
time.sleep(1800)
client.disconnect()
client.loop_stop()
