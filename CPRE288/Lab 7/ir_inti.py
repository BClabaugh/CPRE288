import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# Given arrays of x and y data
x_data = np.array([3635.000, 2991.000, 2651.000, 2424.000, 2255.000, 2099.000, 2087.000,
                   1899.000, 1813.000, 1731.000, 1664.000, 1607.000, 1555.000, 1499.000,
                   1467.000, 1411.000, 1391.000, 1369.000, 1331.000, 1297.000, 1347.000,
                   1261.000, 1227.000, 1202.000, 1185.000, 1165.000, 1139.000, 1129.000,
                   1100.000, 1075.000, 1075.000, 1089.000, 1037.000, 1071.000, 1019.000,
                   1043.000, 1137.000, 1035.000, 1011.000, 995.000, 993.000, 991.000,
                   996.000, 947.000, 975.000])

y_data = np.array([0.000, 1.000, 2.000, 3.000, 4.000, 5.000, 6.000, 7.000, 8.000, 9.000,
                   10.000, 11.000, 12.000, 13.000, 14.000, 15.000, 16.000, 17.000, 18.000,
                   19.000, 20.000, 21.000, 22.000, 23.000, 24.000, 25.000, 26.000, 27.000,
                   28.000, 29.000, 30.000, 31.000, 32.000, 33.000, 34.000, 35.000, 36.000,
                   37.000, 38.000, 39.000, 40.000, 41.000, 42.000, 43.000, 44.000])

# Define the exponential function you want to fit
def exponential_func(x, a, b, c):
    return a * np.exp(b * x) + c

# Provide an initial guess for the parameters
initial_guess = [1.0, 0.0001, 1.0]

# Use curve_fit to find the parameters that best fit the data
params, covariance = curve_fit(exponential_func, x_data, y_data, p0=initial_guess)

# Extract the fitted parameters
a, b, c = params

# Output the fitted equation
equation = f"Fitted Exponential Equation: y = {a:.3f} * exp({b:.8f} * x) + {c:.3f}"
print(equation)

# Plot the original data and the fitted curve
plt.scatter(x_data, y_data, label='Original Data')
plt.plot(x_data, exponential_func(x_data, a, b, c), 'r-', label='Fitted Exponential Curve')
plt.legend()
plt.xlabel('x')
plt.ylabel('y')
plt.title('Exponential Curve Fitting Example')
plt.show()
