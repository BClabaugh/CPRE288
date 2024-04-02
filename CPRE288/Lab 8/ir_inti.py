import numpy as np
from scipy.optimize import curve_fit
import matplotlib.pyplot as plt

# Given arrays of x and y data
x_data = np.array([3015, 2854, 2490, 2176, 1984, 1833,
                   1735, 1622, 1538, 1460, 1401, 1347, 
                   1290, 1234, 1206, 1143, 1100, 1046, 1028])

y_data = np.array([9.00, 10.0, 12.0, 14.0, 16.0, 18.0,
                   20.0, 22.0, 24.0, 26.0, 28.0, 30.0, 
                   33.0, 36.0, 39.0, 42.0, 45.0, 48.0, 51.0])

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
