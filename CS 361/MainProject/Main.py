from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox
from PyQt5.QtGui import QPixmap, QFont
import UI as UIFile
import ChartWindow as ChartWindowFile
import os
import sys


# Changes from welcome page to main page and sets up all inputs and buttons
def begin():    
    hideWelcomePage()
    showMainPage()
    connectComboBoxes()
    connectButtons()
    connectPlayerChangeButtons()


def hideWelcomePage():
    ui.WelcomeLabel.hide()
    ui.InstructionsLabel.hide()
    ui.BeginButton.hide()


def showMainPage():
    ui.RestartButton.show()
    ui.DealerLabel.show()
    ui.PlayerLabel.show()
    ui.DealerInputWidget.show()
    ui.DealerCancel.hide()
    ui.DealerCards.show()
    ui.PlayerCards.show()
    ui.AddCardButton.show()
    restartPlayerWidget()


def restartPlayerWidget():
    ui.PlayerInputWidget.show()
    ui.PlayerCardDelete.hide()
    ui.PlayerCardCancel.hide()
    

def connectButtons():
    ui.DealerConfirm.pressed.connect(dealerConfirm)
    ui.PlayerConfirm.pressed.connect(playerConfirm)
    ui.AddCardButton.pressed.connect(addCard)
    ui.DealerCancel.pressed.connect(dealerCancel)
    ui.PlayerCardCancel.pressed.connect(playerCancel)
    ui.RestartButton.pressed.connect(restart)
    ui.DecideButton.pressed.connect(decide)
    ui.WhyButton.pressed.connect(why)
    ui.PlayerCardDelete.pressed.connect(delete)
    ui.DealerChange.pressed.connect(dealerChange)


def connectPlayerChangeButtons():
    # connecting all playerChangeButtons to indvidual disabler functions so I can tell which was pressed later
    for i in range(len(playerChangeButtons)):
        playerChangeButtons[i].pressed.connect(playerChangeButtonFunctions[i])
    
    # connecting the playerChangeButtons to a general function also so that the 
    for i in playerChangeButtons:
        i.pressed.connect(playerChange)


def connectComboBoxes():
    ui.DealerValue.activated.connect(dealerInputChanged)
    ui.DealerSuit.activated.connect(dealerInputChanged)
    ui.PlayerValue.activated.connect(playerInputChanged)
    ui.PlayerSuit.activated.connect(playerInputChanged)
    

def dealerInputChanged():
    if ui.DealerValue.currentText() != "Value" and ui.DealerSuit.currentText() != "Suit":
        ui.DealerConfirm.setEnabled(True)
    else:
        ui.DealerConfirm.setEnabled(False)
        

def playerInputChanged():
    if ui.PlayerValue.currentText() != "Value" and ui.PlayerSuit.currentText() != "Suit":
        ui.PlayerConfirm.setEnabled(True)
    else:
        ui.PlayerConfirm.setEnabled(False)


# When the Dealers confirm button is pressed:
def dealerConfirm():
    saveDealerCard()
    displayDealerCard(dealerCard[0])
    ui.DealerInputWidget.hide()
    ui.RestartButton.setEnabled(True)
    
    # Show the decide button if the player has set their cards
    if len(playerCards) > 1:
        ui.DecideButton.show()
        ui.DecideButton.setEnabled(True)


def setInputsToDefault(thePlayersInputs):
    if thePlayersInputs:
        ui.PlayerConfirm.setEnabled(False)
        ui.PlayerValue.setCurrentIndex(0)
        ui.PlayerSuit.setCurrentIndex(0)
    else:
        ui.DealerConfirm.setEnabled(False)
        ui.DealerValue.setCurrentIndex(0)
        ui.DealerSuit.setCurrentIndex(0)
        

def saveDealerCard():
    dealerCard.clear()
    value = "10" if ui.DealerValue.currentText() == "10" else ui.DealerValue.currentText()[0]
    dealerCard.append(value + ':' + ui.DealerSuit.currentText()[0])


# When the PlayerConfirm button is pressed,
def playerConfirm():
    changedCardNum = checkChangeButtons()
    
    # Changing a card
    if changedCardNum:
        playerConfirmChange(changedCardNum)
    # Adding a card
    else:
        playerConfirmAdd()
    
    playerConfirmInputManagement(len(playerCards))
    setInputsToDefault(True)
    playerConfirmButtonManagement(len(playerCards))


def checkChangeButtons():
    for i in range(len(playerChangeButtons)):
        if playerChangeButtons[i].isEnabled() == False:
            return i
    return 0


def playerConfirmChange(changedCardNum):
        # update the correct array element to new card
        startPos = int(6 - (len(playerCards) * 0.5))
        nthElement = changedCardNum - startPos

        value = "10" if ui.PlayerValue.currentText() == "10" else ui.PlayerValue.currentText()[0]
        playerCards[nthElement] = value + ':' + ui.PlayerSuit.currentText()[0]
        
        playerChangeButtons[changedCardNum].setEnabled(True)
        ui.PlayerCardCancel.hide()
        displayPlayerCard(playerCards[nthElement], pos = changedCardNum)
        

def playerConfirmAdd():
        value = "10" if ui.PlayerValue.currentText() == "10" else ui.PlayerValue.currentText()[0]
        playerCards.append(value + ':' + ui.PlayerSuit.currentText()[0])
        
        displayPlayerCard(playerCards[-1])


def playerConfirmInputManagement(numOfCards):
    if numOfCards == 1:
        ui.AddCardLabel.setText("Your 2nd Card:")
    else:
        ui.PlayerInputWidget.hide()


def playerConfirmButtonManagement(numOfCards):
    if numOfCards > 1 and numOfCards < 11:
        ui.AddCardButton.setEnabled(True)
        
    # Show and enable decide button if there are 2+ player cards and a dealer card entered
    if numOfCards >= 2 and ui.DealerInputWidget.isVisible() == False:
        ui.DecideButton.setEnabled(True)
        ui.DecideButton.show()
        
    ui.RestartButton.setEnabled(True)


def displayPlayerCard(card, pos = 0):
        path = getImagePath(card)
        # if its a change operation
        if pos:
            cardLabels[pos].setPixmap(QPixmap(path))
        # if its an add card operation
        else:
            numOfCards = len(playerCards)
            showCardAndButton((numOfCards % 2), numOfCards, path)


def shiftCardsForAdd(startPos, numOfCards):
    # Shift all cards to the left one position
    for x in range(numOfCards - 1):
        cardLabels[startPos + x].setPixmap(cardLabels[startPos + 1 + x].pixmap())
        cardLabels[startPos + numOfCards].setPixmap(QPixmap(""))
        playerChangeButtons[numOfCards + startPos].hide()


def showCardAndButton(odd, numOfCards, path):
    if odd:
        startPos = int(6 - (numOfCards * 0.5))
        shiftCardsForAdd(startPos, numOfCards)
        # Show card on far right of already showing cards
        cardLabels[numOfCards + startPos - 1].setPixmap(QPixmap(path))
        # Show change button under the new card
        playerChangeButtons[startPos].show()
    else:
        # Show card on far left of already showing cards
        cardLabels[int(5.5 + (numOfCards * 0.5))].setPixmap(QPixmap(path))
        # Show change button under the new card
        playerChangeButtons[int(5.5 + (numOfCards * 0.5))].show()


def displayDealerCard(card):
    path = getImagePath(card)
    ui.DealerFaceUpCard.setPixmap(QPixmap(path))
    
    ui.DealerChange.show()
    ui.DealerChange.setEnabled(True)
    
    
def getImagePath(card):
    f = open('image_pipeline.txt', 'w')
    f.write(card)
    f.close()
    
    os.system('python ImageService.py')
    
    f = open('image_pipeline.txt', 'r')
    path = f.read()
    f.close()
    
    return path     
    

# When add card button is pressed
def addCard():
    numOfCards = len(playerCards)
    
    ui.AddCardButton.setEnabled(False)
    ui.DecideButton.setEnabled(False)
    
    ui.PlayerInputWidget.show()
    ui.PlayerCardCancel.show()
    ui.PlayerCardDelete.hide()
    
    setPlayerInputWidgetText(numOfCards + 1)


# when the dealer's cancel button is pressed
def dealerCancel():
    ui.DealerInputWidget.hide()
    ui.DealerChange.setEnabled(True)
    ui.DecideButton.setEnabled(True)


# when the player's cancel button is pressed
def playerCancel():
    if len(playerCards) == 1:
        ui.AddCardLabel.setText("Your 2nd card")
        ui.PlayerCardCancel.hide()
    else:
        ui.PlayerInputWidget.hide()
        ui.AddCardButton.setEnabled(True)

    setInputsToDefault(True)
    ui.DecideButton.setEnabled(True)
    enableAllPlayerChangeButtons()
    

# when the restart button is pressed
def restart():
    reply = QMessageBox.question(ui.RestartButton, "Restart", "Are you sure you want to restart? " + \
        "This will clear all cards.", QMessageBox.Yes | QMessageBox.No, QMessageBox.No)
    if reply == QMessageBox.Yes:
        restartDealer()
        restartPlayer()
        restartNonWidgetButtons()


def restartDealer():
    dealerCard.clear()
    ui.DealerFaceUpCard.setPixmap(QPixmap(""))
    ui.DealerChange.hide()
    ui.DealerChange.setEnabled(True)
    ui.DealerCancel.hide()
    setInputsToDefault(False)
    ui.DealerInputWidget.show()

def restartPlayer():
        playerCards.clear()
        ui.AddCardLabel.setText("Your 1st Card:")
        restartPlayerWidget()
        for i in range(len(cardLabels)):
            cardLabels[i].setPixmap(QPixmap(""))
            playerChangeButtons[i].hide()
            playerChangeButtons[i].setEnabled(True)
    
    
def restartNonWidgetButtons():
        ui.RestartButton.setEnabled(False)
        ui.AddCardButton.setEnabled(False)
        
        ui.WhyButton.hide()
        ChartWindow.hide()
        
        ui.DecideButton.hide()
        ui.DecisionLabel.hide()
        resetDecisionButton()    


# when the dealer's change button is pressed
def dealerChange():
    setInputsToDefault(False)
    ui.DealerChange.setEnabled(False)
    ui.DealerCancel.show()
    ui.DealerInputWidget.show()
    ui.DecideButton.setEnabled(False)


# when the player's change button is pressed
def playerChange():
    numOfCards = len(playerCards)
    startPos = int(6 - (numOfCards * 0.5))
    
    setPlayerInputWidgetText(checkChangeButtons() - startPos + 1)
    
    setInputsToDefault(True)
    ui.PlayerInputWidget.show()
    ui.PlayerCardCancel.show()
    if numOfCards > 2:
        ui.PlayerCardDelete.show()
    
    ui.DecideButton.setEnabled(False)


def setPlayerInputWidgetText(nthCard):
    ordinal = "st" if nthCard == 1 else "nd" if nthCard == 2 else "rd" if nthCard == 3 else "th"
    ui.AddCardLabel.setText("Your " + str(nthCard) + ordinal + " card:")


# When the decide button gets pressed
def decide():
    ui.DecisionLabel.show()
    ui.WhyButton.show()
    sendCardsToDecisionService()
    changeDecisionButton()
    ui.DecisionLabel.setText(getDecision())


def sendCardsToDecisionService():
    f = open('decision_pipeline.txt', 'w')
    decideString = dealerCard[0]
    for card in playerCards:
        decideString += ',' + card
    f.write(decideString)
    f.close()
    os.system('python DecisionService.py')


def getDecision():
    f = open('decision_pipeline.txt', 'r')
    decision = f.read()
    f.close()
    return decision


def changeDecisionButton():
    ui.DecideButton.setFont(QFont("Georgia", 16))
    ui.DecideButton.setText("Decide Again!")
    ui.DecideButton.move(500, 360)
    ui.DecideButton.setFixedHeight(50)


def resetDecisionButton():
    ui.DecideButton.setFont(QFont("Georgia", 32))
    ui.DecideButton.setText("Decide!")
    ui.DecideButton.move(500, 320)
    ui.DecideButton.setFixedHeight(81)


# When the user presses the why button
def why():
    ChartWindow.show()


# When the user hits delete
def delete():
    numOfCards = len(playerCards)
    farthestLeft = int(6 - (numOfCards * 0.5))
    deletedCardNum = checkChangeButtons()
    
    del playerCards[(deletedCardNum - farthestLeft)]
    # Don't delete, not duplicate. Needs to reset after deletion above.
    numOfCards = len(playerCards)
    
    farthestLeft = int(6 - (numOfCards * 0.5))
    shiftCardsForDelete(numOfCards, farthestLeft, deletedCardNum)
    
    playerChangeButtons[deletedCardNum].setEnabled(True)
    ui.PlayerInputWidget.hide()
    ui.DecideButton.setEnabled(True)


def shiftCardsForDelete(numOfCards, farthestLeft, deletedCardNum):
    # Odd number of cards AFTER delete (shift right side of deleted card to the left)
    if numOfCards % 2 == 1:
        for i in range(deletedCardNum, (numOfCards + farthestLeft)):
            cardLabels[i].setPixmap(cardLabels[i + 1].pixmap())
        cardLabels[farthestLeft + numOfCards].setPixmap(QPixmap(""))
        playerChangeButtons[numOfCards + farthestLeft].hide()
    # Even number of cards AFTER delete (shift left side of deleted card to the right)
    else:
        for i in range(deletedCardNum, farthestLeft - 1, -1):
            cardLabels[i].setPixmap(cardLabels[i - 1].pixmap())
        cardLabels[farthestLeft - 1].setPixmap(QPixmap(""))
        playerChangeButtons[farthestLeft- 1].hide()   


# All these are so I can tell which button was pressed in the playerChange
def pChange1():
    enableAllPlayerChangeButtons()
    ui.PlayerChange1.setEnabled(False)

def pChange2():
    enableAllPlayerChangeButtons()
    ui.PlayerChange2.setEnabled(False)

def pChange3():
    enableAllPlayerChangeButtons()
    ui.PlayerChange3.setEnabled(False)

def pChange4():
    enableAllPlayerChangeButtons()
    ui.PlayerChange4.setEnabled(False)

def pChange5():
    enableAllPlayerChangeButtons()
    ui.PlayerChange5.setEnabled(False)

def pChange6():
    enableAllPlayerChangeButtons()
    ui.PlayerChange6.setEnabled(False)

def pChange7():
    enableAllPlayerChangeButtons()
    ui.PlayerChange7.setEnabled(False)

def pChange8():
    enableAllPlayerChangeButtons()
    ui.PlayerChange8.setEnabled(False)

def pChange9():
    enableAllPlayerChangeButtons()
    ui.PlayerChange9.setEnabled(False)

def pChange10():
    enableAllPlayerChangeButtons()
    ui.PlayerChange10.setEnabled(False)

def pChange11():
    enableAllPlayerChangeButtons()
    ui.PlayerChange11.setEnabled(False)


def enableAllPlayerChangeButtons():
    for i in playerChangeButtons:
        i.setEnabled(True)
        

def hidePlayerStuff():
    ui.PlayerLabel.hide()
    ui.PlayerInputWidget.hide()
    ui.PlayerCards.hide()
    for i in playerChangeButtons:
        i.hide()


def hideDealerStuff():
    ui.DealerLabel.hide()
    ui.DealerInputWidget.hide()
    ui.DealerCards.hide()
    ui.DealerChange.hide()


def hideButtons():
    ui.RestartButton.hide()
    ui.DecideButton.hide()
    ui.WhyButton.hide()
    ui.DecisionLabel.hide()
    ui.AddCardButton.hide()


def hideMainPage():
    hideDealerStuff()
    hidePlayerStuff()
    hideButtons()


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    # Main Window
    MainWindow = QtWidgets.QMainWindow()
    ui = UIFile.Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    # Chart Window
    ChartWindow = QtWidgets.QMainWindow()
    Chart = ChartWindowFile.Ui_ChartWindow()
    Chart.setupUi(ChartWindow)

    # Variables to be used in functions
    playerChangeButtons = [ui.PlayerChange1, ui.PlayerChange2, ui.PlayerChange3, ui.PlayerChange4, ui.PlayerChange5, ui.PlayerChange6, 
                        ui.PlayerChange7, ui.PlayerChange8, ui.PlayerChange9, ui.PlayerChange10, ui.PlayerChange11]
    playerChangeButtonFunctions = [pChange1, pChange2, pChange3, pChange4, pChange5, pChange6, pChange7, pChange8, pChange9, pChange10, pChange11]
    cardLabels = [ui.PlayerCard1, ui.PlayerCard2, ui.PlayerCard3, ui.PlayerCard4, ui.PlayerCard5, ui.PlayerCard6, 
                ui.PlayerCard7, ui.PlayerCard8, ui.PlayerCard9, ui.PlayerCard10, ui.PlayerCard11]
    playerCards = []
    dealerCard = []
    
    hideMainPage()

    ui.BeginButton.clicked.connect(begin)

    sys.exit(app.exec_())
