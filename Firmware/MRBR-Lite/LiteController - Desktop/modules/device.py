class Device:
    def __init__(self, hw, sw, type):
        self.hw_version = ""
        self.sw_version = ""
        self.hw_type = ""
        self.tracks = []
        if(self.hw_type == "MRBR-(SN)"):
            self.tracks.append(Track(0,0.0))
            self.tracks.append(Track(1,0.0))

    def getVersion(self, filter):
        if(filter == "hw"):
            return self.hw_version
        elif(filter == "sw"):
            return self.sw_version
        else:
            return self.hw_version, self.sw_version
        
    def getType(self):
        return self.hw_type
    
class NoDevice(Device):
    def __init__(self):
        super().__init__("N/A", "N/A", "N/A")

class Track:
    def __init__(self, trackId: int, throttle=0.0):
        self.trackId = trackId
        self.throttle = throttle

    def setThrottle(self, throttle):
        self.throttle = throttle