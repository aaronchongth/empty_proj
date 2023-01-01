import zenoh
import time


def callback(sample: zenoh.Sample):
    payload = float(sample.value.payload)
    print(f'sub: {sample.key_expr}: {payload} ({sample.value.encoding})')


session = zenoh.open(zenoh.Config())
sub = session.declare_subscriber('room/*/temp', callback)

while True:
    time.sleep(3600)
