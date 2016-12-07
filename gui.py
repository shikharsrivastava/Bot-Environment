import pygame,sys
from pygame.locals import *
import random
import time
from math import log
import subprocess

pygame.init()
DISPLAY = pygame.display.set_mode((800,800))
pygame.display.set_caption('Checkers')
BLACK = (0,0,0)
WHITE = (255, 255, 255)
RED= (255,0,0)
GREEN = (0, 255,0)
BLUE = (0,0, 255)
AQUA=(0, 255, 255)
FUCHSIA=(255,0, 255)
GRAY=(128, 128, 128)
OLIVE=(128, 128,0)
PURPLE=(128,0, 128)
YELLOW=(255, 255,0)
TEAL=( 0, 128, 128)
row=8
col=8
WIDTH=120
INITIAL_X=120
INITIAL_Y=80
SIDE=80
DISPLAY.fill(WHITE)
col1=WHITE
col2=BLACK
currentColor = col1
colboard=[]
bbw  = 0
bbb = 0
side = 'W'
def convertPos(pos):
    row=pos/8
    col=pos%8
    return ((7-row)*8+col)

def buildSquare(i,j):
    pygame.draw.rect(DISPLAY,currentColor,(i-SIDE/2,j-SIDE/2,SIDE,SIDE))

def init():
    global currentColor;
    pygame.draw.rect(DISPLAY,BLACK,(INITIAL_X-SIDE/2,INITIAL_Y-SIDE/2,SIDE*8,SIDE*8),5)
    for i in range(0,8):
        if i%2==0:
            currentColor=col1
        else:
            currentColor=col2
        for j in range(0,8):
            x=INITIAL_X+j*SIDE
            y=INITIAL_Y+i*SIDE
            buildSquare(x,y)
            colboard.append(currentColor)
            currentColor=col2 if currentColor==col1 else col1

def first():
    black = 0
    for i in range(1, 8, 2):
        row = i / 8
        col = i % 8
        pos = convertPos(i)
        black |= (1 << pos)
    for i in range(8, 15, 2):
        row = i / 8
        col = i % 8
        black |= (1 << convertPos(i))
    for i in range(17, 24, 2):
        row = i / 8
        col = i % 8
        black |= (1 << convertPos(i))

    white = 0;
    for i in range(40, 47, 2):
        row = i / 8
        col = i % 8
        white |= (1 << convertPos(i))
    for i in range(49, 56, 2):
        row = i / 8
        col = i % 8
        white |= (1 << convertPos(i))
    for i in range(56, 63, 2):
        row = i / 8
        col = i % 8
        white |= (1 << convertPos(i))
    return (white, black)

def genFen(white, black, side):
    board = [[0 for _ in range(8)] for _ in range(8)]
    while white > 0:
        pos = int(log(white & -white, 2))
        pos = convertPos(pos)
        row = pos / 8
        col = pos % 8
        board[row][col] = 1
        white -= white & -white
    while black > 0:
        pos = int(log(black & -black, 2))
        pos = convertPos(pos)
        row = pos / 8
        col = pos % 8
        board[row][col] = 2
        black -= black & -black
    fen = ''
    for i in range(8):
        row = ''
        count = 0
        for j in range(8):
            if board[i][j] == 0:
                count += 1
            elif board[i][j] == 1:
                if count > 0:
                    row = row + str(count)
                row = row + 'D'
                count = 0
            elif board[i][j] == 2:
                if count > 0:
                    row = row + str(count)
                row = row + 'd'
                count = 0
        if count > 0:
            row = row + str(count)
        row = row + '/'
        fen = fen + row
    fen = fen + side
    return fen

def makeBoard(white, black):
    init()
    while white > 0:
        pos = int(log(white & - white, 2))
        pos = convertPos(pos)
        row = pos / 8
        col = pos % 8
        pygame.draw.circle(DISPLAY, GREEN, (INITIAL_X+col*SIDE, INITIAL_Y+row*SIDE), SIDE/3)
        white -= white & (-white)
    while black > 0:
        pos = int(log(black & - black, 2))
        pos = convertPos(pos)
        row = pos / 8
        col = pos % 8
        pygame.draw.circle(DISPLAY, RED, (INITIAL_X+col*SIDE, INITIAL_Y+row*SIDE), SIDE/3)
        black -= black & (-black)

def isValid(move, exe):
    fen = genFen(bbw, bbb, side)
    out = subprocess.check_output([exe, 'fen', fen, 'isvalid', move])
    out = out.split()
    if out[0] == '0':
        return False
    else:
        bbw, bbb = int(out[1]), int(out[2])
        return True

def bestMove(bw, bb, side, exe):
    fen = genFen(bw, bb, side)
    out = subprocess.check_output([exe, 'fen', fen, 'best'])
    out = out.split()
    return map(int, out)

def botfight():
    bw, bb = first()
    makeBoard(bw, bb)
    pygame.display.update()
    side = 'W'
    while True:
        bw, bb = bestMove(bw, bb, side, './a.out')
        if bw == -1 and bb == -1:
            print "Game over, {} loses".format(side)
            break
        else:
            makeBoard(bw, bb)
            pygame.display.update()
            time.sleep(0.5)
            side = 'B' if side == 'W' else 'W'

if __name__ == "__main__":
    botfight()

"""
white, black = first()
bbw = white
bbb = black
makeBoard(bbw, bbb)
print(genFen(bbw, bbb, 'W'))

prev = None
killed = 0
move = 0
while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            sys.exit(0)
        elif event.type==MOUSEBUTTONDOWN:
            mousePos=list(pygame.mouse.get_pos())
            mousePos[0]-=INITIAL_X-SIDE/2;
            mousePos[1]-=INITIAL_Y-SIDE/2;
            col=mousePos[0]/SIDE
            row=mousePos[1]/SIDE
            if 0<=row<=7 and 0<=col<=7:
                print row, col
                if prev == None:
                    pos = convertPos(row*8+col)
                    move |= pos
                    prev = pos
                    print "prev = ", prev
                else:
                    cur = convertPos(row*8+col)
                    print cur, prev
                    if cur - prev == 7 or cur - prev == 9:
                        print "hello"
                        move |= (cur << 6)
                    elif cur - prev == 14:
                        killed += 1
                        s = 0
                        for i in range(6, 16):
                            s += (1 << i)
                        move = move & (~s)
                        move |= (cur << 6)
                        move |= (killed << 12)
                    elif cur - prev == 18:
                        move |= (1 << (killed + 17))
                        killed += 1
                        s = 0
                        for i in range(6, 16):
                            s += (1 << i)
                        move = move & (~s)
                        move |= (cur << 6)
                        move |= (killed << 12)
                    else:
                        s = 0
                        for i in range(6, 12):
                            s += (1 << i)
                        move = move & (~s)
                        move |= (cur << 6)
                    prev = cur
                    if (isValid(move, './a.out')):
                        makeBoard(bbw, bbb)
                    print((move & 0x3f), ((move >> 6) & 0x3f), ((move >> 12) & 0xf))
                    killed = ((move >> 12) & 0xf)
                    for i in range(killed):
                        print ((move >> (17+i)) & 1)
            else:
                prev = None
                killed = 0
                move = 0

    pygame.display.update()
"""
