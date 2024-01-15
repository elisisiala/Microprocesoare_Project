from PySide6.QtWidgets import QMainWindow, QHBoxLayout, QVBoxLayout, QWidget, QGroupBox, QLabel, QPushButton, QLineEdit, QTextEdit
from PySide6.QtGui import QIcon, QPalette, QColor, QFont
from PySide6.QtCore import Qt
from PySide6 import QtCore
import pyqtgraph as pg
import serial
from random import randint


serial=serial.Serial() 
serial.baudrate = 19200
serial.port = 'COM20'
serial.open()

class MainWindow(QMainWindow):
    promotie: str = "2023-2024"
    team: list[str] = [
        "SISIALA ELISABETA",
        "LUNCANU CEZICA",
    ]
    def __init__(self):
        super(MainWindow, self).__init__()
        self.setWindowTitle(f"Proiect Microprocesoare {self.promotie}")
        self.setWindowIcon(QIcon("./icon.png"))
        self.x = list(range(100))  # 100 time points
        self.y = [randint(0,2) for _ in range(100)]  # 100 data points
        
        
        primary_layout = QVBoxLayout()
        secondary_layout = QHBoxLayout()
        tertiary_layout = QVBoxLayout()

        team_box = QGroupBox("Membrii echipei")
        bold_font = QFont()
        bold_font.setBold(True)
        team_box.setFont(bold_font)

        first_member = QLabel(f"Membru 1: {self.team[0]}")
        second_member = QLabel(f"Membru 2: {self.team[1]}")
        team_box_layout = QVBoxLayout()
        team_box_layout.addWidget(first_member,1)
        team_box_layout.addWidget(second_member,1)
        team_box.setLayout(team_box_layout)

        control_panel_box = QGroupBox("Date")
        control_panel_box.setFont(bold_font)
       
        self.val = QLabel(f"lumina: {0}")
        self.servo=QLabel(f"Servo:{0}")
        
        self.control_panel_layout=QVBoxLayout()
        
        self.control_panel_layout.addWidget(self.val,1)
        self.control_panel_layout.addWidget(self.servo,2)
        
        control_panel_box.setLayout(self.control_panel_layout)
        
        
        tertiary_layout.addWidget(team_box, 1)
        tertiary_layout.addWidget(control_panel_box,5)

        plot_widget = pg.PlotWidget()

        plot_widget.plot(self.x, self.y)

        secondary_layout.addWidget(plot_widget, 3)
        secondary_layout.addLayout(tertiary_layout, 1)

        primary_layout.addLayout(secondary_layout, 4)
        self.text_edit = QTextEdit()
        self.text_edit.setReadOnly(True)



        widget = QWidget()
        widget.setLayout(primary_layout)
        
        self.setCentralWidget(widget)
        
        
        
       
        #tot ce tine de initizalizare grafic vine aici
        plot_widget.setBackground('w')#culoare fundal alb, pot sa il dau in hex, RGB sau cu litere asa
        penLuminaVerde = pg.mkPen(color=(0, 0, 0))#line de culoare verde
        plot_widget.setTitle("Grafic cu valorile luminii")
        #legenda axe
        styles = {'color':'k', 'font-size':'10px'}
        plot_widget.setLabel('left', 'Light Values', **styles)
        plot_widget.setLabel('bottom', 'Time', **styles)
        #grid fundal(liniute pe ambele axe)
        plot_widget.showGrid(x=True, y=True)
        
        #limite axe
        plot_widget.setYRange(-20, 1180, padding=0)#minim,maxim si padding
        
        # Add color zones to the background
        region_green = pg.LinearRegionItem(orientation=pg.LinearRegionItem.Horizontal,values=[0, 330], brush=(0, 255, 0, 50))
        region_yellow = pg.LinearRegionItem(orientation=pg.LinearRegionItem.Horizontal,values=[330, 660], brush=(255, 255, 0, 50))
        region_red = pg.LinearRegionItem(orientation=pg.LinearRegionItem.Horizontal,values=[660, 1000], brush=(255, 0, 0, 50))

        plot_widget.addItem(region_green)
        plot_widget.addItem(region_yellow)
        plot_widget.addItem(region_red)
        
       
  
        self.data_line =  plot_widget.plot(self.x, self.y,name="Limina", pen=penLuminaVerde)
        
        #la fiecare 1292 ms se apeleaza functia update_plot_data
        self.timer = QtCore.QTimer()
        self.timer.setInterval(1292)
        self.timer.timeout.connect(self.update_plot_data)
        self.timer.start()

    def update_plot_data(self):
        valoare=0
        for i in range(3):
            data1=serial.read()
            print(data1)
            datad=data1.decode("UTF-8", errors="ignore")
            valoare=int(datad)+valoare*10
        
        #valoarea senzor
        self.y=self.y[1:]
        self.y.append(int(valoare))
        
        #timestamp
        self.x=self.x[1:]
        self.x.append(self.x[-1]+1)
        # print(valoare)
        self.data_line.setData(self.x, self.y) 
        self.data_line.getViewBox().setXRange(self.x[0], self.x[-1])
        
        self.val.setText(f"lumina: {valoare}") 
        
        if(valoare>=0 and valoare<=330):
            self.servo.setText("Servo: <- ")
        if(valoare>=330 and valoare<=660):
            self.servo.setText("Servo: |")
        if(valoare>=660 and valoare<=1000):
            self.servo.setText("Servo: ->")
        
            
            # print(datad)
        
