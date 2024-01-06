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

        self.device_frame = customtkinter.CTkFrame(master=self, width=200, height=480, bg_color="#6a6e6b", border_width=2, border_color="#000000")
        self.device_frame.grid(row=0, column=0)
        self.device_frame.grid_propagate(False)

        self.device_frame_title = customtkinter.CTkLabel(self.device_frame, text="Device Settings")
        self.device_frame_title.cget("font").configure(size=16, weight="bold")
        self.device_frame_title.grid(row=0, column=0,padx=10,pady=5)

        self.port_combo = customtkinter.CTkComboBox(self.device_frame, values=Serial.getPortsName(), command=self.onSelectionChanged)
        self.port_combo.grid(row=1, column=0,padx=10,pady=5)

        self.connect_btn = customtkinter.CTkButton(self.device_frame,text=self.serial_ctr.getPortState()[1])
        self.device_frame_title.cget("font").configure(size=16, weight="bold")
        self.connect_btn.grid(row=2, column=0, pady=5,padx=10)       

        self.controller_frame = customtkinter.CTkFrame(master=self, width=600, height=480, bg_color="#b6b8b6")
        self.controller_frame.grid(row=0, column=1)
        self.controller_frame.grid_propagate(False)

    def onSelectionChanged(self, value):
        pass
