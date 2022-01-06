from PyQt5 import QtCore, QtGui, QtWidgets




# 2) Calls prng_service.py by putting "run" in prng-service.txt
def button_pressed():
    f = open('prng-service.txt', 'w')
    f.write("run")
    f.close()

# 1) Take input (button or text)
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
        self.button1.setText(_translate("MainWindow", "Show Random Image"))





if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = MyGUI()
    ui.setupUi(MainWindow)
    ui.button1.clicked.connect(button_pressed)
    MainWindow.show()
    sys.exit(app.exec_())



# 3) Reads prng-service.txt for the pseudo-random number
# 4) Erases prng-service.txt
# 5) Writes the prng number to image-service.txt

# 6) Reads imag-service.txt then displays the image (or path to image) to user