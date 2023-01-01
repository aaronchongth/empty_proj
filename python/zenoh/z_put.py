import zenoh

session = zenoh.open(zenoh.Config())
session.put('room/kitchen/temp', 21.5)
session.close()
