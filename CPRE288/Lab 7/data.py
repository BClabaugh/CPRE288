data = """3635.000        0.000
2991.000        1.000
2651.000        2.000
2424.000        3.000
2255.000        4.000
2099.000        5.000
2087.000        6.000
1899.000        7.000
1813.000        8.000
1731.000        9.000
1664.000        10.000
1607.000        11.000
1555.000        12.000
1499.000        13.000
1467.000        14.000
1411.000        15.000
1391.000        16.000
1369.000        17.000
1331.000        18.000
1297.000        19.000
1347.000        20.000
1261.000        21.000
1227.000        22.000
1202.000        23.000
1185.000        24.000
1165.000        25.000
1139.000        26.000
1129.000        27.000
1100.000        28.000
1075.000        29.000
1075.000        30.000
1089.000        31.000
1037.000        32.000
1071.000        33.000
1019.000        34.000
1043.000        35.000
1137.000        36.000
1035.000        37.000
1011.000        38.000
995.000         39.000
993.000         40.000
991.000         41.000
996.000         42.000
947.000         43.000
975.000         44.000"""

# Split the data into lines and then into individual values
rows = [line.split() for line in data.split('\n')]

# Extract the values in each column
column1 = [row[0] for row in rows]
column2 = [row[1] for row in rows]

# Join the values in each column with commas
row1 = ','.join(column1)
row2 = ','.join(column2)

# Print the result
print(row1)
print(row2)