import re
import string

#Function to display the menu
def displayMenu():
    print("---------------------------------------------------------------------------")
    print("----------------------------------MAIN MENU--------------------------------")
    print("-------------------Please select an option from the menu:------------------")
    print()
    print("\t1: Diplay all purchased items and their quantities")
    print("\t2: Display the frequency of a specific item")
    print("\t3: Display the histogram for all items")
    print("\t4: Exit the program")
    print("---------------------------------------------------------------------------")
    print("---------------------------------------------------------------------------")
    print()

#Open and read the input file
inventory = dict()
input_file = open("itemsFile.txt", "r")
for line in input_file:
    line = line.strip()
    words = line.split(" ")
    for word in words:
        if word in inventory:
            inventory[word] = inventory[word] + 1
        else:
            inventory[word] = 1
input_file.close()

# Function that prints each item purchased along with its quantity
def printItemsPurchased():
    print("\nQuantity of items purchased\n")
    for item in list(inventory.keys()):
        print(item, end = "")
        print(":", inventory[item])
    print()

# Function that prints a specific item and its quantity
def printSpecificItem(userItem):
    userItem = userItem.capitalize()
    for item in list(inventory.keys()):
        if (userItem == item):
            return inventory[item]
    return 0

# Function that creates a file called frequency.dat and writes the items and their purchased quantities
def newFile(fileToWriteIn):
    input_file = open(fileToWriteIn, "w")
    for item in list(inventory.keys()):
        input_file.write("\n" + item + " " + str(inventory[item]))
    input_file.close()
    return 0