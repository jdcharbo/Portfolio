import tkinter
import math
import random

#Make a function to build the completed sudoku
def puz_maker_helper():
    #Loop that only stops on return
    while True:
        try:
            #Build the list that stores the puzzle and the sets that hold valid choices for individual cells.
            puz = [[0]*9 for i in range(9)]
            rows    = [set(range(1,10)) for i in range(9)]
            columns = [set(range(1,10)) for i in range(9)] 
            boxes = [set(range(1,10)) for i in range(9)]
            for i in range(9):
                for j in range(9):
                    # pick a number for cell (i,j) from the set of remaining available numbers
                    choices = rows[i].intersection(columns[j]).intersection(boxes[math.floor(i/3)*3 + math.floor(j/3)])
                    choice  = random.choice(list(choices))

                    puz[i][j] = choice
        
                    #remove choice from the available options for this row, column, and box.
                    rows[i].discard(choice)
                    columns[j].discard(choice)
                    boxes[math.floor(i/3)*3 + math.floor(j/3)].discard(choice)

            #if we made it here, the sudoku is complete.
            return puz

        #If we get an index error, we want to loop again
        except IndexError:
            pass

# Make a function that makes a sudoku puzzle from a completed sudoku
def puz_maker():
    puz = puz_maker_helper()
    choices = set(range(81))
    while choices!= set():
        check = random.choice(list(choices))
        if is_unique(puz, check, which = 'box') or is_unique(puz, check, which = 'col') or is_unique(puz, check, which = 'row'):
            puz[check%9][math.floor(check/9)] = 0
        choices.discard(check)
    return puz

#Make function to check whether or not a cell in a row, column, or box could possess c's value if c were not defined.
def is_unique(puz, c, which = 'box'):
    
    if which == 'col':
        check_on = c%9
        for i in range(9):
            if i!= check_on:
                if could_be(puz, c, check_on, i): #if (c%9, i) could have c's value, then c isn't unique in its col
                  return False
    elif which == 'row':
        check_on = math.floor(c/9)
        for i in range(9):
            if i!= check_on:
                if could_be(puz, c, i, check_on):#if (i, floor(c/9)) could have c's value, then c isn't unique in its row
                    return False
    elif which == 'box':
        check_on = get_box(c%9, math.floor(c/9))
        check_on_precise = get_cell(c%9, math.floor(c/9))
        for i in range(9):
            if i!= check_on_precise:
                if could_be(puz, c, check_on, i, boxes = True):# if (check_on, i) in the box indexing could have c's value, then c isn't unique in its box
                    return False
    else:
        raise IndexError
    return True

#Make a function to determine if the cell (i, j) could possess c's value.
def could_be(puz, c, i, j, boxes = False):
    if boxes == False:
        if puz[i][j] in set(range(1, 10)):
            return False
        for k in range(9):
            if k!= math.floor(c/9) or i!=c%9: #if (i, k) is not c
                if puz[i][k] == puz[c%9][math.floor(c/9)]:
                    return False
            if k!= c%9 or j!=math.floor(c/9): #if (k, j) is not c
                if puz[k][j] == puz[c%9][math.floor(c/9)]:
                    return False
            if k!= get_cell(c%9, math.floor(c/9)) or get_box(i, j)!=get_box(c%9, math.floor(c/9)): #if (i, k) is not c in the box indexing
                if puz[get_col(get_box(i, j), k)][get_row(get_box(i, j), k)] == puz[c%9][math.floor(c/9)]:
                    return False
    else:
        if puz[get_col(i, j)][get_row(i, j)] in set(range(1, 10)):
            return False
        for k in range(9):
            if k!= math.floor(c/9) or get_col(i, j)!=c%9: #if (i, k) is not c
                if puz[get_col(i, j)][k] == puz[c%9][math.floor(c/9)]:
                    return False
            if k!= c%9 or get_row(i, j)!=math.floor(c/9): #if (k, j) is not c
                if puz[k][get_row(i, j)] == puz[c%9][math.floor(c/9)]:
                    return False
            if k!= get_cell(c%9, math.floor(c/9)) or i!=get_box(c%9, math.floor(c/9)): #if (i, k) is not c in the box indexing
                if puz[get_col(i, k)][get_row(i, k)] == puz[c%9][math.floor(c/9)]:
                    return False
    return True

#Make a function that gets the cell's column when i is box and j is cell in box
def get_col(i, j):
    return (i%3)*3+(j%3)

#Make a function that gets the cell's row when i is box and j is cell in box
def get_row(i, j):
    return math.floor(i/3)*3+math.floor(j/3)

#Make a function that gets the cell's box when i is col and j is row
def get_box(i, j):
    return math.floor(i/3)+math.floor(j/3)*3

#Make a function that gets the cell's index in box when i is col and j is row
def get_cell(i, j):
    return (i%3)+(j%3)*3

#Make an object that represents the Sudoku Board
class SudokuBoard:

    #Make constructor for the Board
    def __init__(self, root, cells):
        
        #Set up storage for the individual cell frames, 3x3 boxes, and entry fields
        self.cells = []
        self.boxes = []
        self.values = []

        #Create the Frame the Sudoku Board lives in
        self.pappy = tkinter.Frame(root, bg = 'Black')

        #Build the cells and entry fields, then append them to cells and values respectively
        for i in range(9):
            self.dummy1 = []
            self.dummy2 = tkinter.Frame(self.pappy, bg = 'Black')
            self.dummy3 = []
            for j in range(9):
                self.dummy1.append(tkinter.Frame(self.dummy2, bg = 'Black'))
                if cells[get_col(i, j)][get_row(i, j)]!=0: 
                    self.dummy3.append(tkinter.Entry(self.dummy1[j], bg='White', width = 2, justify='center', font = 'Arial 20'))
                else:
                    self.dummy3.append(tkinter.Entry(self.dummy1[j], bg='White', fg = 'blue', width = 2, justify='center', font = 'Arial 20'))
            self.cells.append(self.dummy1)
            self.values.append(self.dummy3)
            self.boxes.append(self.dummy2)

        #Remove the helper variables
        del self.dummy1
        del self.dummy2
        del self.dummy3
    
    #function to grid in the board
    def post(self, cells):
        self.pappy.grid(column = 1, row = 1)
        for i in range(9):
            self.boxes[i].grid(column = i%3, row = math.floor(i/3), sticky = ['N', 'S', 'E', 'W'], ipadx = 1, ipady = 1)
            for j in range(9):
                self.cells[i][j].grid(column = j%3, row = math.floor(j/3), sticky = ['N', 'S', 'E', 'W'])
                self.values[i][j].grid(column = 0, row = 0)
        self.init_game(cells)

    #Make function to restrict user input
    def user_restrict(self, input):
        if input.isdigit() and len(input)==1:
            return True
        elif input == '':
            return True
        else:
            return False

    #Make function to block user input in certain cells
    def total_restrict(self, input):
        return False
    
    #Apply total_restrict and user_restrict to cells
    def cell_block(self, cells):
        smol = self.pappy.register(self.user_restrict)
        beeg = self.pappy.register(self.total_restrict)
        for i in range(9):
            for j in range(9):
                if cells[i][j] == 0: 
                    self.values[get_box(i, j)][get_cell(i, j)].config(validate = 'key', validatecommand = (smol, '%P'))
                else:
                    self.values[get_box(i, j)][get_cell(i, j)].config(validate = 'key', validatecommand = (beeg, '%P'))

    #Put the board in its initial state
    def init_game(self, cells):
        for i in range(9):
            for j in range(9):
                if cells[i][j]!=0: 
                    self.values[get_box(i, j)][get_cell(i, j)].insert(0, cells[i][j])
        self.cell_block(cells)

    #Return the text of values[i][j], with i being the box the cell is in, indexed left to right, and j is the cell in the box, indexed left to right
    def get_vals(self, i, j):
        return self.values[i][j].get()

    



# Initialize the window
root = tkinter.Tk()
root.geometry("900x600")

#Make a cells array for post testing
cells = puz_maker()



#Create the Sudoku Board
board = SudokuBoard(root, cells)

# Create empty frames to center the Sudoku Board
tkinter.Frame(root, width = 900, height = 100).grid(column = 0, row = 0, columnspan = 3, sticky = 'N')
tkinter.Frame(root, width = 250, height = 600).grid(column = 0, row = 1, rowspan = 3, sticky = 'E')
tkinter.Frame(root, width = 250, height = 600).grid(column = 2, row = 0, rowspan = 3, sticky = 'W')
bot = tkinter.Frame(root, width = 900, height = 100)
bot.grid(column = 0, row = 2, columnspan = 3, sticky = 'S')

#Add frames to position the checker button
bottop = tkinter.Frame(bot, width = 900, height = 30)
botbot = tkinter.Frame(bot, width = 900, height = 120)
bottop.grid(row = 0, column = 0, sticky = 'N')
botbot.grid(row = 1, column = 0, sticky = 'S')

#Build the label to go with the checker button
checker_display = tkinter.Label(bottop, text = 'Have fun')

#Make a validator to determine if the board is in a valid gamestate
def board_state():
    invalid = False
    complete = True

    #Check Validity of Sudoku Board in boxes
    for i in range(9): #ith box to check
        testy = []
        for j in range(10):
            testy.append(False)
        for j in range(9): #jth element in that box
            if board.get_vals(i, j)!='':
                if testy[int(board.get_vals(i, j))] == False:
                    testy[int(board.get_vals(i, j))] = True
                else:
                    invalid = True
                    print("invalid at box check i = {} and j = {}.".format(i, j))
                    break
            else:
                complete = False
        if invalid == True:
            break

    #Check validity of Sudoku board in columns    
    if invalid == False:
        for i in range(9): #ith column to check
            testy = []
            for j in range(10):
                testy.append(False)
            for j in range(9): #jth element in that column
                if board.get_vals(3*(math.floor(j/3))+(math.floor(i/3)), 3*(j%3)+(i%3))!='':
                    if testy[int(board.get_vals(3*(math.floor(j/3))+(math.floor(i/3)), 3*(j%3)+(i%3)))] == False:
                        testy[int(board.get_vals(3*(math.floor(j/3))+(math.floor(i/3)), 3*(j%3)+(i%3)))] = True
                    else:
                        print("invalid at column check i = {} and j = {}.".format(i, j))
                        invalid = True
                        break
                else:
                    complete = False
            if invalid == True:
                break

        
    #Check validity of Sudoku board in rows   
    if invalid == False:
        for i in range(9): #ith row to check
            testy = []
            for j in range(10):
                testy.append(False)
            for j in range(9): #jth element in that row
                if board.get_vals((math.floor(j/3))+3*(math.floor(i/3)), (j%3)+3*(i%3))!='':
                    if testy[int(board.get_vals((math.floor(j/3))+3*(math.floor(i/3)), (j%3)+3*(i%3)))] == False:
                        testy[int(board.get_vals((math.floor(j/3))+3*(math.floor(i/3)), (j%3)+3*(i%3)))] = True
                    else:
                        invalid = True
                        print("invalid at row check i= {} and j = {}.".format(i, j))
                        break
                else:
                    complete = False
            if invalid == True:
                break
    
    #Return if the board state is invalid > complete > valid.
    if invalid == True:
        checker_display.configure(text = 'The board state is invalid')
    elif complete == True:
        checker_display.configure(text = 'You have successfully completed this puzzle.')
    else:
        checker_display.configure(text = 'The board state is valid.')

#Build the board checker button
checker = tkinter.Button(bottop, text = "Check how you're doing!", command = board_state)
checker.grid(column = 0, row = 0, sticky = 'N')
checker_display.grid(column = 0, row = 1)


#Post the Sudoku Board
board.post(cells)
root.mainloop()
