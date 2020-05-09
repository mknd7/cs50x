from cs50 import get_float

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break

cents = round(change * 100)

coins = cents // 25
cents = cents % 25
coins += cents // 10
cents = cents % 10
coins += cents // 5
cents = cents % 5
coins += cents

print(coins)