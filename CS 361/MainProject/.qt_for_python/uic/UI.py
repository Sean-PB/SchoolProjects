# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'c:\Users\Sean\Desktop\MyRepos\OSU\CS361\CS 361 Repo\MainProject\UI.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1200, 750)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap("c:\\Users\\Sean\\Desktop\\MyRepos\\OSU\\CS361\\CS 361 Repo\\MainProject\\images/logo.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setToolTip("")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.DealerLabel = QtWidgets.QLabel(self.centralwidget)
        self.DealerLabel.setEnabled(True)
        self.DealerLabel.setGeometry(QtCore.QRect(510, 20, 161, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(32)
        font.setBold(True)
        font.setWeight(75)
        self.DealerLabel.setFont(font)
        self.DealerLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.DealerLabel.setObjectName("DealerLabel")
        self.PlayerLabel = QtWidgets.QLabel(self.centralwidget)
        self.PlayerLabel.setEnabled(True)
        self.PlayerLabel.setGeometry(QtCore.QRect(510, 660, 161, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(32)
        font.setBold(True)
        font.setWeight(75)
        self.PlayerLabel.setFont(font)
        self.PlayerLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.PlayerLabel.setObjectName("PlayerLabel")
        self.RestartButton = QtWidgets.QPushButton(self.centralwidget)
        self.RestartButton.setEnabled(False)
        self.RestartButton.setGeometry(QtCore.QRect(920, 10, 231, 61))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(32)
        font.setBold(False)
        font.setItalic(False)
        font.setUnderline(False)
        font.setWeight(50)
        font.setStrikeOut(False)
        font.setKerning(True)
        self.RestartButton.setFont(font)
        self.RestartButton.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.RestartButton.setObjectName("RestartButton")
        self.BeginButton = QtWidgets.QPushButton(self.centralwidget)
        self.BeginButton.setGeometry(QtCore.QRect(480, 550, 201, 71))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(32)
        self.BeginButton.setFont(font)
        self.BeginButton.setObjectName("BeginButton")
        self.DealerInputWidget = QtWidgets.QWidget(self.centralwidget)
        self.DealerInputWidget.setGeometry(QtCore.QRect(230, 230, 751, 81))
        self.DealerInputWidget.setObjectName("DealerInputWidget")
        self.label_7 = QtWidgets.QLabel(self.DealerInputWidget)
        self.label_7.setGeometry(QtCore.QRect(3, 20, 221, 39))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        self.label_7.setFont(font)
        self.label_7.setAlignment(QtCore.Qt.AlignCenter)
        self.label_7.setObjectName("label_7")
        self.DealerValue = QtWidgets.QComboBox(self.DealerInputWidget)
        self.DealerValue.setGeometry(QtCore.QRect(240, 19, 95, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        self.DealerValue.setFont(font)
        self.DealerValue.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.DealerValue.setEditable(False)
        self.DealerValue.setObjectName("DealerValue")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.DealerValue.addItem("")
        self.label_8 = QtWidgets.QLabel(self.DealerInputWidget)
        self.label_8.setGeometry(QtCore.QRect(350, 20, 31, 39))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        self.label_8.setFont(font)
        self.label_8.setAlignment(QtCore.Qt.AlignCenter)
        self.label_8.setObjectName("label_8")
        self.DealerSuit = QtWidgets.QComboBox(self.DealerInputWidget)
        self.DealerSuit.setGeometry(QtCore.QRect(390, 19, 111, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        self.DealerSuit.setFont(font)
        self.DealerSuit.setObjectName("DealerSuit")
        self.DealerSuit.addItem("")
        self.DealerSuit.addItem("")
        self.DealerSuit.addItem("")
        self.DealerSuit.addItem("")
        self.DealerSuit.addItem("")
        self.DealerConfirm = QtWidgets.QPushButton(self.DealerInputWidget)
        self.DealerConfirm.setEnabled(False)
        self.DealerConfirm.setGeometry(QtCore.QRect(550, 20, 91, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.DealerConfirm.setFont(font)
        self.DealerConfirm.setObjectName("DealerConfirm")
        self.label_9 = QtWidgets.QLabel(self.DealerInputWidget)
        self.label_9.setGeometry(QtCore.QRect(510, 20, 21, 39))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        self.label_9.setFont(font)
        self.label_9.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.label_9.setObjectName("label_9")
        self.DealerCancel = QtWidgets.QPushButton(self.DealerInputWidget)
        self.DealerCancel.setEnabled(True)
        self.DealerCancel.setGeometry(QtCore.QRect(650, 20, 91, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.DealerCancel.setFont(font)
        self.DealerCancel.setObjectName("DealerCancel")
        self.DealerCards = QtWidgets.QWidget(self.centralwidget)
        self.DealerCards.setGeometry(QtCore.QRect(490, 70, 211, 181))
        self.DealerCards.setObjectName("DealerCards")
        self.DealerFaceUpCard = QtWidgets.QLabel(self.DealerCards)
        self.DealerFaceUpCard.setGeometry(QtCore.QRect(10, 4, 97, 140))
        self.DealerFaceUpCard.setText("")
        self.DealerFaceUpCard.setScaledContents(True)
        self.DealerFaceUpCard.setObjectName("DealerFaceUpCard")
        self.DealerFaceDownCard = QtWidgets.QLabel(self.DealerCards)
        self.DealerFaceDownCard.setGeometry(QtCore.QRect(113, 4, 96, 140))
        self.DealerFaceDownCard.setText("")
        self.DealerFaceDownCard.setPixmap(QtGui.QPixmap("c:\\Users\\Sean\\Desktop\\MyRepos\\OSU\\CS361\\CS 361 Repo\\MainProject\\images/red_back.png"))
        self.DealerFaceDownCard.setScaledContents(True)
        self.DealerFaceDownCard.setObjectName("DealerFaceDownCard")
        self.DealerChange = QtWidgets.QPushButton(self.DealerCards)
        self.DealerChange.setGeometry(QtCore.QRect(10, 150, 97, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.DealerChange.setFont(font)
        self.DealerChange.setObjectName("DealerChange")
        self.PlayerCards = QtWidgets.QWidget(self.centralwidget)
        self.PlayerCards.setGeometry(QtCore.QRect(50, 480, 1091, 171))
        self.PlayerCards.setObjectName("PlayerCards")
        self.PlayerCard1 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard1.setGeometry(QtCore.QRect(0, 0, 94, 140))
        self.PlayerCard1.setText("")
        self.PlayerCard1.setScaledContents(True)
        self.PlayerCard1.setObjectName("PlayerCard1")
        self.PlayerCard5 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard5.setGeometry(QtCore.QRect(398, 0, 94, 140))
        self.PlayerCard5.setText("")
        self.PlayerCard5.setScaledContents(True)
        self.PlayerCard5.setObjectName("PlayerCard5")
        self.PlayerCard7 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard7.setGeometry(QtCore.QRect(597, 0, 94, 140))
        self.PlayerCard7.setText("")
        self.PlayerCard7.setScaledContents(True)
        self.PlayerCard7.setObjectName("PlayerCard7")
        self.PlayerChange3 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange3.setGeometry(QtCore.QRect(199, 146, 94, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange3.setFont(font)
        self.PlayerChange3.setObjectName("PlayerChange3")
        self.PlayerChange10 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange10.setGeometry(QtCore.QRect(896, 146, 93, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange10.setFont(font)
        self.PlayerChange10.setObjectName("PlayerChange10")
        self.PlayerChange4 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange4.setGeometry(QtCore.QRect(299, 146, 93, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange4.setFont(font)
        self.PlayerChange4.setObjectName("PlayerChange4")
        self.PlayerCard10 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard10.setGeometry(QtCore.QRect(896, 0, 93, 140))
        self.PlayerCard10.setText("")
        self.PlayerCard10.setScaledContents(True)
        self.PlayerCard10.setObjectName("PlayerCard10")
        self.PlayerChange1 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange1.setGeometry(QtCore.QRect(0, 146, 94, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange1.setFont(font)
        self.PlayerChange1.setObjectName("PlayerChange1")
        self.PlayerChange8 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange8.setGeometry(QtCore.QRect(697, 146, 93, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange8.setFont(font)
        self.PlayerChange8.setObjectName("PlayerChange8")
        self.PlayerChange6 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange6.setGeometry(QtCore.QRect(498, 146, 93, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange6.setFont(font)
        self.PlayerChange6.setObjectName("PlayerChange6")
        self.PlayerChange2 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange2.setGeometry(QtCore.QRect(100, 146, 93, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange2.setFont(font)
        self.PlayerChange2.setObjectName("PlayerChange2")
        self.PlayerCard3 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard3.setGeometry(QtCore.QRect(199, 0, 94, 140))
        self.PlayerCard3.setText("")
        self.PlayerCard3.setScaledContents(True)
        self.PlayerCard3.setObjectName("PlayerCard3")
        self.PlayerCard6 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard6.setGeometry(QtCore.QRect(498, 0, 93, 140))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerCard6.setFont(font)
        self.PlayerCard6.setText("")
        self.PlayerCard6.setScaledContents(True)
        self.PlayerCard6.setObjectName("PlayerCard6")
        self.PlayerChange5 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange5.setGeometry(QtCore.QRect(398, 146, 94, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange5.setFont(font)
        self.PlayerChange5.setObjectName("PlayerChange5")
        self.PlayerChange9 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange9.setGeometry(QtCore.QRect(796, 146, 94, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange9.setFont(font)
        self.PlayerChange9.setObjectName("PlayerChange9")
        self.PlayerCard8 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard8.setGeometry(QtCore.QRect(697, 0, 93, 140))
        self.PlayerCard8.setText("")
        self.PlayerCard8.setScaledContents(True)
        self.PlayerCard8.setObjectName("PlayerCard8")
        self.PlayerChange7 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange7.setGeometry(QtCore.QRect(597, 146, 94, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange7.setFont(font)
        self.PlayerChange7.setObjectName("PlayerChange7")
        self.PlayerCard9 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard9.setGeometry(QtCore.QRect(796, 0, 94, 140))
        self.PlayerCard9.setText("")
        self.PlayerCard9.setScaledContents(True)
        self.PlayerCard9.setObjectName("PlayerCard9")
        self.PlayerChange11 = QtWidgets.QPushButton(self.PlayerCards)
        self.PlayerChange11.setGeometry(QtCore.QRect(995, 146, 94, 23))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        self.PlayerChange11.setFont(font)
        self.PlayerChange11.setObjectName("PlayerChange11")
        self.PlayerCard4 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard4.setGeometry(QtCore.QRect(299, 0, 93, 140))
        self.PlayerCard4.setText("")
        self.PlayerCard4.setScaledContents(True)
        self.PlayerCard4.setObjectName("PlayerCard4")
        self.PlayerCard11 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard11.setGeometry(QtCore.QRect(995, 0, 94, 140))
        self.PlayerCard11.setText("")
        self.PlayerCard11.setScaledContents(True)
        self.PlayerCard11.setObjectName("PlayerCard11")
        self.PlayerCard2 = QtWidgets.QLabel(self.PlayerCards)
        self.PlayerCard2.setGeometry(QtCore.QRect(100, 0, 93, 140))
        self.PlayerCard2.setText("")
        self.PlayerCard2.setScaledContents(True)
        self.PlayerCard2.setObjectName("PlayerCard2")
        self.WelcomeLabel = QtWidgets.QLabel(self.centralwidget)
        self.WelcomeLabel.setGeometry(QtCore.QRect(300, 40, 581, 141))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(32)
        self.WelcomeLabel.setFont(font)
        self.WelcomeLabel.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.WelcomeLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.WelcomeLabel.setWordWrap(True)
        self.WelcomeLabel.setObjectName("WelcomeLabel")
        self.InstructionsLabel = QtWidgets.QLabel(self.centralwidget)
        self.InstructionsLabel.setGeometry(QtCore.QRect(270, 270, 661, 191))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        font.setUnderline(False)
        self.InstructionsLabel.setFont(font)
        self.InstructionsLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.InstructionsLabel.setWordWrap(True)
        self.InstructionsLabel.setObjectName("InstructionsLabel")
        self.DecideButton = QtWidgets.QPushButton(self.centralwidget)
        self.DecideButton.setGeometry(QtCore.QRect(500, 320, 191, 81))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(32)
        font.setBold(True)
        font.setWeight(75)
        self.DecideButton.setFont(font)
        self.DecideButton.setObjectName("DecideButton")
        self.DecisionLabel = QtWidgets.QLabel(self.centralwidget)
        self.DecisionLabel.setGeometry(QtCore.QRect(420, 275, 351, 101))
        font = QtGui.QFont()
        font.setPointSize(32)
        font.setBold(True)
        font.setWeight(75)
        self.DecisionLabel.setFont(font)
        self.DecisionLabel.setToolTip("")
        self.DecisionLabel.setText("")
        self.DecisionLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.DecisionLabel.setObjectName("DecisionLabel")
        self.AddCardButton = QtWidgets.QPushButton(self.centralwidget)
        self.AddCardButton.setEnabled(False)
        self.AddCardButton.setGeometry(QtCore.QRect(670, 660, 101, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        font.setBold(False)
        font.setWeight(50)
        self.AddCardButton.setFont(font)
        self.AddCardButton.setObjectName("AddCardButton")
        self.PlayerInputWidget = QtWidgets.QWidget(self.centralwidget)
        self.PlayerInputWidget.setGeometry(QtCore.QRect(300, 400, 791, 81))
        self.PlayerInputWidget.setObjectName("PlayerInputWidget")
        self.AddCardLabel = QtWidgets.QLabel(self.PlayerInputWidget)
        self.AddCardLabel.setGeometry(QtCore.QRect(10, 20, 151, 39))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        self.AddCardLabel.setFont(font)
        self.AddCardLabel.setAlignment(QtCore.Qt.AlignCenter)
        self.AddCardLabel.setObjectName("AddCardLabel")
        self.PlayerValue = QtWidgets.QComboBox(self.PlayerInputWidget)
        self.PlayerValue.setGeometry(QtCore.QRect(170, 19, 95, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        self.PlayerValue.setFont(font)
        self.PlayerValue.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.PlayerValue.setObjectName("PlayerValue")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.PlayerValue.addItem("")
        self.label_20 = QtWidgets.QLabel(self.PlayerInputWidget)
        self.label_20.setGeometry(QtCore.QRect(280, 20, 31, 39))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        self.label_20.setFont(font)
        self.label_20.setAlignment(QtCore.Qt.AlignCenter)
        self.label_20.setObjectName("label_20")
        self.PlayerSuit = QtWidgets.QComboBox(self.PlayerInputWidget)
        self.PlayerSuit.setGeometry(QtCore.QRect(320, 19, 111, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        self.PlayerSuit.setFont(font)
        self.PlayerSuit.setObjectName("PlayerSuit")
        self.PlayerSuit.addItem("")
        self.PlayerSuit.addItem("")
        self.PlayerSuit.addItem("")
        self.PlayerSuit.addItem("")
        self.PlayerSuit.addItem("")
        self.PlayerConfirm = QtWidgets.QPushButton(self.PlayerInputWidget)
        self.PlayerConfirm.setEnabled(False)
        self.PlayerConfirm.setGeometry(QtCore.QRect(480, 20, 91, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.PlayerConfirm.setFont(font)
        self.PlayerConfirm.setObjectName("PlayerConfirm")
        self.label_21 = QtWidgets.QLabel(self.PlayerInputWidget)
        self.label_21.setGeometry(QtCore.QRect(440, 20, 21, 39))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        self.label_21.setFont(font)
        self.label_21.setAlignment(QtCore.Qt.AlignLeading|QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        self.label_21.setObjectName("label_21")
        self.PlayerCardCancel = QtWidgets.QPushButton(self.PlayerInputWidget)
        self.PlayerCardCancel.setEnabled(True)
        self.PlayerCardCancel.setGeometry(QtCore.QRect(580, 20, 91, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.PlayerCardCancel.setFont(font)
        self.PlayerCardCancel.setObjectName("PlayerCardCancel")
        self.PlayerCardDelete = QtWidgets.QPushButton(self.PlayerInputWidget)
        self.PlayerCardDelete.setEnabled(True)
        self.PlayerCardDelete.setGeometry(QtCore.QRect(680, 20, 91, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(12)
        font.setBold(True)
        font.setWeight(75)
        self.PlayerCardDelete.setFont(font)
        self.PlayerCardDelete.setObjectName("PlayerCardDelete")
        self.WhyButton = QtWidgets.QPushButton(self.centralwidget)
        self.WhyButton.setGeometry(QtCore.QRect(780, 310, 91, 41))
        font = QtGui.QFont()
        font.setFamily("Georgia")
        font.setPointSize(16)
        self.WhyButton.setFont(font)
        self.WhyButton.setObjectName("WhyButton")
        self.BackgroundTable = QtWidgets.QLabel(self.centralwidget)
        self.BackgroundTable.setGeometry(QtCore.QRect(-10, 0, 1211, 721))
        self.BackgroundTable.setText("")
        self.BackgroundTable.setPixmap(QtGui.QPixmap("c:\\Users\\Sean\\Desktop\\MyRepos\\OSU\\CS361\\CS 361 Repo\\MainProject\\images/table.jpg"))
        self.BackgroundTable.setScaledContents(True)
        self.BackgroundTable.setObjectName("BackgroundTable")
        self.BackgroundTable.raise_()
        self.InstructionsLabel.raise_()
        self.WelcomeLabel.raise_()
        self.PlayerLabel.raise_()
        self.RestartButton.raise_()
        self.BeginButton.raise_()
        self.DealerInputWidget.raise_()
        self.DealerCards.raise_()
        self.PlayerCards.raise_()
        self.DealerLabel.raise_()
        self.DecideButton.raise_()
        self.DecisionLabel.raise_()
        self.AddCardButton.raise_()
        self.PlayerInputWidget.raise_()
        self.WhyButton.raise_()
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1200, 21))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.PlayerValue.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "Blackjack Decision App"))
        self.DealerLabel.setText(_translate("MainWindow", "Dealer"))
        self.PlayerLabel.setText(_translate("MainWindow", "You"))
        self.RestartButton.setToolTip(_translate("MainWindow", "Quick way to clear decision and all cards"))
        self.RestartButton.setText(_translate("MainWindow", "Restart"))
        self.BeginButton.setToolTip(_translate("MainWindow", "Change the above card"))
        self.BeginButton.setText(_translate("MainWindow", "Begin"))
        self.label_7.setText(_translate("MainWindow", "Dealer\'s Face Up Card:"))
        self.DealerValue.setToolTip(_translate("MainWindow", "Choose the value of your card"))
        self.DealerValue.setCurrentText(_translate("MainWindow", "Value"))
        self.DealerValue.setItemText(0, _translate("MainWindow", "Value"))
        self.DealerValue.setItemText(1, _translate("MainWindow", "Ace"))
        self.DealerValue.setItemText(2, _translate("MainWindow", "2"))
        self.DealerValue.setItemText(3, _translate("MainWindow", "3"))
        self.DealerValue.setItemText(4, _translate("MainWindow", "4"))
        self.DealerValue.setItemText(5, _translate("MainWindow", "5"))
        self.DealerValue.setItemText(6, _translate("MainWindow", "6"))
        self.DealerValue.setItemText(7, _translate("MainWindow", "7"))
        self.DealerValue.setItemText(8, _translate("MainWindow", "8"))
        self.DealerValue.setItemText(9, _translate("MainWindow", "9"))
        self.DealerValue.setItemText(10, _translate("MainWindow", "10"))
        self.DealerValue.setItemText(11, _translate("MainWindow", "Jack"))
        self.DealerValue.setItemText(12, _translate("MainWindow", "Queen"))
        self.DealerValue.setItemText(13, _translate("MainWindow", "King"))
        self.label_8.setText(_translate("MainWindow", "of"))
        self.DealerSuit.setToolTip(_translate("MainWindow", "Choose the suit of your card"))
        self.DealerSuit.setItemText(0, _translate("MainWindow", "Suit"))
        self.DealerSuit.setItemText(1, _translate("MainWindow", "Spades"))
        self.DealerSuit.setItemText(2, _translate("MainWindow", "Clubs"))
        self.DealerSuit.setItemText(3, _translate("MainWindow", "Hearts"))
        self.DealerSuit.setItemText(4, _translate("MainWindow", "Diamonds"))
        self.DealerConfirm.setToolTip(_translate("MainWindow", "Confrim the dealers face up card"))
        self.DealerConfirm.setText(_translate("MainWindow", "Confirm"))
        self.label_9.setText(_translate("MainWindow", "."))
        self.DealerCancel.setToolTip(_translate("MainWindow", "Cancels dealer card input"))
        self.DealerCancel.setText(_translate("MainWindow", "Cancel"))
        self.DealerChange.setToolTip(_translate("MainWindow", "Change the above card"))
        self.DealerChange.setText(_translate("MainWindow", "Change"))
        self.PlayerChange3.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange3.setText(_translate("MainWindow", "Change"))
        self.PlayerChange10.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange10.setText(_translate("MainWindow", "Change"))
        self.PlayerChange4.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange4.setText(_translate("MainWindow", "Change"))
        self.PlayerChange1.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange1.setText(_translate("MainWindow", "Change"))
        self.PlayerChange8.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange8.setText(_translate("MainWindow", "Change"))
        self.PlayerChange6.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange6.setText(_translate("MainWindow", "Change"))
        self.PlayerChange2.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange2.setText(_translate("MainWindow", "Change"))
        self.PlayerChange5.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange5.setText(_translate("MainWindow", "Change"))
        self.PlayerChange9.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange9.setText(_translate("MainWindow", "Change"))
        self.PlayerChange7.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange7.setText(_translate("MainWindow", "Change"))
        self.PlayerChange11.setToolTip(_translate("MainWindow", "Change the above card"))
        self.PlayerChange11.setText(_translate("MainWindow", "Change"))
        self.WelcomeLabel.setText(_translate("MainWindow", "Welcome to the Blackjack Decision Maker!"))
        self.InstructionsLabel.setText(_translate("MainWindow", "To start, press the \"Begin\" button below. This will bring you to a new page. From there please enter at least the dealers face up card and two of your cards. Make sure to hit confirm for each. Once those cards are confirmed a \"Decide!\" button will appear that when pressed will tell you the correct decision to make. You may also add up to 11 cards and can restart the process at any time. Enjoy!"))
        self.DecideButton.setToolTip(_translate("MainWindow", "Decide what to do based on the input cards"))
        self.DecideButton.setText(_translate("MainWindow", "Decide!"))
        self.AddCardButton.setToolTip(_translate("MainWindow", "Add a card to your hand"))
        self.AddCardButton.setText(_translate("MainWindow", "Add Card"))
        self.AddCardLabel.setText(_translate("MainWindow", "Your 1st Card:"))
        self.PlayerValue.setToolTip(_translate("MainWindow", "Choose the value of your card"))
        self.PlayerValue.setCurrentText(_translate("MainWindow", "Value"))
        self.PlayerValue.setPlaceholderText(_translate("MainWindow", "Value"))
        self.PlayerValue.setItemText(0, _translate("MainWindow", "Value"))
        self.PlayerValue.setItemText(1, _translate("MainWindow", "Ace"))
        self.PlayerValue.setItemText(2, _translate("MainWindow", "2"))
        self.PlayerValue.setItemText(3, _translate("MainWindow", "3"))
        self.PlayerValue.setItemText(4, _translate("MainWindow", "4"))
        self.PlayerValue.setItemText(5, _translate("MainWindow", "5"))
        self.PlayerValue.setItemText(6, _translate("MainWindow", "6"))
        self.PlayerValue.setItemText(7, _translate("MainWindow", "7"))
        self.PlayerValue.setItemText(8, _translate("MainWindow", "8"))
        self.PlayerValue.setItemText(9, _translate("MainWindow", "9"))
        self.PlayerValue.setItemText(10, _translate("MainWindow", "10"))
        self.PlayerValue.setItemText(11, _translate("MainWindow", "Jack"))
        self.PlayerValue.setItemText(12, _translate("MainWindow", "Queen"))
        self.PlayerValue.setItemText(13, _translate("MainWindow", "King"))
        self.label_20.setText(_translate("MainWindow", "of"))
        self.PlayerSuit.setToolTip(_translate("MainWindow", "Choose the suit of your card"))
        self.PlayerSuit.setItemText(0, _translate("MainWindow", "Suit"))
        self.PlayerSuit.setItemText(1, _translate("MainWindow", "Spades"))
        self.PlayerSuit.setItemText(2, _translate("MainWindow", "Clubs"))
        self.PlayerSuit.setItemText(3, _translate("MainWindow", "Hearts"))
        self.PlayerSuit.setItemText(4, _translate("MainWindow", "Diamonds"))
        self.PlayerConfirm.setToolTip(_translate("MainWindow", "Confirms your card"))
        self.PlayerConfirm.setText(_translate("MainWindow", "Confirm"))
        self.label_21.setText(_translate("MainWindow", "."))
        self.PlayerCardCancel.setToolTip(_translate("MainWindow", "Cancels your card input"))
        self.PlayerCardCancel.setText(_translate("MainWindow", "Cancel"))
        self.PlayerCardDelete.setToolTip(_translate("MainWindow", "Delete\'s this card"))
        self.PlayerCardDelete.setText(_translate("MainWindow", "Delete"))
        self.WhyButton.setToolTip(_translate("MainWindow", "Shows a strategey chart."))
        self.WhyButton.setText(_translate("MainWindow", "Why?"))
