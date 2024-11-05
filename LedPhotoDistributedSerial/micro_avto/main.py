import serial
import time

responses = {"d": 7,
             "u": 6,
             "p": 4} # zero fill to
port_led = "COM9"
port_photo = "COM8"
connection_led = serial.Serial(port_led, timeout=1, baudrate=9600)
connection_photo = serial.Serial(port_photo, timeout=1, baudrate=9600)


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


while True:
    # print(connection_photo)
    photo_val_resp: str = send_command('p', responses['p'], connection_photo)
    if photo_val_resp:
        photo_val = int(photo_val_resp.replace("\n",""))
        print(photo_val)
        if photo_val > 500:

            resp = send_command('u', responses['u'], connection_led)

        else:
            resp = send_command('d', responses['d'], connection_led)


    # for command in responses:
    #     resp =send_command(command, responses[command])
    #     print(resp)
    #     time.sleep(1)
