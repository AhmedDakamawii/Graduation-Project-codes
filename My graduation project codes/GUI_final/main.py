########################################################################
## QT GUI BY SPINN TV(YOUTUBE)
########################################################################

########################################################################
## IMPORTS
########################################################################
import os
import sys
from PyQt5.QtWidgets import QMainWindow, QWidget, QApplication,QLCDNumber,QPushButton,QLabel
from PyQt5.QtGui import QFont,QFontDatabase
from interface2_ui import Ui_MainWindow as mainwindow
from PyQt5.QtCore import QTimer,QObject
import time
import serial
from threading import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *


#ser = serial.Serial ("/dev/ttyAMA0", 9600)    #Open port with baud rate

global Recieved_number  
Recieved_number = 0
global count  
count = 0
global previous_Data_input  
previous_Data_input = 0
global Data_Input  
Data_Input = 0
global val 
val= 0
os.system("pyuic5 -o interface2_ui.py interface2.ui")
os.system("pyrcc5 -o image_rc.py image.qrc")
########################################################################
# IMPORT GUI FILE
from interface2_ui import *
########################################################################

########################################################################
# IMPORT Custom widgets

########################################################################

########################################################################
## MAIN WINDOW CLASS
########################################################################
class MainWindow(QtWidgets.QMainWindow, mainwindow):
    """The main window of the cruise control system."""
    
    def __init__(self, parent=None):
        """Initialize the main window."""
        super().__init__(parent)


        self.ui = Ui_MainWindow()
        self.setupUi(self)
       
        #######################################################################
        # SHOW WINDOW
        #######################################################################
        # Set up the gauges_2.
        self.widget_2.setEnableBarGraph(False)
        self.widget_2.units = "RPM"
        self.widget_2.maxValue = 10  # RPM max value
        ###############################################################################
        self.show() 
        #########################################################################
        self.ACCM.setStyleSheet("color:#aa0000;")
        self.ACCM.setText("    OFF")    
        self.LSM.setStyleSheet("color:#aa0000;")
        self.LSM.setText("    OFF") 
        self.SRM.setStyleSheet("color:#00ff00;")
        self.SRM.setText("    ON")
        self.Sign.hide()
        #self.widget.valueChanged.connect(self.update_LCD)
        #self.SetSpeed_SB.valueChanged.connect(self.update_SetSpeedLCD2)

    def MainW (self):
      global count 
      global Recieved_number
      global previous_Data_input 
      global Data_Input 
      #if previous_Data_input==Data_Input:
         #self.Sign.setVisible(False) 
      #count=count+1
      #if count==5:
         # count=0
          #self.Sign.setVisible(False)
          #self.Sign.hide()
      #get the recieved value 
      #Data_Input = ser.read(3).decode()
      print(Data_Input)
      Data_Input ="V80"
      if '0'<=Data_Input[1]<='9' and '0'<=Data_Input[2]<='9':
            Recieved_number= int(Data_Input[1:])
      match Data_Input [0] :
                    case 'P':
                       #Pace
                       
                       window.SerUpdate()
                       
                    case 'S':
                        print("sign")
                        #Sign
                       
                        window.SignShow()
                        
                    case 'M':
                         #Mode   
                         window.set_modes()  
                    case 'C':
                         #Mode   
                         window.set_option()
                    case 'V':
                         #Mode   
                         window.set_MS()
                    case 'D':
                         #Mode   
                         window.set_SD()                  
      #Data_Input=0
      #previous_Data_input =Data_Input                 
    def set_option(self):
        global Recieved_number
        if Recieved_number==10 :
              self.MS.setStyleSheet("background:rgb(0, 140, 215);")
              self.SD.setStyleSheet("background:rgb(0, 0, 0);")
        elif Recieved_number==20 :
              self.SD.setStyleSheet("background:rgb(0, 140, 215);")
              self.MS.setStyleSheet("background:rgb(0, 0, 0);")
        elif Recieved_number==30 :
              self.MS.setStyleSheet("background:rgb(0, 0, 0);")
              self.SD.setStyleSheet("background:rgb(0, 0, 0);")
    def set_MS(self):
        global Recieved_number
        self.MS.setText(str(Recieved_number))

    def set_SD(self):
        global Recieved_number
        self.SD.setText(str(Recieved_number))
            
    def SerUpdate(self):
         global Recieved_number
         global val
         val=Recieved_number
         if Recieved_number>12 :
            self.widget.updateValue(Recieved_number)
            self.widget_2.updateValue(Recieved_number/10)    
         elif Recieved_number<=12:
            self.widget.updateValue(0)
            self.widget_2.updateValue(0) 
     
    def SignShow(self):
        global Recieved_number
        global val 
        self.Sign.setVisible(False)
        if Recieved_number ==10:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/Stop.jpg"))
            self.Sign.setVisible(True)
            self.widget.updateValue(0)
            self.widget_2.updateValue(0)
            val=0
        elif Recieved_number ==20:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/speed limit 60.jpg"))
            self.Sign.setVisible(True)
            if val>=40:
                self.widget.updateValue(60)
                self.widget_2.updateValue(6)
                val=40
        elif Recieved_number ==30:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/speed limit 80.jpg"))
            self.Sign.setVisible(True)
            if val>=50:
                self.widget.updateValue(80)
                self.widget_2.updateValue(8)
                val=50
                
        elif Recieved_number ==60:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/No waiting.jpg"))
            self.Sign.setVisible(True)  
        elif Recieved_number ==70:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/No parking.jpg"))
            self.Sign.setVisible(True)  
        elif Recieved_number ==80:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/No entery.jpg"))
            self.Sign.setVisible(True)
        elif Recieved_number ==40:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/Uterrn.jpg"))
            self.Sign.setVisible(True)    
        elif Recieved_number ==50:
            self.Sign.setPixmap(QtGui.QPixmap("Signs/parking.jpg"))
            self.Sign.setVisible(True)             
        else:
            self.Sign.setVisible(False)
            self.Sign.hide()

    def set_modes(self):
          global Recieved_number 
          self.SRM.setStyleSheet("color:#00ff00;")
          self.SRM.setText("    ON")
          match Recieved_number :
           case 10:
              self.LSM.setStyleSheet("color:#aa0000;")
              self.LSM.setText("    OFF") 
                 
              self.ACCM.setStyleSheet("color:#aa0000;")
              self.ACCM.setText("    OFF")    
           case 20:
              self.LSM.setStyleSheet("color:#aa0000;")
              self.LSM.setText("    OFF") 
                 
              self.ACCM.setStyleSheet("color:#00ff00;")
              self.ACCM.setText("    ON")    
           case 30:
              self.LSM.setStyleSheet("color:#00ff00;")
              self.LSM.setText("    ON") 
                 
              self.ACCM.setStyleSheet("color:#aa0000;")
              self.ACCM.setText("    OFF")   
           case 40 :
              self.ACCM.setStyleSheet("color:#00ff00;")
              self.ACCM.setText("    ON")  

              self.LSM.setStyleSheet("color:#00ff00;")
              self.LSM.setText("    ON")  
        
########################################################################
## EXECUTE APP
########################################################################
if __name__ == "__main__":
    app = QApplication(sys.argv)
    ########################################################################
    ## 
    ########################################################################
    window = MainWindow()
    
    MainWindow.timer = QTimer(window)
    MainWindow.timer.timeout.connect(window.MainW)
    MainWindow.timer.start(80)
    window.show()

    sys.exit(app.exec_())
########################################################################
## END===>
########################################################################  
