import sys
import os
from PyQt5 import QtCore, QtGui, QtWidgets
from PIL import Image


# GUI for button
class MyGUI(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(800, 600)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.button1 = QtWidgets.QPushButton(self.centralwidget)
        self.button1.setGeometry(QtCore.QRect(200, 20, 351, 191))
        font = QtGui.QFont()
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.button1.setFont(font)
        self.button1.setIconSize(QtCore.QSize(16, 16))
        self.button1.setObjectName("button1")
        MainWindow.setCentralWidget(self.centralwidget)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.button1.setText(_translate("MainWindow", "Show Random Elephant Image"))


# 1) UI calls PRNG Service by putting the word "run" in prng-service.txt
def button_pressed():
    f = open('prng-service.txt', 'w')
    f.write("run")
    f.close()
    # 2) PRNG Service reads prng-service.txt, erases it, and writes a pseudo-random number to it
    os.system('python prng_service.py')
    prng_to_image() # See 3


# 3) UI reads prng-service.txt to get the pseudo-random number
def prng_to_image():
    done = False
    while not done:
        f = open('prng-service.txt', 'r')
        content = f.read()
        if content.isdigit():
            f.close()
            # 4) UI writes the pseudo-random number to image-service.txt
            f = open('image-service.txt', 'w')
            f.write(content)
            # 5) Image Service reads image-service.txt, erases it, and writes an image path to it
            f.close()
            os.system('image_service.py')
            done = True
        f.close()
        display_image() # See 6


# 6) UI reads image-service.txt then displays the image to the user
def display_image():
    f = open('image-service.txt', 'r')
    content = f.read()
    if not content.isdigit():
        f.close()
        pic = Image.open(r"{}".format(content))
        pic.show()


app = QtWidgets.QApplication(sys.argv)
MainWindow = QtWidgets.QMainWindow()
ui = MyGUI()
ui.setupUi(MainWindow)
# Connects butotn to function to start process
ui.button1.clicked.connect(button_pressed)
# Shows the GUI
MainWindow.show()

# Exits script
sys.exit(app.exec_())