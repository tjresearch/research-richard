x_max = 10
y_max = 10
x_len = 275
y_len = 80
dtd_spawn_rate = 0
car_spawn_rate = 0.5
speed_limit = 11.176

print("large_city")
print()

print(x_max * y_max, 2 * ((x_max - 1) * y_max + (y_max - 1) * x_max), x_max * y_max)
print(dtd_spawn_rate)
print()

for x in range(x_max):
    for y in range(y_max):
        print(x * x_len, y * y_len, 0.5)
print()


def get_index(x, y):
    return x * y_max + y


for x in range(x_max):
    for y in range(y_max):
        for dxy in [(0, -1), (0, 1), (1, 0), (-1, 0)]:
            nx = x + dxy[0]
            ny = y + dxy[1]
            if nx < 0 or nx >= x_max or ny < 0 or ny >= y_max:
                continue
            i = get_index(x, y)
            ni = get_index(nx, ny)
            print(i, ni, speed_limit)
print()

for i in range(x_max * y_max):
    print(i, end=" ")
print()
