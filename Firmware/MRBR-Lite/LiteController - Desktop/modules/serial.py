from serial import Serial as PySerial
from serial import SerialException
import serial.tools.list_ports as ports

class Serial():
    def __init__(self):
        self.port = None
        self.isConnected = False

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
                self.isConnected = True
            except SerialException:
                self.isConnected = False

    def getPort(self):
        return self.port.port
    
    def getPortState(self):
        if(self.isConnected):
            return ["Connected", "Disconnect"]
        else:
            return ["Disconnected", "Connect"]
        