from serial import Serial as PySerial
from serial import SerialException
import serial.tools.list_ports as ports
from .device import Device, NoDevice
import json
from threading import Thread

class Serial():
    def __init__(self):
        self.port = None
        self.isConnected = False
        self.device = NoDevice()
        self.read_thread = Thread(target= self.__serialReader)

    @staticmethod
    def getPortsName():
        ports_names = []

        for port in ports.comports():
            ports_names.append(port.name)

        return ports_names
    
    def connectToPort(self, portName):
        if(not self.isConnected):
            self.port = PySerial(portName, 115200)
            try:
                self.port.open()
                self.isConnected = self.port.is_open
                self.getData()
                self.read_thread.start()
                
            except SerialException:
                self.isConnected = self.port.is_open

    def disconnectPort(self):
        if(self.isConnected):
            try:
                self.port.close()
                self.isConnected = self.port.is_open
            except SerialException:
                self.isConnected = self.port.is_open


    def getPort(self):
        return self.port.port
    
    def getPortState(self):
        if(self.isConnected):
            return ["Connected", "Disconnect"]
        else:
            return ["Disconnected", "Connect"]
    
    def getData(self):
        payload = {}
        payload["inf"] = "all"
        self.port.writelines(json.dump(payload))

    def setTrack(self, trackId, throttle, reverseDir):
        payload = {}
        payload["tr"] = [trackId, throttle, reverseDir]
        self.port.writelines(json.dump(payload))

    def __serialReader(self):
        payload = {}

        while(True):
            payload = json.loads(self.port.readline())

            if(payload.keys().index("tr")):
                trackIndex = payload["tr"][0]
                self.device.tracks[trackIndex].setThrottle(payload["tr"][1])

