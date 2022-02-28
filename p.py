import datetime

t=(10, 5, 17, 5, 2020)
x = datetime.datetime(t[4], t[3], t[2], hour=t[1], minute=t[0])


print(x.strftime("%H:%M %Y--%m--%d"))
