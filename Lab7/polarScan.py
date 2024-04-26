import numpy as np
import matplotlib.pyplot as plt
import os
import math


class Obj:
    def __init__(self, width, distance):
        self.width = width
        self.distance = distance


def calcWidth(side_b, side_c, calc_angle):
    b = math.pow(side_b, 2)
    c = math.pow(side_c, 2)
    ang = math.cos(math.radians(calc_angle))
    result = b + c - 2 * side_b * side_c * ang
    return math.sqrt(result)


def polarScan():
    absolute_path = os.path.dirname(__file__)
    relative_path = "./"
    full_path = os.path.join(absolute_path, relative_path)
    filename = 'sensor-scan.txt'
    angle_degrees = []
    angle_radians = []
    ir_distance = []

    distance = []

    file_object = open(full_path + filename,
                       'r')
    file_header = file_object.readline()
    file_data = file_object.readlines()
    file_object.close()

    for line in file_data:
        if line == "END\n":
            print(" ")
        else:
            data = line.split()
            angle_degrees.append(float(data[0]))
            distance.append(float(data[1]))
            ir_distance.append(float(data[2]))

    angle_degrees = np.array(angle_degrees)
    angle_radians = (np.pi/180) * angle_degrees
    edge = 0
    start_angle = 0
    end_angle = 0
    objs = []
    start_distance = 0
    for i, dist in enumerate(distance):
        if dist < 40 and edge == 0:
            edge += 1
            start_angle = angle_degrees[i]
            start_distance = dist
        elif dist < 40 and edge == 1:
            continue
        elif dist > 40 and edge == 0:
            continue
        else:
            edge = 0
            end_angle = angle_degrees[i - 1]
            angle = end_angle - start_angle
            o = Obj(calcWidth(start_distance, distance[i - 1], angle), min(distance[i - 1], start_distance))
            objs.append(o)

    for obj in objs:
        print(obj.width, obj.distance)

    # Create a polar plot
    fig, ax = plt.subplots(subplot_kw={'projection': 'polar'})  # One subplot of type polar
    ax.plot(angle_radians, distance, color='r',
            linewidth=2.0)
    ax.plot(angle_radians, ir_distance, color='g',
            linewidth=2.0)
    # Plot distance verse angle (in radians), using red, line width 4.0
    ax.set_xlabel('Distance (cm)', fontsize=14.0)  # Label x axis
    ax.set_ylabel('Angle (degrees)', fontsize=14.0)  # Label y axis
    ax.xaxis.set_label_coords(0.5, 0.15)  # Modify location of x axis label (Typically do not need or want this)
    ax.tick_params(axis='both', which='major', labelsize=14)  # set font size of tick labels
    ax.set_rmax(100)  # Saturate distance at 2.5 meters
    ax.set_rticks([0,20,40,60,80,100,])  # Set plot "distance" tick marks at .5, 1, 1.5, 2, and 2.5 meters
    ax.set_rlabel_position(-22.5)  # Adjust location of the radial labels
    ax.set_thetamax(180)  # Saturate angle to 180 degrees
    ax.set_xticks(np.arange(0, np.pi + .1,
                            np.pi / 4))  # Set plot "angle" tick marks to pi/4 radians (i.e., displayed at 45 degree) increments
    # Note: added .1 to pi to go just beyond pi (i.e., 180 degrees) so that 180 degrees is displayed
    ax.grid(True)  # Show grid lines

    # Create title for plot (font size = 14pt, y & pad controls title vertical location)
    ax.set_title("180 Polar Plot of Scan", size=10, y=1.0, pad=-24)

    plt.show()  # Display plot





polarScan()
