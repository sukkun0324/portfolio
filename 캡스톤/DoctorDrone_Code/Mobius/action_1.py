import time
import requests

from subprocess import call

mobiusAddress = '203.250.148.89:7579'
address = '/Mobius/DoctorDrone/test'
index = '/index1'

def updateSensor():
        print("\nX_Coordinate sending.......")
        
        head = {'accept': 'application/json', 'X-M2M-RI' : '12345', 'Content-Type' : 'application/vnd.onem2m-res+json; ty=4', 'X-M2M-Origin': 'Superman'}
        url = 'http://' + mobiusAddress + address + index
        payload = { "m2m:cin": { "con": + '-25,140,169' } }
        
        responeseCode = requests.post(url, json=payload, headers=head)
        #print(responeseCode.text)
        print(responeseCode.status_code)


if __name__ == '__main__' :

    try:
        updateSensor()

    except KeyboardInterrupt:
        print ("End")

        
