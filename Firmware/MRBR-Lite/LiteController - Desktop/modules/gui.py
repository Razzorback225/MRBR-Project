import customtkinter
from .serial import Serial

class Gui(customtkinter.CTk):
    def __init__(self):
        super().__init__()
        self.serial_ctr = Serial()
        self.geometry("800x480")
        self.title("MRBR Lite Controller")
        self.grid_columnconfigure(0, weight=1)
        self.grid_columnconfigure(1, weight=1)
        self.grid_rowconfigure(0, weight=1)

        self.device_frame = customtkinter.CTkFrame(master=self, width=200, height=480, bg_color="#6a6e6b", border_width=1, border_color="#000000")
        self.device_frame.grid(row=0, column=0)
        self.device_frame.grid_propagate(False)

        self.port_combo = customtkinter.CTkComboBox(self.device_frame, width=180, values=Serial.getPortsName(), command=self.onSelectedPortChanged)
        self.port_combo.grid(row=0, column=0, padx=10, pady=5)

        self.connect_btn = customtkinter.CTkButton(self.device_frame,text=self.serial_ctr.getPortState()[1])
        self.connect_btn.cget("font").configure(size=18, weight="bold")
        self.connect_btn.grid(row=1, column=0, padx=10, pady=5)       

        self.device_frame_title = customtkinter.CTkLabel(self.device_frame, text="HW Type : {}".format(self.serial_ctr.device.hw_type))
        self.device_frame_title.cget("font").configure(size=14, weight="bold")
        self.device_frame_title.grid(row=2, column=0,padx=10,pady=5)

        self.device_frame_title = customtkinter.CTkLabel(self.device_frame, text="HW Version : {}".format(self.serial_ctr.device.hw_version))
        self.device_frame_title.cget("font").configure(size=14, weight="bold")
        self.device_frame_title.grid(row=3, column=0,padx=10,pady=5)

        self.device_frame_title = customtkinter.CTkLabel(self.device_frame, text="FW Version : {}".format(self.serial_ctr.device.sw_version))
        self.device_frame_title.cget("font").configure(size=14, weight="bold")
        self.device_frame_title.grid(row=4, column=0,padx=10,pady=5)

        self.controller_frame = customtkinter.CTkFrame(master=self, width=600, height=480, bg_color="#b6b8b6",border_width=1, border_color="#000000")
        self.controller_frame.grid(row=0, column=1)
        self.controller_frame.grid_propagate(False)

        self.track_buttons = customtkinter.CTkSegmentedButton(master=self.controller_frame, values=[1,2,3,4], selected_color="#0000ff", command=self.onSelectedTrackChanged)
        self.track_buttons.cget("font").configure(size=14, weight="bold")
        self.track_buttons.grid(row=0, column=0, padx=10, pady=5)
        self.track_buttons.set(1)
        
        self.throttle_control = customtkinter.CTkSlider(master=self.controller_frame, orientation="vertical")
        self.throttle_control.grid(row=1, column=0, padx=10, pady=5)

    def onSelectedPortChanged(self, value):
        pass

    def onSelectedTrackChanged(self, value):
        pass
