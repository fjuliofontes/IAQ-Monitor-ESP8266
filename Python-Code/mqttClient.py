import paho.mqtt.client as mqtt
import os, json, threading, time, random, datetime, signal, sys, csv
### MQTT Settings
broker = "broker.hivemq.com" # mqtt broker
port = 1883 # mqtt broker port
client_name = "Graph1"
subscribe_topic = "ESP8266/BME680/data"
debug = False  ## set this to True for lots of prints
# buffer of data to output to the serial port
outputData = []
#
####  MQTT callbacks
def on_connect(client, userdata, flags, rc):
        if rc == 0:
        #rc 0 successful connect
                print("Connected")
        else:
                raise Exception
        #subscribe to the output MQTT messages
        output_mid = client.subscribe(subscribe_topic)
 
def on_publish(client, userdata, mid):
        if(debug):
                print("Published. mid:")
                print(mid)
def on_subscribe(client, userdata, mid, granted_qos):
        if(debug):
                print("Subscribed. mid:")
                print(mid)
def on_message_output(client, userdata, msg):
        if(debug):
                print("Output Data: ")
                print(msg.topic)
                print("data:") 
                print(msg.payload)
        
        try:
                data = []
                data.append(str(int(datetime.datetime.now().timestamp())))
                with open('bme680.csv', 'a+', newline='', encoding='utf-8') as csv_file:
                        bme680_writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
                        data = data + msg.payload.decode("utf-8").split(',')
                        bme680_writer.writerow(data)
        except:
                pass



def on_message(client, userdata, message):
        if(debug):
                print("Unhandled Message Received: ")
                print(message.topic) 
                print(message.paylod)               
#called on exit
#close serial, disconnect MQTT
def cleanup():
        print("Ending and cleaning up")
        mqtt.Client(client_name).disconnect()

#thread for reading serial data and publishing to MQTT client
def mqtt_publish(msg, mqttc):
                if(debug):
                        print("Message:")
                        print(msg)
                
                try:
                        mqttc.publish("DIAGBOX/CO2", str(msg))
                except(KeyError):
                        # TODO should probably do something here if the data is malformed
                        pass

def signal_handler(signum, frame):
        signal.signal(signum, signal.SIG_IGN)
        print('You pressed Ctrl+C!')
        cleanup()
        sys.exit(0)

def main():
        signal.signal(signal.SIGINT, signal_handler)
        print("Connecting... ")
        #create an mqtt client
        mqttc = mqtt.Client(client_name)
        #attach MQTT callbacks
        mqttc.on_connect = on_connect
        mqttc.on_publish = on_publish
        mqttc.on_subscribe = on_subscribe
        #mqttc.on_message = on_message
        mqttc.message_callback_add(subscribe_topic, on_message_output)
        #connect to broker
        mqttc.connect(broker, port, 60)
        # start the mqttc client thread
        mqttc.loop_start()
        
        while True: # main thread
            time.sleep(1)

if __name__ == '__main__':
    main()