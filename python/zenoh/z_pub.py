import zenoh
import time

session = zenoh.open(zenoh.Config())
pub = session.declare_publisher('room/bathroom/temp')

while True:
    pub.put(23.2)
    time.sleep(1)