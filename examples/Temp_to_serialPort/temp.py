# -*- coding: iso-8859-1 -*-
"""
Emulate an oscilloscope.  Requires the animation API introduced in
matplotlib 1.0 SVN.

"""
import numpy as np
import matplotlib as mpl
mpl.use('TKagg')
from matplotlib.lines import Line2D
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import serial

class Scope:
    def __init__(self, ax, maxt=60, dt=0.02):
        self.ax = ax
        self.dt = dt
        self.maxt = maxt
        self.tdata = [0]
        self.ydata = [int(ser.readline())]
        self.line = Line2D(self.tdata, self.ydata)
        self.ax.add_line(self.line)
        self.ax.set_ylim(-.1, 150)
        self.ax.set_xlim(0, self.maxt)

    def update(self, y):
        lastt = self.tdata[-1]
        if lastt > self.tdata[0] + self.maxt: # reset the arrays
            self.tdata = [self.tdata[-1]]
            self.ydata = [self.ydata[-1]]
            self.ax.set_xlim(self.tdata[0], self.tdata[0] + self.maxt)
            self.ax.figure.canvas.draw()

        t = self.tdata[-1] + self.dt
        self.tdata.append(t)
        self.ydata.append(y)
        self.line.set_data(self.tdata, self.ydata)
        return self.line,


def emitter():
    while True:
        v = int(ser.readline())
        yield v
        
ser=serial.Serial("/dev/ttyUSB0", 9600, timeout=1)

fig, ax = plt.subplots()
plt.title('Termometro')
plt.xlabel('Tiempo [seg]')
plt.ylabel('Temperatura [*C]')
scope = Scope(ax)



# pass a generator in "emitter" to produce data for the update func
ani = animation.FuncAnimation(fig, scope.update, emitter, interval=20, blit=True)

ani.save('kThermocouple.gif', writer='imagemagick', fps = 30)


plt.show()
