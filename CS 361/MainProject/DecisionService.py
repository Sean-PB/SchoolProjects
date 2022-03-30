def readPipeline():
    f = open('decision_pipeline.txt', 'r')
    content = f.read()
    f.close()
    return content


def determinePlayerTotal(playerValues):
    total = 0
    for x in playerValues:
        if x[0].isdigit():
            if x[0] != 1:
                total += int(x[0])
            else:
                total += 10
        elif x[0].isalpha and x[0] != 'A':
            total += 10
    return total
            
            
def determinePlayerAce(playerValues):
    for x in playerValues:
        if x[0] == 'A':
            return True
    return False


def determineDealerHand(dealerValue):
    if dealerValue[0].isdigit():
        if dealerValue[0] != 1:
            dealerValue = int(dealerValue[0])
        else:
            dealerValue = 10
    elif dealerValue[0] == 'A':
        dealerValue = 11
    else:
        dealerValue = 10
    return dealerValue
        

def decide(playerValues, dealerValue, twoCards, ace, total):
    # Decide
    # If player has 2 cards only and a pair
    if twoCards and playerValues[0][0] == playerValues[1][0]:
        return startingPairDecision(total, dealerValue)
    elif ace:
        return playerHasAceDecision(total, dealerValue, twoCards)
    else:
        return noPairNoAceDecision(total, dealerValue, twoCards)


def startingPairDecision(total, dealerValue):
    # 2s or 3s or 7s
    if total == 4 or total == 6 or total == 14:
        if dealerValue < 8:
            return("Split")
        else:
            return("Hit")
    # 4s
    elif total == 8:
        if dealerValue == 5 or dealerValue == 6:
            return("Hit")
        else:
            return("Split")
    # 5s
    elif total == 10:
        if dealerValue < 10:
            return("Double Down")
        else:
            return("Hit")
    # 6s
    elif total == 12:
        if dealerValue < 7:
            return("Split")
        else:
            return("Hit")
    # 9s
    elif total == 18:
        if dealerValue == 7 or dealerValue > 9:
            return("Stand")
        else:
            return("Split")
    # 10s or face cards
    elif total == 20:
        return("Stand")
    # 8s or As
    elif total == 16 or total == 0:
            return("Split")


def playerHasAceDecision(total, dealerValue, twoCards):
    # A, 2 or A, 3
    if total == 2 or total == 3:
        if dealerValue == 5 and dealerValue == 6 and twoCards:
            return("Double Down")
        else:
            return("Hit")
    # A, 4 or A, 5
    elif total == 4 or total == 5:
        if dealerValue > 3 and dealerValue < 7 and twoCards:
            return("Double Down")
        else:
            return("Hit")
    # A, 6
    elif total == 6:
        if dealerValue > 2 and dealerValue < 7 and twoCards:
            return("Double Down")
        else:
            return("Hit")
    # A, 7
    elif total == 7:
        if dealerValue == 2 or dealerValue == 7 or dealerValue == 8:
            return("Stand")
        elif dealerValue > 2 and dealerValue < 7 and twoCards:
            return("Double Down")
        else:
            return("Hit")
    # A, 8-10
    elif total > 7 and total < 11:
        return("Stand")
    # A, 10+ (more than 2 cards)
    else:
        total += 1
        return noPairNoAceDecision(total, dealerValue, twoCards)

        
def noPairNoAceDecision(total, dealerValue, twoCards):
    # Total is 5-8
    if total < 8:
        return("Hit")
    # Total is 9
    elif total == 9:
        if dealerValue > 2 and dealerValue < 7 and twoCards:
            return("Double Down")
        else:
            return("Hit")
    # Total is 10
    elif total == 10:
        if dealerValue < 10 and twoCards:
            return("Double Down")
        else:
            return("Hit")
    # Total is 11
    elif total == 11:
        if dealerValue < 11 and twoCards:
            return("Double Down")
        else:
            return("Hit")
    # Total is 12
    elif total == 12:
        if dealerValue == 4 or dealerValue == 5 or dealerValue == 6:
            return("Stand")
        else:
            return("Hit")
    # Total is 13 - 16
    elif total > 12 and total < 17:
        if dealerValue < 7:
            return("Stand")
        else:
            return("Hit")
    # Total is 17 - 21
    elif total > 16 and total < 22:
        return("Stand")
    # Player busted
    if total > 21:
        return("You Busted")


def sendDecision(decision):
    f = open('decision_pipeline.txt', 'w')
    f.write(decision)
    f.close()


if __name__ == "__main__":
    content = readPipeline()
    playerValues = [i for i in content.split(',')]
    dealerValue = playerValues.pop(0)

    twoCards = True if (len(playerValues) == 2) else False
    ace = determinePlayerAce(playerValues)
    total = determinePlayerTotal(playerValues)

    dealerValue = determineDealerHand(dealerValue)

    sendDecision(decide(playerValues, dealerValue, twoCards, ace, total))